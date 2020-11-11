/*
 * Authors: Ivan Zhong
 * Organisation: HYPED
 * Date:
 * Description: WORK IN PROGRESS
 *
 * Configuration and local data structure are encapsulated in namespace bms.
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

#ifndef SENSORS_BMS_HP_HPP_
#define SENSORS_BMS_HP_HPP_

#include <cstdint>
#include <vector>

#include "sensors/interface.hpp"
#include "utils/concurrent/thread.hpp"
#include "utils/io/can.hpp"
#include "utils/system.hpp"
#include "utils/utils.hpp"

namespace hyped {

    // Forward declarations
    namespace utils { class Logger; }
    namespace utils { namespace io { class Can; } }
    namespace utils { namespace io { class CanProccesor; } }
    namespace utils { namespace io { namespace can { struct Frame; } } }

    namespace sensors {

        using utils::Logger;
        using utils::io::Can;
        using utils::io::CanProccesor;
        using utils::concurrent::Thread;
        using data::Data;

        namespace bms {
            // how often shall request messages be sent (from old code)
            constexpr uint32_t kFreq    = 4;           // in Hz
            constexpr uint32_t kPeriod  = 1000/kFreq;  // in milliseconds

            /**
             * HP BMS BaseID:
             *    ID:  390
             *    Hex: 0x186
             *
             * Event ID:
             *    BMS_HCU_INFO: 0x186040F3
             */

            constexpr uint64_t kHPBMSIdBase      = 0x186040F3 //HP BMS based id

        }  // namespace bms

        class BMSHP : public CanProccesor, public BMSInterface {
            friend Can;

            public:
                /**
                 * @brief Construct a new BMSHP object
                 * @param id  - !!!NOT USED FOR NOW!!!
                 * @param log - logger for message output
                 */
                BMSHP(uint16_t id, Logger& log = utils::System::getLogger());

                // from BMSInterface
                bool isOnline() override;
                void getData(BatteryData* battery) override;

                // from CanProcessor
                bool hasId(uint32_t id, bool extended) override;

            private:
                void processNewData(utils::io::can::Frame& message) override;

            private:
                Logger&         log_;
                uint16_t        can_id_;            // CAN id to be used
                //uint64_t        thermistor_id_;     // thermistor expansion module CAN id
                //uint16_t        cell_id_;           // broadcast message ID
                BatteryData     local_data_;        // stores values from CAN
                uint64_t        last_update_time_;  // stores arrival time of CAN message
                // for making sure only one object per BMS unit exist
                static std::vector<uint16_t> existing_ids_;
                NO_COPY_ASSIGN(BMSHP);
            };

    }}  // namespace hyped::sensors

#endif //SENSORS_BMS_HP_HPP_
