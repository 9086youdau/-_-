#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"

typedef struct
{
	D3DXVECTOR3 Pos;//�ʒu
	D3DXVECTOR3 move;//�ړ���
	D3DXCOLOR color;//�F
	int nType;//���
	int nLife;//����
	bool bUse;//�g�p���Ă��邩�ǂ���
	LPDIRECT3DTEXTURE9 pTextureBillboard = NULL;
}BILLBOARD;

//===============
//�v���g�^�C�v�錾
//===============
HRESULT InitBillboard(void);//����������
void UninitBillboard(void);//�I������
void UpdateBillboard(void);//�X�V����
void DrawBillboard(void);//�`�揈��
void SetBillboard(D3DXVECTOR3 pos, int nLife, D3DXVECTOR3 move,int nType);
BILLBOARD *GetBillboard(void);
#endif
