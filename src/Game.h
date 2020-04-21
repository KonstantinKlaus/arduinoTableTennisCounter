#ifndef GAME_H
#define GAME_H
class Game
{
private:

    // game points
    int pointsP1 = 0;
    int pointsP2 = 0;

    int setPointsP1 = 0;
    int setPointsP2 = 0;

    // last state
    int prevPointsP1 = 0;
    int prevPointsP2 = 0;

    int prevSetPointsP1 = 0;
    int prevSetPointsP2 = 0;

    // right of service
    int rightOfService = PLAYER_1;

public:

    static const int PLAYER_1 = 0;
    static const int PLAYER_2 = 1;

    Game();

    void playerGetPoint(int playerID);

    void resetGame();

    void revertGame();

    void backupGameState();

    void playerGetSetPoint(int playerID);

    int getPoints(int playerID);

    int getSetPoints(int playerID);
};

#endif