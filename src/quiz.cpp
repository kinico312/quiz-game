#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include "head.hpp"

std::map<std::pair<int, int>, Question> questions_dict;

std::map<std::pair<int, int>, Question> dictionary()
{
    int row = 0, col = 0;
    const int COLS_PER_ROW = 5;

    std::ifstream file("Questions.csv");
    std::map<std::pair<int, int>, Question> local_dict;

    if (!file.is_open()) {
        std::cout << "Не удалось открыть файл Questions.csv\n";
        return local_dict;
    }

    std::string line;
    int line_count = 0;
    int loaded_questions = 0;

    while (std::getline(file, line))
    {
        line_count++;

        if (line.empty()) {
            continue;
        }

        std::vector<std::string> cells;
        std::stringstream s(line);
        std::string cell;

        while (std::getline(s, cell, ';')) {
            cell.erase(0, cell.find_first_not_of(" \t"));
            cell.erase(cell.find_last_not_of(" \t") + 1);
            cells.push_back(cell);
        }

        if (cells.size() >= 8) {
            try {
                Question q;
                q.topic = cells[0];
                q.cost = std::stoi(cells[1]);
                q.text = cells[2];
                q.options = { cells[3], cells[4], cells[5], cells[6] };
                q.flag = true;

                // Просто берем значение из столбца - это уже A, B, C, D
                std::string correct_str = cells[7];

                // Удаляем запятую в конце если есть
                if (!correct_str.empty() && correct_str.back() == ',') {
                    correct_str.pop_back();
                }

                // Сохраняем как есть
                q.correct = correct_str;

                local_dict[{row, col}] = q;
                loaded_questions++;

                col++;
                if (col >= COLS_PER_ROW) {
                    col = 0;
                    row++;
                }

            }
            catch (const std::exception& e) {
                std::cout << "Ошибка в строке " << line_count << ": " << e.what() << "\n";
            }
        }
        else {
            std::cout << "Ошибка в строке " << line_count << ": только " << cells.size()
                << " колонок, ожидается 8\n";
        }
    }
    file.close();

    std::cout << "Загружено вопросов: " << loaded_questions << "\n";
    questions_dict = local_dict;
    return local_dict;
}