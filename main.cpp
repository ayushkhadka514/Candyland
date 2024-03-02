#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include "rng.h"
#include "Player.h"
#include "Board.h"
#include "Candyland.h"


using namespace std;

int main(){

    srand(static_cast<unsigned int>(time(0)));
    Candyland candyland;
    Board board;
    string input;
    
    cout << "Welcome to Candyland!" << endl;
    cout << "Player enter Player 1's name: " << endl;
    getline(cin, input);
    Player p1(input, 1);
    cout << "Player enter Player 2's name: " << endl;
    getline(cin, input);
    Player p2(input, 2);
    candyland.loadCandies("candies.txt");
    candyland.loadcharacters("characters.txt");
    candyland.loadriddles("riddles.txt"); 
    
    board.addSpecialTile();
    candyland.setCandyStores("Winnie's Candy Shop", 0);
    candyland.setCandyStores("Willy Wonka's Candy Factory", rng(40,10));
    candyland.setCandyStores("Fuzzy's Candy Emporium", rng(50, 80));

    cout << p1.getUsername() << ", Select your character!" << endl;
    candyland.displayCharacterList();
    bool valid = false;
    do{
        getline(cin, input);
        // Transform the input to lowercase
        transform(input.begin(), input.end(), input.begin(), ::tolower);

        for (int i = 0; i < 2; i++) {
            string characterNameLowerCase = candyland.getCharacterList()[i].character_name;
            // Transform the character name to lowercase
            transform(characterNameLowerCase.begin(), characterNameLowerCase.end(), characterNameLowerCase.begin(), ::tolower);

            if (input == characterNameLowerCase) {
                p1.setCharName(candyland.getCharacterList()[i].character_name);
                p1.setGold(candyland.getCharacterList()[i].character_gold);
                p1.setStamina(candyland.getCharacterList()[i].character_stamina);
                for(int j = 0; j < 9; j++){
                    Candy temp_candy;
                    temp_candy = candyland.getCharacterList()[i].character_candies[j];
                    p1.setPlayerInventory(temp_candy);
                } 
                valid = true;
                break;
            } 
        }
        if(!valid){
            cout << "Invalid input" << endl;
        }
    } while (!valid);

    cout << p1.getUsername() << " selected " << p1.getCharName() << "!" << endl;

    p1.displayStats();

    cout << p2.getUsername() << ", Select your character!" << endl;
    candyland.displayCharacterList();
    valid = false;

    do{
        getline(cin, input);
        // Transform the input to lowercase
        transform(input.begin(), input.end(), input.begin(), ::tolower);

        for (int i = 0; i < 2; i++) {
            string characterNameLowerCase = candyland.getCharacterList()[i].character_name;
            // Transform the character name to lowercase
            transform(characterNameLowerCase.begin(), characterNameLowerCase.end(), characterNameLowerCase.begin(), ::tolower);

            if (input == characterNameLowerCase) {
                p2.setCharName(candyland.getCharacterList()[i].character_name);
                p2.setGold(candyland.getCharacterList()[i].character_gold);
                p2.setStamina(candyland.getCharacterList()[i].character_stamina);
                for(int j = 0; j < 9; j++){
                    Candy temp_candy;
                    temp_candy = candyland.getCharacterList()[i].character_candies[j];
                    p2.setPlayerInventory(temp_candy);
                } 
                valid = true;
                break;
            } 
        }
        if(!valid){
            cout << "Invalid input" << endl;
        }
    } while (!valid);

    cout << p2.getUsername() << " selected " << p2.getCharName() << "!" << endl;

    p2.displayStats();

    cout << p1.getUsername() << ", would you like to go to a candystore? (y, n)" << endl;
    do{
        getline(cin, input);
    } while(input != "y" && input != "n");

    if(input == "y"){
        candyland.shopping(p1);
    }

    cout << p2.getUsername() << ", would you like to go to a candystore? (y, n)" << endl;
    do{
        getline(cin, input);
    } while(input != "y" && input != "n");

    if(input == "y"){
        candyland.shopping(p2);
    }

    do{
        if (p1.getWinner() || p2.getWinner()) {
        cout << "Game Over!" << endl;
        break;
        }
        if(p1.getSkipTurnCounter() > 0 && p2.getSkipTurnCounter() > 0){
            p1.setSkipTurnCounter(0);
            p2.setSkipTurnCounter(0);
            p1.setStamina(100);
            p2.setStamina(100);
        }
        if(p1.getStamina() <= 0){
            cout << p1.getUsername() << "'s stamina is too low! You will miss 2 turns" << endl;
            cout << "Stamina will be replenished to 100" << endl;
            p1.setSkipTurnCounter(2);
            p1.setStamina(100);
        }
        if(p2.getStamina() <= 0){
            cout << p2.getUsername() << "'s stamina is too low! You will miss 2 turns" << endl;
            cout << "Stamina will be replenished to 15" << endl;
            p2.setSkipTurnCounter(2);
            p2.setStamina(15);
        }
        if(p1.getSkipTurnCounter() <= 0){
            candyland.playTurn(p1, p2, board);
        }
        if(p2.getSkipTurnCounter() <= 0){
            candyland.playTurn(p2, p1, board);
        }
    }while(p1.getWinner() == false && p2.getWinner() == false);


    ofstream outputfile("stats.txt");
    if(outputfile.is_open()){
        if(p1.getWinner() == true){
            cout << "Player 1 wins!" << endl;
        }
        else if(p2.getWinner() == true){
            cout << "Player 2 wins!" << endl;
        }
        outputfile << "Player 1 stats:" << endl;
        outputfile << "Player 1 name: " << p1.getUsername() << endl;
        outputfile << "Player 1 character name: " << p1.getCharName() << endl;
        outputfile << "Player 1 gold: " << p1.getGold() << endl;
        outputfile << "Player 1 stamina: " << p1.getStamina() << endl;
        outputfile << "Player 1 candies: " << endl;
        for (int i = 0; i < 9; i++) {
            if (p1.getInventoryElement(i).name.empty()) {
                outputfile << "[Empty]";
            }
            else{
                outputfile << "[" << p1.getInventoryElement(i).name << "]";
            }
            if((i + 1) % 3 == 0 && i != 0){
                outputfile << endl;
            }
        }

        outputfile << "Player 2 stats:" << endl;
        outputfile << "Player 2 name: " << p2.getUsername() << endl;
        outputfile << "Player 2 character name: " << p2.getCharName() << endl;
        outputfile << "Player 2 gold: " << p2.getGold() << endl;
        outputfile << "Player 2 stamina: " << p2.getStamina() << endl;
        outputfile << "Player 2 candies: " << endl;
        for (int i = 0; i < 9; i++) {
            if (p2.getInventoryElement(i).name.empty()) {
                outputfile << "[Empty]";
            }
            else{
                outputfile << "[" << p2.getInventoryElement(i).name << "]";
            }
            if((i + 1) % 3 == 0 && i != 0){
                outputfile << endl;
            }
        }
    }
    return 0;
}