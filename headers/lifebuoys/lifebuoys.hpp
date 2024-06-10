#include <iostream>
class Kolo_ratunkowe { //klasa abstrakcyjna
public:
    explicit Kolo_ratunkowe();
    virtual int use(int); // czysto wirtualna metoda
    bool available;
};

class Pol_na_pol : public Kolo_ratunkowe { //dziedziczenie  
public:
    int use(int) override;
};

class Widownia : public Kolo_ratunkowe {
public:
    int use(int) override;
};

class Telefon : public Kolo_ratunkowe {
public:
    int use(int) override;
};