#ifndef _ENEMY_H_
#define _ENEMY_H_

#define MAX_ENEMY (256)//�G�̍ő吔
#define MAX_TYPE_ENEMY (3)//�G�̎�ސ�
#define MAX_ENEMY_SIZE (145)//�G�̃T�C�Y

#include "main.h"

//========
//�G�̏��
//========
typedef enum
{
	ENEMYSTATE_NOMAL = 0 ,//�ʏ펞
	ENEMYSTATE_DAMAGE,//�_���[�W���
	ENEMYSTATE_MAX
}ENEMYSTATE;

//===========
//�G�̍\����
//===========
typedef struct
{
	D3DXVECTOR3 Pos;//�ʒu
	D3DXVECTOR3 move;//�ړ���
	int nType;//���
	bool bUse;//�g�p���Ă��邩�ǂ���
	int g_nCounterAni;//�A�j���[�V����
	int g_nPatternAni;//�A�j���[�V����
	int g_nseetAni;//�A�j���[�V����
	ENEMYSTATE state;//���
	int nCounterState;//��ԃJ�E���^�[
	int nLife;//�̗�
}ENEMY;

//===============
//�v���g�^�C�v�錾
//===============
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SETENEMY(D3DXVECTOR3 Pos, int nType);
ENEMY *GetEnemy(void);
bool HitEnemy(int nIdx, int nDamage);
int GetEnemyNumber(void);
#endif