#ifndef RT_SHM_H
#define RT_SHM_H


int rt_shm_open(const char *name, int oflag, mode_t mode);
int rt_shm_unlink(const char *name);

#endif
