#ifndef RT_SHM_RING_H
#define RT_SHM_RING_H

#include "linux/types.h"

typedef struct _rt_shm_blk_info_t{
    size_t start_addr_offset;
    size_t end_addr_offset;
}rt_shm_blk_info_t;

typedef struct _rt_shm_ring_info_t{
    size_t left;
    size_t pool_start_offset;
    size_t pool_end_offset;
    //rt_shm_blk_info_t* first_blk;  cant use virtual address.
    //rt_shm_blk_info_t* last_blk;
    size_t first_blk_offset;
    size_t last_blk_offset;
}rt_shm_ring_info_t;



#endif
