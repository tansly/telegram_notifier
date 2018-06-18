#ifndef TELEGRAM_NOTIFIER_GLOBAL_H
#define TELEGRAM_NOTIFIER_GLOBAL_H

#include <mutex>

namespace Global {

extern std::mutex cout_mutex;
extern std::mutex cerr_mutex;

}

#endif /* TELEGRAM_NOTIFIER_GLOBAL_H */
