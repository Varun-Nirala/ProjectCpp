/*
	@file	: BigInt.cpp
	@breif	: Implementing BigInt(no limit in number of digits) numbers
	@date	: 03-March-2017

	@NOTE	: Currently only supports, Integers
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <ctype.h>

#include "BigInt.h"

using std::string;

namespace PersonalInt
{
	BigInt::BigInt()
		:m_size(0),
		m_isNegative(false),
		m_pArray(NULL)
	{
	}

	BigInt::BigInt(const string &dataString)
		:m_size(0),
		m_isNegative(false),
		m_pArray(NULL)
	{
		try
		{
			InitializeWithString(dataString.c_str());
		}
		catch (std::string s_error)
		{
			std::cout << "Error:: " << s_error.c_str() << std::endl;
			throw;
		}
	}

	BigInt::BigInt(const char* dataString)
		:m_size(0),
		m_isNegative(false),
		m_pArray(NULL)
	{
		try
		{
			InitializeWithString(dataString);
		}
		catch (std::string s_error)
		{
			std::cout << "Error:: " << s_error.c_str() << std::endl;
			throw;
		}
	}

	BigInt::BigInt(const __int64 &num)
		:m_size(0),
		m_isNegative(false),
		m_pArray(NULL)
	{
		InitializeWithString(std::to_string(num).c_str());
	}

	// Copy Constructor
	BigInt::BigInt(const BigInt &bigInt)
		:m_size(0),
		m_isNegative(false),
		m_pArray(NULL)
	{
		MakeCopy(bigInt);
	}

	// Move Copy Constructor
	BigInt::BigInt(BigInt &&bigInt)
	{
		m_size = bigInt.m_size;
		m_pArray = bigInt.m_pArray;
		m_isNegative = bigInt.m_isNegative;

		bigInt.m_size = 0;
		bigInt.m_pArray = NULL;
		bigInt.m_isNegative = false;
	}

	BigInt::~BigInt()
	{
		this;
		std::cout << "Address : " << this << std::endl;
		Clear();
	}

	void BigInt::Clear()
	{
		if (m_pArray)
		{
			delete[] m_pArray;
			m_pArray = NULL;
		}
		m_size = 0;
		m_isNegative = false;
	}

	__int64 BigInt::size() const
	{
		return m_size;
	}

	void BigInt::InitializeWithString(const char *dataString)
	{
		if (std::strlen(dataString) == 0)
		{
			char str[] = "DataString provided is NULL.\n";
			throw str;
		}

		delete[] m_pArray;
		m_isNegative = false;

		__int64 size = std::strlen(dataString);
		__int64 index = 0, i = 0;

		m_size = size;

		if (dataString[0] == '-')
		{
			m_isNegative = true;
			m_size--;
			index++;
		}
		m_pArray = new int[m_size];
		char ch;
		for (index; index < size; ++index, ++i)
		{
			ch = dataString[index];
			if (isdigit(ch))
			{
				m_pArray[i] = to_Int(ch);
			}
			else
			{
				Clear();
				throw "InputData string contain non-numbric character.\n";
			}
		}
	}

	int BigInt::to_Int(const char ch) const
	{
		return std::move(ch - '0');
	}

	char BigInt::to_Char(const int digit) const
	{
		return std::move(digit + '0');
	}

	std::string BigInt::to_String() const
	{
		if (m_size == 0)
			return "";

		std::string rc;

		rc.reserve(m_size);
		__int64 i;

		for (i = 0; i < m_size; ++i)
		{
			rc.push_back(to_Char(m_pArray[i]));
		}
		return rc;
	}

	void BigInt::reverse(BigInt &bigInt)
	{
		__int64 size = bigInt.size();
		__int64 start, last = size - 1;

		for (start = 0; start < size; ++start, --last)
		{
			std::swap(bigInt.m_pArray[start], bigInt.m_pArray[last]);
		}
	}

	bool BigInt::reserve(__int64 cap)
	{
		Clear();
		m_pArray = new int[cap - 1];
		if (m_pArray)
		{
			m_size = cap;
			for (__int64 i = 0; i < cap; ++i)
			{
				m_pArray[i] = 0;
			}
			return true;
		}
		else
		{
			return false;
		}
	}

	// Member Overloaded operators
	BigInt& BigInt::operator = (const BigInt &bigInt)
	{
		if (this == &bigInt)
		{
			return *this;
		}

		MakeCopy(bigInt);

		return *this;
	}

	BigInt& BigInt::operator = (const std::string &dataString)
	{
		try
		{
			InitializeWithString(dataString.c_str());
		}
		catch (std::string s_error)
		{
			std::cout << "Error:: " << s_error.c_str() << std::endl;
			throw;
		}
		return *this;
	}

	BigInt& BigInt::operator= (const __int64 &num)
	{
		string s_num = std::to_string(num);
		InitializeWithString(s_num.c_str());
		return *this;
	}

	BigInt& BigInt::operator= (BigInt &&bigInt)			// Move Assignment
	{
		if (this == &bigInt)
		{
			return *this;
		}

		delete[] m_pArray;
		m_size = bigInt.m_size;
		m_pArray = bigInt.m_pArray;
		m_isNegative = bigInt.m_isNegative;

		bigInt.m_size = 0;
		bigInt.m_pArray = NULL;
		bigInt.m_isNegative = false;

		return *this;
	}

	void BigInt::MakeCopy(const BigInt &bigInt)
	{
		if (m_pArray)
		{
			delete[] m_pArray;
		}
		m_size = bigInt.m_size;
		m_pArray = new int[bigInt.m_size];
		m_isNegative = bigInt.m_isNegative;

		for (__int64 i = 0; i < m_size; ++i)
		{
			m_pArray[i] = bigInt.m_pArray[i];
		}
	}

	bool BigInt::CompareDigits(const BigInt &rhs) const
	{
		__int64 max = m_size;
		for (__int64 i = 0; i < max; ++i)
		{
			if (this->m_pArray[i] != rhs.m_pArray[i])
				return false;
		}
		return true;
	}

	BigInt BigInt::Add(const BigInt &rhs) const
	{
		if (m_size == 0 || rhs.m_size == 0)
		{
			return BigInt(*this);
		}
		else if ((m_isNegative && !rhs.m_isNegative) || (!m_isNegative && rhs.m_isNegative))
		{
			return Sub(rhs);
		}
		else // if both are of same sign
		{
			int carry = 0;
			int sum;
			string num;

			if (this->m_isNegative)
			{
				num.reserve(std::max(this->m_size, rhs.m_size) + 1);
			}
			else
			{
				num.reserve(std::max(this->m_size, rhs.m_size));
			}

			__int64 lhs_index = m_size - 1, rhs_index = rhs.m_size - 1;

			for (; lhs_index >= 0 && rhs_index >= 0; --lhs_index, --rhs_index)
			{
				sum = carry + this->m_pArray[lhs_index] + rhs.m_pArray[rhs_index];
				num += std::to_string(sum%10);
				carry = sum / 10;
			}

			if (lhs_index)
			{
				for (; lhs_index >= 0; --lhs_index)
				{
					sum = carry + this->m_pArray[lhs_index];
					num += std::to_string(sum % 10);
					carry = sum / 10;
				}
			}
			else if (rhs_index)
			{
				for (; rhs_index >= 0; --rhs_index)
				{
					sum = carry + rhs.m_pArray[lhs_index];
					num += std::to_string(sum % 10);
					carry = sum / 10;
				}
			}

			if (this->m_isNegative)
			{
				num += "-";
			}
			std::reverse(num.begin(), num.end());

			return std::move(BigInt(num));
		}
	}

	// It assumes that this pointer have same or more number of digit as rhs have
	// it do this - rhs operation and it wont change any sign
	BigInt BigInt::SubHelper(const BigInt &rhs) const
	{
		if (*this == rhs)
		{
			return BigInt();
		}
		else
		{
			__int64 lhs_index = m_size - 1, rhs_index = rhs.m_size - 1;
			int borrow = 0;
			long long borrow_index = m_size - 2;
			__int64 left, right;
			string num;
			num.reserve(m_size - 1);

			for (; lhs_index >= 0 && rhs_index >= 0; --lhs_index, --rhs_index, --borrow_index)
			{
				left = this->m_pArray[lhs_index];
				right = rhs.m_pArray[rhs_index];

				if (borrow)
				{
					--left;
					borrow = 0;
				}

				if (left < right)
				{
					left += 10;
					borrow = 1;
				}

				num += std::to_string(left - right);
			}
			std::reverse(num.begin(), num.end());

			return std::move(BigInt(num));
		}
	}

	BigInt BigInt::Sub(const BigInt &rhs) const
	{
		int borrow = 0;
		if (m_size == 0 || rhs.m_size == 0)
		{
			return BigInt(*this);
		}
		else if ((m_isNegative && !rhs.m_isNegative) || (!m_isNegative && rhs.m_isNegative))
		{
			BigInt rc = (m_size >= rhs.m_size) ? SubHelper(rhs) : rhs.SubHelper(*this);
			(m_size >= rhs.m_size) ? (rc.m_isNegative = rhs.m_isNegative) : (rc.m_isNegative = this->m_isNegative);
			return rc;
		}
		else if (m_isNegative && rhs.m_isNegative) // Both negative
		{
			return Add(rhs);
		}
		else // Both positive
		{
			return std::move(SubHelper(rhs));
		}
	}

	bool BigInt::LessThan(const BigInt &rhs) const
	{
		bool rc = false;

		// if lhs is negative but rhs is positive
		if (this->m_isNegative && !rhs.m_isNegative)
		{
			rc = true;
		}
		// if lhs is positive but rhs is negative
		else if (!this->m_isNegative && rhs.m_isNegative)
		{
			rc = false;
		}
		// if both have same sign
		else
		{
			// compare assuming them as positive
			if (m_size < rhs.m_size)
			{
				rc = true;
			}
			else if (m_size > rhs.m_size)
			{
				rc = false;
			}
			else if (m_size == rhs.m_size)
			{
				__int64 index = m_size;
				if (m_pArray[index] < rhs.m_pArray[index])
				{
					rc = true;
				}
				else
				{
					rc = false;
				}
			}

			// if both are negative invert the answer
			if (m_isNegative && rhs.m_isNegative)
			{
				rc = !rc;
			}
		}
		return rc;
	}

	bool BigInt::operator== (const BigInt &r_bigInt) const
	{
		bool rc = false;

		if (this->m_size == r_bigInt.m_size && this->m_isNegative == r_bigInt.m_isNegative)
		{
			rc = CompareDigits(r_bigInt);
		}
		return rc;
	}

	bool BigInt::operator< (const BigInt &r_bigInt) const
	{
		bool rc = false;
		// If both are positive number
		if (!this->m_isNegative && !r_bigInt.m_isNegative)
		{
			rc = LessThan(r_bigInt);
		}
		// if lhs is negative but rhs is positive
		else if (this->m_isNegative && !r_bigInt.m_isNegative)
		{
			rc = true;
		}
		// if lhs is positive but rhs is negative
		else if (!this->m_isNegative && r_bigInt.m_isNegative)
		{
			rc = false;
		}
		// if both are neagtive negative
		else if (this->m_isNegative && r_bigInt.m_isNegative)
		{
			rc = !(LessThan(r_bigInt));
		}
		return rc;
	}

	bool BigInt::operator<= (const BigInt &r_bigInt) const
	{
		return (*this == r_bigInt || *this < r_bigInt);
	}

	bool BigInt::operator> (const BigInt &r_bigInt) const
	{
		bool rc = false;
		// If both are positive number
		if (!this->m_isNegative && !r_bigInt.m_isNegative)
		{
			rc = !(LessThan(r_bigInt));
		}
		// if lhs is negative but rhs is positive
		else if (this->m_isNegative && !r_bigInt.m_isNegative)
		{
			rc = false;
		}
		// if lhs is positive but rhs is negative
		else if (!this->m_isNegative && r_bigInt.m_isNegative)
		{
			rc = true;
		}
		// if both are neagtive negative
		else if (this->m_isNegative && r_bigInt.m_isNegative)
		{
			rc = LessThan(r_bigInt);
		}
		return rc;
	}

	bool BigInt::operator>= (const BigInt &r_bigInt) const
	{
		return (*this == r_bigInt || *this > r_bigInt);
	}
	
	int& BigInt::operator[] (const __int64 index)
	{
		return m_pArray[index];
	}

	const int& BigInt::operator[] (const __int64 index) const
	{
		return m_pArray[index];
	}

	// Friend Overloaded operators
	// Binary +
	BigInt operator+(const BigInt &l_bigInt, const BigInt &r_bigInt)
	{
		return l_bigInt.Add(r_bigInt);
	}

	// Binary -
	BigInt operator-(const BigInt &l_bigInt, const BigInt &r_bigInt)
	{
		return l_bigInt.Sub(r_bigInt);
	}

	// Multiplication
	BigInt operator*(const BigInt &l_bigInt, const BigInt &r_bigInt)
	{
		return l_bigInt.LongMultplication(r_bigInt);
	}

	std::ostream& operator<< (std::ostream &out, const BigInt &bigInt)
	{
		__int64 i, size = bigInt.m_size;

		if (bigInt.m_isNegative)
		{
			out << "-";
		}

		for (i = 0; i < size; ++i)
		{
			out << bigInt.m_pArray[i];
		}
		return out;
	}

	/*
	LONG MULTIPLICATION
		multiply(a[1..p], b[1..q], base)							// Operands containing rightmost digits at index 1
		product = [1..p + q]										// Allocate space for result
		for b_i = 1 to q											// for all digits in b
		carry = 0
		for a_i = 1 to p											//for all digits in a
		product[a_i + b_i - 1] += carry + a[a_i] * b[b_i]
		carry = product[a_i + b_i - 1] / base
		product[a_i + b_i - 1] = product[a_i + b_i - 1] mod base
		product[b_i + p] += carry									// last digit comes from final carry
		return product
	*/
	BigInt BigInt::LongMultplication(const BigInt &num2, int base) const
	{
		BigInt result;
		__int64 max, total_number = 0;
		__int64 index_2, index_1, num2size, num1size;

		num1size = this->m_size;
		num2size = num2.size();
		
		max = num1size + num2size;

		result.reserve(num1size + num2size);	// Allocate max space required

		int carry = 0;
		for (index_2 = num2size - 1; index_2 >= 0; --index_2)
		{
			carry = 0;
			for (index_1 = num1size - 1; index_1 >= 0; --index_1)
			{
				result[index_1 + index_2] += carry + (*this)[index_1] * num2[index_2];
				carry = result[index_1 + index_2] / base;
				result[index_1 + index_2] = result[index_1 + index_2] % base;
				result[index_2 + num1size - 1] += carry;
			}
		}
		result.m_isNegative = (this->m_isNegative && num2.m_isNegative);
		std::cout << result << std::endl;
		std::cout << (&result) << std::endl;
		return std::move(result);
	}

}// namespace PersonalInt


/*
procedure karatsuba(num1, num2)
	if (num1 < 10) or (num2 < 10)
	return num1*num2
	// calculates the size of the numbers 
	m = max(size_base10(num1), size_base10(num2))
	m2 = m / 2
	// split the digit sequences about the middle 
	high1, low1 = split_at(num1, m2)
	high2, low2 = split_at(num2, m2)
	// 3 calls made to numbers approximately half the size 
	z0 = karatsuba(low1, low2)
	z1 = karatsuba((low1 + high1), (low2 + high2))
	z2 = karatsuba(high1, high2)
	return (z2 * 10 ^ (2 * m2)) + ((z1 - z2 - z0) * 10 ^ (m2)) + (z0)
*/