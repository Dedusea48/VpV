#include <iostream>
#include <windows.h>
#include <ctime>
#include <conio.h>
#include <fstream>

using namespace std;

const int xo = 900; // начальные кординаты
const int yo = 500; // начальные кординаты
const int r = 4;    // радиус шара

void frame(const long double a[6], int s , clock_t milliseconds) { // отрисовка тел, пауза, стираем кроя тел

    HWND hwnd = GetConsoleWindow();
    HDC hdc = GetDC(hwnd);

    for (int r1 = r; r1 != -r - 1; r1--) // отрисовка тел
        for (int r2 = -r; r2 != r + 1; r2++) {
            SetPixel(hdc, xo + (int) (a[0] * s) + r1, yo + (int) (a[1] * s) + r2,
                     RGB(200, 0, 255));
            SetPixel(hdc, xo + (int) (a[2] * s) + r1, yo + (int) (a[3] * s) + r2,
                     RGB(255, 200, 0));
            SetPixel(hdc, xo + (int) (a[4] * s) + r1, yo + (int) (a[5] * s) + r2,
                     RGB(255, 04, 0));
        }


    clock_t time_end = clock() + milliseconds * CLOCKS_PER_SEC / 1000; //пауза
    for (; clock() <= time_end;) { time_end = time_end; }

    // Стираем края тел
    for (int r1 = r; r1 != -r - 1; r1--) {
        for (int r2 = -r; r2 != r + 1; r2++) {
            if(abs(r1)>=r-1||abs(r2)>=r-1) {
                SetPixel(hdc, xo + (int) (a[0] * s) + r1, yo + (int) (a[1] * s) + r2,
                         RGB(242, 242, 242));
                SetPixel(hdc, xo + (int) (a[2] * s) + r1, yo + (int) (a[3] * s) + r2,
                         RGB(242, 242, 242));
                SetPixel(hdc, xo + (int) (a[4] * s) + r1, yo + (int) (a[5] * s) + r2,
                         RGB(242, 242, 242));
            }


        }
    }

}
void com(const long double a[6], int s) { //отрисовка центра масс
    HWND hwnd = GetConsoleWindow();
    HDC hdc = GetDC(hwnd);
    for (int r1 = r-1; r1 != -r; r1--)
        for (int r2 = -r+1; r2 != r; r2++)
            SetPixel(hdc, xo + (int) ((a[0] + a[2] + a[4])*s/3) + r1, yo + (int) ((a[1] + a[3] + a[5])*s/3) + r2,
                     RGB(0, 0, 0));
    ReleaseDC(hwnd, hdc);
}


int main() {
    system("color FC");
    setlocale(LC_ALL, "RUS");
    HWND hwnd;
    char Title[1024];
    GetConsoleTitle(Title, 1024); // Узнаем имя окна
    hwnd=FindWindow(nullptr, Title); // Узнаем hwnd окна
    ShowWindow(hwnd,SW_SHOWMAXIMIZED); // Увеличиваем размеры консоли до максимума

//    system("mode con cols=120 lines=50"); // Задаём размеры консоли

    fstream F;
    long double a[6];
    int in, s;

    for(;;) {
        cin >> in;
        switch (in) {
            case 1:
                F.open("D:\\data\\data1.txt");
                s = 300;  // маштаб
                break;
            case 2:
                F.open("D:\\data\\data2.txt");
                s = 600;  // маштаб
                break;
            case 3:
                F.open("D:\\data\\data3.txt");
                s = 300;  // маштаб
                break;
            case 4:
                F.open("D:\\data\\data4.txt");
                s = 300;  // маштаб
                break;
            case 5:
                F.open("D:\\data\\data5.txt");
                s = 300;  // маштаб
                break;
            case 6:
                F.open("D:\\data\\data6.txt");
                s = 500;  // маштаб
                break;
            case 7:
                F.open("D:\\data\\data7.txt");
                s = 200;  // маштаб
                break;
            case 8:
                F.open("D:\\data\\data8.txt");
                s = 200;  // маштаб
                break;
            case 9:
                F.open("D:\\data\\data9.txt");
                s = 200;  // маштаб
                break;
            default:
                return 0;
        }

        if (F) {
            for (int i = 0; !F.eof() && !kbhit(); i++) { //когда достигнем конца файла, в этом случае F.eof() вернет истину.

                F >> a[0] >> a[1] >> a[2] >> a[3] >> a[4] >> a[5];//чтение очередного значения из потока F
                frame(a,s, 15);// Рисуем
                com(a, s);      // Рисуем центр масс
            }
        } else
            cout << "Fail not exist" << endl;  //если открытие файла прошло некорректно

        F.close(); //закрытие потока
        system("pause");
    }
}