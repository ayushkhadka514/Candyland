#include <iostream>
#include <string>
#include "rng.h"
#include "Player.h"
#include "Board.h"
#include "Candyland.h"
using namespace std;

Board::Board()
{
    resetBoard();
}

void Board::resetBoard()
{
    const int COLOR_COUNT = 3;
    const string COLORS[COLOR_COUNT] = {MAGENTA, GREEN, BLUE};
    Tile new_tile;
    string current_color;
    for (int i = 0; i < _BOARD_SIZE - 1; i++)
    {
        current_color = COLORS[i % COLOR_COUNT];
        new_tile = {current_color, "regular tile"};
        _tiles[i] = new_tile;
    }
    new_tile = {ORANGE, "regular tile"};
    _tiles[_BOARD_SIZE - 1] = new_tile;

    _special_tile_count = 0;
}

void Board::displayTile(int position, Player &p1, Player &p2)
{
    if (position < 0 || position >= _BOARD_SIZE)
    {
        return;
    }
    Tile target = _tiles[position];
    cout << target.color << " ";
    if (position == p1.getPlayerPosition() && position == p2.getPlayerPosition())
    {
        cout << "X";
    }
    else if(position == p1.getPlayerPosition()){
        cout << p1.getPlayerNum();
    }
    else if(position == p2.getPlayerPosition()){
        cout << p2.getPlayerNum();
    }
    else
    {
        cout << " ";
    }
    cout << " " << RESET;
}

void Board::displayBoard(Player &p1, Player &p2)
{
    // First horizontal segment
    for (int i = 0; i <= 23; i++)
    {
        displayTile(i, p1, p2);
    }
    cout << endl;
    // First vertical segment
    for (int i = 24; i <= 28; i++)
    {
        for (int j = 0; j < 23; j++)
        {
            cout << "   ";
        }
        displayTile(i, p1, p2);
        cout << endl;
    }
    // Second horizontal segment
    for (int i = 52; i > 28; i--)
    {
        displayTile(i, p1, p2);
    }
    cout << endl;
    // Second vertical segment
    for (int i = 53; i <= 57; i++)
    {
        displayTile(i, p1 , p2);
        for (int j = 0; j < 23; j++)
        {
            cout << "   ";
        }
        cout << endl;
    }
    // Third horizontal segment
    for (int i = 58; i < _BOARD_SIZE; i++)
    {
        displayTile(i, p1, p2);
    }
    cout << ORANGE << "Castle" << RESET << endl;
}


int Board::getBoardSize() const
{
    return _BOARD_SIZE;
}



void Board::addSpecialTile(){

    Candyland candyland;
    // requirements specify at least 4 special tiles with a minimum 25% chance of each tile being a special
    for(int i = 0; i < _BOARD_SIZE; i++){
        int randomnumber = rng(4, 1); //random number 1-4
        if(randomnumber == 1 ){ //25% chance of the random number being 1
        _special_tile_positions.push_back(i); // add the board position in the vector
        _special_tile_count++;
        }
        //loops thru every tile
    }
}

bool Board::isSpecialTile(int board_position){
    for (int i = 0; i < _special_tile_count; i++)
    {
        if(_special_tile_positions[i] == board_position)
        {
            return true;
        }
    }
    return false;
}

int Board::getSpecialTileCount() const{
    return _special_tile_count;
}

void Board::addTreasure(){
    for(int i = 0; i < 3; i++){
        _treasure_positions[i] = rng(70, 20);
    }
}

bool Board::isTileTreasure(int board_position){
    for(int i = 0; i < 3; i++){
        if(_treasure_positions[i] == board_position){
            return true;
        }
    }
    return false;
}
