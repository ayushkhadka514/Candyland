#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include "rng.h"
#include "Player.h"
#include "Board.h"
#include "Candyland.h"

using namespace std;


vector <Candy> Candyland::loadCandies(string filename){
    ifstream file;
    string line, name_, description_, effect_type_, effect_value_, price_, candy_type_;

    file.open(filename);

    if (!file.is_open()) {
        cout << "Failed to open file" << endl;
        return _candylist;
    } else {
        while (getline(file, line)) {
            Candy candy;
            stringstream ss(line);

            getline(ss, name_, '|');
            // cout<< name_ << endl;
            candy.name = name_;
            getline(ss, description_, '|');
            // cout << description_ << endl;
            candy.description = description_;
            getline(ss, effect_type_, '|');
            // cout << effect_type_ << endl;
            candy.effect_type = effect_type_;
            getline(ss, effect_value_, '|');
            // cout << effect_value_ << endl;
            candy.effect_value = stoi(effect_value_);
            getline(ss, candy_type_, '|');
            // cout << candy_type_ << endl;
            candy.candy_type = candy_type_;
            getline(ss, price_, '|');
            // cout << price_ << endl;
            candy.price = stod(price_);

            if (!candy.name.empty()) {
                _candylist.push_back(candy);
            }
        }
        file.close();
    } 
    return _candylist;
}

vector <Character> Candyland:: loadcharacters(string filename){
    ifstream file;
    string line, character_name, character_stamina, character_gold;
    string temp_candy_name;
    Candy temp_candy;
    string candies[9];
    int list_size = getCandyList().size();

    file.open(filename);
    if (!file.is_open()) {
        cout << "Failed to open file" << endl;
        return _characterlist;
    } 
    else{
        while(getline(file, line)){
            Character character;
            stringstream ss(line);

            getline(ss, character_name, '|');
            character.character_name = character_name;
            getline(ss, character_stamina, '|');
            character.character_stamina = stoi(character_stamina);
            getline(ss, character_gold, '|');
            character.character_gold = stoi(character_gold);
            for(int i = 0; i < 5; i++){
                getline(ss, temp_candy_name, ',');
                for(int j = 0; j < list_size; j++){
                    if(temp_candy_name == getCandyList()[j].name){
                        temp_candy = getCandyList()[j];
                    }
                }
                character.character_candies[i] = temp_candy;
            }
            for(int i = 5; i < 9; i++){
                character.character_candies[i] = {};
            }
            _characterlist.push_back(character);
        }

        file.close();
    }
    return _characterlist;
}

vector <Riddles> Candyland:: loadriddles(string filename){
    ifstream file;
    string line, question_, answer_;

    file.open(filename);
    if (!file.is_open()) {
        cout << "Failed to open file" << endl;
        return _riddlelist;
    } 
    else{
        while(getline(file, line)){
            Riddles riddle;
            stringstream ss(line);

            getline(ss, question_, '|');
            riddle.question = question_;
            getline(ss, answer_);
            riddle.answer = answer_;

            _riddlelist.push_back(riddle);
        }
    }
    file.close();
    return _riddlelist;
}

Cards Candyland::drawcard(){
    int randomnumber = -1;
    Cards drawn_card;
    randomnumber = rng(11, 0);  
    //11 and 0 bc there are 12 cards in the deck and the random number will be the index we use for the array of cards
    drawn_card = _card_deck[randomnumber];
    return drawn_card;
}

