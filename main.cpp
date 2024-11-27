#include <iostream>
#include <map>
#include <string>

using namespace std;

char getPlayerSymbol(int player) {
    switch (player) {
        case 1:
            return 'X';
        case 2:
            return 'O';
        default:
            return 'E';
    }
}


string getPlayerName() {
    string playerName;
    cout << "Ingrese el nombre del jugador: ";
    cin >> playerName;
    return playerName;
}

int getPlayerCount() {
    int playerCount = 1;
    cout << "Selecciones el modo de juego: " << endl;
    cout << "<1> para jugar solo" << endl;
    cout << "<2> para 2 jugadores" << endl;

    int input = 0;

    cin >> input;

    if (input == 1 || input == 2) {
        return input;
    } else {
        cout << "Opcion no valida" << endl;
        getPlayerCount();
    }
    return playerCount;
}

map <string, string> gameMenu() {
    map <string, string> gameData;

    cout << "Bienvenido a Tic Tac Toe!" << endl;
    int playerCount = getPlayerCount();
    gameData["playerCount"] = to_string(playerCount);
    gameData["playerTwoName"] = "computer";

    gameData["playerOneName"] = getPlayerName();
    if (playerCount == 2) {
        gameData["playerTwoName"] = getPlayerName();
    }
    return gameData;
}

int checkWinner(char board[3][3], char player) {
            if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
                return 1;
            }
            else if (board[0][2] == player && board[1][1] == player && board[2][0] == player) {
                return 1;
            }
            else if (board[0][0] == player && board[0][1] == player && board[0][2] == player) {
                return 1;
            }
            else if (board[1][0] == player && board[1][1] == player && board[1][2] == player) {
                return 1;
            }
            else if (board[2][0] == player && board[2][1] == player && board[2][2] == player) {
                return 1;
            }
            else if (board[0][0] == player && board[1][0] == player && board[2][0] == player) {
                return 1;
            }
            else if (board[0][1] == player && board[1][1] == player && board[2][1] == player) {
                return 1;
            }
            else if (board[0][2] == player && board[1][2] == player && board[2][2] == player) {
                return 1;
            }
            return 0;
}

bool checkGameOver(char board[3][3], int player) {
    int count = 0;
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (board[row][col] != ' ') {
                count++;
            }
        }
    }
    if (checkWinner(board, getPlayerSymbol(player)) == 1 || count == 9) {
        return true;
    }
    return false;
}

template<int r, int c>
void drawBoard(char (&board)[r][c]) {
    for (int row =0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (col == 0) {
                cout << " " << board[row][col] << " | ";
            }
            else if (col == 2) {
                cout << board[row][col] << " ";
            }
            else {

                cout << board[row][col] << " | ";
            }
        }
        if (row == 2) {
            continue;
        }
        cout << endl<< "-----------" << endl;
    }
    cout << endl;
    return;
}

map<string,int> getPosition(int pos) {
    map<string,int> position;
    switch (pos) {
        case 1:
            position["row"] = 0;
            position["col"] = 0;
            return position;
        case 2:
            position["row"] = 0;
            position["col"] = 1;
            return position;
        case 3:
            position["row"] = 0;
            position["col"] = 2;
            return position;
        case 4:
            position["row"] = 1;
            position["col"] = 0;
            return position;
        case 5:
            position["row"] = 1;
            position["col"] = 1;
            return position;
        case 6:
            position["row"] = 1;
            position["col"] = 2;
            return position;
        case 7:
            position["row"] = 2;
            position["col"] = 0;
            return position;
        case 8:
            position["row"] = 2;
            position["col"] = 1;
            return position;
        case 9:
            position["row"] = 2;
            position["col"] = 2;
            return position;
        default:
            return position;
    }
}


void endGame(char (&board)[3][3], map<string,string> playerData) {
    string playerOneName = playerData["playerOneName"];
    string playerTwoName = playerData["playerTwoName"];

    int winner = 0;
    cout << "El juego ha terminado" << endl;

    if (checkWinner(board, getPlayerSymbol(1))) {
        cout << "El ganador es " << playerOneName << endl;
    } else if (checkWinner(board, getPlayerSymbol(2))) {
        cout << "El ganador es " << playerTwoName << endl;
    } else {
        cout << "El juego ha terminado en empate" << endl;
    }
}

