#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"

//========================
//�}�N����`
//========================
#define MAXITEM (256)
#define MAXITEMVER (MAXITEM * 4)

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
	D3DXVECTOR3 aPos[MAXITEMVER];
	D3DXVECTOR3 Vec[MAXITEMVER];
	D3DXVECTOR3 g_Vec[MAXITEMVER];
	float PlayerVec[MAXITEMVER];
	bool bUse;
	int nType;
	//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DTEXTURE9 g_apTextureItem = NULL;
	int nCntScore;
}Item;

//==========================
//�v���g�^�C�v�錾
//==========================
void InitItem(void);//����������
void UninitItem(void);//�I������
void UpdateItem(void);//�X�V����
void DrawItem(void);//�J�����̐ݒ�,Draw�̈�ԏ�Œ�`
Item *GetItem(void);
bool CollisionVecItem(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidthMax, float fWidthMin, float fDepthMax, float fDepthMin, float fHeightMax, float fHeightMin);
void SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
int nCnt(void);
#endif