bool Candyland::playRockPaperScissors(){
    // similar implementation to hw 7
    // have a character array of size 3 with elements r, p, s and then randomly select using random number function 0-2
    bool win;
    bool tie = true;
    char rps[3] = {'r', 'p', 's'};
    char p_choice;
    char c_choice;
    int randomnumber = 0;
    cout << "Welcome to Rock, Paper, Scissors" << endl;
    do{
        do{
            cout << "Select your choice (r, p, s)" << endl;
            cin >> p_choice;
            if(p_choice != 'r' && p_choice != 'p' && p_choice != 's'){
            cout << "Invalid choice! Please try again" << endl;
            }
            else{
                cout << "You chose " << p_choice << "!" << endl;
            }
        } while(p_choice != 'r' && p_choice != 'p' && p_choice != 's');
        randomnumber = rng(2,0);
        c_choice = rps[randomnumber];
        if(p_choice == 'r'){
            if(c_choice == 'r'){
                cout << "Computer chose " << c_choice << "!" << endl;
                cout << "It's a tie! Play again" << endl;
                tie = true;
            }
            else if(c_choice == 'p'){
                cout << "Computer chose " << c_choice << "!" << endl;
                cout << "You lost :(" << endl;
                tie = false;
                win = false;
            }
            else{
                cout << "Computer chose " << c_choice << "!" << endl;
                cout << "You won!" << endl;
                win = true;
                tie = false;
            }
        }
        else if(p_choice == 'p'){
            if(c_choice == 'r'){
                cout << "Computer chose " << c_choice << "!" << endl;
                cout << "You won!" << endl;
                win = true;
                tie = false;
            }
            else if(c_choice == 'p'){
                cout << "Computer chose " << c_choice << "!" << endl;
                cout << "It's a tie! Play again" << endl;
                tie = true;
            }
            else{
                cout << "Computer chose " << c_choice << "!" << endl;
                cout << "You lost :(" << endl;
                tie = false;
                win = false;
            }
        }
        else{
            if(c_choice == 'r'){
                cout << "Computer chose " << c_choice << "!" << endl;
                cout << "You lost :(" << endl;
                tie = false;
                win = false;
            }
            else if(c_choice == 'p'){
                cout << "Computer chose " << c_choice << "!" << endl;
                cout << "You won!" << endl;
                win = true;
                tie = false;
            }
            else{
                cout << "Computer chose " << c_choice << "!" << endl;
                cout << "It's a tie! Play again" << endl;
                tie = true;
            }
        }
    } while(tie == true);
    return win;
}

vector <Candy> Candyland::getCandyList() const{
    return _candylist;
}

vector <Character> Candyland:: getCharacterList() const{
    return _characterlist;
}

vector <Riddles> Candyland:: getRiddleList() const{
    return _riddlelist;
}

void Candyland:: calamity(Player &p1){
    int randomnum = -1;
    bool win = false;
    randomnum = rng(5,1);
    if(randomnum == 1){  // 20% chance of calamity
        randomnum = rng(100, 1);
        if(randomnum <= 30){  // 30% chance for bandits
            randomnum = rng(10, 1);
            if(p1.getGold() < randomnum){
                randomnum = p1.getGold();
            }
            p1.setGold(p1.getGold() - randomnum);
            cout << "You have been attacked by candy bandits! They stole " << randomnum << " gold from you!" << endl;
        }
        else if(randomnum > 30 && randomnum <= 65){ // 35% chance of lollipop labyrinth
            cout << "You get lost in a lollipop labyrinth and the way back to the board is draining!" << endl;
            cout << "You will lose 5-10 stamina points but you can recover if you win a game of rock paper scissors!" << endl;
            win = playRockPaperScissors();
            if(win == true){
                cout << "You recovered your stamina!" << endl;
            }
            else{
                randomnum = rng(10,5);
                if(p1.getStamina() < randomnum){
                    randomnum = p1.getStamina();
                }
                p1.setStamina(p1.getStamina() - randomnum);
                cout << "You lost " << randomnum << " stamina points" << endl;
            }
            
        }
        else if(randomnum > 65 && randomnum <= 80){  // 15% chance for candy avalanche
            cout << "You got caught in the middle of a Candy Avalanche and will need to miss a turn to get back on track!" << endl;
            cout << "One way you can recover is to win a game of rock paper scissors!" << endl;
            win = playRockPaperScissors();
            if(win == true){
                cout << "You recovered and won't miss a turn!" << endl;
            }
            else{
                p1.setSkipTurnCounter(2);
                cout << "You will have to miss a turn" << endl;
            }
        }
        else{ // 20% chance  for sticky taffy
            vector <Candy> magical;
            char choice;
            string input;
            bool valid_input = false;
            cout << "Oops! You landed on sticky taffy and will have to miss a turn!" << endl;
            for(int i = 0; i < 9; i++){
                if(p1.getInventoryElement(1).candy_type == "magical"){
                    magical.push_back(p1.getInventoryElement(i));
                }
            } 
            if(!magical.empty()){
                cout << "However, you have magical candy in your inventory that can recover your lost turn!" << endl;
                cout << "Would you like to use one of your magical candies? (y, n)" << endl;
                cin >> choice;
                if(choice == 'y'){
                    int size = magical.size();
                    cout << "Choose which candy to use! (enter name)" << endl;
                    for(int i = 0; i < size; i++){
                        cout << magical[i].name << endl;
                    }
                    do{
                        getline(cin, input);
                        transform(input.begin(), input.end(), input.begin(), ::tolower);
                        for(int i = 0; i < size; i++){
                            string lower_magical = magical[i].name;
                            transform(lower_magical.begin(), lower_magical.end(), lower_magical.begin(), ::tolower);
                            if(input == lower_magical){
                                Candy remove_candy = magical[i];
                                p1.removeCandy(remove_candy);
                                cout << "You used a magical candy to avoid skipping a turn!" << endl;
                                valid_input = true;
                                break;
                            }
                        }
                    } while(valid_input == false);
                }
                else{
                    p1.setSkipTurnCounter(2);
                    cout << "You will be skipped for one turn" << endl;
                }
            }
            else{
                p1.setSkipTurnCounter(2);
            }
        }
    }
    else{
        cout << "You avoided any calamities!" << endl;
    }
}

