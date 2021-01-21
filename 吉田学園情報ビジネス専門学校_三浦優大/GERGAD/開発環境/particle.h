#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "main.h"
#include "enemy.h"

//�e�̍\����
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 move;
	D3DXCOLOR color;
	int g_nCounterAnim;
	int g_nPatternAnim;
	int g_nseetAnim;
	float fRadius;
	bool bUse;//�g�p���Ă��邩�ǂ���
	int nLife;
}PARTICLE;
//
//�v���g�^�C�v�錾
//
HRESULT InitParticle(void);
void UninitParticle(void);
void UpdateParticle(void);
void DrawParticle(void);
void SetParticle(D3DXVECTOR3 pos,int nLife, D3DXVECTOR3 move);

#endif
