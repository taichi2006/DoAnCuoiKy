#pragma once
#include<iostream>
using namespace std;

struct Food {
    string name;
    int price;
    int time;
    int quantity = 0;  // Số lượng (dùng khi lưu trong Cart)
};
