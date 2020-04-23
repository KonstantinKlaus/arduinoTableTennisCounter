#ifndef GAME_H
#define GAME_H

enum player {player_1, player_2};

enum gameState {player1Wins, player2Wins, running};

class Game
{
private:

    // variables
    gameState curState = running;
    gameState prevState = running;

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
    player rightOfService = player_1;
    player prevRightOfService = player_1;

    // functions

    void switchRightOfService();

public:

    // functions

    Game();

    void playerGetPoint(player player);

    void resetGame();

    void revertGame();

    void backupGameState();

    void playerGetSetPoint(player player);

    int getPoints(player player);

    int getSetPoints(player player);

    player getServingPlayer();

    gameState getState();
};

#endif