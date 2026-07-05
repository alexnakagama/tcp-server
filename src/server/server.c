#include <server/server.h>
#include <unistd.h>

int server_init(Server *server, uint16_t server_port) {
}

int server_accept(Server *server, Client *client) {
}

void server_run(Server *server) {

}

void server_broadcast(Server *server, Client *sender, const char *msg) {

}

void server_close(Server *server) {
    if (!server) return;   

    close(server->fd);
}
