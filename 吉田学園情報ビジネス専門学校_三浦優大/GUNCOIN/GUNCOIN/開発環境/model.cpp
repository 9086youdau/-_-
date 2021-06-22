//================================================
//
//���f������[model.h]
// Author; miura yuudai
//
//================================================

#define _CRT_SECURE_NO_WARNINGS
#include "model.h"
#include "input.h"
#include "camera.h"
#include "bullet.h"
#include "math.h"
#include "object.h"
#include <stdio.h>
#include "Billboard.h"
#include "gamepad.h"
#include "wall.h"
#include "item.h"
#include "light.h"

//==============================================================================
// �}�N����`
//==============================================================================
//#define MODEL_MOVE	(1.0f)
//#define MODEL_TURN	(0.1f)
#define PLAYER_MOVE		(4.65f)
#define PLAYER_TURN		(0.1f)
#define VTX_MINP		(D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f))		// �����_�ŏ��l
#define	VTX_MAXP		(D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f))	// �����_�ő�l
#define TEXT_LENGTH		(128)	// �e�L�X�g�ǂݍ��݂̍ő吔
#define DATA_LENGTH		(64)	// �f�[�^�ǂݍ��݂̍ő吔
#define MOVE_MIN		(0.5f)	// �ړ����[�V�������̍ŏ��ړ���
#define MOVECNT_MAX		(20)	// �ړ����[�V�����ȍ~�J�E���g�ő�l
#define SPHERE_SLICE	(10)	// ���̃X���C�X��
#define SPHERE_STACK	(7)		// ���̃X�^�b�N��

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
Player g_player;							// �v���C���[�̍\����

//==============================================================================
// ����������
//==============================================================================
HRESULT InitModel(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();// �f�o�C�X�̎擾

	LoadMotion();

	// X�t�@�C���̓ǂݍ���
	for (int nCnt = 0; nCnt < (g_player.nNumModel); nCnt++)
	{
		D3DXLoadMeshFromX(
			g_player.aModel[nCnt].aFileName,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_player.aModel[nCnt].pBuffMatModel,
			NULL,
			&g_player.aModel[nCnt].nNumMatModel,
			&g_player.aModel[nCnt].pMeshModel);

		g_player.aModel[nCnt].bUse = false;
	}

	g_player.nNumModel = MODEL_PARTS;

	D3DXMATERIAL *pMat;		// �}�e���A���ւ̃|�C���^

	// �}�e���A�����ɑ΂���|�C���^���擾
	pMat = (D3DXMATERIAL*)g_player.aModel[0].pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_player.nNumModel; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			// �t�@�C�������g�p���ăe�N�X�`����ǂݍ���
			D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/body_d.tga",&g_player.aModel[0].pTextureModel);
		}
	}

	// �ϐ��̏�����
	g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.motionType = MOTIONTYPE_MODELNEUTRAL;
	g_player.bLoopMotion = false;
	g_player.nNumKey = 0;
	g_player.nKey = 0;
	g_player.nCounterMotion = 0;
	g_player.g_vtxMinPlayer = VTX_MINP;
	g_player.g_vtxMaxPlayer = VTX_MAXP;
	g_player.as.vtxMinSphere = VTX_MINP;
	g_player.as.vtxMaxSphere = VTX_MAXP;
	g_player.bMotionChange = false;
	g_player.nBrendFrame = 5;
	g_player.weapon = WEAPON_NONE;

	// ���[�J���ϐ��錾
	int nNumVtx;			// ���_��
	DWORD sizeFVF;			// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;			// ���_�o�b�t�@�ւ̃|�C���^

	// ���_�����擾
	nNumVtx = g_player.aModel[0].pMeshModel->GetNumVertices();

	// ���_�t�H�[�}�b�g�̃T�C�Y�̎擾
	sizeFVF = D3DXGetFVFVertexSize(g_player.aModel[0].pMeshModel->GetFVF());

	// ���_�o�b�t�@�����b�N
	g_player.aModel[0].pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	// ���_���W�̔�r�ƍX�V
	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	// ���_���W�̑��

		// �e���W�̍ő�l�̔�r
		if (g_player.g_vtxMaxPlayer.x < vtx.x)
		{
			g_player.g_vtxMaxPlayer.x = vtx.x;
		}
		if (g_player.g_vtxMaxPlayer.y < vtx.y)
		{
			g_player.g_vtxMaxPlayer.y = vtx.y;
		}
		if (g_player.g_vtxMaxPlayer.z < vtx.z)
		{
			g_player.g_vtxMaxPlayer.z = vtx.z;
		}

		// �e���W�̍ŏ��l�̔�r
		if (g_player.g_vtxMinPlayer.x > vtx.x)
		{
			g_player.g_vtxMinPlayer.x = vtx.x;
		}
		if (g_player.g_vtxMinPlayer.y > vtx.y)
		{
			g_player.g_vtxMinPlayer.y = vtx.y;
		}
		if (g_player.g_vtxMinPlayer.z > vtx.z)
		{
			g_player.g_vtxMinPlayer.z = vtx.z;
		}

		pVtxBuff += sizeFVF;	// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
	}

	// ���_�o�b�t�@���A�����b�N
	g_player.aModel[0].pMeshModel->UnlockVertexBuffer();

	return S_OK;
}

