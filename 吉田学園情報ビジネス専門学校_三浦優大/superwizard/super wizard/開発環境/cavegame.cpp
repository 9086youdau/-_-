#include "cavegame.h"
#include "bullet.h"
#include "Player.h"
#include "Explosion.h"
#include "bg.h"
#include "particle.h"
#include "input.h"
#include "Block.h"
#include "result.h"
#include "effect.h"
#include "enemy.h"
#include "Score.h"
#include "Pause.h"
#include "Timer.h"

//�O���[�o���ϐ�
bool g_bbPause = false;//�|�[�Y�����ǂ���
int g_apData;

HRESULT InitCaveGame(void)
{
	ITEM *pExplosion;
	pExplosion = GetItem();

	g_apData = 1;

	if (g_apData == 1)
	{
		//�w�i�̏�����
		InitBG();
	}

	//�e�̏���������
	InitBullet();

	//�G�̏���������
	InitEnemy();

	SETENEMY(D3DXVECTOR3(4100.0f, 200.0f, 0.0f), 1);
	SETENEMY(D3DXVECTOR3(1200.0f, 200.0f, 0.0f), 0);

	//�u���b�N�̏�����
	InitBlock();

	for (int nCntBlock = 0; nCntBlock < 15; nCntBlock++)
	{
		SetBlock(D3DXVECTOR3(650.0f + (nCntBlock * 60.0f), 800.0f, 0.0f), 30, 30, 8);
		SetBlock(D3DXVECTOR3(650.0f + (nCntBlock * 60.0f), 300.0f, 0.0f), 30, 30, 8);
	}

	for (int nCntBlock = 0; nCntBlock < 25; nCntBlock++)
	{
		SetBlock(D3DXVECTOR3(3000.0f + (nCntBlock * 60.0f), 970.0f, 0.0f), 30, 30, 0);
		//SetBlock(D3DXVECTOR3(3000.0f + (nCntBlock * 60.0f), 970.0f, 0.0f), 30, 30, 8);
	}

	SetBlock(D3DXVECTOR3(950.0f, 970.0f, 0.0f), 1000, 30, 1);
	SetBlock(D3DXVECTOR3(950.0f, 1030.0f, 0.0f), 1000, 30, 1);

	SetBlock(D3DXVECTOR3(400.0f, 900.0f, 0.0f), 30, 30, 8);

	//�N�b�p��̍����u���b�N
	SetBlock(D3DXVECTOR3(2960.0f, 970.0f, 0.0f), 30, 30, 8);
	SetBlock(D3DXVECTOR3(2960.0f, 910.0f, 0.0f), 30, 30, 8);
	SetBlock(D3DXVECTOR3(2900.0f, 970.0f, 0.0f), 30, 30, 8);
	SetBlock(D3DXVECTOR3(2900.0f, 910.0f, 0.0f), 30, 30, 8);
	SetBlock(D3DXVECTOR3(2960.0f, 850.0f, 0.0f), 30, 30, 8);
	SetBlock(D3DXVECTOR3(2900.0f, 850.0f, 0.0f), 30, 30, 8);

	//�N�b�p��̉E���u���b�N
	SetBlock(D3DXVECTOR3(4560.0f, 970.0f, 0.0f), 30, 30, 8);
	SetBlock(D3DXVECTOR3(4560.0f, 910.0f, 0.0f), 30, 30, 8);
	SetBlock(D3DXVECTOR3(4500.0f, 970.0f, 0.0f), 30, 30, 8);
	SetBlock(D3DXVECTOR3(4500.0f, 910.0f, 0.0f), 30, 30, 8);
	SetBlock(D3DXVECTOR3(4560.0f, 850.0f, 0.0f), 30, 30, 8);
	SetBlock(D3DXVECTOR3(4560.0f, 790.0f, 0.0f), 30, 30, 8);
	SetBlock(D3DXVECTOR3(4560.0f, 730.0f, 0.0f), 30, 30, 8);
	SetBlock(D3DXVECTOR3(4560.0f, 670.0f, 0.0f), 30, 30, 8);
	SetBlock(D3DXVECTOR3(4500.0f, 850.0f, 0.0f), 30, 30, 8);
	SetBlock(D3DXVECTOR3(4500.0f, 790.0f, 0.0f), 30, 30, 8);
	SetBlock(D3DXVECTOR3(4500.0f, 730.0f, 0.0f), 30, 30, 8);
	SetBlock(D3DXVECTOR3(4500.0f, 670.0f, 0.0f), 30, 30, 8);
	SetBlock(D3DXVECTOR3(4610.0f, 970.0f, 0.0f), 30, 30, 8);
	SetBlock(D3DXVECTOR3(4660.0f, 970.0f, 0.0f), 30, 30, 8);
	SetBlock(D3DXVECTOR3(4720.0f, 970.0f, 0.0f), 30, 30, 8);
	SetBlock(D3DXVECTOR3(4780.0f, 970.0f, 0.0f), 30, 30, 8);



	SetBlock(D3DXVECTOR3(40.0f, 400.0f, 0.0f), 30, 540, 7);
	SetBlock(D3DXVECTOR3(-20.0f, 400.0f, 0.0f), 30, 540, 7);

	//SetBlock(D3DXVECTOR3(300.0f, 400.0f, 0.0f), 30, 540, 7);

	SetBlock(D3DXVECTOR3(1050.0f, 600.0f, 0.0f), 30, 30, 2);


	SetBlock(D3DXVECTOR3(590.0f, 300.0f, 0.0f), 30, 30, 6);
	SetBlock(D3DXVECTOR3(1550.0f, 300.0f, 0.0f), 30, 30, 6);
	SetBlock(D3DXVECTOR3(590.0f, 800.0f, 0.0f), 30, 30, 9);
	SetBlock(D3DXVECTOR3(1550.0f, 800.0f, 0.0f), 30, 30, 9);

	//�t�@�C�A�[�o�[�]�[��
	SetBlock(D3DXVECTOR3(2100.0f, 870.0f, 0.0f), 30, 30, 6);
	SetBlock(D3DXVECTOR3(2300.0f, 870.0f, 0.0f), 30, 30, 9);
	SetBlock(D3DXVECTOR3(2500.0f, 870.0f, 0.0f), 30, 30, 9);
	SetBlock(D3DXVECTOR3(2700.0f, 830.0f, 0.0f), 30, 30, 6);




	//�|���S���̏���������
	InitPlayer();

	//�����̏�����
	InitItem();

	SetItem(D3DXVECTOR3(4700.0f, 900.0f, 0.0f), 4, pExplosion->move);

	//�G�t�F�N�g�̏�����
	InitEffect();

	//�p�[�e�B�N���̏�����
	InitParticle();

	//�X�R�A�̏�����
	InitScore();

	//�|�[�Y�̏�����
	InitPause();

	//�^�C�}�[�̏�����
	InitTimer();

	return S_OK;
}

