#include <windows.h>
#include <array>
#include <vector>
#include <string>


void SetColor(int);
void ShowConsoleCursor(bool);
void SetCoursor(COORD);
std::array<int, 2> GetConsoleSize();
std::vector<int> znajdzPozostaleLiczby(std::vector<int>);

class Licznik { //klasy
private:
    int wartosc;

public:
    Licznik(int w = 0);
    Licznik(const Licznik& inny);
    Licznik& operator++(); //przeciążanie operatora
    int getWartosc() const;
    void setWartosc(int w);
    friend void resetuj(Licznik& l); //deklaracja przyjaciela
};
