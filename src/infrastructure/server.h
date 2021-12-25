#include <netinet/in.h>
#pragma once

typedef struct server Server;

typedef struct client Client;

Server *Server_Create(int port);

void Server_Destroy(Server *self);

void Server_HandleEvents(Server *self, void (*onClientConnected)(Client *), void (*onClientData)(Client *, char *, size_t));
