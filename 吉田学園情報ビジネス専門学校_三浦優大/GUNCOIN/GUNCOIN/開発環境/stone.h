#ifndef _STONE_H_
#define _STONE_H_

#include "main.h"

//========================
//�}�N����`
//========================
#define MAXSTONE (256)
#define MAXSTONEVER (MAXSTONE * 4)

//===============
//�\���̂̒�`
//===============
typedef struct
{
	D3DXVECTOR3 Pos;//�ʒu
	D3DXVECTOR3 move;//�ړ���
	D3DXVECTOR3 rot;//����
	D3DXVECTOR3 rotmove;//����
	D3DXVECTOR3 rotDest;//�ړI�̌���
	D3DXVECTOR3 MaxStone;//�ő�l
	D3DXVECTOR3 MinStone;//�ŏ��l
	D3DXVECTOR3 aPos[MAXSTONEVER];
	D3DXVECTOR3 Vec[MAXSTONEVER];
	D3DXVECTOR3 g_Vec[MAXSTONEVER];
	float PlayerVec[MAXSTONEVER];
	bool bUse;
	int nType;
	//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DTEXTURE9 g_apTextureStone[3];

}STONE;

//==========================
//�v���g�^�C�v�錾
//==========================
void InitStone(void);//����������
void UninitStone(void);//�I������
void UpdateStone(void);//�X�V����
void DrawStone(void);//�J�����̐ݒ�,Draw�̈�ԏ�Œ�`
STONE *GetStone(void);
bool CollisionVec(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidthMax, float fWidthMin, float fDepthMax, float fDepthMin, float fHeightMax, float fHeightMin);
void SetStone(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType);
#endif

