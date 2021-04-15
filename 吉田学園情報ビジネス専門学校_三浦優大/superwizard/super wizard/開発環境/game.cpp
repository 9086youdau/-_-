#include "game.h"
#include "bullet.h"
#include "Player.h"
#include "Explosion.h"
#include "bg.h"
#include "particle.h"
#include "input.h"
#include "Block.h"
#include "result.h"
#include "enemy.h"
#include "Timer.h"
#include "Score.h"
#include "effect.h"
#include "Pause.h"

//�O���[�o���ϐ�
bool g_bPause = false;//�|�[�Y�����ǂ���
int g_pData;
//int g_aapData;
int nLife;
int nCount;
float fAngle;
D3DXVECTOR3 move;

HRESULT InitGame(void)
{
	g_pData = 1;

	//g_aapData = 0;

	nCount++;

	ITEM *pExplosion;
	pExplosion = GetItem();

	if (g_pData == 1)
	{
		//�w�i�̏�����
		InitBG();
	}
	g_bPause = false;

	//�e�̏���������
	InitBullet();

	//�G�̏���������
	InitEnemy();

	SETENEMY(D3DXVECTOR3(2800.0f, 200.0f, 0.0f), 0);
	SETENEMY(D3DXVECTOR3(1200.0f, 200.0f, 0.0f), 0);
	SETENEMY(D3DXVECTOR3(5400.0f, 500.0f, 0.0f), 2);
	SETENEMY(D3DXVECTOR3(5200.0f, 200.0f, 0.0f), 2);

	//�u���b�N�̏�����
	InitBlock();

	//�ʘH�u���b�N
	for (int nCntBlock = 0; nCntBlock < 18; nCntBlock++)
	{
		SetBlock(D3DXVECTOR3(650.0f + (nCntBlock * 60.0f), 600.0f, 0.0f), 30, 30, 0);
		SetBlock(D3DXVECTOR3(650.0f + (nCntBlock * 60.0f), 300.0f, 0.0f), 30, 30, 0);
		SetBlock(D3DXVECTOR3(2400.0f + (nCntBlock * 60.0f), 950.0f, 0.0f), 30, 30, 0);
		SetBlock(D3DXVECTOR3(4200.0f + (nCntBlock * 60.0f), 600.0f, 0.0f), 30, 30, 0);
		SetBlock(D3DXVECTOR3(4200.0f + (nCntBlock * 60.0f), 300.0f, 0.0f), 30, 30, 0);
	}

	for (int nCntBlock = 0; nCntBlock < 35; nCntBlock++)
	{
		SetBlock(D3DXVECTOR3(3600.0f + (nCntBlock * 60.0f), 950.0f, 0.0f), 30, 30, 0);
	}

	SetBlock(D3DXVECTOR3(2400.0f, 150.0f, 0.0f),30,30,0);

	for (int nCntBlock = 0; nCntBlock < 12; nCntBlock++)
	{
		SetBlock(D3DXVECTOR3(2460.0f + (nCntBlock * 60.0f), 890.0f, 0.0f), 30, 30, 0);
	}
	for (int nCntBlock = 0; nCntBlock < 11; nCntBlock++)
	{
		SetBlock(D3DXVECTOR3(2520.0f + (nCntBlock * 60.0f), 830.0f, 0.0f), 30, 30, 0);
	}
	for (int nCntBlock = 0; nCntBlock < 10; nCntBlock++)
	{
		SetBlock(D3DXVECTOR3(2580.0f + (nCntBlock * 60.0f), 770.0f, 0.0f), 30, 30, 0);
	}
	for (int nCntBlock = 0; nCntBlock < 9; nCntBlock++)
	{
		SetBlock(D3DXVECTOR3(2640.0f + (nCntBlock * 60.0f), 710.0f, 0.0f), 30, 30, 0);
	}
	for (int nCntBlock = 0; nCntBlock < 8; nCntBlock++)
	{
		SetBlock(D3DXVECTOR3(2700.0f + (nCntBlock * 60.0f), 650.0f, 0.0f), 30, 30, 0);
	}
	for (int nCntBlock = 0; nCntBlock < 7; nCntBlock++)
	{
		SetBlock(D3DXVECTOR3(2760.0f + (nCntBlock * 60.0f), 590.0f, 0.0f), 30, 30, 0);
	}
	for (int nCntBlock = 0; nCntBlock < 6; nCntBlock++)
	{
		SetBlock(D3DXVECTOR3(2820.0f + (nCntBlock * 60.0f), 530.0f, 0.0f), 30, 30, 0);
	}
	for (int nCntBlock = 0; nCntBlock < 5; nCntBlock++)
	{
		SetBlock(D3DXVECTOR3(2880.0f + (nCntBlock * 60.0f), 470.0f, 0.0f), 30, 30, 0);
	}
	for (int nCntBlock = 0; nCntBlock < 4; nCntBlock++)
	{
		SetBlock(D3DXVECTOR3(2940.0f + (nCntBlock * 60.0f), 410.0f, 0.0f), 30, 30, 0);
	}
	for (int nCntBlock = 0; nCntBlock < 3; nCntBlock++)
	{
		SetBlock(D3DXVECTOR3(3000.0f + (nCntBlock * 60.0f), 350.0f, 0.0f), 30, 30, 0);
	}
	for (int nCntBlock = 0; nCntBlock < 2; nCntBlock++)
	{
		SetBlock(D3DXVECTOR3(3060.0f + (nCntBlock * 60.0f), 290.0f, 0.0f), 30, 30, 0);
	}

	SetBlock(D3DXVECTOR3(950.0f, 950.0f, 0.0f), 1000, 30, 1);

	SetBlock(D3DXVECTOR3(5500.0f, 830.0f, 0.0f), 90, 90, 3);


	SetBlock(D3DXVECTOR3(2280.0f, 830.0f, 0.0f), 30, 30, 6);
	SetBlock(D3DXVECTOR3(2080.0f, 890.0f, 0.0f), 30, 30, 6);

	SetBlock(D3DXVECTOR3(1280.0f, 430.0f, 0.0f), 30, 30, 6);

	SetBlock(D3DXVECTOR3(500.0f, 600.0f, 0.0f), 30, 30, 2);

	SetBlock(D3DXVECTOR3(500.0f, 890.0f, 0.0f), 30, 30, 0);

	//�|���S���̏���������
	InitPlayer();

	//�����̏�����
	InitItem();

	for (int nCntItem = 0; nCntItem < 15; nCntItem++)
	{
		SetItem(D3DXVECTOR3(1500.0f + (nCntItem * 60.0f), 410.0f, 0.0f), 2, pExplosion->move);
	}

	//�G�t�F�N�g�̏�����
	InitEffect();

	//�p�[�e�B�N���̏�����
	InitParticle();

	//�^�C�}�[�̏�����
	InitTimer();

	//�X�R�A�̏�����
	InitScore();

	//�|�[�Y�̏�����
	InitPause();

	return S_OK;
}

