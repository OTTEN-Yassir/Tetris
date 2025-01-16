#include "View.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

void View::displayBoard(const Game &game) {
    const Board &board = game.getBoardGame();
    for (const auto &y: board.getBoard()) {
        std::cout << "\t    ";
        for (const auto &x: y) {
            if (!x->getIsOccupied()) {
                std::cout << ". ";
            } else {
                std::cout << "# ";
            }
        }
        std::cout << std::endl;
    }
}

void View::displayTime(std::chrono::time_point<std::chrono::steady_clock> startTime) {
    auto currentTime = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime);

    int hours = elapsed.count() / 3600;
    elapsed -= std::chrono::hours(hours);
    int minutes = elapsed.count() / 60;
    elapsed -= std::chrono::minutes(minutes);
    int seconds = elapsed.count();

    std::cout << std::setfill('0') << std::setw(2) << hours << ":"
              << std::setfill('0') << std::setw(2) << minutes << ":"
              << std::setfill('0') << std::setw(2) << seconds << std::endl;
}

void View::displayLevelScore(int level, int score, int completedRows,
                             std::chrono::time_point<std::chrono::steady_clock> startTime) {
    std::cout << "Level : " << level << " Score : " << score << " Rows : " << completedRows
              << " Time : ";
    displayTime(startTime);
}

std::string View::askCommands() {
    std::cout << "Enter a command (MOVE : Q, S, D | ROTATE : A, E | DROP : F | QUIT : T)" << std::endl;
    std::string input;
    std::cin >> input;
    return input;
}

void View::displayErrorCommands() {
    std::cout << "\n\n";
    std::cout << "    ERROR !!!!! INVALIDE COMMAND" << std::endl;
    std::cout << "    You must enter a valid command ! " << std::endl;
    std::cout << "\n\n" << std::endl;

}

bool View::wantUpdateSize() {
    std::string response;
    do {
        std::cout << "Do you want to modify the size of the game board? (y/n): ";
        std::cin >> response;
        transform(response.begin(), response.end(), response.begin(), ::toupper);
        clearCin();
    } while (response != "Y" && response != "N");
    return response == "Y";
}

bool View::wantPreFillBoard() {
    std::string response;
    do {
        std::cout << "Do you want to play on a pre-filled brick board? (y/n): ";
        std::cin >> response;
        transform(response.begin(), response.end(), response.begin(), ::toupper);
        clearCin();
    } while (response != "Y" && response != "N");
    return response == "Y";
}

bool View::wantChangeLevel() {
    std::string response;
    do {
        std::cout << "Do you want to choice a level ? (y/n): ";
        std::cin >> response;
        transform(response.begin(), response.end(), response.begin(), ::toupper);
        clearCin();
    } while (response != "Y" && response != "N");
    return response == "Y";
}

int View::askDensity() {
    int density;
    do {
        std::cout << "Enter the density (0..10): ";
        std::cin >> density;
        clearCin();
    } while (density < 0 || density > 10);
    return density;
}

int View::askLevel() {
    int level;
    do {
        std::cout << "Enter the level (1..20): ";
        std::cin >> level;
        clearCin();
    } while (level < 1 || level > 20);
    return level;
}

std::pair<int, int> View::askSize() {
    int height, width;
    std::cout << "Enter the height of the game board: ";
    std::cin >> height;
    clearCin();

    std::cout << "Enter the width of the game board: ";
    std::cin >> width;
    clearCin();

    return std::make_pair((int) height, (int) width);
}

void View::clearCin() const {
    std::cin.clear(); // Effacer le flag d'erreur
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignorer jusqu'à la fin de la ligne

}

void View::displayTitle() {
    std::string border(26, '*');
    std::string padding = "*";
    padding += std::string(24, ' ');
    padding += "*";

    std::cout << "\t" << border << std::endl;
    std::cout << "\t" << padding << std::endl;
    std::cout << "\t" << "*    Welcome to Tetris   *" << std::endl;
    std::cout << "\t" << padding << std::endl;
    std::cout << "\t" << border << "\n" << std::endl;

}

void View::displayLost() {
    std::string border(17, '*');
    std::string padding = "*";
    padding += std::string(15, ' ');
    padding += "*";

    std::cout << "\n\t    " << border << std::endl;
    std::cout << "\t    " << padding << std::endl;
    std::cout << "\t    " << "*   YOU LOST !  *" << std::endl;
    std::cout << "\t    " << padding << std::endl;
    std::cout << "\t    " << border << std::endl;

}

void View::displayWin() {
    std::string border(16, '*');
    std::string padding = "*";
    padding += std::string(14, ' ');
    padding += "*";

    std::cout << "\n\t    " << border << std::endl;
    std::cout << "\t    " << padding << std::endl;
    std::cout << "\t    " << "*   YOU WIN !  *" << std::endl;
    std::cout << "\t    " << padding << std::endl;
    std::cout << "\t    " << border << std::endl;
}
