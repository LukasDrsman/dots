#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct Spec
{
	int L;
	int *L_spec;
	int *offset;
}
spec;

int idx(int l, int r, int c, spec s);
double sigma(double x);

void output(double *dest, double *input, double *W, spec s);
void train(double *W, spec s, double S[][s.L_spec[0]], double T[][s.L_spec[s.L - 1]], int X, double eta);

int main(void)
{
	int L;
	L = 3;

	int L_spec[] = {2, 8, 1};

	int total;
	total = 0;

	for (int i = 0; i < (L - 1); i++)
		total += L_spec[i] * L_spec[i + 1];

	double W[total];
	printf("total = %d\n", total);
	
	srand(time(NULL));
	for (int i = 0; i < total; i++)
		W[i] = (rand() % 1000000) / 1000000.0;

	int offset[L -  1];
	offset[0] = 0;

	for (int i = 1; i < (L - 1); i++)
		offset[i] = offset[i - 1] + L_spec[i - 1] * L_spec[i];

	// spec struct
	spec s;
	s.L = L;
	s.L_spec = L_spec;
	s.offset = offset;


	// print W tensor
	printf("W tensor =\n");
	for (int l = 0; l < (L - 1); l++)
	{
		int R, C;
		R = s.L_spec[l + 1];
		C = s.L_spec[l];

		printf("(l = %d)", l);
		for (int r = 0; r < R; r++)
		{
			printf("\n");
			for (int c = 0; c < C; c++)
			{
				printf("%f ", W[idx(l, r, c, s)]);
			}
		}
		printf("\n\n");
	}

	double S[][2] = {{2,3}, {1,5}, {6,8}};
	double T[][1] = {{1.0}, {0.0}, {1.0}};
	train(W, s, S, T, 3, 1);

}

// return W mat index 
int idx(int l, int r, int c, spec s)
{
	return c + s.L_spec[l] * r + s.offset[l];
}

double sigma(double x)
{
	return 1/(1 + exp(-x));
}

void output(double *dest, double *input, double *W, spec s)
{
	int offset1, offset2;
	offset1 = 0;

	for (int i = 0; i < s.L_spec[0]; i++) dest[i] = input[i];

	for (int l = 0; l < (s.L - 1); l++)
	{	
		offset2 = offset1 + s.L_spec[l];

		int R, C;
		R = s.L_spec[l + 1];
		C = s.L_spec[l];

		for (int r = 0; r < R; r++)   
		{
			double *curr, *prev;
			curr = dest;
			curr += offset2;

			prev = dest;
			prev += offset1;
			
			curr[r] = 0;
			for (int c = 0; c < C; c++)
			{
				curr[r] += W[idx(l, r, c, s)] * prev[c];
			}
			curr[r] = sigma(curr[r]);
		}

		offset1 = offset2;
	}
}


void train(double *W, spec s, double S[][s.L_spec[0]], double T[][s.L_spec[s.L - 1]], int X, double eta)
{
	int total;
	total = 0;
	for (int i = 0; i < s.L; i++) total += s.L_spec[i];
	
	int offset[s.L];
	offset[0] = 0;	

	for (int i = 1; i < s.L; i++)
		offset[i] = offset[i - 1] + s.L_spec[i - 1];


	do
	{
		double o[X][total], d[X][total];
		for (int x = 0; x < X; x++) output(o[x], S[x], W, s);

		// TODO: calculate error
		// TODO: calculate deltas
		
		// calculate deltas
		for (int x = 0; x < X; x++)
		{
			// output layers
			for (int i = 0; i < s.L_spec[s.L - 1]; i++)
			{
				double a;
				a = o[x][i + offset[s.L - 1]];
				printf("a = %f\n", a);
				d[x][i + offset[s.L - 1]] = 2.0/X * (a - T[x][i]) * a * (1 - a);
			}

			// TODO: internals
		}

		printf("d tensor =\n");
		for (int x = 0; x < X; x++)
		{
			printf("(x = %d)", x);
			for (int n = 0; n < s.L; n++)
			{
				printf("\n");
				for (int i = 0; i < s.L_spec[n]; i++)
				{
					printf("%f ", d[x][i + offset[n]]);
				}
			}
			printf("\n\n");
		}

	}
	while (0);
}