//==============================================================================
// �I������
//==============================================================================
void UninitModel(void)
{
	for (int nCnt = 0; nCnt < g_player.nNumModel; nCnt++)
	{
		if (g_player.aModel[nCnt].pMeshModel != NULL)
		{// ���b�V���̔j��
			g_player.aModel[nCnt].pMeshModel->Release();
			g_player.aModel[nCnt].pMeshModel = NULL;
		}

		else if (g_player.aModel[nCnt].pBuffMatModel != NULL)
		{// �o�b�t�@�̔j��
			g_player.aModel[nCnt].pBuffMatModel->Release();
			g_player.aModel[nCnt].pBuffMatModel = NULL;
		}
	}

	if (g_player.as.pMeshSphere != NULL)
	{
		g_player.as.pMeshSphere->Release();
		g_player.as.pMeshSphere = NULL;
	}

	else if (g_player.as.pBuffMatSphere != NULL)
	{
		g_player.as.pBuffMatSphere->Release();
		g_player.as.pBuffMatSphere = NULL;
	}
}

//==============================================================================
// �X�V����
//==============================================================================
void UpdateModel(void)
{
	// �J�����̎擾
	Camera camera = GetCamera();

	g_player.posOld = g_player.pos;
	g_player.as.posold = g_player.as.pos;

	// ���[�V�����̍X�V
	UpdateMotion(g_player.motionType);

	// �ړ��ʂ̉��Z
	g_player.pos += g_player.move;
	
	

	// ���f���̈ړ�
	if (IsButtonPush(KEYINFO_UP) == true)
	{
		if (g_player.nMoveCnt < 20)
		{
			g_player.nMoveCnt++;
		}

		if (g_player.motionType != MOTIONTYPE_JUMP)
		{
			g_player.motionType = MOTIONTYPE_MODELMOVE;
		}

		if (IsButtonPush(KEYINFO_LEFT) == true)
		{// �������
			g_player.move.x -= cosf(camera.rot.y + D3DX_PI / 4) * PLAYER_MOVE;
			g_player.move.z += sinf(camera.rot.y + D3DX_PI / 4) * PLAYER_MOVE;
			g_player.rotDest.y = camera.rot.y + (D3DX_PI * 3 / 4);
		}
		else if (IsButtonPush(KEYINFO_RIGHT) == true)
		{// �E�����
			g_player.move.x += cosf(camera.rot.y - D3DX_PI / 4) * PLAYER_MOVE;
			g_player.move.z -= sinf(camera.rot.y - D3DX_PI / 4) * PLAYER_MOVE;
			g_player.rotDest.y = camera.rot.y - (D3DX_PI * 3 / 4);
		}
		else
		{// �����
			g_player.move.x += sinf(camera.rot.y) * PLAYER_MOVE;
			g_player.move.z += cosf(camera.rot.y) * PLAYER_MOVE;
			g_player.rotDest.y = camera.rot.y + D3DX_PI;
		}
	}
	else if (IsButtonPush(KEYINFO_DOWN) == true)
	{
		if (g_player.nMoveCnt < MOVECNT_MAX)
		{
			g_player.nMoveCnt++;
		}
		if (g_player.motionType != MOTIONTYPE_JUMP)
		{
			g_player.motionType = MOTIONTYPE_MODELMOVE;
		}
		if (IsButtonPush(KEYINFO_LEFT) == true)
		{// ��������
			g_player.move.x += cosf(camera.rot.y + D3DX_PI * 3 / 4) * PLAYER_MOVE;
			g_player.move.z -= sinf(camera.rot.y + D3DX_PI * 3 / 4) * PLAYER_MOVE;
			g_player.rotDest.y = camera.rot.y + D3DX_PI / 4;
		}
		else if (IsButtonPush(KEYINFO_RIGHT) == true)
		{// �E������
			g_player.move.x -= cosf(camera.rot.y - D3DX_PI * 3 / 4) * PLAYER_MOVE;
			g_player.move.z += sinf(camera.rot.y - D3DX_PI * 3 / 4) * PLAYER_MOVE;
			g_player.rotDest.y = camera.rot.y + D3DX_PI / -4;
		}
		else
		{// ������
			g_player.move.x += sinf(camera.rot.y - D3DX_PI) * PLAYER_MOVE;
			g_player.move.z += cosf(camera.rot.y - D3DX_PI) * PLAYER_MOVE;
			g_player.rotDest.y = camera.rot.y;
		}
	}
	else if (IsButtonPush(KEYINFO_LEFT) == true)
	{// ������
		if (g_player.nMoveCnt < MOVECNT_MAX)
		{
			g_player.nMoveCnt++;
		}
		g_player.move.x -= cosf(camera.rot.y) * PLAYER_MOVE;
		g_player.move.z += sinf(camera.rot.y) * PLAYER_MOVE;
		g_player.rotDest.y = camera.rot.y + (D3DX_PI / 2);
		if (g_player.motionType != MOTIONTYPE_JUMP)
		{
			g_player.motionType = MOTIONTYPE_MODELMOVE;
		}
	}
	else if (IsButtonPush(KEYINFO_RIGHT) == true)
	{// �E����
		if (g_player.nMoveCnt < MOVECNT_MAX)
		{
			g_player.nMoveCnt++;
		}

		g_player.move.x += cosf(camera.rot.y) * PLAYER_MOVE;
		g_player.move.z -= sinf(camera.rot.y) * PLAYER_MOVE;
		g_player.rotDest.y = camera.rot.y + (D3DX_PI / -2);
		if (g_player.motionType != MOTIONTYPE_JUMP)
		{
			g_player.motionType = MOTIONTYPE_MODELMOVE;
		}
	}
	else
	{
		if (g_player.nMoveCnt > 0)
		{
			g_player.nMoveCnt--;
		}
	}

	// �ړ����[�V��������ҋ@���[�V������
	if (g_player.motionType == MOTIONTYPE_MODELMOVE && g_player.nMoveCnt == 0)
	{
		g_player.nCounterMotion = 0;
		g_player.nKey = 0;
		g_player.motionType = MOTIONTYPE_MODELNEUTRAL;
	}

	if (g_player.weapon == WEAPON_NONE)
	{
		if (IsButtonDown(KEYINFO_ATTACK) == true)
		{
			if (g_player.motionType == MOTIONTYPE_MODELNEUTRAL)
			{
				g_player.nKey = 0;
				g_player.nCounterMotion = 0;
				g_player.motionType = MOTIONTYPE_MODELACTION;
			}
		}
	}

	// ���f���̏㏸�E���~
	if (GetKeyboardPress(DIK_T) == true)
	{
		g_player.move.y = 2;
	}
	else if (GetKeyboardPress(DIK_X) == true)
	{
		g_player.move.y = -2;
	}
	else
	{
		g_player.move.y = 0;
	}

	// ���f���̐���
	if (GetKeyboardPress(DIK_K) == true)
	{
		g_player.rotDest.y += D3DX_PI / 36;
	}
	if (GetKeyboardPress(DIK_L) == true)
	{
		g_player.rotDest.y -= D3DX_PI / 36;
	}

	// �ړI�̉�]�p�̏��
	if (g_player.rotDest.y - g_player.rot.y < -D3DX_PI)
	{
		g_player.rotDest.y += D3DX_PI * 2.0f;
	}
	else if (g_player.rotDest.y - g_player.rot.y > D3DX_PI)
	{
		g_player.rotDest.y -= D3DX_PI * 2.0f;
	}

	// �����̍X�V
	g_player.rot.y += (g_player.rotDest.y - g_player.rot.y) * 0.1f;

	// ���݂̉�]�p�̏��
	if (g_player.rot.y < -D3DX_PI)
	{
		g_player.rot.y += D3DX_PI * 2.0f;
	}
	else if (g_player.rot.y > D3DX_PI)
	{
		g_player.rot.y -= D3DX_PI * 2.0f;
	}

	// ������̌�������
	g_player.move.x += (0.0f - g_player.move.x) * 0.5f;
	g_player.move.z += (0.0f - g_player.move.z) * 0.5f;


	CollisionVecObject(&g_player.pos, &g_player.posOld, &g_player.move, g_player.g_vtxMaxPlayer.x, g_player.g_vtxMinPlayer.x, g_player.g_vtxMaxPlayer.z, g_player.g_vtxMinPlayer.z, g_player.g_vtxMaxPlayer.y, g_player.g_vtxMinPlayer.y);
	CollisionVecItem(&g_player.pos, &g_player.posOld, &g_player.move ,g_player.g_vtxMaxPlayer.x, g_player.g_vtxMinPlayer.x, g_player.g_vtxMaxPlayer.z, g_player.g_vtxMinPlayer.z, g_player.g_vtxMaxPlayer.y, g_player.g_vtxMinPlayer.y);
	CollisionVecWall(&g_player.pos, &g_player.posOld, &g_player.move, g_player.g_vtxMaxPlayer.x, g_player.g_vtxMinPlayer.x, g_player.g_vtxMaxPlayer.z, g_player.g_vtxMinPlayer.z, g_player.g_vtxMaxPlayer.y, g_player.g_vtxMinPlayer.y);
}

