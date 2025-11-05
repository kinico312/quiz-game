#include <iostream>
#include "head.hpp"
#include <cstdlib>
#include <chrono>
#include <thread>

void game() {
	setlocale(LC_ALL, "RU");

	Tracking::init_default_user("Игрок 1");

	for (int i = 0; i <= 25; i++) { 
		print_questions_matrix();
		std::cout << "\n";
		char answer = display_question_with_answers();
		std::this_thread::sleep_for(std::chrono::seconds(3));
		system("cls");
	}


}