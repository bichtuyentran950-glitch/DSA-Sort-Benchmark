#include <iostream>
#include <string>
#include <random>

using namespace std;

int main(int argc, char* argv[]) {
    // Kiểm tra xem người dùng có nhập đủ tham số không
    if (argc != 3) {
        cerr << "Cu phap: ./test_gen <int/strlexi/strlenlexi> <1/2/3/4/5>\n";
        return 1;
    }

    string type = argv[1];           // "int", "strlexi", hoac "strlenlexi"
    int test_num = stoi(argv[2]);    // 1, 2, 3, 4, 5

    if (test_num < 1 || test_num > 5) {
        cerr << "Loi: So thu tu test phai tu 1 den 5.\n";
        return 1;
    }

    if (type == "int") {
        // logic sinh Test cho Bài A 
        mt19937 rng(1337);
    int N = 100000;
    
    for (int t = 1; t <= 5; ++t) {
        cout<< N << "\n";
        if (t == 1) { // Max int & Min int xen kẽ
            for (int i = 0; i < N; i++) cout << (i % 2 == 0 ? 2147483647 : -2147483648) << "\n";
        } else if (t == 2) { // Toàn số âm cực lớn
            for (int i = 0; i < N; i++) cout << -2147483000 - (rng() % 500) << "\n";
        } else if (t == 3) { // Sắp xếp giảm dần (worst case cơ bản)
            for (int i = 0; i < N; i++) cout << 2147483647 - i << "\n";
        } else { // Random nhưng số ký tự dài
            for (int i = 0; i < N; i++) {
                int val = (rng() % 2 == 0 ? 1 : -1) * (1000000000 + rng() % 1000000000);
                cout << val << "\n";
            }
        }
    }
        cout << "Dang sinh test " << test_num << " cho bai int...\n";
        
    } else if (type == "strlexi") {
        // logic sinh Test cho Bài B 
        int N = 100000;
    int Len = 100;
    mt19937 rng(42);

    for (int t = 1; t <= 5; ++t) {
        cout << N << "\n";
        
        if (t == 1 || t == 2) { 
            // CỤM 31: Ép fallback insertion sort chạy O(N^2)
            // Nhóm 31 phần tử (vì code B fallback nếu n < 32).
            for (int i = 0; i < N; i += 31) {
                int group_size = min(31, N - i);
                // Tạo ngược chiều để insertion sort chậm nhất
                for (int j = group_size - 1; j >= 0; --j) {
                    string s(98, (t == 1) ? 'a' : 'z'); // 98 ký tự đầu giống hệt
                    s += (char)('a' + (j / 26));
                    s += (char)('a' + (j % 26));
                    cout << s << "\n";
                }
            }
        } else if (t == 3) { // Toàn bộ giống hệt nhau trừ ký tự cuối cùng, xếp ngược
            for (int i = N - 1; i >= 0; --i) {
                string s(99, 'x');
                s += (char)('a' + (i % 26));
                cout << s << "\n";
            }
        } else { // Random cực dài để tốn RAM và Cache
            for (int i = 0; i < N; ++i) {
                string s = "";
                for(int j=0; j<Len; ++j) s += (char)('a' + rng() % 26);
                cout << s << "\n";
            }
        }
    }
    } else if (type == "strlenlexi") {
        //logic sinh Test cho Bài C 
    int N = 10000; // Giới hạn bài C chỉ có 10^4
    int Len = 100;
    mt19937 rng(99);

    for (int t = 1; t <= 5; ++t) {
        cout << N << "\n";
        
        if (t == 1 || t == 2) {
            // Ép vào cùng 1 bucket độ dài (Len = 100)
            // Code C fallback ở n < 25, nên ta tạo nhóm 24 chuỗi ngược chiều
            for (int i = 0; i < N; i += 24) {
                int group_size = min(24, N - i);
                for (int j = group_size - 1; j >= 0; --j) {
                    string s(98, (t == 1) ? 'b' : 'y'); 
                    s += (char)('a' + (j / 26));
                    s += (char)('a' + (j % 26));
                    cout << s << "\n";
                }
            }
        } else if (t == 3) { // Đảo ngược 1 mảng giống nhau phần lớn
             for (int i = N - 1; i >= 0; --i) {
                string s(98, 'm');
                s += (char)('a' + ((i / 26) % 26));
                s += (char)('a' + (i % 26));
                cout << s << "\n";
            }
        } else { // Trùng lặp hoàn toàn (Dupes)
            string base_str(100, 'k');
            for (int i = 0; i < N; ++i) cout << base_str << "\n";
        }
    }
    } else {
        cerr << "Loi: Tham so bai toan khong hop le.\n";
        return 1;
    }

    return 0;
}
