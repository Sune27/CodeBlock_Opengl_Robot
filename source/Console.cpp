#include "Console.h"
using namespace std;

void hideCursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    // Lấy thông tin hiện tại của con trỏ
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);

    // Thiết lập con trỏ cho kích thước tối thiểu để làm cho nó gần như vô hình
    cursorInfo.bVisible = TRUE;  // Đảm bảo con trỏ vẫn hiển thị (để tránh lỗi)
    cursorInfo.dwSize = 1;        // Đặt kích thước con trỏ là nhỏ nhất

    // Cập nhật thông tin con trỏ
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}
void setCursorPosition(int x, int y)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cursorPosition;
    cursorPosition.X = x;
    cursorPosition.Y = y;
    SetConsoleCursorPosition(console, cursorPosition);
}
