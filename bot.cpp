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

#include "config.h"
#include "bot.h"
#include "curl_handle.h"
#include "global.h"

#include <iostream>
#include <mutex>
#include <string>

extern std::mutex cerr_mutex;

void Bot::send_message(const std::string &message)
{
    auto url = bot_url + "sendMessage?chat_id=" + Config::chat_id + "&text=" +
        Curl::escape(message);

    std::string result;
    auto code = Curl::perform(result, url);
    if (code != CURLE_OK) {
        std::lock_guard<std::mutex> lock(Global::cerr_mutex);

        std::cerr << curl_easy_strerror(code);
    }
}
