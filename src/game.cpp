#include <iostream>
#include "head.hpp"
#include <cstdlib>
#include <chrono>
#include <thread>
#include "multiple_players.hpp"

using namespace std;

void game()
{
	setlocale(LC_ALL, "RU");

	create_multiple_players_auto();

	for (int i = 0; i <= 25; i++) {
		print_questions_matrix();
		std::cout << "\n";

		int row, col;
		cout << "Введите строку и столбец вопроса (0-4 0-4): ";
		std::cin >> row >> col;
		handleQuestion(row, col);
		setQuestionFlag(row, col, false);
		
	}
	system("cls");
}



