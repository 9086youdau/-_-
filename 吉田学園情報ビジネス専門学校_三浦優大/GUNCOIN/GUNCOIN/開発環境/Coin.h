#ifndef _COIN_H_
#define _COIN_H_

#define MAX_COIN (2)//�X�R�A�̍ő吔
#include "main.h"

//�e�̍\����
typedef struct
{
	int nCoin;//����
	LPDIRECT3DTEXTURE9 g_apTextureCoin = NULL;//�e�N�X�`���փ|�C���^
}COIN;

//===============
//�v���g�^�C�v�錾
//===============
HRESULT InitCoin(void);
void UninitCoin(void);
void UpdateCoin(void);
void DrawCoin(void);
COIN *GetCoin(void);
void AddCoin(int nValue);
#endif