/*
	@file	: BigInt.h
	@breif	: Implementing BigInt(no limit in number of digits) numbers
	@date	: 03-March-2017

	@NOTE	: Currently only supports, Integers

	@Assumption : No operation will reach the limit of number of digit crossing the size of long long int
*/

#ifndef _BIGINT_H_
#define _BIGINT_H_

#include <iostream>
#include <string>
#include <cstring>

namespace PersonalInt
{
	class BigInt
	{
		public:
			BigInt();
			BigInt(const std::string &dataString);
			BigInt(const char* dataString);
			BigInt(const long long int &num);

			BigInt(const BigInt &bigInt);
			BigInt(BigInt &&bigInt);					// move copy constructor

			~BigInt();

			void Clear();

			bool reserve(long long int cap);

			long long int size() const;

			std::string to_String() const;

			// Member Overloaded operators
			BigInt& operator= (const BigInt &bigInt);
			BigInt& operator= (const std::string &dataString);
			BigInt& operator= (const long long int &num);
			BigInt& operator= (BigInt &&bigInt);		// move assigment operator

			bool operator== (const BigInt &r_bigInt) const;
			bool operator< (const BigInt &r_bigInt) const;
			bool operator<= (const BigInt &r_bigInt) const;

			bool operator> (const BigInt &r_bigInt) const;
			bool operator>= (const BigInt &r_bigInt) const;

			BigInt operator-() const;
			BigInt operator+() const;

			int& operator[] (const long long int index);
			const int& operator[] (const long long int index) const;

			// Friend Overloaded operators
			friend BigInt operator+(const BigInt &bigInt, long long int &value);		// Bigint + int
			friend BigInt operator+(long long int &value, const BigInt &bigInt);		// int + BigInt
			friend BigInt operator+(const BigInt &l_bigInt, const BigInt &r_bigInt);	// BigInt + BigInt

			friend BigInt operator-(const BigInt &bigInt, long long int &value);		// Bigint + int
			friend BigInt operator-(long long int &value, const BigInt &bigInt);		// int + BigInt
			friend BigInt operator-(const BigInt &l_bigInt, const BigInt &r_bigInt);	// BigInt + BigInt
			
			friend BigInt operator*(const BigInt &bigInt, long long int &value);		// Bigint + int
			friend BigInt operator*(long long int &value, const BigInt &bigInt);		// int + BigInt
			friend BigInt operator*(const BigInt &l_bigInt, const BigInt &r_bigInt);

			friend std::ostream& operator<< (std::ostream &out, const BigInt &bigInt);

		private:
			const int* const GetArray() const;
			bool isNegative() const;

			void InitializeWithString(const char *dataString);
			void InitializeWithLongInt(const long long int &num);

			inline int to_Int(const char ch) const;
			inline char to_Char(const int digit) const;

			BigInt Add(const BigInt &rhs) const;
			BigInt Sub(const BigInt &rhs) const;

			// Use when digit are more that 360-480 bits, i.e 40 - 60 Bytes
			// using when both digit's size is more than 15
			BigInt Karatsuba(const BigInt &num1, const BigInt &num2);

			// Use normally when digits are less than 360 bits
			BigInt LongMultplication(const BigInt &num2, int base = 10) const;

			// It assumes that this pointer have same or more number of digit as rhs have
			// it do this - rhs operation and it wont change any sign
			BigInt SubHelper(const BigInt &rhs) const;
			bool LessThan(const BigInt &rhs) const;

			// Assumes both have same size
			inline bool CompareDigits(const BigInt &rhs) const;
			void MakeCopy(const BigInt &bigInt);
			inline void reverse(BigInt &bigInt);

		private:
			long long int	m_size;
			bool			m_isNegative;
			int				*m_pArray;
	};
}
#endif