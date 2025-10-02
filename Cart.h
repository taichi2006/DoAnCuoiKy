#pragma once

#include <iostream>
#include "Food.h"
using namespace std;

struct Cart {
    string customerName;
    int tableId;
    string foodName;        // Tên món (cho hiển thị đơn giản)
    Food orderDetails[20];  // Danh sách các món trong đơn hàng
    int orderCount = 0;     // Số loại món trong đơn hàng
    int quantity;           // Tổng số lượng món
    int totalMoney;
    int totalTime;
    string status = "dang doi"; // 3 trang thai: "dang doi", "dang lam", "da xong"
    bool cancelFood=false;

};