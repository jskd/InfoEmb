/**
 * @file   thread_priority_invert.c
 * @brief  Programme pouvant produire une situation d'_is_invert de priorité
 *         entre des thread pour le TP5 d'InfoEmb
 * @auhtor Jérôme Skoda <contact@jeromeskoda.fr>
 */

// A ce qui paraît c'est utile
#define _GNU_SOURCE

#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <semaphore.h>


static const int _debug= 0;
static const int _schedpolicy= SCHED_FIFO;
static int _medium_is_executed = 0;
static int _is_invert = 0;


#define handle_error(error, msg) \
  { errno = error; perror(msg); exit(EXIT_FAILURE); }


pthread_mutex_t thread_lock;
sem_t sem_high,sem_medium,sem_low;


void thread_high()
{
  sem_wait(&sem_high);
  pthread_mutex_lock(&thread_lock);

  if(_debug) printf("Thread high priority run.\n");
  sem_post(&sem_low);
  if(_medium_is_executed) _is_invert = 1;

  pthread_mutex_unlock(&thread_lock);
  pthread_exit(0);
}

void thread_medium()
{
  sem_wait(&sem_medium);
  pthread_mutex_lock(&thread_lock);

  if(_debug) printf("Thread medium priority run.\n");
  _medium_is_executed = 1;

  pthread_mutex_unlock(&thread_lock);
  pthread_exit(0);
}

void thread_low()
{
  sem_wait(&sem_low);
  pthread_mutex_lock(&thread_lock);

  if(_debug) printf("Thread low priority run.\n");
  sem_post(&sem_medium);
  sem_post(&sem_high);

  pthread_mutex_unlock(&thread_lock);
  pthread_exit(0);
}

static void _set_attr_param_thread(pthread_attr_t* attr, int priority,
  int policy, int inherit)
{
  pthread_attr_init(attr);
  struct sched_param param;
  param.sched_priority = priority;
  pthread_attr_setschedpolicy(attr, policy);
  pthread_attr_setschedparam(attr, &param);
  pthread_attr_setinheritsched(attr, inherit);
  pthread_attr_setdetachstate(attr, PTHREAD_CREATE_JOINABLE);
}

char test_invert(int policy, int inherit) {

  pthread_t pid_high, pid_low, pid_medium;
  pthread_attr_t attr_high, attr_low, attr_medium;
  int error;

  int priority_high= sched_get_priority_max(inherit);
  int priority_low= sched_get_priority_min(inherit);
  int priority_medium= (priority_high + priority_low)/2;

  _set_attr_param_thread(&attr_high,  priority_high,  policy, inherit);
  _set_attr_param_thread(&attr_low,    priority_low,    policy, inherit);
  _set_attr_param_thread(&attr_medium, priority_medium, policy, inherit);

  error= pthread_create(&pid_high, &attr_high, (void *)thread_high, NULL);
  if (error != 0)
    handle_error(error, "pthread_create thread high priority");

  error= pthread_create(&pid_low, &attr_low, (void *)thread_low, NULL);
  if (error != 0)
    handle_error(error, "pthread_create thread low priority");

  error= pthread_create(&pid_medium, &attr_medium, (void *)thread_medium, NULL);
  if (error != 0)
    handle_error(error, "pthread_create thread medium priority");

  error= pthread_join(pid_high,  NULL);
  if (error != 0)
    handle_error(error, "pthread_join thread high priority");

  error= pthread_join(pid_low,  NULL);
  if (error != 0)
    handle_error(error, "pthread_join thread low priority");

  error= pthread_join(pid_medium,  NULL);
  if (error != 0)
    handle_error(error, "pthread_medium thread high priority");

  pthread_attr_destroy(&attr_high);
  pthread_attr_destroy(&attr_low);
  pthread_attr_destroy(&attr_medium);

}

int main(int argc, char* argv[])
{

  sem_init(&sem_high,  0, 0);
  sem_init(&sem_medium, 0, 0);
  sem_init(&sem_low,    0, 1);

  pthread_mutex_init(&thread_lock, NULL);

  if(argc > 1)
    test_invert(_schedpolicy, PTHREAD_INHERIT_SCHED);
  else
    test_invert(_schedpolicy, PTHREAD_EXPLICIT_SCHED);

  if(_is_invert)
    printf("%s\n", "Inversion détectée");
  else
    printf("%s\n", "Inversion non détectée");

  return 0;
}
