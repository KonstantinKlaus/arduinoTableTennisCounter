#ifndef GAME_H
#define GAME_H



class Game
{


public:

    // additional types
    enum player {player_1, player_2};
    enum playerPosition {pos_1, pos_2};
    enum gameState {player1Wins, player2Wins, running, changeover};

    // functions

    Game();

    void playerGetPoint(player player);
    void playerGetPoint(playerPosition pos);

    void playerGetSetPoint(player player);
    void playerGetSetPoint(playerPosition pos);

    void resetGame();

    void revertGame();

    void backupGameState();

    int getPoints(player player);
    int getPoints(playerPosition pos);

    int getSetPoints(player player);
    int getSetPoints(playerPosition pos);

    player getServingPlayer();
    playerPosition getServingPosition();

    player getPlayer(playerPosition pos);

    gameState getState();

    void playersChangeover();
    void confirmChangeover();

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

    // player positions
    player playerPos_1 = player_1;
    player playerPos_2 = player_2;

    player prevPlayerPos_1 = player_1;
    player prevPlayerPos_2 = player_2;

    // functions

    void switchRightOfService();

};

#endif