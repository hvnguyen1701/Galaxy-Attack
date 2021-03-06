# Galaxy Attack

* Họ tên: Hoàng Văn Nguyên
* Mã sinh viên: 21020370
* Lớp môn học: INT2215 1, nhóm 8

## Mục lục
* [1. Hướng dẫn cài đặt](#huong-dan-cai-dat)  
* [2. Mô tả chung về trò chơi, các ý tưởng chính](#mo-ta-chung)  
* [3. Mô tả các chức năng đã cài đặt](#mo-ta-chuc-nang)  
* [4. Các kỹ thuật lập trình được sử dụng trong chương trình](#ky-thuat-lap-trinh)  
* [5. Kết luận, hướng phát triển và các điều tâm đắc rút ra được sau khi hoàn thiện chương trình](#ket-luan)

<a name="huong-dan-cai-dat"/>

## 1. Hướng dẫn cài đặt

Bắt đầu bằng việc cài đặt [MinGW-W64 GCC-7.3.0-SEH](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/7.3.0/threads-win32/seh/x86_64-7.3.0-release-win32-seh-rt_v5-rev0.7z) và [git](https://git-scm.com/downloads).

### Cài đặt MinGW-W64 (64bit)
* Giải nén file x86_64-7.3.0-release-win32-seh-rt_v5-rev0.7z
* Copy thư mục `mingw64` vào **<ROOTDIR>** (Ví dụ `D:\software`)
* Cài đặt đường dẫn PATH đến **<ROOTDIR>\mingw64\bin**
* Kiểm tra bằng cách gọi `g++` và `mingw32-make` trong terminal

### Cách lấy chương trình về
  
Tiếp theo, sao chép kho lưu trữ này bằng cách mở một trình Terminal và nhập các lệnh sau (không nhập ký tự $ đầu tiên trên mỗi dòng, đó chỉ là quy ước để cho thấy rằng đây là dấu nhắc của Terminal):
```
$ git clone https://github.com/hvnguyen1701/Galaxy-Attack.git
$ cd Galaxy-Attack
```
  
### Chạy những lệnh sau đây là có thể chạy được chương trình:
  
```
$ mingw32-make
$ ./GalaxyAttack.exe
```

* Chú ý: 
```
libpng warning: iCCP: known incorrect sRGB profile
libpng warning: iCCP: cHRM chunk does not match sRGB
libpng warning: iCCP: known incorrect sRGB profile
libpng warning: iCCP: cHRM chunk does not match sRGB
libpng warning: iCCP: known incorrect sRGB profile
libpng warning: iCCP: cHRM chunk does not match sRGB
```
Những `libpng warning` ở trên khi chạy chương trình không phải là lỗi do code mà là do ảnh lấy từ trên internet.
  
* Nếu gặp trục trặc, lỗi, vui lòng liên hệ với em để biết thêm thông tin.

<a name="mo-ta-chung"/>
  
## 2. Mô tả chung về trò chơi, các ý tưởng chính
  
* Người chơi vào vai nhân vật Solu (solution) điều khiển phi thuyền Fantom chiến đấu với kẻ thù trong vũ trụ (chi tiết cốt truyện có thể xem trong game).
* Người chơi có lượng giáp tối đa là 5, nếu lượng giáp trở về 0, chỉ cần dính một viên đạn nữa thì trò chơi sẽ kết thúc, nếu va chạm với tàu địch hoặc thiên thạch sẽ lập tức dừng trò chơi bất kể lượng giáp nhiều đến đâu.
* Có thể thu thập các vật phẩm (item) để tăng lượng giáp, đổi loại đạn.
* Cố gắng né tránh đạn của kẻ thù, phi thuyền địch, các viên thiên thạch.
* Tiêu diệt được một kẻ địch sẽ được điểm, cố gắng lấy được điểm càng cao càng tốt trước khi bị game over.

<a name="mo-ta-chuc-nang"/>
  
## 3. Mô tả các chức năng đã cài đặt

[Video minh họa](https://youtu.be/hUkjESWQ4_4) (thật ra game rất mượt nhưng vì máy yếu nên lúc quay video hơi giật)
  
### Game có cốt truyện, hướng dẫn chơi.
  
### Sinh ra và di chuyển:
  * Trượt bản đồ (tạo cảm giác như đang di chuyển).
  * Phi thuyền địch sinh ra ngẫu nhiên ở phía trên màn hình và có thể di chuyển sang ngang (trái, phải) hoặc tiến tới.
  * Thiên thạch rơi ngẫu nhiên từ 2 bên và di chuyển xuống dưới.
  * Khi đạt được số điểm nhất định sẽ xuất hiện cổng không gian.
  * Các loại đạn được bắn liên tục.
  * Khi hạ gục kẻ địch có xác suất rơi vật phẩm (item), nhặt được sẽ tăng giáp, đổi loại đạn.
  
### Xử lý va chạm:
  * Giữa phi thuyền người chơi và
    * đạn của phi thuyền địch.
    * phi thuyền địch.
    * thiên thạch.
    * cổng dịch chuyển không gian.
    * vật phẩm.
  * Giữa phi thuyền địch và
    * đạn của phi thuyền người chơi.
    * thiên thạch.

### Xử lý các vụ nổ:
  * Vụ nổ phi thuyền địch (có hiệu ứng).
  * Vụ nổ phi thuyền người chơi (có hiệu ứng).

### Điểm số:
  * In ra màn hình Menu điểm của 3 người có số điểm cao nhất (có cập nhật).
  * Cập nhật điểm số liên tục trong lúc chơi trò chơi.

### Giao diện người dùng:
  * Màn hình Menu:
    * Nút `Play`: bắt đầu chơi.
    * Nút `Help`: đọc cốt truyện và hướng dẫn chơi (có 3 trang, có nút bấm `Next` để sang trang mới).
    * Nút `Exit`: thóa khỏi trò chơi.
  * Màn hình Pause Game:
    * Nút `Continue`: tiếp tục chơi game.
    * Nút `Back`: trở về màn hình Menu.
  * Màn hình Game Over:
    * Click bất kì vào màn hình để về màn hình Menu.
  * Có hiển thị thanh giáp của nhân vật lúc chơi trò chơi.

### Trong lúc chơi trò chơi nếu ấn phím `Esc` hoặc `Alt + Tab` hoặc phím `Windows`, game sẽ được dừng lại (chuyển qua màn hình Pause).

### Hiệu ứng hình ảnh lúc dùng cổng không gian.

### Âm thanh:
  * Nhạc nền.
  * Tiếng nổ của phi thuyền người chơi.
  * Tiếng nổ của phi thuyền kẻ địch.
  * Tiếng nhặt được vật phẩm.
  * Tiếng đạn được bắn ra.
  * Tiếng dùng cổng không gian.
 
### Xử lý FPS (Frames per second): tùy chỉnh tùy ý.

<a name="ky-thuat-lap-trinh"/>
  
## 4. Các kỹ thuật lập trình được sử dụng trong chương trình
  
* Sử dụng mảng, vector, string, vector con trỏ, hàm sort.
* Cấp phát động, quản lý bộ nhớ.
* Sinh số ngẫu nhiên.
* Nhập xuất file `.log`.
* Sử dụng tham chiếu, tham trị, hằng tham chiếu.
* Sử dụng Class
  * private, protected, public.
  * Class kế thừa.
  * Hàm khởi tạo (constructor) và hàm hủy (destructor).
  * Hàm hằng.
* Tách hàm, tách file, quản lý file `.cpp` và file `.h`.
* Sử dụng thư viện đồ họa SDL2, SDL2 image, SDL2 mixer, SDL2 ttf.
* Log và báo cáo lỗi.

<a name="ket-luan"/>
  
## 5. Kết luận, hướng phát triển và các điều tâm đắc rút ra được sau khi hoàn thiện chương trình
  
### Kết luận
  * Làm game không quá khó, nhưng cần rất nhiều thời gian, cần có ý tưởng sáng tạo thì mới tạo nên trò chơi cuốn hút được.
  * Có nhiều ý tưởng nhưng không phải cái nào cũng thực hiện được.
  * Thư viện đồ họa khá quan trọng trong việc thiết kế game.
  * Không cần dùng những thuật toán hay cấu trúc dữ liệu phức tạp cũng có thể làm nên một game tuyệt vời.
  
### Hướng phát triển tiếp theo
  * Có thể sử dụng thư viện đồ họa khác đẹp hơn.
  * Thêm nhiều loại đạn có sức mạnh khác nhau.
  * Bổ sung thêm các vật phẩm (item) có công dụng khác nhau.
  * Thêm loại đạn tên lửa hành trình theo dõi mục tiêu (dùng thuật toán A* hoặc BFS, Dijkstra, ...).
  * Bổ sung thêm boss có thanh máu, thêm nhiều loại kẻ địch có sức mạnh khác nhau.
  * Thêm chức năng chọn độ khó của game (dễ, thường, khó).
  * Cải thiện lại giao diện.
  * Cải tiến cốt truyện.
  * Tối ưu, cải tiến mã nguồn hơn nữa.
  
### Các điều tâm đắc rút ra được sau khi hoàn thiện chương trình
  * Tìm kiếm hình ảnh miễn phí mà bản thân cảm thấy hài lòng là rất khó.
  * Làm game thất sự cần một designer.
  * Hiểu được logic của game, các bước thiết kế, xây dựng game.
  * Nếu tách file, tách hàm nhiều, viết code như kể chuyện thì rất dễ gỡ lỗi và đọc code cũng rất dễ hiểu.
  * Tưởng tượng và thực thi rất khác xa nhau.

## Nguồn tham khảo:
  * https://github.com/chauttm/advprogram
  * https://www.stdio.vn
  * https://lazyfoo.net
  * https://wiki.libsdl.org
  * https://www.libsdl.org/projects/SDL_image/docs/SDL_image.html
  * https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer.html
  * https://www.libsdl.org/projects/docs/SDL_ttf/SDL_ttf.html