//==============================================================================
// �`�揈��
//==============================================================================
void DrawModel(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p
	D3DMATERIAL9 shadowDef;						// ���݂̃V���h�E�}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							// �}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATRIX ShadowMatrix;//�V���h�E�}�g���b�N�X
	D3DXVECTOR4 veclight;//���C�g�̃x�N�g��
	D3DXVECTOR3 pos, normal;//���ʏ�̍��W�A�x�N�g��
	D3DXPLANE plane;//����

	D3DLIGHT9 *plight = GetLight();

	veclight = D3DXVECTOR4(0.2f, 0.8f, 0.4f, 0.0f);

	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&ShadowMatrix);

	// �v���C���[�̃��[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_player.mtxWorld);

	D3DXPlaneFromPointNormal(&plane, &pos, &normal);

	// �v���C���[�̌����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);
	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxRot);

	// �v���C���[�̈ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);
	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxTrans);

	// �v���C���[�̃��[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_player.mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// ���݂̃V���h�E�}�e���A�����擾
	pDevice->GetMaterial(&shadowDef);

	for (int nCntModel = 0; nCntModel < g_player.nNumModel; nCntModel++)
	{
		D3DXMATRIX mtxRotModel, mtxTransModel;	// �v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxParent;					// �e�̃}�g���b�N�X

		// �e�p�[�c�̃��[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_player.aModel[nCntModel].mtxWorld);

		// �e�p�[�c�̌����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_player.aModel[nCntModel].rot.y, g_player.aModel[nCntModel].rot.x, g_player.aModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxRotModel);

		// �e�p�[�c�̈ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTransModel, g_player.aModel[nCntModel].pos.x, g_player.aModel[nCntModel].pos.y, g_player.aModel[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxTransModel);

		// �e�p�[�c�̐e�}�g���b�N�X��ݒ�
		if (g_player.aModel[nCntModel].nIdxModelParent != -1)
		{
			mtxParent = g_player.aModel[g_player.aModel[nCntModel].nIdxModelParent].mtxWorld;
		}
		else
		{
			mtxParent = g_player.mtxWorld;	// �v���C���[�̃}�g���b�N�X��ݒ�
		}

		// �Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxParent);

		// �e�p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_player.aModel[nCntModel].mtxWorld);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_player.aModel[0].pBuffMatModel->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_player.aModel[nCntModel].nNumMatModel; nCntMat++)
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_player.aModel[0].pTextureModel);

			// ���f��(�p�[�c)�̕`��
			g_player.aModel[nCntModel].pMeshModel->DrawSubset(nCntMat);
		}

		// �ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);

		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		for (int nCntMat = 0; nCntMat < (int)g_player.aModel[nCntModel].nNumMatModel; nCntMat++)
		{
			shadowDef.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&shadowDef);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);

			//�V���h�E�}�g���b�N�X�̐���
			D3DXMatrixShadow(&ShadowMatrix, &veclight, &plane);

			D3DXMatrixMultiply(&ShadowMatrix, &g_player.aModel[nCntModel].mtxWorld, &ShadowMatrix);

			//�e���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &ShadowMatrix);

			//���f���p�[�c�̕`��
			g_player.aModel[nCntModel].pMeshModel->DrawSubset(nCntMat);
		}
	}

	// �ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&shadowDef);

	AttackParts();
}

