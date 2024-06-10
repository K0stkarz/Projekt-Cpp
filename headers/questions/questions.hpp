class Question{
public:
    explicit Question(std::string, std::string, std::string, std::string, std::string, int);
    ~Question(); 
    std::string getContent() const;
    std::string getAnswerA() const;
    std::string getAnswerB() const;
    std::string getAnswerC() const;
    std::string getAnswerD() const;
    int getCorrectAnswer() const;
private:
    std::string answer_a, answer_b, answer_c, answer_d, content;
    int correct_answer;
};

std::vector<Question> LoadQuestions(std::string);
int getRandomIndex(const std::vector<Question>& vec);

