#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

//�}�N����`
#define MAX_BULLET_SIZE (100)
#define MAX_SIZE (40)
#define	MAX_POLYGON_SIZE (10)

typedef enum
{
	BULLETTYPE_ENEMY=0,
	BULLETTYPE_ENEMY_HOMING,
	BULLETTYPE_ENEMY_HOMING2,
	BULLETTYPE_ENEMY_HOMING3,
	BULLETTYPE_MAX
}BULLETTYPE;

//�e�̍\����
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 move;//�ړ���
	D3DXCOLOR col;
	BULLETTYPE nType;
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
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, D3DXCOLOR col, BULLETTYPE nType);

#endif