#include "stdio.h"
#include "stdlib.h"
#include "sys/shm.h"

#include "rt_shm_ring.h"
#include "rt_shm.h"

uint8_t rt_shm_create(int key,size_t len){
    rt_shm_ring_info_t* ring;
    
    if(len < sizeof(rt_shm_ring_info_t)){
        return -1;
    }
    
    ring = (rt_shm_blk_info_t*)shmat(key,NULL,0);
    ring->pool_start_offset = MM_ALIGN_UP(sizeof(rt_shm_ring_info_t));
    ring->pool_end_offset = MM_ALIGN_UP(len);
    ring->first_blk_offset = 0;
    ring->last_blk_offset = 0;
    ring->left = ring->pool_end_offset - ring->pool_start_offset;

    return 1;
}

uint8_t rt_shm_push(int key,void *addr,size_t len){
    uint8_t* base_addr;
    rt_shm_ring_info_t* ring;
    rt_shm_blk_info_t* last_blk;
    rt_shm_blk_info_t* new_blk;
    base_addr = shmat(key,NULL,0);
    ring = (rt_shm_blk_info_t*)base_addr;

    if(ring->left < MM_ALIGN_UP(sizeof(rt_shm_blk_info_t))+MM_ALIGN_UP(len))){
        return -1;
    }

    last_blk = (rt_shm_blk_info_t*)(base_addr+ring->last_blk_offset);

    new_blk = (rt_shm_blk_info_t*)last_blk->end_addr_offset;
    new_blk->start_addr_offset = last_blk->end_addr_offset;
    new_blk->end_addr_offset = new_blk->start_addr_offset + MM_ALIGN_UP(sizeof(rt_shm_blk_info_t))+MM_ALIGN_UP(len)
    if(new_blk->end_addr_offset >ring->pool_end_offset){
        new_blk->end_addr_offset = new_blk->end_addr_offset - ring->pool_end_offset + ring->pool_start_offset;
    }
    
    if((ring->pool_end_offset - new_blk->end_addr_offset) < MM_ALIGN_UP(sizeof(rt_shm_blk_info_t))){
        if(ring->left <MM_ALIGN_UP(sizeof(rt_shm_blk_info_t))+MM_ALIGN_UP(len)) + ring->pool_end_offset - new_blk->end_addr_offset ){
            return -1;
        }
        new_blk->end_addr_offset = ring->pool_end_offset;
    }

    if(new_blk->end_addr_offset <= new_blk->start_addr_offset){
        memcpy();
    }

}

void rt_shm_pop(int key,void* addr){

    int* addr_start;

    addr_start = addr;

    if(addr_start == NULL){
        addr_start = shmat(key, NULL, 0);
    }

    rt_shm_ring_info_t *ring;
    ring = (rt_shm_blk_info_t)addr_start;
    
    if(ring->blk_num ==0 ){
        return 1;
    }

    int* first_blk_start_addr;
    first_blk_start_addr = (int*)(int**)&ring->first_blk;

    rt_shm_blk_info_t *blk;
    blk = (rt_shm_blk_info_t *)first_blk_start_addr;
    
    int s_offset,e_offset;

    s_offset = sizeof(rt_shm_blk_info_t);
    e_offset = s_offset + blk->length;

    if(e_offset > s_offset){
        memcpy(to_addr,first_blk_start_addr+s_offset,first_blk_start_addr+e_offset);
    }else{
        memcpy(to_addr,first_blk_start_addr+s_offset,addr_start+ring->pool_end_offset);
        memcpy(to_addr+ring->pool_end_offset-s_offset,addr_start+ring->pool_start_offset,)
    }

    --ring->blk_num;
    ring->first_blk = first_blk_start_addr+sizeof(rt_shm_blk_info_t)+blk->length;

    return 1;
}




