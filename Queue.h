#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>
#include "Cart.h"
#include "Table.h"
using namespace std;

struct Queue {
    int values[100]{}; // Lưu thời gian TTL ban đầu (giây)
    int cartIndexes[100]{}; // Lưu index của cart tương ứng
    chrono::steady_clock::time_point startTimes[100]{}; // Thời điểm bắt đầu
    int right = -1;
    bool processing = false; // Đánh dấu có timer đang chạy không
    Cart* cartArray = nullptr; // Pointer đến mảng cart
    Table* tableArray = nullptr;
    atomic<bool> autoUpdateRunning{false}; // Điều khiển background thread

    // Set cart array pointer
    void setCartArray(Cart* carts) {
        cartArray = carts;
    }

    void setTableArray(Table* table){
        tableArray = table;
    }

    // Bắt đầu background thread tự động cập nhật
    void startAutoUpdate() {
        if (!autoUpdateRunning) {
            autoUpdateRunning = true;
            thread autoThread(&Queue::backgroundUpdate, this);
            autoThread.detach();
        }
    }

    // Dừng background thread
    void stopAutoUpdate() {
        autoUpdateRunning = false;
    }

    // Background thread function
    void backgroundUpdate() {
        while (autoUpdateRunning) {
            this_thread::sleep_for(chrono::seconds(1)); // Kiểm tra mỗi giây
            autoPop(); // Tự động kiểm tra và cập nhật
        }
    }

    // push 1 timer, TTL tính bằng giây
    void push(int ttlSeconds, int cartIndex) {
        right++;
        values[right] = ttlSeconds;
        cartIndexes[right] = cartIndex;
        
        // Set trạng thái ban đầu là "dang doi"
        if (cartArray != nullptr) {
            cartArray[cartIndex].status = "dang doi";
        }
    }

    // pop thủ công
    bool pop() {
        if (right > -1) {
            int completedCartIndex = cartIndexes[0];

            if (cartArray != nullptr) {
                cartArray[completedCartIndex].status = "da xong";
                
                // Kiểm tra xem bàn này còn món nào chưa xong không
                int tableId = cartArray[completedCartIndex].tableId;
                bool stillActive = false;
                for (int i = 0; i < 100; i++) {
                    if (cartArray[i].tableId == tableId &&
                        cartArray[i].status != "da xong" &&
                        cartArray[i].status != "da huy" &&
                        !cartArray[i].customerName.empty()) {
                        stillActive = true;
                        break;
                    }
                }

                // Nếu không còn món nào → bàn trống
                if (!stillActive && tableArray != nullptr) {
                    tableArray[tableId - 1].empty = true;
                    tableArray[tableId - 1].customerName = "";
                }
            }

            // Xoá khỏi queue
            for (int i = 1; i <= right; i++) {
                values[i - 1] = values[i];
                cartIndexes[i - 1] = cartIndexes[i];
                startTimes[i - 1] = startTimes[i];
            }
            right--;
            processing = false;
            startNextTimer();
            return true;
        }
        return false;
    }

    // Bắt đầu timer đầu tiên nếu chưa có timer nào chạy
    void startNextTimer() {
        while (!processing && right >= 0) {
            if (cartArray[cartIndexes[0]].cancelFood) {
                // Bỏ món hủy ra khỏi queue
                for (int i = 1; i <= right; i++) {
                    values[i - 1] = values[i];
                    cartIndexes[i - 1] = cartIndexes[i];
                    startTimes[i - 1] = startTimes[i];
                }
                right--;
                continue; // kiểm tra món kế tiếp
            }
            processing = true;
            startTimes[0] = chrono::steady_clock::now();

            if (cartArray != nullptr) {
                cartArray[cartIndexes[0]].status = "dang lam";
            }
            break;
        }
    }

    // auto pop chỉ timer đầu tiên nếu hết hạn
    void autoPop() {
        if (processing && right >= 0) {
            auto now = chrono::steady_clock::now();
            auto elapsed = chrono::duration_cast<chrono::seconds>(now - startTimes[0]).count();
            
            if (elapsed >= values[0]) {
                pop();
            }
        } else if (!processing) {
            startNextTimer(); // Thử bắt đầu timer tiếp theo nếu có
        }
    }

    int getSize() {
        return right + 1;
    }

    // Hàm cập nhật lại thời gian của 1 cart trong queue
    void updateCartTime(int cartIndex, int newTime) {
        for (int i = 0; i <= right; i++) {
            if (cartIndexes[i] == cartIndex) {
                values[i] = newTime;
                // reset lại timer nếu là cart đang xử lý
                if (i == 0) {
                    startTimes[0] = chrono::steady_clock::now();
                }
                break;
            }
        }
    }

    // void print() {
    //     // cout << "=== TRANG THAI QUEUE ===\n";
    //     // cout << "Auto Update: " << (autoUpdateRunning ? "ON" : "OFF") << "\n";
    //     // cout << "Queue co " << getSize() << " timer";
    //     if (processing && right >= 0) {
    //         auto now = chrono::steady_clock::now();
    //         auto elapsed = chrono::duration_cast<chrono::seconds>(now - startTimes[0]).count();
    //         string customerName = (cartArray != nullptr) ? cartArray[cartIndexes[0]].customerName : "Unknown";
    //         cout << "\nDang xu ly: " << customerName << " (" << elapsed << "/" << values[0] << "s)";
    //     }
    //     cout << "\n========================\n";
    // }
};