void UninitCaveGame(void)
{

	g_apData = 0;

	//BGM���I�����鏈��
	//StopSound();

	//�w�i�̏I������
	UninitBG();

	//�u���b�N�̏I������
	UninitBlock();

	//�|���S���̏I������
	UninitPlayer();

	//�e�̏I������
	UninitBullet();

	//�����̏I������
	UninitItem();

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

	//�^�C�}�[�̏I������
	UninitTimer();
}

void UpdateCaveGame(void)
{
	//g_aData--;
	//�|�[�Y��ʂ̏���
	if (GetKeyboardTrigger(DIK_P) == true)
	{
		g_bbPause = g_bbPause ? false : true;
	}
	if (g_bbPause == true)
	{
		UpdatePause();
	}
	else
	{
		//�w�i�̍X�V����
		UpdateBG();
			
		//�u���b�N�X�V����
		UpdateBlock();

		//�|���S���̍X�V����
		UpdatePlayer();

		//�e�̍X�V����
		UpdateBullet();

		//�����̍X�V����
		UpdateItem();

		//�G�̍X�V����
		UpdateEnemy();

		//�X�R�A�̍X�V����
		UpdateScore();

		//�G�t�F�N�g�̍X�V����
		UpdateEffect();

		//�p�[�e�B�N���̍X�V����
		UpdateParticle();

		//�^�C�}�[�̍X�V����
		UpdateTimer();
	}
}

void DrawCaveGame(void)
{

	//�w�i�̕`�揈��
	DrawBG();

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

	//�w�i�̕`�揈��
	DrawScore();

	//�G�t�F�N�g�̕`�揈��
	DrawEffect();

	//�p�[�e�B�N���̕`�揈��
	DrawParticle();

	//�^�C�}�[�̕`�揈��
	DrawTimer();

	if (g_bbPause == true)
	{
		DrawPause();
	}
}
int GetcaveGameNumber(void)
{
	return g_apData;
}