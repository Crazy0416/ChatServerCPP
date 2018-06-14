//
// Created by kimminho on 18. 6. 14.
//

#include <cstring>
#include <unistd.h>
#include "ChatServer.h"

ChatServer::ChatServer(int port) {
    if((socketFd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(1);
    }

    serverAddr.sin_family = PF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(port);

    if (bind(socketFd, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0)  {
        perror("bind");
        exit(1);
    }
    listen(socketFd, 5);
}

void ChatServer::start() {
    while(true) {
        struct sockaddr_in clientAddr;
        socklen_t clientAddrLen;

        int clientSocket = accept(socketFd, (struct sockaddr *)&clientAddr, &clientAddrLen);

        std::thread t(&ChatServer::workThread, this, clientSocket, clientAddr);
        t.detach();
    }
}

void ChatServer::workThread(int clientFd, struct sockaddr_in clientAddr) {

    int len = 1;
    std::string clientName = std::to_string(clientAddr.sin_addr.s_addr );

    std::cout << "접속한 클라이언트: " << clientAddr.sin_addr.s_addr << ":" << clientAddr.sin_port << std::endl;
    char   buff_rcv[BUFF_SIZE];


    while((len = recv(clientFd, buff_rcv, BUFF_SIZE, 0)) > 0) {
        std::cout << clientName << ": " << buff_rcv << ": len:" << len << std::endl;
        memset(&buff_rcv[0], 0, BUFF_SIZE);

        send(clientFd, "hello\n", 6, 0);
    }
    close(clientFd);
}