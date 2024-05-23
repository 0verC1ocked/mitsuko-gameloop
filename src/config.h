#pragma once

#include <cstdint>

enum Config : long {
    GAME_LOOP_TIME = 10,
};

enum PoolAllocatorConfig : uint32_t {
  CHUNKS_PER_BLOCK_MM = 2050,
};
