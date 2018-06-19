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

#ifndef TELEGRAM_NOTIFIER_BOT_H
#define TELEGRAM_NOTIFIER_BOT_H

#include "config.h"

#include <functional>
#include <optional>
#include <json/json.h>
#include <string>

namespace Bot {

static const std::string bot_url = std::string("https://api.telegram.org/bot") + Config::token + "/";

void send_message(const std::string &message, bool notify=true);

std::optional<Json::Value> get_updates(int offset=0, int timeout=60);

/*
 * TODO: What if we want to pass parameters to callbacks?
 */
void register_callback(std::string command, std::function<void(void)> callback);

/*
 * Update handling loop for the bot.
 * Blocks forever, polls updates and handles incoming commands using
 * registered callbacks.
 */
void update_handler();

}

#endif /* TELEGRAM_NOTIFIER_BOT_H */
