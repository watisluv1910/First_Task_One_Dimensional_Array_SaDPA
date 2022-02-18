#include <iostream>
#include <locale.h>
#include <string>

using namespace std;

void menuOutput();
bool isCorrect(int length);
void fillArray(string* array, int length);
void outputArray(string* array, int* indexesArray, int length, string option);
int* findIndex(string* array, int* indexesArray, int length, string option);
int n;
void insertion(string* array, int* indexesArray, int length, string option, int chosenIndex);
void removal(string* array, int* indexesArray, int length, string option, int chosenIndex);
string* resizeString(string* array, int actualArrayLength, int extensionsNumber);
int* resizeInt(int* indexesArray, int actualArrayLength, int extensionsNumber);


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

void fillArray(string* array, int length) {
	for (size_t i = 0; i < length; i++) {
		cin >> array[i];
	}
}

void outputArray(string* array, int* indexesArray, int length, string option) {
	if (option == "elements") {
		for (size_t i = 0; i < length; i++) {
			cout << i + 1 << ". " << array[i] << endl;
		}
	}
	else {
		for (size_t i = 0; i < length; i++) {
			cout << i + 1 << ". " << indexesArray[i] << endl;
		}
	}
}

int* findIndex(string* array, int* indexesArray, int length, string option) {
	n = 0;
	for (size_t i = 0; i < length; i++) {
		if (array[i].find("0") != string::npos && option == "with_zero" 
			|| array[i].find("0") == string::npos && option == "without_zero") {
			indexesArray = resizeInt(indexesArray, n, 1);
			indexesArray[n] = i;
			n++;
		}
	}
	return indexesArray;
}

// chosenIndex is necessery only with option "one"
void insertion(string* array, int* indexesArray, int length, string option, int chosenIndex = -1) {
	string addition;
	if (option == "one") {
		cin >> addition;
		if (chosenIndex == -1) {
			for (size_t i = length - 1; i >= indexesArray[0]; i--) {
				array[i + 1] = array[i];
			}
			array[indexesArray[0] + 1] = addition;
		}
		else {
			for (size_t i = length - 1; i >= chosenIndex; i--) {
				array[i + 1] = array[i];
			}
			array[chosenIndex + 1] = addition;
		}
	}
	else {
		for (size_t i = 0; i < n; i++) {
			cin >> addition;
			int j = length - 1;
			while (j >= indexesArray[i]) {
				array[j + 1] = array[j];
				j--;
			}
			array[indexesArray[i] + 1] = addition;
			length++;
			for (size_t k = i + 1; k < n; k++) {
				indexesArray[k]++;
			}
		}
	}
}

void removal(string* array, int* indexesArray, int length, string option, int chosenIndex = -1) {
	if (option == "one") {
		if (chosenIndex == -1) {
			for (size_t i = indexesArray[0]; i < length - 1; i++) {
				array[i] = array[i + 1];
			}
		}
		else {
			for (size_t i = chosenIndex; i < length - 1; i++) {
				array[i] = array[i + 1];
			}
		}
	}
	else {
		for (size_t i = 0; i < n; i++) {
			int j = indexesArray[i];
			while (j < length - 1) {
				array[j] = array[j + 1];
				j++;
			}
			length--;
			for (size_t k = i + 1; k < n; k++) {
				indexesArray[k]--;
			}
		}
	}
}

string* resizeString(string* array, int actualArrayLength, int extensionsNumber) {
	long newArrayLength = actualArrayLength + extensionsNumber;
	string* extendedArray = new string[newArrayLength];
	if (newArrayLength >= actualArrayLength) {
		for (int i = 0; i < actualArrayLength; i++) {
			extendedArray[i] = array[i];
		}
	}
	else {
		for (int i = 0; i < newArrayLength; i++) {
			extendedArray[i] = array[i];
		}
	}
	delete[] array;
	return extendedArray;
}

int* resizeInt(int* indexesArray, int actualArrayLength, int extensionsNumber) {
	long newArrayLength = actualArrayLength + extensionsNumber;
	int* extendedIndexesArray = new int[newArrayLength];
	for (int i = 0; i < actualArrayLength; i++) {
		extendedIndexesArray[i] = indexesArray[i];
	}
	delete[] indexesArray;
	return extendedIndexesArray;
}

