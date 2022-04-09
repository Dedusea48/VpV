#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

struct tel{
    long double mas, x, y, vx, vy;
};

long double length(tel t1, tel t2){ //находим длину между двумя телами
    return (sqrt( ( t1.x - t2.x ) * ( t1.x - t2.x ) + ( t1.y - t2.y ) * ( t1.y - t2.y ))) ;
}

long double p1 = 0.416822; // начальные условия взятые с сайта http://three-body.ipb.ac.rs/sol.php?id=5

long double p2 = 0.330333; // начальные условия взятые с сайта http://three-body.ipb.ac.rs/sol.php?id=5
int main() {
    long double IP[3][2] = { // начальныые кординаты
            {-1.0, 0.0},
            {1.0, 0.0},
            {0.0, 0.0}

    };
    long double IV[3][2] = { // начальная скорость
            {p1,p2},
            {p1,p2},
            {-2*p1,-2*p2}
    };
    const long double G = 1; // гравитационная постоянная
    tel t[4];
    // Объявляем тела
    t[1] = {1,IP[0][0] ,IP[0][1], IV[0][0], -IV[0][1]};
    t[2] = {1,IP[1][0] ,IP[1][1], IV[1][0], -IV[1][1]};
    t[3] = {1,IP[2][0], IP[2][1], IV[2][0], -IV[2][1]};

    ofstream f;          // поток для записи
    f.open("D:\\data\\data9.txt"); // окрываем файл для записи
    long double l12, l23, l31, F12, F23, F31, a1y, a2y, a3y, a1x, a2x, a3x, dt = pow(10, -8);

    for ( int j = 0; j != 20000 ; j++){
        f << t[1].x << " " << t[1].y << " " << t[2].x << " " << t[2].y << " " << t[3].x << " " << t[3].y << endl; // считываем
        cout << j << endl;
        for (int i = 0; i * dt < 0.05; i++) {

            //Посчитаем растояние между телами // Это упростит последующие вычисления
            l12 = length(t[1], t[2]);
            l23 = length(t[2], t[3]);
            l31 = length(t[3], t[1]);

            //Посчитаем силы

            F12 = (G * t[1].mas * t[2].mas) / (l12 * l12);
            F23 = (G * t[2].mas * t[3].mas) / (l23 * l23);
            F31 = (G * t[3].mas * t[1].mas) / (l31 * l31);

            //Посчитаем проекции ускорений
            a1x = ((t[2].x - t[1].x) / l12 * F12 + (t[3].x - t[1].x) / l31 * F31) / t[1].mas;
            a2x = ((t[1].x - t[2].x) / l12 * F12 + (t[3].x - t[2].x) / l23 * F23) / t[2].mas;
            a3x = ((t[1].x - t[3].x) / l31 * F31 + (t[2].x - t[3].x) / l23 * F23) / t[3].mas;

            a1y = ((t[2].y - t[1].y) / l12 * F12 + (t[3].y - t[1].y) / l31 * F31) / t[1].mas;
            a2y = ((t[1].y - t[2].y) / l12 * F12 + (t[3].y - t[2].y) / l23 * F23) / t[2].mas;
            a3y = ((t[1].y - t[3].y) / l31 * F31 + (t[2].y - t[3].y) / l23 * F23) / t[3].mas;

            //Изменим кординаты тел
            t[1].x += t[1].vx * dt + a1x * dt * dt / 2;
            t[2].x += t[2].vx * dt + a2x * dt * dt / 2;
            t[3].x += t[3].vx * dt + a3x * dt * dt / 2;

            t[1].y += t[1].vy * dt + a1y * dt * dt / 2;
            t[2].y += t[2].vy * dt + a2y * dt * dt / 2;
            t[3].y += t[3].vy * dt + a3y * dt * dt / 2;

            //Изменим значения проекциё скоростей
            t[1].vx += a1x * dt;
            t[2].vx += a2x * dt;
            t[3].vx += a3x * dt;

            t[1].vy += a1y * dt;
            t[2].vy += a2y * dt;
            t[3].vy += a3y * dt;

            if (l23 == 0 || l12 == 0 || l31 == 0) {
                cout << "BOOM";
                return 0;
            }
        }
    }
    f.close();
    return 0;
}