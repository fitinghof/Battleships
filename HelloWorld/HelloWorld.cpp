#include <limits>
#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <windows.h>
#include <fstream>


int carrier[2] = { 2,4 };
int cruiser[2] = { 1,3 };
int destroyer[2] = { 1,2 };
int smallboat[2] = { 1,1 };
int ships[8][8] = { //the board
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0}
};
std::string visualboard[9][10] = {
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

int row,column;
int hits = 0;
int turns = 1;
int shipnumber = 0;
int text_line_chooser = 0;

char inputmenu;
char input[2] = {};
char numbers[8] = {
	'1','2','3','4','5','6','7','8'
};
char alphabet[8] = {
	'a','b','c','d','e','f','g','h'
};

std::string battleships = "______       _   _   _           _     _\n| ___ \\     | | | | | |         | |   (_)\n| |_/ / __ _| |_| |_| | ___  ___| |__  _ _ __  ___\n| ___ \\/ _` | __| __| |/ _ \\/ __| \'_ \\| | \'_ \\/ __|\n| |_/ / (_| | |_| |_| |  __/\\__ \\ | | | | |_) \\__ \\ \n\\____/ \\__,_|\\__|\\__|_|\\___||___/_| |_|_| .__/|___/\n                                        | |        \n		    		        |_|\n";
std::string boat = "			       __/___\n			 _____/______|\n		 _______/_____\\_______\\_____\n		 \\              < < <       |\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

//functions
void fireandmark() {
	while (true) {
		row = 0;
		column = 0;
        std::cin >> input;
		for (int i = 0; i < 9 && alphabet[i] != input[0]; ++i) {
			column = i+1;
		}
		for (int i = 0; i < 9 && numbers[i] != input[1]; ++i) {
			row = i+1;
		}

		if (row > 7 || column > 7 || row < 0 || column < 0) {
			text_line_chooser = 1; //invalid input
			continue;
		}
		break;
	}
	if (ships[row][column] == 2) {text_line_chooser = 2; //already shot here
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
            std::cout << visualboard[i][j] << " ";
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
        std::cout << "invalid input, try again\n\n";
	}
	else if (text_line_chooser == 2) {
        std::cout << "You already shot here try again\n\n";
	}
	else if (text_line_chooser == 3) {
        std::cout << "Hit!\n\n";
	}
	else if (text_line_chooser == 4) {
        std::cout << "You missed! Try again\n\n";
	}
}
void createship(int a[] = {}) {
    while (true) {
        srand((unsigned)time(NULL));
        int z = rand() % 2;
        int x = (rand() % 8) - a[0] + 1;
        int y = (rand() % 8) -a[1] + 1;
        if (z == 1) {
            std::swap(a[1], a[0]);
        }
        bool canPlace = true;
        for (int i = 0; i < a[0]; i++) {
            for (int j = 0; j < a[1]; j++) {
                int row = x + i;
                int col = y + j;

                if (row < 0 || row >= 7 || col < 0 || col >= 7 || ships[row][col] != 0) {
                    canPlace = false;
                    break;
                }
            }
            if (canPlace) {
                for (int i = 0; i < a[0]; i++) {
                    for (int j = 0; j < a[1]; j++) {
                        ships[x + i][y + j] = 1;
                    }
                }
                break;
            }
        }

        if (canPlace) {           
            break;
        }
    }
}


std::string inputstring = "n"; // input string
std::string text; // string used for getline() function
std::string names[1000]; // string that is used to load all the names from the playerlist file

int i = 0; // simple counter int
int namechoice; // used to store which character you choosed 

bool filefail = false; // used to indicate a file has failed loading, being created or similar

class player {
public:
    std::string name;
    int wins;
    int losses;
    player() : wins(0), losses(0) {}

};

player newplayer; // temporary storage of plater data
player player1;
player player2;

void saveplayer(const player& p) {

    std::ofstream playerfile(p.name + ".txt");
    if (playerfile.is_open() && !p.name.empty()) {
        playerfile << p.name << "\n" << p.wins << "\n" << p.losses;
        playerfile.close();
        std::cout << p.name << ": Save successfull\n";

    }
    else if (p.name.empty()) {
        std::cout << "Player 2: No data to save, skipped\n";

    }
    else std::cout << p.name << " save failed, try again\n";

}
void createplayer(player& p) {
    std::cout << "Enter name\n";

    while (true) {
        std::cin.ignore();
        getline(std::cin, inputstring);
        std::ofstream playerlist("playernames.txt", std::ios::app);

        if (playerlist.is_open()) {
            playerlist << inputstring << "\n";
            playerlist.close();

            std::ofstream playerfile(inputstring + ".txt");

            if (playerfile.is_open()) {
                p.name = inputstring;
                p.wins = 0;
                p.losses = 0;
                playerfile << p.name << "\n" << p.losses << "\n" << p.wins;
                playerfile.close();
                break;
            }
            else std::cout << "file creation failed, try again";

        }
        else std::cout << "file creation failed, try again";

    }
}
void loadplayer(player& p) {
    while (true) {
        std::cout << "Which one is you? type the number.\n";
        while (true) {
            std::ifstream playerlist("playernames.txt", std::ios::in);
            if (playerlist.is_open()) {
                while (getline(playerlist, text)) {
                    i++;
                    names[i] = text;
                    std::cout << i << " " << text << std::endl;
                }
                playerlist.close();
                break;
            }
        }

        //makes sure input is valid
        while (true) {
            filefail = false;
            std::cin >> namechoice;
            if (!std::cin.fail() && !(namechoice > i) && !(namechoice < 1)) {
                std::cin.clear();
                break;
            }
            std::cin.clear();
            std::cout << "invalid input, input must be a number listed on the screen.\n";
        }

        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

        //makes sure playerfile opens
        int retries = 0;
        while (true) {
            std::ifstream playerfile(names[namechoice] + ".txt");
            if (playerfile.is_open()) {
                playerfile >> p.name >> p.wins >> p.losses;
                break;


                retries++;

                if (retries > 3) {
                    std::cout << "opening playerfile failed. \nDo you want to create a new player?";
                    std::cin >> input;
                    while (true) {
                        std::cin >> input;
                        if (input == "Y" || input == "y" || input == "yes" || input == "Yes") {
                            createplayer(player1);
                            return;
                        }
                        else if (input == "N" || input == "n" || input == "no" || input == "No") {
                            filefail = true;
                            break;
                        }
                        else std::cout << "invalid input try again";
                    }
                }
            }


        }

        if (!filefail) { // if there isn't a filefail, this makes sure the loop isn't repeated
            break;
        }
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
	while(true) {
    std::cout << "Have you played before? Y/N\n\n";

    while (true) {
        std::cin >> inputstring;
        if (inputstring == "Y" || inputstring == "y" || inputstring == "yes" || inputstring == "Yes") {
            loadplayer(player1);
            break;
        }
        else if (inputstring == "N" || inputstring == "n" || inputstring == "no" || inputstring == "No") {
            createplayer(player1);

            break;
        }
        else std::cout << "invalid input try again";
    }

    std::cout << battleships << boat << "Hi " << player1.name << "!\n\nDo you want to play agains the (C)omputer or (S)witch player 1? \n"; // << "What do you want to do\n\nPlay against (P)layer\nPlay against (C)omputer\n(Q)uit\n\n"

    std::cin >> inputmenu;

	if (inputmenu == 'C' || inputmenu == 'c') {
        createship(carrier);
        createship(cruiser);
        createship(cruiser);
        createship(cruiser);
        createship(destroyer);
        createship(destroyer);
        createship(destroyer);
        createship(smallboat);
        createship(smallboat);
        createship(smallboat);
        createship(smallboat);

        
        shipcounter();
		while (hits < shipnumber) {
			clear_screen();
            std::cout << "Turn:" << turns << "\nYou need to sink " << shipnumber << " ships to win!\n\n";
			print_hit_result();

			print_board();
            for (int i = 0; i < 8; i++) {
                std::cout<<"\n";
                for (int j = 0; j < 8; j++) {
                    std::cout << ships[i][j] << " ";
                }
            };

            std::cout << "\n\nYou have sunk " << hits << " out of " << shipnumber << " ships.\nPlease enter where to shoot\n\n";

			fireandmark();
		}
        std::cout << "\n\nYou Win! It took " << turns << " turns to sink all ships";
        player1.wins++;
	}
	
    }
    saveplayer(player1);
    return 0;
}

	
