//-----------------------------------------------------------------
//
// �Q�[���̏��� (game.h)
// Author:Miurayudai
//
//-----------------------------------------------------------------

#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

//======================================
//�v���g�^�C�v�錾
//======================================
HRESULT InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
bool SetPause(bool bPause);
#endif
