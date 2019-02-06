/*
    Copyright (C) 2018 Yağmur Oymak

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef TELEGRAM_NOTIFIER_CONFIG_HPP
#define TELEGRAM_NOTIFIER_CONFIG_HPP

#include <string>

namespace Config {

/*
 * Set token and chat_id according to the config file.
 * Config file must include both the API token and the chat id.
 * Returns true on success, false on failure.
 *
 * TODO: Also get the port number from the config file.
 */
bool parse_config(std::string path = "/etc/telegrambotd.conf");

/*
 * Set by parse_config(), according to the config file.
 */
inline std::string token;
inline std::string chat_id;

constexpr inline unsigned short port = 6666;

}

#endif /* TELEGRAM_NOTIFIER_CONFIG_H */
