#include "config.h"
#include "bot.h"
#include "curl_handle.h"

#include <optional>

void Bot::send_message(const std::string &message)
{
    auto url = bot_url + "sendMessage?chat_id=" + Config::chat_id + "&text=" +
        Curl::escape(message);

    std::string result;
    auto code = Curl::perform(result, url);
    if (code != CURLE_OK) {
        curl_easy_strerror(code);
    }
}
