// Predict-correct.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//Решение начально - краевой задачи с помощью схемы предиктор - корректора:
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <math.h>
#define pi 3.14159
#define double long double
using namespace std;

const int N = 200;
const int T = 400;
double t = 1.0 / T;
double h = 1.0 / N;
double e = 0.001;
double u[T + 1][N + 1];
double u1[N + 2];

FILE *w1, *pervyi, *vtoroi;

double f(double x) {
	return -3 * x + 1;
}
double F(double t, double x) {
	if ((t <= x) && (x <= 1 - 2 * t)) { return (x - 1.0 / 3) / (t - 1.0 / 3); }
	else {

		if (t > 1.0 / 3) {
			//if (t == 1) { cout << (1.0 / 3 - 1.0 / 2 * (t - 1.0 / 3)) << " " << x << "\n"; }
			if (x == 0) { return 1; }

			if ((x <= (1.0 / 3 - 1.0 / 2 * (t - 1.0 / 3)))) { return 1; }
			else {
				if ((x > (1.0 / 3 - 1.0 / 2 * (t - 1.0 / 3)))) { return -2; }
			}
		}
		else {
			if (x < t) { return 1; }
			if (x > 1 - 2 * t) { return -2; }
		}
	}

}
int main()
{
	cout << fixed;
	//cout.precision(10);
	pervyi = fopen("u_h.txt", "w");
	vtoroi = fopen("u.txt", "w");
	w1 = fopen("w1.plt", "w");
	for (int i = 0; i <= T; i++) {
		u[i][0] = 1;
		u[i][N] = -2;
	}
	for (int i = 0; i <= N; i++) {
		u[0][i] = f(i*h);
	}
	for (int n = 0; n < T; n++) {
		for (int i = 0; i < N; i++) {
			u1[i] = 1.0 / 2 * (u[n][i] + u[n][i + 1]) - t / (4 * h)*(u[n][i] + u[n][i + 1])*((u[n][i + 1] - u[n][i]));

		}
		for (int i = 1; i < N; i++) {
			u[n + 1][i] = u[n][i] - t * (u1[i] * u1[i] - u1[i - 1] * u1[i - 1]) / (2.0 * h);
		}

	}
	double maxosh = 0;
	for (int n = 0; n <= T / 3 - 1; n++) {
		for (int i = 0; i <= N; i++) {

			maxosh = max(maxosh, abs(u[n][i] - F(n*t, i*h)));
			//cout << n << " " << maxosh << "\n";
				//fprintf(pervyi, "%f %f %f\n", n*t, i*h, u[n][i]);

		//fprintf(vtoroi, "%f %f %f\n", n*t, i*h, F(n*t,i*h));
		}
		//fprintf(pervyi, "\n");
		//fprintf(vtoroi, "\n");
	}

	for (int i = 0; i <= N; i++) {
		fprintf(pervyi, "%f %f\n", i*h, u[T / 2][i]);
		
	}
	int N_new = 1000;
	double h_new = 1.0 / N_new;
	for (int i = 0; i <= N_new; i++) {
		fprintf(vtoroi, "%f %f\n", i*h_new, F(0.5, i*h_new));

	}
	
	//}
	cout <<"absolute error: "<< maxosh << "\n";
	//fprintf(w1, "set palette defined (-3 'blue', 0 'white', 1 'red')\nsplot 'f.txt' w pm3d");
	fprintf(w1, "set grid\nplot 'u_h.txt' with lines,'u.txt' with lines");
	fclose(w1);
	//system("start w1.plt");

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
