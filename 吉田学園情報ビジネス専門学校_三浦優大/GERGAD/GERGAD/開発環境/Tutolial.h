//-----------------------------------------------------------------
//
// �`���[�g���A���̏��� (Tutolial.h)
// Author:Miurayudai
//
//-----------------------------------------------------------------

#ifndef _TUTOLIAL_H_
#define _TUTOLIAL_H_

#include "main.h"

//=================================================
//�\���̂̒�`
//=================================================
typedef struct
{
	D3DXVECTOR3 Pos;//�ʒu
	D3DXCOLOR col;
	int nType;//���
	bool bUse;//�g�p���Ă��邩�ǂ���
}TUTOLIAL;

//================================================
//�v���g�^�C�v�錾
//================================================
HRESULT InitTutolial(void);
void UninitTutolial(void);
void UpdateTutolial(void);
void DrawTutolial(void);
void SetTutolial(int nCount);
#endif
