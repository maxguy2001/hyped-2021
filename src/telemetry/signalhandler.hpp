/*
 * Author: Neil Weidinger
 * Organisation: HYPED
 * Date: May 2019
 * Description:
 *
 *    Copyright 2019 HYPED
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

#ifndef TELEMETRY_SIGNALHANDLER_HPP_
#define TELEMETRY_SIGNALHANDLER_HPP_

#include "utils/logger.hpp"

namespace hyped {

using utils::Logger;

namespace telemetry {

class SignalHandler {
  public:
    SignalHandler();
    static bool gotSigPipeSignal();

  private:
    static void sigPipeHandler(int signum);
    static bool receivedSigPipeSignal;
    static Logger log_;
};

}  // namespace telemetry
}  // namespace hyped

#endif  // TELEMETRY_SIGNALHANDLER_HPP_
