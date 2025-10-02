#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <iomanip>

#include "Food.h"
#include "Customer.h"
#include "Queue.h"
#include "Cart.h"
#include "Table.h"
#include "SinglyLinkedList.h"

using namespace std;

// case 6
void sortMenuAscending(Food food[], int &foodCount) {
    for (int i = 0; i < foodCount - 1; i++) {
        for (int j = i + 1; j < foodCount; j++) {
            if (food[i].price > food[j].price) {
                swap(food[i], food[j]);
            }
        }
    }
}

// case 5
void printMenu(Food food[], int foodCount) {
    int col1 = 9;   // Number
    int col2 = 26;  // Name
    int col3 = 17;  // Price

    const string cyan   = "\033[36m";
    const string green  = "\033[32m";
    const string yellow = "\033[33m";
    const string orange = "\033[38;5;208m";
    const string reset  = "\033[0m";

    cout << "\n" << cyan << "========================= MENU =========================" << reset << "\n";

    // border trên
    cout << "+" << string(col1, '-') 
         << "+" << string(col2, '-') 
         << "+" << string(col3, '-') 
         << "+\n";

    // header
    cout << "|" << orange   << setw(col1) << left << "Number" << reset
         << "|" << orange  << setw(col2) << left << "Name"   << reset
         << "|" << orange << setw(col3) << left << "Price"  << reset
         << "|\n";

    // border ngang
    cout << "+" << string(col1, '-') 
         << "+" << string(col2, '-') 
         << "+" << string(col3, '-') 
         << "+\n";

    // dữ liệu
    for (int i = 0; i < foodCount; i++) {
        cout << "|" << cyan  << setw(col1) << left << (i + 1) << reset
             << "|" << green << setw(col2) << left << food[i].name << reset
             << "|" << yellow<< setw(col3) << left << (to_string(food[i].price) + " VND") << reset
             << "|\n";
    }

    // border dưới
    cout << "+" << string(col1, '-') 
         << "+" << string(col2, '-') 
         << "+" << string(col3, '-') 
         << "+\n";
    
    cout << cyan << "========================================================" << reset << "\n";
}


