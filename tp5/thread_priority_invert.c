/**
 * @file   thread_priority_invert.c
 * @brief  Programme pouvant produire une situation d'inversion de priorité
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

// Config
static const int _debug= 0;
static const int _schedpolicy= SCHED_FIFO;
static const int _detachstate= PTHREAD_CREATE_JOINABLE;

// Var
static int _medium_is_executed = 0;
static int _is_invert = 0;

// Synchronisation
static pthread_mutex_t _thread_lock;
static sem_t _sem_high, _sem_medium, _sem_low;

// Pour afficher les erreur
#define handle_error(error, msg) \
  { errno = error; perror(msg); exit(EXIT_FAILURE); }

/**
 * @brief Thread de priorité haute, doit à priorie s'executer avant thread_medium
 */
void thread_high()
{
  sem_wait(&_sem_high);
  pthread_mutex_lock(&_thread_lock);

  if(_debug) printf("Thread high priority run.\n");
  sem_post(&_sem_low);
  if(_medium_is_executed) _is_invert = 1;

  pthread_mutex_unlock(&_thread_lock);
  pthread_exit(0);
}
/**
 * @brief Thread de priorité moyenne, doit à priorie s'executer après thread_high
 */
void thread_medium()
{
  sem_wait(&_sem_medium);
  pthread_mutex_lock(&_thread_lock);

  if(_debug) printf("Thread medium priority run.\n");
  _medium_is_executed = 1;

  pthread_mutex_unlock(&_thread_lock);
  pthread_exit(0);
}

/**
 * @brief Thread de priorité basse, débloque tout les autres thread
 */
void thread_low()
{
  sem_wait(&_sem_low);
  pthread_mutex_lock(&_thread_lock);

  if(_debug) printf("Thread low priority run.\n");
  sem_post(&_sem_medium);
  sem_post(&_sem_high);

  pthread_mutex_unlock(&_thread_lock);
  pthread_exit(0);
}

/**
 * @brief Parametrage des thread
 * @param[out] attr Attribut en sortie
 * @param[in]  priority
 *             Utilisez sched_get_priority_max / min si vous avez un doute
 * @param[in]  policy
 *             Exemple: SCHED_RR ou SCHED_FIFO
 * @param[in]  inherit
 *             Exemple: PTHREAD_INHERIT_SCHED ou PTHREAD_EXPLICIT_SCHED
 */
static void _set_attr_param_thread(pthread_attr_t* attr, int priority,
  int policy, int inherit)
{
  pthread_attr_init(attr);
  struct sched_param param;
  param.sched_priority = priority;
  pthread_attr_setschedpolicy(attr, policy);
  pthread_attr_setschedparam(attr, &param);
  pthread_attr_setinheritsched(attr, inherit);
  pthread_attr_setdetachstate(attr, _detachstate);
}

/**
 *  @brief Crée 3 threads de priorité differente afin de détecter une inversion
 *         de priorité
 *  @param[in] policy
 *             Exemple: SCHED_RR ou SCHED_FIFO
 *  @param[in] inherit
 *             Exemple: PTHREAD_INHERIT_SCHED ou PTHREAD_EXPLICIT_SCHED
 */
void test_invert(int policy, int inherit) {

  pthread_t pid_high, pid_low, pid_medium;
  pthread_attr_t attr_high, attr_low, attr_medium;
  int error;

  int priority_high= sched_get_priority_max(policy);
  int priority_low= sched_get_priority_min(policy);
  int priority_medium= (priority_high + priority_low)/2;

  _set_attr_param_thread(&attr_high,   priority_high,   policy, inherit);
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

/**
 *  @brief Ecrit "Inversion détectée" dans une situation d'inversion de priorité
 *         de thread ou "Inversion non détectée" dans le cas contraire
 *         S'il y a un argument, le scheduling s'effectura avec de l'héritage de
 *         priorité (PTHREAD_INHERIT_SCHED) sinon de manière explicit
 *         (PTHREAD_EXPLICIT_SCHED)
 */
int main(int argc, char* argv[])
{
  // Init semaphore
  sem_init(&_sem_high,   0, 0);
  sem_init(&_sem_medium, 0, 0);
  sem_init(&_sem_low,    0, 1);

  // Init mutex
  pthread_mutex_init(&_thread_lock, NULL);

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
