#include "BigInt_Extend.h"

/****************************************************************
 * Unsigned Big Integer						*
 ****************************************************************/

const unsigned_BigInt	unsigned_Zero = 0;
const unsigned_BigInt	unsigned_One = 1;
const signed_BigInt	Zero = 0;
const signed_BigInt	One = 1;
const signed_BigInt	Minus_One = -1;


Dec_BigInt operator + (const Dec_BigInt &A, const Dec_BigInt &B)
{
	Dec_BigInt R;
	int i;
	int Carry = 0;
	for (i = 0; i < A.len || i < B.len || Carry > 0; ++ i)
	{
		if (i < A.len) Carry += A[i];
		if (i < B.len) Carry += B[i];
		R[i] = Carry % base_dec;
		Carry /= base_dec;
	}
	R.len = i;
	return R;	
}

Dec_BigInt operator * (const Dec_BigInt &A, const int B)
{
	int i;
	if (B == 0) return 0;
	Dec_BigInt R;
	long long Carry = 0;
	for (i = 0; i < A.len || Carry > 0; ++ i)
	{
		if (i < A.len) Carry += (long long)(A[i]) * B;
		R[i] = Carry % base_dec;
		Carry /= base_dec;
	}
	R.len = i;
	return R;
}





int compare(const unsigned_BigInt &A, const unsigned_BigInt &B)
{
	if (A.len != B.len) return A.len > B.len ? 1 : -1;
	int i;
	for (i = A.len - 1; i >= 0 && A[i] == B[i]; -- i);
	if (i < 0) return 0;
	return A[i] > B[i] ? 1 : -1;
}


void shift_right_base(unsigned_BigInt &A)
{
	if (A.len == 0) return;
	for (int i = 0; i < A.len - 1; ++ i)
		A[i] = A[i + 1];
	-- A.len;
}

void shift_left_base(unsigned_BigInt &A)
{
	if (A.len == 0) return;
	for (int i = A.len; i > 0; -- i)
		A[i] = A[i - 1];
	A[0] = 0;
	++ A.len;
}

void shift_right(unsigned_BigInt &A)
{
	if (A.len == 0) return;
	for (int i = 0; i < A.len - 1; ++ i)
	{
		A[i] = (A[i] >> 1);
		if ((A[i + 1] & 1) == 1)
			A[i] = A[i] | __base;
	}
	A[A.len - 1] = A[A.len - 1] >> 1;
	if (A[A.len - 1] == 0) -- A.len;
}

void shift_left(unsigned_BigInt &A)
{
	if (A.len == 0) return;
	int k = A.len;
	if ((A[A.len - 1] & __base) != 0)
		A[A.len ++] = 1;
	for (int i = k - 1; i > 0; -- i)
	{
		A[i] = (A[i] << 1) & base_mod;
		if ((A[i - 1] & __base) != 0)
			++ A[i];
	}
	A[0] = (A[0] << 1) & base_mod;
}






unsigned_BigInt operator + (const unsigned_BigInt &A, const unsigned_BigInt &B)
{
	unsigned_BigInt R;
	int i;
	int Carry = 0;
	for (i = 0; i < A.len || i < B.len || Carry > 0; ++ i)
	{
		if (i < A.len) Carry += A[i];
		if (i < B.len) Carry += B[i];
		R[i] = Carry & base_mod;
		Carry >>= base_bit;
	}
	R.len = i;
	return R;
	
}

unsigned_BigInt operator - (const unsigned_BigInt &A, const unsigned_BigInt &B)
{
	unsigned_BigInt R;
	int Carry = 0;
	R.len = A.len;
	for (int i = 0; i < R.len; ++ i)
	{
		R[i] = A[i] - Carry;
		if (i < B.len) R[i] -= B[i];
		if (R[i] < 0) Carry = 1, R[i] += base;
		else Carry = 0;
	}
	while (R.len > 0 && R[R.len - 1] == 0) -- R.len;
	return R;
}

unsigned_BigInt operator * (const unsigned_BigInt &A, const int B)
{
	int i;
	if (B == 0) return 0;
	unsigned_BigInt R;
	long long Carry = 0;
	for (i = 0; i < A.len || Carry > 0; ++ i)
	{
		if (i < A.len) Carry += (long long)(A[i]) * B;
		R[i] = Carry & base_mod;
		Carry >>= base_bit;
	}
	R.len = i;
	return R;
}

