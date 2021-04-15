#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"

//�e�̍\����
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 move;//�ʒu
	int nType;
	int nLife;
	bool bUse;//�g�p���Ă��邩�ǂ���
	int g_nCounterAnim;//�A�j���[�V����
	int g_nPatternAnim;//�A�j���[�V����
	int g_nseetAnim;//�A�j���[�V����
}ITEM;
//
//�v���g�^�C�v�錾
//
HRESULT InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);
void SetItem(D3DXVECTOR3 pos,int nType, D3DXVECTOR3 move);
ITEM *GetItem(void);
#endif
