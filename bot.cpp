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
#include <json/json.h>
#include <memory>
#include <mutex>
#include <optional>
#include <string>
#include <sstream>

void Bot::send_message(const std::string &message)
{
    auto url = bot_url + "sendMessage?chat_id=" + Config::chat_id + "&text=" +
        Curl::escape(message);

    std::string result;
    auto code = Curl::perform(result, url);
    if (code != CURLE_OK) {
        std::lock_guard<std::mutex> lock {Global::cerr_mutex};

        std::cerr << "Bot::send_message(): " << curl_easy_strerror(code) << std::endl;
    }

    /*
     * TODO: Check the result object and print some error message
     * if the Telegram api responded with an error.
     */
}

std::optional<Json::Value> Bot::get_updates(int offset, int timeout)
{
    std::string curl_result;
    std::ostringstream url_stream {bot_url + "getUpdates?", std::ios_base::ate};

    url_stream << "timeout=" << timeout << '&';
    url_stream << "offset=" << offset << '&';

    auto code = Curl::perform(curl_result, url_stream.str());
    if (code != CURLE_OK) {
        std::lock_guard<std::mutex> lock {Global::cerr_mutex};

        std::cerr << "Bot::get_updates(): " << curl_easy_strerror(code) << std::endl;

        return {};
    }

    Json::CharReaderBuilder builder;
    std::unique_ptr<Json::CharReader> reader {builder.newCharReader()};
    Json::Value updates;
    std::string errors;
    if (!reader->parse(curl_result.c_str(), curl_result.c_str() + curl_result.size(),
                &updates, &errors)) {

        std::lock_guard<std::mutex> lock {Global::cerr_mutex};

        std::cerr << "Bot::get_updates(): " << errors << std::endl;

        return {};
    }

    return {updates};
}
