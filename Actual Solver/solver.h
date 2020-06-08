// To prohibit this file from being used more than once
#ifndef SOLVER_H
#define SOLVER_H

// Adding all the necessary files for this project
#include <vector>
#include <iostream>

using namespace std;

class Solver {
public:
	// To save typing space
	using bvector = vector<vector<char>>;

	// Creates the solver (default constructor)
	// REQUIREMENTS: nothing
	// MODIFIES: object
	// EFFECTS: creates the object
	Solver();

	// REQUIREMENTS: the board
	// MODIFIES: object
	// EFFECTS: creates the object with the specified board
	//   Will also destroy the board as specified
	Solver(bvector& board);

	// REQUIREMENTS: the board
	// MODIFIES: object
	// EFFECTS: creates the object with the specified board
	//   will not change the board put in
	Solver(const bvector& board);

	// REQUIRMENETS: the board stored is an actual board
	// MODIFIES: board
	// EFFECTS: solves the soduko puzzle by filling in all the blanks
	// RETURNS: if there is a solution to the board
	bool solve();

	// REQUIREMENTS: a board is inputted
	// MODIFES: the board inputted
	// EFFECTS: modifies to make the board solved
	// RETURNS: if there is a solution to the board
	bool solve(bvector& board);

	// REQUIRMENTS: correct input
	// MODIFIES: board
	// EFFECTS: inputs new values into the soduko puzzle
	void inputNewBoard();

	// REQUIREMENTS: correct input
	// MODIFIES: board
	// EFFECTS: prompts the user to input new values
	void inputNewValue();

	// REQUIREMENTS: the coordinates of the point to change (from 0 - 8)
	// MODIFIES: board
	// EFFECTS: changes the board at the value specified
	void inputNewValue(const size_t& i, const size_t& j, const char& val);

	// REQUIREMENTS: the coordiantes of the point to change (from 1 - 9)
	// MODIFIES: board
	// EFFECTS: changes the board at the value specified
	void inputNewValue(const int& i, const int& j, const char& val);

	// REQUIREMENTS: nothing
	// MODIFIES: nothing
	// EFFECTS: check if the board is valid
	bool isValid();

	// REQUIREMENTS: nothing
	// MODIFIES: nothing
	// EFFECTS: prints out the board
	void print() const;

	// REQUIREMENTS: nothing
	// MODIFIES: nothing
	// EFFECTS: prints out the board with numbers on the side
	void print_nums() const;

	// REQUIREMENTS: nothing
	// MODIFIES: nothing
	// EFFECTS: returns the board that is used to store the data
	bvector& getBoard();
private:
	// the board that stores all the information
	bvector _board;

	// REQUIREMENTS: the two positions of the board
	// MODIFIES: board
	// EFFECTS: searches for possible solutions given the position
	// RETURNS: if there is a solution to the board
	bool checkPos(size_t i, size_t j);

	// REQUIREMENTS: the correct input
	// MODIIFES: nothing
	// EFFECTS: returns the value that was inputted
	int inputHelper();
};

#endif