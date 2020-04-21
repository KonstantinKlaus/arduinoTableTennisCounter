#ifndef GAME_H
#define GAME_H

enum player {PLAYER_1, PLAYER_2};

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
    player rightOfService = PLAYER_1;

public:

    Game();

    void playerGetPoint(player player);

    void resetGame();

    void revertGame();

    void backupGameState();

    void playerGetSetPoint(player player);

    int getPoints(player player);

    int getSetPoints(player player);
};

#endif