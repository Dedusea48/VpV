#include <fstream>

using namespace std;

const int xo = 479; // начальные кординаты
const int yo = 279; // начальные кординаты
const int s = 100;  // маштаб

void frame(const long double a[], clock_t milliseconds) {
    HWND hwnd = GetConsoleWindow();
    HDC hdc = GetDC(hwnd);
    int r = 3;

// Рисуем
    for (int r1 = r; r1 != -r - 1; r1--)
        for (int r2 = -r; r2 != r + 1; r2++) {
            SetPixel(hdc, xo + (int) (a[0] * s) + r1, yo + (int) (a[1] * s) + r2, RGB(0, 128, 128));
            SetPixel(hdc, xo + (int) (a[2] * s) + r1, yo + (int) (a[3] * s) + r2, RGB(128, 0, 128));
            SetPixel(hdc, xo + (int) (a[4] * s) + r1, yo + (int) (a[5] * s) + r2, RGB(128, 128, 0));
        }

    clock_t time_end = clock() + milliseconds * CLOCKS_PER_SEC / 1000;
    for (; clock() <= time_end;) { time_end = time_end; }

// Стираем
    for (int r1 = r; r1 != -r - 1; r1--) {
        for (int r2 = -r; r2 != r + 1; r2++) {
            SetPixel(hdc, xo + (int) (a[0] * s) + r1, yo + (int) (a[1] * s) + r2, RGB(12, 12, 12));
            SetPixel(hdc, xo + (int) (a[2] * s) + r1, yo + (int) (a[3] * s) + r2, RGB(12, 12, 12));
            SetPixel(hdc, xo + (int) (a[4] * s) + r1, yo + (int) (a[5] * s) + r2, RGB(12, 12, 12));
        }
    }
    ReleaseDC(hwnd, hdc);
}

int main() {
    setlocale (LC_ALL, "RUS");
    system("mode con cols=120 lines=50"); // Задаём размеры консоли
    long double a[6];
    fstream F;
    F.open("D:\\data\\data2.txt");

    if (F){
        for (int i = 0;!F.eof();i++ ){ //когда достигнем конца файла, в этом случае F.eof() вернет истину.

            F >> a[0] >> a[1] >> a[2] >> a[3] >> a[4] >> a[5];//чтение очередного значения из потока F
            frame(a,15);
        }
        F.close(); //закрытие потока
    }
    else
        cout << "Fail not exist" << endl;  //если открытие файла прошло некорректно

    system("pause");
    return 0;
}