#include<bits/stdc++.h>

using namespace std;

#define SIZE 8 // Size of board;
#define FILLED 1 // Used to fill board
#define DIFF 8   // Used to differs first filled square

int board[SIZE][SIZE] = {0};

struct Point {
	int x, y;
};

struct Tile {
	int size; // Tile size
	Point p;  // Missing point 
	Point start; // Where tile starts
};

Tile bigTile;

// Add a missing point and define bigTile ( that covers the whole board ).
void startBoard() {
	Point missing = {4, 5};		// Define here the missing point position
	Point start = {0, 0};		// Define the point (0, 0) as start
	bigTile.size = SIZE;		// Same as the board size
        bigTile.p = missing;
	bigTile.start = start;
	board[missing.x][missing.y] = DIFF; // Fill the missing point with DIFF
}

// Print current situation of the board
void printBoard() {
	cout << endl;
	for( int j = 0; j < SIZE; ++j ) {
		for( int i = 0; i < SIZE; ++i )
			cout << board[i][j] << " ";
		cout << endl;
	}

	cin.get();	// Press some key before continue
}

// Recursive function that uses divide and conquer
void divideAndConquer(Tile & tile) {
	int sX = tile.start.x;
	int sY = tile.start.y;
	int size = tile.size;

	// Base case. Must filout missing squares.
	if( tile.size == 2 ) {
		for ( int j = sY; j < sY + size; ++j )
			for( int i = sX; i < sX + size; ++i )
				if ( tile.p.x != i || tile.p.y != j ) 
					board[i][j] = FILLED;
		printBoard();
	} else {
		// Locate the missing square
		int newSize = tile.size / 2;
		int left = ( tile.p.x < tile.start.x + newSize );
		int up	= ( tile.p.x < tile.start.y + newSize );

		// Place the L shape tile at center. Subdivide tile in 4.
		// Defining center points
		Point	p1 = {sX + newSize - 1 , sY + newSize - 1},
			p2 = {sX + newSize     , sY + newSize - 1},
			p3 = {sX + newSize - 1 , sY + newSize    },
			p4 = {sX + newSize     , sY + newSize    };

		// Defining starting points
		Point s1 = {sX, sY},
		      s2 = {sX + newSize, sY},
		      s3 = {sX, sY + newSize},
		      s4 = {sX + newSize, sY + newSize};

		// Defining tiles
		Tile  t1 = { newSize, p1, s1 },
		      t2 = { newSize, p2, s2 },
		      t3 = { newSize, p3, s3 },
		      t4 = { newSize, p4, s4 };
		
		
		// Taking back the one that already exists
		if( left && up )
			t1.p = tile.p;
		else if ( ~left && up )
			t2.p = tile.p;
		else if ( left && ~up )
			t3.p = tile.p;
		else if ( ~left && ~up )
			t4.p = tile.p;

		// Call recursively for following four subsquares
		divideAndConquer( t1 );
		divideAndConquer( t2 );
		divideAndConquer( t3 );
		divideAndConquer( t4 );

		// Fill the center
		if( left && up ) {
			//board[p1.x][p1.y] = FILLED;
			board[p2.x][p2.y] = FILLED;
			board[p3.x][p3.y] = FILLED;
			board[p4.x][p4.y] = FILLED;
		} else if ( ~left && up ) {
			board[p1.x][p1.y] = FILLED;
			//board[p2.x][p2.y] = FILLED;
			board[p3.x][p3.y] = FILLED;
			board[p4.x][p4.y] = FILLED;
		} else if ( left && ~up ) {
			board[p1.x][p1.y] = FILLED;
			board[p2.x][p2.y] = FILLED;
			//board[p3.x][p3.y] = FILLED;
			board[p4.x][p4.y] = FILLED;
		} else if ( ~left && ~up ) {
			board[p1.x][p1.y] = FILLED;
			board[p2.x][p2.y] = FILLED;
			board[p3.x][p3.y] = FILLED;
			//board[p4.x][p4.y] = FILLED;
		}
		printBoard();
	}	
}


int main() {
	cout << "Starting to fill board up..." << endl;

	startBoard();
	printBoard();
	divideAndConquer(bigTile);

	cout << endl << "All board was filled!" << endl;
	return 0;
}
