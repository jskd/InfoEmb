/**
 * @file   thread_priority_invert.c
 * @brief  Programme pouvant produire une situation d'inversion de priorité
 *         entre des thread pour le TP5 d'InfoEmb
 * @auhtor Jérôme Skoda <contact@jeromeskoda.fr>
 */

// A ce qui paraît c'est utile
 #define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>
#include <time.h>
#include <semaphore.h>

static const int _schedpolicy= SCHED_FIFO;

pthread_mutex_t thread_lock;
sem_t sem_hight,sem_medium,sem_low;

int medium_executed = 0;
int inversion = 0;

void thread_hight()
{
  sem_wait(&sem_hight);
  printf("Thread hight priority run.\n");
  pthread_mutex_lock(&thread_lock);
  sem_post(&sem_low);
  pthread_mutex_unlock(&thread_lock);
  if(medium_executed) inversion = 1;
}

void thread_medium()
{
  sem_wait(&sem_medium);
  printf("Thread medium priority run.\n");
  pthread_mutex_lock(&thread_lock);
  pthread_mutex_unlock(&thread_lock);
  medium_executed = 1;
}

void thread_low()
{
  sem_wait(&sem_low);
  printf("Thread low priority run.\n");
  pthread_mutex_lock(&thread_lock);
  sem_post(&sem_medium);
  sem_post(&sem_hight);
  pthread_mutex_unlock(&thread_lock);
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
}


char test_invert(int policy, int inherit) {

  int priority_hight= sched_get_priority_max(inherit);
  int priority_low= sched_get_priority_min(inherit);
  int priority_medium= (priority_hight + priority_low)/2;

  pthread_t pid_hight, pid_low, pid_medium;
  pthread_attr_t attr_hight, attr_low, attr_medium;

  _set_attr_param_thread(&attr_hight,  priority_hight,  policy, inherit);
  _set_attr_param_thread(&attr_low,    priority_low,    policy, inherit);
  _set_attr_param_thread(&attr_medium, priority_medium, policy, inherit);

  pthread_create(&pid_hight , &attr_hight,  (void *)thread_hight,  NULL);
  pthread_create(&pid_low   , &attr_low,    (void *)thread_low,    NULL);
  pthread_create(&pid_medium, &attr_medium, (void *)thread_medium, NULL);

  pthread_join(pid_hight,  NULL);
  pthread_join(pid_low,    NULL);
  pthread_join(pid_medium, NULL);

  pthread_attr_destroy(&attr_hight);
  pthread_attr_destroy(&attr_low);
  pthread_attr_destroy(&attr_medium);

}

int main(int argc, char* argv[])
{

  sem_init(&sem_hight,  0, 0);
  sem_init(&sem_medium, 0, 0);
  sem_init(&sem_low,    0, 1);

  pthread_mutex_init(&thread_lock, NULL);

  if(argc > 1)
    test_invert(_schedpolicy, PTHREAD_INHERIT_SCHED);
  else
    test_invert(_schedpolicy, PTHREAD_EXPLICIT_SCHED);

  if(inversion)
    printf("%s\n", "Inversion détectée");
  else
    printf("%s\n", "Inversion non détectée");

  return 0;
}