void move(int player, char (&board)[3][3], string playerName) {
    bool res;
    int pos;
    cout << ">>> Jugador " << playerName << " <<<" <<endl;
    cout << "Selecciona una casilla para jugar: " << endl;
    cout << "ingrese el numero de la casilla (1-9): " << endl;

    cin >> pos;
    if (pos < 1 || pos > 9) {
        cout << "Opcion no valida" << endl;
        return;
    }
    map<string,int> position = getPosition(pos);
    int row = position["row"];
    int col = position["col"];

    if (board[row][col] != ' ') {
        cout << "La casilla seleccionada esta ocupada" << endl;
        return;
    }
    else {
        board[row][col] = getPlayerSymbol(player);
        drawBoard(board);
    }
}

int minimax(char board[3][3], int depth, bool isMax)
{
    int score = -1;

    if (checkWinner(board, getPlayerSymbol(1) == 1)) {
        score = 10;
    }
    else if (checkWinner(board, getPlayerSymbol(2) == 1)) {
        score = -10;
    }
    else if (checkWinner(board, getPlayerSymbol(1) == 0)){
        score = 0;
    }

    // If Maximizer has won the game return evaluated score
    if (score == 10) {
        return score;
    }

    // If Minimizer has won the game return evaluated score
    if (score == -10) {
        return score;
    }
    // If there are no more moves and no winner then
    // it is a tie
    if ((checkGameOver(board, 1)==true || checkGameOver(board,2)) && (checkWinner(board, getPlayerSymbol(1)) == 0 || checkWinner(board, getPlayerSymbol(2)) == 0)) {
        return 0;
    }

    // If this maximizer's move
    if (isMax)
    {
        int best = -1000;

        // Traverse all cells
        for (int i = 0; i<3; i++)
        {
            for (int j = 0; j<3; j++)
            {
                // Check if cell is empty
                if (board[i][j]==' ')
                {
                    // Make the move
                    board[i][j] = 'O';

                    // Call minimax recursively and choose
                    // the maximum value
                    best = max( best,
                        minimax(board, depth+1, !isMax) );

                    // Undo the move
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }

    // If this minimizer's move
    else
    {
        int best = 1000;

        // Traverse all cells
        for (int i = 0; i<3; i++)
        {
            for (int j = 0; j<3; j++)
            {
                // Check if cell is empty
                if (board[i][j]==' ')
                {
                    // Make the move
                    board[i][j] = 'X';

                    // Call minimax recursively and choose
                    // the minimum value
                    best = min(best,
                           minimax(board, depth+1, !isMax));

                    // Undo the move
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
}

void computerMove(char (&board)[3][3]) {

    int bestVal = -1000;
    map<string,int> bestMove;
    bestMove["row"] = -1;
    bestMove["col"] = -1;

    for (int i = 0; i<3; i++)
    {
        for (int j = 0; j<3; j++)
        {
            // Check if cell is empty
            if (board[i][j]==' ')
            {
                // Make the move
                board[i][j] = 'O';

                // compute evaluation function for this
                // move.
                int moveVal = minimax(board, 0, false);

                // Undo the move
                board[i][j] = ' ';

                // If the value of the current move is
                // more than the best value, then update
                // best/
                if (moveVal > bestVal)
                {
                    bestMove["row"] = i;
                    bestMove["col"] = j;
                    bestVal = moveVal;
                }
            }
        }
    }

    board[bestMove["row"]][bestMove["col"]] = 'O';
    drawBoard(board);
}

void startGame(map<string,string> playerData,int players = 1) {
    char board[3][3] = {{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};

    bool gameOver = false;

    int winner = 0;

    drawBoard(board);

    do {
        if (players == 1) {
            move(1,board, playerData["playerOneName"]);
            if (checkGameOver(board, 1)) {
                break;
            };
            computerMove(board);
            if (checkGameOver(board, 2)) {
                break;
            };
        }
        else if (players == 2) {
            move(1,board,playerData["playerOneName"]);
            if (checkGameOver(board, 1)) {
                break;
            };
            move(2,board,playerData["playerTwoName"]);
            if (checkGameOver(board, 2)) {
                break;
            };
        }
    } while (gameOver == false);

    endGame(board, playerData);
}

int main(int argc, char *argv[]) {

    map<string,string> gameData = gameMenu();

    int playerCount = stoi(gameData["playerCount"]);

    map<string,string> playerData;
    playerData["playerOneName"] = gameData["playerOneName"];
    playerData["playerTwoName"] = gameData["playerTwoName"];

    startGame(playerData,playerCount);

    return 0;
}
