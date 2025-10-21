#include <iostream>
#include <map>
#include <string>


// Функция для создание и инициализации словаря игроков

std::map<std::string, int> create_players_map(int number_of_players) {
    std::map<std::string, int> players; // Создаем пустую карту для хранения имен и очков игроков
    // Проходим циклом по количеству игроков

    for (int i = 1; i <= number_of_players; ++i) {
        std::string player_name;
        // Запрашиваем имя каждого игрока и добавляем в карту, где имя - ключ, а начальные очки - значение
        std::cout << "Введите имя игрока " << i << ": ";
        std::cin >> player_name;
        players[player_name] = 0;
    }

    return players; // Возвращаем карту игроков
}

//  Для проверки

int main() {

    setlocale(LC_ALL, "Rus"); // Подключаем русский язык
    int number_of_plaers; // Создаем переменную для колчиства игроков
    std::cout << "Введите количество игроков: ";
    std::cin >> number_of_plaers; // Запрашиваем количество игроков

  std::map<std::string, int> players = create_players_map(number_of_plaers); // Создаем карту

  for (const auto& pair : players) {
    std::cout << pair.first  << ": " << pair.second << std::endl; // Вывод карт для проверки
  }

  return 0;
}
