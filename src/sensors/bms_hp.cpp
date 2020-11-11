/*
 * Authors: Ivan Zhong
 * Organisation: HYPED
 * Date:
 * Description: WORK IN PROGRESS
 *
 *    Copyright 2020 HYPED
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#include "sensors/bms_hp.hpp"

#include "utils/logger.hpp"
#include "utils/timer.hpp"

namespace hyped {

    namespace sensors {

//        std::vector<uint16_t> BMSHP::existing_ids_;   // NOLINT [build/include_what_you_use]

        BMSHP::BMSHP(uint16_t id, Logger& log)
                : log_(log),
                  can_id_(id*2 + bms::kHPBase), //Not used for now
                  thermistor_id_(id + bms::kThermistorBase),
                  cell_id_(id + bms::kCellBase),
                  local_data_ {},
                  last_update_time_(0)
        {
//            // verify this BMSHP unit has not been instantiated
//            for (uint16_t i : existing_ids_) {
//                if (id == i) {
//                    log_.ERR("BMSHP", "BMSHP %d already exists, duplicate unit instantiation", id);
//                    return;
//                }
//            }
//            existing_ids_.push_back(id);

            // tell CAN about yourself
            Can::getInstance().registerProcessor(this);
            Can::getInstance().start();
        }

        bool BMSHP::isOnline()
        {
            // consider online if the data has been updated in the last second
            return (utils::Timer::getTimeMicros() - last_update_time_) < 1000000;
        }

        void BMSHP::getData(BatteryData* battery)
        {
            *battery = local_data_;
        }

        bool BMSHP::hasId(uint32_t id, bool extended)
        {
            // HPBMS
//            if (id == can_id_ || id == static_cast<uint16_t>(can_id_ + 1)) return true;

            if (id == kHPBMSIdBase) return true;

            return false;
        }

        void BMSHP::processNewData(utils::io::can::Frame& message)
        {
            // OLD HP CODE START
            // thermistor expansion module
//            if (message.id == thermistor_id_) {   // C
//                local_data_.low_temperature     = message.data[1];
//                local_data_.high_temperature    = message.data[2];
//                local_data_.average_temperature = message.data[3];
//            }
//
//            log_.DBG2("BMSHP", "High Temp: %d, Average Temp: %d, Low Temp: %d",
//                      local_data_.high_temperature,
//                      local_data_.average_temperature,
//                      local_data_.low_temperature);


            //is BMS_HCU_INFO event
            //message structure:
            //[BatVoltage, BatCurrent, BatSoc, BatSoh, BatState, BatAlmLv]
            //BatState:             BatAlmLv:
            //       1:Sleep                0: No Alarm
            //       2:Power Up             1: Level 1 Alarm (most serious)
            //       3:Standby              2: Level 2 Alarm
            //       4:Pre-charge           3: Level 3 Alarm
            //       5:Run                  4: Level 4 Alarm
            //       6:Shutdown
            //       7:Error
            if (message.id == kHPBMSIdBase){
                local_data_.voltage = (message.data[0] << 8) | message.data[1];    //V
                local_data_.current = (message.data[2] << 8) | message.data[3];    //A
                local_data_.soc = message.data[4];                                 //%
                local_data_.soh = message.data[5];                                 //%
                local_data_.batState = message.data[6] & 0x0F;
                local_data_.batAlmLv = message.data[6] >> 4;
            }

            log_.DBG2("BMSHP", "received data BatVoltage,BatCurrent,BatSoc,BatSoh,BatState,BatAlmLv: %u,%u,%u,%u,%u,%u",
                      local_data_.voltage,
                      local_data_.current,
                      local_data_.soc,
                      local_data_.soh,
                      local_data_.batState,
                      local_data_.batAlmLv);
        }
    }}  // namespace hyped::sensors

