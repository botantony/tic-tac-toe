// import libraries (printf, scanf, string support, booleans)
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// define a new Enum type for a cell in the grid
// each cell has 3 states: EMPTY, CROSS, CIRCLE
typedef enum {
	EMPTY,
	CROSS,
	CIRCLE,
} Cell;

// this function prints a grid
// "." - empty, "x" - cross, "o" - circle
// print "?" if it doesn't match any of the above
void printGrid(Cell** grid) {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			switch (grid[i][j]) {
				case EMPTY:
					printf(".");
					break;
				case CROSS:
					printf("x");
					break;
				case CIRCLE:
					printf("o");
					break;
				default:
					printf("?");
					break;
			}
		}
		printf("\n");
	}
}

// function with main game cycle
// args: pointer to a grid array, user input, "isCircle" bool, pointer to the victory flag
void mainGameCycle(Cell** grid, char input[3], bool isCircle, bool* victory) {
	// print error for incorrect input
	// first and second characters must be either 1, 2, or 3
	if (!((input[0] == '1' || input[0] == '2' || input[0] == '3')
		&&
		(input[1] == '1' || input[1] == '2' || input[1] == '3'))) { 
		printf("Incorrect input! Use the following format: <Row><Col>!\n");
		return;
	}
	// get the number of the row and the column from the input
	// "char" is basically an integer, so by subtracting '1' from the character we get the number minus 1
	// eg: '9' - '1' == 8, since '9' == 57 and '1' == 49
	int row = input[0] - '1';
	int col = input[1] - '1';
	// check if the row we choose is not empty
	if (grid[row][col] != EMPTY) {
		printf("This cell is already taken!\n");
		return;
	}
	// determine what we should add to the grid using "isCircle" boolean
	if (isCircle) {
		grid[row][col] = CIRCLE;
	} else {
		grid[row][col] = CROSS;
	}
	printGrid(grid);
	Cell currPlayer = isCircle ? CIRCLE : CROSS;
	// check win conditions
	for (int i = 0; i < 3; ++i) {
		// check each row
		if (grid[i][0] == currPlayer && grid[i][1] == currPlayer && grid[i][2] == currPlayer) {
			printf("The player \"%c\" won!\n", isCircle ? 'o' : 'x');
			*victory = true;
			return;
		}
		// check each column
		if (grid[0][i] == currPlayer && grid[1][i] == currPlayer && grid[2][i] == currPlayer) {
			printf("The player \"%c\" won!\n", isCircle ? 'o' : 'x');
			*victory = true;
			return;
		}
		// check diagonals
		if (grid[0][0] == currPlayer && grid[1][1] == currPlayer && grid[2][2] == currPlayer) {
			printf("The player \"%c\" won!\n", isCircle ? 'o' : 'x');
			*victory = true;
			return;
		}
		if (grid[2][0] == currPlayer && grid[1][1] == currPlayer && grid[0][2] == currPlayer) {
			printf("The player \"%c\" won!\n", isCircle ? 'o' : 'x');
			*victory = true;
			return;
		}
	}
}

int main() {
	// the string has 3 characters because the last one must be a "null" symbol \0
	// in C this symbol determines the end of a string
	char input[3];
	bool validInput = false;
	bool isCircle = false;
	bool victory = false;

	printf("Press `q` and hit Enter if you want to quit the game.\n\n");
	printf("Print 2 numbers from 1 to 3 (including). The first number is the row, the second one is the column.\n");
	printf("F.e.: \"12\" respond for the first row and the second column.\n");
	printf("The turn switches every round, you start as X player.\n");
	// allocate memory for the "Cell" 2D array (grid)
	// we need to use pointers here because we want to change the value of this
	// array in "mainGameCycle()" function
	Cell** grid = (Cell**)malloc(3*sizeof(Cell*));
	for (int i = 0; i < 3; ++i) {
		grid[i] = (Cell*)malloc(sizeof(Cell));
	}

	// fill the grid with emptry cells
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			grid[i][j] = EMPTY;
		}
	}
	// infinite cycle
	while (true) {
		// end the game if one of the players won
		if (victory) {
			// free allocated memory
			for (int i = 0; i < 3; ++i) {
				free(grid[i]);
			}
			free(grid);
			return 0;
		}
		// wait for the user input
		printf(">> ");
		scanf("%2s", input);
		// end the game if the player entered "q"
		if (strcmp(input, "q") == 0)  {
			// free allocated memory
			for (int i = 0; i < 3; ++i) {
				free(grid[i]);
			}
			free(grid);
			return 0;
		}
		mainGameCycle(grid, input, isCircle, &victory);
		// swap the boolean "isCircle"
		// by doing this each round this variable will change
		isCircle = !isCircle;
	}
}