unsigned_BigInt operator * (const unsigned_BigInt &A, const unsigned_BigInt &B)
{
	if (B.len == 0) return 0;
	unsigned_BigInt R;
	for (int i = 0; i < A.len; ++ i)
	{
		long long Carry = 0;
		for (int j = 0; j < B.len || Carry > 0; ++ j)
		{
			if (j < B.len) Carry += (long long)(A[i]) * B[j];
			if (i + j < R.len) Carry += R[i + j];
			if (i + j >= R.len) R[R.len ++] = Carry & base_mod;
			else R[i + j] = Carry & base_mod;
			Carry >>= base_bit;
		}
	}
	return R;
}



unsigned_BigInt operator / (const unsigned_BigInt &A, const int B)
{

	unsigned_BigInt R;
	long long C = 0;
	for (int i = A.len - 1; i >= 0; -- i)
	{
		C = (C << base_bit) + A[i];
		R[i] = C / B;
		C %= B;
	}
	R.len = A.len;
	while (R.len > 0 && R[R.len - 1] == 0) -- R.len;
	return R;

}

unsigned_BigInt operator % (const unsigned_BigInt &A, const int B)
{
	long long C = 0;
	for (int i = A.len - 1; i >= 0; -- i)
	{
		C = (C << base_bit) + A[i];
		C %= B;
	}
	return C;
}


/*
 * Function multiply(x, y):
 * 
 * Input: Two n-bit integers x and y, where y ≥ 0
 * Output: Their product
 *
 * if y = 0: return 0
 * z = multiply(x, floor(y / 2))
 * if y is even:
 *	return 2 * z
 * else:
 *	return x + 2 * z
 *
 */


unsigned_BigInt multiply(const unsigned_BigInt &A, unsigned_BigInt B)
{
	static bool flag[exponentiation_size];  //odd ---> true, even ---> false
	static int top;
	static unsigned_BigInt Z;
	
	Z = B;
	for (top = 0; compare(Z, unsigned_Zero) != 0; ++ top)
	{
		flag[top] = ((Z[0] & 1) == 1);
		shift_right(Z);
	}

	Z = unsigned_Zero;
	for (int i = top - 1; i >= 0; -- i)
	{
		shift_left(Z);
		if (flag[i])
			Z = Z + A;
	}
	return Z;
}

/*
 *
 * Function divide(x, y):
 *
 * Input: Two n-bit integers x and y, where y ≥ 1
 * Output: The quotient and remainder of x divided by y
 *
 * if x = 0: return (q, r) = (0, 0)
 * (q, r) = divide(floor(x / 2), y)
 * q = 2 * q, r = 2 * r
 * if x is odd: r = r + 1
 * if r ≥ y: r = r - y, q = q + 1
 * return (q, r)
 *
 */



void divide(const unsigned_BigInt &A, const unsigned_BigInt &B, unsigned_BigInt &Q, unsigned_BigInt &R)
{
	static bool flag[exponentiation_size];  //odd ---> true, even ---> false
	static int top;
	static unsigned_BigInt temp_divide;
	
	temp_divide = A;
	for (top = 0; compare(temp_divide, B) >= 0; ++ top)
	{
		flag[top] = ((temp_divide[0] & 1) == 1);
		shift_right(temp_divide);
	}
	
	Q = 0; R = temp_divide;
	
	for (int i = top - 1; i >= 0; -- i)
	{
		shift_left(Q); shift_left(R);
		if (flag[i])
			R = R + 1;
		if (compare(R, B) >= 0)
		{
			R = R - B;
			Q = Q + 1;
		}
	}
}


unsigned_BigInt operator / (const unsigned_BigInt &A, const unsigned_BigInt &B)
{
	if (compare(A, B) < 0) return 0;

	unsigned_BigInt R, Carry = 0;
	int left, right, mid;
	for (int i = A.len - 1; i >= 0; -- i)
	{
		shift_left_base(Carry);
		Carry = Carry + A[i];

		left = 0;
		right = base;
		while (left + 1 < right)
		{
			mid = (left + right) >> 1;
			if (compare(B * mid , Carry) <= 0)
				left = mid;
			else
				right = mid;
		}
		R[i] = left;
		Carry = Carry - B * left;
	}
	R.len = A.len;
	while (R.len > 0 && R[R.len - 1] == 0) -- R.len;
	return R;

}

unsigned_BigInt operator % (const unsigned_BigInt &A, const unsigned_BigInt &B)
{
	if (compare(A, B) < 0) return A;

	unsigned_BigInt Carry = 0;
	int left, right, mid;
	for (int i = A.len - 1; i >= 0; -- i)
	{
		shift_left_base(Carry);
		Carry = Carry + A[i];
		
		left = 0;
		right = base;
		while (left + 1 < right)
		{
			mid = (left + right) >> 1;
			if (compare(B * mid, Carry) <= 0)
				left = mid;
			else
				right = mid;
		}
		Carry = Carry - B * left;
	}
	return Carry;

}

