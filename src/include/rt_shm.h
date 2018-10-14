#ifndef RT_SHM_H
#define RT_SHM_H


/* alignment: */
#define MM_ALIGN_BIT            3
#define MM_ALIGN_SIZE           (1 << MM_ALIGN_BIT)
#define MM_ALIGN_MASK           (MM_ALIGN_SIZE - 1)
#define MM_ALIGN_UP(a)          (((a) + MM_ALIGN_MASK) & ~MM_ALIGN_MASK)
#define MM_ALIGN_DOWN(a)        ((a) & ~MM_ALIGN_MASK)


int rt_shm_open(const char *name, int oflag, mode_t mode);
int rt_shm_unlink(const char *name);

#endif
