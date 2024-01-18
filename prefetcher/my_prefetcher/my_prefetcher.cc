#include "cache.h"
#include "my_prefetcher.h"

namespace my_prefetcher
{
#define MAX_WINDOW_SIZE 16
    std::unordered_map<uint64_t, uint16_t> addr_map;
    uint64_t addr_list[MAX_WINDOW_SIZE] = {};
    uint16_t curr = 15;
    uint16_t start = 0;
    uint16_t end = 0;
    void updateWindow(uint64_t addr)
    {
        uint64_t no = addr >> LOG2_BLOCK_SIZE;
        if(addr_map.find(no) != addr_map.end())
        {
            uint16_t last = curr;
            curr = addr_map[no];
            // 如果是从某处跳转到前面的，更新工作窗口
            if(last == end)
            {
                uint16_t tmp = start;
                while(tmp != curr)
                {
                    addr_map.erase(addr_list[tmp]);
                    tmp = (tmp + 1) % MAX_WINDOW_SIZE;
                }
                start = curr;
            }
        }
        else
        {
            // curr向后移动
            curr = (curr + 1) % MAX_WINDOW_SIZE;
            // 如果工作窗口已满，则从map中删除
            if(addr_map.size() == MAX_WINDOW_SIZE)
                addr_map.erase(addr_list[curr]);
            // 将当前地址加入工作窗口
            addr_map[no] = curr;
            addr_list[curr] = no;
            end = curr;
        }
    }
    uint64_t getNextAddr()
    {
        if(curr == end)
            return addr_list[start];
        else
            return addr_list[(curr + 1) % MAX_WINDOW_SIZE];
    }
    bool isInWindow(uint64_t addr)
    {
        if(addr_map.find(addr >> LOG2_BLOCK_SIZE) != addr_map.end())
            return true;
        else
            return false;
    }
}



void CACHE::prefetcher_initialize() {}

void CACHE::prefetcher_cycle_operate() {}

uint32_t CACHE::prefetcher_cache_operate(uint64_t addr, uint64_t ip, uint8_t cache_hit, bool useful_prefetch, uint8_t type, uint32_t metadata_in)
{
    my_prefetcher::updateWindow(addr);
    prefetch_line(my_prefetcher::getNextAddr(), true, metadata_in);
  return metadata_in;
}

uint32_t CACHE::prefetcher_cache_fill(uint64_t addr, uint32_t set, uint32_t way, uint8_t prefetch, uint64_t evicted_addr, uint32_t metadata_in)
{
  return metadata_in;
}

void CACHE::prefetcher_final_stats() {}
