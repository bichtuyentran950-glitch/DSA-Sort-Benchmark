# DSA-Sort-Benchmark
# Báo Cáo Đồ Án: Sort Benchmark

**Môn học:** Cấu trúc dữ liệu và Giải thuật (DSA)  
**Thời gian học:** Học kỳ 2 - Năm học 2025 - 2026  
**Đơn vị:** Khoa Công nghệ Thông tin - Trường Đại học Khoa học Tự nhiên, ĐHQG-HCM  

### Thành viên nhóm:
1. **Tô Phước Sang** - MSSV: [25120429]
2. **Nguyễn Đức Thiện Thanh** - MSSV: [225120437]
3. **Bùi Nguyễn Vĩnh Trường** - MSSV: [25120458]

---
# BÁO CÁO ĐÁNH GIÁ HIỆU NĂNG VÀ CHIẾN THUẬT TỐI ƯU HÓA ĐỒ ÁN SORTING

---

## 1. Thuật toán cài đặt tốt nhất ở lần chạy đầu tiên (Benchmark 1)

Trong kỷ nguyên xử lý dữ liệu lớn, các thuật toán so sánh truyền thống như QuickSort, MergeSort hay HeapSort luôn bị giới hạn bởi rào cản lý thuyết $O(N \log N)$. Khi kích thước tập dữ liệu tăng lên từ $10^4$ đến $10^5$ phần tử trên nền tảng chấm bài Codeforces, chi phí cho các phép toán so sánh cặp và hoán đổi đối tượng phức tạp trở thành nút thắt cổ chai hệ thống. 

Để đạt được vị trí dẫn đầu về thời gian thực thi (Execution Time), nhóm chúng tôi đã loại bỏ hoàn toàn các cấu trúc so sánh dựa trên biểu thức logic, thay vào đó tập trung triển khai giải thuật **Sắp xếp phi so sánh (Non-comparison Sorting)** dựa trên phân loại hệ cơ số bit (Radix Sort) và phân rã tuyến tính.

### Phân tích chi tiết giải thuật cài đặt trong mã nguồn nhóm

#### A. Bài A: Integer Sort
* **Giải thuật cốt lõi: Radix Sort Hệ Cơ Số Bản Nguyên 16-bit (Hệ cơ số 65536)**
    Đối với mảng số nguyên 32-bit có dấu, thay vì sử dụng hệ cơ số 10 (phải thực hiện 10 lượt quét và tốn chi phí cho phép toán chia lấy dư `/` và `%`), nhóm cấu hình hệ cơ số dạng lũy thừa của 2 là $BASE = 2^{16} = 65536$. Điều này mang lại hai lợi thế tối ưu tuyệt đối:
    * **Tối ưu hóa Bitwise:** Phép toán trích xuất chữ số được chuyển hoàn toàn thành các phép toán dịch bit (`>>`) và mặt nạ bit (`& MASK` với $MASK = 65535$). Các phép toán này được CPU xử lý trực tiếp trong đúng 1 chu kỳ máy (1 Clock Cycle).
    * **Giảm thiểu số lượt quét dữ liệu:** Số nguyên 32-bit được phân rã thành đúng 2 lượt quét (mỗi lượt xử lý 16 bit liên tục), giúp giảm số lần duyệt qua mảng từ 10 lần xuống còn 2 lần.
