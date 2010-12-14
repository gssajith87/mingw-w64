#include <windows.h>
#include "pthread.h"
#include "barrier.h"
#include "ref.h" 
#include "misc.h"

int pthread_barrier_destroy(pthread_barrier_t *b_)
{
    pthread_barrier_t bDestroy;
    int r = barrier_ref_destroy(b_,&bDestroy);
    
    if (r)
      return r;

    barrier_t *b = (barrier_t *)bDestroy;
    
    pthread_mutex_lock(&b->m);

    if (sem_destroy(&b->sems[0]) != 0)
    {
        /* Could this happen? */
        *b_ = bDestroy;
        pthread_mutex_unlock (&b->m);
        return EBUSY;
    }
    if (sem_destroy(&b->sems[1]) != 0)
    {
      sem_init (&b->sems[0], b->share, 0);
      *b_ = bDestroy;
      pthread_mutex_unlock (&b->m);
      return -1;
    }
    pthread_mutex_unlock(&b->m);
    if(pthread_mutex_destroy(&b->m) != 0) {
     sem_init (&b->sems[0], b->share, 0);
     sem_init (&b->sems[1], b->share, 0);
     *b_ = bDestroy;
     return -1;
    }
    b->valid = DEAD_BARRIER;
    free(bDestroy);
    return 0;

}

int
pthread_barrier_init (pthread_barrier_t *b_, void *attr, unsigned int count)
{
    barrier_t *b;

    if (!count || !b_)
      return EINVAL;

    if (!(b = (pthread_barrier_t)calloc(1,sizeof(*b))))
       return ENOMEM;
    if (!attr || *((int **)attr) == NULL)
      b->share = PTHREAD_PROCESS_PRIVATE;
    else
      memcpy (&b->share, *((void **) attr), sizeof (int));
    b->total = count;
    b->count = count;
    b->valid = LIFE_BARRIER;
    b->sel = 0;

    if (pthread_mutex_init(&b->m, NULL) != 0)
    {
      free (b);
      return ENOMEM;
    }

    if (sem_init(&b->sems[0], b->share, 0) != 0)
    {
       pthread_mutex_destroy(&b->m);
       free (b);
       return ENOMEM;
    }
    if (sem_init(&b->sems[1], b->share, 0) != 0)
    {
       pthread_mutex_destroy(&b->m);
       sem_destroy(&b->sems[0]);
       free (b);
       return ENOMEM;
    }
    barrier_ref_set (b_,b);
    /* *b_ = b; */

    return 0;
}

int pthread_barrier_wait(pthread_barrier_t *b_)
{
  long sel;
  int r;

  r = barrier_ref(b_);
  if(r) return r;

  barrier_t *b = (barrier_t *)*b_;

  if ((r = pthread_mutex_lock(&b->m))) return  barrier_unref(b_,EINVAL);
  sel = b->sel;
  InterlockedDecrement((long*)&b->total);
  if (b->total == 0)
  {
    b->total = b->count;
    pthread_mutex_unlock(&b->m);
    if (b->count > 1)
      r = sem_post_multiple (&b->sems[sel], b->count - 1);
    if (!r)
      r = InterlockedCompareExchange((long*)&b->sel, !sel, sel) == sel ? PTHREAD_BARRIER_SERIAL_THREAD : 0;
    return barrier_unref(b_,r);
  }
  pthread_mutex_unlock(&b->m);
  if ((r = sem_wait(&b->sems[sel])) == 0)
    r = InterlockedCompareExchange((long*)&b->sel, !sel, sel) == sel ? PTHREAD_BARRIER_SERIAL_THREAD : 0;
  return barrier_unref(b_,r);
}

int pthread_barrierattr_init(void **attr)
{
  int *p;

  if (!(p = (int *) calloc (1, sizeof (int))))
    return ENOMEM;

  *p = PTHREAD_PROCESS_PRIVATE;
  *attr = p;

  return 0;
}

int pthread_barrierattr_destroy(void **attr)
{
  void *p;
  if (!attr || (p = *attr) == NULL)
    return EINVAL;
  *attr = NULL;
  free (p);
  return 0;
}

int pthread_barrierattr_setpshared(void **attr, int s)
{
  if (!attr || *attr == NULL
      || (s != PTHREAD_PROCESS_SHARED && s != PTHREAD_PROCESS_PRIVATE))
    return EINVAL;
  memcpy (*attr, &s, sizeof (int));
  return 0;
}

int pthread_barrierattr_getpshared(void **attr, int *s)
{
  if (!attr || !s || *attr == NULL)
    return EINVAL;
  memcpy (s, *attr, sizeof (int));
  return 0;
}
