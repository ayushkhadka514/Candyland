#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <vector>

using namespace std;

struct Candy
{
    string name;
    string description;
    string effect_type;
    int effect_value;
    double price;
    string candy_type;
};
struct Character{
    string character_name;
    int character_stamina;
    int character_gold;
    Candy character_candies[9];
};

struct Riddles{
    string question;
    string answer;
};

struct Cards{
    string color;
    int move;
};

struct Candystore{
    string store_name;
    Candy store_candies[5];
    int store_position;
};

struct Tile
{
    string color;
    string tile_type;
};

class Player{
    public:
        Player();
        Player(string, int);
        int getGold() const;
        int getStamina() const;
        string getCharName() const;
        string getUsername() const;
        void setGold(int gold);
        void setStamina(int stamina);
        void setCharName(string char_name);
        void displayStats() const;
        void setUserName(string username);
        int getPlayerNum() const;
        void movePlayer(int tile_to_move_forward);
        int getPlayerPosition() const;
        void setPlayerPosition(int);

        bool getWinner() const;

        Candy getInventoryElement(int index);
        bool setPlayerInventory(Candy);
        void removeCandy(Candy);

        void setSkipTurnCounter(int);
        int getSkipTurnCounter() const;

        void setImmunity(bool);
        bool getImmunity() const;

    private:
        int _gold;
        string _char_name;
        int _stamina;
        Candy _inventory[9];
        string _username;
        int _player_position;
        int _player_num;
        int _skip_turn_counter;
        bool _immunity;
        bool _winner;
};

#endif