#ifndef _SCORE_H_
#define _SCORE_H_

#define MAX_SCORE (8)//�G�̍ő吔
#include "main.h"


//===============
//�v���g�^�C�v�錾
//===============
HRESULT InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void SetScore(void);
void AddScore(int nValue);
#endif