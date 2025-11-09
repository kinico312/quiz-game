#include <iostream>
#include "head.hpp"
#include <cstdlib>
#include <chrono>
#include <thread>


using namespace std;

void game() 
{
	setlocale(LC_ALL, "RU");

	string name;
	cout << "Введите имя игрока: ";
	cin >> name;
	create_user(name);

	for (int i = 0; i <= 25; i++) {
		print_questions_matrix();
		std::cout << "\n";

		int row, col;
		cout << "Введите строку и столбец вопроса (0-4 0-4): ";
		std::cin >> row >> col;

		auto result = display_question_with_answers(row, col);
		char answer = result.first;
		bool valid = result.second;
		if (!valid) 
		{
			cout << "Пропускаем вопрос...\n";
			this_thread::sleep_for(chrono::seconds(3));
			continue;
		}
		check_answer(answer, row, col);
		std::this_thread::sleep_for(std::chrono::seconds(3));
		system("cls");
	}
	system("cls");
	std::cout << "=========================================\n";
	std::cout << "ИГРА ОКОНЧЕНА!\n";
	std::cout << "Игрок '" << get_current_player_name() << "' набрал " << get_current_player_score() << " очков.\n";
	std::cout << "=========================================\n";

}