int main() {
	setlocale(LC_ALL, "Russian");
	string* array = new string [0];
	int* indexesArray = new int [0];
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
				array = resizeString(array, 0, actualArrayLength); //extenction
				cout << "\nВведите элементы массива через Enter или Space:\n";
				fillArray(array, actualArrayLength);
			}
			else {
				cout << "\nКоличество элементов массива введено некорректно. "
					"Попробуйте ещё раз.\n";
			}
			break;
		}
		case 2: { // array output
			cout << "\nВывод элементов массива:\n";
			if (actualArrayLength <= 0) {
				cout << "\nМассив пуст.\n";
			}
			else {
				outputArray(array, indexesArray, actualArrayLength, "elements");
			}
			break;
		}
		case 3: { // find without 0
			indexesArray = findIndex(array, indexesArray, actualArrayLength, "with_zero");
			if (n == 1) {
				cout << "\nИндекс элемента массива, "
					"значение которого содержит цифру 0:\n"
					<< indexesArray[0] << endl;
			}
			else if (n > 1) {
				cout << "\nИндексы элементов массива, "
					"значение которых содержит цифру 0:\n";
				outputArray(array, indexesArray, n, "indexes");
			}
			else {
				cout << "\nВ массиве нет искомых элементов.\n";
			}
			break;
		}
		case 4: { // insert
			indexesArray = findIndex(array, indexesArray, actualArrayLength, "without_zero");
			if (n == 1) {
				cout << "\nИндекс элемента массива, значение "
					"которого не содержит цифру 0:\n"
					<< indexesArray[0] << endl;
				array = resizeString(array, actualArrayLength, 1);
				cout << "\nВведите число, которое хотите вставить в массив:\n";
				insertion(array, indexesArray, actualArrayLength, "one");
				actualArrayLength++;
				cout << "\nФинальный вид массива:\n";
				outputArray(array, indexesArray, actualArrayLength, "elements");
			}
			else if (n > 1) {
				cout << "\nИндексы элементов массива, значение "
					"которых не содержит цифру 0:\n";
				outputArray(array, indexesArray, n, "indexes");
				int option = 0;
				cout << "\nЕсли хотите выполнить вставку после всех "
					"найденных элементов, введите 1.\nЕсли хотите выполнить "
					"вставку после конкретного элемента, введите 2.\n";
				cin >> option;
				if (option == 1) {
					array = resizeString(array, actualArrayLength, n);
					insertion(array, indexesArray, actualArrayLength, "all");
					actualArrayLength += n;
					cout << "\nФинальный вид массива:\n";
					outputArray(array, indexesArray, actualArrayLength, "elements");
				}
				else if (option == 2) {
					cout << "\nВыберите номер индекса элемента, "
						"после которого хотите вставить новый:\n";
					int chosenIndex = -1;
					cin >> chosenIndex;
					array = resizeString(array, actualArrayLength, 1);
					insertion(array, indexesArray, actualArrayLength, "one", chosenIndex);
					actualArrayLength++;
					cout << "\nФинальный вид массива:\n";
					outputArray(array, indexesArray, actualArrayLength, "elements");
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
			indexesArray = findIndex(array, indexesArray, actualArrayLength, "with_zero");
			if (n == 1) {
				cout << "\nИндекс элемента массива, значение "
					"которого содержит цифру 0:\n"
					<< indexesArray[0] << endl;
				cout << "\nЭлемент массива, который будет удалён:\n"
					<< array[indexesArray[0]] << endl;
				removal(array, indexesArray, actualArrayLength, "one");
				array = resizeString(array, actualArrayLength, -1);
				actualArrayLength--;
				cout << "\nФинальный вид массива:\n";
				outputArray(array, indexesArray, actualArrayLength, "elements");
			}
			else if (n > 1) {
				cout << "\nИндексы элементов массива, значение "
					"которых содержит цифру 0:\n";
				outputArray(array, indexesArray, n, "indexes");
				int option = 0;
				cout << "\nЕсли хотите выполнить удаление всех "
					"найденных элементов, введите 1.\nЕсли хотите выполнить "
					"удаление конкретного элемента, введите 2.\nВаш выбор:\n";
				cin >> option;
				if (option == 1) {
					removal(array, indexesArray, actualArrayLength, "all");
					array = resizeString(array, actualArrayLength, (-1)*n);
					actualArrayLength -= n;
					cout << "\nФинальный вид массива:\n";
					outputArray(array, indexesArray, actualArrayLength, "elements");
				}
				else if (option == 2) {
					cout << "\nВыберите индекс элемента, который хотите удалить:\n";
					int chosenIndex = -1;
					cin >> chosenIndex;
					removal(array, indexesArray, actualArrayLength, "one", chosenIndex);
					array = resizeString(array, actualArrayLength, -1);
					actualArrayLength--;
					cout << "\nФинальный вид массива:\n";
					outputArray(array, indexesArray, actualArrayLength, "elements");
				}
				else {
					cout << "\nНекорректный ввод. Попробуйте ещё раз\n";
					break;
				}
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