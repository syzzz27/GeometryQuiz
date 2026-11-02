#include "QuestionBank.h"
#include "Circle.h"
#include "Square.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Trapezoid.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <ctime>

using namespace std;

QuestionBank::QuestionBank(UserManager& um) : userMgr(um), totalScore(0) {}
QuestionBank::~QuestionBank() { clearAllShapes(); }
void printNum(double num) {
    if (num == (int)num) {
        cout << (int)num;
    }
    else {
        cout << num;
    }
}


void QuestionBank::clearAllShapes() {
    for (size_t i = 0; i < shapes.size(); i++) delete shapes[i];
    shapes.clear();
    history.clear();
    totalScore = 0;
}

void QuestionBank::initQuestions(int num) {
    for (int i = 0; i < num; i++) {
        Shape* s = nullptr;
        switch (rand() % 5) {
        case 0: s = new Circle(); break;
        case 1: s = new Square(); break;
        case 2: s = new Rectangle(); break;
        case 3: s = new Triangle(); break;
        case 4: s = new Trapezoid(); break;
        }
        if (s) { s->genData(); shapes.push_back(s); }
    }
}

void QuestionBank::sortQuestions() {
    if (shapes.empty()) return;
    std::sort(shapes.begin(), shapes.end(), [](Shape* a, Shape* b) { return *a < *b; });
    cout << "★ 题目已按面积从小到大排序完成！" << endl;
}

void QuestionBank::runQuiz() {
    if (shapes.empty()) { cout << "题库为空，请先生成或加载题目！" << endl; return; }

    time_t startTime = time(0);
    totalScore = 0;
    int correctCount = 0;

    for (size_t i = 0; i < shapes.size(); i++) {
        Shape* s = shapes[i];
        cout << "\n---------------- 第 " << (i + 1) << " 题 ----------------" << endl;
        s->printShapeArt();
        s->printQuestion();

        double uArea, uPeri;
        cout << "请输入面积: "; cin >> uArea;
        cout << "请输入周长: "; cin >> uPeri;


        // 1. 判断逻辑：面积和周长都必须和正确答案（getPerimeter）比较
        bool correct = (abs(uArea - s->getArea()) < 0.1) && (abs(uPeri - s->getPerimeter()) < 0.1);
        s->setUserAnswer(uArea, uPeri, correct);

        if (correct) {
            cout << "★ 回答正确！" << endl;
            totalScore += 10;
            correctCount++;
        }
        else {
            cout << "☆ 回答错误。正确答案: 面积 ";
            printNum(s->getArea());

            cout << "，周长 ";
            printNum(s->getPerimeter());
            cout << endl;
        }
    }

    time_t endTime = time(0);
    int timeSpent = (int)difftime(endTime, startTime);

    HistoryRecord record;
    record.practiceId = history.size() + 1;
    record.correctCount = correctCount;
    record.wrongCount = shapes.size() - correctCount;
    record.score = totalScore;
    history.push_back(record);

    userMgr.updateCurrentUserStats(shapes.size(), correctCount, timeSpent);
    cout << "\n答题结束！本次得分: " << totalScore << " 分，用时: " << timeSpent << " 秒。" << endl;
}


// ----------------- 错题重做 -----------------
void QuestionBank::retryWrongQuestions() {
    bool hasWrong = false;
    for (size_t i = 0; i < shapes.size(); i++) {
        Shape* s = shapes[i];
        if (s->getIsAnswered() && !s->getIsCorrect()) {
            hasWrong = true;
            cout << "\n---------------- 错题重做 ----------------" << endl;
            s->printShapeArt();
            s->printQuestion();

            double uArea, uPeri;
            cout << "请重新计算面积: "; cin >> uArea;
            cout << "请重新计算周长: "; cin >> uPeri;

            // 面积和周长必须同时正确
            if (abs(uArea - s->getArea()) < 0.1 && abs(uPeri - s->getPerimeter()) < 0.1) {
                cout << "★ 这次完全答对了！" << endl;
                s->setUserAnswer(uArea, uPeri, true);
            }
            else {
                cout << "☆ 还是不对，正确答案是: 面积 " << s->getArea() << "，周长 " << s->getPerimeter() << endl;
            }
        }
    }
    if (!hasWrong) cout << "\n太棒了，全对，没有错题！" << endl;
} 

