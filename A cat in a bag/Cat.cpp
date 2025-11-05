#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <string>
#include "Header.h"

using namespace std;

// Матрица 6x6, где true - "кот в мешке", false - обычная ячейка.  Инициализируется вся false.
bool catMatrix[6][6] = { false };

//Функция, генерирующая позицию "кота в мешке" случайным образом.
void generateCatPosition() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1, 5); // Диапазон от 1 до 5 (исключая первые строку и столбец).

    int row = distrib(gen);
    int col = distrib(gen);

    catMatrix[row][col] = true; // Устанавливаем случайную ячейку как "кота в мешке".
}

//Функция, определяющая, является ли ячейка "котом в мешке"
bool isCatInBag(int row, int col) {
    return catMatrix[row][col];
}

pair<int, int> chooseQuestion() {
    int row, col;
    cout << "Введите номер строки (1-5): ";
    cin >> row;
    cout << "Введите номер столбца (1-5): ";
    cin >> col;

    if (isCatInBag(row, col)) {
        cout << "Кот в мешке!" << endl;
    }

    cout << "Кому передадите ход (сейчас ходит " << g_Current_Player() << ")?" << endl;

    string next_Player;
    do {
        cout << "Введите имя игрока которому передаете ход: ";
        cin >> next_Player;
    } while (!playerExists(next_Player) || nextPlayer == g_Current_Player());

    cout << "Теперь ходит " << next_Player << "!" << endl;
    set_Current_Player(next_Player);

    return make_pair(row, col);
}
