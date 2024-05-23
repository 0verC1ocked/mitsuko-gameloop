#pragma once

#include <mutex>

/**
 * A chunk within a larger block.
 */
struct Chunk {
  Chunk *next;
};

class PoolAllocator {
public:
  PoolAllocator(size_t chunksPerBlock) : mChunksPerBlock(chunksPerBlock) {}
  void *allocate(size_t size);
  void deallocate(void *ptr, size_t size);

  int number_of_allocs = 0;
  int number_of_deallocs = 0;
  int free_spaces_left = 0;

private:
  /**
   * Number of chunks per larger block.
   */
  size_t mChunksPerBlock;
  std::mutex mtx; // Mutex for thread safety

  /**
   * Allocation pointer.
   */
  Chunk *mAlloc = nullptr;

  /**
   * Allocates a larger block (pool) for chunks.
   */
  Chunk *allocateBlock(size_t chunkSize);
};

extern PoolAllocator *g_match_model_allocator;
extern PoolAllocator *g_enet_allocator;
