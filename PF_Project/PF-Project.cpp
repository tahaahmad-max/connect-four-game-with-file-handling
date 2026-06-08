#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <limits>

// ANSI Escape Codes for Text Colors
#define RESET   "\033[0m"
#define RED     "\033[91m"     // Player X
#define CYAN    "\033[96m"     // Player O
#define YELLOW  "\033[93m"     // Alerts / Turn Indicator
#define GREEN   "\033[92m"     // Wins / Success
#define BLUE    "\033[34m"     // Board Frame
#define MAGENTA "\033[95m"     // Menu Titles

// Function Prototypes
void show_game();
void game_check();
void record();

// Global Variables  *** FIXED: declared as proper arrays ***
char game[6][7];      // was: char game;
int  r_col[7];        // was: int r_col;
char turn;
std::string name_1;
std::string name_2;
int count_for_X = 0;
int count_for_O = 0;
bool flag = false;
bool flag1 = false;

int main()
{
    int col;
    srand((unsigned int)time(0));
    int for_turn;
    int choice;

    std::cout << MAGENTA << "\t--------------------" << std::endl;
    std::cout << "\t--------------------" << std::endl;
    std::cout << "\t||  CONNECT FOUR  ||" << std::endl;
    std::cout << "\t||      GAME      ||" << std::endl;
    std::cout << "\t--------------------" << std::endl;
    std::cout << "\t-------------------- \n\n\n" << RESET;

    do
    {
        std::cout << BLUE << "-----------------------\n" << RESET;
        std::cout << BLUE << "|                     |\n" << RESET;
        std::cout << BLUE << "|     " << MAGENTA << "-----------" << BLUE << "     |\n" << RESET;
        std::cout << BLUE << "|    " << MAGENTA << "|| M E N U ||" << BLUE << "    |\n" << RESET;
        std::cout << BLUE << "|     " << MAGENTA << "-----------" << BLUE << "     |\n" << RESET;
        std::cout << BLUE << "|                     |\n" << RESET;
        std::cout << BLUE << "| " << YELLOW << "1." << RESET << "  Play Game.      " << BLUE << "|\n" << RESET;
        std::cout << BLUE << "| " << YELLOW << "2." << RESET << "  Credits.        " << BLUE << "|\n" << RESET;
        std::cout << BLUE << "| " << YELLOW << "3." << RESET << "  Instructions.   " << BLUE << "|\n" << RESET;
        std::cout << BLUE << "| " << YELLOW << "4." << RESET << "  Record.         " << BLUE << "|\n" << RESET;
        std::cout << BLUE << "| " << RED << "5." << RESET << "  Exit.           " << BLUE << "|\n" << RESET;
        std::cout << BLUE << "-----------------------\n\n" << RESET;
        std::cout << "Enter your choice : ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            system("cls");
            std::cout << RED << "Invalid Input! Please enter a number.\n" << RESET << std::endl;
            choice = 0;
            continue;
        }

        // Reset state for a new game
        for (int i = 0; i < 7; i++) {
            r_col[i] = 5;        // bottom-most available row index per column
        }
        flag = false;
        flag1 = false;
        count_for_X = 0;
        count_for_O = 0;

        switch (choice)
        {
        case 1:
            std::cout << "\nEnter Name of Player " << RED << "X" << RESET << " : ";
            std::cin >> name_1;
            std::cout << "Enter Name of Player " << CYAN << "O" << RESET << " : ";
            std::cin >> name_2;

            std::cout << "\n[ TOSS ] -> ";
            for_turn = (rand() % 2) + 1;
            if (for_turn == 1)
            {
                std::cout << GREEN << "Won by " << RED << name_1 << " (X)" << RESET << ".\n" << std::endl;
                turn = 'X';
            }
            else
            {
                std::cout << GREEN << "Won by " << CYAN << name_2 << " (O)" << RESET << ".\n" << std::endl;
                turn = 'O';
            }

            // Clear board
            for (int i = 0; i < 6; i++)
                for (int j = 0; j < 7; j++)
                    game[i][j] = ' ';

            show_game();

            for (;;)
            {
                if (turn == 'X')
                {
                    std::cout << "\n" << RED << ">>" << RESET << " Player " << RED << "X" << RESET
                        << " turn (" << RED << name_1 << RESET << ")" << std::endl;
                    std::cout << "Enter Column (1 to 7) : ";

                    if (!(std::cin >> col)) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        system("cls");
                        std::cout << RED << "Invalid Input! Enter a number between 1 and 7.\n" << RESET << std::endl;
                        show_game();
                        continue;
                    }

                    if (col >= 1 && col <= 7)
                    {
                        int col_idx = col - 1;
                        if (r_col[col_idx] >= 0)
                        {
                            game[r_col[col_idx]][col_idx] = 'X';
                            r_col[col_idx]--;
                        }
                        else
                        {
                            system("cls");
                            std::cout << RED << "Column full! Try another column.\n" << RESET << std::endl;
                            show_game();
                            continue;
                        }
                    }
                    else
                    {
                        system("cls");
                        std::cout << RED << "Invalid Column! Enter 1 to 7.\n" << RESET << std::endl;
                        show_game();
                        continue;
                    }

                    system("cls");
                    count_for_X++;
                    show_game();
                    game_check();

                    if (flag)  break;
                    if (flag1)
                    {
                        std::ofstream handler("record.txt", std::ios::app);
                        handler << "Game has been draw between " << name_1 << " and " << name_2 << std::endl;
                        std::cout << YELLOW << "Game has been draw between " << name_1 << " and " << name_2 << RESET << std::endl;
                        break;
                    }
                    turn = 'O';
                }
                else // turn == 'O'
                {
                    std::cout << "\n" << CYAN << ">>" << RESET << " Player " << CYAN << "O" << RESET
                        << " turn (" << CYAN << name_2 << RESET << ")" << std::endl;
                    std::cout << "Enter Column (1 to 7) : ";

                    if (!(std::cin >> col)) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        system("cls");
                        std::cout << RED << "Invalid Input! Enter a number between 1 and 7.\n" << RESET << std::endl;
                        show_game();
                        continue;
                    }

                    if (col >= 1 && col <= 7)
                    {
                        int col_idx = col - 1;
                        if (r_col[col_idx] >= 0)
                        {
                            game[r_col[col_idx]][col_idx] = 'O';
                            r_col[col_idx]--;
                        }
                        else
                        {
                            system("cls");
                            std::cout << RED << "Column full! Try another column.\n" << RESET << std::endl;
                            show_game();
                            continue;
                        }
                    }
                    else
                    {
                        system("cls");
                        std::cout << RED << "Invalid Column! Enter 1 to 7.\n" << RESET << std::endl;
                        show_game();
                        continue;
                    }

                    system("cls");
                    count_for_O++;
                    show_game();
                    game_check();

                    if (flag)  break;
                    if (flag1)
                    {
                        std::ofstream handler("record.txt", std::ios::app);
                        handler << "Game has been draw between " << name_1 << " and " << name_2 << std::endl;
                        std::cout << YELLOW << "Game has been draw between " << name_1 << " and " << name_2 << RESET << std::endl;
                        break;
                    }
                    turn = 'X';
                }
            }

            std::cout << YELLOW << "----------" << std::endl;
            std::cout << "|End Game|" << std::endl;
            std::cout << "----------\n\n" << RESET;
            break;

        case 2:
            std::cout << CYAN
                << "----------------------------------\n"
                << "|                                |\n"
                << "|        -----------------       |\n"
                << "|        || C R E D I T S ||     |\n"
                << "|        -----------------       |\n"
                << "|                                |\n"
                << "| This Game is made by :         |\n"
                << "|                                |\n"
                << "| 1.  Taha Ahmad        23F-3040.|\n"
                << "| 2.  Rana Haseeb       23F-3096.|\n"
                << "| 3.  Jarrar Laeeq      22F-3334.|\n"
                << "----------------------------------\n\n" << RESET;
            break;

        case 3:
            std::cout << YELLOW
                << "---------------------------------------------------------------------------------------------------------------------------------------------------------------\n"
                << "| Instructions to Play the Game:                                                                                                                              |\n"
                << "|                                                                                                                                                             |\n"
                << "| 1. Choose a Letter (X or O).                                                                                                                                |\n"
                << "| 2. Take turns dropping a disc into any of the seven columns (1-7).                                                                                          |\n"
                << "| 3. Connect four of your discs horizontally, vertically, or diagonally to win.                                                                               |\n"
                << "| 4. Block your opponent while working towards your own four-in-a-row.                                                                                        |\n"
                << "| 5. The game ends when a player connects four or the board is full (draw).                                                                                   |\n"
                << "| 6. After the game ends, you can start a new game from the menu.                                                                                             |\n"
                << "| 7. Have fun!                                                                                                                                                |\n"
                << "---------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n" << RESET;
            break;

        case 4:
            std::cout << MAGENTA
                << "----------------------------------\n"
                << "|        -----------------       |\n"
                << "|        || R E C O R D S ||     |\n"
                << "|        -----------------       |\n"
                << "----------------------------------\n\n" << RESET;
            record();
            std::cout << std::endl;
            break;

        case 5:
            std::cout << GREEN << "Exiting Game. Goodbye!\n" << RESET;
            break;

        default:
            std::cout << RED << "Invalid Input. Please Input Again.\n\n" << RESET;
        }

    } while (choice != 5);

    return 0;
}