// ----------------- 手动添加题目 -----------------
void QuestionBank::addShapeManually() {
    int type;
    cout << "\n类型 (1.圆 2.正方形 3.长方形 4.三角形 5.梯形): ";
    cin >> type;

    switch (type) {
    case 1: { double r; cout << "半径: "; cin >> r; shapes.emplace_back(new Circle(r)); break; }
    case 2: { double s; cout << "边长: "; cin >> s; shapes.emplace_back(new Square(s)); break; }
    case 3: { double l, w; cout << "长和宽: "; cin >> l >> w; shapes.emplace_back(new Rectangle(l, w)); break; }
    case 4: { double a, b, c; cout << "三边: "; cin >> a >> b >> c; shapes.emplace_back(new Triangle(a, b, c)); break; }
    case 5: { double t, b, h, l1, l2; cout << "上底 下底 高 两腰: "; cin >> t >> b >> h >> l1 >> l2; shapes.emplace_back(new Trapezoid(t, b, h, l1, l2)); break; }
    default: cout << "无效！" << endl; return;
    }
    cout << "★ 添加成功！当前题数: " << shapes.size() << endl;
}

// ----------------- 手动删除题目 -----------------
void QuestionBank::deleteShapeManually() {
    if (shapes.empty()) return;
    viewAllQuestions();
    int index; cout << "要删除的题目编号: "; cin >> index;
    if (index >= 1 && index <= (int)shapes.size()) {
        int idx = index - 1;
        delete shapes[idx]; // 先释放内存
        shapes.erase(shapes.begin() + idx); // 再移除指针
        cout << "★ 删除成功！当前题数: " << shapes.size() << endl;
    }
    else cout << "编号无效！" << endl;
}

// ----------------- 查看所有题目 -----------------
void QuestionBank::viewAllQuestions() const {
    cout << "\n========= 所有题目记录 =========" << endl;
    if (shapes.empty()) { cout << "暂无题目。" << endl; return; }
    for (size_t i = 0; i < shapes.size(); i++) {
        cout << "第 " << (i + 1) << " 题：";
        shapes[i]->printQuestion();
        if (!shapes[i]->getIsAnswered()) cout << " [未答]" << endl;
        else if (shapes[i]->getIsCorrect()) cout << " [答对]" << endl;
        else cout << " [答错]" << endl;
    }
}

// ----------------- 查看历史成绩 -----------------
void QuestionBank::viewHistory() const {
    cout << "\n========= 我的历史做题记录 =========" << endl;
    if (history.empty()) { cout << "暂无记录。" << endl; return; }
    for (size_t i = 0; i < history.size(); i++) {
        cout << "第 " << history[i].practiceId << " 次: 对 " << history[i].correctCount
            << " 错 " << history[i].wrongCount << "，得分 " << history[i].score << endl;
    }
}

// ----------------- 保存文件 -----------------
void QuestionBank::saveToFile() const {
    if (userMgr.getCurrentUser().empty()) return;
    string filename = userMgr.getCurrentUser() + "_data.txt";
    ofstream out(filename);
    if (!out.is_open()) return;

    out << shapes.size() << " " << history.size() << "\n";
    for (size_t i = 0; i < shapes.size(); i++) {
        out << shapes[i]->getType() << " ";
        shapes[i]->saveData(out);
    }
    for (size_t i = 0; i < history.size(); i++) {
        out << history[i].practiceId << " " << history[i].correctCount << " "
            << history[i].wrongCount << " " << history[i].score << "\n";
    }
    out.close();
}

// ----------------- 读取文件 -----------------
void QuestionBank::loadFromFile() {
    if (userMgr.getCurrentUser().empty()) return;
    clearAllShapes();

    string filename = userMgr.getCurrentUser() + "_data.txt";
    ifstream in(filename);
    if (!in.is_open()) return;

    // 这里就是报 E0020 错误的地方，确保这两行变量声明在！
    int shapeCount = 0;
    int historyCount = 0;

    if (!(in >> shapeCount >> historyCount)) return;

    for (int i = 0; i < shapeCount; i++) {
        string type; in >> type;
        Shape* s = nullptr;
        if (type == "Circle") s = new Circle();
        else if (type == "Square") s = new Square();
        else if (type == "Rectangle") s = new Rectangle();
        else if (type == "Triangle") s = new Triangle();
        else if (type == "Trapezoid") s = new Trapezoid();

        if (s) { s->loadData(in); shapes.push_back(s); }
    }
    for (int i = 0; i < historyCount; i++) {
        HistoryRecord record;
        in >> record.practiceId >> record.correctCount >> record.wrongCount >> record.score;
        history.push_back(record);
    }
    in.close();
    cout << "★ 成功恢复用户 [" << userMgr.getCurrentUser() << "] 的 " << shapeCount << " 道题目记录。" << endl;
}