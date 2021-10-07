/*Для функції f (x) = sin (x) + x побудувати перший інтерполяційний поліном Ньютона (для рівновіддалених вузлів).
Порівняти значення полінома в точках х = -6.7 -5.5 -3.2; зі значеннями точної функції, оцінити точність наближення.*/

/*For the function f (x) = sin (x) + x construct the first Newton's interpolation polynomial (for equidistant nodes).
Compare the value of the polynomial at the points x = -6.7 -5.5 -3.2; with the values of the exact function,
estimate the accuracy of the approximation.*/

#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

//function
double func(double x) {
	return sin(x) + x;
}

//output of vector elements for solved methods
void print(vector<double> vec, vector<double> x) {
	for (int i = 0; i < vec.size(); i++) {
		cout << "Solution in point: " << x[i] << " = " << vec[i] << endl;
	}
	cout << endl;
}

//output of vector elements
void print(vector<double> vec) {
	for (int i = 0; i < vec.size(); i++) {
		cout << vec[i] << " ";
	}
	cout << endl;
}

//output of error between the exact and found value
void eps(vector<double> vec, vector<double> x) {
	for (int i = 0; i < vec.size(); i++) {
		cout << "Precision in point: " << x[i] << " = " << setw(10) << abs(abs(vec[i]) - abs(func(x[i]))) << endl;
	}
}

double factorial(double number) {
	if (number == 0) {
		return 1;
	}
	if (number != 1) {
		return number * factorial(number - 1);
	}
	return number;
}

//newton polinomial with const step
void polinomNewtonWithStep(vector<double> x, vector<double> _x, vector<double> _y) {
	cout << endl << "______Answer method of Newton multipliers with step____________" << endl;
	vector<double> result;
	vector<double> temp;
	double size = _x.size();
	double** difor = new double* [size];
	double h = _x[1] - _x[0];
	for (int i = 0; i < size; i++) {
		difor[i] = new double[size + 1];
	}
	for (int i = 0; i < size; i++) {
		difor[0][i] = _y[i];										
	}
	for (int i = 0; i < size - 1; i++) {
		for (int j = 1; j < size - i; j++) {
			difor[i + 1][j - 1] = (difor[i][j] - difor[i][j - 1]);		// Write the finite difference
		}
	}
	for (int j = 0; j < size; j++) {
		temp.push_back(difor[j][0] / (pow(h, j) * factorial(j)));		//write coefficients 
	}
	for (int j = 0; j < size; j++) {
		delete[] difor[j];												//delete array
	}
	for (int i = 0; i < size - 1; i++) {
		double sum = temp[0];
		for (int j = 1; j < size; j++) {
			double mul = 1;
			for (int k = 0; k < j; k++) {
				mul *= (x[i] - _x[k]);
			}
			sum += temp[j] * mul;
		}
		result.push_back(sum);
	}
	print(result, x);
	eps(result, x);
}

int main()
{
	double xTemp;
	double yTemp;
	vector<double> x;
	vector<double> y;
	vector<double> _x;
	ifstream fileD("data.txt");
	while (!fileD.eof()) {
		fileD >> xTemp >> yTemp;
		x.push_back(xTemp);
		y.push_back(yTemp);
	}
	fileD.close();
	ifstream fileEx2("newtonPolinomialWithStep.txt");
	while (!fileEx2.eof()) {
		fileEx2 >> xTemp;
		_x.push_back(xTemp);
	}
	fileEx2.close();
	cout << endl << "x: ";
	print(x);
	cout << "y: ";
	print(y);
	cout << "Dots: ";
	print(_x);
	cout << endl;
	polinomNewtonWithStep(_x, x, y);
}