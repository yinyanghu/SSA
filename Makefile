all:			SSA Simple_SSA BigInt_Extend.o 

SSA:			SSA.cpp BigInt_Extend.o
	g++ SSA.cpp BigInt_Extend.o -O3 -o SSA

Simple_SSA:		Simple_SSA.cpp
	g++ Simple_SSA.cpp -O3 -o Simple_SSA

BigInt_Extend.o:	BigInt_Extend.cpp BigInt_Extend.h
	g++ BigInt_Extend.cpp -c -O3

clean:
	rm *.o
	rm SSA Simple_SSA
