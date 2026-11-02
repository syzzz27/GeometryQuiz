#pragma once
#include <string>
#include <vector>
#include "Shape.h"
#include "UserManager.h"

struct HistoryRecord {
    int practiceId;
    int correctCount;
    int wrongCount;
    int score;
};

class QuestionBank {
private:
    std::vector<Shape*> shapes;
    std::vector<HistoryRecord> history;
    int totalScore;
    UserManager& userMgr;

public:
    QuestionBank(UserManager& um);
    ~QuestionBank();

    void initQuestions(int num);
    void runQuiz();
    void viewAllQuestions() const;
    void retryWrongQuestions();
    void viewHistory() const;

    void addShapeManually();
    void deleteShapeManually();
    void clearAllShapes();
    void sortQuestions();

    void saveToFile() const;
    void loadFromFile();
};