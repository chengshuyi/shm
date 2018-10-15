#include "stdio.h"
#include "stdlib.h"
#include "sys/shm.h"

#include "rt_shm_ring.h"
#include "rt_shm.h"

uint8_t rt_shm_create(key_t key,size_t len){
    int shmid;
    rt_shm_ring_info_t* ring;
    
    if(len < sizeof(rt_shm_ring_info_t)){
        return -1;
    }
    shmid = shmget(key, len, IPC_CREAT | 0666);

    if(shmid == -1){
        return -1;
    }

    ring = (rt_shm_blk_info_t*)shmat(shmid,NULL,0);
    ring->pool_start_offset = MM_ALIGN_UP(sizeof(rt_shm_ring_info_t));
    ring->pool_end_offset = MM_ALIGN_UP(len);
    ring->first_blk_offset = 0;
    ring->last_blk_offset = 0;
    ring->left = ring->pool_end_offset - ring->pool_start_offset;

    return 1;
}

uint8_t rt_shm_push(key_t key,void *addr,size_t len){
    int shmid;
    uint8_t* base_addr;
    rt_shm_ring_info_t* ring;
    int ret;
    /* */
    if(len > UDP_PACKET_MAX_LEN){
        return -1;
    }
    
    /* get the shm id.*/
    shmid = shmget(key,0,0);
    if(shmid == -1){
        return -1;
    }
    /* get the virtual address in process and the pool struct info.*/
    base_addr = shmat(shmid,NULL,0);
    if(base_addr == (void*)-1){
        return -1;
    }
    ring = (rt_shm_blk_info_t*)base_addr;

    /* have enough space to store data.*/
    if(ring->left < MM_ALIGN_UP(sizeof(rt_shm_blk_info_t))+MM_ALIGN_UP(len))){
        shmdt(shmid);
        return -1;
    }
    ring_push(ring,addr,len);
    shmdt(shmid);
    return 1;
}

uint8_t rt_shm_pop(key_t key,void* addr,size_t* len){
    int shmid;
    uint8_t* base_addr;
    rt_shm_ring_info_t *ring;

    shmid = shmget(key,0,0);
    if(shmid == -1){
        return -1;
    }

    base_addr = shmat(shmid, NULL, 0);
    if(base_addr == (void*)-1){
        return -1;
    }

    ring = (rt_shm_blk_info_t*)base_addr;
    if(ring->num==0){
        return -1;
    }
    ring_pop(ring,addr,len);    
    shmdt(shmid);
    return 1;
}




