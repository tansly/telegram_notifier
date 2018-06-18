#include "global.h"

#include <mutex>

namespace Global {

std::mutex cout_mutex;
std::mutex cerr_mutex;

}
