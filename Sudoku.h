#include<iostream>
#include<cstdlib>
using namespace std;

class Sudoku{
	public:
		void giveQuestion();
		void readIn();
		void solve();
		bool check(int);
		void backtrace(int);
		void changeNum(int,int);
		void changeRow(int,int);
		void changeCol(int,int);
		void rotate(int);
		void flip(int);
		void transform();
	private:
		int i,j,k,ans;
		int map[9][9],tmp[9][9],map2[9][9];
};
