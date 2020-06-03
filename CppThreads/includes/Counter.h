#pragma once

#include <iostream>

void counterFunc(int id, int numIterations)
{
	for (int i = 0; i < numIterations; ++i)
	{
		std::cout << "Counter " << id << " has value ";
		std::cout << i << std::endl;
	}
}

class Counter
{
	public:
		Counter(int id, int numIterations)
			: mId(id)
			, mNumIterations(numIterations)
		{
		}

		void operator() () const
		{
			Process();
		}

		void Process() const
		{
			for (int i = 0; i < mNumIterations; ++i)
			{
				std::cout << "Counter " << mId << " has value ";
				std::cout << i << std::endl;
			}
		}

	private:
		int mId;
		int mNumIterations;
};