#pragma once
#include <bits/stdc++.h>
#include <chrono>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <chrono>
#include <ctime>
#include <mutex>
#include <semaphore.h>

using namespace std;

enum request_t
{
    connect_CR = 0,
    list_CR = 1,
    create_CR = 2,
    join_CR = 3,
    leave_CR = 4,
    delete_CR = 5,
    BROADCAST_MESSAGE = 6,
    list_users = 7,
    PRIVATE_MESSAGE = 8,
    DISCONNECT = 9,
    connect_USR = 10
};
