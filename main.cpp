#include <iostream>;
#include <map>;
#include <string>;

using namespace std;

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
}

map <string, string> gameMenu() {
    map <string, string> gameData;

    cout << "Bienvenido a Tic Tac Toe!" << endl;
    int playerCount = getPlayerCount();
    gameData["playerCount"] = to_string(playerCount);
    gameData["playerOneName"] = "player";
    gameData["playerTwoName"] = "computer";

    return gameData;
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


void gameOver(char (&board)[3][3]) {
    cout << "El juego ha terminado" << endl;

}

char getPlayerSymbol(int player) {
    switch (player) {
        case 1:
            return 'X';
        case 2:
            return 'O';
    }
}

void move(int player, char (&board)[3][3]) {
    int pos;
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

    if (board[row][col] == 'X' || board[row][col] == 'O') {
        cout << "La casilla seleccionada esta ocupada" << endl;
        return;
    }
    else {
        board[row][col] = getPlayerSymbol(player);
        drawBoard(board);
    }

}

void computerMove(char (&board)[3][3]) {

}

void startGame(int players = 1) {
    char board[3][3] = {{'1','2','3'},{'4','5','6'},{'7','8','9'}};

    bool gameOver = false;

    drawBoard(board);

    while (gameOver != true) {
        if (players == 1) {
            move(1,board);
            computerMove(board);
        }
        else if (players == 2) {
            move(1,board);
            move(2,board);
        }
    }
    // if (gameOver == true) {
    //     gameOver(board);
    // }
}

int main(int argc, char *argv[]) {

    map<string,string> gameData = gameMenu();

    int playerCount = stoi(gameData["playerCount"]);

    startGame(playerCount);



    return 0;


}
