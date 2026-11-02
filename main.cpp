#include <iostream>
#include <ctime>
#include <cstdlib>
#include <limits>
#include "UserManager.h"
#include "QuestionBank.h"

using namespace std;

int main() {
    srand((unsigned int)time(0));
    UserManager userMgr;
    QuestionBank bank(userMgr);

    cout << "======================================" << endl;
    cout << "      几何图形练习系统     " << endl;
    cout << "======================================" << endl;

    int loginChoice = 0;
    while (userMgr.getCurrentUser().empty()) {
        cout << "\n1. 登录\n2. 注册\n3. 查看排行榜\n0. 退出\n请选择: ";
        cin >> loginChoice;

        if (loginChoice == 1 || loginChoice == 2) {
            string username;
            cout << "请输入用户名: "; cin >> username;
            if (loginChoice == 1) {
                if (!userMgr.login(username)) cout << "登录失败，用户不存在！\n";
                else {
                    cout << "登录成功！\n";
                    bank.loadFromFile();
                }
            }
            else {
                if (userMgr.registerUser(username)) cout << "注册成功，请登录！\n";
                else cout << "注册失败，用户名已存在！\n";
            }
        }
        else if (loginChoice == 3) {
            userMgr.showRankByAccuracy();
            userMgr.showRankByTime();
        }
        else if (loginChoice == 0) return 0;
    }

    int choice = 0;
    do {
        cout << "\n========== 用户: " << userMgr.getCurrentUser() << " ==========" << endl;
        cout << "1. 生成新题目（随机）" << endl;
        cout << "2. 开始答题" << endl;
        cout << "3. 排序(按面积)" << endl;
        cout << "4. 检查/回看题目记录" << endl;
        cout << "5. 错题重做" << endl;
        cout << "6. 手动添加题目" << endl;
        cout << "7. 手动删除题目" << endl;
        cout << "8. 查看本地历史成绩" << endl;
        cout << "9. 查看全局排行榜" << endl;
        cout << "10. 注销/切换账号" << endl;
        cout << "0. 退出系统 (自动保存)" << endl;
        cout << "请选择: ";

        if (!(cin >> choice)) {
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1;
        }

        switch (choice) {
        case 1: { int n; cout << "生成数量: "; cin >> n; bank.initQuestions(n); break; }
        case 2: bank.runQuiz(); break;
        case 3: bank.sortQuestions(); break;
        case 4: bank.viewAllQuestions(); break;
        case 5: bank.retryWrongQuestions(); break;
        case 6: bank.addShapeManually(); break;
        case 7: bank.deleteShapeManually(); break;
        case 8: bank.viewHistory(); break;
        case 9:
            userMgr.showRankByAccuracy();
            userMgr.showRankByTime();
            break;
        case 10:
            bank.saveToFile();
            userMgr.logout();
            bank.clearAllShapes();
            cout << "已注销。请重新启动程序登录。" << endl;
            return 0;
        case 0:
            bank.saveToFile();
            cout << "数据已保存，感谢使用！" << endl;
            break;
        default: cout << "输入无效！" << endl; break;
        }
    } while (choice != 0);

    return 0;
}