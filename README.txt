------------------------
HOW TO COMPILE AND RUN
------------------------
Compile: g++ -std=c++17 -Wall -Werror -Wpedantic rng.cpp Player.cpp Board.cpp Candyland.cpp main.cpp
Run: ./a.exe

------------------------
DEPENDENCIES
------------------------
Board.cpp, Candyland.cpp, Player.cpp, rng.cpp, main.cpp, riddles.txt, candies.txt, characters.txt must be in the same directory as the cpp files in order to compile.

------------------------
SUBMISSION INFORMATION
------------------------
CSCI1300 Fall 2023 Project 2
Author: Ayush Khadka
Recitation: 404 - Gaurav Roy
Date: 12/07/2023

------------------------
ABOUT THIS PROJECT
------------------------
This project implements an interactive board game fashioned after the game Candyland. It's a 2 player only game and players draw cards trying to make it through the board and reach the castle. On their way, there are powerups (candies) they can use to put them ahead or their opponent behind. There are special tiles that can help or hurt them and calamities that also try to stop the players from reaching the castle.
