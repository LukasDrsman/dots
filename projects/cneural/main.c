#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define THIRD 0.3333333333333333

double sigma(double x);

double sigma(double x)
{
	return 1/(1 + exp(-x));
}

int main(int argc, char *argv[])
{
	int I, O, X;
	I = 3;
	O = 1;
	X = 4;

	if (argc < 2) return 1;

	double eta;
	eta = atof(argv[1]);

	double W[O][I];

	srand(time(NULL));
	for (int i = 0; i < O; i++)
		for (int j = 0; j < I; j++)
			W[i][j] = rand() % 1;

	double S[][3] = { {1, 2, 3}, {8, 1, 2}, {2, 3, 4}, {3, 5, 5} };
	double T[][1] = { {1}, {0}, {1}, {0} };

	while (1)
	{
		// calculate error and delta
		double E;
		E = 0;
		double delta[X][O];
		for (int x = 0; x < X; x++)
		{
			double o[O];
			// output for sample S[x]
			for (int i = 0; i < O; i++)
			{
				o[i] = 0;
				for (int j = 0; j < I; j++)
				{
					o[i] += W[i][j] * S[x][j];
				}
				o[i] = sigma(o[i]);
			}
		
			// calculate error and delta
			for (int i = 0; i < O; i++)
			{
				double a;
				a = (o[i] - T[x][i]);
				E += a * a;

				delta[x][i] = THIRD * 2 * a * o[i] * (1 - o[i]);
			}
		}
		E *= THIRD;
		printf("E = %f\n", E);

		if (E <= 0.000001) break;

		// gradient descent
		for (int i = 0; i < O; i++)
		{
			for (int j = 0; j < I; j++)
			{
				double dw;
				dw = 0;
				for (int x = 0; x < X; x++) dw += S[x][j] * delta[x][i];
				dw *= -eta;

				W[i][j] += dw;
			}
		}
	}

	printf("W =");
	for (int i = 0; i < O; i++)
	{
		printf("\n");
		for (int j = 0; j < I; j++) printf("%f ", W[i][j]);
	}
	printf("\n");
}
