#include <netinet/in.h>
#include <server/server.h>
#include <sys/socket.h>
#include <unistd.h>

/* This function configures a socket TCP so it acts as a server
    * Parameters: Server *server, uint16_t server_port (pointer to a server, unsigned int of a server port)
    * Returns: int (0 succeed) (-1 error)
    *
    * All TCP servers in C are: socket -> bind -> listen -> accept
*/
int server_init(Server *server, uint16_t server_port) {
    if (!server) return -1;

    // Creates the socket TCP
    server->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server->fd == 1) return -1;

    // Configures the server address
    // IPv4, port, accept connections in all IPs of the PC
    server->addr.sin_family = AF_INET;
    server->addr.sin_port = htons(server_port);
    server->addr.sin_addr.s_addr = INADDR_ANY;

    // bind() tells the OS this socket will use this IP and this port
    // assigns an address to the socket
    if (bind(server->fd, (struct sockaddr *)&server->addr, sizeof(server->addr)) < 0) {
        return -1;
    }

    if (listen(server->fd, SOMAXCONN) < 0) return -1;

    return 0;
}

/* This function accepts the pending client connection and fills the Client structure with info about the connected client
    * Parameters: Server *server, Client *client (pointer to Server) (pointer to Client)
    * Returns: int (0 succeed) (-1 error)
*/
int server_accept(Server *server, Client *client) {
    if (!server || !client) return -1;

    socklen_t addr_len = sizeof(client->address);

    client->sockfd = accept(
        server->fd, 
        (struct sockaddr *)&client->address, 
        &addr_len);

    if (client->sockfd == -1) return -1;

    return 0;
}

void server_broadcast(Server *server, Client *sender, const char *msg) {
    if (!server) return;

    if (!sender) return;

    if (msg == NULL) return;
}

void server_close(Server *server) {
    if (!server) return;   

    close(server->fd);
}
