#include <limits>
#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <windows.h>
#include <fstream>
#include <ctime>

int counter1 = 0;//debugging
int counter0 = 0;//debugging

int carrier[2] = { 2,4 }; //Different ship sizeas
int cruiser[2] = { 1,3 };
int destroyer[2] = { 1,2 };
int smallboat[2] = { 1,1 };

const int boardsize = 10;
int ships[boardsize][boardsize] = { 0 }; //the board

int visualboard[boardsize][boardsize] = { 0 };

int row,column;
int hits = 0;
int turns = 1;
int shipnumber = 0;
int text_line_chooser = 0;

char inputmenu;
std::string input;

char alphabet[25] = {
	'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','x','y','z'
};



std::string battleships = "______       _   _   _           _     _\n| ___ \\     | | | | | |         | |   (_)\n| |_/ / __ _| |_| |_| | ___  ___| |__  _ _ __  ___\n| ___ \\/ _` | __| __| |/ _ \\/ __| \'_ \\| | \'_ \\/ __|\n| |_/ / (_| | |_| |_| |  __/\\__ \\ | | | | |_) \\__ \\ \n\\____/ \\__,_|\\__|\\__|_|\\___||___/_| |_|_| .__/|___/\n                                        | |        \n		    		        |_|\n";
std::string boat = "			       __/___\n			 _____/______|\n		 _______/_____\\_______\\_____\n		 \\              < < <       |\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

//functions
void fireandmark() {
    while (true) {
        row = 0;
        column = 0;
        std::cin >> input;

        if (input.size() < 2) {
            continue;
        }

        char colChar = input[0];
        char rowChar = input[1];

        int colIndex = -1;
        for (int i = 0; i <= boardsize; ++i) {
            if (alphabet[i] == colChar) {
                colIndex = i;
                break;
            }
        }

        if (colIndex == -1) {
            text_line_chooser = 1; // invalid input
            continue;
        }

        int rowNumber = rowChar - '0';
        if (input.length() == 3) {
            rowNumber = (rowChar - '0') * 10 + (input[2] - '0');
        }

        row = rowNumber - 1; // Convert to 0-based index
        column = colIndex;

        if (row >= boardsize || column >= boardsize || row < 0 || column < 0) {
            text_line_chooser = 1; // invalid input
            continue;
        }

        break;
    }

    if (ships[row][column] == 2) {
        text_line_chooser = 2; // already shot here
    }
    else if (ships[row][column] == 1) {
        ships[row][column] = 2;
        hits++;
        visualboard[row][column] = 1;
        text_line_chooser = 3; // Hit
    }
    else {
        visualboard[row][column] = 2;
        ships[row][column] = 2;
        text_line_chooser = 4; // miss
        turns++;
    }
}
void print_board(int a[boardsize][boardsize]) {
 
    std::cout << "  a b c d e f g";
	for (int i = 0; i < boardsize; i++) {
        if (i > 8) {
            std::cout << "\n" << i + 1 << " ";
        }
        else std::cout << "\n" << i + 1 << "  ";        
        for (int j = 0; j < boardsize; j++) {
           
            switch (a[i][j]){
            case 0: 
                std::cout << 0 << " ";
                break;
            case 1:
                std::cout << "X ";
                break;
            case 2: 
                std::cout << "B ";
                break;
            }
		}
	};
}
int shipcounter() {
	for (int i = 0; i < boardsize; i++) {
		for (int j = 0; j < boardsize; j++) {
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
void createship(int a[], int b) {

    srand(static_cast<unsigned>(time(NULL)));
    int shipsplaced = 0;
    bool valid = true;
    int validslot[2][boardsize * boardsize * 5]{};
    int listcounter = 0;
    while (true) {
        int z;
            z = rand() % 100;
        if (z <= 50) { counter1++; }
        else counter0++;
        std::cout << z;
        if(z<=50) {
            for (int i = 0; i < (boardsize - a[0] + 1); i++) {
                for (int j = 0; j < (boardsize - a[1] + 1); j++) {
                    valid = true;
                    if (ships[i][j] == 0) {                      
                        for (int k = 0; k < a[0]; k++) {
                            for (int l = 0; l < a[1]; l++) {
                                if (!(ships[i + k][j + l] == 0)) {
                                    valid = false;
                                    continue;
                                }
                            }

                        }
                        if (!valid) {
                            continue;
                        }
                        if (valid) {
                            validslot[0][listcounter] = i;
                            validslot[1][listcounter] = j;
                            listcounter++;
                        }
                    }
                    else if (ships[i][j] == 1) {
                        continue;
                    }

                }

            }
        }
        if (z <= 50) {
        int x = rand() % listcounter;
            for (int i = 0; i < (a[0]); i++) {
                for (int j = 0; j < a[1]; j++) {
                    ships[validslot[0][x] + i][validslot[1][x] + j] = 1;
                }
            }       
        }

        if (z > 50) {
            for (int i = 0; i < (boardsize - a[1] + 1); i++) {
                for (int j = 0; j < (boardsize - a[0] + 1); j++) {
                    valid = true;
                    if (ships[i][j] == 0) {                    
                        for (int k = 0; k < a[1]; k++) {
                            for (int l = 0; l < a[0]; l++) {
                                if (!(ships[i + k][j + l] == 0)) {
                                    valid = false;
                                    continue;
                                }
                            }

                        }
                        if (!valid) {
                            continue;
                        }
                        if (valid) {
                            validslot[0][listcounter] = i;
                            validslot[1][listcounter] = j;
                            listcounter++;
                        }
                    }
                    else if (ships[i][j] == 1) {
                        continue;
                    }

                }

            }
        }
        if (z > 50) {
            int x = rand() % listcounter;
                for (int i = 0; i < (a[1]); i++) {
                    for (int j = 0; j < a[0]; j++) {
                        ships[validslot[0][x] + i][validslot[1][x] + j] = 1;
                    }
                }
           

        }
        std::cout << "\n";
            for (int i = 0; i < boardsize; i++) {//debugging
                std::cout << "\n";
                for (int j = 0; j < boardsize; j++) {
                    std::cout << ships[i][j] << " ";
                }
            };

            shipsplaced++;
            if (shipsplaced == b || listcounter == 0) {
                return;
            }
            listcounter = 0;
        
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
       createship(carrier,1);
       createship(cruiser, 3);
       createship(destroyer,4);       
       createship(smallboat,5);
        std::cout << counter0 << " " << counter1;//debugging

        shipnumber = 0;
        shipcounter();
		while (hits < shipnumber) {
			//clear_screen();
            std::cout << "Turn:" << turns << "\nYou need to sink " << shipnumber << " ships to win!\n\n";
			print_hit_result();

			print_board(visualboard);
            

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

	