//==============================================================================
// �v���C���[�̍U���ʒu���f
//==============================================================================
void AttackParts(void)
{
	//// ���[�J���ϐ��錾
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	//D3DXMATRIX mtxRotAttack, mtxTransAttack;	// �v�Z�p�}�g���b�N�X
	//D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p
	//D3DXMATRIX mtxParent;						// �e�̃}�g���b�N�X
	//D3DXMATERIAL *pMat;

	//// ���݂̃}�e���A�����擾
	//pDevice->GetMaterial(&matDef);

	//// �U������}�g���b�N�X�̏�����
	//D3DXMatrixIdentity(&g_player.as.mtxWorld);

	//// �U������̌����𔽉f
	//D3DXMatrixRotationYawPitchRoll(
	//	&mtxRotAttack,
	//	g_player.as.rot.y,
	//	g_player.as.rot.x,
	//	g_player.as.rot.z);
	//D3DXMatrixMultiply(
	//	&g_player.as.mtxWorld,
	//	&g_player.as.mtxWorld,
	//	&mtxRotAttack);

	//// �e�p�[�c�̈ʒu�𔽉f
	//D3DXMatrixTranslation(
	//	&mtxTransAttack,
	//	g_player.as.pos.x,
	//	g_player.as.pos.y,
	//	g_player.as.pos.z);
	//D3DXMatrixMultiply(
	//	&g_player.as.mtxWorld,
	//	&g_player.as.mtxWorld,
	//	&mtxTransAttack);

	////mtxParent = g_player.aModel[g_player.as.nParts].mtxWorld;

	//// �Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɣ��蔭���p�[�c�̃}�g���b�N�X���|�����킹��
	///*D3DXMatrixMultiply(
	//	&g_player.as.mtxWorld,
	//	&g_player.as.mtxWorld,
	//	&mtxParent);*/

	//// ����̃��[���h�}�g���b�N�X�̐ݒ�
	//pDevice->SetTransform(D3DTS_WORLD, &g_player.as.mtxWorld);

	//// �}�e���A���f�[�^�ւ̃|�C���^���擾
	//pMat = (D3DXMATERIAL*)g_player.as.pBuffMatSphere->GetBufferPointer();

	//pMat[0].MatD3D.Diffuse = g_player.as.col;

	//for (int nCntModel = 0; nCntModel < 1; nCntModel++)
	//{
	//	//�}�e���A���̐ݒ�
	//	pDevice->SetMaterial(&pMat[nCntModel].MatD3D);

	//	if (g_player.as.bUse == true)
	//	{
	//		// ���f��(�p�[�c)�̕`��
	//		//g_player.as.pMeshSphere->DrawSubset(nCntModel);
	//	}
	//}
	//// �ۑ����Ă����}�e���A����߂�
	//pDevice->SetMaterial(&matDef);
}


//==============================================================================
// ���f���̎擾
//==============================================================================
Player *GetModel(void)
{
	return &g_player;
}

