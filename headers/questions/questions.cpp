#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <random>
#include <cstdlib>
#include <ctime>

#include "questions.hpp"

using namespace std;

Question::Question(string cont, string ans_a, string ans_b, string ans_c, string ans_d, int cor_ans){
    answer_a = ans_a;
    answer_b = ans_b;
    answer_c = ans_c;
    answer_d = ans_d;
    content = cont;
    correct_answer = cor_ans;
}

Question::~Question(){
    cout<<"Pomyślnie załadowano pytanie!"<<endl;
}

std::string Question::getContent() const { return content; }
std::string Question::getAnswerA() const { return answer_a; }
std::string Question::getAnswerB() const { return answer_b; }
std::string Question::getAnswerC() const { return answer_c; }
std::string Question::getAnswerD() const { return answer_d; }
int Question::getCorrectAnswer() const { return correct_answer; }

std::vector<Question> LoadQuestions(std::string filename){
    std::vector<Question> questions;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Nie można otworzyć pliku: " << filename << std::endl;
        return questions; // Zwraca pusty wektor w przypadku błędu
    }

    std::string content, ans_a, ans_b, ans_c, ans_d, cor_ans_str;
    int cor_ans;

    while (std::getline(file, content) && std::getline(file, ans_a) && 
           std::getline(file, ans_b) && std::getline(file, ans_c) && 
           std::getline(file, ans_d) && std::getline(file, cor_ans_str)) {
            std::istringstream(cor_ans_str) >> cor_ans;
        questions.emplace_back(content, ans_a, ans_b, ans_c, ans_d, cor_ans);
    }

    file.close();
    return questions;
}

int getRandomIndex(const std::vector<Question>& vec) {
    if (vec.empty()) {
        throw std::invalid_argument("Vector is empty");
    }

    srand((unsigned) time(NULL));
    int random = (rand() % vec.size());
    return random;
}