Em chào thầy! :))
Hôm nay em quay clip này để giới thiệu cho thầy và các bạn về game mà em sẽ định làm

Nói qua một chút về game thì nó sẽ là một game rắn săn mồi với logic bình thường như bao game rắn khác. Vì em chưa quen hoàn toàn với việc sử dụng SDL nên
nghĩ ra game mới sẽ tương đối khó khăn và phức tạp nên em quyết định sẽ làm một game có sẵn và tùy biến

Game sẽ có những tính năng sau:
- Giao diện đồ họa
- Game Menu:
    + Play
    + Highscore
    + Credit
- Game logic: sẽ giống như game rắn bình thường, rắn chạy trong 1 khung vuông kích cỡ 600 x 580 có tường bao quanh. Rắn tìm kiếm và ăn thức ăn để tăng độ
dài lên, trò chơi sẽ kết thúc nếu rắn đâm vào tường hoặc tự cắn vào thân mình
- Đó vẫn chưa phải những tính năng cuối cùng nhưng em sẽ cố gắng làm được ít nhất là như miêu tả trên, nếu điều kiện về thời gian và trình độ cho chép e sẽ
cố gắng mở rộng các tính năng của trò chơi

Hướng làm:
- Tạo ra các đối tượng: bề mặt(render background,score board,wall,..: những đối tượng không di chuyển), rắn, thức ăn.
- Tọa độ hóa các đối tượng là rắn và thức ăn sao cho chúng có tọa độ hay đổi, mỗi đốt rắn là một đối tượng trong cấu trúc struct Tọa độ và lưu dưới dạng
mảng của tọa độ đó 
example
   snake[0] : x0, y0
   snake[1] : x1, y1
- Mỗi khí tọa độ của đầu rắn trùng với tọa độ thức ăn thì độ dài mảng sẽ tăng

Tiến độ:
Hiện tại em đang trong quá trình khiến cho rắn có thể di chuyển và render được con rắn có nhiều đốt lên màn hình, em sẽ demo game vào thời điểm hiện tại


Em đã kết thúc phần trình bày của mình.
Em chào thầy !!

