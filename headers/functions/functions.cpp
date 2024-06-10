#include <iostream>
#include <windows.h>
#include <array>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>


#include "functions.hpp"

void SetColor(int color){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO     cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; 
    SetConsoleCursorInfo(out, &cursorInfo);
}

void SetCoursor(COORD c){
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

std::array<int, 2> GetConsoleSize(){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;
  
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    return {columns, rows};  
}

std::vector<int> znajdzPozostaleLiczby(std::vector<int> znaneLiczby) {
    std::vector<int> wszystkieLiczby = {1, 2, 3, 4};

    for (int i = 0; i < znaneLiczby.size(); i++) {
        wszystkieLiczby.erase(std::remove(wszystkieLiczby.begin(), wszystkieLiczby.end(), znaneLiczby[i]), wszystkieLiczby.end());
    }

    return wszystkieLiczby;
}

Licznik::Licznik(int w) : wartosc(w) { }// konstruktor

Licznik::Licznik(const Licznik& inny) : wartosc(inny.wartosc) { }// konstruktor kopiujący

Licznik& Licznik::operator++() { //przeciążanie operatora
    ++this->wartosc;
    return *this;
}

int Licznik::getWartosc() const {
    return this->wartosc;
}

void Licznik::setWartosc(int w) {
    this->wartosc = w;
}

void resetuj(Licznik& l) {
    l.wartosc = 0;
}