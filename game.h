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

#define MAX_SCORES 8
#define PLAYER_ONE 0
#define PLAYER_TWO 1
#define MAX_COLS 20
#define MAX_ROWS 15

//------------------------------------------------------------
// Types
//------------------------------------------------------------

//TODO: Complete this struct...
typedef struct {
	// General:
    UINT32 scores[MAX_SCORES];
    // Current game:
    UINT8 world[MAX_ROWS][MAX_COLS];
    UINT32 lastScore;
    BOOL victory;
} GameData;

//------------------------------------------------------------
// General
//------------------------------------------------------------

void InitializeGame();

//------------------------------------------------------------
// Scores
//------------------------------------------------------------

void InitializeScores();
void AddScore(UINT32 score);
char * ScoreToString(UINT32 score);
char * ScoreToString10(UINT32 score);
void SaveScores();
void LoadScores();

//------------------------------------------------------------
// World
//------------------------------------------------------------

void InitializeWorld();
void DrawWorlCell(UINT8 row, UINT8 col);
void DrawWorldPlayer1(UINT8 row, UINT8 col);
void DrawWorldPlayer2(UINT8 row, UINT8 col);
void DrawWorldSoldier1(UINT8 row, UINT8 col);
void DrawWorldLife(UINT8 row, UINT8 col);
void DrawWorldWall(UINT8 row, UINT8 col);
void DrawWorldEmpty(UINT8 row, UINT8 col);

//------------------------------------------------------------
// Game
//------------------------------------------------------------

void InitializeNewGame();
void DrawGame();
void DrawGameScore();
void DrawGameSprite(UINT16 x, UINT16 y, const UINT8 * data);

//------------------------------------------------------------
// Menus
//------------------------------------------------------------

void DrawMenu();
void DrawNewGame();
void DrawGameOver();
void DrawScores();
void DrawHelp();

#ifdef __cplusplus
}
#endif

#endif
