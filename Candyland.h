#ifndef CANDYLAND_H
#define CANDYLAND_H
#include <vector>
#include <iostream>
#include "Player.h"

using namespace std;


class Candyland{
    public:
        vector <Candy> loadCandies(string filename);
        vector <Character> loadcharacters(string filename);
        vector <Riddles> loadriddles(string filename);
        vector <Candy> getCandyList() const;
        vector <Riddles> getRiddleList() const;
        vector <Character> getCharacterList() const;

        void playTurn(Player &p1, Player &p2, Board &board);
        void calamity(Player &p1);
        bool playRockPaperScissors();
        void displayCharacterList();
        void shopping(Player &p1);
        bool isPositionCandyStore(int board_position);
        void setCandyStores(string, int);
        void displayCandyStore(Candystore);
        void playTreasure(Player &p1);
        void marshmallowHail(Player &p1, Player &p2);
        void useCandy(Player &p1, Player &p2, Candy);

        vector <Candystore> getCandyStores() const;

        Cards drawcard();

    private:
        // there are more single "cards" to make the double cards rarer (25% chance at double card)
        Cards _card_deck[12] = {{"Magenta", 1} , {"Green", 1}, {"Blue", 1}, 
        {"Magenta", 1} , {"Green", 1}, {"Blue", 1}, 
        {"Magenta", 1} , {"Green", 1}, {"Blue", 1},
        {"Magenta", 2} , {"Green", 2}, {"Blue", 2}};
        vector <Candy> _candylist;
        vector <Character> _characterlist;
        vector <Riddles> _riddlelist;
        vector <Candystore> _candystores;
        const static int _MAX_CANDY_STORE = 3;
};
#endif