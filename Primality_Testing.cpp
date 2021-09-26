#include <iostream>
#include <ctime>
#include <cmath>
#include <iomanip>
using namespace std;

bool Basic(int num);
bool Eratosthenes(int num);
bool Fermat(int num, int k);
bool MillerRabin(int num, int k);

int main() {
	bool prime;
	double inputNum = 0, k = 0;
	clock_t start, end;
	srand(time(NULL));
	cout << "Please enter a number: ";
	cin >> inputNum;
	while (int(inputNum) != inputNum || inputNum < 0) {
		cout << "You should enter a positive integer, please enter again: ";
		cin >> inputNum;
	}
	cout << "Please enter parameter k: ";
	cin >> k;
	while (int(k) != k || k <= 0) {
		cout << "You should enter an integer between 1~2147483647, please enter again: ";
		cin >> k;
	}
	cout << endl << left << setw(15) << "Algorithm" 
		<< left << setw(8) << "prime"
		<< left << setw(10) << "run-time" << endl;
	cout << "--------------------------------" << endl;
	
	start = clock();
	prime = Basic(int(inputNum));
	end = clock();

	cout << left << setw(15) << "Basic"
		<< left << setw(8) << boolalpha << prime
		<< left << setw(4) << end - start << "ms" << endl;

	if (inputNum < pow(2,31) - 1) {
		start = clock();
		prime = Eratosthenes(int(inputNum));
		end = clock();
		cout << left << setw(15) << "Eratosthenes"
			<< left << setw(8) << boolalpha << prime
			<< left << setw(4) << end - start << "ms" << endl;
	}
	else {
		cout << left << setw(15) << "Eratosthenes"
			<< left << setw(8) << "-----"
			<< setw(10) << "-----" << "*out of memory" << endl;
	}

	start = clock();
	prime = Fermat(int(inputNum), int(k));
	end = clock();
	cout << left << setw(15) << "Fermat"
		<< left << setw(8) << boolalpha << prime
		<< left << setw(4) << end - start << "ms" <<endl;

	start = clock();
	prime = MillerRabin(int(inputNum), int(k));
	end = clock();
	cout << left << setw(15) << "Miller-Rabin"
		<< left << setw(8) << boolalpha << prime
		<< left << setw(4) << end - start << "ms" << endl;

	system("pause");
	return 0;
}

bool Basic(int num) {
	for (int i = 2; i * i <= num; ++i) {
		if (num % i == 0) {
			return false;
		}
	}
	return true;
}

bool Eratosthenes(int num) {
	if (num == 0 || num == 1) {
		return false;
	}
	else {
		bool* numbers;
		numbers = new bool[num + 1];
		bool result;
		for (int i = 2; i < num; i++) {
			numbers[i] = true;
		}
		for (int i = 2; i < sqrt(num); i++) {
			if (numbers[i] == true) {
				for (int j = 2; j < num; j++) {
					if (i * j <= num) {
						numbers[i * j] = false;
					}
				}
			}
		}
		result = numbers[num];
		delete[] numbers;
		return result;
	}
}

bool Fermat(int num, int k) {
	for (int i = 0; i < k; i++) {
		int x = (rand() % (num - 1)) + 1;
		if (unsigned long(pow(x, num-1)) % num != 1) {
			return false;
		}
	}
	return true;
}

bool MillerRabin(int num, int k) {
	if (num < 2 || num % 2 == 0) {
		return false;
	}
	else {
		int D = num - 1;
		int R = 0;
		while (D % 2 == 0) {
			D /= 2;
			R++;
		}
		for (int i = 0; i < k; i++) {
			int A = (rand() % (num - 3)) + 2;
			int x = int(pow(A, D)) % num;
			for (int i = 1; i < R; i++) {
				x = int(pow(x, 2)) % num;
				if (x == 1) {
					return false;
				}
			}
			return false;
		}
		return true;
	}
}