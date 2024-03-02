#include "Player.h"
#include "rng.h"
#include <iostream>
#include <cstdlib>

using namespace std;

int rng(int up, int lb){
    int randomnum = 0;
    randomnum = (rand()%(up + 1 - lb)) + lb;
    return randomnum;
}