void Candyland::displayCharacterList(){
    int size = _characterlist.size();
    for(int i = 0; i < size; i++){
        cout << "Character Name: " << getCharacterList()[i].character_name << endl;
        cout << "Character Stats:" << endl;
        cout << "Stamina: " << getCharacterList()[i].character_stamina;
        cout << "       Gold: " << getCharacterList()[i].character_gold << endl;
        cout << "Candies: " << endl;
        for (int j = 0; j < 9; j++) {
            if (getCharacterList()[i].character_candies[j].name.empty()) {
                cout << "[Empty]";
            }
            else {
                cout << "[" << getCharacterList()[i].character_candies[j].name << "]";
            }
            if((j + 1) % 3 == 0 && j != 0){
                cout << endl;
            }
        }
    }
}

void Candyland::shopping(Player &p1) {
    string temp;
    int storeIndex = -1;
    bool valid_input = false;

    if (p1.getPlayerPosition() == 0) {
        storeIndex = 0;
    } else if (p1.getPlayerPosition() == getCandyStores()[1].store_position) {
        storeIndex = 1;
    } else {
        storeIndex = 2;
    }

    displayCandyStore(_candystores[storeIndex]);

    do {
        cout << "Enter the name of the candy you want to buy or enter (exit) if you want to leave!" << endl;
        getline(cin, temp);
        transform(temp.begin(), temp.end(), temp.begin(), ::tolower);

        if (temp == "exit") {
            break;
        }

        bool foundCandy = false;

        for (int i = 0; i < 5; i++) {
            Candy candy = _candystores[storeIndex].store_candies[i];
            string lower_candy = _candystores[storeIndex].store_candies[i].name;
            transform(lower_candy.begin(), lower_candy.end(), lower_candy.begin(), ::tolower);

            if (temp == lower_candy) {
                foundCandy = true;

                for (int j = 0; j < 9; j++) {
                    if (p1.setPlayerInventory(candy) == false) {
                        cout << "Inventory is full!" << endl;
                        break;
                    } else if (p1.getGold() >= candy.price) {
                        p1.setGold(p1.getGold() - candy.price);
                        cout << "Successfully bought " << candy.name << "!" << endl;
                        cout << "Gold balance: " << p1.getGold() << endl;
                        valid_input = true;
                        break;
                    } else {
                        cout << "Not enough gold to purchase " << candy.name << endl;
                        break;
                    }
                }

                break;
            }
        }

        if (!foundCandy && !valid_input) {
            cout << "Invalid candy name! Please try again." << endl;
        }

    } while (!valid_input);
    
    if (valid_input) {
        cout << "Thank you for shopping! Have a wonderful journey." << endl;
    } else {
        cout << "You chose to leave the store. Have a great day!" << endl;
    }
}


vector <Candystore> Candyland::getCandyStores() const{
    return _candystores;
}

void Candyland::setCandyStores(string name, int position){
    Candystore store;
    store.store_name = name;
    vector <int> temp;
    int num = -1;
    while(temp.size() < 5){
        num = rng(getCandyList().size() -1 , 0);
        if(find(temp.begin(), temp.end(), num) == temp.end()){
            temp.push_back(num);
        }
    }
    for(int i = 0; i < 5; i++){
        store.store_candies[i] = getCandyList()[temp[i]];
    }

    store.store_position = position;
    _candystores.push_back(store);
}

bool Candyland::isPositionCandyStore(int board_position)
{
    for (int i = 0; i < 3; i++){
        if(_candystores[i].store_position == board_position){
            return true;
        }
    }
    return false;
}

void Candyland::displayCandyStore(Candystore h){
    cout << "Welcome to " << h.store_name << "!" << endl;
    cout << "Available Candies: " << endl;
    for(int i = 0; i < 5; i++){
        cout << h.store_candies[i].name<< "         Price: " << h.store_candies[i].price << endl;
    }
}

