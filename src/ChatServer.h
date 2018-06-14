//
// Created by kimminho on 18. 6. 14.
//

#ifndef CHATSERVER_CHATSERVER_H
#define CHATSERVER_CHATSERVER_H
#pragma once

#include <stdlib.h>
#include <cstdlib>
#include <cstdio>
#include <sys/socket.h>
#include <string>
#include <netinet/in.h>
#include <thread>
#include <iostream>

#define BUFF_SIZE 256

class ChatServer {
private:
    int socketFd;   // 소켓 파일디스크럽터
    struct sockaddr_in serverAddr;      // 소켓 구조체
    int ad;


public:
    ChatServer(int port);
    ~ChatServer() {};

public:
    void start();
    void workThread(int clientFd, struct sockaddr_in clientAddr);
};


#endif //CHATSERVER_CHATSERVER_H
