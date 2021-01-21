#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

//========
//�v���C���[�̏��
//========
typedef enum
{
	PLAYERSTATE_NOMAL = 0,//�ʏ펞
	PLAYERSTATE_DAMAGE,//�_���[�W���
	PLAYERSTATE_MAX
}PLAYERSTATE;

//�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 Pos;//�ʒu
	D3DXVECTOR3 move;//�ړ���
	int nType;//���
	int nLife;//����
	PLAYERSTATE state;//���
	int nCounterState;
	bool bUse;//�g�p���Ă��邩�ǂ���
}PLAYER;

//===============
//�v���g�^�C�v�錾
//===============
HRESULT InitPlayer(void);//����������
void UninitPlayer(void);//�I������
void UpdatePlayer(void);//�X�V����
void DrawPlayer(void);//�`�揈��
void SetPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife , int nType);//�v���C���[�̐ݒ�
bool HitPlayer(int nDamage);
PLAYER *GetPlayer(void);

#endif
