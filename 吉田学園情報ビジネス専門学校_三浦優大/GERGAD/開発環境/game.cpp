#include "game.h"
#include "bullet.h"
#include "Player.h"
#include "enemy.h"
#include "Explosion.h"
#include "bg.h"
#include "sound.h"
#include"effect.h"
#include "Pause.h"
#include "particle.h"
#include "Score.h"
#include "input.h"
#include "Hp.h"

//�O���[�o���ϐ�
bool g_bPause = false;//�|�[�Y�����ǂ���

HRESULT InitGame(void)
{
	//�w�i�̏�����
	InitBG();

	//�e�̏���������
	InitBullet();

	//�G�̏���������
	InitEnemy();

	//for (int nCntEnemy = 0; nCntEnemy < 20; nCntEnemy++)
	{
		//SETENEMY(D3DXVECTOR3(600 + (nCntEnemy * 75.0f), 100, 0.0f), 0);
	}

	SETENEMY(D3DXVECTOR3(570 ,350, 0.0f), 0);

	//�|���S���̏���������
	InitPlayer();

	//�����̏�����
	InitExplosion();

	//�G�t�F�N�g�̏�����
	InitEffect();

	//�p�[�e�B�N���̏�����
	InitParticle();

	//�X�R�A�̏�����
	InitScore();

	//�|�[�Y�̏�����
	InitPause();

	SetBG(D3DXVECTOR3(0, 0, 0.0f), 0);
	SetBG(D3DXVECTOR3(0, 0, 0.0f), 1);
	SetBG(D3DXVECTOR3(1400, 900, 0.0f), 2);
	SetBG(D3DXVECTOR3(1640, 400, 0.0f), 3);
	SetBG(D3DXVECTOR3(1725, 400, 0.0f), 4);

	InitHp();

	return S_OK;
}

void UninitGame(void)
{
	//BGM���I�����鏈��
	StopSound();

	//�w�i�̏I������
	UninitBG();

	//�|���S���̏I������
	UninitPlayer();

	//�e�̏I������
	UninitBullet();

	//�����̏I������
	UninitExplosion();

	//�G�̏I������
	UninitEnemy();

	//�X�R�A�̏I������
	UninitScore();

	//�|�[�Y�̏I������
	UninitPause();

	//�G�t�F�N�g�̏I������
	UninitEffect();

	//�p�[�e�B�N���̏I������
	UninitParticle();

	UninitHp();
}

void UpdateGame(void)
{ 
	//�|�[�Y��ʂ̏���
	if (GetKeyboardTrigger(DIK_P) == true)
	{
		g_bPause = g_bPause ? false : true;
	}
	if (g_bPause == true)
	{
		UpdatePause();
	}
	else
	{
		//�w�i�̍X�V����
		UpdateBG();

		//�|���S���̍X�V����
		UpdatePlayer();

		//�e�̍X�V����
		UpdateBullet();

		//�����̍X�V����
		UpdateExplosion();

		//�G�̍X�V����
		UpdateEnemy();

		//�X�R�A�̍X�V����
		UpdateScore();

		//�G�t�F�N�g�̍X�V����
		UpdateEffect();

		//�p�[�e�B�N���̍X�V����
		UpdateParticle();

		UpdateHp();

	}
}

void DrawGame(void)
{
	//�w�i�̕`�揈��
	DrawBG();

	//�e�̕`�揈��
	DrawBullet();

	//�|���S���̕`�揈��
	DrawPlayer();

	//�G�̕`�揈��
	DrawEnemy();

	//�����̕`�揈��
	DrawExplosion();

	//�w�i�̕`�揈��
	DrawScore();

	//�G�t�F�N�g�̕`�揈��
	DrawEffect();

	//�p�[�e�B�N���̕`�揈��
	DrawParticle();

	DrawHp();

	if (g_bPause == true)
	{
		DrawPause();
		
	}
	
}