void Candyland::playTreasure(Player &p){
    string input;
    cout << "You have landed on a treasure tile!" << endl;
    cout << "If you solve a riddle, you will gain 20-40 coins!" << endl;
    int size = getRiddleList().size();
    int random = rng(size -1, 0);
    cout << endl;
    cout << "Question: " << getRiddleList()[random].question << endl;
    getline(cin, input);
    transform(input.begin(), input.end(), input.begin(), ::tolower);
    string answer_lower = getRiddleList()[random].answer;
    transform(answer_lower.begin(), answer_lower.end(), answer_lower.begin(), ::tolower);

    if(input == answer_lower){
        int gold_won = rng(40,20);
        p.setGold(p.getGold() + gold_won);
        cout << "You solved the riddle correctly!" << endl;
        cout << "You won " << gold_won << " gold!" << endl;
    }
    else{
        cout << "Sorry, that's wrong, the answer was " << getRiddleList()[random].answer << endl;
    }
}

void Candyland::marshmallowHail(Player &p1, Player &p2){
    int randomnum = rng(20, 1); // 5% chance at hailstorm
    if(randomnum == 1){
        cout << "A marshmallow hailstorm has occured and moved all players back a random amount" << endl;
        randomnum = rng(5,1);
        p1.movePlayer(-randomnum);
        cout << p1.getUsername() << " was moved back " << randomnum << " tiles" << endl;
        randomnum = rng(5,1);
        p2.movePlayer(-randomnum);
        cout << p2.getUsername() << " was moved back " << randomnum << " tiles" << endl;
    }
}

void Candyland::useCandy(Player &p1, Player &p2, Candy candy) {
    if(candy.effect_type == "stamina+"){
        p1.setStamina(p1.getStamina() + candy.effect_value);
        cout << "Player 1 gained " << candy.effect_value << " stamina" << endl;
    }
    else if(candy.effect_type == "stamina-"){
        if (p2.getImmunity() == false) {
            p2.setStamina(p2.getStamina() + candy.effect_value);
            cout << "Player 2 lost " << candy.effect_value << " stamina" << endl;
        } 
        else{
            cout << p2.getUsername() << " had immunity!" << endl;
            cout << p2.getUsername() << " is no longer immune" << endl;
            p2.setImmunity(false);
        }
    }
    else if(candy.effect_type == "gold+"){
        p1.setGold(p1.getGold() + candy.effect_value);
        cout << p1.getUsername() << " gained " << candy.effect_value << " gold from candy" << endl;
    }
    else if(candy.effect_type == "gold-"){
        if(p2.getImmunity() == false){
            p2.setGold(p2.getGold() + candy.effect_value);
            cout << p2.getUsername() << " lost " << candy.effect_value << " gold from candy" << endl;
        }
    }
    else if(candy.effect_type == "other"){
        p1.setImmunity(true);
        cout << p1.getUsername() << " has gained immunity" << endl;
    }

    p1.removeCandy(candy);

}

