#include <iostream>
#include <Windows.h>
#include <fstream>
#include <conio.h>
#include <ctime>
#include <string>
#include "book_manager.h"

using namespace std;

// 全局变量
BookManager library;

// 函数声明
void adminSystem();
void userSystem();

// 管理员系统
void adminSystem() {
    system("cls");
    string password = "admin123";  // 管理员密码
    string input;
    cout << "请输入管理员密码：";
    cin >> input;

    if (input != password) {
        cout << "\n密码错误！按任意键返回...";
        _getch();
        system("cls");
        return;
    }

    char choice;
    do {
        cout << "\n\t\t\t\t欢迎进入管理员系统\n\n";
        cout << "\n\t\t\t\t1.录入图书";
        cout << "\n\t\t\t\t2.显示图书";
        cout << "\n\t\t\t\t3.查找图书";
        cout << "\n\t\t\t\t4.修改图书";
        cout << "\n\t\t\t\t5.删除图书";
        cout << "\n\t\t\t\t6.统计信息";
        cout << "\n\t\t\t\t7.返回主菜单";
        cout << "\n\n\n\t\t\t\t请选择：";
        cin >> choice;

        switch (choice) {
        case '1': library.input(); break;
        case '2': library.show(); break;
        case '3': library.search(); break;
        case '4': library.change(); break;
        case '5': library.del(); break;
        case '6': library.statistics(); break;
        case '7': system("cls"); return;
        default:
            cout << "\n\a\t\t\t\t选择有误！请重新选择。";
            break;
        }
    } while (true);
}

// 用户系统
void userSystem() {
    system("cls");
    char choice;
    do {
        cout << "\n\t\t\t\t欢迎进入用户系统\n\n";
        cout << "\n\t\t\t\t1.查看图书";
        cout << "\n\t\t\t\t2.借阅图书";
        cout << "\n\t\t\t\t3.归还图书";
        cout << "\n\t\t\t\t4.返回主菜单";
        cout << "\n\n\n\t\t\t\t请选择：";
        cin >> choice;

        switch (choice) {
        case '1': 
            library.input(); 
            system("cls");
            break;
        case '2': 
            library.show(); 
            system("cls");
            break;
        case '3': 
            library.search(); 
            system("cls");
            break;
        case '4': 
            library.change(); 
            system("cls");
            break;
        case '5': 
            library.del(); 
            system("cls");
            break;
        case '6': 
            library.statistics(); 
            system("cls");
            break;
        case '7': system("cls"); return;
        default:
            cout << "\n\a\t\t\t\t选择有误！请重新选择。";
            system("cls");
            break;
        }
    } while (true);
}

// 主函数
int main() {
    char choice;
    do {
        cout << endl << endl << endl << endl;
        cout << "\t\t\t\t欢迎使用图书管理系统";
        cout << endl << endl << endl;
        cout << "\n\t\t\t\t1.管理员系统";
        cout << "\n\t\t\t\t2.用户系统";
        cout << "\n\t\t\t\t3.退出系统";
        cout << "\n\n\n\t\t\t\t请选择：";
        cin >> choice;

        while (choice != '1' && choice != '2' && choice != '3') {
            cout << "\n\a\t\t\t\t选择有误！请重新选择。";
            cout << "\n\t\t\t\t请选择：";
            cin >> choice;
        }

        switch (choice) {
        case '1':
            adminSystem();
            break;
        case '2':
            userSystem();
            break;
        case '3':
            cout << "\n\n感谢使用图书管理系统，再见！\n";
            return 0;
        }
    } while (true);

    return 0;
}