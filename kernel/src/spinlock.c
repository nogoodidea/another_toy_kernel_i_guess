#include <stdbool.h>
#include <stdatomic.h>

typedef struct {
  void * ptr;
  volatile atomic_flag lock;
} spinlock_t;

void int_spinlock(spinlock_t *spinlock, void *ptr){
  spinlock->ptr = ptr;
  atomic_flag_clear_explicit(&spinlock->lock,memory_order_release);
}

void *aquire_lock(spinlock_t *spinlock){
  while(!atomic_flag_test_and_set_explicit(&spinlock->lock, memory_order_acquire)){}
  return spinlock->ptr;
}

void drop_spinlock(spinlock_t *spinlock){
  atomic_flag_clear(&spinlock->lock);
}
