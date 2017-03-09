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
		m_pArray(NULL),
		m_num(0)
	{
	}

	BigInt::BigInt(const string &dataString)
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

	BigInt::BigInt(const long long int &num)
	{
		string s_num = std::to_string(num);
		InitializeWithString(s_num);
	}

	// Copy Constructor
	BigInt::BigInt(const BigInt &bigInt)
	{
		MakeCopy(bigInt);
	}

	// Move Constructor
	BigInt::BigInt(BigInt &&bigInt)
	{
		delete[] m_pArray;
		m_size = bigInt.m_size;
		m_pArray = bigInt.m_pArray;
		m_isNegative = bigInt.m_isNegative;

		bigInt.m_size = 0;
		bigInt.m_pArray = NULL;
		bigInt.m_isNegative = false;
	}

	void BigInt::InitializeWithString(const std::string &dataString)
	{
		if (dataString.empty())
		{
			char str[] = "DataString provided is NULL.\n";
			throw str;
		}

		delete[] m_pArray;
		m_isNegative = false;

		int size = dataString.size();
		int index = 0, i = 0;

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
				m_pArray[i] = ConvertToInt(ch);
			}
			else
			{
				throw "InputData string contain non-numbric character.\n";
			}
		}
	}

	int BigInt::ConvertToInt(const char &ch)
	{
		return std::move(ch - '0');
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
			InitializeWithString(dataString);
		}
		catch (std::string s_error)
		{
			std::cout << "Error:: " << s_error.c_str() << std::endl;
			throw;
		}
		return *this;
	}

	BigInt& BigInt::operator= (const long long int &num)
	{
		string s_num = std::to_string(num);
		InitializeWithString(s_num);
		return *this;
	}

	BigInt& BigInt::operator= (BigInt &&bigInt)
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

		for (int i = 0; m_size; ++i)
		{
			m_pArray[i] = bigInt.m_pArray[i];
		}
	}

	bool BigInt::CompareDigits(const BigInt &rhs)
	{
		int max = m_size;
		for (int i = 0; i < max; ++i)
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

			int lhs_index = m_size - 1, rhs_index = rhs.m_size - 1;

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

			return BigInt(num);
		}
	}

	BigInt BigInt::Sub(const BigInt &rhs) const
	{
		int carry = 0;

		if (m_size == 0 || rhs.m_size == 0)
		{
			return BigInt(*this);
		}
		else if ((m_isNegative && !rhs.m_isNegative) || (!m_isNegative && rhs.m_isNegative))
		{

		}
		else
		{
			return Add(rhs);
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
				int index = m_size;
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

	bool BigInt::operator== (const BigInt &r_bigInt)
	{
		bool rc = false;

		if (this->m_size == r_bigInt.m_size && this->m_isNegative == r_bigInt.m_isNegative)
		{
			rc = CompareDigits(r_bigInt);
		}
		return rc;
	}

	bool BigInt::operator< (const BigInt &r_bigInt)
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

	bool BigInt::operator<= (const BigInt &r_bigInt)
	{
		return (*this == r_bigInt || *this < r_bigInt);
	}

	bool BigInt::operator> (const BigInt &r_bigInt)
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

	bool BigInt::operator>= (const BigInt &r_bigInt)
	{
		return (*this == r_bigInt || *this > r_bigInt);
	}
	
	// Friend Overloaded operators
	// Binary +
	BigInt operator+(const BigInt &bigInt, long long int &value)
	{
		return bigInt.Add(BigInt(value));
	}

	BigInt operator+(long long int &value, const BigInt &bigInt)
	{
		return bigInt.Add(value);
	}

	BigInt operator+(const BigInt &l_bigInt, const BigInt &r_bigInt)
	{
		return l_bigInt.Add(r_bigInt);
	}

	// Binary -
	BigInt operator-(const BigInt &bigInt, long long int &value)
	{
		return bigInt.Sub(BigInt(value));
	}

	BigInt operator-(long long int &value, const BigInt &bigInt)
	{
		return (BigInt(value)).Sub(bigInt);
	}

	BigInt operator-(const BigInt &l_bigInt, const BigInt &r_bigInt)
	{
		return l_bigInt.Sub(r_bigInt);
	}

	std::ostream& operator<< (std::ostream &out, const BigInt &bigInt)
	{
		int i, size = bigInt.m_size;

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

}// namespace PersonalInt
