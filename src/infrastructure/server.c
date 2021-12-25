#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>

#include <netdb.h>
#include <netinet/in.h>

#include "server.h"
#include "log.h"

struct client {
    int fd;
};

struct server {
    int fd;
    int port;
    struct sockaddr_in serv_addr;
};

Server *Server_Create(int port) {
    Server *self = calloc(1, sizeof(Server));
    int ret;

    self->fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (self->fd < 0) {
        Log_Error("Failed to create server: %s", strerror(errno));
        free(self);
        return NULL;
    }

    memset(&self->serv_addr, 0, sizeof(struct sockaddr_in));
    self->serv_addr.sin_family = AF_INET;
    self->serv_addr.sin_addr.s_addr = INADDR_ANY;
    self->serv_addr.sin_port = htons(self->port);

    ret = bind(self->fd, (struct sockaddr *) &self->serv_addr, sizeof(struct sockaddr_in));
    if (ret < 0) {
        Log_Error("Failed to create server: %s", strerror(errno));
        Server_Destroy(self);
        return NULL;
    }

    ret = listen(self->fd, 5);
    if (ret < 0) {
        Log_Error("Failed to create server: %s", strerror(errno));
        Server_Destroy(self);
        return NULL;
    }

    Log_Info("Server started on port %d", port);

    return self;
}

void Server_Destroy(Server *self) {
    if (self) {
        close(self->fd);
        free(self);
    }
}

void Server_HandleEvents(Server *self, void (*onClientConnected)(Client *), void (*onClientData)(Client *, char *, size_t)) {
    fd_set all_fds;

    FD_ZERO(&all_fds);
    FD_SET(self->fd, &all_fds);
}
