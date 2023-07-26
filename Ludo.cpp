#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

enum class PowerUpType {
    DoubleMove,
    SkipTurn,
    SwapPositions
};

class Player {
private:
    string name;
    int position;

public:
    Player(string playerName) : name(playerName), position(0) {}

    string getName() const {
        return name;
    }

    int getPosition() const {
        return position;
    }

    void setPosition(int newPosition) {
        position = newPosition;
    }
};

class PowerUp {
private:
    PowerUpType type;

public:
    PowerUp(PowerUpType powerUpType) : type(powerUpType) {}

    PowerUpType getType() const {
        return type;
    }

    void applyEffect(Player& player, vector<Player>& players, int currentPlayerIndex) {
        switch (type) {
            case PowerUpType::DoubleMove:
                cout << player.getName() << " used Double Move power-up!" << endl;
                break;
            case PowerUpType::SkipTurn:
                cout << player.getName() << " used Skip Turn power-up!" << endl;
                break;
            case PowerUpType::SwapPositions:
                cout << player.getName() << " used Swap Positions power-up!" << endl;
                // Implement the logic for swapping positions between players
                break;
        }
    }
};

class LudoGame {
private:
    vector<Player> players;
    vector<int> diceNumbers;
    int currentPlayerIndex;

public:
    LudoGame(const vector<string>& playerNames) {
        for (const auto& playerName : playerNames)
            players.push_back(Player(playerName));

        diceNumbers = {1, 2, 3, 4, 5, 6};
        currentPlayerIndex = 0;

        srand(static_cast<unsigned int>(time(nullptr)));
    }

    int rollDice() {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Press Enter to roll the dice...";
        cin.get();

        int diceIndex = rand() % diceNumbers.size();
        int diceNumber = diceNumbers[diceIndex];
        cout << players[currentPlayerIndex].getName() << " rolled a " << diceNumber << endl;

        int currentPosition = players[currentPlayerIndex].getPosition();
        int newPosition = currentPosition + diceNumber;
        if (newPosition <= 100)
            players[currentPlayerIndex].setPosition(newPosition);
        else
            cout << "Cannot move. Try again." << endl;

        if (diceNumber != 6)
            currentPlayerIndex = (currentPlayerIndex + 1) % players.size();

        return diceNumber;
    }

    void applyPowerUp(PowerUpType powerUpType) {
        PowerUp powerUp(powerUpType);
        powerUp.applyEffect(players[currentPlayerIndex], players, currentPlayerIndex);
    }

    void displayPlayerPositions() const {
        for (const auto& player : players)
            cout << player.getName() << ": " << player.getPosition() << endl;
    }

    bool isGameOver() const {
        for (const auto& player : players) {
            if (player.getPosition() == 100) {
                return true;
            }
        }
        return false;
    }

    string getWinner() const {
        int maxPosition = -1;
        string winner;
        for (const auto& player : players) {
            if (player.getPosition() > maxPosition) {
                maxPosition = player.getPosition();
                winner = player.getName();
            }
        }
        return winner;
    }
};

int main() {
    vector<string> playerNames = {"Player 1", "Player 2", "Player 3", "Player 4"};
    LudoGame game(playerNames);

    while (true) {
        game.displayPlayerPositions();
        int diceNumber = game.rollDice();

        if (diceNumber == 6) {
            PowerUpType randomPowerUp = static_cast<PowerUpType>(rand() % 3);
            game.applyPowerUp(randomPowerUp);
        }

        if (game.isGameOver()) {
            cout << "Game Over! " << game.getWinner() << " wins!" << endl;
            break;
        }
    }

    return 0;
}
