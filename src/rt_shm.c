#include "stdio.h"
#include "stdlib.h"
#include "sys/shm.h"

#include "rt_shm_ring.h"

void rt_shm_create(int key){

}

void rt_shm_push(int key,void* addr){

}

void rt_shm_pop(int key,void* addr){

    int* addr_start;

    addr_start = addr;

    if(addr_start == NULL){
        addr_start = shmat(key, NULL, 0);
    }

    rt_shm_ring_info_t *ring;
    ring = addr_start;
    
    if(ring->blk_num ==0 ){
        return 1;
    }

    int* first_blk_start_addr;
    first_blk_start_addr = (int*)(int**)&ring->first_blk;
    


}



