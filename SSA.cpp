#include <cstdlib>
#include "BigInt_Extend.h"
#include <ctime>

#define Random_Bits	200
#define base_dec_bit	9

//using namespace std;

const unsigned_BigInt	unsigned_Two = 2;
const unsigned_BigInt	unsigned_Three = 3;
const unsigned_BigInt	unsigned_Five = 5;
const unsigned_BigInt	unsigned_Seven = 7;

bool is_even(const unsigned_BigInt &A)
{
	if (A.len == 0) return true;
	return ((A[0] & 1) == 0);
}

bool is_odd(const unsigned_BigInt &A)
{
	if (A.len == 0) return false;
	return ((A[0] & 1) != 0);
}

unsigned_BigInt Euclid_GCD(const unsigned_BigInt A, const unsigned_BigInt B)
{
	return (B.len == 0) ? A : Euclid_GCD(B, A % B);
}

unsigned_BigInt Get_Random(const int bits)
{
	unsigned_BigInt	Ret = 0;
	if (bits > 1) Ret = (rand() % 9 + 1);
	int i;
	for (i = 2; i + base_dec_bit - 1 < bits; i += base_dec_bit)
	{
		int k = 0;
		for (int j = 1; j <= base_dec_bit; ++ j)
			k = k * 10 + rand() % 10;
		Ret = Ret * base + k;
	}
	for (int j = i; j < bits; ++ j)
		Ret = Ret * 10 + (rand() % 10);

	return Ret;
}


unsigned_BigInt	Modular_Exponentiation(unsigned_BigInt A, unsigned_BigInt B, const unsigned_BigInt &N)
{
	unsigned_BigInt	Ret = 1;
	while (B.len != 0)
	{
		if ((B[0] & 1) != 0)
			Ret = (Ret * A) % N;
		A = (A * A) % N;
		shift_right(B);
	}
	return Ret;
}


signed_BigInt Jac(const unsigned_BigInt A, const unsigned_BigInt N)
{
	if (compare(A, unsigned_One) == 0) return One;
	if (compare(A, unsigned_Two) == 0)
	{
		unsigned_BigInt	temp = N % 8;
		if (compare(temp, unsigned_Three) == 0 || compare(temp, unsigned_Five) == 0)
			return Minus_One;
		else
			return One;
	}
	if (compare(A, N) > 0)
		return Jac(A % N, N);
	if (is_odd(A))
	{
		if (is_odd((A - 1) / 2) && is_odd((N - 1) / 2))
			return -Jac(N, A);
		else
			return Jac(N, A);
	}
	else
		return Jac(unsigned_Two, N) * Jac(A / 2, N);
}

unsigned_BigInt		N;
unsigned_BigInt		A;

unsigned_BigInt		left, right;

int reliability;

int main()
{
	printf("Reliability = ");
	scanf("%d", &reliability);
	printf("N = \n");
	N = unsigned_read();

	if (is_even(N))
	{
		printf("Composite!\n");
		return 0;
	}
	srand(time(NULL));

	while (reliability -- )
	{
		A = Get_Random(Random_Bits);
//		A.print(); printf("\n");

		A = A % (N - 1) + 1;

		unsigned_BigInt K = Euclid_GCD(N, A);

//		K.print(); printf("\n");

		if (compare(K, unsigned_One) != 0)
		{
			printf("Composite!\n");
			return 0;
		}

		signed_BigInt J = Jac(A, N);
		if (compare(J, Minus_One) == 0)
			left = N - 1;
		else
			left = 1;

//		left.print(); printf("\n");

		right = Modular_Exponentiation(A, (N - 1) / 2, N);

//		right.print(); printf("\n");


		if (compare(left, right) != 0)
		{
			printf("Composite!\n");
			return 0;
		}
	}
	printf("Prime with High Probability!\n");

	return 0;
}
