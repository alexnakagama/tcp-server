# TCP Chat Server in C

A simple TCP chat server built from scratch in C using low-level POSIX socket APIs.

The goal of this project is to understand how network communication works internally by implementing a server that manages client connections, receives messages, and broadcasts them to connected clients.

## Features

* TCP socket creation
* Server initialization (`socket`, `bind`, `listen`)
* Accepting client connections
* Client management
* Username assignment
* Message broadcasting
* Dynamic client handling
* Manual memory management

## Project Structure

```
.
├── include/
│   ├── server/
│   │   └── server.h
│   └── client/
│       └── client.h
│
├── src/
│   ├── server/
│   │   └── server.c
│   └── client/
│       └── client.c
│
├── main.c
└── Makefile
```

## How It Works

The server follows this flow:

```
Initialize Server
        |
        v
Create socket
        |
        v
Bind address and port
        |
        v
Listen for connections
        |
        v
Accept clients
        |
        v
Store connected clients
        |
        v
Receive messages
        |
        v
Broadcast messages
```

## Architecture

The project is divided into two main modules:

### Server

Responsible for:

* Creating and configuring the TCP socket
* Accepting new connections
* Managing connected clients
* Broadcasting messages
* Closing server resources

### Client

Responsible for:

* Storing client information
* Managing client data
* Assigning usernames
* Cleaning up client resources

## Compilation

Compile using `gcc`:

```bash
gcc -Wall -Wextra -Wpedantic -std=c11 \
    main.c src/server/server.c src/client/client.c \
    -o server
```

Or using the provided Makefile:

```bash
make
```

## Running

Start the server:

```bash
./server
```

Then connect using a TCP client:

```bash
nc localhost 8080
```

## Future Improvements

* Support multiple clients simultaneously using `poll()` or `select()`
* Add client authentication
* Handle disconnected clients automatically
* Improve error handling
* Add message timestamps
* Implement a custom client application

