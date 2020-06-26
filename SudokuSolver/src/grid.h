#pragma once

#include <iostream>
#include <algorithm>
#include <cassert>

const int gcBLANK = 0;

template<typename T>
class Grid
{
	public:
		Grid(int row, int col)
		{
			init(row, col);
		}

		~Grid()
		{
			destroy();
		}

		bool resize(int row, int col)
		{
			destroy();
			init(row, col);
		}

		T& at(int row, int col)
		{
			assert(!(row >= mRow));
			assert(!(col >= mCol));
			return mGrid[row][col];
		}

		const T& at(int row, int col) const
		{
			assert(!(row >= mRow));
			assert(!(col >= mCol));
			return mGrid[row][col];
		}


		int numRow() const
		{
			return mRow;
		}

		int numCol() const
		{
			return mCol;
		}

		Grid<T>* clone()
		{
			Grid<T>* cloneGrid = new Grid<T>(mRow, mCol);

			for (int i = 0; i < mRow; ++i)
			{
				for (int j = 0; j < mCol; ++j)
				{
					cloneGrid->mGrid[i][j] = mGrid[i][j];
				}
			}
			return cloneGrid;
		}

	private:
		void init(int row, int col)
		{
			mCol = col;
			mRow = row;

			mGrid = new T*[mRow] {gcBLANK};

			for (int i = 0; i < mRow; ++i)
			{
				mGrid[i] = new T[mCol]{ gcBLANK };
			}
		}

		void destroy()
		{
			for (int i = 0; i < mRow; ++i)
			{
				delete[]  mGrid[i];
			}
			delete mGrid;
			mGrid = NULL;
			mCol = mRow = 0;
		}

	private:
		int		**mGrid {NULL};
		int		mCol;
		int		mRow;
};