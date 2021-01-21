#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"
#include "enemy.h"


//�e�̍\����
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 move;
	D3DXCOLOR col;
	int nType;
	int g_nCounterAnim;
	int g_nPatternAnim;
	int g_nseetAnim;
	bool bUse;//�g�p���Ă��邩�ǂ���
	int nLife;
}EFFECT;
//
//�v���g�^�C�v�錾
//
HRESULT InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos,int nLife,D3DXVECTOR3 move);
EFFECT *GetEffect(void);

#endif
