#include "UserManager.h"
#include <fstream>
#include <algorithm>
#include <iomanip>

using namespace std;

UserManager::UserManager() { loadUsers(); }

void UserManager::loadUsers() {
    ifstream in(userFile);
    if (!in.is_open()) return;
    UserRecord u;
    while (in >> u.username >> u.totalQuestions >> u.correctQuestions >> u.totalTime) {
        users.push_back(u);
    }
    in.close();
}

void UserManager::saveUsers() {
    ofstream out(userFile);
    for (const auto& u : users) {
        out << u.username << " " << u.totalQuestions << " " << u.correctQuestions << " " << u.totalTime << "\n";
    }
    out.close();
}

bool UserManager::registerUser(const string& username) {
    for (const auto& u : users) {
        if (u.username == username) return false;
    }
    users.push_back({ username, 0, 0, 0 });
    saveUsers();
    return true;
}

bool UserManager::login(const string& username) {
    for (const auto& u : users) {
        if (u.username == username) {
            currentUser = username;
            return true;
        }
    }
    return false;
}

void UserManager::logout() { currentUser = ""; }

void UserManager::updateCurrentUserStats(int addQuestions, int addCorrects, int addTime) {
    for (auto& u : users) {
        if (u.username == currentUser) {
            u.totalQuestions += addQuestions;
            u.correctQuestions += addCorrects;
            u.totalTime += addTime;
            break;
        }
    }
    saveUsers();
}

void UserManager::showRankByAccuracy() {
    vector<UserRecord> sorted = users;
    sort(sorted.begin(), sorted.end(), [](const UserRecord& a, const UserRecord& b) {
        return a.getAccuracy() > b.getAccuracy();
        });
    cout << "\n=========== 正确率排行榜 ===========" << endl;
    cout << "排名\t用户名\t\t正确率\t\t答题数" << endl;
    for (size_t i = 0; i < sorted.size(); i++) {
        cout << i + 1 << "\t" << left << setw(10) << sorted[i].username
            << fixed << setprecision(1) << sorted[i].getAccuracy() << "%\t\t" << sorted[i].totalQuestions << endl;
    }
}

void UserManager::showRankByTime() {
    vector<UserRecord> sorted = users;
    sort(sorted.begin(), sorted.end(), [](const UserRecord& a, const UserRecord& b) {
        return a.totalTime < b.totalTime;
        });
    cout << "\n=========== 速度排行榜 ===========" << endl;
    cout << "排名\t用户名\t\t总用时" << endl;
    for (size_t i = 0; i < sorted.size(); i++) {
        cout << i + 1 << "\t" << left << setw(10) << sorted[i].username
            << sorted[i].totalTime << " 秒" << endl;
    }
}