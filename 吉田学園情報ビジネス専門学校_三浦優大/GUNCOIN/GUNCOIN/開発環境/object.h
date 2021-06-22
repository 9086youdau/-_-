#ifndef _STONE_H_
#define _STONE_H_

#include "main.h"

//======================================
//�}�N����`
//======================================
#define MAX_OBJECT_TYPE (2)
#define MAXOBJECT (256)
#define MAXOBJECTVER (MAXOBJECT * 4)

//======================================
//�\���̂̒�`
//======================================
typedef struct
{
	D3DXVECTOR3 Pos;//�ʒu
	D3DXVECTOR3 move;//�ړ���
	D3DXVECTOR3 rot;//����
	D3DXVECTOR3 rotmove;//����
	D3DXVECTOR3 rotDest;//�ړI�̌���
	D3DXVECTOR3 MaxObject;//�ő�l
	D3DXVECTOR3 MinObject;//�ŏ��l
	D3DXVECTOR3 aPosObject[MAXOBJECTVER];
	D3DXVECTOR3 VecObject[MAXOBJECTVER];
	D3DXVECTOR3 aVecObject[MAXOBJECTVER];
	float ObjectVec[MAXOBJECTVER];
	bool bUse;
	int nType;
}OBJECT;

//==========================
//�v���g�^�C�v�錾
//==========================
void InitObject(void);//����������
void UninitObject(void);//�I������
void UpdateObject(void);//�X�V����
void DrawObject(void);//�`�揈��
OBJECT *GetObject(void);
bool CollisionVecObject(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidthMax, float fWidthMin, float fDepthMax, float fDepthMin, float fHeightMax, float fHeightMin);
void SetObject(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType);
#endif

