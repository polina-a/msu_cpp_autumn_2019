#pragma once

#include <iostream>


class BigInt{
	bool is_neg;
	char* data;
	size_t size;
public:
	BigInt(const int n);
	BigInt(const BigInt& n);

	BigInt& operator=(const BigInt& a);
	BigInt(BigInt&& moved);
	BigInt& operator=(BigInt&& moved);

	BigInt operator-()const;
	friend BigInt operator+(const BigInt& a,const BigInt& b);
	friend BigInt operator-(const BigInt& a,const BigInt& b);

	friend bool operator==(const BigInt& a,const BigInt& b);
	friend bool operator>=(const BigInt& a,const BigInt& b);
	friend bool operator!=(const BigInt& a,const BigInt& b);
	friend bool operator<=(const BigInt& a,const BigInt& b);
	friend bool operator>(const BigInt& a,const BigInt& b);
	friend bool operator<(const BigInt& a,const BigInt& b);

	friend ostream & operator<<(ostream & out, const BigInt & a);
	~BigInt();
};

