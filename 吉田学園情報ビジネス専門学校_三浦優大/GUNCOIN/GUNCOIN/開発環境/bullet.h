#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

//�e�̍\����
typedef struct
{
	D3DXVECTOR3 Pos;//�ʒu
	D3DXVECTOR3 move;//�ړ���
	D3DXCOLOR col;
	int nLife;//����
	D3DXMATRIX mtxWorld;//���[���h�}�g���b�N�X
	bool bUse;//�g�p���Ă��邩�ǂ���
}BULLET;

//==================
//�v���g�^�C�v�錾
//==================
HRESULT InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife);
BULLET *GetBullet(void);
#endif