void UninitGame(void)
{
	//BGM���I�����鏈��
	//StopSound();

	//g_pData--;
	//if (g_pData == 1)
	{
		//�w�i�̏I������
		UninitBG();
	}

	//�u���b�N�̏I������
	UninitBlock();

	//�|���S���̏I������
	UninitPlayer();

	//�e�̏I������
	UninitBullet();

	//�G�̏I������
	UninitEnemy();

	//�����̏I������
	UninitItem();

	//�G�̏I������
	//UninitEnemy();

	//�^�C�}�[�̏I������
	UninitTimer();

	//�X�R�A�̏I������
	UninitScore();

	//�|�[�Y�̏I������
	UninitPause();

	//�G�t�F�N�g�̏I������
	UninitEffect();

	//�p�[�e�B�N���̏I������
	UninitParticle();
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
		//g_pData--;
		//if (g_pData == 1)
		{
			//�w�i�̍X�V����
			UpdateBG();

			//UpdateResult();
		}

		//�u���b�N�X�V����
		UpdateBlock();

		//�|���S���̍X�V����
		UpdatePlayer();

		//�e�̍X�V����
		UpdateBullet();

		//�G�̏I������
		UpdateEnemy();

		//�����̍X�V����
		UpdateItem();

		//�G�̍X�V����
		//UpdateEnemy();

		//�^�C�}�[�̍X�V����
		UpdateTimer();

		//�G�t�F�N�g�̍X�V����
		UpdateEffect();

		//�X�R�A�̏I������
		UpdateScore();

		//�p�[�e�B�N���̍X�V����
		UpdateParticle();
	}
}

void DrawGame(void)
{
	//if (g_pData == 1)
	{
		//�w�i�̕`�揈��
		DrawBG();
		//DrawResult();
	}

	//�e�̕`�揈��
	DrawBullet();

	//�u���b�N�̕`�揈��
	DrawBlock();

	//�|���S���̕`�揈��
	DrawPlayer();

	//�G�̕`�揈��
	DrawEnemy();

	//�����̕`�揈��
	DrawItem();

	//�^�C�}�[�̕`�揈��
	DrawTimer();

	//�X�R�A�̕`�揈��
	DrawScore();

	//�G�t�F�N�g�̕`�揈��
	DrawEffect();

	//�p�[�e�B�N���̕`�揈��
	DrawParticle();

	if (g_bPause == true)
	{
		DrawPause();
		
	}
}
int GetGameNumber(void)
{
	return g_pData;
}
int GetGameNumber2(void)
{
	return S_OK; //g_aapData;
}
