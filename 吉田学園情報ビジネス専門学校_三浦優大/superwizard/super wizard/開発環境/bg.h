#ifndef _BG_H_
#define _BG_H_

#include "main.h"

//===============
//�\���̂̒�`
//===============
typedef struct
{
	D3DXVECTOR3 Pos;//�ʒu
	D3DXVECTOR3 move;
	int nType;//���
	bool bUse;//�g�p���Ă��邩�ǂ���
	int g_nCounterAnim;//�A�j���[�V����
	int g_nPatternAnim;//�A�j���[�V����
	int g_nseetAnim;//�A�j���[�V����
}BG;

//===============
//�v���g�^�C�v�錾
//===============
HRESULT InitBG(void);
void UninitBG(void);
void UpdateBG(void);
void DrawBG(void);
void SetVertexBG(int nCntBG);
#endif
