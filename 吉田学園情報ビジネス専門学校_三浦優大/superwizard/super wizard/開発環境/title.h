#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"
#include "input.h"
#include "fade.h"


typedef enum
{
	TITLETYPE_TITLENOMAL = 0,
	TITLETYPE_BG,
	TITLETYPE_TITLE,
	TITLETYPE_PRESSENTER,
	TITLETYPE_MAX
}TITLETYPE;

typedef struct
{
	D3DXVECTOR3 Pos;//�ʒu
	D3DXCOLOR col;
	int nType;//���
	bool bUse;//�g�p���Ă��邩�ǂ���
}TITLE;

//===============
//�v���g�^�C�v�錾
//===============

HRESULT InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);
void SetTitle(int nCount);
#endif