//==============================================================================
// ���[�V�����̍X�V
//==============================================================================
void UpdateMotion(MOTIONMODELTYPE motionType)
{
	// �L�[���ƃ��[�v���̑��
	g_player.nNumKey = g_player.aMotionInfo[motionType].nNumKey;
	g_player.bLoopMotion = g_player.aMotionInfo[motionType].bLoop;

	// ���[�V�����J�E���^�[�̉��Z
	if (g_player.bMotionChange == true)
	{// ���[�V�����u�����h���s��
		if (g_player.nCounterMotion < g_player.nBrendFrame)
		{// �J�E���g���
			g_player.nCounterMotion++;
		}
	}
	else
	{// �ʏ펞
		if (g_player.nCounterMotion < g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].nFrame)
		{// �J�E���g���
			g_player.nCounterMotion++;
		}
	}

	if (g_player.as.nCntFrameTotal < g_player.nFrameTotal[motionType])
	{
		g_player.as.nCntFrameTotal++;
	}

	// ���f���p�[�c���Ƃ̃��[�V�����A�j���[�V����
	for (int nCnt = 0; nCnt < MODEL_PARTS; nCnt++)
	{
		if (g_player.nKey == g_player.nNumKey - 1 && g_player.bLoopMotion == true)
		{// ���[�v���čŏ��ɖ߂�Ƃ�
			g_player.aModel[nCnt].pos.x = g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fPosX + (g_player.aMotionInfo[motionType].aKeySet[0].aKey[nCnt].fPosX - g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fPosX) * ((float)g_player.nCounterMotion / (float)g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].nFrame);
			g_player.aModel[nCnt].pos.y = g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fPosY + (g_player.aMotionInfo[motionType].aKeySet[0].aKey[nCnt].fPosY - g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fPosY) * ((float)g_player.nCounterMotion / (float)g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].nFrame);
			g_player.aModel[nCnt].pos.z = g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fPosZ + (g_player.aMotionInfo[motionType].aKeySet[0].aKey[nCnt].fPosZ - g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fPosZ) * ((float)g_player.nCounterMotion / (float)g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].nFrame);
			g_player.aModel[nCnt].rot.x = g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fRotX + (g_player.aMotionInfo[motionType].aKeySet[0].aKey[nCnt].fRotX - g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fRotX) * ((float)g_player.nCounterMotion / (float)g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].nFrame);
			g_player.aModel[nCnt].rot.y = g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fRotY + (g_player.aMotionInfo[motionType].aKeySet[0].aKey[nCnt].fRotY - g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fRotY) * ((float)g_player.nCounterMotion / (float)g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].nFrame);
			g_player.aModel[nCnt].rot.z = g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fRotZ + (g_player.aMotionInfo[motionType].aKeySet[0].aKey[nCnt].fRotZ - g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fRotZ) * ((float)g_player.nCounterMotion / (float)g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].nFrame);
			g_player.aModel[nCnt].posMemo = g_player.aModel[nCnt].pos;
			g_player.aModel[nCnt].rotMemo = g_player.aModel[nCnt].rot;
		}
		else if (g_player.bMotionChange == true)
		{// ���[�V�����u�����h
			g_player.aModel[nCnt].pos.x = g_player.aModel[nCnt].posMemo.x + (g_player.aMotionInfo[g_player.motionType].aKeySet[0].aKey[nCnt].fPosX - g_player.aModel[nCnt].posMemo.x) * ((float)g_player.nCounterMotion / (float)g_player.nBrendFrame);
			g_player.aModel[nCnt].pos.y = g_player.aModel[nCnt].posMemo.y + (g_player.aMotionInfo[g_player.motionType].aKeySet[0].aKey[nCnt].fPosY - g_player.aModel[nCnt].posMemo.y) * ((float)g_player.nCounterMotion / (float)g_player.nBrendFrame);
			g_player.aModel[nCnt].pos.z = g_player.aModel[nCnt].posMemo.z + (g_player.aMotionInfo[g_player.motionType].aKeySet[0].aKey[nCnt].fPosZ - g_player.aModel[nCnt].posMemo.z) * ((float)g_player.nCounterMotion / (float)g_player.nBrendFrame);
			g_player.aModel[nCnt].rot.x = g_player.aModel[nCnt].rotMemo.x + (g_player.aMotionInfo[g_player.motionType].aKeySet[0].aKey[nCnt].fRotX - g_player.aModel[nCnt].rotMemo.x) * ((float)g_player.nCounterMotion / (float)g_player.nBrendFrame);
			g_player.aModel[nCnt].rot.y = g_player.aModel[nCnt].rotMemo.y + (g_player.aMotionInfo[g_player.motionType].aKeySet[0].aKey[nCnt].fRotY - g_player.aModel[nCnt].rotMemo.y) * ((float)g_player.nCounterMotion / (float)g_player.nBrendFrame);
			g_player.aModel[nCnt].rot.z = g_player.aModel[nCnt].rotMemo.z + (g_player.aMotionInfo[g_player.motionType].aKeySet[0].aKey[nCnt].fRotZ - g_player.aModel[nCnt].rotMemo.z) * ((float)g_player.nCounterMotion / (float)g_player.nBrendFrame);
			g_player.aModel[nCnt].posMemo = g_player.aModel[nCnt].pos;
			g_player.aModel[nCnt].rotMemo = g_player.aModel[nCnt].rot;
		}
		else
		{// �ʏ펞
			g_player.aModel[nCnt].pos.x = g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fPosX + (g_player.aMotionInfo[motionType].aKeySet[g_player.nKey + 1].aKey[nCnt].fPosX - g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fPosX) * ((float)g_player.nCounterMotion / (float)g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].nFrame);
			g_player.aModel[nCnt].pos.y = g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fPosY + (g_player.aMotionInfo[motionType].aKeySet[g_player.nKey + 1].aKey[nCnt].fPosY - g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fPosY) * ((float)g_player.nCounterMotion / (float)g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].nFrame);
			g_player.aModel[nCnt].pos.z = g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fPosZ + (g_player.aMotionInfo[motionType].aKeySet[g_player.nKey + 1].aKey[nCnt].fPosZ - g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fPosZ) * ((float)g_player.nCounterMotion / (float)g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].nFrame);
			g_player.aModel[nCnt].rot.x = g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fRotX + (g_player.aMotionInfo[motionType].aKeySet[g_player.nKey + 1].aKey[nCnt].fRotX - g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fRotX) * ((float)g_player.nCounterMotion / (float)g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].nFrame);
			g_player.aModel[nCnt].rot.y = g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fRotY + (g_player.aMotionInfo[motionType].aKeySet[g_player.nKey + 1].aKey[nCnt].fRotY - g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fRotY) * ((float)g_player.nCounterMotion / (float)g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].nFrame);
			g_player.aModel[nCnt].rot.z = g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fRotZ + (g_player.aMotionInfo[motionType].aKeySet[g_player.nKey + 1].aKey[nCnt].fRotZ - g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fRotZ) * ((float)g_player.nCounterMotion / (float)g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].nFrame);
			g_player.aModel[nCnt].posMemo = g_player.aModel[nCnt].pos;
			g_player.aModel[nCnt].rotMemo = g_player.aModel[nCnt].rot;
		}

		if (g_player.bMotionChange == false)
		{// ���[�V�����ω��Ȃ�
			if (g_player.nCounterMotion == g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].nFrame)
			{// �L�[�t���[���I����
				if (g_player.motionType != MOTIONTYPE_JUMP || g_player.nKey != g_player.nNumKey - 2)
				{// �W�����v�ȊO�ŃL�[�I�������Z�b�g
					g_player.nCounterMotion = 0;
				}

				if (g_player.nKey == g_player.nNumKey - 1 && g_player.bLoopMotion == true)
				{// ���[�v����Ƃ�
					g_player.nKey = 0;
					g_player.as.nCntFrameTotal = 0;
				}
				else if (g_player.nKey == g_player.nNumKey - 2 && g_player.bLoopMotion == false)
				{// ���[�v�����I������Ƃ�
					if (g_player.motionTypeOld != MOTIONTYPE_JUMP)
					{// ���O���W�����v�ȊO�̎�
						g_player.motionType = MOTIONTYPE_MODELNEUTRAL;	// �j���[�g�����ֈڍs
						g_player.as.nCntFrameTotal = 0;
					}
				}
				else if (g_player.nKey < g_player.nNumKey)
				{// �L�[�̃J�E���g
					g_player.nKey++;
				}
			}
			else if (g_player.motionTypeOld != g_player.motionType)
			{// ���[�V�����ω���	
				g_player.nKey = 0;
				g_player.nCounterMotion = 0;
				g_player.attack.nCntFrameTotal = 0;

				if (g_player.motionTypeOld == MOTIONTYPE_MODELNEUTRAL && g_player.motionType == MOTIONTYPE_MODELMOVE)
				{// �j���[�g��������ړ���
					g_player.nBrendFrame = MBF_NEU_MOVE;
				}
				else if (g_player.motionTypeOld == MOTIONTYPE_MODELMOVE && g_player.motionType == MOTIONTYPE_MODELNEUTRAL)
				{// �ړ�����j���[�g������
					g_player.nBrendFrame = MBF_MOVE_NEU;
				}
				else if (g_player.motionTypeOld == MOTIONTYPE_MODELNEUTRAL && g_player.motionType == MOTIONTYPE_MODELACTION)
				{// �j���[�g��������A�N�V������
					g_player.nBrendFrame = g_player.aMotionInfo[MOTIONTYPE_MODELACTION].aKeySet[0].nFrame;
				}
				else if (g_player.motionTypeOld == MOTIONTYPE_MODELACTION && g_player.motionType == MOTIONTYPE_MODELNEUTRAL)
				{// �A�N�V��������j���[�g������
					g_player.nBrendFrame = MBF_ACT_NEU;
				}
				break;
			}
		}
		else if (g_player.bMotionChange == true)
		{// ���[�V�����u�����h���̃J�E���g���Z�b�g
			if (g_player.nCounterMotion == g_player.nBrendFrame || g_player.motionTypeOld != g_player.motionType)
			{
				g_player.nKey = 0;
				g_player.nCounterMotion = 0;
				g_player.as.nCntFrameTotal = 0;
				g_player.bMotionChange = false;
			}
		}

		// �Ō��̓����蔻��̗L����
		if (g_player.motionType == MOTIONTYPE_MODELACTION)
		{
			if (g_player.as.nCntFrameTotal >= g_player.as.nStartFrame &&
				g_player.as.nCntFrameTotal <= g_player.as.nEndFrame)
			{// �J�E���g�͈͓��ŗL��
				g_player.as.bUse = true;
				if (g_player.motionType == MOTIONTYPE_MODELACTION)
				{
					if (g_player.as.nCntFrameTotal == g_player.as.nStartFrame)
					{
						//PlaySound(SOUND_LABEL_SE_SMASH);
					}
				}
				else
				{
					if (g_player.as.nCntFrameTotal == g_player.as.nStartFrame)
					{
						//PlaySound(SOUND_LABEL_SE_SLASH);
					}
				}
			}
		}
		else
		{// ����ȊO
			g_player.as.bUse = false;
		}

		// �����蔻��̕\��
		if (g_player.as.bUse == true)
		{
			g_player.as.col.a = 1.0f;
		}
		else
		{
			g_player.as.col.a = 0.0f;
		}
	}

	// ���O�̃��[�V������Ԃ̕ۑ�
	g_player.motionTypeOld = g_player.motionType;
}
//==============================================================================
// .txt�t�H���_�̓ǂݍ���
//==============================================================================
void LoadMotion(void)
{
	// ���[�J���ϐ��錾
	FILE *pFile = NULL;
	char aEqual[2] = { NULL };					// �u=�v�ǂݎ��p�ϐ�
	bool bComment = false;						// �R�����g�A�E�g���邩
	char aText[TEXT_LENGTH] = { NULL };			// �e�L�X�g�ǂݎ��p�ϐ�
	char aCharaSet[DATA_LENGTH] = { NULL };		// �L�����f�[�^�ǂݎ��p�ϐ�
	char aPartsSet[DATA_LENGTH] = { NULL };		// �p�[�c�f�[�^�ǂݎ��p�ϐ�
	char aMotionSet[DATA_LENGTH] = { NULL };	// ���[�V�����ǂݎ��p�ϐ�
	char aKeySet[DATA_LENGTH] = { NULL };		// �L�[�ݒ���ǂݎ��p�ϐ�
	char aKey[DATA_LENGTH] = { NULL };			// �L�[���ǂݎ��p�ϐ�

	//g_player[0].modelType = (ModelType)pSelect->chara;

	// strcmp�ǂݎ��p�|�C���^
	char *pText = &aText[0];
	char *pCharaSet = &aCharaSet[0];
	char *pPartsSet = &aPartsSet[0];
	char *pMotionSet = &aMotionSet[0];
	char *pKeySet = &aKeySet[0];
	char *pKey = &aKey[0];

	// �f�[�^�̓ǂݍ���
	pFile = fopen("data/TEXT/motion_player00.txt", "r");

		if (pFile != NULL)
		{ //�t�@�C���W�J�\
			aText[0] = { NULL };
			aCharaSet[0] = { NULL };
			aPartsSet[0] = { NULL };
			aMotionSet[0] = { NULL };
			aKeySet[0] = { NULL };
			aKey[0] = { NULL };
			int nIdxParts = 0;			// �p�[�c��
			int nMotion = 0;			// ���[�V�����̐�
			int nCntFile = 0;			// X�f�[�^�̐�
			int nAs = 0;
			while (strcmp("END_SCRIPT", pText) != 0)
			{
				aText[0] = { NULL };
				if (bComment == false)
				{// �R�����g�A�E�g���Ă��Ȃ�
					fscanf(pFile, "%s", &aText[0]);

					if (aText[0] == '#')
					{// ������̐擪���u#�v�Ȃ�΃R�����g�A�E�g��
						bComment = true;
					}
					else
					{// �ʏ펞
						if (strcmp("NUM_MODEL", pText) == 0)
						{// ���f���̐�
							fscanf(pFile, "%s", &aEqual[0]);
							fscanf(pFile, "%d", &g_player.nNumModel);
						}
						else if (strcmp("MODEL_FILENAME", pText) == 0)
						{// X�t�@�C�����̓ǂݍ���
							fscanf(pFile, "%s", &aEqual[0]);
							fscanf(pFile, "%s", &g_player.aModel[nCntFile].aFileName[0]);
							nCntFile++;
						}
						else if (strcmp("CHARACTERSET", pText) == 0)
						{// �L�����̏��
							while (strcmp("END_CHARACTERSET", pCharaSet) != 0)
							{// �L�������̓ǂݎ��
								fscanf(pFile, "%s", &aCharaSet[0]);
								if (strcmp("NUM_PARTS", pCharaSet) == 0)
								{

								}
								else if (strcmp("RADIUS", pCharaSet) == 0)
								{// �����蔻��
									fscanf(pFile, "%s", &aEqual[0]);
									fscanf(pFile, "%f", &g_player.fOutRadius);
								}
								else if (strcmp("HEIGHT", pCharaSet) == 0)
								{// �����蔻��
									fscanf(pFile, "%s", &aEqual[0]);
									fscanf(pFile, "%f", &g_player.fHeight);
								}
								else if (strcmp("PARTSSET", pCharaSet) == 0)
								{// �p�[�c���
									aPartsSet[0] = { NULL };

									while (strcmp("END_PARTSSET", pPartsSet) != 0)
									{
										fscanf(pFile, "%s", &aPartsSet[0]);
										if (strcmp("INDEX", pPartsSet) == 0)
										{// �p�[�c���̓ǂݎ��
											fscanf(pFile, "%s", &aEqual[0]);
											fscanf(pFile, "%d", &nIdxParts);
										}
										else if (strcmp("PARENT", pPartsSet) == 0)
										{// �p�[�c�̐e���
											fscanf(pFile, "%s", &aEqual[0]);
											fscanf(pFile, "%d", &g_player.aModel[nIdxParts].nIdxModelParent);
										}
										else if (strcmp("POS", pPartsSet) == 0)
										{// �p�[�c�̈ʒu���
											fscanf(pFile, "%s", &aEqual[0]);
											fscanf(pFile, "%f", &g_player.aModel[nIdxParts].pos.x);
											fscanf(pFile, "%f", &g_player.aModel[nIdxParts].pos.y);
											fscanf(pFile, "%f", &g_player.aModel[nIdxParts].pos.z);
											g_player.aModel[nIdxParts].posReset = g_player.aModel[nIdxParts].pos;
										}
										else if (strcmp("ROT", pPartsSet) == 0)
										{// �p�[�c�̊p�x���
											fscanf(pFile, "%s", &aEqual[0]);
											fscanf(pFile, "%f", &g_player.aModel[nIdxParts].rot.x);
											fscanf(pFile, "%f", &g_player.aModel[nIdxParts].rot.y);
											fscanf(pFile, "%f", &g_player.aModel[nIdxParts].rot.z);
										}
									}
								}
							}
						}
						else if (strcmp("MOTIONSET", pText) == 0)
						{
							// �ϐ��̏�����
							aMotionSet[0] = { NULL };

							// ���[�J���ϐ��錾
							int nLoop = 0;
							int nKeySet = 0;

							while (strcmp("END_MOTIONSET", pMotionSet) != 0)
							{// ���[�V�����̓ǂݍ���
								fscanf(pFile, "%s", &aMotionSet[0]);
								if (strcmp("LOOP", pMotionSet) == 0)
								{// ���[�v���邩
									fscanf(pFile, "%s", &aEqual[0]);
									fscanf(pFile, "%d", &nLoop);
									if (nLoop == 1)
									{// �P�̏ꍇ���[�v����
										g_player.bLoopMotion = true;
										g_player.aMotionInfo[nMotion].bLoop = true;
									}
								}
								else if (strcmp("NUM_KEY", pMotionSet) == 0)
								{// �L�[���̓ǂݍ���
									fscanf(pFile, "%s", &aEqual[0]);
									fscanf(pFile, "%d", &g_player.nNumKey);
								}
								else if (strcmp("COLLISION", pMotionSet) == 0)
								{
									fscanf(pFile, "%s", &aEqual[0]);
									fscanf(pFile, "%d", &g_player.as.nParts);
									fscanf(pFile, "%f", &g_player.as.pos.x);
									fscanf(pFile, "%f", &g_player.as.pos.y);
									fscanf(pFile, "%f", &g_player.as.pos.z);
									fscanf(pFile, "%f", &g_player.as.fRadius);
									fscanf(pFile, "%d", &g_player.as.nStartFrame);
									fscanf(pFile, "%d", &g_player.as.nEndFrame);
									nAs++;
								}
								else if (strcmp("KEYSET", pMotionSet) == 0)
								{// �L�[�̓ǂݍ���
								 // ���[�J���ϐ��錾
									int nKey = 0;
									// �ϐ��̏�����
									aKeySet[0] = { NULL };

									while (strcmp("END_KEYSET", pKeySet) != 0)
									{// �L�[��񍀖ڂ̓ǂݍ���
										fscanf(pFile, "%s", &aKeySet[0]);

										if (aKeySet[0] == '#')
										{// �R�����g�A�E�g
										 // ���[�J���ϐ��錾
											char c = NULL;
											char d = NULL;
											fscanf(pFile, "%c", &c);
											while (c != '\n' && d != '\n')
											{
												fscanf(pFile, "%s", &aKey[0]);
												fscanf(pFile, "%c", &d);
											}
										}

										if (strcmp("KEY", pKeySet) == 0)
										{// �L�[���̓ǂݍ���
											aKey[0] = { NULL };
											while (strcmp("END_KEY", pKey) != 0)
											{// �ʒu�E�p�x�̓ǂݍ���
												fscanf(pFile, "%s", &aKey[0]);
												if (strcmp("POS", pKey) == 0)
												{// �ʒu���̓ǂݍ���
													fscanf(pFile, "%s", &aEqual[0]);
													fscanf(pFile, "%f", &g_player.aMotionInfo[nMotion].aKeySet[nKeySet].aKey[nKey].fPosX);
													fscanf(pFile, "%f", &g_player.aMotionInfo[nMotion].aKeySet[nKeySet].aKey[nKey].fPosY);
													fscanf(pFile, "%f", &g_player.aMotionInfo[nMotion].aKeySet[nKeySet].aKey[nKey].fPosZ);
													g_player.aMotionInfo[nMotion].aKeySet[nKeySet].aKey[nKey].fPosX += g_player.aModel[nKey].pos.x;
													g_player.aMotionInfo[nMotion].aKeySet[nKeySet].aKey[nKey].fPosY += g_player.aModel[nKey].pos.y;
													g_player.aMotionInfo[nMotion].aKeySet[nKeySet].aKey[nKey].fPosZ += g_player.aModel[nKey].pos.z;
												}
												else if (strcmp("ROT", pKey) == 0)
												{// �p�x���̓ǂݍ���
													fscanf(pFile, "%s", &aEqual[0]);
													fscanf(pFile, "%f", &g_player.aMotionInfo[nMotion].aKeySet[nKeySet].aKey[nKey].fRotX);
													fscanf(pFile, "%f", &g_player.aMotionInfo[nMotion].aKeySet[nKeySet].aKey[nKey].fRotY);
													fscanf(pFile, "%f", &g_player.aMotionInfo[nMotion].aKeySet[nKeySet].aKey[nKey].fRotZ);
												}
											}
											nKey++;
										}
										else if (strcmp("FRAME", pKeySet) == 0)
										{// �L�[�t���[�����̓ǂݍ���
											fscanf(pFile, "%s", &aEqual[0]);
											fscanf(pFile, "%d", &g_player.aMotionInfo[nMotion].aKeySet[nKeySet].nFrame);
											g_player.nFrameTotal[nMotion] += g_player.aMotionInfo[nMotion].aKeySet[nKeySet].nFrame;
											if (g_player.aMotionInfo[nMotion].bLoop == false && nKeySet == (g_player.nNumKey - 1))
											{
												g_player.nFrameTotal[nMotion] -= g_player.aMotionInfo[nMotion].aKeySet[nKeySet].nFrame;
											}
										}
									}
									nKeySet++;
								}
							}
							g_player.aMotionInfo[nMotion].nNumKey = nKeySet;	// �L�[���̐ݒ�
							nMotion++;
						}
					}
				}
				else if (bComment == true)
				{// �R�����g�A�E�g����
				 // ���[�J���ϐ��錾
					char a = NULL;
					char b = NULL;
					fscanf(pFile, "%c", &a);
					while (a != '\n' && b != '\n')
					{
						fscanf(pFile, "%s", &aText[0]);
						fscanf(pFile, "%c", &b);
					}
					bComment = false;
				}
			}
			fclose(pFile);
		}
		else
		{ // �t�@�C���W�J�s��
		}
}
