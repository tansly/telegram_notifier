# telegram_notifier

A Telegram bot that I use to send notifications from my servers to my phone.
Listens TCP port 6666 on the machine for "notifications", which are (hopefully) plain text.
Sends whatever it receives in a Telegram message.
Callbacks can be defined to trigger code when certain commands are sent to the bot.
There are a few commands right now, which are:
* `/pause`: Pauses all messages sent by the bot. Messages will be stored in a queue
instead and will be sent when a `/continue` is received.
* `/continue`: Resumes normal operation of the bot and sends all messages waiting
in the queue that were stored when the bot was paused.
* `/notifyoff`: Disables chat notifications. Sets the `disable_notification`
parameter of the `sendMessage` method of the bot API.
* `/notifyon`: Reenables chat notifications. (Notifications are enabled by default)

# Requirements
* Boost
* jsoncpp
* cmake

# TODO

* Configuration: Use a config file for configuration; port, API key etc.
* What else?
