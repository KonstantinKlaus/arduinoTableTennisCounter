#ifndef GAME_H
#define GAME_H
class Game
{
private:
    // update availible
    bool updated = false;

    // game points
    int pointsP1 = 0;
    int pointsP2 = 0;

    int gamePointsP1 = 0;
    int gamePointsP2 = 0;

    // last state
    int prevPointsP1 = 0;
    int prevPointsP2 = 0;

    int prevGamePointsP1 = 0;
    int prevGamePointsP2 = 0;

public:
    Game();

    void resetUpdate();

    bool isUpdateAvailible();

    void playerGetPoint(int playerID);

    void resetGame();

    void revertGame();

    void backupGameState();

    void playerGetSetPoint(int playerID);

    int getPoints(int playerID);
};

#endif