int main(){

    Queue queue;
    Food food[100];
    int foodCount=3;
    food[0]={"banh mi",15000,20};
    food[1]={"hu tieu",25000,20};
    food[2]={"bun bo",100000,20};
    Table table[9];
    Customer customer[100];
    Cart cart[100];
    
    // Lien ket queue voi cart array va table array
    queue.setCartArray(cart);
    queue.setTableArray(table);
    
    // Bat dau auto update system
    queue.startAutoUpdate();
    
    for(int i=0;i<9;i++){
        table[i].id=i+1;
    }
    int x,y=0,z;
    bool t=true;
    while(t){
        cout << "\033[36m========================================================\033[0m\n";
        cout << "\033[1;33m                   HE THONG QUAN LI                   \033[0m\n";
        cout << "\033[36m========================================================\033[0m\n";
        cout << "\033[32m1.\033[0m Xem ban\n";
        cout << "\033[32m2.\033[0m Chon ban\n";
        cout << "\033[32m3.\033[0m Xem hoa don\n";
        cout << "\033[32m4.\033[0m Huy hoa don\n";
        cout << "\033[32m5.\033[0m Xem menu\n";
        cout << "\033[32m6.\033[0m Them mon\n";
        cout << "\033[32m7.\033[0m Xoa mon\n";
        cout << "\033[32m8.\033[0m Them mon vao ban\n";
        cout << "\033[32m9.\033[0m Tim mon trong menu\n";
        cout << "\033[32m10.\033[0m Tim kiem hoa don\n";
        cout << "\033[32m11.\033[0m xem doanh thu cua hang\n";
        cout << "\033[31m0.\033[0m Thoat\n";
        cout << "\033[36m========================================================\033[0m\n";
        cout << "Chon thao tac: ";
        cin>>z;
        switch(z){
            case 1: {
                int width = 16;   // chiều rộng mỗi bàn
                int height = 7;   // chiều cao mỗi bàn

                cout << "\033[36m===================== DANH SACH BAN ====================\033[0m\n";

                for (int row = 0; row < 3; row++) { // 3 hàng
                    for (int line = 0; line < height; line++) { // mỗi hàng cao height dòng
                        for (int col = 0; col < 3; col++) { // 3 cột
                            int idx = row * 3 + col;

                            // Màu nền: xanh nếu trống, đỏ nếu có khách
                            string bgColor = table[idx].empty ? "\033[42m" : "\033[41m";
                            string reset = "\033[0m";
                            string border = "\033[37m"; // màu viền trắng

                            if (line == 0 || line == height - 1) {
                                // viền trên/dưới
                                cout << border << "+";
                                for (int i = 0; i < width; i++) cout << "-";
                                cout << "+" << reset << " ";
                            } else {
                                cout << border << "|" << reset; // viền trái
                                if (line == height / 2) {
                                    // dòng giữa: hiển thị tên bàn hoặc khách
                                    string text;
                                    if (table[idx].empty) {
                                        text = "Ban " + to_string(idx + 1) + ": Trong";
                                    } else {
                                        text = "Ban " + to_string(idx + 1) + ": " + table[idx].customerName;
                                        if (text.length() > width) text = text.substr(0, width); // cắt vừa width
                                    }
                                    int padding = (width - text.length()) / 2;
                                    cout << bgColor;
                                    for (int i = 0; i < padding; i++) cout << " ";
                                    cout << text;
                                    for (int i = 0; i < width - text.length() - padding; i++) cout << " ";
                                    cout << reset;
                                } else {
                                    // các dòng còn lại: nền màu
                                    cout << bgColor;
                                    for (int i = 0; i < width; i++) cout << " ";
                                    cout << reset;
                                }
                                cout << border << "|" << reset << " "; // viền phải
                            }
                        }
                        cout << endl;
                    }
                }

                cout << "\033[36m========================================================\033[0m\n";
                break;
            }
            case 2:{
                int width = 16;   // chiều rộng mỗi bàn
                int height = 7;   // chiều cao mỗi bàn

                cout << "\033[36m===================== DANH SACH BAN ====================\033[0m\n";

                for (int row = 0; row < 3; row++) { // 3 hàng
                    for (int line = 0; line < height; line++) { // mỗi hàng cao height dòng
                        for (int col = 0; col < 3; col++) { // 3 cột
                            int idx = row * 3 + col;

                            // Màu nền: xanh nếu trống, đỏ nếu có khách
                            string bgColor = table[idx].empty ? "\033[42m" : "\033[41m";
                            string reset = "\033[0m";
                            string border = "\033[37m"; // màu viền trắng

                            if (line == 0 || line == height - 1) {
                                // viền trên/dưới
                                cout << border << "+";
                                for (int i = 0; i < width; i++) cout << "-";
                                cout << "+" << reset << " ";
                            } else {
                                cout << border << "|" << reset; // viền trái
                                if (line == height / 2) {
                                    // dòng giữa: hiển thị tên bàn hoặc khách
                                    string text;
                                    if (table[idx].empty) {
                                        text = "Ban " + to_string(idx + 1) + ": Trong";
                                    } else {
                                        text = "Ban " + to_string(idx + 1) + ": " + table[idx].customerName;
                                        if (text.length() > width) text = text.substr(0, width); // cắt vừa width
                                    }
                                    int padding = (width - text.length()) / 2;
                                    cout << bgColor;
                                    for (int i = 0; i < padding; i++) cout << " ";
                                    cout << text;
                                    for (int i = 0; i < width - text.length() - padding; i++) cout << " ";
                                    cout << reset;
                                } else {
                                    // các dòng còn lại: nền màu
                                    cout << bgColor;
                                    for (int i = 0; i < width; i++) cout << " ";
                                    cout << reset;
                                }
                                cout << border << "|" << reset << " "; // viền phải
                            }
                        }
                        cout << endl;
                    }
                }

                cout << "\033[36m========================================================\033[0m\n";
                
                int selectedTable;
                bool validTable = false;
                
                while (!validTable) {
                    cout << "Chon ban: ";
                    cin >> selectedTable;
                    
                    // Kiểm tra số bàn hợp lệ
                    if (selectedTable < 1 || selectedTable > 9) {
                        cout << "\033[31mSo ban khong hop le! Vui long chon tu 1-9.\033[0m\n";
                        continue;
                    }
                    
                    // Kiểm tra bàn có trống không
                    if (!table[selectedTable - 1].empty) {
                        cout << "\033[31mBan " << selectedTable << " da co khach: " 
                             << table[selectedTable - 1].customerName 
                             << ". Vui long chon ban khac!\033[0m\n";
                        continue;
                    }
                    
                    validTable = true;
                }
                
                x = selectedTable;
                cout << "Nhap ten khach: ";
                cin >> customer[y].name;

                table[x - 1].empty = false;
                table[x - 1].customerName = customer[y].name;
                customer[y].tableId = table[x - 1].id;

                // Tao SinglyLinkedList de luu cac mon da chon
                SinglyLinkedList selectedFoods;
                bool continueOrdering = true;
                
                while (continueOrdering) {
                    printMenu(food, foodCount);
                    
                    cout << "\n\033[95mCac mon da chon:\033[0m ";
                    if (selectedFoods.getSize() == 0) {
                        cout << "\033[90m(Chua chon mon nao)\033[0m\n";
                    } else {
                        cout << "\n";
                        for (int i = 0; i < selectedFoods.getSize(); i++) {
                            Food selectedFood = selectedFoods.getValue(i);
                            cout << "- " << selectedFood.name << " (" << selectedFood.price << " VND)\n";
                        }
                    }

                    cout << "\nChon mon (0 de hoan thanh dat mon): ";
                    int k; 
                    cin >> k;
                    
                    if (k == 0) {
                        if (selectedFoods.getSize() == 0) {
                            cout << "\033[31mBan chua chon mon nao! Vui long chon it nhat 1 mon.\033[0m\n";
                            continue;
                        }
                        continueOrdering = false;
                    } else if (k < 1 || k > foodCount) {
                        cout << "\033[31mLua chon khong hop le! Vui long chon lai.\033[0m\n";
                        continue;
                    } else {
                        // Them mon vao SinglyLinkedList (luu Food object)
                        selectedFoods.add(food[k - 1]);
                        cout << "\033[32mDa them " << food[k - 1].name << " vao don hang!\033[0m\n";
                    }
                }
                
                // Xu ly tat ca cac mon da chon tu SinglyLinkedList
                cout << "\n\033[36m================== XAC NHAN DON HANG ===================\033[0m\n";
                cout << "Khach hang: \033[32m" << customer[y].name << "\033[0m\n";
                cout << "Ban: \033[33m" << x << "\033[0m\n";
                cout << "Cac mon da dat:\n";
                
                // Tạo một hóa đơn duy nhất cho tất cả các món
                cart[y].customerName = customer[y].name;
                cart[y].tableId = table[x - 1].id;
                cart[y].status = "dang doi";
                cart[y].cancelFood = false;
                cart[y].orderCount = selectedFoods.getSize();
                
                int totalOrderValue = 0;
                int totalOrderTime = 0;
                string orderSummary = "";
                int totalQuantity = 0;
                
                // Lưu tất cả các món vào orderDetails
                for (int i = 0; i < selectedFoods.getSize(); i++) {
                    Food selectedFood = selectedFoods.getValue(i);
                    
                    cout << "Mon " << (i + 1) << ": " << selectedFood.name;
                    cout << " - Nhap so luong: ";
                    int quantity;
                    cin >> quantity;
                    
                    // Lưu vào orderDetails với số lượng
                    cart[y].orderDetails[i] = selectedFood;
                    cart[y].orderDetails[i].quantity = quantity;  // Lưu số lượng vào Food
                    
                    int itemTotal = quantity * selectedFood.price;
                    int itemTime = quantity * selectedFood.time;
                    
                    totalOrderValue += itemTotal;
                    totalOrderTime += itemTime;
                    totalQuantity += quantity;
                    
                    // Tạo chuỗi tóm tắt đơn hàng
                    if (i > 0) orderSummary += ", ";
                    orderSummary += to_string(quantity) + "x " + selectedFood.name;
                    
                    cout << "\033[32m  -> " << quantity << " x " << selectedFood.name 
                         << " = " << itemTotal << " VND\033[0m\n";
                }
                
                // Lưu thông tin tổng hợp vào cart
                cart[y].foodName = orderSummary; // Tên tổng hợp cho hiển thị
                cart[y].quantity = totalQuantity; // Tổng số lượng
                cart[y].totalMoney = totalOrderValue;
                cart[y].totalTime = totalOrderTime;
                
                // Chỉ push một lần vào queue cho toàn bộ đơn hàng
                queue.push(cart[y].totalTime, y);
                queue.autoPop();
                
                cout << "\n\033[36m=================== TONG KET HOA DON ===================\033[0m\n";
                cout << "\033[32mKhach hang:\033[0m " << customer[y].name << "\n";
                cout << "\033[33mBan:\033[0m " << x << "\n";
                //cout << "\033[34mCac mon:\033[0m " << orderSummary << "\n";
                cout << "\033[33mTong gia tri:\033[0m " << totalOrderValue << " VND\n";
                cout << "\n\033[32mDat mon thanh cong!\033[0m\n";
                
                y++;
                break;
            }
            case 3:
                cout << "\033[36m================== DANH SACH HOA DON ===================\033[0m\n";
                                
                if (y == 0) {
                    cout << "\033[90m                    Chua co hoa don nao                    \033[0m\n";
                } else {
                    for (int i = 0; i < y; i++) {
                        cout << "\n\033[36m+" << string(54, '-') << "+\033[0m\n";
                        cout << "\033[36m|\033[0m \033[33mHOA DON #" << (i + 1) << "\033[0m";
                        cout << string(54 - 10 - to_string(i + 1).length(), ' ') << "\033[36m|\033[0m\n";
                        cout << "\033[36m+" << string(54, '-') << "+\033[0m\n";
                        
                        // Thông tin khách hàng và bàn
                        cout << "\033[36m|\033[0m \033[32mKhach hang:\033[0m " << cart[i].customerName;
                        cout << string(54 - 13 - cart[i].customerName.length(), ' ') << "\033[36m|\033[0m\n";
                        cout << "\033[36m|\033[0m \033[33mBan so:\033[0m " << cart[i].tableId;
                        cout << string(54 - 9 - to_string(cart[i].tableId).length(), ' ') << "\033[36m|\033[0m\n";
                        
                        // Danh sách món
                        cout << "\033[36m|\033[0m \033[34mCac mon da dat:\033[0m";
                        cout << string(54 - 16, ' ') << "\033[36m|\033[0m\n";
                        
                        // Hiển thị các món từ orderDetails
                        for (int j = 0; j < cart[i].orderCount; j++) {
                            Food food = cart[i].orderDetails[j];
                            string foodLine = "  - " + to_string(food.quantity) + "x " + food.name + " (" + to_string(food.price) + " VND)";
                            cout << "\033[36m|\033[0m " << foodLine;
                            cout << string(54 - 1 - foodLine.length(), ' ') << "\033[36m|\033[0m\n";
                        }
                        
                        // Thông tin tổng hợp
                        cout << "\033[36m+" << string(54, '-') << "+\033[0m\n";
                        cout << "\033[36m|\033[0m \033[95mSo loai mon:\033[0m " << cart[i].quantity;
                        cout << string(54 - 13 - to_string(cart[i].quantity).length()-1, ' ') << "\033[36m|\033[0m\n";
                        cout << "\033[36m|\033[0m \033[93mTong tien:\033[0m " << cart[i].totalMoney << " VND";
                        cout << string(54 - 11 - to_string(cart[i].totalMoney).length() - 4 -1, ' ') << "\033[36m|\033[0m\n";
                        
                        // Trạng thái (không icon, chỉ chữ)
                        cout << "\033[36m|\033[0m \033[96mTrang thai:\033[0m ";
                        string statusText;

                        if (cart[i].status == "da xong") {
                            statusText = "\033[32mDa xong\033[0m";      // xanh lá
                        } else if (cart[i].status == "dang lam") {
                            statusText = "\033[93mDang lam\033[0m";     // vàng
                        } else if (cart[i].status == "da huy") {
                            statusText = "\033[31mDa huy\033[0m";       // đỏ
                        } else {
                            statusText = "\033[38;5;208mDang doi\033[0m"; // cam
                        }

                        cout << statusText;

                        // Độ dài statusText có chứa mã màu ANSI → nếu dùng length() thì bị sai căn lề.
                        // => chỉ tính độ dài thực của chữ hiển thị thôi:
                        int visibleLength;
                        if (cart[i].status == "da xong") visibleLength = 7;
                        else if (cart[i].status == "dang lam") visibleLength = 8;
                        else if (cart[i].status == "da huy") visibleLength = 6;
                        else visibleLength = 8;

                        cout << string(54 - 12 - visibleLength - 1, ' ') << "\033[36m|\033[0m\n";
                        
                        cout << "\033[36m+" << string(54, '-') << "+\033[0m\n";
                    }
                }
                cout << "\033[36m" << string(56, '=') << "\033[0m\n";
                break;

            case 4:{
                int width = 16;   // chiều rộng mỗi bàn
                int height = 7;   // chiều cao mỗi bàn

                cout << "\033[36m===================== DANH SACH BAN ====================\033[0m\n";

                for (int row = 0; row < 3; row++) { // 3 hàng
                    for (int line = 0; line < height; line++) { // mỗi hàng cao height dòng
                        for (int col = 0; col < 3; col++) { // 3 cột
                            int idx = row * 3 + col;

                            // Màu nền: xanh nếu trống, đỏ nếu có khách
                            string bgColor = table[idx].empty ? "\033[42m" : "\033[41m";
                            string reset = "\033[0m";
                            string border = "\033[37m"; // màu viền trắng

                            if (line == 0 || line == height - 1) {
                                // viền trên/dưới
                                cout << border << "+";
                                for (int i = 0; i < width; i++) cout << "-";
                                cout << "+" << reset << " ";
                            } else {
                                cout << border << "|" << reset; // viền trái
                                if (line == height / 2) {
                                    // dòng giữa: hiển thị tên bàn hoặc khách
                                    string text;
                                    if (table[idx].empty) {
                                        text = "Ban " + to_string(idx + 1) + ": Trong";
                                    } else {
                                        text = "Ban " + to_string(idx + 1) + ": " + table[idx].customerName;
                                        if (text.length() > width) text = text.substr(0, width); // cắt vừa width
                                    }
                                    int padding = (width - text.length()) / 2;
                                    cout << bgColor;
                                    for (int i = 0; i < padding; i++) cout << " ";
                                    cout << text;
                                    for (int i = 0; i < width - text.length() - padding; i++) cout << " ";
                                    cout << reset;
                                } else {
                                    // các dòng còn lại: nền màu
                                    cout << bgColor;
                                    for (int i = 0; i < width; i++) cout << " ";
                                    cout << reset;
                                }
                                cout << border << "|" << reset << " "; // viền phải
                            }
                        }
                        cout << endl;
                    }
                }

                cout << "\033[36m========================================================\033[0m\n";
                cout<<"chon ban muon huy: ";
                int l;
                cin>>l;
                if(table[l-1].empty==true){
                    cout<<"ban khong co mon"<<endl;
                }else{
                    for(int i=0;i<y;i++){
                        if(cart[i].tableId != l) continue; // so sánh đúng tableId, không dùng l-1

                        if(cart[i].status=="da xong"){
                            continue;
                        }else if(cart[i].status=="dang lam"){
                            cout<<"\033[31mmon dang lam khong the huy!\033[0m"<<endl;
                        }else if(cart[i].status=="dang doi"){
                            cart[i].cancelFood=true;
                            cart[i].status="da huy"; // viết thường đồng bộ
                            table[l-1].empty=true;
                            cout<<"da huy mon "<<cart[i].foodName<<" cua ban "<<l<<endl;
                        }
                    }
                }
                break;
            }
            case 5:
                printMenu(food, foodCount);
                break;
            case 6:
                {
                printMenu(food, foodCount);
                cout << "\n\033[36m======================= ADD FOOD =======================\033[0m\n";
                cout<<"food name: ";
                cin.ignore();
                string foodName;
                getline(cin,foodName);
                cout<<"price: ";
                int price;
                cin>>price;
                cout<<"time make food: ";
                int timeMakeFood;
                cin>>timeMakeFood;
                food[foodCount].name=foodName;
                food[foodCount].price=price;
                food[foodCount].time=timeMakeFood;
                foodCount++;
                sortMenuAscending(food, foodCount);
                break;
                }
            case 7:{
                printMenu(food, foodCount);
                cout << "\n\033[36m===================== DETELE FOOD ======================\033[0m\n"; 
                cout<<"number: ";
                int number;
                cin>>number;
                if(number<1 || number>foodCount){
                    cout<<"\033[31mkhong co mon trong menu!\033[0m"<<endl;
                    break;
                }else{
                    for(int i=number-1;i<foodCount;i++){
                        food[i]=food[i+1];
                    }
                }
                foodCount--;
                break;
            }
            case 8: {
                cout << "\033[36m=================== CAP NHAT HOA DON ===================\033[0m\n";
                cout << "Chon ban muon cap nhat: ";
                int banThem;
                cin >> banThem;

                if (banThem < 1 || banThem > 9) {
                    cout << "\033[31mSo ban khong hop le!\033[0m\n";
                    break;
                }
                if (table[banThem - 1].empty) {
                    cout << "\033[31mBan " << banThem << " hien dang trong!\033[0m\n";
                    break;
                }

                // Tìm cart của bàn này
                int cartIndex = -1;
                for (int i = 0; i < y; i++) {
                    if (cart[i].tableId == banThem && cart[i].status != "da huy") {
                        cartIndex = i;
                        break;
                    }
                }
                if (cartIndex == -1) {
                    cout << "\033[31mKhong tim thay hoa don cua ban nay!\033[0m\n";
                    break;
                }

                Cart &c = cart[cartIndex];

                // ================= TRUONG HOP DA XONG =================
                if (c.status == "da xong") {
                    cout << "\033[32mBan " << banThem << " hien tai dang trong!\033[0m\n";
                    table[banThem - 1].empty = true;
                    break;
                }

                // ================= TRUONG HOP DANG LAM =================
                if (c.status == "dang lam") {
                    cout << "\033[33mHoa don dang lam -> chi duoc them mon moi.\033[0m\n";

                    int newTime = 0, newMoney = 0, newQuantity = 0;
                    SinglyLinkedList themMonList;
                    bool tiepTuc = true;

                    while (tiepTuc) {
                        printMenu(food, foodCount);
                        cout << "\nChon mon (0 de hoan thanh): ";
                        int k; cin >> k;
                        if (k == 0) {
                            tiepTuc = false;
                        } else if (k < 1 || k > foodCount) {
                            cout << "\033[31mLua chon khong hop le!\033[0m\n";
                        } else {
                            themMonList.add(food[k-1]);
                        }
                    }

                    int base = c.orderCount;
                    for (int i = 0; i < themMonList.getSize(); i++) {
                        Food f = themMonList.getValue(i);
                        cout << "Nhap so luong cho " << f.name << ": ";
                        int sl; cin >> sl;
                        f.quantity = sl;
                        c.orderDetails[base + i] = f;
                        c.orderCount++;
                        newMoney += sl * f.price;
                        newTime += sl * f.time;
                        newQuantity += sl;
                    }

                    c.totalMoney += newMoney;
                    c.totalTime += newTime;
                    c.quantity += newQuantity;

                    // Cập nhật queue
                    queue.updateCartTime(cartIndex, c.totalTime);
                    cout << "\033[32mDa them mon thanh cong!\033[0m\n";
                }

                // ================= TRUONG HOP DANG DOI =================
                else if (c.status == "dang doi") {
                    cout << "\033[33mHoa don dang doi -> co the xoa mon cu va them mon moi.\033[0m\n";
                    bool tiepTucCapNhat = true;
                    while (tiepTucCapNhat) {
                        cout << "\n\033[36m================ CAP NHAT HOA DON BAN " << banThem << " =================\033[0m\n";
                        cout << "1. Xoa mon cu\n";
                        cout << "2. Them mon moi\n";
                        cout << "0. Hoan tat cap nhat\n";
                        cout << "Chon thao tac: ";
                        int opt; cin >> opt;

                        if (opt == 0) {
                            tiepTucCapNhat = false;
                        }
                        else if (opt == 1) {
                            if (c.orderCount == 0) {
                                cout << "\033[31mHoa don khong co mon nao de xoa!\033[0m\n";
                                continue;
                            }
                            cout << "\nDanh sach mon hien tai:\n";
                            for (int i = 0; i < c.orderCount; i++) {
                                cout << i+1 << ". " << c.orderDetails[i].quantity << "x "
                                    << c.orderDetails[i].name << " (" << c.orderDetails[i].price << " VND)\n";
                            }
                            cout << "Nhap so thu tu mon muon xoa: ";
                            int idx; cin >> idx;
                            if (idx >= 1 && idx <= c.orderCount) {
                                int pos = idx - 1;
                                // Trừ tiền + thời gian
                                c.totalMoney -= c.orderDetails[pos].price * c.orderDetails[pos].quantity;
                                c.totalTime -= c.orderDetails[pos].time * c.orderDetails[pos].quantity;
                                c.quantity -= c.orderDetails[pos].quantity;
                                // Dịch mảng
                                for (int j = pos; j < c.orderCount-1; j++) {
                                    c.orderDetails[j] = c.orderDetails[j+1];
                                }
                                c.orderCount--;
                                cout << "\033[32mDa xoa mon thanh cong!\033[0m\n";
                            } else {
                                cout << "\033[31mSo thu tu khong hop le!\033[0m\n";
                            }
                        }
                        else if (opt == 2) {
                            SinglyLinkedList themMonList;
                            bool tiepTucThem = true;
                            while (tiepTucThem) {
                                printMenu(food, foodCount);
                                cout << "\nChon mon muon them (0 de hoan thanh): ";
                                int k; cin >> k;
                                if (k == 0) {
                                    tiepTucThem = false;
                                } else if (k < 1 || k > foodCount) {
                                    cout << "\033[31mLua chon khong hop le!\033[0m\n";
                                } else {
                                    themMonList.add(food[k-1]);
                                }
                            }

                            int base = c.orderCount;
                            for (int i = 0; i < themMonList.getSize(); i++) {
                                Food f = themMonList.getValue(i);
                                cout << "Nhap so luong cho " << f.name << ": ";
                                int sl; cin >> sl;
                                f.quantity = sl;
                                c.orderDetails[base + i] = f;
                                c.orderCount++;
                                c.totalMoney += sl * f.price;
                                c.totalTime += sl * f.time;
                                c.quantity += sl;
                            }
                            cout << "\033[32mDa them mon moi thanh cong!\033[0m\n";
                        }
                        else {
                            cout << "\033[31mLua chon khong hop le!\033[0m\n";
                        }

                        // Sau mỗi thao tác thì cập nhật queue
                        queue.updateCartTime(cartIndex, c.totalTime);
                    }

                    cout << "\033[32mDa cap nhat hoa don dang doi thanh cong!\033[0m\n";
                }
                break;
            }
            case 9: {
                cout << "\n\033[36m===================== TIM KIEM MON =====================\033[0m\n";
                cout << "Nhap ten mon muon tim: ";
                cin.ignore();
                string keyword;
                getline(cin, keyword);

                // Chuyển về chữ thường để so sánh không phân biệt hoa/thường
                auto toLower = [](string s) {
                    for (char &c : s) c = tolower(c);
                    return s;
                };
                string keyLower = toLower(keyword);

                bool found = false;
                // dung NAIVE cho dễ cài đặt và bảo chì trong c++ có hỗ trợ hàm find rồi
                cout << "\nKet qua tim kiem:\n";
                for (int i = 0; i < foodCount; i++) {
                    string foodNameLower = toLower(food[i].name);
                    if (foodNameLower.find(keyLower) != string::npos) {
                        cout << "- " << food[i].name 
                            << " | " << food[i].price << " VND"
                            << " | Thoi gian lam: " << food[i].time << "s\n";
                        found = true;
                    }
                }

                if (!found) {
                    cout << "\033[31mKhong tim thay mon nao phu hop!\033[0m\n";
                }
                cout << "\033[36m========================================================\033[0m\n";
                break;
            }
            case 10: {
                cout << "\n\033[36m=================== TIM KIEM HOA DON ===================\033[0m\n";
                cout << "1. Tim theo ten khach hang\n";
                cout << "2. Tim theo so ban\n";
                cout << "Chon thao tac: ";
                int opt; cin >> opt;

                bool found = false;

                auto inHoaDon = [&](int idx) {
                    cout << "\n\033[36m+" << string(54, '-') << "+\033[0m\n";
                    cout << "\033[36m|\033[0m \033[33mHOA DON #" << (idx + 1) << "\033[0m";
                    cout << string(54 - 10 - to_string(idx + 1).length(), ' ') << "\033[36m|\033[0m\n";
                    cout << "\033[36m+" << string(54, '-') << "+\033[0m\n";

                    cout << "\033[36m|\033[0m \033[32mKhach hang:\033[0m " << cart[idx].customerName;
                    cout << string(54 - 13 - cart[idx].customerName.length(), ' ') << "\033[36m|\033[0m\n";

                    cout << "\033[36m|\033[0m \033[33mBan so:\033[0m " << cart[idx].tableId;
                    cout << string(54 - 9 - to_string(cart[idx].tableId).length(), ' ') << "\033[36m|\033[0m\n";

                    cout << "\033[36m|\033[0m \033[34mCac mon da dat:\033[0m";
                    cout << string(54 - 16, ' ') << "\033[36m|\033[0m\n";
                    for (int j = 0; j < cart[idx].orderCount; j++) {
                        Food food = cart[idx].orderDetails[j];
                        string foodLine = "  - " + to_string(food.quantity) + "x " + food.name + " (" + to_string(food.price) + " VND)";
                        cout << "\033[36m|\033[0m " << foodLine;
                        cout << string(54 - 1 - foodLine.length(), ' ') << "\033[36m|\033[0m\n";
                    }

                    cout << "\033[36m+" << string(54, '-') << "+\033[0m\n";
                    cout << "\033[36m|\033[0m \033[95mSo loai mon:\033[0m " << cart[idx].quantity;
                    cout << string(54 - 13 - to_string(cart[idx].quantity).length()-1, ' ') << "\033[36m|\033[0m\n";

                    cout << "\033[36m|\033[0m \033[93mTong tien:\033[0m " << cart[idx].totalMoney << " VND";
                    cout << string(54 - 11 - to_string(cart[idx].totalMoney).length() - 4 -1, ' ') << "\033[36m|\033[0m\n";

                    cout << "\033[36m|\033[0m \033[96mTrang thai:\033[0m ";
                    string statusText;
                    int visibleLength;
                    if (cart[idx].status == "da xong") { statusText = "\033[32mDa xong\033[0m"; visibleLength = 7; }
                    else if (cart[idx].status == "dang lam") { statusText = "\033[93mDang lam\033[0m"; visibleLength = 8; }
                    else if (cart[idx].status == "da huy") { statusText = "\033[31mDa huy\033[0m"; visibleLength = 6; }
                    else { statusText = "\033[38;5;208mDang doi\033[0m"; visibleLength = 8; }

                    cout << statusText;
                    cout << string(54 - 12 - visibleLength - 1, ' ') << "\033[36m|\033[0m\n";

                    cout << "\033[36m+" << string(54, '-') << "+\033[0m\n";
                };

                if (opt == 1) {
                    cin.ignore();
                    cout << "Nhap ten khach hang: ";
                    string keyword;
                    getline(cin, keyword);

                    auto toLower = [](string s) {
                        for (char &c : s) c = tolower(c);
                        return s;
                    };
                    string keyLower = toLower(keyword);

                    for (int i = 0; i < y; i++) {
                        string custLower = toLower(cart[i].customerName);
                        if (custLower.find(keyLower) != string::npos) {
                            found = true;
                            inHoaDon(i);
                        }
                    }
                } 
                else if (opt == 2) {
                    cout << "Nhap so ban: ";
                    int ban; cin >> ban;

                    for (int i = 0; i < y; i++) {
                        if (cart[i].tableId == ban) {
                            found = true;
                            inHoaDon(i);
                        }
                    }
                } 
                else {
                    cout << "\033[31mLua chon khong hop le!\033[0m\n";
                }

                if (!found) {
                    cout << "\033[31mKhong tim thay hoa don nao!\033[0m\n";
                }

                cout << "\033[36m========================================================\033[0m\n";
                break;
            }
            case 11: {
                cout << "\n\033[36m====================== DOANH THU =======================\033[0m\n";

                long long tongDoanhThu = 0;
                int soHoaDonHoanThanh = 0;
                int soHoaDonHuy = 0;

                for (int i = 0; i < y; i++) {
                    if (cart[i].status == "da xong") {
                        tongDoanhThu += cart[i].totalMoney;
                        soHoaDonHoanThanh++;
                    } 
                    else if (cart[i].status == "da huy") {
                        soHoaDonHuy++;
                    }
                }

                cout << "\033[32mTong so hoa don hoan thanh:\033[0m " << soHoaDonHoanThanh << "\n";
                cout << "\033[31mTong so hoa don da huy:\033[0m " << soHoaDonHuy << "\n";
                cout << "\033[95mTong doanh thu:\033[0m " << tongDoanhThu << " VND\n";

                cout << "\033[36m========================================================\033[0m\n";
                break;
            }
            default:
                cout << "Dang thoat chuong trinh...\n";
                queue.stopAutoUpdate();
                this_thread::sleep_for(chrono::milliseconds(500)); // Cho thread ket thuc
                t=false;
                break;
        }
    }
    return 0;
}