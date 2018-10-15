#include "rt_shm_ring.h"

void ring_push(rt_shm_ring_info_t* ring , void* addr, size_t len)
{
    rt_shm_blk_info_t* last_blk;
    rt_shm_blk_info_t* next_blk;
    size_t consume;

    last_blk = (rt_shm_blk_info_t *)(ring + ring->last_blk_offset);

    next_blk = (rt_shm_blk_info_t *)last_blk->end_addr_offset;
    next_blk->start_addr_offset = last_blk->end_addr_offset;
    next_blk->end_addr_offset = next_blk->start_addr_offset + MM_ALIGN_UP(sizeof(rt_shm_blk_info_t)) + MM_ALIGN_UP(len);

    if (next_blk->end_addr_offset > ring->pool_end_offset){
        consume = next_blk->end_addr_offset - next_blk->start_addr_offset;
        /* data sperated at the ending address.*/
        memcpy(ring+next_blk->start_addr_offset,addr,ring->pool_end_offset-next_blk->start_addr_offset);
        next_blk->end_addr_offset = next_blk->end_addr_offset - ring->pool_end_offset + ring->pool_start_offset;
        memcpy(ring->pool_start_offset,addr+ring->pool_end_offset-next_blk->start_addr_offset,len-ring->pool_end_offset+next_blk->start_addr_offset);
    }else if(ring->pool_end_offset - next_blk->end_addr_offset < MM_ALIGN_UP(sizeof(rt_shm_blk_info_t))){
        /* To avoid blk struct sperated at the ending address.*/        
        next_blk->end_addr_offset = ring->pool_end_offset;
        consume = next_blk->end_addr_offset - next_blk->start_addr_offset;
        memcpy(next_blk->start_addr_offset,addr,len);
    }

    

    ring->last_blk_offset = last_blk->end_addr_offset;
    ring->left-=consume;
}

void ring_pop(rt_shm_ring_info_t *ring, void* addr, size_t *len)
{
    rt_shm_blk_info_t* first_blk;

    if(first_blk->end_addr_offset < first_blk->start_addr_offset){
        memcpy(addr,first_blk->start_addr_offset,ring->pool_end_offset-first_blk->start_addr_offset);
        memcpy(addr+ring->pool_end_offset-first_blk->start_addr_offset,ring->pool_start_offset,len-ring->pool_end_offset+first_blk->start_addr_offset);
    }else{
        memcpy(addr,first_blk->start_addr_offset,first_blk->length);
    }
    *len = first_blk->length;

    ring->first_blk_offset = first_blk->end_addr_offset;
    ring->left += first_blk->a_len;
    --ring->num;
}
