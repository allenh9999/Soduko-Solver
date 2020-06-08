#include "solver.h"
#include <iostream>
#include <ios>

using namespace std;

int main() {
	// for speed
	ios_base::sync_with_stdio(false);
	Solver solver;
	while (!solver.isValid()) {
		cout << "The board is not valid. Please input a valid board" << endl;
		solver.inputNewBoard();
	}
	cout << "Solution: " << endl;
	solver.solve();
	solver.print_nums();
}