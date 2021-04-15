#ifndef _WALL_H_
#define _WALL_H_

#include "main.h"

//========================
//�}�N����`
//========================
#define MAXWALL (256)
#define MAXWALLVER (MAXWALL * 4)

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
	D3DXVECTOR3 aPos[MAXWALLVER];
	D3DXVECTOR3 Vec[MAXWALLVER];
	D3DXVECTOR3 g_Vec[MAXWALLVER];
	float PlayerVec[MAXWALLVER];
	bool bUse;
	int nType;
	//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DTEXTURE9 g_apTextureWall = NULL;
}WALL;

//==========================
//�v���g�^�C�v�錾
//==========================
void InitWall(void);//����������
void UninitWall(void);//�I������
void UpdateWall(void);//�X�V����
void DrawWall (void);//�J�����̐ݒ�,Draw�̈�ԏ�Œ�`
WALL *GetWall(void);
bool CollisionVecWall(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidthMax, float fWidthMin, float fDepthMax, float fDepthMin, float fHeightMax, float fHeightMin);
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot,int nType);
#endif


