#include <iostream>
#include <cstdlib>
#include <ctime>

class Player {
public:
    Player(const std::string& name) : name(name) {}
    std::string getName() const { return name; }
private:
    std::string name;
};

class UpAndDownGame {
public:
    UpAndDownGame(Player& player1, Player& player2) 
        : player1(player1), player2(player2), currentPlayer(&player1) {
        std::srand(std::time(0));
        targetNumber = std::rand() % 100;
        lowerBound = 0;
        upperBound = 99;
    }

    void play() {
        while (true) {
            int guess = getGuess();
            if (guess == targetNumber) {
                std::cout << currentPlayer->getName() << " wins!\n";
                break;
            } else if (guess < targetNumber) {
                std::cout << "Up\n";
                lowerBound = std::max(lowerBound, guess + 1);
            } else {
                std::cout << "Down\n";
                upperBound = std::min(upperBound, guess - 1);
            }
            switchPlayer();
        }
    }

private:
    Player& player1;
    Player& player2;
    Player* currentPlayer;
    int targetNumber;
    int lowerBound;
    int upperBound;

    int getGuess() {
        int guess;
        while (true) {
            std::cout << currentPlayer->getName() << ", enter a number between " << lowerBound << " and " << upperBound << ": ";
            std::cin >> guess;
            if (std::cin.fail() || guess < lowerBound || guess > upperBound) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter a number between " << lowerBound << " and " << upperBound << ".\n";
            } else {
                break;
            }
        }
        return guess;
    }

    void switchPlayer() {
        currentPlayer = (currentPlayer == &player1) ? &player2 : &player1;
    }
};

int main() {
    Player player1("Player 1");
    Player player2("Player 2");
    UpAndDownGame game(player1, player2);
    game.play();
    return 0;
}