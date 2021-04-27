Sinh viên: Hoàng Gia Minh
ID: 20020443
Game: Rắn săn mồi

Luồng hoạt động: class Game có 2 hàm chính là init (hiển thị đồ họa của đối tượng trong trò chơi: rắn, tường,....) và run (nơi các sự kiện trong game xảy ra)
2 hàm đó sẽ được đặt trong hàm main. Các đối tượng sẽ được gọi trong hàm run.

Menu:
- Start: Lựa chọn chế độ chơi

- Highscore

- Credit: Thông tin về game

Gameplay + chức năng: Menu game, 2 chế độ gameplay 

Người chơi điều khiên rắn bằng các phím lên/xuống/trái/phải

+ Classic: Có tường bao quanh, trò chơi kết thúc khi rắn va chạm với thân hoặc đâm vào tường

+ Modern: Không có tường bao quanh: khi rắn đi ra ngoài khu vực chơi sẽ xuất hiện ở chiều ngược lại, trò chơi kết thúc chỉ khi rắn va chạm với thân

Khi trò chơi kết thúc thì màn hình sẽ render GAMEOVER dưới dạng ảnh và chuyển sang hiện thị xem người chơi có muốn chơi lại hay không, nếu có thì thoát vòng lặp
của chế độ chơi và đi đến game menu, nếu không thì thoát toàn bộ vòng lặp game, đóng cửa sổ.

