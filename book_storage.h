#ifndef BOOK_STORAGE_H
#define BOOK_STORAGE_H

#include "book.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

class BookStorage {
public:
    // 将图书信息保存到CSV文件
    static bool saveToCSV(const std::vector<Book>& books, const std::string& filename) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            return false;
        }

        // 写入CSV头部
        file << "ISBN,书名,作者,出版年份,出版月份,出版日期,价格,总库存,可借数量\n";

        // 写入图书数据
        for (const auto& book : books) {
            file << book.ISBN << ","
                 << book.name << ","
                 << book.author << ","
                 << book.year << ","
                 << book.month << ","
                 << book.day << ","
                 << book.price << ","
                 << book.total << ","
                 << book.available << "\n";
        }

        file.close();
        return true;
    }

    // 从CSV文件加载图书信息
    static bool loadFromCSV(std::vector<Book>& books, const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            return false;
        }

        std::string line;
        // 跳过CSV头部
        std::getline(file, line);

        // 读取图书数据
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string field;
            Book book;

            // 读取每个字段
            std::getline(ss, book.ISBN, ',');
            std::getline(ss, book.name, ',');
            std::getline(ss, book.author, ',');
            
            std::getline(ss, field, ',');
            book.year = std::stoi(field);
            std::getline(ss, field, ',');
            book.month = std::stoi(field);
            std::getline(ss, field, ',');
            book.day = std::stoi(field);
            
            std::getline(ss, field, ',');
            book.price = std::stof(field);
            std::getline(ss, field, ',');
            book.total = std::stoi(field);
            std::getline(ss, field, ',');
            book.available = std::stoi(field);

            // 设置日期数组
            book.datetime[0] = book.year;
            book.datetime[1] = book.month;
            book.datetime[2] = book.day;

            // 初始化借阅状态数组
            for (int i = 0; i < 100; i++) {
                book.borrowed[i] = false;
            }

            books.push_back(book);
        }

        file.close();
        return true;
    }
};

#endif // BOOK_STORAGE_H