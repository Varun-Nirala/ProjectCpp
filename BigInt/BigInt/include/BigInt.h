/*
	@file	: BigInt.h
	@breif	: Implementing BigInt(no limit in number of digits) numbers
	@date	: 03-March-2017

	@NOTE	: Currently only supports, Integers
*/

#ifndef _BIGINT_H_
#define _BIGINT_H_

#include <iostream>
#include <string>

namespace PersonalInt
{
	class BigInt
	{
		public:
			BigInt();
			BigInt(const std::string &dataString);
			BigInt(const long long int &num);

			BigInt(const BigInt &bigInt);
			BigInt(BigInt &&bigInt);					// move copy constructor

			const int size() const;

			// Member Overloaded operators
			BigInt& operator= (const BigInt &bigInt);
			BigInt& operator= (const std::string &dataString);
			BigInt& operator= (const long long int &num);
			BigInt& operator= (BigInt &&bigInt);		// move assigment operator

			bool operator== (const BigInt &r_bigInt);
			bool operator< (const BigInt &r_bigInt);
			bool operator<= (const BigInt &r_bigInt);

			bool operator> (const BigInt &r_bigInt);
			bool operator>= (const BigInt &r_bigInt);

			BigInt operator-() const;
			BigInt operator+() const;

			// Friend Overloaded operators

			friend BigInt operator+(const BigInt &bigInt, long long int &value);		// Bigint + int
			friend BigInt operator+(long long int &value, const BigInt &bigInt);		// int + BigInt
			friend BigInt operator+(const BigInt &l_bigInt, const BigInt &r_bigInt);	// BigInt + BigInt

			friend BigInt operator+(const BigInt &bigInt, long long int &value);		// Bigint + int
			friend BigInt operator+(long long int &value, const BigInt &bigInt);		// int + BigInt
			friend BigInt operator+(const BigInt &l_bigInt, const BigInt &r_bigInt);	// BigInt + BigInt

			friend std::ostream& operator<< (std::ostream &out, const BigInt &bigInt);

		private:
			const int* const GetArray() const;
			bool isNegative() const;

			void InitializeWithString(const std::string &dataString);
			void InitializeWithLongInt(const long long int &num);

			inline int ConvertToInt(const char &ch);

			BigInt Add(const BigInt &lhs, const BigInt &rhs);
			bool LessThan(const BigInt &lhs, const BigInt &rhs);

			void MakeCopy(const BigInt &bigInt);

		private:
			int				m_size;
			bool			m_isNegative;
			int				*m_pArray;
			long long int	m_num;
	};
}
#endif