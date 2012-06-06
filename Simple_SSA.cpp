#include <iostream>
#include <cstdlib>
#include <ctime>


using namespace std;

int GCD(int a, int b)
{
	return (b == 0) ? a : GCD(b, a % b);
}

int Jac(int a, int n)
{
	//cout << a << " " << n << endl;
	if (a == 1) return 1;
	if (a == 2)
	{
		if ((n & 7) == 3 || (n & 7) == 5)
			return -1;
		else
			return 1;
	}
	if (a > n) return Jac(a % n, n);
	if (a < n)
	{
		if ((a & 1) != 0)
		{
			int k = ((a - 1) >> 1) * ((n - 1) >> 1);
			return ((k & 1) == 0) ? Jac(n, a) : -Jac(n, a);
		}
		else
			return Jac(2, n) * Jac(a >> 1, n);
	}
}

int Exp_Mod(int a, int p, int n)
{
	int base = a;
	int ret = 1;
	while (p != 0)
	{
		if ((p & 1) != 0)
			ret = (ret * base) % n;
		p = p >> 1;
		base = (base * base) % n;
	}
	return ret;
}

int N;

int A;

const int reliability = 100;

int main()
{
	srand(time(NULL));
	cin >> N;	
	if ((N & 1) == 0)
	{
		cout << "Composite!" << endl;
		return 0;
	}
	for (int k = 0; k < reliability; ++ k)
	{
		int A = rand() % (N - 1) + 1;
		if (GCD(A, N) != 1)
		{
			cout << "Composite!" << endl;
			return 0;
		}

		int left = Jac(A, N);
		if (left < 0) left += N;

		int right = Exp_Mod(A, (N - 1) >> 1, N);

		if (left != right)
		{
			cout << "Composite!" << endl;
			return 0;
		}
	}
	cout << "Prime with High Probability!" << endl;
	return 0;
}
