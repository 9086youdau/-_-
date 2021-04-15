#include "game.h"
#include "bullet.h"
#include "input.h"
#include "result.h"
#include "model.h"
#include "wall.h"
#include "camera.h"
#include "Billboard.h"
#include "bullet.h"
#include "meshfield.h"
#include "light.h"
#include "stone.h"
#include "fade.h"
#include "enemy.h"
#include "Timer.h"
#include "gamepad.h"
#include "item.h"
#include "Coin.h"

//�O���[�o���ϐ�
bool g_bPause = false;//�|�[�Y�����ǂ���
int g_pData;
int nLife;
float fAngle;
D3DXVECTOR3 move;

HRESULT InitGame(void)
{
	g_pData = 1;

	if (g_pData == 1)
	{

	}
	g_bPause = false;

	InitBillboard();
	InitLight();
	InitCamera();
	InitModel();
	InitTimer();
	InitCoin();
	InitMeshfield();
	InitEnemy();

	//��ʘH�̃��f��
	SetEnemy(D3DXVECTOR3(0.0f, 0.0f, 0.0f),0);

	//���ʘH�̃��f��
	SetEnemy(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);

	Player *pModel;
	pModel = GetModel();

	InitStone();
	SetStone(D3DXVECTOR3(-390.0f, 0.0f, 350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);
	SetStone(D3DXVECTOR3(-410.0f, 0.0f, -450.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);
	SetStone(D3DXVECTOR3(410.0f, 0.0f, -450.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);
	SetStone(D3DXVECTOR3(390.0f, 0.0f, 350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);
	SetStone(D3DXVECTOR3(200.0f, 0.0f, 250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetStone(D3DXVECTOR3(-200.0f, 0.0f, 250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetStone(D3DXVECTOR3(200.0f, 0.0f, -250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetStone(D3DXVECTOR3(-200.0f, 0.0f, -250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);

	InitBullet();
	InitWall();
	//�͂ޟB
	SetWall(D3DXVECTOR3(500.0f, 0.0f, 270.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(D3DXVECTOR3(500.0f, 0.0f, -270.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(D3DXVECTOR3(-500.0f, 0.0f, 270.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(D3DXVECTOR3(-500.0f, 0.0f, -270.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(D3DXVECTOR3(270.0f, 0.0f, 500.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f), 0);
	SetWall(D3DXVECTOR3(-270.0f, 0.0f, 500.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f),0);
	SetWall(D3DXVECTOR3(270.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f), 0);
	SetWall(D3DXVECTOR3(-270.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f), 0);
	//��ʘH
	SetWall(D3DXVECTOR3(110.0f, 0.0f, 610.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(D3DXVECTOR3(110.0f, 0.0f, 880.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(D3DXVECTOR3(-110.0f, 0.0f, 610.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(D3DXVECTOR3(-110.0f, 0.0f, 880.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(D3DXVECTOR3(110.0f, 0.0f, 1150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(D3DXVECTOR3(-110.0f, 0.0f, 1150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	//���ʘH
	SetWall(D3DXVECTOR3(110.0f, 0.0f, -610.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(D3DXVECTOR3(110.0f, 0.0f,-880.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(D3DXVECTOR3(-110.0f, 0.0f, -610.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(D3DXVECTOR3(-110.0f, 0.0f, -880.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(D3DXVECTOR3(110.0f, 0.0f, -1150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(D3DXVECTOR3(-110.0f, 0.0f, -1150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	//�E�ʘH
	SetWall(D3DXVECTOR3(610.0f, 0.0f, 110.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f), 0);
	SetWall(D3DXVECTOR3(880.0f, 0.0f, 110.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f), 0);
	SetWall(D3DXVECTOR3(1150.0f, 0.0f, 110.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f), 0);
	SetWall(D3DXVECTOR3(-610.0f, 0.0f, 110.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f), 0);
	SetWall(D3DXVECTOR3(-880.0f, 0.0f, 110.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f), 0);
	SetWall(D3DXVECTOR3(-1150.0f, 0.0f, 110.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f), 0);
	//���ʘH
	SetWall(D3DXVECTOR3(610.0f, 0.0f, -110.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f), 0);
	SetWall(D3DXVECTOR3(880.0f, 0.0f, -110.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f), 0);
	SetWall(D3DXVECTOR3(1150.0f, 0.0f, -110.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f), 0);
	SetWall(D3DXVECTOR3(-610.0f, 0.0f, -110.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f), 0);
	SetWall(D3DXVECTOR3(-880.0f, 0.0f, -110.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f), 0);
	SetWall(D3DXVECTOR3(-1150.0f, 0.0f, -110.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f), 0);

	//���̃{�X����
	SetWall(D3DXVECTOR3(220.0f, 0.0f, -1270.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f), 0);
	SetWall(D3DXVECTOR3(-220.0f, 0.0f, -1270.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f), 0);
	SetWall(D3DXVECTOR3(350.0f, 0.0f, -1400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(D3DXVECTOR3(-350.0f, 0.0f, -1400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(D3DXVECTOR3(350.0f, 0.0f, -1670.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(D3DXVECTOR3(-350.0f, 0.0f, -1670.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(D3DXVECTOR3(350.0f, 0.0f, -1940.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(D3DXVECTOR3(-350.0f, 0.0f, -1940.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(D3DXVECTOR3(150.0f, 0.0f, -2100.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f), 0);
	SetWall(D3DXVECTOR3(-150.0f, 0.0f, -2100.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f), 0);


	//���̃{�X����
	SetWall(D3DXVECTOR3(220.0f, 0.0f, 1270.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f), 0);
	SetWall(D3DXVECTOR3(-220.0f, 0.0f, 1270.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f), 0);
	SetWall(D3DXVECTOR3(350.0f, 0.0f, 1400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(D3DXVECTOR3(-350.0f, 0.0f, 1400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(D3DXVECTOR3(350.0f, 0.0f, 1670.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(D3DXVECTOR3(-350.0f, 0.0f, 1670.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(D3DXVECTOR3(350.0f, 0.0f, 1940.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(D3DXVECTOR3(-350.0f, 0.0f, 1940.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetWall(D3DXVECTOR3(150.0f, 0.0f, 2100.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f), 0);
	SetWall(D3DXVECTOR3(-150.0f, 0.0f, 2100.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f), 0);

	InitItem();
	for (int nCntStone = 0; nCntStone < 10; nCntStone++)
	{
		SetItem(D3DXVECTOR3(0.0f, 50.0f, 500.0f + (nCntStone * 100.0f)), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	for (int nCntStone = 0; nCntStone < 10; nCntStone++)
	{
		SetItem(D3DXVECTOR3(0.0f, 50.0f, -500.0f + (nCntStone * -100.0f)), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}


	return S_OK;
}

void UninitGame(void)
{
	UninitBillboard();
	UninitCamera();
	UninitLight();
	UninitModel();
	UninitEnemy();
	UninitStone();
	UninitBullet();
	UninitTimer();
	UninitCoin();
	UninitWall();
	UninitMeshfield();
	UninitItem();
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
	}
	else
	{

		UpdateLight();
		UpdateCamera();
		UpdateModel();
		UpdateEnemy();
		UpdateStone();
		UpdateBullet();
		UpdateWall();
		UpdateBillboard();
		UpdateTimer();
		UpdateCoin();
		UpdateMeshfield();
		UpdateItem();
	}
}

void DrawGame(void)
{
	
	SetCamera();
	DrawEnemy();
	DrawMeshfield();
	DrawWall();
	DrawStone();
	DrawCoin();
	DrawTimer();
	DrawBullet();
	DrawBillboard();
	DrawItem();
	DrawModel();

	if (g_bPause == true)
	{
	}
}
int GetGameNumber(void)
{
	return g_pData;
}
int GetGameNumber2(void)
{
	return S_OK; 
}