void Candyland::playTurn(Player &p1, Player &p2, Board &board){
    bool endturn = false;
    board.displayBoard(p1, p2);
    int choice = 0;
    cout << p1.getUsername() << ", It is your turn!" << endl;
    do{
        cout << "Choose 1 of these options: " << endl;
        cout << "1. Draw a card" << endl;
        cout << "2. Use candy" << endl;
        cout << "3. Show stats" << endl;
        cin >> choice;
        cin.ignore();
        if(choice == 1){
            Cards a = drawcard();
            int tiles_moved = -1;
            cout << "Card drawn: " << a.color << " " << a.move << endl;
            if(p1.getPlayerPosition() % 3 == 0){
                if(a.color == "Magenta" && a.move == 1){
                    p1.movePlayer(3);
                    tiles_moved = 3;
                }
                else if(a.color == "Magenta" && a.move == 2){
                    p1.movePlayer(6);
                    tiles_moved = 6;
                }
                else if(a.color == "Green" && a.move == 1){
                    p1.movePlayer(1);
                    tiles_moved = 1;
                }
                else if(a.color == "Green" && a.move == 2){
                    p1.movePlayer(4);
                    tiles_moved = 4;
                }
                else if(a.color == "Blue" && a.move == 1){
                    p1.movePlayer(2);
                    tiles_moved = 2;
                }
                else if(a.color == "Blue" && a.move == 2){
                    p1.movePlayer(5);
                    tiles_moved = 5;
                }
            }
            else if(p1.getPlayerPosition() % 3 == 1){
                if(a.color == "Magenta" && a.move == 1){
                    p1.movePlayer(2);
                    tiles_moved = 2;
                }
                else if(a.color == "Magenta" && a.move == 2){
                    p1.movePlayer(5);
                    tiles_moved = 5;
                }
                else if(a.color == "Green" && a.move == 1){
                    p1.movePlayer(3);
                    tiles_moved = 3;
                }
                else if(a.color == "Green" && a.move == 2){
                    p1.movePlayer(6);
                    tiles_moved = 6;
                }
                else if(a.color == "Blue" && a.move == 1){
                    p1.movePlayer(1);
                    tiles_moved = 1;
                }
                else if(a.color == "Blue" && a.move == 2){
                    p1.movePlayer(4);
                    tiles_moved = 4;
                }
            }
            else{
                if(a.color == "Magenta" && a.move == 1){
                    p1.movePlayer(1);
                    tiles_moved = 1;
                }
                else if(a.color == "Magenta" && a.move == 2){
                    p1.movePlayer(4);
                    tiles_moved = 4;
                }
                else if(a.color == "Green" && a.move == 1){
                    p1.movePlayer(2);
                    tiles_moved = 2;
                }
                else if(a.color == "Green" && a.move == 2){
                    p1.movePlayer(5);
                    tiles_moved = 5;
                }
                else if(a.color == "Blue" && a.move == 1){
                    p1.movePlayer(3);
                    tiles_moved = 3;
                }
                else if(a.color == "Blue" && a.move == 2){
                    p1.movePlayer(6);
                    tiles_moved = 3;
                }
            }
            calamity(p1);

            if(isPositionCandyStore(p1.getPlayerPosition()) == true){
                char choice;
                cout << "You landed on a candy store! Would you like to go shopping? (y, n)" << endl;
                cin >> choice;
                if(choice == 'y'){
                    shopping(p1);
                }
            }
            if(board.isSpecialTile(p1.getPlayerPosition()) == true){
                int randomnum = -1;
                randomnum = rng(4, 1);
                if(randomnum == 1){  //shortcut tile
                    cout << "You found a hidden passage and advanced 4 tiles!" << endl;
                    p1.movePlayer(4);
                }
                else if(randomnum == 2){  // Ice cream Shop 
                    p2.setSkipTurnCounter(1);
                    cout << "You landed on an Ice Cream Shop and get another turn!" << endl;
                }
                else if(randomnum == 3){  // gumdrop forest
                    p1.movePlayer(-4);
                    int gold_lost = -1;
                    gold_lost = rng(10, 5);
                    if(gold_lost > p1.getGold()){
                        gold_lost = p1.getGold();
                    }
                    p1.setGold(p1.getGold() - gold_lost);
                    cout << "You are lost in the Gumdrop Forest! You move 4 tiles back and lose " << gold_lost << "gold!" << endl;
                }
                else{
                    p1.movePlayer(-tiles_moved);
                    cout << "You landed on a gingerbread house and it's sent you back to your previous tile!" << endl;
                }
            }
            if(board.isTileTreasure(p1.getPlayerPosition())){
                playTreasure(p1);
            }
            marshmallowHail(p1, p2);
            p1.setStamina(p1.getStamina() - 10);
            p1.displayStats();
            p2.setSkipTurnCounter(p2.getSkipTurnCounter() - 1);
            endturn = true;
        }
        else if(choice == 2){
            bool valid_input = false;
            p1.displayStats();
            string input;
            string lower_candy;
            cout << "Choose a candy to use! (enter candy name)" << endl;
            getline(cin, input);
            Candy temp_candy;

            transform(input.begin(), input.end(), input.begin(), ::tolower);
            for(int i = 0; i < 9; i++){
                lower_candy = p1.getInventoryElement(i).name;
                transform(lower_candy.begin(), lower_candy.end(), lower_candy.begin(), ::tolower);
                if(input == lower_candy){
                    temp_candy = p1.getInventoryElement(i);
                    valid_input = true;
                    break;
                }
            }
            if(valid_input == true){
                useCandy(p1, p2, temp_candy);
            }
            else{
                cout << "Invalid input!" << endl;
            }
        }
        else if(choice == 3){
            p1.displayStats();
        }
        else{
            cout << "Invalid input!" << endl;
        }

    } while(endturn == false);
}

