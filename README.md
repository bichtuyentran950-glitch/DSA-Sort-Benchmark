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

Trong giai đoạn đầu của dự án, mục tiêu hàng đầu của nhóm là xây dựng một bộ khung giải thuật tường minh, có tính tổng quát cao nhằm nhanh chóng định hình cấu trúc phân rã dữ liệu. Do đó, nhóm đã lựa chọn thuật toán **Quick Sort phân hoạch theo cơ chế Hoare (Hoare Partition Scheme)** làm nền tảng cốt lõi cho cả 3 bài toán kiểm thử hiệu năng.

### Phân tích chi tiết giải thuật cài đặt trong mã nguồn:

#### A. Bài A (Integer Sort): Phân hoạch điểm chốt trung vị tuyến tính
* **Cơ chế hoạt động:** Thuật toán áp dụng mô hình chia để trị kinh điển. Điểm chốt (pivot) được lựa chọn trực tiếp tại vị trí trung tâm của mảng `a[(left + right) / 2]` nhằm nỗ lực chia mảng thành hai nửa cân bằng về mặt kích thước.
* **Tối ưu hóa hệ thống:** Nhóm đã cô lập hai dòng lệnh `ios_base::sync_with_stdio(false);` và `cin.tie(nullptr);` nhằm ngắt liên kết giữa luồng nhập xuất của C và C++, giúp giảm tải chi phí đồng bộ và đẩy tốc độ đọc luồng dữ liệu của `cin/cout` tiệm cận tốc độ của bộ hàm `scanf/printf`. Việc sử dụng con trỏ động cấp phát qua từ khóa `new` giúp chương trình tối ưu hóa việc sử dụng vùng nhớ Heap thay vì làm tràn vùng nhớ Stack khi kích thước dữ liệu $N$ đạt ngưỡng $10^5$.

#### B. Bài B (Lexicographic Sort): Quick Sort cải tiến chọn Chốt Trung Vị Ba Phần Tử (Median-of-Three Pivot)
* **Cơ chế chọn chốt nâng cao:** Để cải thiện nhược điểm của việc chọn chốt cố định, nhóm đã xây dựng hàm bổ trợ `medianPivot`. Hàm này thực hiện so sánh ba phần tử đứng đầu (`l`), đứng giữa (`mid`) và đứng cuối (`r`) của phân đoạn, sau đó hoán vị để lấy ra phần tử có giá trị trung vị làm chốt.
* **Lợi điểm hiệu năng:** Kỹ thuật chọn chốt này giúp giải thuật Quick Sort có độ phòng thủ tốt hơn trước các mảng dữ liệu đã được sắp xếp sẵn hoặc mảng nghịch thế, cố gắng duy trì cây đệ quy ở trạng thái lý tưởng là $O(N \log N)$ và hạn chế chi phí mất cân bằng phân hoạch.

