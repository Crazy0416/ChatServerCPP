#include "src/ChatServer.h"

int main() {
    ChatServer server(5000);
    server.start();

    return 0;
}