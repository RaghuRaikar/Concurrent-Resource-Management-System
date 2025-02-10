#include "resource_manager.h"

#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct resource_manager {
  pthread_mutex_t client_mutex;
  pthread_mutex_t maintenance_mutex;
  pthread_cond_t maintenance_done;
  pthread_cond_t client_done;
  sem_t clients;
  sem_t maintenance;
  bool maintenance_active;
  int capacity;
  int num_clients;
  int num_maintenance;
} resource_manager_t;

resource_manager_t *resource_manager_init(int capacity) {
  resource_manager_t *rm = malloc(sizeof(resource_manager_t));
  pthread_mutex_init(&rm->client_mutex, NULL);
  pthread_mutex_init(&rm->maintenance_mutex, NULL);
  pthread_cond_init(&rm->maintenance_done, NULL);
  pthread_cond_init(&rm->client_done, NULL);
  sem_init(&rm->clients, 0, capacity);
  sem_init(&rm->maintenance, 0, 1);
  rm->maintenance_active = false;
  rm->capacity = capacity;
  rm->num_clients = 0;
  rm->num_maintenance = 0;
  return rm;
}

void resource_manager_destroy(resource_manager_t **rm_ptr) {
  resource_manager_t *rm = *rm_ptr;
  pthread_mutex_destroy(&rm->client_mutex);
  pthread_mutex_destroy(&rm->maintenance_mutex);
  pthread_cond_destroy(&rm->maintenance_done);
  pthread_cond_destroy(&rm->client_done);
  sem_destroy(&rm->clients);
  sem_destroy(&rm->maintenance);
  free(rm);
  *rm_ptr = NULL;
}

void resource_client_enter(resource_manager_t *rm) {
  sem_wait(&rm->clients);
  pthread_mutex_lock(&rm->client_mutex);
  while (rm->num_maintenance > 0 || rm->num_clients == rm->capacity) {
    pthread_cond_wait(&rm->client_done, &rm->client_mutex);
  }
  rm->num_clients++;
  pthread_mutex_unlock(&rm->client_mutex);
}

void resource_client_leave(resource_manager_t *rm) {
  pthread_mutex_lock(&rm->client_mutex);
  rm->num_clients--;
  sem_post(&rm->clients);
  if (rm->num_clients == 0 && rm->maintenance_active) {
    pthread_cond_broadcast(&rm->client_done);
    pthread_cond_broadcast(&rm->maintenance_done);
  }
  pthread_mutex_unlock(&rm->client_mutex);
}

void resource_maintenance_enter(resource_manager_t *rm) {
  sem_wait(&rm->maintenance);
  pthread_mutex_lock(&rm->maintenance_mutex);
  rm->num_maintenance++;
  rm->maintenance_active = true;
  while (rm->num_clients > 0) {
    pthread_cond_wait(&rm->maintenance_done, &rm->maintenance_mutex);
  }
}

void resource_maintenance_leave(resource_manager_t *rm) {
  rm->num_maintenance--;
  if (rm->num_maintenance == 0 && rm->maintenance_active) {
    rm->maintenance_active = false;
    pthread_cond_broadcast(&rm->maintenance_done);
    pthread_cond_broadcast(&rm->client_done);
  }
  pthread_mutex_unlock(&rm->maintenance_mutex);
  sem_post(&rm->maintenance);
}
