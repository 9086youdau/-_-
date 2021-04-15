#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "main.h"

typedef enum
{
	BLOCKTYPE_BLOCK = 0,
	BLOCKTYPE_BLOCK_FILED,
	BLOCKTYPE_BLOCK_BLOCK,
	BLOCKTYPE_BLOCK_ITEM,
	BLOCKTYPE_MAX
}BLOCKTYPE;

//===============
//�\���̂̒�`
//===============
typedef struct
{
	D3DXVECTOR3 Pos;//�ʒu
	D3DXVECTOR3 oldPos;//�ʒu
	D3DXVECTOR3 move;
	float fWidth;//��
	float fHeight;//����
	int nType;
	bool bUse;//�g���Ă��邩
}BLOCK;

//===============
//�v���g�^�C�v�錾
//===============
HRESULT InitBlock(void);//����������
void UninitBlock(void);//�I������
void UpdateBlock(void);//�X�V����
void DrawBlock(void);//�`�揈��
void SetBlock(D3DXVECTOR3 pos, float fWidth, float fHeight,int nType);//�u���b�N�ݒu����
BLOCK *GetBlock(void);
int GetBlockNumber(void);
#endif
