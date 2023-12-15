# OmegleAUB

## About
OmegleAUB is a multithreaded chatroom application that supports many operation between client and server.

## Technologies used
- C++ Socket programming (Backend)

## Compilation Command

- make sure you are in the archictecture directory & you are running on linux
- g++ -Wall -g -o main test/main_shell.cpp implementation/*.cpp -lpthread
- g++ -Wall -g -o server server.cpp implementation/*.cpp -lpthread
- g++ -Wall -g -o client client.cpp implementation/*.cpp -lpthread
## Run application
- ./server
- ./client (if you want)
- ./main
