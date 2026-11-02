#pragma once
#include <string>
#include <vector>
#include <iostream>

struct UserRecord {
    std::string username;
    int totalQuestions; // 总答题数
    int correctQuestions; // 总答对数
    int totalTime; // 总用时（秒）

    // 计算正确率
    double getAccuracy() const {
        if (totalQuestions == 0) return 0.0;
        return (double)correctQuestions / totalQuestions * 100.0;
    }
};

class UserManager {
private:
    std::vector<UserRecord> users;
    std::string currentUser;
    const std::string userFile = "users_rank.txt";

public:
    UserManager();
    void loadUsers();
    void saveUsers();

    bool registerUser(const std::string& username);
    bool login(const std::string& username);
    void logout();
    std::string getCurrentUser() const { return currentUser; }

    // 更新当前用户的成绩数据
    void updateCurrentUserStats(int addQuestions, int addCorrects, int addTime);

    // 显示排名
    void showRankByAccuracy();
    void showRankByTime();
}; 