#### C. Bài C (Length-aware Lexicographic Sort): Phân loại đa tiêu chí dựa trên hàm so sánh tùy biến (Custom Comparator)
* **Xây dựng hàm so sánh phức hợp:** Để đáp ứng yêu cầu ưu tiên về chiều dài chuỗi trước rồi mới đến thứ tự từ điển, nhóm đã thiết kế hàm logic `cmp(const string &s, const string &t)`. Hàm này đóng vai trò là một bộ lọc hai tầng:
  ```cpp
  if (s.size() != t.size())
      return s.size() < t.size();
  return s < t;




## 2. Cách thức sinh test case trong test_gen.cpp

Hệ thống sinh dữ liệu kiểm thử (Test Generator) được thiết kế có mục đích chiến lược: Không sinh dữ liệu ngẫu nhiên một cách mù quáng, mà tập trung bẻ gãy cấu trúc dữ liệu và khai thác tối đa các góc khuất (Corner Cases) trong mã nguồn đối thủ, ép các giải thuật của họ rơi vào trạng thái suy biến tệ nhất (Worst-case Scenario).

### Phân tích chi tiết chiến thuật sinh test

## 2. Cách thức sinh test case trong test_gen.cpp

Hệ thống sinh dữ liệu kiểm thử (`test_gen.cpp`) được thiết kế dựa trên một chiến lược tấn công có chủ đích: Chủ động phân tích kiến trúc mã nguồn của đối thủ để tìm ra các góc khuất thuật toán, từ đó sinh dữ liệu "ác tính" nhằm ép các giải thuật lai và các tầng đệ quy của họ rơi vào trạng thái suy biến tệ nhất (Worst-case Scenario).

[CHIẾN THUẬT BẺ GÃY THUẬT TOÁN ĐỐI THỦ]
                                   
    ─► Bài A: Ép Introsort di chuyển phần tử xa ──► Phá vỡ L1/L2 Cache
    
    ─► Bài B: Ép MSD Radix Sort đệ quy sâu 99 tầng ──► Quá tải bộ nhớ Stack
    
    ─► Bài C: Khai thác tính Unstable của Counting Sort ──► Phá hủy Logic (WA)

    ---

### 1. Chi tiết chiến thuật bẻ gãy thuật toán Bài A (Số nguyên)

* **Thuật toán mục tiêu của đối thủ:** Đối thủ cài đặt thuật toán lai **Introsort** (`Sort_ket_hop`). Giải thuật này sử dụng QuickSort phân hoạch 3 nhánh (`Phan_hoach_3way`) kết hợp chọn chốt trung vị làm chủ đạo, tự động chuyển giao sang HeapSort (`Heap_Sort`) nếu độ sâu đệ quy vượt ngưỡng $2 \times \log_2(N)$, và dọn dẹp bằng Insertion Sort (`Insertion_Sort`) khi kích thước mảng con nhỏ hơn hoặc bằng 24.
* **Lý do lựa chọn thuật toán mục tiêu này:** Introsort là một bộ phòng thủ rất mạnh, mục tiêu của đối thủ là tránh bẫy suy biến $O(N^2)$ kinh điển của QuickSort bằng cách ép cây đệ quy chuyển sang HeapSort khi gặp mảng bị chia lệch. Do đó, nếu chỉ sinh test xếp sẵn thông thường, HeapSort của đối thủ sẽ xử lý rất dễ dàng trong $O(N \log N)$. Nhóm quyết định không đánh vào độ sâu đệ quy, mà đánh thẳng vào **chi phí hoán đổi phần tử trên RAM** và **kiến trúc bộ nhớ đệm**.
* **Cơ chế tăng thời gian chạy trong `test_gen.cpp`:**
    * **Test case 1 & 3 (Min/Max đan xen và Mảng giảm dần):** Hệ thống sinh test chủ động tạo ra tập dữ liệu có quy luật nghịch thế hoàn toàn hoặc các giá trị biên đan xen cực đại/cực tiểu liên tục (`2147483647` và `-2147483648`). 
    * **Tại sao test này làm chậm đối thủ:** Dù hàm `Trung_vi` của đối thủ có cố gắng chọn một phần tử chốt ở giữa, nhưng cấu trúc mảng nghịch thế buộc các vòng lặp dịch con trỏ `while (v[i] < pivot)` và `while (v[j] > pivot)` luôn dừng lại ở hai đầu mút của phân đoạn. Điều này ép câu lệnh `swap(v[i], v[lt])` hoặc `swap(v[i], v[gt])` phải thực hiện tráo đổi các phần tử nằm cách xa nhau nhất trong bộ nhớ vật lý. Hành vi này liên tục bẻ gãy tính liên tục của dữ liệu, gây ra hiện tượng trượt bộ đệm liên tục (**L1/L2 Cache Misses**). CPU bắt buộc phải nạp lại dữ liệu từ RAM thay vì Cache, khiến số lượng chu kỳ máy tăng vọt và làm chậm đáng kể vận tốc thực thi của Introsort.

---

### 2. Chi tiết chiến thuật bẻ gãy thuật toán Bài B (Từ điển)

* **Thuật toán mục tiêu của đối thủ:** Đối thủ cài đặt thuật toán **MSD (Most Significant Digit) Radix Sort** thuần túy hoạt động trực tiếp trên mảng chuỗi `vector<string> &v`. Tại mỗi tầng, thuật toán khởi tạo mảng đếm `int count[29]` để phân loại ký tự, sau đó thực hiện hoán vị chuỗi qua mảng tạm bằng lệnh `swap(temp[count[c]++], v[i])` và gán ngược lại bằng `swap(v[i], temp[i - low])`. Đặc biệt, thuật toán của đối thủ **không cấu hình ngưỡng cắt đệ quy (No Fallback Threshold)** cho các mảng kích thước nhỏ.
* **Lý do lựa chọn thuật toán mục tiêu này:** MSD Radix Sort có ưu điểm xử lý chuỗi ký tự theo tốc độ tuyến tính, tuy nhiên điểm yếu cốt lõi của nó là sự phụ thuộc vào độ dài tiền tố trùng nhau. Đối thủ lại thao tác hoán vị trực tiếp trên các đối tượng `std::string` và để nhánh đệ quy chạy sâu tuyệt đối đến khi phân đoạn mảng con chỉ còn $\le 1$ phần tử mới dừng lại. Nhóm quyết định đánh thẳng vào **giới hạn bộ nhớ Stack** của kiến trúc đệ quy này.
* **Cơ chế tăng thời gian chạy trong `test_gen.cpp`:**
    * **Test case 1, 2 & 3 (Trùng lặp tiền tố sâu):** Hệ thống sinh test tạo ra $10^5$ chuỗi ký tự có độ dài tối đa (100 ký tự), trong đó **98 đến 99 ký tự đầu tiên giống hệt nhau** (toàn bộ là ký tự `'a'`, `'z'` hoặc `'x'`) và chỉ sinh sai biệt ngẫu nhiên ở 1 - 2 ký tự cuối cùng theo thứ tự nghịch thế.
    * **Tại sao test này làm chậm đối thủ:** Khi nạp bộ dữ liệu này, giải thuật của đối thủ không thể phân tách mảng ở 98 tầng đầu tiên vì tất cả ký tự đều rơi vào cùng một bucket. Chương trình bị ép phải gọi đệ quy sâu xuống 98 tầng liên tục cho toàn bộ quy mô dữ liệu. Tại mỗi tầng đệ quy, CPU phải tiêu tốn tài nguyên để khởi tạo lại mảng đếm `count` cục bộ và thực hiện hai vòng lặp gán `swap` chuỗi thực tế. Việc tráo đổi con trỏ quản lý vùng nhớ Heap của đối tượng `std::string` ở độ sâu đệ quy lớn sẽ gây ra hiện tượng quá tải bộ nhớ đệm Stack (**Stack Overflow / Stack Overhead**), đẩy thời gian chạy vượt ngưỡng đóng băng hệ thống và kích hoạt lỗi **Time Limit Exceeded (TLE)** hoặc **Memory Limit Exceeded (MLE)**.

---

### 3. Chi tiết chiến thuật bẻ gãy thuật toán Bài C (Độ dài + Từ điển)

* **Thuật toán mục tiêu của đối thủ:** Đối thủ giải quyết bài toán sắp xếp phức hợp (ưu tiên độ dài trước, từ điển sau) bằng cách thực hiện quy trình ngược: Đầu tiên gọi hàm `msd_radix_sort` trên toàn bộ mảng chuỗi để xếp theo thứ tự từ điển, sau đó gọi hàm `countingSort` dựa trên độ dài chuỗi (`a[i].length()`) để đưa các chuỗi ngắn lên đầu mảng.
* **Lý do lựa chọn thuật toán mục tiêu này:** Nhóm phát hiện một sai lầm nghiêm trọng trong tư duy thiết kế luồng xử lý của đối thủ. Thay vì gom nhóm độ dài trước rồi mới xếp từ điển, đối thủ lại xếp từ điển trước rồi cố gắng dùng một tầng Counting Sort ở cuối để sắp đặt lại vị trí theo chiều dài. Nhóm lựa chọn thuật toán mục tiêu này để đánh gãy **tính ổn định (Stability)** của giải thuật sắp xếp, tạo ra sự sai lệch kết quả đầu ra.
* **Cơ chế tăng thời gian chạy trong `test_gen.cpp`:**
    * **Test case 1, 2 & 3 (Chiều dài đồng nhất kết hợp lặp tiền tố):** Hệ thống sinh test ép toàn bộ dữ liệu $10^4$ chuỗi rơi vào **cùng một độ dài duy nhất là 100 ký tự**, đồng thời áp dụng cấu trúc lặp tiền tố sâu giống như Bài B.
    * **Tại sao test này làm chậm và phá hủy mã nguồn đối thủ:** 1. *Về mặt thời gian chạy:* Việc trùng độ dài khiến bước `countingSort` của đối thủ bị vô hiệu hóa vì toàn bộ dữ liệu bị dồn vào đúng một bucket độ dài duy nhất. Thuật toán của đối thủ bị ép phải xử lý toàn bộ áp lực sắp xếp từ điển ở bước 1 trên một không gian chuỗi lặp tiền tố, gây nghẽn Cache và chậm hệ thống tương tự Bài B.
        2. *Về mặt phá hủy logic (Trọng tâm):* Trong hàm `countingSort`, đối thủ viết lệnh hoán vị dữ liệu thông qua cấu trúc dồn ép chỉ số mảng tạm: `swap(temp[count[len]++], a[i])`. Trong khoa học máy tính, hành vi hoán đổi vị trí dựa trên cơ chế hoán vị trực tiếp mảng gốc này là một giải thuật **Sắp xếp không ổn định (Unstable Sort)**. Nó hoàn toàn không bảo toàn trật tự vị trí tương đối của các phần tử có cùng giá trị phân loại (cùng độ dài 100). Hậu quả là, sau khi chạy xong tầng Counting Sort của đối thủ, toàn bộ trật tự từ điển đã được sắp xếp vất vả ở bước 1 sẽ bị đảo lộn và phá hủy hoàn toàn. Chương trình của đối thủ sẽ xuất ra kết quả sai lệch logic đề bài và nhận điểm số 0 (**Wrong Answer**) ngay lập tức từ hệ thống.
---

## 3. Thuật toán cài đặt tốt nhất ở lần thứ hai (Benchmark 2)

### Phân tích chi tiết giải thuật cài đặt trong mã nguồn nhóm
Mặc dù bộ khung giải thuật Quick Sort ở vòng Benchmark 1 mang lại sự mạch lạc về mặt cấu trúc và dễ dàng cài đặt, nhóm thẳng thắn nhìn nhận mã nguồn lúc đó vẫn còn tồn tại những lỗ hổng kỹ thuật nghiêm trọng dưới áp lực dữ liệu lớn của Codeforces:

* **Hiểm họa suy biến độ phức tạp $O(N^2)$ (Worst-case Scenario):**
  Trong Bài A và Bài C, việc chọn chốt cố định ở vị trí giữa mảng `(l + r) / 2` vô tình tạo ra một tử huyệt. Nếu đối thủ sử dụng bộ sinh test case có quy luật phân bố giá trị đặc biệt (ví dụ: các phần tử trùng lặp giá trị số lượng lớn hoặc các cấu trúc sắp xếp răng cưa), phân hoạch Hoare sẽ bị chia lệch hoàn toàn (một bên chứa 1 phần tử, bên còn lại chứa $N-1$ phần tử). Lúc này, cây đệ quy sẽ phình to thành $N$ tầng, độ phức tạp thời gian lập tức bị suy biến từ $O(N \log N)$ thành $O(N^2)$, gây ra lỗi **Time Limit Exceeded (TLE)**.
* **Chi chi phí hoán đổi đối tượng chuỗi nặng nề:**
  Trong Bài B và Bài C, việc sử dụng hàm `swap(a[i], a[j])` trực tiếp trên các mảng đối tượng `std::string` tạo ra gánh nặng rất lớn cho CPU. Mỗi phép hoán đổi bắt buộc phải thực hiện các chuỗi thao tác sao chép con trỏ vùng nhớ động trên Heap. Khi dữ liệu lớn và số lần hoán đổi tăng lên, chi phí quản lý vùng nhớ này sẽ lấn át hoàn toàn thời gian tính toán của thuật toán.

**💡 Giải pháp chuyển dịch:** Chính vì những giới hạn vật lý và hiểm họa suy biến hiệu năng của thuật toán dựa trên phép so sánh nêu trên, nhóm đã quyết định hướng đến một tư duy tiếp cận tối ưu hoàn toàn mới ở các giai đoạn sau: Thay thế Quick Sort bằng **Radix Sort** – giải thuật phi so sánh với độ phức tạp tuyến tính $O(N)$ để thiết lập hàng phòng thủ vững chắc trước mọi bộ test case ác tính.
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
## 4. Kết luận

Thông qua đồ án Benchmark 1 & 2, nhóm chúng em đã chứng minh được sức mạnh của việc kết hợp giữa cấu trúc dữ liệu tối ưu (**Radix Sort**) và các kỹ thuật lập trình tinh chỉnh hệ thống chuyên sâu (**Bitwise**, **Indirect Array**, **Output Buffer**). 

Mặc dù vẫn còn những điểm có thể cải tiến và tối ưu hơn nữa về mặt lý thuyết chống suy biến đệ quy chuỗi, nhóm tự hào rằng hệ thống hiện tại đã hoạt động với một hiệu suất thực thi cực kỳ cao, ổn định và đáp ứng tốt các áp lực dữ liệu lớn trên nền tảng kiểm thử.


