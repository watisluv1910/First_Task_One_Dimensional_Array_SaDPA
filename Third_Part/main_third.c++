#include <iostream>
#include <locale.h>
#include <string>
#include <vector>

using namespace std;

void menuOutput();
bool isCorrect(int length);
void fillArray(vector<string>& array);
bool isInIndexesArray(vector<int>& indexesArray, int chosenIndex);
void outputArray(vector<string>& array, vector<int>& indexesArray, string option);
void findIndex(vector<string>& array, vector<int>& indexesArray, string option);
void insertion(vector<string>& array, vector<int>& indexesArray, string option, int chosenIndex);
void removal(vector<string>& array, vector<int>& indexesArray, string option, int chosenIndex);

void menuOutput() {
	cout << "Практическое задание №1 ИКБО-03-21 Насевич В.В.\n"
		"Вариант 19.\n\nМеню:\n"
		"1)Введите 1, чтобы заполнить массив.\n"
		"2)Введите 2, чтобы вывести массив.\n"
		"3)Введите 3, чтобы найти индекс элемента массива, "
		"значение которого содержит цифру 0.\n"
		"4)Введите 4, чтобы вставить новый элемент в массив после элемента, "
		"значение которого не содержит цифру 0\n"
		"5)Введите 5, чтобы удалить элементы массива, "
		"значение которого содержит цифру 0.\n\n"
		"Введите 0 для выхода из программы.\n";
}

bool isCorrect(int length) {
	return (0 < length && length <= numeric_limits<int>::max()) ? true : false;
}

void fillArray(vector<string> &array) {
	for (auto& element: array) {
		cin >> element;
	}
}

bool isInIndexesArray(vector<int>& indexesArray, int chosenIndex) {
	for (auto& element: indexesArray) {
		if (element == chosenIndex) {
			return true;
		}
	}
	return false;
}

void outputArray(vector<string>& array, vector<int>& indexesArray, string option) {
	if (option == "elements") {
		for (size_t i = 0; i < array.size(); i++) {
			cout << i + 1 << ". " << array.at(i) << endl;
		}
	}
	else {
		for (size_t i = 0; i < indexesArray.size(); i++) {
			cout << i + 1 << ". " << indexesArray.at(i) << endl;
		}
	}
}

void findIndex(vector<string>& array, vector<int>& indexesArray, string option) {
	indexesArray.clear();
	for (size_t i = 0; i < array.size(); i++) {
		if (array[i].find("0") != string::npos && option == "with_zero"
			|| array[i].find("0") == string::npos && option == "without_zero") {
			indexesArray.push_back(i);
		}
	}
}

// chosenIndex is necessery only with option "one"
void insertion(vector<string>& array, vector<int>& indexesArray, string option, int chosenIndex = -1) {
	string addition;
	if (option == "one") {
		cin >> addition;
		if (chosenIndex == -1) {
			/*array.push_back(addition);
			swap(array.at(indexesArray.at(0) + 1), array.back());*/
			array.insert(array.begin() + indexesArray.at(0) + 1, addition);
		}
		else {
			array.insert(array.begin() + chosenIndex + 1, addition);
		}
	}
	else {
		for (size_t i = 0; i < indexesArray.size(); i++) {
			cin >> addition;
			array.insert(array.begin() + indexesArray.at(i) + 1, addition);;
			for (size_t k = i + 1; k < indexesArray.size(); k++) {
				indexesArray.at(k)++;
			}
		}
	}
}

void removal(vector<string>& array, vector<int>& indexesArray, string option, int chosenIndex = -1) {
	if (option == "one") {
		if (chosenIndex == -1) {
			array.erase(array.begin() + indexesArray.at(0));
		}
		else {
			array.erase(array.begin() + chosenIndex);
		}
	}
	else {
		for (size_t i = 0; i < indexesArray.size(); i++) {
			array.erase(array.begin() + indexesArray.at(i));
			for (size_t k = i + 1; k < indexesArray.size(); k++) {
				indexesArray.at(k)--;
			}
		}
	}
}

