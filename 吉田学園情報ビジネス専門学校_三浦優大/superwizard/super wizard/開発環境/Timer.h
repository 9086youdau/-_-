#ifndef _TIMER_H_
#define _TIMER_H_

#define MAX_TIMER (3)//�X�R�A�̍ő吔
#include "main.h"

//�e�̍\����
typedef struct
{
	int nTimer;//����
}TIMER;

//===============
//�v���g�^�C�v�錾
//===============
HRESULT InitTimer(void);
void UninitTimer(void);
void UpdateTimer(void);
void DrawTimer(void);
TIMER *GetTimer(void);
void AddTimer(int nValue);
#endif