#pragma once

#include <pthread.h>

#include "resource_manager.h"

typedef struct client {
  resource_manager_t* rm;
  int client_id;
  pthread_t thread;
} client_t;

client_t make_client(int client_id, resource_manager_t* rm);

void* client_enter(void* ptr);
void* client_leave(void* ptr);

typedef struct maintenance {
  resource_manager_t* rm;
  int maintenance_id;
  pthread_t thread;
} maintenance_t;

maintenance_t make_maintenance(int maintenance_id, resource_manager_t* rm);

void* maintenance_enter(void* ptr);
void* maintenance_leave(void* ptr);

int msleep(long ms);
