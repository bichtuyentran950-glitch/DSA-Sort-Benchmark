#include <iostream>
#include <string>
#include <random>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Cu phap: ./test_gen <int/strlexi/strlenlexi> <1/2/3/4/5>\n";
        return 1;
    }

    string type = argv[1];           
    int test_num = stoi(argv[2]);    

    if (test_num < 1 || test_num > 5) {
        cerr << "Loi: So thu tu test phai tu 1 den 5.\n";
        return 1;
    }

    if (type == "int") {
        mt19937 rng(1337);
        int N = 100000;
    
        for (int t = 1; t <= 5; ++t) {
            cout<< N << "\n";
            if (t == 1) { 
                // Khai thác điểm yếu: Đối thủ dùng QuickSort 3-way (Dựa trên so sánh). 
                // Test xen kẽ Min/Max ép các bước phân hoạch (partition) phải di chuyển phần tử liên tục với quãng đường xa nhất.
                for (int i = 0; i < N; i++) cout << (i % 2 == 0 ? 2147483647 : -2147483648) << "\n";
            } else if (t == 2) { 
                // Ép phân hoạch mảng âm với độ phân tán nhỏ.
                for (int i = 0; i < N; i++) cout << -2147483000 - (rng() % 500) << "\n";
            } else if (t == 3) { 
                // Worst-case kinh điển của các thuật toán so sánh: Mảng nghịch thế (giảm dần).
                for (int i = 0; i < N; i++) cout << 2147483647 - i << "\n";
            } else { 
                // Random để kiểm tra độ ổn định của cây đệ quy QuickSort/HeapSort.
                for (int i = 0; i < N; i++) {
                    int val = (rng() % 2 == 0 ? 1 : -1) * (1000000000 + rng() % 1000000000);
                    cout << val << "\n";
                }
            }
        }
        cout << "Dang sinh test " << test_num << " cho bai int...\n";
        
    } else if (type == "strlexi") {
        int N = 100000;
        int Len = 100;
        mt19937 rng(42);

        for (int t = 1; t <= 5; ++t) {
            cout << N << "\n";
            
            if (t == 1 || t == 2) { 
                // KHAI THÁC LỖI ĐỐI THỦ: MSD Radix Sort của họ KHÔNG CÓ ĐIỀU KIỆN DỪNG (Fallback) cho mảng nhỏ.
                // 98 ký tự đầu giống hệt nhau sẽ ép code đối thủ gọi đệ quy sâu 98 tầng liên tục cho TỪNG nhóm nhỏ.
                // Ngoài ra, đối thủ dùng std::string::swap trực tiếp, gây quá tải bộ nhớ khi đệ quy sâu.
                for (int i = 0; i < N; i += 31) {
                    int group_size = min(31, N - i);
                    for (int j = group_size - 1; j >= 0; --j) {
                        string s(98, (t == 1) ? 'a' : 'z'); 
                        s += (char)('a' + (j / 26));
                        s += (char)('a' + (j % 26));
                        cout << s << "\n";
                    }
                }
            } else if (t == 3) { 
                // Ép đệ quy 99 tầng trên toàn bộ N phần tử.
                for (int i = N - 1; i >= 0; --i) {
                    string s(99, 'x');
                    s += (char)('a' + (i % 26));
                    cout << s << "\n";
                }
            } else { 
                // Random chuỗi dài tối đa để test giới hạn RAM do đối thủ không dùng mảng con trỏ.
                for (int i = 0; i < N; ++i) {
                    string s = "";
                    for(int j=0; j<Len; ++j) s += (char)('a' + rng() % 26);
                    cout << s << "\n";
                }
            }
        }
    } else if (type == "strlenlexi") {
        int N = 10000; 
        int Len = 100;
        mt19937 rng(99);

        for (int t = 1; t <= 5; ++t) {
            cout << N << "\n";
            
            if (t == 1 || t == 2) {
                // KHAI THÁC LỖI CHÍ MẠNG: Đối thủ dùng Counting Sort KHÔNG ỔN ĐỊNH (Unstable) ở bước cuối.
                // Các chuỗi cùng độ dài 100 này sau khi được đối thủ xếp từ điển, sẽ bị hàm countingSort dùng hàm swap() làm xáo trộn lại toàn bộ vị trí -> Sai kết quả (Wrong Answer).
                for (int i = 0; i < N; i += 24) {
                    int group_size = min(24, N - i);
                    for (int j = group_size - 1; j >= 0; --j) {
                        string s(98, (t == 1) ? 'b' : 'y'); 
                        s += (char)('a' + (j / 26));
                        s += (char)('a' + (j % 26));
                        cout << s << "\n";
                    }
                }
            } else if (t == 3) { 
                // Vừa test lỗi Unstable Sort, vừa ép đệ quy sâu như Bài B.
                 for (int i = N - 1; i >= 0; --i) {
                    string s(98, 'm');
                    s += (char)('a' + ((i / 26) % 26));
                    s += (char)('a' + (i % 26));
                    cout << s << "\n";
                }
            } else { 
                // Trùng lặp hoàn toàn để test giới hạn biến đếm count của Radix Sort đối thủ.
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
