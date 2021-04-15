#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

//�}�N����`
#define MAX_BULLET_SIZE (20)
#define MAX_SIZE (15)
#define	MAX_POLYGON_SIZE (20)

//�e�̍\����
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 move;//�ړ���
	D3DXCOLOR col;
	int nType;
	int nLife;//����
	bool bUse;//�g�p���Ă��邩�ǂ���
}BULLET;

//
//�v���g�^�C�v�錾
//
HRESULT InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, D3DXCOLOR col, int nType);
BULLET *GetBullet(void);
#endif