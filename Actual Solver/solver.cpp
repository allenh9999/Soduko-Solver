// Include the header file into the program
#include "solver.h"

// Creates the solver (default constructor)
// REQUIREMENTS: nothing
// MODIFIES: object
// EFFECTS: creates the object
Solver::Solver() {
	inputNewBoard();
}

// REQUIREMENTS: the board
// MODIFIES: object
// EFFECTS: creates the object with the specified board
//   Will also destroy the board as specified
Solver::Solver(bvector& board) {
	swap(board, _board);
}

// REQUIREMENTS: the board
// MODIFIES: object
// EFFECTS: creates the object with the specified board
//   will not change the board put in
Solver::Solver(const bvector& board) {
	_board = board;
}

// REQUIRMENETS: the board stored is an actual board
// MODIFIES: board
// EFFECTS: solves the soduko puzzle by filling in all the blanks
// RETURNS: if there is a solution to the board
bool Solver::solve() {
	return checkPos(0, 0);
}

// REQUIREMENTS: a board is inputted
// MODIFIES: the board inputted
// EFFECTS: modifies to make the board solved
// RETURNS: if there is a solution to the board
bool Solver::solve(bvector& board) {
	board.swap(_board);
	bool returnValue = checkPos(0, 0);
	board.swap(_board);
	return returnValue;
}

// REQUIRMENTS: correct input
// MODIFIES: board
// EFFECTS: inputs new values into the soduko puzzle
void Solver::inputNewBoard() {
	cout << "Enter the 81 characters for the board\n";
	cout << "Use a period '.' to symbolize a blank space";
	cout << endl;
	if (_board.empty()) {
		for (int i = 0; i < 9; ++i) {
			_board.push_back(vector<char>());
			for (int j = 0; j < 9; ++j) {
				char temp;
				cin >> temp;
				_board.back().push_back(temp);
				while (_board.back().back() != '.' && !(_board.back().back() >= '1' && _board.back().back() <= '9')) {
					if (!isspace(_board.back().back())) cout << "Please input a correct character" << endl;
					cin >> _board.back().back();
				}
			}
		}
	}
	else {
		for (int i = 0; i < 9; ++i) {
			for (int j = 0; j < 9; ++j) {
				cin >> _board[i][j];
				while (_board[i][j] != '.' && !(_board[i][j] >= '1' && _board[i][j] <= '9')) {
					if(!isspace(_board[i][j])) cout << "Please input a correct character" << endl;
					cin >> _board[i][j];
				}
			}
		}
	}
}

// REQUIREMENTS: correct input
// MODIFIES: board
// EFFECTS: prompts the user to input new values
void Solver::inputNewValue() {
	cout << "Please input the row you want to insert the value (from 1-9):" << endl;
	int row = inputHelper();
	cout << "Now please input the column you want to insert the value (from 1-9):" << endl;
	int col = inputHelper();
	cout << "Please input the value that you want to change to (from 1-9):" << endl;
	int val = inputHelper();
	_board[row - 1][col - 1] = (char) (val + '1' - 1);
}

// REQUIREMENTS: the coordinates of the point to change (from 0 - 8)
// MODIFIES: board
// EFFECTS: changes the board at the value specified
void Solver::inputNewValue(const size_t& i, const size_t& j, const char& val) {
	_board[i][j] = val;
}

// REQUIREMENTS: the coordinates of the point to change (from 1 - 9)
// MODIFIES: board
// EFFECTS: changes the board at the value specified
void Solver::inputNewValue(const int& i, const int& j, const char& val) {
	_board[i - 1][j - 1] = val;
}

// REQUIREMENTS: nothing
// MODIFIES: nothing
// EFFECTS: check if the board is valid
bool Solver::isValid() {
	int nums[9];
	auto _reset = [](int nums[]) -> void {
		for (size_t i = 0; i < 9; ++i) {
			nums[i] = 0;
		}
	};
	_reset(nums);
	auto check = [](int nums[]) -> bool {
		for (size_t i = 0; i < 9; ++i) {
			if (nums[i] > 1) return false;
		}
		return true;
	};
	// check for each col and row
	for (size_t i = 0; i < 9; ++i) {
		// col
		for (size_t j = 0; j < 9; ++j) {
			if(_board[i][j] != '.') ++nums[_board[i][j] - '1'];
		}
		if (!check(nums)) return false;
		_reset(nums);
		// row
		for (size_t j = 0; j < 9; ++j) {
			if (_board[j][i] != '.') ++nums[_board[j][i] - '1'];
		}
		if (!check(nums)) return false;
		_reset(nums);
	}
	// now check for each of the squares
	for (size_t i = 0; i < 9; i += 3) {
		for (size_t j = 0; j < 9; j += 3) {
			for (size_t k = 0; k < 3; ++k) {
				for (size_t l = 0; l < 3; ++l) {
					if (_board[i + k][j + l] != '.') ++nums[_board[i + k][j + l] - '1'];
				}
			}
			if (!check(nums)) return false;
			_reset(nums);
		}
	}
	return true;
}

// REQUIREMENTS: nothing
// MODIFIES: nothing
// EFFECTS: prints out the board
void Solver::print() const {
	for (const auto& i : _board) {
		for (const auto& j : i) {
			cout << j << ' ';
		}
		cout << '\n';
	}
	cout << flush;
}

// REQUIREMENTS: nothing
// MODIFIES: nothing
// EFFECTS: prints out the board with numbers on the side
void Solver::print_nums() const {
	cout << "    ";
	for (size_t i = 0; i < 9; ++i) {
		cout << i + 1 << ' ';
	}
	cout << "\n    _________________\n";
	for (size_t i = 0; i < 9; ++i) {
		cout << i + 1 << "  |";
		for (const auto& j : _board[i]) {
			cout << j << ' ';
		}
		cout << '\n';
	}
	cout << flush;
}

// REQUIREMENTS: the two positions of the board
// MODIFIES: board
// EFFECTS: searches for possible solutions given the position
// RETURNS: if there is a solution to the board
bool Solver::checkPos(size_t i, size_t j) {
	if (j == 9) {
		++i;
		j = 0;
	}
	if (i == 9) return true;
	auto checkValid = [i,j](const char& val, Solver::bvector& _board) -> bool {
		// check col and row
		for (char k = 0; k < 9; ++k) {
			if (_board[k][j] == val || _board[i][k] == val) return false;
		}
		// check square
		char m = i - (i % 3), n = j - (j % 3);
		for (char k = 0; k < 3; ++k) {
			for (char l = 0; l < 3; ++l) {
				if (_board[m][n] == val) return false;
				++n;
			}
			n = j - (j % 3);
			++m;
		}
		return true;
	};
	if (_board[i][j] == '.') {
		for (char val = '1'; val <= '9'; ++val) {
			if (checkValid(val,_board)) {
				_board[i][j] = val;
				if (checkPos(i, j + 1)) return true;
			}
		}
	}
	else {
		return checkPos(i, ++j);
	}
	_board[i][j] = '.';
	return false;
}

// REQUIREMENTS: the correct input
// MODIIFES: nothing
// EFFECTS: returns the value that was inputted
int Solver::inputHelper() {
	char val;
	cin >> val;
	while (val < '1' || val > '9') {
		cout << "You did not enter a number. Please enter a number from 1-9" << endl;
		cin >> val;
	}
	return (int) (val - '1' + 1);
}

// REQUIREMENTS: nothing
// MODIFIES: nothing
// EFFECTS: returns the board that is used to store the data
Solver::bvector& Solver::getBoard() {
	return _board;
}