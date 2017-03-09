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
			throw "DataString provided is NULL.\n";
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

	BigInt BigInt::Add(const BigInt &lhs, const BigInt &rhs)
	{
		int carry = 0;
	}

	bool BigInt::LessThan(const BigInt &lhs, const BigInt &rhs)
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
		else if (this->m_isNegative && rhs.m_isNegative)
		{
			if (lhs.m_size < rhs.m_size)
			{
				rc = true;
			}
			else if (lhs.m_size > rhs.m_size)
			{
				rc = false;
			}
			else if (lhs.m_size == rhs.m_size)
			{
				int index = lhs.m_size;
				if (lhs.m_pArray[index] < rhs.m_pArray[index])
				{
					rc = true;
				}
				else
				{
					rc = false;
				}
			}
		}
		else
		{
			// TODO :: Error situation
		}
		return rc;
	}

	bool BigInt::operator== (const BigInt &r_bigInt)
	{

	}

	bool BigInt::operator< (const BigInt &r_bigInt)
	{
		bool rc = false;
		// If both are positive number
		if (!this->m_isNegative && !r_bigInt.m_isNegative)
		{
			rc = LessThan(*this, r_bigInt);
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
			rc = !(LessThan(*this, r_bigInt));
		}
		return rc;
	}

	bool BigInt::operator<= (const BigInt &r_bigInt)
	{
		bool rc = false;

	}

	bool BigInt::operator> (const BigInt &r_bigInt)
	{
		bool rc = false;
		// If both are positive number
		if (!this->m_isNegative && !r_bigInt.m_isNegative)
		{
			rc = !(LessThan(*this, r_bigInt));
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
			rc = LessThan(*this, r_bigInt);
		}
		return rc;
	}

	bool BigInt::operator>= (const BigInt &r_bigInt)
	{
	}

	// Friend Overloaded operators
	// Binary +
	BigInt operator+(const BigInt &bigInt, long long int &value)
	{

	}

	BigInt operator+(long long int &value, const BigInt &bigInt)
	{
	}

	BigInt operator+(const BigInt &l_bigInt, const BigInt &r_bigInt)
	{
	}

	// Binary -
	BigInt operator-(const BigInt &bigInt, long long int &value)
	{
	}

	BigInt operator-(long long int &value, const BigInt &bigInt)
	{
	}

	BigInt operator-(const BigInt &l_bigInt, const BigInt &r_bigInt)
	{
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
		out << std::endl;
		return out;
	}

}// namespace PersonalInt
