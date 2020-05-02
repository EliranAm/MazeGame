# Maze Game

### Description: 
The project purpose was to build a Dungeons and Dragons multiple user online game.
The users share the same map created by the server, they can talk with each other, fight monsters together or apart, or fight each other.

### Language: 
The project was written in C++ 11 and used TCP and Telnet protocols.

### How to Run:
#### Server:
  - Make the makefile in MazeGame/Maze folder to build the game server.
  - Run MazeApp.
  - You can run with Port number as parameter (default is 5100).
  - You can edit the map in MazeGame/Maze/map.txt.
#### Client:
  - Open terminal and connect with the game server using telnet
  - Command: telnet server_ip server_port

### Environment: 
The application compiled and tested on Ubuntu 14.0.4 32-bit, gcc 4.8.4.

