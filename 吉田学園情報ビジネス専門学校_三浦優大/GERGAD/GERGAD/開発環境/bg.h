//-----------------------------------------------------------------
//
// �o�b�N�O���E���h�̏��� (bg.h)
// Author:Miurayudai
//
//-----------------------------------------------------------------

#ifndef _BG_H_
#define _BG_H_

#include "main.h"

//======================================
//�\���̂̒�`
//======================================
typedef struct
{
	D3DXVECTOR3 Pos;//�ʒu
	int nType;//���
	bool bUse;//�g�p���Ă��邩�ǂ���
}BG;

//==========================================
//�v���g�^�C�v�錾
//==========================================
HRESULT InitBG(void);
void UninitBG(void);
void UpdateBG(void);
void DrawBG(void);
void SetBG(D3DXVECTOR3 Pos, int nType);
#endif
