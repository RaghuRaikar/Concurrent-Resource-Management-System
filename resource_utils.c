#define _POSIX_C_SOURCE 200809L

#include "resource_utils.h"

#include <errno.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

client_t make_client(int client_id, resource_manager_t* rm) {
  client_t c;
  c.client_id = client_id;
  c.rm = rm;
  return c;
}

void* client_enter(void* ptr) {
  client_t* c = (client_t*)ptr;
  printf("Client %d comes in\n", c->client_id);
  resource_client_enter(c->rm);
  printf("Client %d entered\n", c->client_id);
  return NULL;
}

void* client_leave(void* ptr) {
  client_t* c = (client_t*)ptr;
  printf("Client %d leaves\n", c->client_id);
  resource_client_leave(c->rm);
  printf("Client %d left\n", c->client_id);
  return NULL;
}

maintenance_t make_maintenance(int maintenance_id, resource_manager_t* rm) {
  maintenance_t m;
  m.maintenance_id = maintenance_id;
  m.rm = rm;
  return m;
}

void* maintenance_enter(void* ptr) {
  maintenance_t* m = (maintenance_t*)ptr;
  printf("Maintenance %d comes in\n", m->maintenance_id);
  resource_maintenance_enter(m->rm);
  printf("Maintenance %d entered\n", m->maintenance_id);
  return NULL;
}

void* maintenance_leave(void* ptr) {
  maintenance_t* m = (maintenance_t*)ptr;
  printf("Maintenance %d leaves\n", m->maintenance_id);
  resource_maintenance_leave(m->rm);
  printf("Maintenance %d left\n", m->maintenance_id);
  return NULL;
}

int msleep(long ms) {
  struct timespec ts;
  int res;
  ts.tv_sec = ms / 1000;
  ts.tv_nsec = (ms % 1000) * 1000000;
  do {
    res = nanosleep(&ts, &ts);
  } while (res && errno == EINTR);
  return res;
}
