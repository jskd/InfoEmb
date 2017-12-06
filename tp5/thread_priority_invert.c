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

pthread_mutex_t verrou;
sem_t sem1,sem2,sem3;

int medium_executed = 0;
int inversion = 0;

void thread_hight()
{
  sem_wait(&sem1);
  pthread_mutex_lock(&verrou);
  printf("Thread_1 : HIGH Pritority\n");
  sem_post(&sem3);
  pthread_mutex_unlock(&verrou);
  if(medium_executed) inversion = 1;
}

void thread_medium()
{
  sem_wait(&sem2);
  pthread_mutex_lock(&verrou);
  printf("Thread_2 : MEDIUM Pritority\n");
  pthread_mutex_unlock(&verrou);
  medium_executed = 1;
}

void thread_low()
{
  sem_wait(&sem3);
  pthread_mutex_lock(&verrou);
  printf("Thread_3 : LOW Pritority\n");
  sem_post(&sem2);
  sem_post(&sem1);
  pthread_mutex_unlock(&verrou);
}


static void _set_attr_param_thread(pthread_attr_t* attr, int priority,
  int policy, int inherit)
{
  struct sched_param param;
  param.sched_priority = priority;
  pthread_attr_setschedpolicy(attr, policy);
  pthread_attr_setschedparam(attr, &param);
  pthread_attr_setinheritsched(attr, inherit);
}


char test_invert(int policy, int inherit) {

  int priority_hight= sched_get_priority_max(policy);
  int priority_low= sched_get_priority_min(policy);
  int priority_medium= (priority_hight + priority_low)/2;

  pthread_t pid_hight, pid_low, pid_medium;
  pthread_attr_t attr_hight, attr_low, attr_medium;

  pthread_attr_init(&attr_hight);
  pthread_attr_init(&attr_low);
  pthread_attr_init(&attr_medium);

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

  sem_init(&sem1, 0, 0);
  sem_init(&sem2, 0, 0);
  sem_init(&sem3, 0, 1);

  pthread_mutex_init(&verrou, NULL);

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
