//-----------------------------------------------------------------
//
// �G�̏��� (enemy.h)
// Author:Miurayudai
//
//-----------------------------------------------------------------

#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

//==============================
//�G�̏��
//==============================
typedef enum
{
	ENEMYSTATE_NOMAL = 0 ,//�ʏ펞
	ENEMYSTATE_DAMAGE,//�_���[�W���
	ENEMYSTATE_MAX
}ENEMYSTATE;

//===================================
//�G�̍\����
//===================================
typedef struct
{
	D3DXVECTOR3 Pos;//�ʒu
	D3DXVECTOR3 move;//�ړ���
	int nType;//���
	bool bUse;//�g�p���Ă��邩�ǂ���
	int nCounterAni;//�A�j���[�V����
	int nPatternAni;//�A�j���[�V����
	int nseetAni;//�A�j���[�V����
	ENEMYSTATE state;//���
	int nCounterState;//��ԃJ�E���^�[
	int nLife;//�̗�
	D3DXVECTOR3 rotEnemy;//�G�̃T�C�Y���
	float fLengthEnemy;//�Ίp���̒���
	float fAngleEnemy;//�Ίp���̊p�x
}ENEMY;

//==========================================
//�v���g�^�C�v�錾
//==========================================
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SETENEMY(D3DXVECTOR3 Pos, int nType);
ENEMY *GetEnemy(void);
bool HitEnemy(int nIdx, int nDamage);
int GetEnemyNumber(void);
#endif