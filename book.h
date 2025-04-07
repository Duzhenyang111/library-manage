#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <vector>

// 图书节点类
class Book {
public:
    std::string ISBN;         // 国际标准书号
    std::string name;         // 书名
    std::string author;       // 作者
    int year;            // 出版年份
    int month;           // 出版月份
    int day;             // 出版日期
    int datetime[3];     // 装入书的年、月、日，以便比较
    float price;         // 图书价格
    int total;           // 总库存量
    int available;       // 可借数量
    bool borrowed[100];  // 借阅状态数组，true表示已借出，false表示可借
};

#endif // BOOK_H