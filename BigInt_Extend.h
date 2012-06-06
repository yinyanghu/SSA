#include <cstdio>
#include <cstring>
#include "Math.h"

#define capacity		100
#define base			0x40000000  // 2^30
#define __base			0x20000000  // 2^29
//#define base_dec_bit 9
#define base_bit		30
#define base_mod		0x3FFFFFFF
#define base_dec		1000000000
#define exponentiation_size	1500	

#define read_size		1000

struct Dec_BigInt
{
	int len;
	int __data[capacity];
	Dec_BigInt() : len(0) {}
	Dec_BigInt(const Dec_BigInt &source) : len(source.len)
	{
		memcpy(__data, source.__data, len * sizeof *__data);
	}
	Dec_BigInt(int key) : len(0)
	{
		for (; key > 0; key /= base_dec)
			__data[len ++] = key % base_dec;
	}
	int & operator [] (int Index) { return __data[Index]; }
	int operator [] (int Index) const { return __data[Index]; }

	void print()
	{
		if (len == 0)
		{
			printf("0");
			return;
		}
		printf("%d", __data[len - 1]);
		for (int i = len - 2; i >= 0; -- i)
			for (int j = base_dec / 10; j > 0; j /= 10)
				printf("%d", __data[i] / j % 10);
	}
};


Dec_BigInt operator + (const Dec_BigInt &A, const Dec_BigInt &B);

Dec_BigInt operator * (const Dec_BigInt &A, const int B);






struct unsigned_BigInt
{
	int len;
	int __data[capacity];
	unsigned_BigInt() : len(0) {}
	unsigned_BigInt(const unsigned_BigInt &source) : len(source.len)
	{
		memcpy(__data, source.__data, len * sizeof *__data);
	}
	unsigned_BigInt(int key) : len(0)
	{
		for (; key > 0; key >>= base_bit)
			__data[len ++] = key & base_mod;
	}
	unsigned_BigInt(long long key) : len(0)
	{
		for (; key > 0; key >>= base_bit)
			__data[len ++] = key & base_mod;
	}
	unsigned_BigInt & operator = (const unsigned_BigInt &key)
	{
		len = key.len;
		memcpy(__data, key.__data, len * sizeof *__data);
		return *this;
	}
	int & operator [] (int Index) { return __data[Index]; }
	int operator [] (int Index) const { return __data[Index]; }

	void print()
	{
		if (len == 0)
		{
			printf("0");
			return;
		}
		static Dec_BigInt V;
		V = 0;
		for (int i = len - 1; i >= 0; -- i)
			V = V * base + __data[i];
		V.print();
	}

};

int compare(const unsigned_BigInt &A, const unsigned_BigInt &B);



void shift_right_base(unsigned_BigInt &A);

void shift_left_base(unsigned_BigInt &A);

void shift_right(unsigned_BigInt &A);

void shift_left(unsigned_BigInt &A);



unsigned_BigInt operator + (const unsigned_BigInt &A, const unsigned_BigInt &B);

unsigned_BigInt operator - (const unsigned_BigInt &A, const unsigned_BigInt &B);

unsigned_BigInt operator * (const unsigned_BigInt &A, const int B);

unsigned_BigInt operator * (const unsigned_BigInt &A, const unsigned_BigInt &B);

unsigned_BigInt operator / (const unsigned_BigInt &A, const int B);

unsigned_BigInt operator % (const unsigned_BigInt &A, const int B);

unsigned_BigInt multiply(const unsigned_BigInt &A, unsigned_BigInt B);

void divide(const unsigned_BigInt &A, const unsigned_BigInt &B, unsigned_BigInt &Q, unsigned_BigInt &R);

unsigned_BigInt operator / (const unsigned_BigInt &A, const unsigned_BigInt &B);

unsigned_BigInt operator % (const unsigned_BigInt &A, const unsigned_BigInt &B);

unsigned_BigInt unsigned_read();



struct signed_BigInt
{
	unsigned_BigInt data;
	int sign;
	signed_BigInt() : data(0), sign(0) {}
	signed_BigInt(const signed_BigInt &source) : sign(source.sign)
	{
		data = source.data;
	}
	signed_BigInt(int key) : sign(SGN(key)), data(ABS(key)) {}
	signed_BigInt & operator = (const signed_BigInt &key)
	{
		sign = key.sign;
		data = key.data;
		return *this;
	}
	int & operator [] (int Index) { return data[Index]; }
	int operator [] (int Index) const { return data[Index]; }
	
	void print()
	{
		if (sign == -1) printf("-");
		data.print();
	}
};


int compare(const signed_BigInt &A, const signed_BigInt &B);


signed_BigInt operator + (const signed_BigInt &A, const signed_BigInt &B);

signed_BigInt operator - (const signed_BigInt &A);

signed_BigInt operator - (const signed_BigInt &A, const signed_BigInt &B);

signed_BigInt operator * (const signed_BigInt &A, const signed_BigInt &B);

signed_BigInt operator / (const signed_BigInt &A, const signed_BigInt &B);

signed_BigInt operator % (const signed_BigInt &A, const signed_BigInt &B);

signed_BigInt signed_read();

extern const unsigned_BigInt unsigned_Zero;
extern const unsigned_BigInt unsigned_One;

extern const signed_BigInt Zero;
extern const signed_BigInt One;
extern const signed_BigInt Minus_One;


