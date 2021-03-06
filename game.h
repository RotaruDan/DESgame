//****************************************************************************************************
// Copyright (c) 2015 Gorka Su�rez Garc�a, Dan Cristian Rotaru
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//****************************************************************************************************

#ifndef __GAME_H__
#define __GAME_H__

#include "yukino.h"

#ifdef __cplusplus
extern "C" {
#endif

//------------------------------------------------------------
// Constants
//------------------------------------------------------------

#define MAX_SCORES  8
#define MAX_COLS    20
#define MAX_ROWS    15
#define MAX_PLAYERS 2
#define PLAYER_ONE  0
#define PLAYER_TWO  1
#define MAX_LIVES   3

#define MAX_UPDATE_COUNT 1
#define MAX_ENTITY_COUNT 2
#define MAX_LIVES_COUNT  200

#define SCORE_SOLDIER1 8
#define SCORE_SOLDIER2 16
#define SCORE_PLAYER   32
#define SCORE_LIFE     64

#define CELL_WIDTH  16
#define CELL_HEIGHT 16

#define DIR_NORTH 0
#define DIR_EAST  1
#define DIR_SOUTH 2
#define DIR_WEST  3

#define ACTION_NONE  0
#define ACTION_FIRE  1
#define ACTION_NORTH 2
#define ACTION_EAST  3
#define ACTION_SOUTH 4
#define ACTION_WEST  5

#define STATE_MENU      0
#define STATE_NEW_GAME  1
#define STATE_GAME      2
#define STATE_GAME_OVER 3
#define STATE_SCORES    4
#define STATE_HELP      5

#define W_EMPT 0x00
#define W_PLA1 0x01
#define W_PLA2 0x02
#define W_SHO1 0x04
#define W_SHO2 0x08
#define W_SOL1 0x10
#define W_SOL2 0x20
#define W_LIFE 0x40
#define W_WALL 0x80

#define MSG_NEW_GAME  0xFA
#define MSG_UPDATE    0xFB
#define MSG_ABORT     0xFD
#define MSG_TEST      0xFE

#define NO_GENERATED  0xFF

//------------------------------------------------------------
// Types
//------------------------------------------------------------

typedef struct {
    BOOL alive;
    UINT8 direction;
    UINT8 row, col;
} Shoot;

typedef struct {
    UINT8 direction;
    UINT8 row, col;
    UINT8 lives;
    Shoot shoot;
} Player;

typedef struct {
    // General:
    BOOL pause;
    UINT8 state;
    UINT32 scores[MAX_SCORES];
    // Current game:
    UINT8 world[MAX_ROWS][MAX_COLS];
    Player players[MAX_PLAYERS];
    UINT8 lastGenRow, lastGenCol, lastGenVal;
    UINT8 lastAction, remoteAction;
    UINT8 hostPlayer, entityCount;
    UINT32 lastScore;
    BOOL victory;
    BOOL useInput;
    BOOL useCommunication;
    UINT8 updateCount;
} GameData;

//------------------------------------------------------------
// Game
//------------------------------------------------------------

void InitializeGame();
void InitializeNewGame();
void InitializePlayer(UINT8 player);
void PlayerOneAsHost();
void PlayerTwoAsHost();
void DecEntityCount();

void PlayerQuitOneLife(UINT8 player);
void PlayerAddScore(UINT8 player, UINT32 value);
void ExecuteAction(UINT8 player, UINT8 action);
void PutGeneratedEntity(UINT8 value);
void UpdateEntityGenerator();
void UpdateGame();
void UpdateOnKeyboard(UINT32 keys);
void UpdateOnTimer();

//------------------------------------------------------------
// Communication
//------------------------------------------------------------

BOOL SendByte(char data);
char ReceiveByte();

void StartUpdateCommunication();
void FinishUpdateCommunication();

BOOL SendNewGameMessage();
BOOL SendAbortMessage();
BOOL SendTestMessage();

void NewGameMessageReceived();
void UpdateOnReceiveUART();
void OnReceiveUART();

//------------------------------------------------------------
// Fire
//------------------------------------------------------------

void ExterminateAnnihilateDestroy(UINT8 player, UINT8 row, UINT8 col);
void ExecuteActionFire(UINT8 player);
void UpdatePlayerShoot(UINT8 player);

//------------------------------------------------------------
// Move
//------------------------------------------------------------

void ExecuteActionNorth(UINT8 player);
void ExecuteActionEast(UINT8 player);
void ExecuteActionSouth(UINT8 player);
void ExecuteActionWest(UINT8 player);
void ExecuteActionMove(UINT8 player, UINT8 row1, UINT8 col1, UINT8 row2, UINT8 col2);

//------------------------------------------------------------
// States
//------------------------------------------------------------

void GotoStateMenu();
void GotoStateNewGame();
void GotoStateGame();
void GotoStateGameOver();
void GotoStateScores();
void GotoStateHelp();

//------------------------------------------------------------
// Render
//------------------------------------------------------------

void DrawMenu();
void DrawNewGame();
void DrawGameOver();
void DrawScores();
void DrawHelp();

void DrawGame();
void DrawGameScoreAndLives();
void DrawGameSprite(UINT16 x, UINT16 y, const UINT8 * data);
void DrawGameSprite90(UINT16 x, UINT16 y, const UINT8 * data);
void DrawGameSprite180(UINT16 x, UINT16 y, const UINT8 * data);
void DrawGameSprite270(UINT16 x, UINT16 y, const UINT8 * data);
void DrawWorldPlayer(UINT8 row, UINT8 col, UINT8 player, const UINT8 * data);

//------------------------------------------------------------
// Scores
//------------------------------------------------------------

void InitializeScores();
void AddScore(UINT32 score);
void ResetScores();
void SaveScores();
void LoadScores();

//------------------------------------------------------------
// World
//------------------------------------------------------------

void InitializeWorld();
BOOL IsCellEmpty(UINT8 row, UINT8 col);
BOOL IsCellEmptyOrPickable(UINT8 row, UINT8 col);
void FindPlayerPosition(UINT8 player, UINT8 wid);
void DrawWorlCell(UINT8 row, UINT8 col);
void DrawWorldPlayer1(UINT8 row, UINT8 col);
void DrawWorldPlayer2(UINT8 row, UINT8 col);
void DrawWorldSoldier1(UINT8 row, UINT8 col);
void DrawWorldLife(UINT8 row, UINT8 col);
void DrawWorldWall(UINT8 row, UINT8 col);
void DrawWorldEmpty(UINT8 row, UINT8 col);
void DrawWorldShoot(UINT8 row, UINT8 col);
void ClearWorldCell(UINT8 row, UINT8 col);
void RedrawWorldPlayer(UINT8 player);

//------------------------------------------------------------
// Utility
//------------------------------------------------------------

char * IntToString(UINT32 value);
char * IntToString3(UINT32 value);
char * IntToString10(UINT32 value);
char * IntToStringWithFormat(UINT32 value, const char * format);
UINT8 GetOppositePlayer(UINT8 victim);

#ifdef __cplusplus
}
#endif

#endif
