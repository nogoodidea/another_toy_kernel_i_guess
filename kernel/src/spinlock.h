#ifndef SPINLOCK_H
#define SPINLOCK_H

typedef struct spinlock_t * Spinlock;

void int_spinlock(Spinlock spinlock, void *ptr);

void *aquire_lock(Spinlock spinlock);

void drop_spinlock(Spinlock spinlock);

#endif //SPINLOCK_H