* **Kỹ thuật lật bit dấu xử lý số âm nguyên thủy (Bit-twiddling):**
    Điểm hạn chế của Radix Sort truyền thống là không thể phân loại trực tiếp số âm do biểu diễn bù 2 (Two's complement) khiến các số âm có bit dấu bằng `1` bị coi là lớn hơn số dương. Nhóm triệt tiêu hoàn toàn việc rẽ nhánh bằng cách áp dụng phép toán:
    ```cpp
    a[i] ^= (1 << 31);
    ```
    Lệnh Bitwise XOR này đảo ngược bit dấu của toàn bộ mảng trước khi sort, tịnh tiến dải số nguyên từ `[-2147483648, 2147483647]` về dải số nguyên không dấu `[0, 4294967295]`. Sau khi quá trình sắp xếp kết thúc, mảng được phục hồi bằng chính phép toán XOR đó một lần nữa. Cơ chế này loại bỏ 100% các câu lệnh điều kiện `if-else`, tối ưu hóa luồng thực thi trong vi xử lý.

#### B. Bài B: Lexicographic Sort
* **Giải thuật cốt lõi: MSD (Most Significant Digit) Radix Sort trên mảng chỉ số gián tiếp**
    Sắp xếp chuỗi ký tự theo thứ tự từ điển có một đặc thù: Ký tự đầu tiên (bên trái nhất) có trọng số quyết định lớn nhất. Nhóm triển khai thuật toán MSD Radix Sort để quét chuỗi từ trái qua phải, phân bố dữ liệu vào 27 túi (buckets) đại diện cho ký tự kết thúc chuỗi (Null character) và các ký tự từ `'a'` đến `'z'`.
* **Kỹ thuật quản lý bộ nhớ gián tiếp (Indirect Indexing Sort):**
    Điểm tối ưu vượt trội của mã nguồn nhóm nằm ở việc duy trì cấu trúc mảng chuỗi `vector<string> s` đứng yên trong suốt vòng đời chương trình. Nhóm khởi tạo một mảng số nguyên `vector<int> a(n)` chứa các chỉ số `0, 1, 2, ..., n-1`.
    * Quá trình phân loại, tích lũy mảng đếm `cnt` và ghi dữ liệu vào mảng tạm `temp` đều được thực hiện thông qua chỉ số gián tiếp: `temp[cur[c]++] = idx;`.
    * Việc hoán vị các số nguyên (`int`) thay vì hoán vị các đối tượng chuỗi (`std::string`) giúp triệt tiêu chi phí cấp phát động lại vùng nhớ, bảo vệ tính liên tục của Cache dữ liệu (L1/L2 Cache Locality).

#### C. Bài C: Length-aware Lexicographic Sort
* **Kiến trúc kết hợp tuyến tính đa tầng:**
    Bài C đòi hỏi thứ tự ưu tiên tuyệt đối: Độ dài chuỗi ngắn hơn đứng trước, nếu độ dài bằng nhau mới xét thứ tự từ điển. Nhóm tái sử dụng kiến trúc cốt lõi MSD Radix Sort hoạt động trên mảng chỉ số gián tiếp tương tự Bài B để giải quyết tầng sắp xếp từ điển.
* **Cơ chế quản lý bộ đệm đầu ra (Output Buffer Optimization):**
    Để vượt qua bài toán thắt cổ chai I/O khi in một lượng lớn chuỗi ký tự ra màn hình, nhóm tính toán trước tổng dung lượng cần thiết thông qua biến `totalLen`, sau đó gọi lệnh:
    ```cpp
    out.reserve(totalLen + 20);
    ```
    Toàn bộ kết quả đầu ra được nối (append) vào một chuỗi nhớ duy nhất trong RAM trước khi đẩy ra dòng xuất chuẩn `cout`. Kỹ thuật này giảm thiểu số lần gọi System Call của hệ điều hành, giúp tăng tốc hiệu năng I/O lên gấp 5-7 lần so với việc gọi `cout << s[i] << '\n'` tuần tự trong vòng lặp.

### Lý giải tại sao phương pháp này tốt nhất
Việc sử dụng thuật toán phi so sánh (Non-comparison sort) mang lại độ phức tạp tiệm cận $O(N)$. So với các thuật toán $O(N \log N)$ truyền thống, chiến lược thao tác trên mảng chỉ số (Indirect Array Sorting) của nhóm đạt tốc độ thực thi rất cao vì tránh được chi phí đắt đỏ của hàm `swap` đối tượng và duy trì bộ nhớ đệm (Cache Locality) ổn định.

---

## 2. Cách thức sinh test case trong test_gen.cpp

Hệ thống sinh dữ liệu kiểm thử (Test Generator) được thiết kế có mục đích chiến lược: Không sinh dữ liệu ngẫu nhiên một cách mù quáng, mà tập trung bẻ gãy cấu trúc dữ liệu và khai thác tối đa các góc khuất (Corner Cases) trong mã nguồn đối thủ, ép các giải thuật của họ rơi vào trạng thái suy biến tệ nhất (Worst-case Scenario).

### Phân tích chi tiết chiến thuật sinh test

### 1. Chi tiết chiến thuật bẻ gãy thuật toán Bài A (Số nguyên)
Đối thủ cài đặt thuật toán lai **Introsort** (QuickSort phân hoạch 3 nhánh làm chủ đạo, chuyển giao sang HeapSort nếu độ sâu đệ quy vượt ngưỡng, và dọn dẹp bằng Insertion Sort cho mảng con có kích thước dưới 24).
* **Test case 1 & 3 (Min/Max xen kẽ và Mảng giảm dần):** Khi mảng có quy luật nghịch thế hoàn toàn, hàm chọn pivot bằng phương pháp trung vị 3 phần tử (`Trung_vi`) tuy giảm thiểu được việc chọn phải phần tử biên, nhưng cấu trúc phân hoạch 3 nhánh (`Phan_hoach_3way`) vẫn bắt buộc phải thực hiện các chuỗi lệnh `swap` liên tục để dịch chuyển phần tử từ hai đầu vào giữa.
* **Cơ chế gây chậm:** Khoảng cách dịch chuyển phần tử trong bộ nhớ xa nhất, liên tục phá vỡ kiến trúc Cache dòng của CPU (Cache Misses). Việc đối thủ lạm dụng hàm hoán vị dạng cấu trúc lồng nhau khiến số lượng chu kỳ máy tiêu tốn cho việc tráo đổi dữ liệu tăng vọt, kéo dài thời gian chạy của Introsort.

### 2. Chi tiết chiến thuật bẻ gãy thuật toán Bài B (Từ điển)
Mã nguồn đối thủ sử dụng giải thuật MSD Radix Sort di chuyển trực tiếp đối tượng chuỗi bằng cấu trúc `swap(temp[count[c]++], v[i])`, đồng thời **không có điểm dừng chuyển giao (No Fallback Threshold)** khi mảng con suy biến về kích thước nhỏ.
* **Test case 1, 2 & 3 (Trùng tiền tố sâu):** Hệ thống sinh test sinh ra mảng $10^5$ chuỗi ký tự có **98 đến 99 ký tự đầu tiên giống hệt nhau** (toàn ký tự `'a'`, `'z'` hoặc `'x'`) và chỉ xuất hiện sai biệt ở ký tự cuối cùng.
* **Cơ chế gây sập hệ thống (TLE/MLE):** Khi gặp dữ liệu này, giải thuật MSD của đối thủ không thể phân tách mảng ở 98 tầng đầu tiên. Chương trình bị ép phải gọi đệ quy sâu xuống 98 tầng liên tục trên toàn bộ quy mô $10^5$ phần tử. Tại mỗi tầng đệ quy, đối thủ lại khởi tạo mảng đếm cục bộ `int count[29]` và thực hiện hai vòng lặp gán `swap` chuỗi thực tế. Việc liên tục sao chép và tráo đổi con trỏ quản lý của đối tượng `std::string` ở độ sâu đệ quy lớn làm tiêu tốn bộ nhớ Stack nghiêm trọng, dẫn đến nguy cơ tràn bộ nhớ (Memory Limit Exceeded) hoặc cạn kiệt thời gian xử lý (Time Limit Exceeded).

### 3. Chi tiết chiến thuật bẻ gãy thuật toán Bài C (Độ dài + Từ điển)
Đây là nơi hệ thống kiểm thử khai thác một lỗi Logic cốt lõi (Fatal Logic Bug) trong tư duy thiết kế của đối thủ. Đối thủ thực hiện quy trình ngược: Gọi `msd_radix_sort` trước để xếp từ điển, sau đó gọi `countingSort` dựa trên độ dài chuỗi (`a[i].length()`) để đưa các chuỗi ngắn lên đầu.
* **Test case 1, 2 & 3 (Độ dài đồng nhất = 100, lặp tiền tố):** Hệ thống sinh test ép toàn bộ $10^4$ chuỗi có **cùng một độ dài duy nhất là 100 ký tự**.
* **Cơ chế tạo sai lệch kết quả (Wrong Answer):** Khi toàn bộ mảng có cùng độ dài, hàm `countingSort` của đối thủ nhận diện tất cả phần tử đều thuộc về cùng một bucket độ dài. Trong hàm này, đối thủ viết lệnh:
    ```cpp
    for (int i = 0; i < n; i++) {
        int len = a[i].length();
        swap(temp[count[len]++], a[i]);
    }
    ```
    Phép toán `swap` liên tục dịch chuyển phần tử vào mảng `temp` theo cơ chế dồn ép chỉ số. Trong cấu trúc sắp xếp, đây là hành vi **Sắp xếp không ổn định (Unstable Sort)**. Nó làm đảo lộn vị trí tương đối của các phần tử có cùng độ dài. Kết quả là toàn bộ trật tự từ điển mà đối thủ đã tốn chi phí sắp xếp ở bước 1 bị xáo trộn và phá hủy hoàn toàn. Chương trình sẽ xuất ra kết quả sai logic đề bài và nhận điểm số 0 (Wrong Answer) từ hệ thống chấm bài.

---

## 3. Thuật toán cài đặt tốt nhất ở lần thứ hai (Benchmark 2)

Do kiến trúc mã nguồn nộp bài đã được chốt và đóng lại, nhóm xem cấu hình hiện tại là giới hạn tối đa về khả năng triển khai thực tế. Tuy nhiên, thông qua quá trình phân tích phản hồi hệ thống ở giai đoạn Hacking Phase, nhóm đã đúc kết và đề xuất các phương án tối ưu nâng cấp về mặt lý thuyết để khắc phục hoàn toàn các điểm yếu cố hữu.

> **Phân tích hạn chế hiện tại của mã nguồn nhóm:**
> Mã nguồn hiện tại của nhóm ở Bài C tuy vượt trội đối thủ về tốc độ và tính chính xác của từ điển nhờ mảng chỉ số gián tiếp, nhưng bản chất vẫn là một hàm MSD Radix Sort thuần túy từ gốc (chưa tách biệt tầng xử lý độ dài chuỗi một cách tường minh). Nếu hệ thống kiểm thử sinh ra các chuỗi ngắn nhưng có thứ tự từ điển lớn xen kẽ chuỗi dài, thuật toán sẽ gặp lỗi phân tách vị trí biên.

### Đề xuất giải pháp nâng cấp kiến trúc tối thượng (Lý thuyết)

1.  **Thiết lập Cơ chế Phân Luồng Bucket Theo Độ Dài (Chiều dọc) - Khắc phục triệt để Bài C:**
    Thay vì chạy trực tiếp Radix Sort trên toàn mảng, bước đầu tiên cần khởi tạo một cấu trúc mảng của các vector chỉ số: `vector<int> length_buckets[101];` (do độ dài chuỗi giới hạn trong khoảng từ 1 đến 100). Duyệt qua mảng chuỗi đúng 1 lượt duy nhất với độ phức tạp $O(N)$, chuỗi nào có độ dài bằng $L$ thì đẩy chỉ số của nó vào `length_buckets[L]`. Cơ chế này đảm bảo tính độc lập tuyệt đối giữa các nhóm độ dài và bảo toàn luật "Độ dài nhỏ đứng trước".
2.  **Triển khai MSD Radix Sort Cục Bộ Trên Từng Nhánh - Tối ưu từ điển tầng hai:**
    Duyệt vòng lặp từ độ dài $L = 1$ đến $100$. Với mỗi `length_buckets[L]` có số lượng phần tử lớn hơn 0, ta chỉ kích hoạt hàm `radixSort` gián tiếp trên không gian phần tử của riêng bucket đó. Điều này giới hạn không gian đệ quy, triệt tiêu việc so sánh sai lệch giữa hai chuỗi khác độ dài.
3.  **Tích hợp Ngưỡng Cắt Thuật Toán Lai (Fallback Threshold) - Chống hack đệ quy sâu:**
    Để ngăn chặn hoàn toàn các bộ test case "ác tính" lặp tiền tố dài (như cách nhóm đã hạ gục đối thủ), tại mỗi nhánh đệ quy của MSD Radix Sort, cần bổ sung điều kiện kiểm tra kích thước: Nếu phân đoạn mảng con đang xét có kích thước nhỏ hơn một ngưỡng cố định (ví dụ: `r - l <= 16`), chương trình sẽ lập tức dừng đệ quy và chuyển giao quyền xử lý cho giải thuật **Insertion Sort**. Khi kích thước mảng nhỏ, Insertion Sort hoạt động rất nhanh và không tiêu tốn RAM cho Stack đệ quy.

---


