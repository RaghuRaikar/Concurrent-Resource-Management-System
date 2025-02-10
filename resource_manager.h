#pragma once

struct resource_manager;
typedef struct resource_manager resource_manager_t;

resource_manager_t *resource_manager_init(int capacity);
void resource_manager_destroy(resource_manager_t **rm);

void resource_client_enter(resource_manager_t *rm);
void resource_client_leave(resource_manager_t *rm);

void resource_maintenance_enter(resource_manager_t *rm);
void resource_maintenance_leave(resource_manager_t *rm);
