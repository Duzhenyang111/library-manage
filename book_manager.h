#ifndef BOOK_MANAGER_H
#define BOOK_MANAGER_H

#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <vector>
#include "book.h"
#include "book_storage.h"

class BookManager {
private:
    Book books[100];     // 类中构建一个一维数组，装入按设置的结构体形式的各个图书
    int count;           // 图书的数量

    // 日期比较函数
    int datecmp(int a[], int b[], int n) {
        for (int i = 0; i < n; i++) {
            if (a[i] != b[i]) {
                return a[i] - b[i];
            }
        }
        return 0;
    }

    // 辅助函数
    void saveToFile() {
        std::vector<Book> bookList;
        for (int i = 0; i < count; i++) {
            bookList.push_back(books[i]);
        }
        BookStorage::saveToCSV(bookList, "books.csv");
    }

    void loadFromFile() {
        std::vector<Book> bookList;
        if (BookStorage::loadFromCSV(bookList, "books.csv")) {
            count = 0;
            for (const auto& book : bookList) {
                if (count < 100) {
                    books[count] = book;
                    count++;
                }
            }
        }
    }

public:
    BookManager() : count(0) {
        loadFromFile();
    }

    ~BookManager() {
        saveToFile();
    }

    // 排序函数
    int sort(int i) {
        for (int j = 0; j < count - 1; j++) {
            for (int k = 0; k < count - 1 - j; k++) {
                if (datecmp(books[k].datetime, books[k + 1].datetime, 3) > 0) {
                    Book temp = books[k];
                    books[k] = books[k + 1];
                    books[k + 1] = temp;
                }
            }
        }
        return 0;
    }

    // 输入图书数据的函数
    void input() {
        if (count >= 100) {
            std::cout << "\n图书库已满！\n";
            return;
        }

        std::cout << "\n请输入图书信息：\n";
        std::cout << "ISBN：";
        std::cin >> books[count].ISBN;
        std::cout << "书名：";
        std::cin >> books[count].name;
        std::cout << "作者：";
        std::cin >> books[count].author;
        std::cout << "出版日期（年 月 日）：";
        std::cin >> books[count].year >> books[count].month >> books[count].day;
        books[count].datetime[0] = books[count].year;
        books[count].datetime[1] = books[count].month;
        books[count].datetime[2] = books[count].day;
        std::cout << "价格：";
        std::cin >> books[count].price;
        std::cout << "库存量：";
        std::cin >> books[count].total;
        books[count].available = books[count].total;
        for (int i = 0; i < 100; i++) {
            books[count].borrowed[i] = false;
        }

        count++;
        sort(count);
        std::cout << "\n图书添加成功！\n";
        saveToFile();
    }

    // 显示所有图书的函数
    void show() {
        if (count == 0) {
            std::cout << "\n暂无图书信息！\n";
            return;
        }

        std::cout << "\n图书信息如下：\n";
        std::cout << std::setw(15) << "ISBN" << std::setw(20) << "书名" << std::setw(15) << "作者"
                  << std::setw(15) << "出版日期" << std::setw(10) << "价格" << std::setw(10)
                  << "库存" << std::setw(10) << "可借\n";

        for (int i = 0; i < count; i++) {
            std::cout << std::setw(15) << books[i].ISBN << std::setw(20) << books[i].name
                      << std::setw(15) << books[i].author << std::setw(6) << books[i].year
                      << "/" << std::setw(2) << books[i].month << "/" << std::setw(2)
                      << books[i].day << std::setw(10) << books[i].price << std::setw(10)
                      << books[i].total << std::setw(10) << books[i].available << "\n";
        }
    }

    // 搜索图书的函数
    void search() {
        if (count == 0) {
            std::cout << "\n暂无图书信息！\n";
            return;
        }

        std::cout << "\n请选择搜索方式：\n";
        std::cout << "1. 按ISBN搜索\n";
        std::cout << "2. 按书名搜索\n";
        std::cout << "3. 按作者搜索\n";
        char choice;
        std::cin >> choice;

        std::string keyword;
        std::cout << "请输入关键词：";
        std::cin >> keyword;

        bool found = false;
        for (int i = 0; i < count; i++) {
            bool match = false;
            switch (choice) {
                case '1': match = (books[i].ISBN == keyword); break;
                case '2': match = (books[i].name == keyword); break;
                case '3': match = (books[i].author == keyword); break;
            }

            if (match) {
                if (!found) {
                    std::cout << "\n找到以下图书：\n";
                    std::cout << std::setw(15) << "ISBN" << std::setw(20) << "书名" << std::setw(15)
                              << "作者" << std::setw(15) << "出版日期" << std::setw(10)
                              << "价格" << std::setw(10) << "库存" << std::setw(10) << "可借\n";
                }
                std::cout << std::setw(15) << books[i].ISBN << std::setw(20) << books[i].name
                          << std::setw(15) << books[i].author << std::setw(6) << books[i].year
                          << "/" << std::setw(2) << books[i].month << "/" << std::setw(2)
                          << books[i].day << std::setw(10) << books[i].price << std::setw(10)
                          << books[i].total << std::setw(10) << books[i].available << "\n";
                found = true;
            }
        }

        if (!found) {
            std::cout << "\n未找到相关图书！\n";
        }
    }

