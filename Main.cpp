#include <stdlib.h>
#include <chrono>
#include <iostream>
#include <fstream>

#include <locale.h>
#include <direct.h>

#include <stdio.h>
#include <stdlib.h>

using namespace std;

extern void sort1(int* ar, int N);

extern bool checkSort(int* ar, int N);
// Проверка сортированного массива
// Возвращаемое значение:
//   true  - сортировка выполнена успешно;
//   false - сортировка выполнена с ошибками;

int cmpInt(const void* pi1, const void* pi2)
// Сравнение целых чисел
{
    return (*(int*)pi1 - *(int*)pi2);
}

const char* sortName[3] = {
    "Стандартная QSort",
    "2-х путевое простое слияние", //Названия твоих сортировок
    "Гномья сортировка"
};


class Sort1 {
public:
    int s = 0, p = 1, i = 0, j = 0, k = 0, l = 0, d = 0, q = 0, r = 0, N = 0,
        step = -1;
    bool end_prog = false;
    int* R;
    Sort1(int* array, int count) {
        R = array;
        N = count;
        step2();

        while (!end_prog) {
            switch (step) {
            case 2:
                step2();
                break;
            case 3:
                step3();
                break;
            case 4:
                step4_5();
                break;
            case 6:
                step6();
                break;
            case 7:
                step7();
                break;
            case 8:
                step8_9();
                break;
            case 10:
                step10();
                break;
            case 11:
                step11();
                break;
            case 12:
                step12();
                break;
            case 13:
                step13();
                break;
            default:
                std::cout << "x is undefined"
                    << "\n";
                break;
            }
        }
    }

    void step2() {
        //Начальные данные + создание массива
        if (s == 0) {
            i = 0;
            j = N - 1;
            k = N - 1;
            l = 2 * N;
            ///
            d = 1;
            q = p;
            r = p;
            ///
            step = 3;
        }
        else {
            i = N;
            j = (2 * N) - 1;
            k = 0 - 1;
            l = N;
            ///
            d = 1;
            q = p;
            r = p;
            ///
            step = 3;
        }
    }
    void step3() {
        if (R[i] > R[j]) {
            step = 8;
        }
        else {
            step = 4;
        }
    }
    void step4_5() {
        k = k + d;
        R[k] = R[i];
        i = i + 1;
        q = q - 1;
        if (q > 0) {
            step = 3;
        }
        else {
            step = 6;
        }
    }
    void step6() {
        k = k + d;
        if (k == l) {
            step = 13;
        }
        else {
            R[k] = R[j];
            step = 7;
        }
    }
    void step7() {
        j = j - 1;
        r = r - 1;
        if (r > 0) {
            step = 6;
        }
        else {
            step = 12;
        }
    }
    void step8_9() {
        k = k + d;
        R[k] = R[j];
        j = j - 1;
        r = r - 1;
        if (r > 0) {
            step = 3;
        }
        else {
            step = 10;
        }
    }
    void step10() {
        k = k + d;
        if (k == l) {
            step = 13;
        }
        else {
            R[k] = R[i];
            step = 11;
        }
    }
    void step11() {
        i = i + 1;
        q = q - 1;
        if (q > 0) {
            step = 10;
        }
        else {
            step = 12;
        }
    }
    void step12() {
        q = p;
        r = p;
        d = -d;
        int buf = k;
        k = l;
        l = buf;
        if (j - i < p) {
            step = 10;
        }
        else {
            step = 3;
        }
    }
    void step13() {
        //
        if (s == 0) {
            for (int i = 0; i < N; i++) R[i] = R[i + N + 1];
        }
        //

        p = p + p;
        if (p < N) {
            s = 1 - s;
            step = 2;
        }
        else {
            end_prog = true;
        }
    }


};

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Rus");
    char buf[128];
    cout << _getcwd(buf, 127) << endl;

    // проверить наличие командной строки
    if (argc == 1) {
        return 0;
    }


    // анализ командной строки:
    // получить имя исходного файла с данными
    const char* path = argv[1];
    int nSort = 0;    // номер функции сортировки
    if (argc == 3) {
        nSort = atoi(argv[2]);
        if (!(nSort >= 0 && nSort <= 2))
            nSort = 0;
    }
    ifstream f(path);

    // открыть исходный файл с данными для чтения
    // в случае ошибки вывести сообщение:
    //   "Ошибка открытия файла <path>"
    if (!f.is_open()) {
        cout << "Ошибка открытия файла: " << path << endl;
        return 1;
    }

    int nCount = 0;
    int ar[5000];

    // считать данные из файла (не более 5000 чисел)
    while (nCount < 5000 && f >> ar[nCount]) ++nCount;

    f.close();    // закрыть входной файл

    cout << endl;
    cout << "Из файла " << '"' << path << '"'
        << " считано " << nCount << " чисел" << endl;

    if (nCount <= 20) {
        cout << "Не отсортированный массив: ";
        // отладочная печать массива
        for (int i = 0; i < nCount; ++i) {
            cout << (i == 0 ? "" : ", ") << ar[i];
        }
        cout << endl;
    }


    cout << sortName[nSort] << endl << " " << endl;

    auto start = chrono::steady_clock::now();

    Sort1* obj = new Sort1(ar, nCount);

    auto end = chrono::steady_clock::now();
    long duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    // вывести сообщение:
    //   "Время сортировки <duration> мксек."
    cout << "Время сортировки " << duration << " мСек" << endl;

    if (nCount <= 20) {
        cout << "   Отсортированный массив: ";
        // отладочная печать отсортированного массива
        for (int i = 0; i < nCount; ++i) {
            cout << (i == 0 ? "" : ", ") << ar[i];
        }
        cout << endl;
    }

    // проверить правильность сортировки
    if (checkSort(ar, nCount)) {
        cout << "Отсортированно успешно";
    }
    else
    {
        cout << "Отсортированно неуспешно";
    }

    return 0;
}


bool checkSort(int* ar, int N)
// Проверка сортированного массива
// Возвращаемое значение:
//   true  - сортировка выполнена успешно;
//   false - сортировка выполнена с ошибками;
{
    bool bRet = true;
    for (int i = 0; i < N - 1; ++i) {
        if (ar[i] > ar[i + 1]) {
            bRet = false;
            break;
        }
    }
    return bRet;
}
