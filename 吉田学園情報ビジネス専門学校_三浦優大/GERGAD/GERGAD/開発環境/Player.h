//-----------------------------------------------------------------
//
// �v���C���[��ʂ̏��� (player.h)
// Author:Miurayudai
//
//-----------------------------------------------------------------

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

//======================
//�v���C���[�̏��
//======================
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
	D3DXVECTOR3 rotPlayer;//��]��
	D3DXVECTOR3 movePlayer;//�ړ���
	int nCounterAnim;//�A�j���[�V����
	int nPatternAnim;//�A�j���[�V����
	int nseetAnim;//�A�j���[�V����
	float fLengthPlayer;//�Ίp���̒���
	float fAnglePlayer;//�Ίp���̊p�x
}PLAYER;

//===============
//�v���g�^�C�v�錾
//===============
HRESULT InitPlayer(void);//����������
void UninitPlayer(void);//�I������
void UpdatePlayer(void);//�X�V����
void DrawPlayer(void);//�`�揈��
bool HitPlayer(int nDamage);
PLAYER *GetPlayer(void);

#endif
