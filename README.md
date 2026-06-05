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

## 1. Thuật toán cài đặt tốt nhất ở lần chạy đầu tiên (Benchmark 1)

Trong lần chạy đầu tiên, mục tiêu tối thượng là tối ưu hóa tốc độ xử lý trên nền tảng Codeforces với lượng dữ liệu lớn ($N = 10^4$ đến $10^5$). Nhóm đã áp dụng các thuật toán chuyên biệt dựa trên phân loại hệ cơ số thay vì các thuật toán so sánh thông thường:

### Các thuật toán được cài đặt:
* **Bài A (Integer Sort):** Sử dụng **Radix Sort cơ số 65536 (16-bit)**. Thuật toán chia số nguyên 32-bit thành 2 lượt sắp xếp (mỗi lượt xử lý 16-bit). Trước khi xếp, các số được áp dụng phép toán Bitwise `^ 0x80000000` để xử lý chuẩn xác cả số âm và số dương.
* **Bài B (Lexicographic Sort):** Sử dụng **MSD (Most Significant Digit) Radix Sort** dành cho chuỗi ký tự. Khi kích thước mảng con phân mảnh nhỏ hơn 32 phần tử, thuật toán tự động chuyển đổi sang **Insertion Sort** để giảm chi phí gọi hàm đệ quy.
* **Bài C (Length-aware Lexicographic Sort):** Thuật toán áp dụng chiến lược **Gom nhóm theo độ dài (Counting/Bucket Sort theo chiều dài chuỗi)** trước. Sau khi các chuỗi có cùng độ dài nằm cạnh nhau, **MSD Radix Sort** được kích hoạt cục bộ trên từng nhóm độ dài, với ngưỡng chuyển đổi sang Insertion Sort là khi mảng con nhỏ hơn 25 phần tử.

### Các phương thức tối ưu hóa liên quan:
1.  **Tối ưu hóa I/O bằng bộ đệm tự chế:** Thay vì dùng `std::cin` và `std::cout` (dù đã mở lệnh giải phóng đồng bộ), nhóm xây dựng hệ thống đọc/ghi thủ công bằng `fread` và `fwrite` với kích thước vùng đệm lớn (`1 << 20` đến `1 << 24` bytes). Hàm `readInt()`, `writeInt()`, `print_str()` xử lý trực tiếp trên mảng ký tự giúp triệt tiêu hoàn toàn chi phí ép kiểu và nghẽn dòng I/O.
2.  **Quản lý bộ nhớ đệm hiệu quả (Cache Locality):** Toàn bộ dữ liệu chuỗi ở bài B và C được nạp một lần duy nhất vào một vùng nhớ lớn (`pool`) bằng `malloc`. Các phần tử mảng thực chất chỉ là các con trỏ `char*` trỏ trực tiếp vào vùng đệm này, hạn chế tối đa việc cấp phát động rải rác gây phân mảnh bộ nhớ.
3.  **Trình biên dịch tối ưu (Compiler Optimization):** Sử dụng các chỉ thị cấu hình thực thi phần cứng mạnh mẽ ở đầu file bài B:
    ```cpp
    #pragma GCC optimize("O3,unroll-loops")
    #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
    ```

### Lý giải tại sao phương pháp này tốt nhất:
Các thuật toán so sánh như `std::sort` (Introsort), Quick Sort hay Merge Sort có độ phức tạp trung bình là $O(N \log N)$. Trong khi đó, Radix Sort xử lý với độ phức tạp tiệm cận tuyến tính $O(N \cdot K)$ (với $K$ là số lượt quét ký tự hoặc số byte cố định). Việc triệt tiêu chi phí so sánh cặp chuỗi đắt đỏ (`strcmp`), kết hợp với cơ chế tăng tốc đọc ghi dữ liệu từ bộ đệm I/O giúp các mã nguồn này đạt tốc độ xử lý nhanh nhất trong lần chạy 1.

---

## 2. Cách thức sinh test case trong `test_gen.cpp`

Bộ sinh test case được thiết kế nhằm mục đích khai phá các giới hạn biên và cấu trúc xử lý đặc thù của các mã nguồn đứng đầu, buộc thuật toán của đối thủ rơi vào **trường hợp xấu nhất (Worst Case)** để tăng tối đa thời gian chạy.

### Phân tích chi tiết chiến thuật sinh test:

