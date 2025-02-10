#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#include "resource_manager.h"
#include "resource_utils.h"

int main(void) {
  resource_manager_t* rm = resource_manager_init(3);

  client_t client1 = make_client(1, rm);
  client_t client2 = make_client(2, rm);
  maintenance_t maintenance = make_maintenance(1, rm);

  client_enter(&client1);

  pthread_create(&maintenance.thread, NULL, maintenance_enter, &maintenance);
  msleep(100);

  client_leave(&client1);

  pthread_join(maintenance.thread, NULL);

  pthread_create(&client2.thread, NULL, client_enter, &client2);

  msleep(100);

  maintenance_leave(&maintenance);

  pthread_join(client2.thread, NULL);
  client_leave(&client2);

  resource_manager_destroy(&rm);
}
