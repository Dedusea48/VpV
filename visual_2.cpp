#include <iostream>
#include <windows.h>
#include <ctime>
#include <fstream>

using namespace std;

const int xo = 479; // начальные кординаты
const int yo = 279; // начальные кординаты
const int s = 100;  // маштаб
const int r = 3;    // радиус шара

void frame(long double (*a)[6], clock_t milliseconds) {

    HWND hwnd = GetConsoleWindow();
    HDC hdc = GetDC(hwnd);

    for (int r1 = r; r1 != -r - 1; r1--)
        for (int r2 = -r; r2 != r + 1; r2++) {
            SetPixel(hdc, xo + (int) (a[0][0] * s) + r1, yo + (int) (a[0][1] * s) + r2,
                     RGB(0, 0, 255));
            SetPixel(hdc, xo + (int) (a[0][2] * s) + r1, yo + (int) (a[0][3] * s) + r2,
                     RGB(255, 0, 0));
            SetPixel(hdc, xo + (int) (a[0][4] * s) + r1, yo + (int) (a[0][5] * s) + r2,
                     RGB(0, 255, 0));
        }


    clock_t time_end = clock() + milliseconds * CLOCKS_PER_SEC / 1000;
    for (; clock() <= time_end;) { time_end = time_end; }

    // Стираем
    for (int r1 = r; r1 != -r - 1; r1--) {
        for (int r2 = -r; r2 != r + 1; r2++) {
            SetPixel(hdc, xo + (int) (a[0][0] * s) + r1, yo + (int) (a[0][1] * s) + r2,
                     RGB(12, 12, 12));
            SetPixel(hdc, xo + (int) (a[0][2] * s) + r1, yo + (int) (a[0][3] * s) + r2,
                     RGB(12, 12, 12));
            SetPixel(hdc, xo + (int) (a[0][4] * s) + r1, yo + (int) (a[0][5] * s) + r2,
                     RGB(12, 12, 12));
        }
    }
    SetPixel(hdc, xo + (int) (a[1][0] * s), yo + (int) (a[1][1] * s),
             RGB(0, 0, 200));
    SetPixel(hdc, xo + (int) (a[1][2] * s), yo + (int) (a[1][3] * s),
             RGB(200, 0, 0));
    SetPixel(hdc, xo + (int) (a[1][4] * s), yo + (int) (a[1][5] * s),
             RGB(0, 200, 0));
    ReleaseDC(hwnd, hdc);
}
void com(long double (*a)[6]) {
    HWND hwnd = GetConsoleWindow();
    HDC hdc = GetDC(hwnd);
    for (int r1 = r-1; r1 != -r; r1--)
        for (int r2 = -r+1; r2 != r; r2++)
            SetPixel(hdc, xo + (int) ((a[0][0] + a[0][2] + a[0][4])*s/3) + r1, yo + (int) ((a[0][1] + a[0][3] + a[0][5])*s/3) + r2,
                     RGB(255, 255, 255));
    ReleaseDC(hwnd, hdc);
}


int main() {
    setlocale(LC_ALL, "RUS");
    system("mode con cols=120 lines=50"); // Задаём размеры консоли

    long double a[2][6];


    fstream F;
    F.open("D:\\data\\data5.txt");

    if (F) {

        for (int i = 0; !F.eof(); i++) { //когда достигнем конца файла, в этом случае F.eof() вернет истину.

            for (int k = 0; k != 6; k++)
                a[1][k] = a[0][k];

            F >> a[0][0] >> a[0][1] >> a[0][2] >> a[0][3] >> a[0][4] >> a[0][5];//чтение очередного значения из потока F
            frame(a, 15);// Рисуем
            com(a);      // Рисуем центр масс
        }
        F.close(); //закрытие потока
    } else
        cout << "Fail not exist" << endl;  //если открытие файла прошло некорректно


    system("pause");
    cout << "END.";
    return 0;
}