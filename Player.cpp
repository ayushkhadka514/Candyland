#include <iostream>
#include <string>
#include "rng.h"
#include "Player.h"
#include "Board.h"
#include "Candyland.h"

using namespace std;

Player::Player(){
    _username = "";
    _char_name = "";
    _gold = 0;
    _stamina = 0;
    for(int i = 0; i < 9; i++){
        _inventory[i] = {};
    }
    _player_num = 0;
    _player_position = 0;
    _skip_turn_counter = 0;
    _immunity = false;
    _winner = false;
}
Player::Player(string username, int playernum){
    _username = username;
    _player_num = playernum;
    _char_name = "";
    _gold = 0;
    _stamina = 0;
    _skip_turn_counter = 0;
    for(int i = 0; i < 9; i++){
        _inventory[i] = {};
    }
    _player_position = 0;
    _immunity = false;
    _winner = false;
}

void Player:: setUserName(string username){
    _username = username;
}

int Player::getGold() const{
    return _gold;
}

string Player::getCharName() const{
    return _char_name;
}

int Player::getStamina() const{
    return _stamina;
}

void Player::setGold(int gold){
    _gold = gold;
    if(_gold < 0){
        _gold = 0;
    }
}

void Player::setCharName(string char_name){
    _char_name = char_name;
}

void Player::setStamina(int stamina){
    _stamina = stamina;
}

string Player::getUsername() const{
    return _username;
}

void Player::displayStats() const{
    cout << "Player name: " << _username << endl;
    cout << "Character Name: " << _char_name << endl;
    cout << "Gold: " << _gold << endl;
    cout << "Stamina: " << _stamina << endl;
    cout << "Candies: " << endl;
    for (int i = 0; i < 9; i++) {
        if (_inventory[i].name.empty()) {
            cout << "[Empty]";
        }
        else {
            cout << "[" << _inventory[i].name << "]";
        }
        if((i + 1) % 3 == 0 && i != 0){
            cout << endl;
        }
    }
}

int Player::getPlayerNum() const{
    return _player_num;
}

void Player::setPlayerPosition(int new_position)
{
    _player_position = new_position;
}

int Player::getPlayerPosition() const
{
    return _player_position;
}

void Player::movePlayer(int tile_to_move_forward)
{
    int new_player_position = tile_to_move_forward + _player_position;

    _player_position = new_player_position;
    if(_player_position >= 83){
        _winner = true;
    }
}

bool Player::setPlayerInventory(Candy candy){
    for(int i = 0; i < 9; i++){
        if(_inventory[i].name.empty()){
            _inventory[i].name = candy.name;
            _inventory[i].description = candy.description;
            _inventory[i].effect_type = candy.effect_type;
            _inventory[i].effect_value = candy.effect_value;
            _inventory[i].price = candy.price;
            _inventory[i].candy_type = candy.candy_type;
            return true;
        }
    }
    return false;
}

// returns an index of array
Candy Player:: getInventoryElement(int index){
    return _inventory[index];
}

void Player:: setSkipTurnCounter(int num){
    _skip_turn_counter = num;
}

int Player:: getSkipTurnCounter() const {
    return _skip_turn_counter;
}

void Player::removeCandy(Candy candy){
    int index = -1;
    for(int i = 0; i < 9; i++){
        if(_inventory[i].name == candy.name){
            index = i;
            break;
        }
    }
    for(int i = index; i < 8; i++){
        _inventory[i] = _inventory[i+1];
    }
    _inventory[8] = {};
}

void Player::setImmunity(bool a){
    _immunity = a;
}

bool Player::getImmunity() const{
    return _immunity;
}

bool Player::getWinner() const{
    return _winner;
}