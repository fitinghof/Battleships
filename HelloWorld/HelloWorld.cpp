#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <windows.h>
#include <fstream>

using namespace std;

int ships[8][8] = { //the board
{0,0,0,0,1,1,0,1},
{0,1,1,0,0,0,0,1},
{0,0,0,0,1,0,0,0},
{0,0,0,0,1,1,1,1},
{1,0,0,0,1,0,0,0},
{0,0,0,0,0,0,0,0},
{1,1,1,1,0,0,0,0},
{1,1,1,1,0,0,0,1}
};
string visualboard[9][10] = {
{"   ", " a","b","c","d","e","f","g","h","\n"},
{"1  ", "O","O","O","O","O","O","O","O","\n"},
{"2  ", "O","O","O","O","O","O","O","O","\n"},
{"3  ", "O","O","O","O","O","O","O","O","\n"},
{"4  ", "O","O","O","O","O","O","O","O","\n"},
{"5  ", "O","O","O","O","O","O","O","O","\n"},
{"6  ", "O","O","O","O","O","O","O","O","\n"},
{"7  ", "O","O","O","O","O","O","O","O","\n"},
{"8  ", "O","O","O","O","O","O","O","O","\n"}
};

class player {
public:
	string name;
	int win_loss = wins / losses;
	int wins;
	int losses;
};
player player1;
player player2;
string name;

int row,column;
int hits = 0;
int turns = 0;
int shipnumber = 0;
int text_line_chooser = 0;
bool player_on = false;

char inputmenu;
char input[2] = {};
char numbers[8] = {
	'1','2','3','4','5','6','7','8'
};
char alphabet[8] = {
	'a','b','c','d','e','f','g','h'
};

string battleships = "______       _   _   _           _     _\n| ___ \\     | | | | | |         | |   (_)\n| |_/ / __ _| |_| |_| | ___  ___| |__  _ _ __  ___\n| ___ \\/ _` | __| __| |/ _ \\/ __| \'_ \\| | \'_ \\/ __|\n| |_/ / (_| | |_| |_| |  __/\\__ \\ | | | | |_) \\__ \\ \n\\____/ \\__,_|\\__|\\__|_|\\___||___/_| |_|_| .__/|___/\n                                        | |        \n		    		        |_|\n";
string boat = "			       __/___\n			 _____/______|\n		 _______/_____\\_______\\_____\n		 \\              < < <       |\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

//functions
void hit_registerer() {
	for (int i = 0; i < 9 && alphabet[i] != input[0]; i++) {
		column = i + 1;
	}
	for (int i = 0; i < 9 && numbers[i] != input[1]; i++) {
		row = i + 1;
	}

	if (row > 7 || column > 7 || row < 0 || column < 0) {
		text_line_chooser = 1; //invalid input
	}
	else if (ships[row][column] == 2) {text_line_chooser = 2; //already shot here
	}
	else if (ships[row][column] == 1) {
		ships[row][column] = 2; hits++; visualboard[row + 1][column + 1] = "X"; text_line_chooser = 3; //Hit
	}
	else {
		visualboard[row + 1][column + 1] = "B"; ships[row][column] = 2; text_line_chooser = 4; turns++; //miss
	}
}
void print_board() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 10; j++) {
			cout << visualboard[i][j] << " ";
		}
	};
}
int shipcounter() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			{if (ships[i][j] == 1) { shipnumber++; }
			}
		}
	}
	return shipnumber;
}
void clear_screen(char fill = ' ') {
	COORD tl = { 0,0 };
	CONSOLE_SCREEN_BUFFER_INFO s;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(console, &s);
	DWORD written, cells = s.dwSize.X * s.dwSize.Y;
	FillConsoleOutputCharacter(console, fill, cells, tl, &written);
	FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
	SetConsoleCursorPosition(console, tl);
}
void print_hit_result() {
	if (text_line_chooser == 1) {
		cout << "invalid input, try again\n\n";
	}
	else if (text_line_chooser == 2) {
		cout << "You already shot here try again\n\n";
	}
	else if (text_line_chooser == 3) {
		cout << "Hit!\n\n";
	}
	else if (text_line_chooser == 4) {
		cout << "You missed! Try again\n\n";
	}
}

/*
______       _   _   _           _     _           
| ___ \     | | | | | |         | |   (_)          
| |_/ / __ _| |_| |_| | ___  ___| |__  _ _ __  ___ 
| ___ \/ _` | __| __| |/ _ \/ __| '_ \| | '_ \/ __|
| |_/ / (_| | |_| |_| |  __/\__ \ | | | | |_) \__ \
\____/ \__,_|\__|\__|_|\___||___/_| |_|_| .__/|___/
                                        | |        
                                        |_| 
						__/___
				  _____/______|
		 _______/_____\_______\_____
		 \              < < <       |
		~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

*/

int main() {
	/*srand((unsigned)time(NULL));
	for (int q = 0; q < 8 && shipnumber<20; q++) {
		for (int w = 0; w < 8; w++) {
			ships[q][w] = rand() % 2;
			shipnumber = shipnumber + ships[q][w];
		}
	}
	trash random boat position generator ^
	*/


	cout << battleships << boat; // << "What do you want to do\n\nPlay against (P)layer\nPlay against (C)omputer\n(Q)uit\n\n";
	
	cin >> inputmenu;

	if (inputmenu == 'C' || inputmenu == 'c') {
		// add computer generated board
		shipcounter();

		while (hits < shipnumber) {
			clear_screen();
			cout << "Turn:" << turns << "\nYou need to sink " << shipnumber << " ships to win!\n\n";
			print_hit_result();

			print_board();
			cout << "\n\nYou have sunk " << hits << " out of " << shipnumber << " ships.\nPlease enter where to shoot\n\n";

			cin >> input;

			hit_registerer();
		}


		cout << "\n\nYou Win! It took " << turns << " turns to sink all ships";
	}
	return 0;
}

	