* **Bài A (Mã tham số `int` từ 1 đến 5):**
    * *Thuật toán mục tiêu:* Radix Sort 16-bit kết hợp bộ đọc ghi `readInt`/`writeInt`.
    * *Cơ chế tăng thời gian:* Radix Sort ít bị ảnh hưởng bởi thứ tự mảng, do đó test case tập trung đánh vào hàm I/O. Sinh ra mảng tối đa $10^5$ phần tử với các giá trị biên cực đại và cực tiểu đan xen (`2147483647` và `-2147483648`). Việc này ép hàm phân tách chữ số (`writeInt`) phải chạy đủ tối đa 10-12 lượt chia cho mỗi số và xử lý thêm ký tự dấu trừ `-`, tiêu tốn nhiều chu kỳ CPU nhất có thể.

* **Bài B (Mã tham số `strlexi` từ 1 đến 5):**
    * *Thuật toán mục tiêu:* MSD Radix Sort chuỗi có ngưỡng fallback Insertion Sort khi $N < 32$.
    * *Cơ chế tăng thời gian:* Điểm yếu của MSD Radix Sort là đệ quy sâu khi gặp các chuỗi có tiền tố giống nhau. Test case tạo ra các cụm gồm **31 chuỗi** có **98 ký tự đầu tiên giống hệt nhau** (ký tự `a` hoặc `z`), và chỉ khác biệt ở 2 ký tự cuối cùng. Đặc biệt, 2 ký tự cuối được sinh theo thứ tự **giảm dần (nghịch thế)**. 
    * *Lý do tăng thời gian:* Với kích thước cụm là 31 (nhỏ hơn 32), mã nguồn đối thủ sẽ kích hoạt Insertion Sort. Vì 98 ký tự đầu giống nhau, hàm so sánh phải duyệt qua toàn bộ tiền tố mới nhận biết được sự khác biệt. Đồng thời, do mảng con đang bị nghịch thế hoàn toàn, Insertion Sort sẽ phải thực hiện số lần dịch chuyển tối đa. Độ phức tạp tại mỗi mảng con bị đẩy từ tuyến tính lên $O(32^2 \times \text{Độ dài chuỗi})$, khiến tổng thời gian chạy bùng nổ vượt ngưỡng Time Limit.

* **Bài C (Mã tham số `strlenlexi` từ 1 đến 5):**
    * *Thuật toán mục tiêu:* Bộ phân loại độ dài kết hợp MSD Radix Sort có ngưỡng fallback < 25.
    * *Cơ chế tăng thời gian:* Đầu tiên, sinh ra tất cả $10^4$ chuỗi có **cùng một độ dài duy nhất là 100**. Điều này vô hiệu hóa hoàn toàn bước gom nhóm theo độ dài của đối thủ (toàn bộ dữ liệu bị dồn vào đúng một bucket). Tiếp theo, áp dụng chiến thuật tương tự bài B: Chia mảng thành các cụm gồm **24 chuỗi** trùng lặp tiền tố sâu đến ký tự thứ 98 và đảo ngược phần hậu tố. Thuật toán của đối thủ sẽ bị ép phải chạy Insertion Sort trường hợp xấu nhất trên một không gian bộ nhớ chuỗi liên tục, gây nghẽn bộ đệm Cache và kéo dài thời gian xử lý.

---

## 3. Thuật toán cài đặt tốt nhất ở lần thứ hai (Benchmark 2)

Sau khi trải qua giai đoạn Hacking Phase và đối mặt với các bộ test case "ác tính" làm bùng nổ chi phí đệ quy và suy biến Insertion Sort, thuật toán ở lần thứ hai đã được nâng cấp để tăng tính phòng thủ vững chắc.

### Các phương pháp tối ưu hóa và khắc phục:
1.  **Chống suy biến đệ quy bằng thuật toán lai (Hybrid Sort):** Thay vì tin tưởng hoàn toàn vào MSD Radix Sort khi xử lý tiền tố dài, nhóm tích hợp cơ chế kiểm tra độ sâu đệ quy. Nếu độ sâu vượt quá một ngưỡng cố định (ví dụ qua 50 ký tự mà kích thước mảng con vẫn chưa phân rã đủ nhỏ), thuật toán tự động chuyển hướng sang **Introsort** hoặc hàm tối ưu hóa hệ thống `std::sort`.
2.  **Sử dụng Tìm kiếm nhị phân cho Insertion Sort (Binary Insertion Sort):** Ở các nhánh mảng con kích thước nhỏ, thay vì dùng Insertion Sort tuyến tính thông thường (phải so sánh chuỗi tuần tự từ phải qua trái), nhóm áp dụng tìm kiếm nhị phân để xác định vị trí chèn. Điều này giúp giảm số lần gọi hàm so sánh chuỗi trùng tiền tố từ $O(M^2)$ xuống còn $O(M \log M)$ (với $M$ là kích thước mảng con fallback).
