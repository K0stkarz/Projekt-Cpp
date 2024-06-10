#include <iostream>
#include <random>
#include <ctime>
#include "lifebuoys.hpp"

int Kolo_ratunkowe::use(int correct_answer){} //polimorfizm

Kolo_ratunkowe::Kolo_ratunkowe(){
    available = true;
}

int Pol_na_pol::use(int correct_answer){ //algorytmy
    srand((unsigned) time(NULL));
    int random = (rand() % 4) + 1;
    if (random == correct_answer){
        if (random == 4){
            return --random;
        }
        if(random == 3){
            return ++random;
        }
        return ++random;
    }
    return random;
}

int Widownia::use(int correct_answer){
    srand((unsigned) time(NULL));
    int random = (rand() % 100) + 1;
    if (random >= 25 & random <= 50 || random >= 75){
        return correct_answer;
    } 
    random = (rand() % 4) + 1;
    return random;
}

int Telefon::use(int correct_answer){
    srand((unsigned) time(NULL));
    int random = (rand() % 1000) + 1;
    if (random < 501 || random > 750){
        return correct_answer;
    }
    if (correct_answer == 4){
       return correct_answer--;
    }
    return correct_answer++;
}