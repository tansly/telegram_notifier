cmake_minimum_required (VERSION 3.11.2)

project (telegram_notifier)

set (CMAKE_CXX_STANDARD 17)

set (THREADS_PREFER_PTHREAD_FLAG ON)
find_package (Threads REQUIRED)
find_package (jsoncpp REQUIRED)
find_package (CURL REQUIRED)
find_package (Boost COMPONENTS system REQUIRED)
include_directories (src/)

set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

# XXX: Is there a proper way to set -pthread while compiling all files?
# This is a workaround to set it for all files. Without this it is only set for telegram_notifier.cpp.
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

set (BOT_SOURCES
    src/bot/bot.cpp
    )
set (CURL_HANDLE_SOURCES
    src/curl_handle/curl_handle.cpp
    )
set (GLOBAL_SOURCES
    src/global/global.cpp
    )
set (TELEGRAM_NOTIFIER_SOURCES
    src/telegram_notifier.cpp
    )

add_library (bot_lib
    ${BOT_SOURCES}
    )
add_library (curl_handle_lib
    ${CURL_HANDLE_SOURCES}
    )
add_library (global_lib
    ${GLOBAL_SOURCES}
    )

add_executable (telegrambotd ${TELEGRAM_NOTIFIER_SOURCES})
# XXX: Why the fuck -ljsoncpp is not added? This crap is completely braindead.
target_link_libraries (telegrambotd bot_lib global_lib curl_handle_lib ${CURL_LIBRARIES} ${Boost_SYSTEM_LIBRARIES} ${JSONCPP_LIBRARIES} Threads::Threads -ljsoncpp)
