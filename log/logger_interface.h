#pragma once

#include "logger.h"

namespace basic {
#define LDebug(mod)      ::basic::Logger::debug(CODE_FROM_HERE, mod)
#define LInfo(mod)       ::basic::Logger::info(CODE_FROM_HERE, mod)
#define LWarning(mod)    ::basic::Logger::warning(CODE_FROM_HERE, mod)
#define LError(mod)      ::basic::Logger::error(CODE_FROM_HERE, mod)
#define LStats(mod)      ::basic::Logger::stats(CODE_FROM_HERE, mod)
}