unsigned_BigInt unsigned_read()
{
	unsigned_BigInt ret = 0;
	char ch[read_size];
	scanf("%s", ch);
	int len = strlen(ch);
	for (int i = 0; i < len; ++ i)
		ret = ret * 10 + (int(ch[i]) - int('0'));
	return ret;
}
	








/****************************************************************
 * Signed Big Integer						*
 ****************************************************************/



int compare(const signed_BigInt &A, const signed_BigInt &B)
{
	if (A.sign > B.sign) return 1;
	if (A.sign < B.sign) return -1;
	return compare(A.data, B.data);
}

signed_BigInt operator + (const signed_BigInt &A, const signed_BigInt &B)
{
	if (A.sign == 0) return B;
	if (B.sign == 0) return A;
	signed_BigInt R;
	if (A.sign * B.sign == 1)
	{
		R.data = A.data + B.data;
		R.sign = A.sign;
	}
	else if (A.sign == 1)
	{
		int k = compare(A.data, B.data);
		if (k == 1)
		{
			R.sign = 1;
			R.data = A.data - B.data;
		}
		else if (k == 0)
		{
			R.sign = 0;
			R.data = 0;
		}
		else if (k == -1)
		{
			R.sign = -1;
			R.data = B.data - A.data;
		}
	}
	else
	{
		int k = compare(B.data, A.data);
		if (k == 1)
		{
			R.sign = 1;
			R.data = B.data - A.data;
		}
		else if (k == 0)
		{
			R.sign = 0;
			R.data = 0;
		}
		else if (k == -1)
		{
			R.sign = -1;
			R.data = A.data - B.data;
		}
	}
	return R;
}

signed_BigInt operator - (const signed_BigInt &A)
{
	signed_BigInt R;
	R.sign = -A.sign;
	R.data = A.data;
	return R;
}

signed_BigInt operator - (const signed_BigInt &A, const signed_BigInt &B)
{
	if (B.sign == 0) return A;
	if (A.sign == 0) return -B;
	signed_BigInt R;
	if (A.sign * B.sign == -1)
	{
		R.sign = A.sign;
		R.data = A.data + B.data;
	}
	else
	{
		int k = compare(A.data, B.data);
		if (k == 0)
		{
			R.sign = 0;
			R.data = 0;
			return R;
		}
		if (A.sign == 1 && B.sign == 1)
		{
			if (k == -1)
			{
				R.data = B.data - A.data;
				R.sign = -1;
			}
			else
			{
				R.data = A.data - B.data;
				R.sign = 1;
			}
		}
		else
		{
			if (k == -1)
			{
				R.data = B.data - A.data;
				R.sign = 1;
			}
			else
			{
				R.data = A.data - B.data;
				R.sign = -1;
			}
		}
	}
	return R;
}

signed_BigInt operator * (const signed_BigInt &A, const signed_BigInt &B)
{
	signed_BigInt R;
	if (A.sign * B.sign == 0)
	{
		R.data = 0;
		R.sign = 0;
		return R;
	}
	R.data = A.data * B.data;
	R.sign = A.sign * B.sign;
	return R;
}

signed_BigInt operator / (const signed_BigInt &A, const signed_BigInt &B)
{
	signed_BigInt R;
	if (A.sign == 0)
	{
		R.data = 0;
		R.sign = 0;
		return R;
	}
	R.data = A.data / B.data;
	if (R.data.len == 0)
		R.sign = 0;
	else
		R.sign = A.sign * B.sign;
	return R;
}

signed_BigInt operator % (const signed_BigInt &A, const signed_BigInt &B)
{
	signed_BigInt R;
	if (A.sign == 0)
	{
		R.data = 0;
		R.sign = 0;
		return R;
	}
	R.data = A.data % B.data;
	if (R.data.len == 0)
	{
		R.sign = 0;
		return R;
	}
	R.sign = 1;
	if (A.sign * B.sign == -1)
		R.data = B.data - A.data % B.data;
	return R;
}


signed_BigInt signed_read()
{
	signed_BigInt ret;
	char ch;
	ch = getc(stdin);
	if (ch == '-')
		ret.sign = -1;
	else
	{
		ret.sign = 1;
		ungetc(ch, stdin);
	}
	ret.data = unsigned_read();
	if (compare(ret.data, unsigned_Zero) == 0)
		ret.sign = 0;
	return ret;
}



