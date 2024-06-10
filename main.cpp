#include <iostream>
#include <windows.h>
#include <conio.h> 
#include <array>
#include <vector>
#include <string>

#include "headers/functions/functions.hpp"
#include "headers/questions/questions.hpp"
#include "headers/lifebuoys/lifebuoys.hpp"

using namespace std;

int main(){
    std::string filename = "pytania.txt";
    std::vector<Question> questions = LoadQuestions(filename);
    std::vector<int> old_questions(15, -1); //szablony (vector)
    std::vector<int> znane_liczby(2,0), pytania_pol(2,0);

    Licznik points(0);
    Licznik question_counter = points;

    Kolo_ratunkowe *pol_pol = new Pol_na_pol();
    Kolo_ratunkowe *telefon = new Telefon();
    Kolo_ratunkowe *widownia = new Widownia();
    int kolo_ratunkowe;

    int Set[] = {9,7,7}, color[] = {9,7,7,7};
    int counter = 1, old_x, old_y, qcounter = 1;
    int length, i = 0;
    string wygrana, odp;
    bool unique = false;
    char menu_key;
    bool used_pol_pol = false;
    COORD c = {0,0};//koordynaty opcji
    COORD m = {0,0};//koordynaty nagłówka
    COORD kolo = {0,0};//koordynaty kół ratunkowych
    array<int, 2> console_size = GetConsoleSize();//pobieranie rozmiarów konsoli
    old_x = console_size[0];
    old_y = console_size[1];
    system("CLS");
    SetConsoleOutputCP(65001);
    ShowConsoleCursor(false);
    i = getRandomIndex(questions);
    
    while(1){
        console_size = GetConsoleSize();
        c.X = (console_size[0]/2-6);
        c.Y = (console_size[1]/2-5);
        m.X = (console_size[0]/2-3);
        m.Y = (console_size[1]/2-5);
        c.Y = console_size[1]/2-5;
        if (old_x != console_size[0]){
            system("CLS");
            old_x = console_size[0];
        }
        if (old_y != console_size[1]){
            system("CLS");
            old_y = console_size[1];
        }
        SetCoursor(m);
        SetColor(2);
        cout<<"Menu"<<endl;
        SetColor(Set[0]);
        c.Y++;
        SetCoursor(c);
        cout<<"1. Zacznij grę\n";
        SetColor(Set[1]);
        c.Y++;
        SetCoursor(c);
        cout<<"2. O grze\n";
        SetColor(Set[2]);
        c.Y++;
        SetCoursor(c);
        cout<<"3. Wyjście\n"; 
        
        menu_key = _getch();   
        if (menu_key == 72 && (counter >= 2 && counter <=3)){
            counter--;
        }
        else if (menu_key == 80 && (counter >= 1 && counter <=2)){
            counter++; 
        }
        else if (menu_key == '\r'){
            switch(counter){
                case 1:
                    system("CLS");
                    qcounter = 1;
                    color[0] = 9;
                    color[1] = 7;
                    color[2] = 7;
                    color[3] = 7;
                    while(1){
                        length = questions[i].getContent().length();
                        console_size = GetConsoleSize();
                        c.X = (console_size[0]/2-6);
                        c.Y = (console_size[1]/2-5);
                        m.X = (console_size[0]/2-(length/2));
                        m.Y = (console_size[1]/2-5);
                        c.Y = console_size[1]/2-5;
                        kolo.Y = 0;
                        if (old_x != console_size[0]){
                            system("CLS");
                            old_x = console_size[0];
                        }
                        if (old_y != console_size[1]){
                            system("CLS");
                            old_y = console_size[1];
                        }
                        SetColor(2);
                        SetCoursor(m);
                        c.Y++;
                        cout<<"Pytanie "<< question_counter.getWartosc()+1 <<": "<< questions[i].getContent();
                        SetColor(color[0]);
                        SetCoursor(c);
                        c.Y++;
                        cout<<"A: "<< questions[i].getAnswerA();
                        SetColor(color[1]);
                        SetCoursor(c);
                        c.Y++;
                        cout<<"B: "<< questions[i].getAnswerB();
                        SetColor(color[2]);
                        SetCoursor(c);
                        c.Y++;
                        cout<<"C: "<< questions[i].getAnswerC();
                        SetColor(color[3]);
                        SetCoursor(c);
                        cout<<"D: "<< questions[i].getAnswerD();
                        SetColor(3);
                        SetCoursor(kolo);
                        cout<<"Koła ratunkowe: ";
                        kolo.Y++;
                        SetCoursor(kolo);
                        if(!widownia->available){SetColor(8);}
                        cout<<"W: Pytanie do Widownia ";
                        SetColor(3);
                        kolo.Y++; 
                        SetCoursor(kolo);
                        if(!pol_pol->available){SetColor(8);}
                        cout<<"P: 50 na 50 ";
                        SetColor(3);
                        kolo.Y++; 
                        SetCoursor(kolo);
                        if(!telefon->available){SetColor(8);}
                        cout<<"T: Telefon do przyjaciela ";
                        menu_key = _getch(); 
                        if (menu_key == 72 && (qcounter >= 2 && qcounter <=4)){
                            qcounter--;
                        }
                        else if (menu_key == 80 && (qcounter >= 1 && qcounter <=3)){
                            qcounter++; 
                        }
                        else if (menu_key == '\r'){
                            if (qcounter == questions[i].getCorrectAnswer()){
                                if (used_pol_pol){used_pol_pol = false;}
                                old_questions[question_counter.getWartosc()] = i;
                                ++points; //przeciążanie operatora
                                qcounter = 1;
                                if (points.getWartosc() < 12){
                                    try{ //wyjątki
                                        i = getRandomIndex(questions);                                  
                                        while (!unique) {
                                            unique = true;
                                            for (auto& x : old_questions) { // zakresowa pętla for i iteratory
                                                if (i == x) {
                                                    i = getRandomIndex(questions);
                                                    unique = false;
                                                    break;
                                                }
                                            }
                                        }

                                        if( i == -1){throw "Błąd w losowaniu pytania";}
                                    }  
                                    catch(const char* msg){
                                        m.X = (console_size[0]/2);
                                        m.Y = (console_size[1]/2);
                                        SetColor(4);
                                        SetCoursor(m);
                                        cerr<<"Wystąpił wyjątek: "<<msg;
                                        _getch();
                                    }
                                    unique = false;
                                    ++question_counter; //przeciążanie operatora
                                    system("CLS");
                                }
                                else{
                                    widownia->available = true;
                                    pol_pol->available = true;
                                    telefon->available = true;
                                    used_pol_pol = false;
                                    fill(old_questions.begin(), old_questions.end(), -1); //iteratory old_questions.begin(), old_questions.end()
                                    system("CLS");
                                    m.X = (console_size[0]/2-13);
                                    SetCoursor(m);
                                    SetColor(6);
                                    cout<<"Wygrałeś 1 milion złotych!!";
                                    _getch();
                                    i = getRandomIndex(questions);
                                    resetuj(question_counter);
                                    system("CLS");
                                    resetuj(points);
                                    break; 
                                }
                            }
                            else{
                                widownia->available = true;
                                pol_pol->available = true;
                                telefon->available = true;
                                used_pol_pol = false;
                                fill(old_questions.begin(), old_questions.end(), -1);
                                i = getRandomIndex(questions);
                                system("CLS");
                                m.X = (console_size[0]/2-12);
                                SetCoursor(m);
                                SetColor(3);
                                cout<<"Nie udało ci się wygrać.";
                                if(points.getWartosc() < 2){wygrana = "0";}
                                if(points.getWartosc() >= 2 && points.getWartosc() < 7){wygrana = "1'000";}
                                if(points.getWartosc() >= 7){wygrana = "40'000";}
                                m.Y++;
                                m.X = (console_size[0]/2-((14+wygrana.size())/2));
                                SetCoursor(m);
                                cout<<"Zdobyłeś: "<<wygrana<<" zł.";
                                _getch();
                                resetuj(question_counter);
                                system("CLS");
                                resetuj(points);
                                break; 
                            }
                        }
                        else if(((menu_key == 'w') && (widownia->available)) || ((menu_key == 't') && (telefon->available)) || ((menu_key == 'p') && (pol_pol->available) && (!used_pol_pol))){
                            switch(menu_key){
                                case 'w':
                                    kolo_ratunkowe = widownia->use(questions[i].getCorrectAnswer()); //polimorfizm
                                    widownia->available = false;
                                    c.Y++;
                                    c.X = (console_size[0]/2-13);
                                    if(kolo_ratunkowe == 1){odp="A";}
                                    if(kolo_ratunkowe == 2){odp="B";}
                                    if(kolo_ratunkowe == 3){odp="C";}
                                    if(kolo_ratunkowe == 4){odp="D";}
                                    SetCoursor(c);
                                    SetColor(3);
                                    cout<<"Widownia zagłosowała na: "<<odp;
                                    break;
                                case 't':
                                    kolo_ratunkowe = telefon->use(questions[i].getCorrectAnswer()); //polimorfizm
                                    telefon->available = false;
                                    c.Y++;
                                    c.X = (console_size[0]/2-19);
                                    if(kolo_ratunkowe == 1){odp="A";}
                                    if(kolo_ratunkowe == 2){odp="B";}
                                    if(kolo_ratunkowe == 3){odp="C";}
                                    if(kolo_ratunkowe == 4){odp="D";}
                                    SetCoursor(c);
                                    SetColor(3);
                                    cout<<"Przyjaciel twierdzi, że to odpowiedź: "<<odp;
                                    break;
                                case 'p':
                                    kolo_ratunkowe = pol_pol->use(questions[i].getCorrectAnswer()); //polimorfizm
                                    pol_pol->available = false;
                                    znane_liczby[0] = kolo_ratunkowe;
                                    znane_liczby[1] = questions[i].getCorrectAnswer();
                                    pytania_pol = znajdzPozostaleLiczby(znane_liczby);
                                    used_pol_pol = true;
                                    qcounter = kolo_ratunkowe;
                                    color[pytania_pol[0]-1] = 8;
                                    color[pytania_pol[1]-1] = 8;
                                    color[znane_liczby[0]-1] = 9;
                                    color[znane_liczby[1]-1] = 7;
                                    break;
                            }
                        }

                        if(!used_pol_pol){
                            color[0] = 7;
                            color[1] = 7;
                            color[2] = 7; 
                            color[3] = 7;
                            if (qcounter == 1){color[0] = 9;}
                            if (qcounter == 2){color[1] = 9;}
                            if (qcounter == 3){color[2] = 9;}
                            if (qcounter == 4){color[3] = 9;}
                        }

                        if(used_pol_pol){
                            if (znane_liczby[0]>znane_liczby[1]){
                                if(menu_key == 72){
                                    qcounter = znane_liczby[1];
                                    color[znane_liczby[1]-1] = 9;
                                    color[znane_liczby[0]-1] = 7;
                                }
                                if (menu_key == 80){
                                    qcounter = znane_liczby[0];
                                    color[znane_liczby[0]-1] = 9;
                                    color[znane_liczby[1]-1] = 7;
                                }
                            }
                            else{
                                if(menu_key == 72){
                                    qcounter = znane_liczby[0];
                                    color[znane_liczby[0]-1] = 9;
                                    color[znane_liczby[1]-1] = 7;
                                }
                                if (menu_key == 80){
                                    qcounter = znane_liczby[1];
                                    color[znane_liczby[1]-1] = 9;
                                    color[znane_liczby[0]-1] = 7;
                                }
                            }
                        }
                    }
                    break;
                case 2:
                    system("CLS");
                    SetColor(9);
                    m.X = (console_size[0]/2-7);
                    SetCoursor(m);
                    cout<<"Gra Milionerzy";
                    m.Y++;
                    m.X = (console_size[0]/2-25);
                    SetCoursor(m);
                    cout<<"Aby wygrać trzeba odpowiedzieć poprawnie na 12 pytań";
                    m.Y++;
                    m.X = (console_size[0]/2-11);
                    SetCoursor(m);
                    cout<<"Progi gwarantowane to:";
                    m.Y++;
                     m.X = (console_size[0]/2-24);
                    SetCoursor(m);
                    SetColor(6);
                    cout<<"2. 1000 zł , 7. 40'000 zł oraz 12. 1'000'000 zł";
                    _getch();
                    system("CLS");
                    break;
                case 3:
                    system("CLS");
                    SetColor(4);  
                    SetCoursor(m);  
                    cout<<"Wychodzenie...\n";
                    Sleep(1000);
                    ShowConsoleCursor(true);
                    SetColor(7);
                    system("CLS");
                    exit(0);
                    break;
            }
        }else{
            SetCoursor(c);
            continue;
        }

        Set[0] = 7;
        Set[1] = 7;
        Set[2] = 7; 

        if (counter == 1){Set[0] = 9;}
        if (counter == 2){Set[1] = 9;}
        if (counter == 3){Set[2] = 9;}
        SetCoursor(c);
    }
    return 0;
}