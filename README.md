## This is client and server for chat

Project is on minimal working state right now;
supported features:
- server handles multiple clients;
- clients can communicate in single chat;
     

## Client info:

Made on c++/qt6, connects using QTcpSocket

## Server info:

Made on c++/boost::asio tcp sockets

## interaction model:

client and server can communicate with sending JSON objects to each other

## Configuration:

client builds via qmake+make, or using qtcreator

server builds via cmake+make or with vscode "Run and Debug": Server 