    // 修改图书信息的函数
    void change() {
        if (count == 0) {
            std::cout << "\n暂无图书信息！\n";
            return;
        }

        std::string isbn;
        std::cout << "\n请输入要修改的图书ISBN：";
        std::cin >> isbn;

        for (int i = 0; i < count; i++) {
            if (books[i].ISBN == isbn) {
                std::cout << "\n请输入新的图书信息：\n";
                std::cout << "书名（原：" << books[i].name << "）：";
                std::cin >> books[i].name;
                std::cout << "作者（原：" << books[i].author << "）：";
                std::cin >> books[i].author;
                std::cout << "出版日期（原：" << books[i].year << "/" << books[i].month
                          << "/" << books[i].day << "）：";
                std::cin >> books[i].year >> books[i].month >> books[i].day;
                books[i].datetime[0] = books[i].year;
                books[i].datetime[1] = books[i].month;
                books[i].datetime[2] = books[i].day;
                std::cout << "价格（原：" << books[i].price << "）：";
                std::cin >> books[i].price;
                std::cout << "库存量（原：" << books[i].total << "）：";
                std::cin >> books[i].total;
                books[i].available = books[i].total;

                sort(count);
                std::cout << "\n修改成功！\n";
                saveToFile();
                return;
            }
        }

        std::cout << "\n未找到该图书！\n";
    }

    // 删除图书的函数
    void del() {
        if (count == 0) {
            std::cout << "\n暂无图书信息！\n";
            return;
        }

        std::string isbn;
        std::cout << "\n请输入要删除的图书ISBN：";
        std::cin >> isbn;

        for (int i = 0; i < count; i++) {
            if (books[i].ISBN == isbn) {
                for (int j = i; j < count - 1; j++) {
                    books[j] = books[j + 1];
                }
                count--;
                std::cout << "\n删除成功！\n";
                saveToFile();
                return;
            }
        }

        std::cout << "\n未找到该图书！\n";
    }

    // 借书函数
    void borrow() {
        if (count == 0) {
            std::cout << "\n暂无图书信息！\n";
            return;
        }

        std::string isbn;
        std::cout << "\n请输入要借阅的图书ISBN：";
        std::cin >> isbn;

        for (int i = 0; i < count; i++) {
            if (books[i].ISBN == isbn) {
                if (books[i].available > 0) {
                    for (int j = 0; j < books[i].total; j++) {
                        if (!books[i].borrowed[j]) {
                            books[i].borrowed[j] = true;
                            books[i].available--;
                            std::cout << "\n借阅成功！\n";
                            saveToFile();
                            return;
                        }
                    }
                } else {
                    std::cout << "\n该图书已全部借出！\n";
                    return;
                }
            }
        }

        std::cout << "\n未找到该图书！\n";
    }

    // 还书函数
    void returnBook() {
        if (count == 0) {
            std::cout << "\n暂无图书信息！\n";
            return;
        }

        std::string isbn;
        std::cout << "\n请输入要归还的图书ISBN：";
        std::cin >> isbn;

        for (int i = 0; i < count; i++) {
            if (books[i].ISBN == isbn) {
                if (books[i].available < books[i].total) {
                    for (int j = 0; j < books[i].total; j++) {
                        if (books[i].borrowed[j]) {
                            books[i].borrowed[j] = false;
                            books[i].available++;
                            std::cout << "\n归还成功！\n";
                            saveToFile();
                            return;
                        }
                    }
                } else {
                    std::cout << "\n该图书未被借出！\n";
                    return;
                }
            }
        }

        std::cout << "\n未找到该图书！\n";
    }

    // 统计函数
    void statistics() {
        if (count == 0) {
            std::cout << "\n暂无图书信息！\n";
            return;
        }

        int totalBooks = 0;
        int totalBorrowed = 0;
        float totalValue = 0;

        for (int i = 0; i < count; i++) {
            totalBooks += books[i].total;
            totalBorrowed += (books[i].total - books[i].available);
            totalValue += books[i].price * books[i].total;
        }

        std::cout << "\n图书统计信息：\n";
        std::cout << "图书种类：" << count << "种\n";
        std::cout << "图书总量：" << totalBooks << "本\n";
        std::cout << "已借出：" << totalBorrowed << "本\n";
        std::cout << std::fixed << std::setprecision(2) << "库存总值：" << totalValue << "元\n";
    }
};

#endif // BOOK_MANAGER_H