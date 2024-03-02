#ifndef BOARD_H
#define BOARD_H


#define RED "\033[;41m"     /* Red */
#define GREEN "\033[;42m"   /* Green */
#define BLUE "\033[;44m"    /* Blue */
#define MAGENTA "\033[;45m" /* Magenta */
#define CYAN "\033[;46m"    /* Cyan */
#define ORANGE "\033[48;2;230;115;0m"  /* Orange (230,115,0)*/
#define RESET "\033[0m"

#include <iostream>
#include <vector>
#include "Player.h"
using namespace std;


class Board
{
private:
    const static int _BOARD_SIZE = 83;
    Tile _tiles[_BOARD_SIZE];
    vector <int> _special_tile_positions;
    int _special_tile_count;
    int _player_position;
    int _treasure_positions[3];
public:
    Board();

    void resetBoard();
    void displayTile(int, Player &p1, Player &p2);
    void displayBoard(Player &p1, Player &p2);
    void addSpecialTile();
    
    int getBoardSize() const;
    int getSpecialTileCount() const;

    bool isSpecialTile(int);

    void addTreasure();

    bool isTileTreasure(int);
};

#endif