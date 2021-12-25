#include "game_server.h"
#include "../infrastructure/log.h"
#include "../infrastructure/server.h"

void onClientConnected(Client *client) {
}

void onClientData(Client *client, char *data, size_t size) {
}

int GameServer_Run(void) {
    Server *server;
    int port = 444;

    server = Server_Create(port);
    if (!server) {
        return 1;
    }    

    Server_HandleEvents(server, onClientConnected, onClientData);

    Server_Destroy(server);
    return 0;
}