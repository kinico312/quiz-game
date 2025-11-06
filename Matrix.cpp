#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

void print_questions_matrix() {
    ifstream file("questions.csv");

    if (!file.is_open()) {
        cout << "Не удалось открыть файл!" << endl;
        return;
    }

    map<int, pair<string, vector<string>>> themes;
    string line;
    int currentNumber = 1;
    string currentTheme = "";

    while (getline(file, line)) {
        vector<string> row;
        string cell;
        size_t start = 0;
        size_t end = line.find(';');

        while (end != string::npos) {
            cell = line.substr(start, end - start);
            row.push_back(cell);
            start = end + 1;
            end = line.find(';', start);
        }
        cell = line.substr(start);
        row.push_back(cell);

        if (row.size() >= 3 && !row[0].empty()) {
            if (row[0] != currentTheme) {
                currentTheme = row[0];

                themes[currentNumber] = make_pair(currentTheme, vector<string>());
                currentNumber++;
            }

            if (!themes.empty()) {
                themes[currentNumber - 1].second.push_back(row[1]);
            }
        }
    }

    file.close();

    cout << "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄" << endl;
    cout << "█               ТЕМЫ И БАЛЛЫ                █" << endl;
    cout << "▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀" << endl;

    for (auto it = themes.begin(); it != themes.end(); it++) {
        cout << "▶ " << it->first << ". " << it->second.first << endl;
        cout << "  ";

        for (auto points_it = it->second.second.begin(); points_it != it->second.second.end(); points_it++) {
            cout << "▐ " << *points_it << " ▐ ";
        }
        cout << endl;

        if (next(it) != themes.end()) {
            cout << "  ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░" << endl;
        }
    }

    cout << "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄" << endl;
}