#ifndef MY_PREFETCHER_H
#define MY_PREFETCHER_H


#include <unordered_map>
#include <cstdint>
#include "cache.h"

namespace my_prefetcher {
    bool isInWindow(uint64_t addr);
}



#endif