int main() {
	setlocale(LC_ALL, "Russian");
	vector<string> array;
	vector<int> indexesArray;
	int actualArrayLength = 0, chooseTask = 0;
	menuOutput();
	cout << "\nВаш выбор:\n";
	cin >> chooseTask;
	while (chooseTask != 0) {
		switch (chooseTask) {
		case 1: { // filling the array
			cout << "\nВведите количество элементов в массиве "
				"*Не меньше 1 (единицы):\n";
			cin >> actualArrayLength;
			if (isCorrect(actualArrayLength)) {
				array.resize(actualArrayLength);
				cout << "\nВведите элементы массива через Enter или Space:\n";
				fillArray(array);
			}
			else {
				cout << "\nКоличество элементов массива введено некорректно. "
					"Попробуйте ещё раз.\n";
			}
			break;
		}
		case 2: { // array output
			cout << "\nВывод элементов массива:\n";
			if (array.size() <= 0) {
				cout << "\nМассив пуст.\n";
			}
			else {
				outputArray(array, indexesArray, "elements");
			}
			break;
		}
		case 3: { // find without 0
			findIndex(array, indexesArray, "with_zero");
			if (indexesArray.size() == 1) {
				cout << "\nИндекс элемента массива, "
					"значение которого содержит цифру 0:\n"
					<< indexesArray[0] << endl;
			}
			else if (indexesArray.size() > 1) {
				cout << "\nИндексы элементов массива, "
					"значение которых содержит цифру 0:\n";
				outputArray(array, indexesArray, "indexes");
			}
			else {
				cout << "\nВ массиве нет искомых элементов.\n";
			}
			break;
		}
		case 4: { // insert
			findIndex(array, indexesArray, "without_zero");
			if (indexesArray.size() == 1) {
				cout << "\nИндекс элемента массива, значение "
					"которого не содержит цифру 0:\n"
					<< indexesArray.at(0) << endl;
				cout << "\nВведите число, которое хотите вставить в массив:\n";
				insertion(array, indexesArray, "one");
				cout << "\nФинальный вид массива:\n";
				outputArray(array, indexesArray, "elements");
			}
			else if (indexesArray.size() > 1) {
				cout << "\nИндексы элементов массива, значение "
					"которых не содержит цифру 0:\n";
				outputArray(array, indexesArray, "indexes");
				int option = 0;
				cout << "\nЕсли хотите выполнить вставку после всех "
					"найденных элементов, введите 1.\nЕсли хотите выполнить "
					"вставку после конкретного элемента, введите 2.\n";
				cin >> option;
				if (option == 1) {
					cout << "\nВведите числа, которое хотите вставить в массив:\n";
					insertion(array, indexesArray, "all");
					cout << "\nФинальный вид массива:\n";
					outputArray(array, indexesArray, "elements");
				}
				else if (option == 2) {
					cout << "\nВыберите номер индекса элемента, "
						"после которого хотите вставить новый:\n";
					int chosenIndex = -1;
					cin >> chosenIndex;
					cout << "\nВведите число, которое хотите вставить в массив:\n";
					insertion(array, indexesArray, "one", chosenIndex);
					cout << "\nФинальный вид массива:\n";
					outputArray(array, indexesArray, "elements");
				}
				else {
					cout << "\nНекорректный ввод. Попробуйте ещё раз.\n";
					break;
				}
			}
			else {
				cout << "\nВ массиве нет искомых элементов.\n";
			}
			break;
		}
		case 5: { // delete with 0
			findIndex(array, indexesArray, "with_zero");
			if (indexesArray.size() == 1) {
				cout << "\nИндекс элемента массива, значение "
					"которого содержит цифру 0:\n"
					<< indexesArray.at(0) << endl;
				cout << "\nЭлемент массива, который будет удалён:\n"
					<< array.at(indexesArray.at(0)) << endl;
				removal(array, indexesArray, "one");
				cout << "\nФинальный вид массива:\n";
				outputArray(array, indexesArray, "elements");
			}
			else if (indexesArray.size() > 1) {
				cout << "\nИндексы элементов массива, значение "
					"которых содержит цифру 0:\n";
				outputArray(array, indexesArray, "indexes");
				int option = 0;
				cout << "\nЕсли хотите выполнить удаление всех "
					"найденных элементов, введите 1.\nЕсли хотите выполнить "
					"удаление конкретного элемента, введите 2.\nВаш выбор:\n";
				cin >> option;
				if (option == 1) {
					removal(array, indexesArray, "all");
				}
				else if (option == 2) {
					cout << "\nВыберите индекс элемента, который хотите удалить:\n";
					int chosenIndex = -1;
					cin >> chosenIndex;
					if (isInIndexesArray(indexesArray, chosenIndex)) {
						removal(array, indexesArray, "one", chosenIndex);
					}
					else {
						cout << "\nНекорректный ввод. Попробуйте ещё раз.\n";
						break;
					}
				}
				else {
					cout << "\nНекорректный ввод. Попробуйте ещё раз.\n";
					break;
				}
				cout << "\nФинальный вид массива:\n";
				outputArray(array, indexesArray, "elements");
			}
			else {
				cout << "\nВ массиве нет искомых элементов.\n";
			}
			break;
		}
		default:
			cout << "\nНомер задачи введён некорректно. Попробуйте ещё раз\n";
			break;
		}
		cout << endl;
		system("pause");
		system("cls");
		menuOutput();
		cout << "\nВаш следующий выбор:\n";
		cin >> chooseTask;
	}
	return 0;
}