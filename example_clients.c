#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#include "resource_manager.h"
#include "resource_utils.h"

int main(void) {
  resource_manager_t* rm = resource_manager_init(3);

  client_t client1 = make_client(1, rm);
  client_t client2 = make_client(2, rm);
  client_t client3 = make_client(3, rm);
  client_t client4 = make_client(4, rm);

  client_enter(&client1);
  client_enter(&client2);
  client_enter(&client3);

  pthread_create(&client4.thread, NULL, client_enter, &client4);

  msleep(100);

  client_leave(&client1);

  pthread_join(client4.thread, NULL);

  client_leave(&client2);
  client_leave(&client3);
  client_leave(&client4);

  resource_manager_destroy(&rm);
}
