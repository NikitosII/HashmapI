#include <iostream>
#include "HashM.h"
#include <regex>
#include"Windows.h"

Hashmap::Hashmap() {
	size = 10;
	items = (Item**)calloc(size, sizeof(Item*));
}

// деструк
Hashmap::~Hashmap() {
	for (int i = 0; i < size; ++i) {
		Item* current = items[i];
		while (current != nullptr) {
			Item* next = current->next;
			delete current;
			current = next;
		}
	}
	free(items);
	items = nullptr;
}

// хэш-функция  
long Hashmap::hashFunc(std::string data) {
	long sum = 0;
	for (int i = 0; i < data.length(); i++) {
		sum += data[i];
	}
	return (sum % size);
}

// добавление 
void Hashmap::insertItem(std::string key, std::string data, std::string key2) {

	int index = hashFunc(data);
	Item* current = items[index];

	if (current == nullptr) { 
		items[index] = new Item(key, data, key2);
	}
	else if (current->data == data) { 
		current->key = key;
		return;
	}
	else {
		long i = 1;
		long newIndex = (index + i * i) % size; 
		while (items[newIndex] != nullptr) {
			i++;
			newIndex = (index + i * i) % size;
		}
		items[newIndex] = new Item(key, data, key2);
		return;
	}
}

// нахождение по полной data
std::string Hashmap::getItem(std::string data) {
	int index = hashFunc(data);
	Item* current = items[index];
	while (current != nullptr) {
		if (current->data == data) {
			return current->key;
		}
		current = current->next;
	}
	return " "; 
}

// удаление data
void Hashmap::deleteItem(std::string data) {
	long index = hashFunc(data);

	Item* prev = nullptr;
	Item* current = items[index];

	while (current != nullptr) {
		if (current->data == data) {
			if (prev == nullptr) { 
				items[index] = current->next;
			}
			else {
				prev->next = current->next;
			}
			delete current; 
			return;
		}
		prev = current;
		current = current->next;
	}
}

// вывод всего 
void Hashmap::displayHashmap() {
	for (int i = 0; i < size; i++) {
		Item* current = items[i];

		while (current != nullptr) {

			std::cout << current->key << " - " << current->data << " - " << current->key2 << std::endl;
			current = current->next;
		}
	}
}

// проверка data
bool Hashmap::isValidData(const std::string& data) {
	if (data.length() != 5 || !std::all_of(data.begin(), data.end(), ::isdigit)) {
		return false;
	}

	return true;
}

// проверка имя
bool Hashmap::isValidKey(const std::string& key) {

	for (char c : key) {
		if (std::isdigit(c)) {
			return false;
		}
	}
	return true;
}

// проверка даты 
bool Hashmap::isValidKey2(const std::string& key2) {
	std::regex pattern("^(\\d{2})\\.(\\d{2})\\.(\\d{4})$"); // формат даты 
	std::smatch matches; // объект используется для хранения результатов сопоставления регулярного выражения с key2

	if (!std::regex_match(key2, matches, pattern)) {
		return false;
	} // если совпадает, передаём в matches 

	int day = std::stoi(matches[1]);
	int month = std::stoi(matches[2]);
	int year = std::stoi(matches[3]);

	// Проверка на високосный 
	bool LeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);

	// номер месяца проверка 
	if (month < 1 || month > 12) {
		return false;
	}

	int days_month;
	switch (month) {
	case 2:
		days_month = LeapYear ? 29 : 28;
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		days_month = 30;
		break;
	default:
		days_month = 31;
	}
	// проверки на номер дня 
	if (day < 1 || day > days_month) {
		return false;
	}

	return true;
}


void Hashmap::menu() {

	int choice;
	int Level = 0;
	std::string key, data, key2;

	do {
		std::cout << "•1 Добавление записи \n";
		std::cout << "•2 Поиск\n";
		std::cout << "•3 Удаление записи\n";
		std::cout << "•4 Просмотр всех имеющихся записей\n";
		std::cout << "•5 Поиск по фрагменту\n";
		std::cout << "•0 Выход\n";
		std::cout << "Введите номер пункта(0-5): ";
		std::cin >> choice;

		switch (choice) {
		case 1: {
			if (Level >= size) {
				std::cout << "Хэш-таблица переполнена.\n";
				system("pause");
				system("cls");
			}
			else {

				do {
					std::cout << "Enter ФИО: ";
					std::cin.ignore();
					std::getline(std::cin, key);

				} while (!isValidKey(key));

				do {
					std::cout << "Enter номер договора (из 5 цифр): ";
					std::cin >> data;

				} while (!isValidData(data));

				do {
					std::cout << "Enter др (дд.мм.гггг): ";
					std::cin >> key2;

				} while (!isValidKey2(key2));


				// Если все данные корректны, вставляем 
				insertItem(key, data, key2);
				Level++;

			}
			system("cls");
			break;
		}
		case 2:

			std::cout << "Введите данные для поиска: ";
			std::cin >> data;
			std::cout << "Результат : " << getItem(data) << std::endl;
			system("pause");
			system("cls");
			break;

		case 3:

			std::cout << "Введите данные для удаления ( номер договора ): ";
			std::cin >> data;
			deleteItem(data);
			Level--;
			system("cls");
			break;

		case 4:

			displayHashmap();
			system("pause");
			system("cls");
			break;

		case 5: {

			std::string key3;
			std::cin >> key3;
			std::vector<std::string> results = search(key3);

			if (!results.empty()) {
				std::cout << "Найденные записи:\n";
				for (const std::string& result : results) {
					std::cout << result << std::endl;
				}
			}
			else {
				std::cout << "Ничего не найдено.\n";
			}
			system("pause");
			system("cls");
			break;
		}

		case 0:
			break;
		default:
			std::cout << "Неверный выбор. \n";
			system("pause");
			system("cls");
			break;
		}
	} while (choice != 0);
}


// вычисляет префиксные функции
std::vector<int> Hashmap::prefix_function(const std::string& pattern) {
	int n = pattern.length();
	std::vector<int> pi(n, 0);
	int k = 0;
	for (int i = 1; i < n; ++i) {
		while (k > 0 && pattern[k] != pattern[i]) {
			k = pi[k - 1];
		}
		if (pattern[k] == pattern[i]) {
			++k;
		}
		pi[i] = k;
	}
	return pi;
}

Поиск подстроки
std::vector<int> Hashmap::KMPSearch(const std::string& text, const std::string& pattern) {
	std::vector<int> positions;
	std::vector<int> pi = prefix_function(pattern);
	int n = text.length(); // Длина текста
	int m = pattern.length();// Длина шаблона
	int q = 0;
	for (int i = 0; i < n; ++i) {
		while (q > 0 && pattern[q] != text[i]) {
			q = pi[q - 1];  // Возвращаемся к началу шаблона для поиска следующего вхождения
		}
		if (pattern[q] == text[i]) { // Если символы совпадают, увеличиваем q
			++q;
		}
		if (q == m) { // Если весь шаблон совпал 
			positions.push_back(i - m + 1); // Добавляем позицию вхождения в вектор позиций 
			q = pi[q - 1]; 
		}
	}
	return positions;
}

// ищет все записи в хэш - таблице
std::vector<std::string> Hashmap::search(const std::string& fragment) {
	std::vector<std::string> results; // Вектор для хранения найденных
	for (int i = 0; i < size; ++i) {
		if (items[i] != nullptr) {
			std::vector<int> positions = KMPSearch(items[i]->data, fragment);
			if (!positions.empty()) { 
				results.push_back(items[i]->key);
			}
		}
	}
	return results;

}
