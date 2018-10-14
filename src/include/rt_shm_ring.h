#ifndef RT_SHM_RING_H
#define RT_SHM_RING_H

typedef struct _rt_shm_ring_info_t{
    int blk_num;
    int pool_size;
    int pool_start_offset;
    int pool_end_offset;

    int first_blk;
    int last_blk;
}rt_shm_ring_info_t;

typedef struct _rt_shm_blk_info_t{
    bool avail;
    int length;
}rt_shm_blk_info_t;

#endif
