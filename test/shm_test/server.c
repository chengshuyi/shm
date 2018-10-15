#include "rt_shm.h"


int main(){

    if(rt_shm_create(0x1234,1<<16) == -1){
        return -1;
    }

    

    return 0;

}