//================================================
//���f������[model.h]
// Author; miura yuudai
//
//================================================

#include "enemy.h"
#include "input.h"
#include "camera.h"
#include "Billboard.h"
#include "bullet.h"
#include "stone.h"
#include "model.h"

//=====================
//�O���[�o���ϐ�
//=====================
ENEMYPLAYER g_Player[56];//�ʒu
//MOTION_INFO g_Key;
//D3DXVECTOR3 aPos[2];
//D3DXVECTOR3 Pos;

//====================
//���f���̏���������
//====================
void InitEnemy(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCnt = 0; nCnt < 56; nCnt++)
	{
		//x�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX("data/MODEL/bodymiura.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player[nCnt].aModel[0].pBuffMat, NULL, &g_Player[nCnt].aModel[0].nNumMat, &g_Player[nCnt].aModel[0].pMesh);
		D3DXLoadMeshFromX("data/MODEL/atamamiura.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player[nCnt].aModel[1].pBuffMat, NULL, &g_Player[nCnt].aModel[1].nNumMat, &g_Player[nCnt].aModel[1].pMesh);
		D3DXLoadMeshFromX("data/MODEL/armmiura.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player[nCnt].aModel[2].pBuffMat, NULL, &g_Player[nCnt].aModel[2].nNumMat, &g_Player[nCnt].aModel[2].pMesh);
		D3DXLoadMeshFromX("data/MODEL/arm2miura.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player[nCnt].aModel[3].pBuffMat, NULL, &g_Player[nCnt].aModel[3].nNumMat, &g_Player[nCnt].aModel[3].pMesh);
		D3DXLoadMeshFromX("data/MODEL/handmiura.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player[nCnt].aModel[4].pBuffMat, NULL, &g_Player[nCnt].aModel[4].nNumMat, &g_Player[nCnt].aModel[4].pMesh);
		D3DXLoadMeshFromX("data/MODEL/udemiura.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player[nCnt].aModel[5].pBuffMat, NULL, &g_Player[nCnt].aModel[5].nNumMat, &g_Player[nCnt].aModel[5].pMesh);
		D3DXLoadMeshFromX("data/MODEL/arm3miura.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player[nCnt].aModel[6].pBuffMat, NULL, &g_Player[nCnt].aModel[6].nNumMat, &g_Player[nCnt].aModel[6].pMesh);
		D3DXLoadMeshFromX("data/MODEL/handRmiura.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player[nCnt].aModel[7].pBuffMat, NULL, &g_Player[nCnt].aModel[7].nNumMat, &g_Player[nCnt].aModel[7].pMesh);
		D3DXLoadMeshFromX("data/MODEL/legRmiura.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player[nCnt].aModel[8].pBuffMat, NULL, &g_Player[nCnt].aModel[8].nNumMat, &g_Player[nCnt].aModel[8].pMesh);
		D3DXLoadMeshFromX("data/MODEL/footmiuraL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player[nCnt].aModel[9].pBuffMat, NULL, &g_Player[nCnt].aModel[9].nNumMat, &g_Player[nCnt].aModel[9].pMesh);
		D3DXLoadMeshFromX("data/MODEL/leg2miuraR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player[nCnt].aModel[10].pBuffMat, NULL, &g_Player[nCnt].aModel[10].nNumMat, &g_Player[nCnt].aModel[10].pMesh);
		D3DXLoadMeshFromX("data/MODEL/legmiura.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player[nCnt].aModel[11].pBuffMat, NULL, &g_Player[nCnt].aModel[11].nNumMat, &g_Player[nCnt].aModel[11].pMesh);
		D3DXLoadMeshFromX("data/MODEL/footmiura.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player[nCnt].aModel[12].pBuffMat, NULL, &g_Player[nCnt].aModel[12].nNumMat, &g_Player[nCnt].aModel[12].pMesh);
		D3DXLoadMeshFromX("data/MODEL/leg2miura.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player[nCnt].aModel[13].pBuffMat, NULL, &g_Player[nCnt].aModel[13].nNumMat, &g_Player[nCnt].aModel[13].pMesh);
		D3DXLoadMeshFromX("data/MODEL/body2miura.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player[nCnt].aModel[14].pBuffMat, NULL, &g_Player[nCnt].aModel[14].nNumMat, &g_Player[nCnt].aModel[14].pMesh);

		//�ϐ�������
		g_Player[nCnt].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Player[nCnt].OldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Player[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Player[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Player[nCnt].rotmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Player[nCnt].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Player[nCnt].MaxModel = D3DXVECTOR3(-100000.0f, -100000.0f, -100000.0f);
		g_Player[nCnt].MinModel = D3DXVECTOR3(100000.0f, 100000.0f, 100000.0f);
		g_Player[nCnt].nCounterMotion = 0;
		g_Player[nCnt].aModel[0].bUse = false;
		g_Player[nCnt].motionType = MOTIONTYPE_NEUTRAL;
		g_Player[nCnt].bLoopMotion = false;
		g_Player[nCnt].nNumKey = 0;
		g_Player[nCnt].nKey = 0;
		//g_Player.motiontype = MOTIONTYPE_NEUTRAL;


		for (int nCntPlayer = 0; nCntPlayer < 15; nCntPlayer++)
		{
			g_Player[nCnt].aModel[nCntPlayer].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Player[nCnt].aModel[nCntPlayer].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Player[nCnt].aModel[nCntPlayer].bUse = false;
			g_Player[nCnt].aModel[nCntPlayer].nType = 0;
		}
		g_Player[nCnt].nNumModel = 15;

		D3DXMATERIAL *pMat;		// �}�e���A���ւ̃|�C���^

		// �}�e���A�����ɑ΂���|�C���^���擾
		pMat = (D3DXMATERIAL*)g_Player[0].aModel[0].pBuffMat->GetBufferPointer();

		//for (int nCntMat = 0; nCntMat < (int)g_Player[0].nNumModel; nCntMat++)
		//{
		//	if (pMat[nCntMat].pTextureFilename != NULL)
		//	{
		//		// �t�@�C�������g�p���ăe�N�X�`����ǂݍ���
		//		D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/body_enemyd.png", &g_Player[0].aModel[0].pTextureEnemy);
		//	}
		//}


		int nNumVtx;//���_��
		DWORD sizeFVF;//���_�t�H�[�}�b�g�̃T�C�Y
		BYTE *pVtxBuff;//���_�o�b�t�@�ւ̃|�C���^

		for (int nCntPlayer = 0; nCntPlayer < g_Player[nCnt].nNumModel; nCntPlayer++)
		{
			nNumVtx = g_Player[nCnt].aModel[nCntPlayer].pMesh->GetNumVertices();

			//���_�t�H�[�}�b�g�̃T�C�Y���擾
			sizeFVF = D3DXGetFVFVertexSize(g_Player[nCnt].aModel[nCntPlayer].pMesh->GetFVF());

			//���_�o�b�t�@�̃��b�N
			g_Player[0].aModel[nCntPlayer].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;//���_���W�̑��

				if (vtx.x > g_Player[nCnt].MaxModel.x)
				{
					g_Player[nCnt].MaxModel.x = vtx.x;
				}

				if (vtx.x < g_Player[nCnt].MinModel.x)
				{
					g_Player[nCnt].MinModel.x = vtx.x;
				}

				if (vtx.y > g_Player[nCnt].MaxModel.y)
				{
					g_Player[nCnt].MaxModel.y = vtx.y;
				}

				if (vtx.y < g_Player[nCnt].MinModel.y)
				{
					g_Player[nCnt].MinModel.y = vtx.y;
				}

				if (vtx.z > g_Player[nCnt].MaxModel.z)
				{
					g_Player[nCnt].MaxModel.z = vtx.z;
				}

				if (vtx.z < g_Player[nCnt].MinModel.z)
				{
					g_Player[nCnt].MinModel.z = vtx.z;
				}

				pVtxBuff += sizeFVF;//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			}
			g_Player[nCnt].aModel[nCntPlayer].pMesh->UnlockVertexBuffer();
		}
		//��ʘH���f��
		g_Player[0].Pos = D3DXVECTOR3(500.0f, 0.0f, 0.0f);
		g_Player[0].rot = D3DXVECTOR3(0.0f, 1.57f, 0.0f);

		g_Player[1].Pos = D3DXVECTOR3(-500.0f, 0.0f, 0.0f);
		g_Player[1].rot = D3DXVECTOR3(0.0f, -1.57f, 0.0f);
	}

}
//=======================
//���f���̏I������
//=======================
void UninitEnemy(void)
{
	for (int nCnt = 0; nCnt < 56; nCnt++)
	{
		for (int nCntPlayer = 0; nCntPlayer < g_Player[nCnt].nNumModel; nCntPlayer++)
		{
			//���_�̊J��
			if (g_Player[nCnt].aModel[nCntPlayer].pMesh != NULL)
			{
				g_Player[nCnt].aModel[nCntPlayer].pMesh->Release();
				g_Player[nCnt].aModel[nCntPlayer].pMesh = NULL;
			}

			//�ގ��̊J��
			if (g_Player[nCnt].aModel[nCntPlayer].pBuffMat != NULL)
			{
				g_Player[nCnt].aModel[nCntPlayer].pBuffMat->Release();
				g_Player[nCnt].aModel[nCntPlayer].pBuffMat = NULL;
			}
		}
	}
}
//=======================
//���f���̍X�V����
//=======================
void UpdateEnemy(void)
{
	//Camera *pCamera;
	//pCamera = GetCamera();

	//g_Player.Pos.x += g_Player.move.x;
	//g_Player.Pos.y += g_Player.move.y;
	//g_Player.Pos.z += g_Player.move.z;

	//�e�̒Ǐ]
	//SetPositionShadow(g_Player.nIdx, D3DXVECTOR3(g_Player.Pos.x, 0.0f, g_Player.Pos.z));

	//if (GetKeyboardPress(DIK_UP) == true)//�v���C���[�̉�]
	//{
	//	if (GetKeyboardPress(DIK_LEFT) == true)//�v���C���[�̉�]
	//	{
	//		g_Player.move.x -= cosf(pCamera->rot.y + D3DX_PI / 4) * 0.3f;
	//		g_Player.move.z += sinf(pCamera->rot.y + D3DX_PI / 4) * 0.3f;
	//		g_Player.rotDest.y = pCamera->rot.y + (D3DX_PI * 3 / 4);
	//	}
	//	// ���f���̈ړ�
	//	else if (GetKeyboardPress(DIK_RIGHT) == true)//�v���C���[�̉�]
	//	{
	//		g_Player.move.x += cosf(pCamera->rot.y - D3DX_PI / 4) * 0.3f;
	//		g_Player.move.z -= sinf(pCamera->rot.y - D3DX_PI / 4) * 0.3f;
	//		g_Player.rotDest.y = pCamera->rot.y - (D3DX_PI * 3 / 4);
	//	}
	//	else
	//	{
	//		g_Player.move.x += sinf(pCamera->rot.y) * 0.3f;
	//		g_Player.move.z += cosf(pCamera->rot.y) * 0.3f;
	//		g_Player.rotDest.y = pCamera->rot.y + D3DX_PI;
	//	}
	//}

	//else if (GetKeyboardPress(DIK_DOWN) == true)//�v���C���[�̉�]
	//{
	//	if (GetKeyboardPress(DIK_LEFT) == true)//�v���C���[�̉�]
	//	{
	//		g_Player.move.x += cosf(pCamera->rot.y + D3DX_PI * 3 / 4) * 0.3f;
	//		g_Player.move.z -= sinf(pCamera->rot.y + D3DX_PI * 3 / 4) * 0.3f;
	//		g_Player.rotDest.y = pCamera->rot.y + D3DX_PI / 4;
	//	}
	//	// ���f���̈ړ�
	//	else if (GetKeyboardPress(DIK_RIGHT) == true)//�v���C���[�̉�]
	//	{
	//		g_Player.move.x -= cosf(pCamera->rot.y - D3DX_PI * 3 / 4) * 0.3f;
	//		g_Player.move.z += sinf(pCamera->rot.y - D3DX_PI * 3 / 4) * 0.3f;
	//		g_Player.rotDest.y = pCamera->rot.y + D3DX_PI / -4;
	//	}
	//	else
	//	{
	//		g_Player.move.x += sinf(pCamera->rot.y - D3DX_PI) * 0.3f;
	//		g_Player.move.z += cosf(pCamera->rot.y - D3DX_PI) * 0.3f;
	//		g_Player.rotDest.y = pCamera->rot.y;
	//	}
	//}

	//else if (GetKeyboardPress(DIK_LEFT) == true)//�v���C���[�̉�]
	//{
	//	g_Player.move.x -= cosf(pCamera->rot.y) * 0.3f;
	//	g_Player.move.z += sinf(pCamera->rot.y) * 0.3f;
	//	g_Player.rotDest.y = pCamera->rot.y + (D3DX_PI / 2);

	//	D3DXVECTOR3 move;
	//	int nLife = 10;
	//	float fAngle;

	//	fAngle = (float)(rand() % 628 - 314) / 100.0f;//�����͈̔�
	//	move.x = sinf(fAngle)*0.1f;
	//	move.y = 0.0f;
	//	move.z = cosf(fAngle)*0.1f;
	//	SetBillboard(D3DXVECTOR3(g_Player.Pos.x, g_Player.Pos.y, g_Player.Pos.z), nLife, move, 0);
	//	SetBillboard(D3DXVECTOR3(g_Player.Pos.x, g_Player.Pos.y + 19, g_Player.Pos.z), nLife, move, 0);
	//}

	//else if (GetKeyboardPress(DIK_RIGHT) == true)//�v���C���[�̉�]
	//{
	//	g_Player.move.x += cosf(pCamera->rot.y) * 0.3f;
	//	g_Player.move.z -= sinf(pCamera->rot.y) * 0.3f;
	//	g_Player.rotDest.y = pCamera->rot.y + (D3DX_PI / -2);

	//	D3DXVECTOR3 move;
	//	int nLife = 10;
	//	float fAngle;

	//	fAngle = (float)(rand() % 628 - 314) / 100.0f;//�����͈̔�
	//	move.x = sinf(fAngle)*0.1f;
	//	move.y = 0.0f;
	//	move.z = cosf(fAngle)*0.1f;
	//	SetBillboard(D3DXVECTOR3(g_Player.Pos.x, g_Player.Pos.y, g_Player.Pos.z), nLife, move, 0);
	//	SetBillboard(D3DXVECTOR3(g_Player.Pos.x, g_Player.Pos.y + 19, g_Player.Pos.z), nLife, move, 0);
	//}

	//// ���f���̐���
	//if (GetKeyboardPress(DIK_K) == true)
	//{
	//	g_Player.rotDest.y += D3DX_PI / 18;
	//}
	//if (GetKeyboardPress(DIK_L) == true)
	//{
	//	g_Player.rotDest.y -= D3DX_PI / 18;
	//}

	//// �ړI�̉�]�p�̏��
	//if (g_Player.rotDest.y - g_Player.rot.y < -D3DX_PI)
	//{
	//	g_Player.rotDest.y += D3DX_PI * 2.0f;
	//}
	//else if (g_Player.rotDest.y - g_Player.rot.y > D3DX_PI)
	//{
	//	g_Player.rotDest.y -= D3DX_PI * 2.0f;
	//}

	//// �����̍X�V
	//g_Player.rot.y += (g_Player.rotDest.y - g_Player.rot.y) * 0.1f;

	//D3DXVECTOR3 pos;
	//int nLife;
	//float fAngle;
	//D3DXVECTOR3 move;

	//for (int nCntBillboard = 0; nCntBillboard < 8; nCntBillboard++)
	//{
	//	pos = D3DXVECTOR3(50.0f, 0.0f, -55.0f);//�ʒu
	//	nLife = 550 + rand() % 650;//�����������_��
	//	fAngle = (float)(rand() % 628 - 314) / 100.0f;//�����͈̔�
	//	move.x = sinf(fAngle)*0.1f;
	//	move.y = 0.01f;
	//	move.z = cosf(fAngle)*0.1f;
	//	SetBillboard(pos, nLife, move, 1);
	//}

	//if (GetKeyboardTrigger(DIK_M) == true)//�v���C���[�̉�]
	//{
	//	D3DXVECTOR3 pos;
	//	D3DXVECTOR3 move;
	//	int nLife = 105;

	//	pos = g_Player.Pos;//�ʒu
	//	move.x = -sinf(g_Player.rot.y)*5.5f;//�ړ���
	//	move.y = 0.0f;//�ړ���
	//	move.z = -cosf(g_Player.rot.y)*5.5f;//�ړ���
	//	SetBullet(pos, move, nLife);
	//}

	////if (g_Player.motiontype == MOTIONTYPE_RUN)
	////{
	////	//���݂̃L�[
	////	g_Player.aMotioninfo[0].aKeyinfo[0].aKey[0].fPosx = 0.0f;
	////	g_Player.aMotioninfo[0].aKeyinfo[0].aKey[0].fPosy = 0.0f;
	////	g_Player.aMotioninfo[0].aKeyinfo[0].aKey[0].fPosz = 0.0f;

	////	g_Player.aMotioninfo[0].aKeyinfo[0].aKey[0].fRotx = 0.0f;
	////	g_Player.aMotioninfo[0].aKeyinfo[0].aKey[0].fRoty = 0.0f;
	////	g_Player.aMotioninfo[0].aKeyinfo[0].aKey[0].fRotz = 0.0f;

	////	//���̃L�[
	////	g_Player.aMotioninfo[0].aKeyinfo[1].aKey[0].fPosx = 0.0f;
	////	g_Player.aMotioninfo[0].aKeyinfo[1].aKey[0].fPosy = -160.0f;
	////	g_Player.aMotioninfo[0].aKeyinfo[1].aKey[0].fPosz = 0.0f;

	////	g_Player.aMotioninfo[0].aKeyinfo[1].aKey[0].fRotx = 0.0f;
	////	g_Player.aMotioninfo[0].aKeyinfo[1].aKey[0].fRoty = 0.0f;
	////	g_Player.aMotioninfo[0].aKeyinfo[1].aKey[0].fRotz = 0.0f;

	////	//����
	////	float Key = g_Player.aMotioninfo[0].aKeyinfo[1].aKey[0].fPosy - g_Player.aMotioninfo[0].aKeyinfo[0].aKey[0].fPosy;

	////	g_Player.nCounterMotion++;//�A�j���[�V�������v���X���Ă���
	////	g_Player.aMotioninfo[0].aKeyinfo[0].nFrame++;

	////	//���߂�l
	////	g_Player.aMotioninfo[0].aKeyinfo[1].aKey[0].fPosy = g_Player.aMotioninfo[0].aKeyinfo[0].aKey[0].fPosy + Key * (g_Player.nCounterMotion % 10 == 0 / g_Player.aMotioninfo[0].aKeyinfo[0].nFrame);
	////}

	//// ���݂̉�]�p�̏��
	//if (g_Player.rot.y < -D3DX_PI)
	//{
	//	g_Player.rot.y += D3DX_PI * 2.0f;
	//}
	//else if (g_Player.rot.y > D3DX_PI)
	//{
	//	g_Player.rot.y -= D3DX_PI * 2.0f;
	//}

	//// �ړ��ʂ̌���
	//g_Player.move.x += (0.0f - g_Player.move.x) * 0.1f;
	//g_Player.move.z += (0.0f - g_Player.move.z) * 0.1f;

	// ���[�V�����J�E���^�[�̉��Z
	g_Player[0].nCounterMotion++;

	// ���[�V�����̍X�V
	UpdateEnemyMotion(g_Player[0].motionType);

	g_Player[0].motionType = MOTIONTYPE_NEUTRAL;

	//if (g_Player[0].bUse == false)
	{
		g_Player[0].OldPos = g_Player[0].Pos;

		for (int nCntPlayer = 0; nCntPlayer < 56; nCntPlayer++)
		{
			//�e�p�[�c�̊K�w�\���ݒ�
			g_Player[nCntPlayer].aModel[0].nIdxModelParent = -1;//�e�̃C���f�b�N�X��ݒ� //��
			g_Player[nCntPlayer].aModel[0].Pos = D3DXVECTOR3(0.0f, 85.0f, 0.0f);//�ʒu�̐ݒ�
			g_Player[nCntPlayer].aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̐ݒ�

			g_Player[nCntPlayer].aModel[1].nIdxModelParent = 0;//�e�̃C���f�b�N�X��ݒ�@//��
			g_Player[nCntPlayer].aModel[1].Pos = D3DXVECTOR3(-1.0f, 57.0f, -4.0f);//�ʒu�̐ݒ�
			g_Player[nCntPlayer].aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̐ݒ�

			g_Player[nCntPlayer].aModel[2].nIdxModelParent = 0;//�e�̃C���f�b�N�X��ݒ� //�E�r
			g_Player[nCntPlayer].aModel[2].Pos = D3DXVECTOR3(-10.5f, 50.5f, 0.0f);//�ʒu�̐ݒ�
			g_Player[nCntPlayer].aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̐ݒ�

			g_Player[nCntPlayer].aModel[3].nIdxModelParent = 2;//�e�̃C���f�b�N�X��ݒ�@//�E��
			g_Player[nCntPlayer].aModel[3].Pos = D3DXVECTOR3(-8.0f, -18.0f, -2.5f);//�����̐ݒ�
			g_Player[nCntPlayer].aModel[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̐ݒ�

			g_Player[nCntPlayer].aModel[4].nIdxModelParent = 3;//�e�̃C���f�b�N�X��ݒ� //���r
			g_Player[nCntPlayer].aModel[4].Pos = D3DXVECTOR3(-5.0f, -29.0f, 3.0f);//�ʒu�̐ݒ�
			g_Player[nCntPlayer].aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̐ݒ�

			g_Player[nCntPlayer].aModel[5].nIdxModelParent = 0;//�e�̃C���f�b�N�X��ݒ�@//����
			g_Player[nCntPlayer].aModel[5].Pos = D3DXVECTOR3(8.5f, 50.5f, 0.0f);//�ʒu�̐ݒ�
			g_Player[nCntPlayer].aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̐ݒ�

			g_Player[nCntPlayer].aModel[6].nIdxModelParent = 5;//�e�̃C���f�b�N�X��ݒ�@//�E��
			g_Player[nCntPlayer].aModel[6].Pos = D3DXVECTOR3(8.0f, -18.0f, 0.0f);//�ʒu�̐ݒ�
			g_Player[nCntPlayer].aModel[6].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̐ݒ�

			g_Player[nCntPlayer].aModel[7].nIdxModelParent = 6;//�e�̃C���f�b�N�X��ݒ�@//�E��
			g_Player[nCntPlayer].aModel[7].Pos = D3DXVECTOR3(5.0f, -29.0f, 3.0f);//�ʒu�̐ݒ�
			g_Player[nCntPlayer].aModel[7].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̐ݒ�

			g_Player[nCntPlayer].aModel[8].nIdxModelParent = 14;//�e�̃C���f�b�N�X��ݒ� //����
			g_Player[nCntPlayer].aModel[8].Pos = D3DXVECTOR3(0.0f, 4.0f, 4.0f);//�ʒu�̐ݒ�
			g_Player[nCntPlayer].aModel[8].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̐ݒ�

			g_Player[nCntPlayer].aModel[9].nIdxModelParent = 11;//�e�̃C���f�b�N�X��ݒ�@//����
			g_Player[nCntPlayer].aModel[9].Pos = D3DXVECTOR3(3.0f, -32.0f, -4.0f);//�ʒu�̐ݒ�
			g_Player[nCntPlayer].aModel[9].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̐ݒ�

			g_Player[nCntPlayer].aModel[10].nIdxModelParent = 9;//�e�̃C���f�b�N�X��ݒ�@//�E�I
			g_Player[nCntPlayer].aModel[10].Pos = D3DXVECTOR3(6.0f, -36.0f, 1.0f);//�ʒu�̐ݒ�
			g_Player[nCntPlayer].aModel[10].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̐ݒ�

			g_Player[nCntPlayer].aModel[11].nIdxModelParent = 14;//�e�̃C���f�b�N�X��ݒ�@//���I
			g_Player[nCntPlayer].aModel[11].Pos = D3DXVECTOR3(-2.0f, 6.0f, 4.0f);//�ʒu�̐ݒ�
			g_Player[nCntPlayer].aModel[11].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̐ݒ�

			g_Player[nCntPlayer].aModel[12].nIdxModelParent = 8;//�e�̃C���f�b�N�X��ݒ�@//�E�G
			g_Player[nCntPlayer].aModel[12].Pos = D3DXVECTOR3(-4.0f, -30.0f, -5.0f);//�ʒu�̐ݒ�
			g_Player[nCntPlayer].aModel[12].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̐ݒ�

			g_Player[nCntPlayer].aModel[13].nIdxModelParent = 12;//�e�̃C���f�b�N�X��ݒ�@//���G
			g_Player[nCntPlayer].aModel[13].Pos = D3DXVECTOR3(-4.0f, -36.0f, 0.0f);//�ʒu�̐ݒ�
			g_Player[nCntPlayer].aModel[13].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̐ݒ�

			g_Player[nCntPlayer].aModel[14].nIdxModelParent = 0;//�e�̃C���f�b�N�X��ݒ�@//��
			g_Player[nCntPlayer].aModel[14].Pos = D3DXVECTOR3(0.0f, 2.0f, 0.0f);//�ʒu�̐ݒ�
			g_Player[nCntPlayer].aModel[14].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̐ݒ�
		}

		int nCntEneVec = 0;

		for (int nCount = 0; nCount < ENEMYMMAX; nCount++)
		{
			//aPos�̒l�ݒ�
			g_Player[nCntEneVec].aPos[0 + (nCount * 4)] = D3DXVECTOR3(g_Player[nCntEneVec].Pos.x + g_Player[nCntEneVec].MinModel.x, 0.0f, g_Player[nCntEneVec].Pos.z + g_Player[nCntEneVec].MinModel.z);
			g_Player[nCntEneVec].aPos[1 + (nCount * 4)] = D3DXVECTOR3(g_Player[nCntEneVec].Pos.x + g_Player[nCntEneVec].MinModel.x, 0.0f, g_Player[nCntEneVec].Pos.z + g_Player[nCntEneVec].MaxModel.z);
			g_Player[nCntEneVec].aPos[2 + (nCount * 4)] = D3DXVECTOR3(g_Player[nCntEneVec].Pos.x + g_Player[nCntEneVec].MaxModel.x, 0.0f, g_Player[nCntEneVec].Pos.z + g_Player[nCntEneVec].MaxModel.z);
			g_Player[nCntEneVec].aPos[3 + (nCount * 4)] = D3DXVECTOR3(g_Player[nCntEneVec].Pos.x + g_Player[nCntEneVec].MaxModel.x, 0.0f, g_Player[nCntEneVec].Pos.z + g_Player[nCntEneVec].MinModel.z);

			//�O�ς̎�
			g_Player[nCntEneVec].Vec[0 + (nCount * 4)] = g_Player[nCntEneVec].aPos[1 + (nCount * 4)] - g_Player[nCntEneVec].aPos[0 + (nCount * 4)];
			g_Player[nCntEneVec].Vec[1 + (nCount * 4)] = g_Player[nCntEneVec].aPos[2 + (nCount * 4)] - g_Player[nCntEneVec].aPos[1 + (nCount * 4)];
			g_Player[nCntEneVec].Vec[2 + (nCount * 4)] = g_Player[nCntEneVec].aPos[3 + (nCount * 4)] - g_Player[nCntEneVec].aPos[2 + (nCount * 4)];
			g_Player[nCntEneVec].Vec[3 + (nCount * 4)] = g_Player[nCntEneVec].aPos[0 + (nCount * 4)] - g_Player[nCntEneVec].aPos[3 + (nCount * 4)];

			//CollisionVecEnemy(&g_Player[nCntEneVec].Pos, &g_Player[nCntEneVec].OldPos, &g_Player[nCntEneVec].move, g_Player[nCntEneVec].MaxModel.x, g_Player[nCntEneVec].MinModel.x, g_Player[nCntEneVec].MaxModel.z, g_Player[nCntEneVec].MinModel.z, g_Player[nCntEneVec].MaxModel.y, g_Player[nCntEneVec].MinModel.y);

			nCntEneVec += 1;
		}
	}
	Player *pModel;
	pModel = GetModel();
	
}
//=======================
//���f���̕`�揈��
//=======================
void DrawEnemy(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//�}�e���A���ւ̃|�C���^
	D3DXMATERIAL *pMat;

	//���݂̃}�e���A���ۑ��p
	D3DMATERIAL9 matDef;

	for (int nCnt = 0; nCnt < 56; nCnt++)
	{
		if (g_Player[nCnt].aModel[0].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Player[nCnt].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player[nCnt].rot.y, g_Player[nCnt].rot.x, g_Player[nCnt].rot.z);

			D3DXMatrixMultiply(&g_Player[nCnt].mtxWorld, &g_Player[nCnt].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Player[nCnt].Pos.x, g_Player[nCnt].Pos.y, g_Player[nCnt].Pos.z);

			D3DXMatrixMultiply(&g_Player[nCnt].mtxWorld, &g_Player[nCnt].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Player[nCnt].mtxWorld);

			//���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			for (int nCntModel = 0; nCntModel < g_Player[nCnt].nNumModel; nCntModel++)
			{
				D3DXMATRIX mtxRotModel, mtxTransModel;//�v�Z�p�}�g���b�N�X
				D3DXMATRIX mtxParent;//�e�̃}�g���b�N�X

				//�e�p�[�c�̃��[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_Player[nCnt].aModel[nCntModel].mtxWorld);

				//�e�p�[�c�̌����𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_Player[nCnt].aModel[nCntModel].rot.y, g_Player[nCnt].aModel[nCntModel].rot.x, g_Player[nCnt].aModel[nCntModel].rot.z);
				D3DXMatrixMultiply(&g_Player[nCnt].aModel[nCntModel].mtxWorld, &g_Player[nCnt].aModel[nCntModel].mtxWorld, &mtxRotModel);

				//�e�p�[�c�̈ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTransModel, g_Player[nCnt].aModel[nCntModel].Pos.x, g_Player[nCnt].aModel[nCntModel].Pos.y, g_Player[nCnt].aModel[nCntModel].Pos.z);
				D3DXMatrixMultiply(&g_Player[nCnt].aModel[nCntModel].mtxWorld, &g_Player[nCnt].aModel[nCntModel].mtxWorld, &mtxTransModel);

				//�e�p�[�c�̐e�̃}�g���b�N�X��ݒ�
				if (g_Player[nCnt].aModel[nCntModel].nIdxModelParent != -1)
				{
					mtxParent = g_Player[nCnt].aModel[g_Player[nCnt].aModel[nCntModel].nIdxModelParent].mtxWorld;
				}
				else
				{
					mtxParent = g_Player[nCnt].mtxWorld;//�v���C���[�̃}�g���b�N�X��ݒ�
				}

				//�Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
				D3DXMatrixMultiply(&g_Player[nCnt].aModel[nCntModel].mtxWorld, &g_Player[nCnt].aModel[nCntModel].mtxWorld, &mtxParent);

				//�e�p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_Player[nCnt].aModel[nCntModel].mtxWorld);

				pMat = (D3DXMATERIAL*)g_Player[nCnt].aModel[nCntModel].pBuffMat->GetBufferPointer();

				//�}�e���A���f�[�^�ւ̃|�C���^���擾
				for (int nCntMat = 0; nCntMat < (int)g_Player[nCnt].aModel[nCntModel].nNumMat; nCntMat++)
				{
					if (g_Player[nCnt].aModel[nCntMat].nType == 0)
					{
						//�}�e���A���̐ݒ�
						pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

						//�e�N�X�`���̐ݒ�
						pDevice->SetTexture(0, g_Player[0].aModel[nCntMat].pTextureEnemy);

						//���f���p�[�c�̕`��
						g_Player[0].aModel[nCntModel].pMesh->DrawSubset(nCntMat);
					}
				}
			}
		}
	}

	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}
ENEMYPLAYER *GetEnemy(void)
{
	return &g_Player[0];
}
void SetEnemy(D3DXVECTOR3 pos, int nType)
{
	BYTE *pVtxBuff;//���_�o�b�t�@�ւ̃|�C���^

	 //�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	int nCnt = 0;

	for (int nCntMat = 0; nCntMat < (int)g_Player[nCnt].aModel[nCnt].nNumMat; nCntMat++)
	{
		// ���_�o�b�t�@�����b�N
		g_Player[nCntMat].aModel[nCntMat].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCnt = 0; nCnt < 56; nCnt++)
		{
			if (g_Player[nCnt].aModel[nCntMat].bUse == false)//�e���g�p���Ă��邩�ǂ���
			{
				if (nType == 0)
				{
					//�ʒu�ݒ�
					g_Player[nCnt].aModel[nCntMat].Pos = pos;

					//�^�C�v����
					g_Player[nCnt].aModel[nCntMat].nType = nType;

					//�e�̎g�p
					g_Player[nCnt].aModel[nCntMat].bUse = true;
					break;
				}
			}
		}
		// ���_�o�b�t�@���A�����b�N
		g_Player[nCntMat].aModel[nCntMat].pMesh->UnlockVertexBuffer();
	}

}
//==============================================================================
// ���[�V�����̐ݒ�
//==============================================================================
void SetEnemyMotion(MOTIONTYPE motionType)
{
	//g_player.motionType = motionType;
	if (motionType == MOTIONTYPE_NEUTRAL)
	{// �ҋ@���[�V����
		g_Player[0].bLoopMotion = true;	// ���[�v����
		g_Player[0].nNumKey = 2;	// �L�[��
		g_Player[0].aMotionInfo[0].aKeySet[0].nFrame = 40;	// �t���[����

		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[0].fPosX = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[0].fPosY = -13.50f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[0].fPosZ = -13.90f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[0].fRotX = -0.88f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[0].fRotY = 0.00f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[0].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[1].fPosX = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[1].fPosY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[1].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[1].fRotX = 0.28f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[1].fRotY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[1].fRotZ = 0.0f;
	
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[2].fPosX = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[2].fPosY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[2].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[2].fRotX = 1.29f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[2].fRotY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[2].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[3].fPosX = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[3].fPosY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[3].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[3].fRotX = 0.94f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[3].fRotY = -0.72f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[3].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[4].fPosX = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[4].fPosY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[4].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[4].fRotX = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[4].fRotY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[4].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[5].fPosX = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[5].fPosY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[5].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[5].fRotX = 2.14f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[5].fRotY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[5].fRotZ = 0.35f;

		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[6].fPosX = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[6].fPosY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[6].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[6].fRotX = -0.28f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[6].fRotY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[6].fRotZ = -0.94f;

		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[7].fPosX = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[7].fPosY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[7].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[7].fRotX = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[7].fRotY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[7].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[8].fPosX = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[8].fPosY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[8].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[8].fRotX = 1.04f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[8].fRotY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[8].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[9].fPosX = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[9].fPosY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[9].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[9].fRotX = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[9].fRotY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[9].fRotZ = 0.0f;
	
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[10].fPosX = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[10].fPosY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[10].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[10].fRotX = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[10].fRotY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[10].fRotZ = 0.0f;
	
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[11].fPosX = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[11].fPosY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[11].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[11].fRotX = -0.35f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[11].fRotY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[11].fRotZ = 0.0f;
	
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[12].fPosX = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[12].fPosY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[12].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[12].fRotX = -0.53f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[12].fRotY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[12].fRotZ = 0.0f;
	
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[13].fPosX = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[13].fPosY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[13].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[13].fRotX = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[13].fRotY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[13].fRotZ = 0.0f;
	
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[14].fPosX = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[14].fPosY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[14].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[14].fRotX = 0.44f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[14].fRotY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[0].aKey[14].fRotZ = 0.0f;
	
	
		g_Player[0].aMotionInfo[0].aKeySet[1].nFrame = 8;	// �t���[����
		
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[0].fPosX = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[0].fPosY = -13.50f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[0].fPosZ = -13.90f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[0].fRotX = -0.88f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[0].fRotY = 0.00f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[0].fRotZ = 0.0f;
	
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[1].fPosX = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[1].fPosY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[1].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[1].fRotX = 0.28f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[1].fRotY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[1].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[2].fPosX = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[2].fPosY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[2].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[2].fRotX = 1.29f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[2].fRotY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[2].fRotZ = 0.0f;
	
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[3].fPosX = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[3].fPosY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[3].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[3].fRotX = 0.94f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[3].fRotY = -0.72f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[3].fRotZ = 0.0f;
	
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[4].fPosX = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[4].fPosY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[4].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[4].fRotX = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[4].fRotY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[4].fRotZ = 0.0f;
	
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[5].fPosX = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[5].fPosY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[5].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[5].fRotX = 2.14f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[5].fRotY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[5].fRotZ = 0.35f;

		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[6].fPosX = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[6].fPosY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[6].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[6].fRotX = -0.28f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[6].fRotY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[6].fRotZ = -0.94f;
	
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[7].fPosX = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[7].fPosY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[7].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[7].fRotX = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[7].fRotY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[7].fRotZ = 0.0f;
	
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[8].fPosX = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[8].fPosY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[8].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[8].fRotX = 1.04f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[8].fRotY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[8].fRotZ = 0.0f;
		
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[9].fPosX = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[9].fPosY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[9].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[9].fRotX = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[9].fRotY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[9].fRotZ = 0.0f;
	
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[10].fPosX = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[10].fPosY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[10].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[10].fRotX = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[10].fRotY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[10].fRotZ = 0.0f;
	
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[11].fPosX = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[11].fPosY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[11].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[11].fRotX = -0.35f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[11].fRotY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[11].fRotZ = 0.0f;
		
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[12].fPosX = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[12].fPosY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[12].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[12].fRotX = -0.53f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[12].fRotY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[12].fRotZ = 0.0f;
	
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[13].fPosX = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[13].fPosY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[13].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[13].fRotX = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[13].fRotY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[13].fRotZ = 0.0f;
		
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[14].fPosX = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[14].fPosY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[14].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[14].fRotX = 0.44f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[14].fRotY = 0.0f;
		g_Player[0].aMotionInfo[0].aKeySet[1].aKey[14].fRotZ = 0.0f;
	
	}
	else if (g_Player[0].motionType == MOTIONTYPE_MOVE)
	{// �ړ����[�V����
		g_Player[0].bLoopMotion = true;					// ���[�v����
		g_Player[0].nNumKey = 4;							// �L�[��
		g_Player[0].aMotionInfo[1].aKeySet[0].nFrame = 8;	// �t���[����

		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[0].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[0].fPosY = -7.20f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[0].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[0].fRotX = -0.22f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[0].fRotY = 0.25f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[0].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[1].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[1].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[1].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[1].fRotX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[1].fRotY = -0.19f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[1].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[2].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[2].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[2].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[2].fRotX = -1.29f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[2].fRotY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[2].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[3].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[3].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[3].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[3].fRotX = 1.29f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[3].fRotY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[3].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[4].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[4].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[4].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[4].fRotX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[4].fRotY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[4].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[5].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[5].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[5].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[5].fRotX = 0.50f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[5].fRotY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[5].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[6].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[6].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[6].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[6].fRotX = 1.01f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[6].fRotY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[6].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[7].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[7].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[7].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[7].fRotX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[7].fRotY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[7].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[8].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[8].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[8].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[8].fRotX = 1.17f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[8].fRotY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[8].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[9].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[9].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[9].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[9].fRotX = -0.85f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[9].fRotY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[9].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[10].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[10].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[10].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[10].fRotX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[10].fRotY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[10].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[11].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[11].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[11].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[11].fRotX = -0.44f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[11].fRotY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[11].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[12].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[12].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[12].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[12].fRotX = -0.44f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[12].fRotY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[12].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[13].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[13].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[13].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[13].fRotX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[13].fRotY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[13].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[14].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[14].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[14].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[14].fRotX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[14].fRotY = -0.31f;
		g_Player[0].aMotionInfo[1].aKeySet[0].aKey[14].fRotZ = 0.03f;

		g_Player[0].aMotionInfo[1].aKeySet[1].nFrame = 10;	// �t���[����

		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[0].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[0].fPosY = -19.10f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[0].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[0].fRotX = -0.22f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[0].fRotY = 0.25f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[0].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[1].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[1].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[1].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[1].fRotX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[1].fRotY = -0.19f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[1].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[2].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[2].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[2].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[2].fRotX = -0.54f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[2].fRotY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[2].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[3].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[3].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[3].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[3].fRotX = 1.29f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[3].fRotY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[3].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[4].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[4].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[4].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[4].fRotX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[4].fRotY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[4].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[5].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[5].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[5].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[5].fRotX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[5].fRotY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[5].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[6].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[6].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[6].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[6].fRotX = 1.54f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[6].fRotY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[6].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[7].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[7].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[7].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[7].fRotX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[7].fRotY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[7].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[8].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[8].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[8].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[8].fRotX = 1.13f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[8].fRotY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[8].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[9].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[9].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[9].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[9].fRotX = -1.82f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[9].fRotY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[9].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[10].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[10].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[10].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[10].fRotX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[10].fRotY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[10].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[11].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[11].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[11].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[11].fRotX = 0.41f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[11].fRotY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[11].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[12].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[12].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[12].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[12].fRotX = -1.32f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[12].fRotY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[12].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[13].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[13].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[13].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[13].fRotX = 0.41f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[13].fRotY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[13].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[14].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[14].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[14].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[14].fRotX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[14].fRotY = -0.31f;
		g_Player[0].aMotionInfo[1].aKeySet[1].aKey[14].fRotZ = 0.0f;


		g_Player[0].aMotionInfo[1].aKeySet[2].nFrame = 8;	// �t���[����

		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[0].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[0].fPosY = -10.90f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[0].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[0].fRotX = -0.22f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[0].fRotY = -0.25f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[0].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[1].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[1].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[1].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[1].fRotX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[1].fRotY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[1].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[2].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[2].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[2].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[2].fRotX = 0.57f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[2].fRotY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[2].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[3].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[3].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[3].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[3].fRotX = 0.88f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[3].fRotY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[3].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[4].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[4].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[4].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[4].fRotX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[4].fRotY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[4].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[5].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[5].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[5].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[5].fRotX = -0.91f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[5].fRotY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[5].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[6].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[6].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[6].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[6].fRotX = 1.01f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[6].fRotY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[6].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[7].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[7].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[7].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[7].fRotX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[7].fRotY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[7].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[8].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[8].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[8].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[8].fRotX = -0.57f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[8].fRotY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[8].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[9].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[9].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[9].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[9].fRotX = -0.47f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[9].fRotY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[9].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[10].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[10].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[10].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[10].fRotX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[10].fRotY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[10].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[11].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[11].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[11].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[11].fRotX = 1.23f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[11].fRotY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[11].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[12].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[12].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[12].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[12].fRotX = -0.50f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[12].fRotY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[12].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[13].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[13].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[13].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[13].fRotX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[13].fRotY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[13].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[14].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[14].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[14].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[14].fRotX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[14].fRotY = 0.35f;
		g_Player[0].aMotionInfo[1].aKeySet[2].aKey[14].fRotZ = 0.06f;



		g_Player[0].aMotionInfo[1].aKeySet[3].nFrame = 10;	// �t���[����

		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[0].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[0].fPosY = -18.20f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[0].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[0].fRotX = -0.22f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[0].fRotY = -0.25f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[0].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[1].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[1].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[1].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[1].fRotX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[1].fRotY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[1].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[2].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[2].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[2].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[2].fRotX = 0.03f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[2].fRotY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[2].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[3].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[3].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[3].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[3].fRotX = 0.88f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[3].fRotY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[3].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[4].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[4].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[4].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[4].fRotX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[4].fRotY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[4].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[5].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[5].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[5].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[5].fRotX = -0.44f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[5].fRotY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[5].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[6].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[6].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[6].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[6].fRotX = 1.01f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[6].fRotY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[6].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[7].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[7].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[7].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[7].fRotX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[7].fRotY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[7].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[8].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[8].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[8].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[8].fRotX = 0.16f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[8].fRotY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[8].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[9].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[9].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[9].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[9].fRotX = -1.13f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[9].fRotY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[9].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[10].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[10].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[10].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[10].fRotX = 0.38f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[10].fRotY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[10].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[11].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[11].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[11].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[11].fRotX = 1.04f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[11].fRotY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[11].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[12].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[12].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[12].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[12].fRotX = -1.73f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[12].fRotY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[12].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[13].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[13].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[13].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[13].fRotX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[13].fRotY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[13].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[14].fPosX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[14].fPosY = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[14].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[14].fRotX = 0.0f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[14].fRotY = 0.35f;
		g_Player[0].aMotionInfo[1].aKeySet[3].aKey[14].fRotZ = 0.0f;

	}

	else if (g_Player[0].motionType == MOTIONTYPE_ACTION)
	{// �ړ����[�V����
		g_Player[0].bLoopMotion = true;					// ���[�v����
		g_Player[0].nNumKey = 5;							// �L�[��
		g_Player[0].aMotionInfo[2].aKeySet[0].nFrame = 5;	// �t���[����

		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[0].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[0].fPosY = -5.50f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[0].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[0].fRotX = 0.28f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[0].fRotY = 0.50f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[0].fRotZ = 0.0f;
		
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[1].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[1].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[1].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[1].fRotX = 0.13f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[1].fRotY = 0.03f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[1].fRotZ = 0.0f;
		
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[2].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[2].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[2].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[2].fRotX = -2.83f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[2].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[2].fRotZ = -0.35f;
		
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[3].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[3].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[3].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[3].fRotX = 0.44f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[3].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[3].fRotZ = 0.69f;
		
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[4].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[4].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[4].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[4].fRotX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[4].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[4].fRotZ = 0.0f;
	
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[5].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[5].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[5].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[5].fRotX = 2.64f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[5].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[5].fRotZ = 0.60f;
		
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[6].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[6].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[6].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[6].fRotX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[6].fRotY = -0.94f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[6].fRotZ = -1.76f;
		
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[7].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[7].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[7].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[7].fRotX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[7].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[7].fRotZ = 0.0f;
		
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[8].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[8].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[8].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[8].fRotX = 1.19f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[8].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[8].fRotZ = -0.0f;
		
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[9].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[9].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[9].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[9].fRotX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[9].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[9].fRotZ = 0.0f;
	
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[10].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[10].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[10].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[10].fRotX = 0.47f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[10].fRotY = 0.35f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[10].fRotZ = 0.0f;
	
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[11].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[11].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[11].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[11].fRotX = -0.53f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[11].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[11].fRotZ = 0.0f;
	
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[12].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[12].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[12].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[12].fRotX = -1.92f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[12].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[12].fRotZ = 0.0f;
		
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[13].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[13].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[13].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[13].fRotX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[13].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[13].fRotZ = 0.0f;
	
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[14].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[14].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[14].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[14].fRotX = -0.16f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[14].fRotY = -0.79f;
		g_Player[0].aMotionInfo[2].aKeySet[0].aKey[14].fRotZ = 0.25f;
	
		
	
		g_Player[0].aMotionInfo[2].aKeySet[1].nFrame = 25;	// �t���[����
	
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[0].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[0].fPosY = -5.50f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[0].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[0].fRotX = 0.44f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[0].fRotY = 0.50f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[0].fRotZ = 0.0f;
	
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[1].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[1].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[1].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[1].fRotX = 0.13f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[1].fRotY = 0.03f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[1].fRotZ = 0.0f;
		
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[2].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[2].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[2].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[2].fRotX = 2.83f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[2].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[2].fRotZ = -0.35f;
		
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[3].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[3].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[3].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[3].fRotX = 0.44f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[3].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[3].fRotZ = 0.69f;
	
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[4].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[4].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[4].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[4].fRotX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[4].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[4].fRotZ = 0.0f;
	
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[5].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[5].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[5].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[5].fRotX = 2.55f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[5].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[5].fRotZ = 0.60f;
	
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[6].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[6].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[6].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[6].fRotX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[6].fRotY = -0.94f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[6].fRotZ = -1.76f;

		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[7].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[7].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[7].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[7].fRotX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[7].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[7].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[8].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[8].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[8].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[8].fRotX = 1.19f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[8].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[8].fRotZ = -0.0f;
	
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[9].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[9].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[9].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[9].fRotX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[9].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[9].fRotZ = 0.0f;
	
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[10].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[10].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[10].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[10].fRotX = 0.47f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[10].fRotY = 0.35f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[10].fRotZ = 0.0f;
	
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[11].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[11].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[11].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[11].fRotX = -0.53f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[11].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[11].fRotZ = 0.0f;
		
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[12].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[12].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[12].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[12].fRotX = -1.92f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[12].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[12].fRotZ = 0.0f;
	
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[13].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[13].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[13].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[13].fRotX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[13].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[13].fRotZ = 0.0f;
	
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[14].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[14].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[14].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[14].fRotX = -0.16f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[14].fRotY = -0.79f;
		g_Player[0].aMotionInfo[2].aKeySet[1].aKey[14].fRotZ = 0.25f;
	
		g_Player[0].aMotionInfo[2].aKeySet[2].nFrame = 25;	// �t���[����
		
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[0].fPosX = -0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[0].fPosY = -13.50f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[0].fPosZ = -13.90f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[0].fRotX = -0.88f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[0].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[0].fRotZ = 0.0f;
	
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[1].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[1].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[1].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[1].fRotX = 0.28f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[1].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[1].fRotZ = 0.0f;
		
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[2].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[2].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[2].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[2].fRotX = 1.29f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[2].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[2].fRotZ = 0.0f;
	
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[3].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[3].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[3].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[3].fRotX = 0.94f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[3].fRotY = -0.72f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[3].fRotZ = 0.0f;
	
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[4].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[4].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[4].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[4].fRotX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[4].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[4].fRotZ = 0.0f;
		
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[5].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[5].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[5].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[5].fRotX = 2.14f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[5].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[5].fRotZ = 0.35f;
		
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[6].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[6].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[6].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[6].fRotX = -0.28f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[6].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[6].fRotZ = -0.94f;
		
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[7].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[7].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[7].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[7].fRotX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[7].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[7].fRotZ = 0.0f;
	
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[8].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[8].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[8].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[8].fRotX = 1.04f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[8].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[8].fRotZ = 0.0f;
		
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[9].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[9].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[9].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[9].fRotX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[9].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[9].fRotZ = 0.0f;
		
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[10].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[10].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[10].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[10].fRotX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[10].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[10].fRotZ = 0.0f;
		
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[11].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[11].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[11].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[11].fRotX = -0.35f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[11].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[11].fRotZ = 0.0f;
		
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[12].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[12].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[12].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[12].fRotX = -0.53f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[12].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[12].fRotZ = 0.0f;
	
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[13].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[13].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[13].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[13].fRotX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[13].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[13].fRotZ = 0.0f;
		
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[14].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[14].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[14].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[14].fRotX = 0.44f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[14].fRotY = -0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[2].aKey[14].fRotZ = 0.0f;
	
	
		g_Player[0].aMotionInfo[2].aKeySet[3].nFrame = 25;	// �t���[����
	
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[0].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[0].fPosY = -3.30f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[0].fPosZ = -28.50f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[0].fRotX = -1.26f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[0].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[0].fRotZ = 0.0f;
		
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[1].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[1].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[1].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[1].fRotX = -0.28f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[1].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[1].fRotZ = 0.0f;
	
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[2].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[2].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[2].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[2].fRotX = 0.50f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[2].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[2].fRotZ = 0.0f;
	
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[3].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[3].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[3].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[3].fRotX = 0.94f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[3].fRotY = -0.72f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[3].fRotZ = 0.0f;
	
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[4].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[4].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[4].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[4].fRotX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[4].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[4].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[5].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[5].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[5].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[5].fRotX = 1.29f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[5].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[5].fRotZ = 0.35f;
	
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[6].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[6].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[6].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[6].fRotX = -0.28f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[6].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[6].fRotZ = -0.94f;
		
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[7].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[7].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[7].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[7].fRotX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[7].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[7].fRotZ = 0.0f;
	
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[8].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[8].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[8].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[8].fRotX = 1.04f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[8].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[8].fRotZ = 0.0f;
		
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[9].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[9].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[9].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[9].fRotX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[9].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[9].fRotZ = 0.0f;
	
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[10].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[10].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[10].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[10].fRotX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[10].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[10].fRotZ = 0.0f;
		
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[11].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[11].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[11].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[11].fRotX = -0.82f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[11].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[11].fRotZ = 0.0f;
	
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[12].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[12].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[12].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[12].fRotX = -0.53f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[12].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[12].fRotZ = 0.0f;
		
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[13].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[13].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[13].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[13].fRotX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[13].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[13].fRotZ = 0.0f;
	
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[14].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[14].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[14].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[14].fRotX = 0.44f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[14].fRotY = -0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[3].aKey[14].fRotZ = 0.0f;
	
	
		g_Player[0].aMotionInfo[2].aKeySet[4].nFrame = 25;	// �t���[����
	
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[0].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[0].fPosY = -3.30f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[0].fPosZ = -28.50f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[0].fRotX = -1.26f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[0].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[0].fRotZ = 0.0f;
		
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[1].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[1].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[1].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[1].fRotX = -0.28f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[1].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[1].fRotZ = 0.0f;
		
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[2].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[2].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[2].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[2].fRotX = 0.50f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[2].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[2].fRotZ = 0.0f;
	
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[3].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[3].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[3].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[3].fRotX = 0.94f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[3].fRotY = -0.72f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[3].fRotZ = 0.0f;
	
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[4].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[4].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[4].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[4].fRotX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[4].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[4].fRotZ = 0.0f;
	
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[5].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[5].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[5].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[5].fRotX = 1.29f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[5].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[5].fRotZ = 0.35f;

		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[6].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[6].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[6].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[6].fRotX = -0.28f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[6].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[6].fRotZ = -0.94f;
		
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[7].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[7].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[7].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[7].fRotX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[7].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[7].fRotZ = 0.0f;
		
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[8].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[8].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[8].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[8].fRotX = 1.04f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[8].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[8].fRotZ = 0.0f;
	
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[9].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[9].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[9].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[9].fRotX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[9].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[9].fRotZ = 0.0f;
		
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[10].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[10].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[10].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[10].fRotX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[10].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[10].fRotZ = 0.0f;
		
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[11].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[11].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[11].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[11].fRotX = -0.82f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[11].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[11].fRotZ = 0.0f;

		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[12].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[12].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[12].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[12].fRotX = -0.53f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[12].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[12].fRotZ = 0.0f;
	
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[13].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[13].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[13].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[13].fRotX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[13].fRotY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[13].fRotZ = 0.0f;
		
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[14].fPosX = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[14].fPosY = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[14].fPosZ = 0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[14].fRotX = 0.44f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[14].fRotY = -0.0f;
		g_Player[0].aMotionInfo[2].aKeySet[4].aKey[14].fRotZ = 0.0f;
	
	}
}

//==============================================================================
// ���[�V�����̍X�V
//==============================================================================
void UpdateEnemyMotion(MOTIONTYPE motionType)
{
	SetEnemyMotion(motionType);

	// ���[�J���ϐ��錾
	//D3DXVECTOR3 pos[MAX_KEY][MODEL_PARTS];
	//D3DXVECTOR3 rot[MAX_KEY][MODEL_PARTS];
	//float fFrame[MAX_KEY];
	//float fCntMotion = (float)g_player.nCounterMotion;
	//KEY *pKey = &g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[0];
	//KEY *pKeyDest = &g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[0];
	//KEY *pKeyTop = &g_player.aMotionInfo[motionType].aKeySet[0].aKey[0];

	// �ϐ����
	//for (int nCnt = 0; nCnt < g_player.nNumKey; nCnt++)
	//{
	//	for (int nCntModel = 0; nCntModel < g_player.nNumModel; nCntModel++)
	//	{
	//		pos[nCnt][nCntModel].x = g_player.aMotionInfo[motionType].aKeySet[nCnt].aKey[nCntModel].fPosX;
	//		pos[nCnt][nCntModel].y = g_player.aMotionInfo[motionType].aKeySet[nCnt].aKey[nCntModel].fPosY;
	//		pos[nCnt][nCntModel].z = g_player.aMotionInfo[motionType].aKeySet[nCnt].aKey[nCntModel].fPosZ;
	//		rot[nCnt][nCntModel].x = g_player.aMotionInfo[motionType].aKeySet[nCnt].aKey[nCntModel].fRotX;
	//		rot[nCnt][nCntModel].y = g_player.aMotionInfo[motionType].aKeySet[nCnt].aKey[nCntModel].fRotY;
	//		rot[nCnt][nCntModel].z = g_player.aMotionInfo[motionType].aKeySet[nCnt].aKey[nCntModel].fRotZ;
	//	}
	//	fFrame[nCnt] = (float)g_player.aMotionInfo[motionType].aKeySet[nCnt].nFrame;
	//}

	for (int nCnt = 0; nCnt < ENEMY_PARTS; nCnt++)
	{
		if (g_Player[0].nKey == g_Player[0].nNumKey - 1 && g_Player[0].bLoopMotion == true)
		{
			g_Player[0].aModel[nCnt].Pos.x += (g_Player[0].aMotionInfo[motionType].aKeySet[0].aKey[nCnt].fPosX - g_Player[0].aMotionInfo[motionType].aKeySet[g_Player[0].nKey].aKey[nCnt].fPosX) / (float)g_Player[0].aMotionInfo[motionType].aKeySet[g_Player[0].nKey].nFrame;
			g_Player[0].aModel[nCnt].Pos.y += (g_Player[0].aMotionInfo[motionType].aKeySet[0].aKey[nCnt].fPosY - g_Player[0].aMotionInfo[motionType].aKeySet[g_Player[0].nKey].aKey[nCnt].fPosY) / (float)g_Player[0].aMotionInfo[motionType].aKeySet[g_Player[0].nKey].nFrame;
			g_Player[0].aModel[nCnt].Pos.z += (g_Player[0].aMotionInfo[motionType].aKeySet[0].aKey[nCnt].fPosZ - g_Player[0].aMotionInfo[motionType].aKeySet[g_Player[0].nKey].aKey[nCnt].fPosZ) / (float)g_Player[0].aMotionInfo[motionType].aKeySet[g_Player[0].nKey].nFrame;
			g_Player[0].aModel[nCnt].rot.x = g_Player[0].aMotionInfo[motionType].aKeySet[g_Player[0].nKey].aKey[nCnt].fRotX + (g_Player[0].aMotionInfo[motionType].aKeySet[0].aKey[nCnt].fRotX - g_Player[0].aMotionInfo[motionType].aKeySet[g_Player[0].nKey].aKey[nCnt].fRotX) * ((float)g_Player[0].nCounterMotion / (float)g_Player[0].aMotionInfo[motionType].aKeySet[g_Player[0].nKey].nFrame);
			g_Player[0].aModel[nCnt].rot.y = g_Player[0].aMotionInfo[motionType].aKeySet[g_Player[0].nKey].aKey[nCnt].fRotY + (g_Player[0].aMotionInfo[motionType].aKeySet[0].aKey[nCnt].fRotY - g_Player[0].aMotionInfo[motionType].aKeySet[g_Player[0].nKey].aKey[nCnt].fRotY) * ((float)g_Player[0].nCounterMotion / (float)g_Player[0].aMotionInfo[motionType].aKeySet[g_Player[0].nKey].nFrame);
			g_Player[0].aModel[nCnt].rot.z = g_Player[0].aMotionInfo[motionType].aKeySet[g_Player[0].nKey].aKey[nCnt].fRotZ + (g_Player[0].aMotionInfo[motionType].aKeySet[0].aKey[nCnt].fRotZ - g_Player[0].aMotionInfo[motionType].aKeySet[g_Player[0].nKey].aKey[nCnt].fRotZ) * ((float)g_Player[0].nCounterMotion / (float)g_Player[0].aMotionInfo[motionType].aKeySet[g_Player[0].nKey].nFrame);
			//g_player.aModel[nCnt].rot.x = pKey->fPosX + (pKeyTop->fPosX - pKey->fPosX) * (fCntMotion / fFrame[g_player.nKey]);
			//g_player.aModel
			//g_player.aModel[nCnt].rot.x = rot[g_player.nKey][nCnt].x + (rot[0][nCnt].x - rot[g_player.nKey][nCnt].x) * (fCntMotion / fFrame[g_player.nKey]);
			//g_player.aModel[nCnt].rot.y = rot[g_player.nKey][nCnt].y + (rot[0][nCnt].y - rot[g_player.nKey][nCnt].y) * (fCntMotion / fFrame[g_player.nKey]);
			//g_player.aModel[nCnt].rot.z = rot[g_player.nKey][nCnt].z + (rot[0][nCnt].z - rot[g_player.nKey][nCnt].z) * (fCntMotion / fFrame[g_player.nKey]);
		}
		else
		{
			g_Player[0].aModel[nCnt].Pos.x += (g_Player[0].aMotionInfo[motionType].aKeySet[g_Player[0].nKey + 1].aKey[nCnt].fPosX - g_Player[0].aMotionInfo[motionType].aKeySet[g_Player[0].nKey].aKey[nCnt].fPosX) / (float)g_Player[0].aMotionInfo[motionType].aKeySet[g_Player[0].nKey].nFrame;
			g_Player[0].aModel[nCnt].Pos.y += (g_Player[0].aMotionInfo[motionType].aKeySet[g_Player[0].nKey + 1].aKey[nCnt].fPosY - g_Player[0].aMotionInfo[motionType].aKeySet[g_Player[0].nKey].aKey[nCnt].fPosY) / (float)g_Player[0].aMotionInfo[motionType].aKeySet[g_Player[0].nKey].nFrame;
			g_Player[0].aModel[nCnt].Pos.z += (g_Player[0].aMotionInfo[motionType].aKeySet[g_Player[0].nKey + 1].aKey[nCnt].fPosZ - g_Player[0].aMotionInfo[motionType].aKeySet[g_Player[0].nKey].aKey[nCnt].fPosZ) / (float)g_Player[0].aMotionInfo[motionType].aKeySet[g_Player[0].nKey].nFrame;
			g_Player[0].aModel[nCnt].rot.x = g_Player[0].aMotionInfo[motionType].aKeySet[g_Player[0].nKey].aKey[nCnt].fRotX + (g_Player[0].aMotionInfo[motionType].aKeySet[g_Player[0].nKey + 1].aKey[nCnt].fRotX - g_Player[0].aMotionInfo[motionType].aKeySet[g_Player[0].nKey].aKey[nCnt].fRotX) * ((float)g_Player[0].nCounterMotion / (float)g_Player[0].aMotionInfo[motionType].aKeySet[g_Player[0].nKey].nFrame);
			g_Player[0].aModel[nCnt].rot.y = g_Player[0].aMotionInfo[motionType].aKeySet[g_Player[0].nKey].aKey[nCnt].fRotY + (g_Player[0].aMotionInfo[motionType].aKeySet[g_Player[0].nKey + 1].aKey[nCnt].fRotY - g_Player[0].aMotionInfo[motionType].aKeySet[g_Player[0].nKey].aKey[nCnt].fRotY) * ((float)g_Player[0].nCounterMotion / (float)g_Player[0].aMotionInfo[motionType].aKeySet[g_Player[0].nKey].nFrame);
			g_Player[0].aModel[nCnt].rot.z = g_Player[0].aMotionInfo[motionType].aKeySet[g_Player[0].nKey].aKey[nCnt].fRotZ + (g_Player[0].aMotionInfo[motionType].aKeySet[g_Player[0].nKey + 1].aKey[nCnt].fRotZ - g_Player[0].aMotionInfo[motionType].aKeySet[g_Player[0].nKey].aKey[nCnt].fRotZ) * ((float)g_Player[0].nCounterMotion / (float)g_Player[0].aMotionInfo[motionType].aKeySet[g_Player[0].nKey].nFrame);
			//g_player.aModel[nCnt].rot.x = rot[g_player.nKey][nCnt].x + (rot[g_player.nKey + 1][nCnt].x - rot[g_player.nKey][nCnt].x) * (fCntMotion / fFrame[g_player.nKey]);
			//g_player.aModel[nCnt].rot.y = rot[g_player.nKey][nCnt].y + (rot[g_player.nKey + 1][nCnt].y - rot[g_player.nKey][nCnt].y) * (fCntMotion / fFrame[g_player.nKey]);
			//g_player.aModel[nCnt].rot.z = rot[g_player.nKey][nCnt].z + (rot[g_player.nKey + 1][nCnt].z - rot[g_player.nKey][nCnt].z) * (fCntMotion / fFrame[g_player.nKey]);


			if (g_Player[0].nKey == g_Player[0].nNumKey - 1 && g_Player[0].bLoopMotion == false)
			{
				break;
			}
		}

		if (g_Player[0].nCounterMotion == g_Player[0].aMotionInfo[motionType].aKeySet[g_Player[0].nKey].nFrame)
		{
			g_Player[0].nCounterMotion = 0;

			if (g_Player[0].nKey == g_Player[0].nNumKey - 1 && g_Player[0].bLoopMotion == true)
			{
				g_Player[0].nKey = 0;
			}
			else
			{
				g_Player[0].nKey++;
			}
		}
	}
}
//==============================================================================
// �O�ς𗘗p���������蔻��
//==============================================================================
bool CollisionVecSord(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, float fWidthMax, float fWidthMin, float fDepthMax, float fDepthMin, float fHeightMax, float fHeightMin)
{
	bool bLand = false;

	D3DXVECTOR3 pos = *pPos;// ����Ώۂ̈ʒu

	ENEMYPLAYER	*pPlayer;
	pPlayer = GetEnemy();

	Player *pModel;
	pModel = GetModel();

	int nCntModelEnemy = 0;
	int g_nCntModelEnemy = 0;

	// �I�u�W�F�N�g�Ƃ̓����蔻��
		for (int nCntModel = 0; nCntModel < ENEMYMAXVEC; nCntModel++)
		{
			if (nCntModel == 0 + g_nCntModelEnemy)
			{// ����
				g_Player[nCntModelEnemy].g_Vec[nCntModel] = pos + D3DXVECTOR3(fWidthMax, 0.0f, 0.0f) - g_Player[nCntModelEnemy].aPos[nCntModel];
			}
			else if (nCntModel == 1 + g_nCntModelEnemy)
			{// ����
				g_Player[nCntModelEnemy].g_Vec[nCntModel] = pos + D3DXVECTOR3(0.0f, 0.0f, fDepthMin) - g_Player[nCntModelEnemy].aPos[nCntModel];
			}
			else if (nCntModel == 2 + g_nCntModelEnemy)
			{// �E��
				g_Player[nCntModelEnemy].g_Vec[nCntModel] = pos + D3DXVECTOR3(fWidthMin, 0.0f, 0.0f) - g_Player[nCntModelEnemy].aPos[nCntModel];
			}
			else if (nCntModel == 3 + g_nCntModelEnemy)
			{// ��O
				g_Player[nCntModelEnemy].g_Vec[nCntModel] = pos + D3DXVECTOR3(0.0f, 0.0f, fDepthMax) - g_Player[nCntModelEnemy].aPos[nCntModel];
			}

			// ���l���u+�v�̎��A�����蔻�肪�L��
			g_Player[nCntModelEnemy].PlayerVec[nCntModel] = (g_Player[nCntModelEnemy].Vec[nCntModel].z * g_Player[nCntModelEnemy].g_Vec[nCntModel].x) - (g_Player[nCntModelEnemy].Vec[nCntModel].x * g_Player[nCntModelEnemy].g_Vec[nCntModel].z);

			if (pPos->y <= g_Player[nCntModelEnemy].Pos.y + g_Player[nCntModelEnemy].MaxModel.y - fHeightMin && pPos->y > g_Player[nCntModelEnemy].Pos.y + g_Player[nCntModelEnemy].MinModel.y - fHeightMax)
			{
				if (g_Player[nCntModelEnemy].PlayerVec[0 + (nCntModelEnemy * 4)] > 0.0f && g_Player[nCntModelEnemy].PlayerVec[1 + (nCntModelEnemy * 4)] > 0.0f && g_Player[nCntModelEnemy].PlayerVec[2 + (nCntModelEnemy * 4)] > 0.0f && g_Player[nCntModelEnemy].PlayerVec[3 + (nCntModelEnemy * 4)] > 0.0f)
				{
					if (g_Player[nCntModelEnemy].aModel[0].bUse == true)
					{
						if (pPos->x > pPosOld->x && pPosOld->x < g_Player[nCntModelEnemy].Pos.x + g_Player[nCntModelEnemy].MinModel.x)
						{// ����	
							 pPos->x = g_Player[nCntModelEnemy].Pos.x + g_Player[nCntModelEnemy].MinModel.x - fWidthMax;
							//g_Player[nCntModelEnemy].aModel[0].bUse = false;

						}
						else if (pPos->x < pPosOld->x && pPosOld->x > g_Player[nCntModelEnemy].Pos.x + g_Player[nCntModelEnemy].MaxModel.x)
						{// �E��	
							pPos->x = g_Player[nCntModelEnemy].Pos.x + g_Player[nCntModelEnemy].MaxModel.x - fWidthMin;
							//Player->aModel[0].bUse = false;

						}
						else if (pPos->z <= pPosOld->z && pPos->z > g_Player[nCntModelEnemy].Pos.z)
						{// ����
							pPos->z = g_Player[nCntModelEnemy].Pos.z + g_Player[nCntModelEnemy].MaxModel.z - fDepthMin;
							//g_Player[nCntModelEnemy].aModel[0].bUse = false;

						}
						else if (pPos->z >= pPosOld->z && pPos->z < g_Player[nCntModelEnemy].Pos.z)
						{// ��O
							pPos->z = g_Player[nCntModelEnemy].Pos.z + g_Player[nCntModelEnemy].MinModel.z - fDepthMax;
							//g_Player[nCntModelEnemy].aModel[0].bUse = false;
						}
					}
				}
			}

			if (nCntModel == 3 + (4 * nCntModelEnemy))
			{
				nCntModelEnemy += 1;
				g_nCntModelEnemy += 4;
			}
		}
	return bLand;
}

//bool CollisionVecModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, float fWidthMax, float fWidthMin, float fDepthMax, float fDepthMin, float fHeightMax, float fHeightMin)
//{
//	bool bLand = false;
//
//	D3DXVECTOR3 pos = *pPos;// ����Ώۂ̈ʒu
//
//	ENEMYPLAYER	*pPlayer;
//	pPlayer = GetEnemy();
//
//	Player *pModel;
//	pModel = GetModel();
//
//	int nCntEnemy = 0;
//	int g_nCntEnemy = 0;
//
//	if (pModel->motionType == MOTIONTYPE_MODELMOVE)
//	{
//		// �I�u�W�F�N�g�Ƃ̓����蔻��
//		for (int nCnt = 0; nCnt < ENEMYMAXVEC; nCnt++)
//		{
//			if (nCnt == 0 + g_nCntEnemy)
//			{// ����
//				g_Player[nCntEnemy].g_Vec[nCnt] = pos + D3DXVECTOR3(fWidthMax, 0.0f, 0.0f) - g_Player[nCntEnemy].aPos[nCnt];
//			}
//			else if (nCnt == 1 + g_nCntEnemy)
//			{// ����
//				g_Player[nCntEnemy].g_Vec[nCnt] = pos + D3DXVECTOR3(0.0f, 0.0f, fDepthMin) - g_Player[nCntEnemy].aPos[nCnt];
//			}
//			else if (nCnt == 2 + g_nCntEnemy)
//			{// �E��
//				g_Player[nCntEnemy].g_Vec[nCnt] = pos + D3DXVECTOR3(fWidthMin, 0.0f, 0.0f) - g_Player[nCntEnemy].aPos[nCnt];
//			}
//			else if (nCnt == 3 + g_nCntEnemy)
//			{// ��O
//				g_Player[nCntEnemy].g_Vec[nCnt] = pos + D3DXVECTOR3(0.0f, 0.0f, fDepthMax) - g_Player[nCntEnemy].aPos[nCnt];
//			}
//
//			//aVec[nCnt] = pos - g_aPos[nCnt];	// �ʂ̎n�_�ƑΏۂ̃x�N�g��
//
//			// ���l���u+�v�̎��A�����蔻�肪�L��
//			g_Player[nCntEnemy].PlayerVec[nCnt] = (g_Player[nCntEnemy].Vec[nCnt].z * g_Player[nCntEnemy].g_Vec[nCnt].x) - (g_Player[nCntEnemy].Vec[nCnt].x * g_Player[nCntEnemy].g_Vec[nCnt].z);
//
//			if (pPos->y <= g_Player[nCntEnemy].Pos.y + g_Player[nCntEnemy].MaxModel.y - fHeightMin && pPos->y > g_Player[nCntEnemy].Pos.y + g_Player[nCntEnemy].MinModel.y - fHeightMax)
//			{
//				if (g_Player[nCntEnemy].PlayerVec[0 + (nCntEnemy * 4)] > 0.0f && g_Player[nCntEnemy].PlayerVec[1 + (nCntEnemy * 4)] > 0.0f && g_Player[nCntEnemy].PlayerVec[2 + (nCntEnemy * 4)] > 0.0f && g_Player[nCntEnemy].PlayerVec[3 + (nCntEnemy * 4)] > 0.0f)
//				{
//					if (g_Player[nCntEnemy].aModel[0].bUse == true)
//					{
//						if (pPos->x > pPosOld->x && pPosOld->x < g_Player[nCntEnemy].Pos.x + g_Player[nCntEnemy].MinModel.x)
//						{// ����	
//							pPos->x = g_Player[nCntEnemy].Pos.x + g_Player[nCntEnemy].MinModel.x - fWidthMax;
//						}
//						else if (pPos->x < pPosOld->x && pPosOld->x > g_Player[nCntEnemy].Pos.x + g_Player[nCntEnemy].MaxModel.x)
//						{// �E��	
//							pPos->x = g_Player[nCntEnemy].Pos.x + g_Player[nCntEnemy].MaxModel.x - fWidthMin;
//						}
//						else if (pPos->z <= pPosOld->z && pPos->z > g_Player[nCntEnemy].Pos.z)
//						{// ����
//							pPos->z = g_Player[nCntEnemy].Pos.z + g_Player[nCntEnemy].MaxModel.z - fDepthMin;
//						}
//						else if (pPos->z >= pPosOld->z && pPos->z < g_Player[nCntEnemy].Pos.z)
//						{// ��O
//							pPos->z = g_Player[nCntEnemy].Pos.z + g_Player[nCntEnemy].MinModel.z - fDepthMax;
//							//g_Player[nCntEnemy].aModel[0].bUse = false;
//						}
//					}
//				}
//			}
//
//			if (nCnt == 3 + (4 * nCntEnemy))
//			{
//				nCntEnemy += 1;
//				g_nCntEnemy += 4;
//			}
//		}
//	}
//
//	return bLand;
//}
//==============================================================================
// �O�ς𗘗p�������̓����蔻��
//==============================================================================
//bool CollisionVecSord(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, float fWidthMax, float fWidthMin, float fDepthMax, float fDepthMin, float fHeightMax, float fHeightMin)
//{
//	bool bLand = false;
//
//	D3DXVECTOR3 pos = *pPos;// ����Ώۂ̈ʒu
//
//	ENEMYPLAYER	*pPlayer;
//	pPlayer = GetEnemy();
//
//	Player *pModel;
//	pModel = GetModel();
//
//	int nCntModelEnemy = 0;
//	int g_nCntModelEnemy = 0;
//
//	//if (pModel->motionType == MOTIONTYPE_MODELACTION)
//	{
//		// �I�u�W�F�N�g�Ƃ̓����蔻��
//		for (int nCntModel = 0; nCntModel < ENEMYMAXVEC; nCntModel++)
//		{
//			if (nCntModel == 0 + g_nCntModelEnemy)
//			{// ����
//				g_Player[nCntModelEnemy].g_Vec[nCntModel] = pos + D3DXVECTOR3(fWidthMax, 0.0f, 0.0f) - g_Player[nCntModelEnemy].aPos[nCntModel];
//			}
//			else if (nCntModel == 1 + g_nCntModelEnemy)
//			{// ����
//				g_Player[nCntModelEnemy].g_Vec[nCntModel] = pos + D3DXVECTOR3(0.0f, 0.0f, fDepthMin) - g_Player[nCntModelEnemy].aPos[nCntModel];
//			}
//			else if (nCntModel == 2 + g_nCntModelEnemy)
//			{// �E��
//				g_Player[nCntModelEnemy].g_Vec[nCntModel] = pos + D3DXVECTOR3(fWidthMin, 0.0f, 0.0f) - g_Player[nCntModelEnemy].aPos[nCntModel];
//			}
//			else if (nCntModel == 3 + g_nCntModelEnemy)
//			{// ��O
//				g_Player[nCntModelEnemy].g_Vec[nCntModel] = pos + D3DXVECTOR3(0.0f, 0.0f, fDepthMax) - g_Player[nCntModelEnemy].aPos[nCntModel];
//			}
//
//			//aVec[nCnt] = pos - g_aPos[nCnt];	// �ʂ̎n�_�ƑΏۂ̃x�N�g��
//
//			//nCntModelEnemy = 0;
//			//g_nCntModelEnemy = 0;
//
//			// ���l���u+�v�̎��A�����蔻�肪�L��
//			g_Player[nCntModelEnemy].PlayerVec[nCntModel] = (g_Player[nCntModelEnemy].Vec[nCntModel].z * g_Player[nCntModelEnemy].g_Vec[nCntModel].x) - (g_Player[nCntModelEnemy].Vec[nCntModel].x * g_Player[nCntModelEnemy].g_Vec[nCntModel].z);
//
//			if (pPos->y <= g_Player[nCntModelEnemy].Pos.y + g_Player[nCntModelEnemy].MaxModel.y - fHeightMin && pPos->y > g_Player[nCntModelEnemy].Pos.y + g_Player[nCntModelEnemy].MinModel.y - fHeightMax)
//			{
//				if (g_Player[nCntModelEnemy].PlayerVec[0 + (nCntModelEnemy * 4)] > 0.0f && g_Player[nCntModelEnemy].PlayerVec[1 + (nCntModelEnemy * 4)] > 0.0f && g_Player[nCntModelEnemy].PlayerVec[2 + (nCntModelEnemy * 4)] > 0.0f && g_Player[nCntModelEnemy].PlayerVec[3 + (nCntModelEnemy * 4)] > 0.0f)
//				{
//						if (pPos->x > pPosOld->x && pPosOld->x < g_Player[nCntModelEnemy].Pos.x + g_Player[nCntModelEnemy].MinModel.x)
//						{// ����	
//						 //pPos->x = g_Player[nCntEnemy].Pos.x + g_Player[nCntEnemy].MinModel.x - fWidthMax;
//						 //pPlayer->aModel[0].bUse = false;
//						 
//						}
//						else if (pPos->x < pPosOld->x && pPosOld->x > g_Player[nCntModelEnemy].Pos.x + g_Player[nCntModelEnemy].MaxModel.x)
//						{// �E��	
//						 //pPos->x = g_Player[nCntEnemy].Pos.x + g_Player[nCntEnemy].MaxModel.x - fWidthMin;
//						 //pPlayer->aModel[0].bUse = false;
//
//						}
//						else if (pPos->z <= pPosOld->z && pPos->z > g_Player[nCntModelEnemy].Pos.z)
//						{// ����
//						 //pPos->z = g_Player[nCntEnemy].Pos.z + g_Player[nCntEnemy].MaxModel.z - fDepthMin;
//							//g_Player[nCntModelEnemy].aModel[0].bUse = false;
//
//						}
//						else if (pPos->z >= pPosOld->z && pPos->z < g_Player[nCntModelEnemy].Pos.z)
//						{// ��O
//						 //pPos->z = g_Player[nCntModelEnemy].Pos.z + g_Player[nCntModelEnemy].MinModel.z - fDepthMax;
//							g_Player[nCntModelEnemy].aModel[0].bUse = false;
//						}
//					}
//				}
//
//			if (nCntModel == 3 + (4 * nCntModelEnemy))
//			{
//				nCntModelEnemy += 1;
//				g_nCntModelEnemy += 4;
//			}
//		}
//	}
//	return bLand;
//}