void show_game()
{
    std::cout << YELLOW << "  1   2   3   4   5   6   7  " << RESET << std::endl;
    std::cout << BLUE << "+---+---+---+---+---+---+---+" << RESET << std::endl;
    for (int i = 0; i < 6; i++)
    {
        std::cout << BLUE << "| " << RESET;
        for (int j = 0; j < 7; j++)
        {
            if (game[i][j] == 'X') std::cout << RED << 'X' << RESET;
            else if (game[i][j] == 'O') std::cout << CYAN << 'O' << RESET;
            else                         std::cout << ' ';

            std::cout << BLUE << " | " << RESET;
        }
        std::cout << std::endl;
        std::cout << BLUE << "+---+---+---+---+---+---+---+" << RESET << std::endl;
    }
}

void game_check()
{
    // 1. Horizontal
    for (int i = 0; i < 6; i++)
        for (int j = 0; j <= 3; j++)
            if (game[i][j] == turn && game[i][j + 1] == turn && game[i][j + 2] == turn && game[i][j + 3] == turn)
                flag = true;

    // 2. Vertical
    for (int i = 0; i <= 2; i++)
        for (int j = 0; j < 7; j++)
            if (game[i][j] == turn && game[i + 1][j] == turn && game[i + 2][j] == turn && game[i + 3][j] == turn)
                flag = true;

    // 3. Diagonal top-left to bottom-right
    for (int i = 0; i <= 2; i++)
        for (int j = 0; j <= 3; j++)
            if (game[i][j] == turn && game[i + 1][j + 1] == turn && game[i + 2][j + 2] == turn && game[i + 3][j + 3] == turn)
                flag = true;

    // 4. Diagonal bottom-left to top-right
    for (int i = 3; i < 6; i++)
        for (int j = 0; j <= 3; j++)
            if (game[i][j] == turn && game[i - 1][j + 1] == turn && game[i - 2][j + 2] == turn && game[i - 3][j + 3] == turn)
                flag = true;

    if (flag)
    {
        std::ofstream handler1("record.txt", std::ios::app);
        if (turn == 'X')
        {
            std::cout << GREEN << "\n=========================================" << std::endl;
            std::cout << " [WINNER] Game Won by X Player (" << RED << name_1 << GREEN << ")!" << std::endl;
            std::cout << " Total turns taken = " << count_for_X << std::endl;
            std::cout << "=========================================\n" << RESET << std::endl;
            if (handler1.is_open())
                handler1 << name_1 << " won as X player : in turns = " << count_for_X << std::endl;
        }
        else
        {
            std::cout << GREEN << "\n=========================================" << std::endl;
            std::cout << " [WINNER] Game Won by O Player (" << CYAN << name_2 << GREEN << ")!" << std::endl;
            std::cout << " Total turns taken = " << count_for_O << std::endl;
            std::cout << "=========================================\n" << RESET << std::endl;
            if (handler1.is_open())
                handler1 << name_2 << " won as O player : in turns = " << count_for_O << std::endl;
        }
        return;
    }

    // Check for draw
    int empty_spaces = 0;
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 7; j++)
            if (game[i][j] == ' ') empty_spaces++;

    if (empty_spaces == 0)
        flag1 = true;
}

void record()
{
    std::ifstream handler2("record.txt");
    if (!handler2.is_open()) {
        std::cout << YELLOW << "No historical match records found yet." << RESET << std::endl;
        return;
    }
    std::string str;
    while (std::getline(handler2, str))
        std::cout << GREEN << " > " << str << RESET << std::endl;

    handler2.close();
}