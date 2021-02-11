/*
 * Author: Neil Weidinger
 * Organisation: HYPED
 * Date: March 2019
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

#ifndef TELEMETRY_CLIENT_HPP_
#define TELEMETRY_CLIENT_HPP_

#include <string>
#include "telemetry/signalhandler.hpp"
#include "utils/logger.hpp"
#include "utils/config.hpp"

namespace hyped {

using utils::Logger;
using utils::Config;

namespace telemetry {

class Client {
  public:
    explicit Client(Logger& log);
    ~Client();
    bool connect();
    bool sendData(std::string message);
    std::string receiveData();

  private:
    Client(Logger& log, const utils::Config& config);

    Logger& log_;
    int sockfd_;
    const char* kPort;
    const char* kServerIP;
};

}  // namespace client
}  // namespace hyped

#endif  // TELEMETRY_CLIENT_HPP_
