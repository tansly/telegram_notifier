#include "bot.h"
#include "config.h"
#include "curl_handle.h"

#include <iostream>
#include <thread>
#include <utility>

int main(int argc, char **argv)
{
    Bot::send_message("Hello, Yağmur!");

    return 0;
}
