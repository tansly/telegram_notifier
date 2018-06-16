#ifndef TELEGRAM_NOTIFIER_BOT_H
#define TELEGRAM_NOTIFIER_BOT_H

#include "config.h"

#include <string>

namespace Bot {

    static const std::string bot_url =
        std::string("https://api.telegram.org/bot") + Config::token + "/";

    void send_message(const std::string &);

}

#endif /* TELEGRAM_NOTIFIER_BOT_H */
