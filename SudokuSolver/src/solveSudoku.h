#pragma once

#include "grid.h"
#include <iomanip>
#include <initializer_list>

template<typename T>
class SudokuSolver; // forward declare to make function declaration possible

template<typename T> // declaration
std::ostream& operator<<(std::ostream&, const SudokuSolver<T>&);

// 9 x 9 sudoku solver
template<typename T>
class SudokuSolver
{
	public:
		SudokuSolver(std::initializer_list<std::initializer_list<T>> mat)
			:mMatrix(mat.size(), mat.begin()->size())
		{
			int i = 0;
			int j = 0;
			for (auto list : mat)
			{
				for (auto x : list)
				{
					mMatrix.at(i, j++) = x;
				}
				i++;
				j = 0;
			}
		}

		int numRow() const
		{
			return mMatrix.numRow();
		}

		int numCol() const
		{
			return mMatrix.numCol();
		}

		int& at(int row, int col)
		{
			return mMatrix.at(row, col);
		}

		const int& at(int row, int col) const
		{
			return mMatrix.at(row, col);
		}

		friend std::ostream& operator<<(std::ostream &out, const SudokuSolver<T> &obj)
		{
			obj.printMat(obj.mMatrix);
			return out;
		}

		bool solve()
		{
			return solveSudoku(mMatrix);
		}

	protected:
		bool solveSudoku(Grid<T> &grid)
		{
			int row = 0;
			int col = 0;
			if (!findEmptyLocation(grid, row, col))
			{
				return true;
			}

			for (int i = 1; i < 10; ++i)
			{
				if (isSafe(grid, row, col, i))
				{
					grid.at(row, col) = i;
					if (solveSudoku(grid))
						return true;
					grid.at(row, col) = gcBLANK;
				}
			}
			return false;
		}

		void printMat(const Grid<T> &grid) const
		{
			int setWidth = 2;
			for (int i = 0; i < grid.numRow(); ++i)
			{
				if (i && (i % 3 == 0))
				{
					int max = (setWidth + 1) * grid.numCol() + grid.numCol() / 3;
					for (int k = 0; k < max; ++k)
					{
						std::cout << "-";
					}
					std::cout << std::endl;
				}

				for (int j = 0; j < grid.numCol(); ++j)
				{
					if (j && (j % 3 == 0))
					{
						std::cout << "| ";
					}
					if (grid.at(i, j) != gcBLANK)
					{
						std::cout << std::setw(setWidth) << grid.at(i, j) << " ";
					}
					else
					{
						std::cout << std::setw(setWidth) << char(NULL) << " ";
					}
				}
				std::cout << "\n";
			}
		}

	private:
		bool findEmptyLocation(const Grid<T> &grid, int &row, int &col)
		{
			for (row = 0; row < grid.numRow(); ++row)
			{
				for (col = 0; col < grid.numCol(); ++col)
				{
					if (grid.at(row, col) == gcBLANK)
					{
						return true;
					}
				}
			}
			return false;
		}

		bool isSafe(const Grid<T> &grid, int row, int col, T &val) const
		{
			return !usedInRow(grid, row, val) && !usedInCol(grid, col, val) && !usedIn3x3Box(grid, row, col, val);
		}

		bool usedInRow(const Grid<T> &grid, int row, T &val) const
		{
			for (int i = 0; i < grid.numCol(); ++i)
			{
				if (grid.at(row, i) == val)
				{
					return true;
				}
			}
			return false;
		}

		bool usedInCol(const Grid<T> &grid, int col, T &val) const
		{
			for (int i = 0; i < grid.numRow(); ++i)
			{
				if (grid.at(i, col) == val)
				{
					return true;
				}
			}
			return false;
		}

		bool usedIn3x3Box(const Grid<T> &grid, int row, int col, T &val) const
		{
			int startRow = row - row % 3;
			int startCol = col - col % 3;

			for (int i = startRow; i < 3 + startRow; ++i)
			{
				for (int j = startCol; j < 3 + startCol; ++j)
				{
					if (grid.at(i, j) == val)
					{
						return true;
					}
				}
			}
			return false;
		}

	private:
		Grid<T>		mMatrix;
};