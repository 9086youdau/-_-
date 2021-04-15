//================================================
//
//�΂̏���[stone.h]
// Author; miura yuudai
//
//================================================

#include "stone.h"
#include "input.h"
#include "camera.h"
#include "Billboard.h"
#include "bullet.h"
#include "model.h"

//=====================
//�O���[�o���ϐ�
//=====================
//���b�V���i���_���j�ւ̃|�C���^
LPD3DXMESH g_pMeshStone[4];

//�}�e���A���i�ގ����j�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatStone[4];

DWORD g_nNumMatStone[4];//�}�e���A���̐�
STONE g_PosStone[MAXSTONE];//x�t�@�C��
D3DXMATRIX g_mtxWolrdStone;//���[���h�}�g���b�N�X

//====================
//���f���̏���������
//====================
void InitStone(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//x�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data/MODEL/kusa2.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatStone[0], NULL, &g_nNumMatStone[0], &g_pMeshStone[0]);
	D3DXLoadMeshFromX("data/MODEL/sekizou.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatStone[1], NULL, &g_nNumMatStone[1], &g_pMeshStone[1]);
	D3DXLoadMeshFromX("data/MODEL/kusa.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatStone[2], NULL, &g_nNumMatStone[2], &g_pMeshStone[2]);
	D3DXLoadMeshFromX("data/MODEL/okimono.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatStone[3], NULL, &g_nNumMatStone[3], &g_pMeshStone[3]);


	for (int nCntMat = 0; nCntMat < MAXSTONE; nCntMat++)
	{
		//�ϐ�������
		g_PosStone[nCntMat].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_PosStone[nCntMat].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_PosStone[nCntMat].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_PosStone[nCntMat].rotmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_PosStone[nCntMat].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_PosStone[nCntMat].MaxStone = D3DXVECTOR3(-100000.0f, -100000.0f, -100000.0f);
		g_PosStone[nCntMat].MinStone = D3DXVECTOR3(100000.0f, 100000.0f, 100000.0f);
		g_PosStone[nCntMat].bUse = false;
		g_PosStone[nCntMat].nType = 0;

	}
}
//=======================
//���f���̏I������
//=======================
void UninitStone(void)
{
	for (int nCntMatVer = 0; nCntMatVer < 4; nCntMatVer++)
	{
		//���_�̊J��
		if (g_pMeshStone[nCntMatVer] != NULL)
		{
			g_pMeshStone[nCntMatVer]->Release();
			g_pMeshStone[nCntMatVer] = NULL;
		}

		//�ގ��̊J��
		if (g_pBuffMatStone[nCntMatVer] != NULL)
		{
			g_pBuffMatStone[nCntMatVer]->Release();
			g_pBuffMatStone[nCntMatVer] = NULL;
		}

		//�e�N�X�`���̊J��
		if (g_PosStone[0].g_apTextureStone[0] != NULL)
		{
			g_PosStone[0].g_apTextureStone[0]->Release();
			g_PosStone[0].g_apTextureStone[0] = NULL;
		}
	}
}
//=======================
//���f���̍X�V����
//=======================
void UpdateStone(void)
{

	int nNumVtx;//���_��
	DWORD sizeFVF;//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;//���_�o�b�t�@�ւ̃|�C���^

	for (int nCntMat = 0; nCntMat < MAXSTONE; nCntMat++)
	{
		nNumVtx = g_pMeshStone[g_PosStone[nCntMat].nType]->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_pMeshStone[g_PosStone[nCntMat].nType]->GetFVF());

		//���_�o�b�t�@�̃��b�N
		g_pMeshStone[g_PosStone[nCntMat].nType]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;//���_���W�̑��

			if (vtx.x > g_PosStone[nCntMat].MaxStone.x)
			{
				g_PosStone[nCntMat].MaxStone.x = vtx.x;
			}

			if (vtx.x < g_PosStone[nCntMat].MinStone.x)
			{
				g_PosStone[nCntMat].MinStone.x = vtx.x;
			}

			if (vtx.y > g_PosStone[nCntMat].MaxStone.y)
			{
				g_PosStone[nCntMat].MaxStone.y = vtx.y;
			}

			if (vtx.y < g_PosStone[nCntMat].MinStone.y)
			{
				g_PosStone[nCntMat].MinStone.y = vtx.y;
			}

			if (vtx.z > g_PosStone[nCntMat].MaxStone.z)
			{
				g_PosStone[nCntMat].MaxStone.z = vtx.z;
			}

			if (vtx.z < g_PosStone[nCntMat].MinStone.z)
			{
				g_PosStone[nCntMat].MinStone.z = vtx.z;
			}

			pVtxBuff += sizeFVF;//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		}

		g_pMeshStone[g_PosStone[nCntMat].nType]->UnlockVertexBuffer();
	}
}
//=======================
//���f���̕`�揈��
//=======================
void DrawStone(void)
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

	for (int nCntMat = 0; nCntMat < MAXSTONE; nCntMat++)
	{
		for (int nCntMatVer = 0; nCntMatVer < 4; nCntMatVer++)
		{
			if (g_PosStone[nCntMat].bUse == true)
			{
				//���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_mtxWolrdStone);

				//�����𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_PosStone[nCntMat].rot.y, g_PosStone[nCntMat].rot.x, g_PosStone[nCntMat].rot.z);

				D3DXMatrixMultiply(&g_mtxWolrdStone, &g_mtxWolrdStone, &mtxRot);

				//�ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTrans, g_PosStone[nCntMat].Pos.x, g_PosStone[nCntMat].Pos.y, g_PosStone[nCntMat].Pos.z);

				D3DXMatrixMultiply(&g_mtxWolrdStone, &g_mtxWolrdStone, &mtxTrans);

				//���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_mtxWolrdStone);

				//���݂̃}�e���A�����擾
				pDevice->GetMaterial(&matDef);

				//�}�e���A���f�[�^�ւ̃|�C���^���擾
				pMat = (D3DXMATERIAL*)g_pBuffMatStone[nCntMatVer]->GetBufferPointer();

				for (int nCntMatVer = 0; nCntMatVer < (int)g_nNumMatStone; nCntMatVer++)
				{
					if (g_PosStone[nCntMat].nType == 0)
					{
						//�}�e���A���̐ݒ�
						pDevice->SetMaterial(&pMat[nCntMatVer].MatD3D);

						//�e�N�X�`���̐ݒ�
						pDevice->SetTexture(0, NULL);

						//���f���p�[�c�̕`��
						g_pMeshStone[0]->DrawSubset(nCntMatVer);
						break;
					}

					else if (g_PosStone[nCntMat].nType == 1)
					{
						//�}�e���A���̐ݒ�
						pDevice->SetMaterial(&pMat[nCntMatVer].MatD3D);

						//�e�N�X�`���̐ݒ�
						pDevice->SetTexture(0, NULL);

						//���f���p�[�c�̕`��
						g_pMeshStone[1]->DrawSubset(nCntMatVer);
						break;
					}

					else if (g_PosStone[nCntMat].nType == 2)
					{
						//�}�e���A���̐ݒ�
						pDevice->SetMaterial(&pMat[nCntMatVer].MatD3D);

						//�e�N�X�`���̐ݒ�
						pDevice->SetTexture(0, NULL);

						//���f���p�[�c�̕`��
						g_pMeshStone[2]->DrawSubset(nCntMatVer);
						break;
					}

					else if (g_PosStone[nCntMat].nType == 3)
					{
						//�}�e���A���̐ݒ�
						pDevice->SetMaterial(&pMat[nCntMatVer].MatD3D);

						//�e�N�X�`���̐ݒ�
						pDevice->SetTexture(0, NULL);

						//���f���p�[�c�̕`��
						g_pMeshStone[3]->DrawSubset(nCntMatVer);
						break;
					}
				}

			}
		}
	}
	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}
STONE *GetStone(void)
{
	return &g_PosStone[0];
}
//==============================================================================
// �O�ς𗘗p���������蔻��
//==============================================================================
bool CollisionVec(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidthMax, float fWidthMin, float fDepthMax, float fDepthMin, float fHeightMax, float fHeightMin)
{
	bool bLand = false;

	D3DXVECTOR3 pos = *pPos;// ����Ώۂ̈ʒu

	int g_nCntSt;
	int nCntStone;
	int nCnt = 0;

	g_nCntSt = 0;
	nCntStone = 0;

	for (int nCount = 0; nCount < MAXSTONE; nCount++)
	{
		if (g_PosStone[nCount].bUse == true)
		{
			//aPos�̒l�ݒ�
			g_PosStone[nCount].aPos[0 + (nCount * 4)] = D3DXVECTOR3(g_PosStone[nCount].Pos.x + g_PosStone[nCount].MinStone.x, 0.0f, g_PosStone[nCount].Pos.z + g_PosStone[nCount].MinStone.z);
			g_PosStone[nCount].aPos[1 + (nCount * 4)] = D3DXVECTOR3(g_PosStone[nCount].Pos.x + g_PosStone[nCount].MinStone.x, 0.0f, g_PosStone[nCount].Pos.z + g_PosStone[nCount].MaxStone.z);
			g_PosStone[nCount].aPos[2 + (nCount * 4)] = D3DXVECTOR3(g_PosStone[nCount].Pos.x + g_PosStone[nCount].MaxStone.x, 0.0f, g_PosStone[nCount].Pos.z + g_PosStone[nCount].MaxStone.z);
			g_PosStone[nCount].aPos[3 + (nCount * 4)] = D3DXVECTOR3(g_PosStone[nCount].Pos.x + g_PosStone[nCount].MaxStone.x, 0.0f, g_PosStone[nCount].Pos.z + g_PosStone[nCount].MinStone.z);

			//�O�ς̎�
			g_PosStone[nCount].Vec[0 + (nCount * 4)] = g_PosStone[nCount].aPos[1 + (nCount * 4)] - g_PosStone[nCount].aPos[0 + (nCount * 4)];
			g_PosStone[nCount].Vec[1 + (nCount * 4)] = g_PosStone[nCount].aPos[2 + (nCount * 4)] - g_PosStone[nCount].aPos[1 + (nCount * 4)];
			g_PosStone[nCount].Vec[2 + (nCount * 4)] = g_PosStone[nCount].aPos[3 + (nCount * 4)] - g_PosStone[nCount].aPos[2 + (nCount * 4)];
			g_PosStone[nCount].Vec[3 + (nCount * 4)] = g_PosStone[nCount].aPos[0 + (nCount * 4)] - g_PosStone[nCount].aPos[3 + (nCount * 4)];
		}
	}

	for (int nCount = 0; nCount < MAXSTONEVER; nCount++)
	{
		if (g_PosStone[nCntStone].bUse == true)
		{
			//�O�ς̎�2
			if (nCount == 0 + g_nCntSt)
			{
				g_PosStone[nCntStone].g_Vec[nCount] = pos + D3DXVECTOR3(fWidthMax, 0.0f, 0.0f) - g_PosStone[nCntStone].aPos[nCount];
			}
			else if (nCount == 1 + g_nCntSt)
			{
				g_PosStone[nCntStone].g_Vec[nCount] = pos + D3DXVECTOR3(0.0f, 0.0f, fDepthMin) - g_PosStone[nCntStone].aPos[nCount];
			}
			else if (nCount == 2 + g_nCntSt)
			{
				g_PosStone[nCntStone].g_Vec[nCount] = pos + D3DXVECTOR3(fWidthMin, 0.0f, 0.0f) - g_PosStone[nCntStone].aPos[nCount];
			}
			else if (nCount == 3 + g_nCntSt)
			{
				g_PosStone[nCntStone].g_Vec[nCount] = pos + D3DXVECTOR3(0.0f, 0.0f, fDepthMax) - g_PosStone[nCntStone].aPos[nCount];
			}

			g_PosStone[nCntStone].PlayerVec[nCount] = (g_PosStone[nCntStone].Vec[nCount].z * g_PosStone[nCntStone].g_Vec[nCount].x) - (g_PosStone[nCntStone].Vec[nCount].x * g_PosStone[nCntStone].g_Vec[nCount].z);

			if (pPos->y <= g_PosStone[nCntStone].Pos.y + g_PosStone[nCntStone].MaxStone.y - fHeightMin && pPos->y > g_PosStone[nCntStone].Pos.y + g_PosStone[nCntStone].MinStone.y - fHeightMax)
			{
				if (g_PosStone[nCntStone].PlayerVec[0 + (nCntStone * 4)] > 0.0f && g_PosStone[nCntStone].PlayerVec[1 + (nCntStone * 4)] > 0.0f && g_PosStone[nCntStone].PlayerVec[2 + (nCntStone * 4)] > 0.0f && g_PosStone[nCntStone].PlayerVec[3 + (nCntStone * 4)] > 0.0f)
				{
					if (pPos->x >= pPosOld->x && pPosOld->x < g_PosStone[nCntStone].Pos.x + g_PosStone[nCntStone].MinStone.x)
					{// ����	
						pPos->x = g_PosStone[nCntStone].Pos.x + g_PosStone[nCntStone].MinStone.x - fWidthMax;
						//pMove->x = 0.0f;
					}
					else if (pPos->x <= pPosOld->x && pPosOld->x > g_PosStone[nCntStone].Pos.x + g_PosStone[nCntStone].MaxStone.x)
					{// �E��	
						pPos->x = g_PosStone[nCntStone].Pos.x + g_PosStone[nCntStone].MaxStone.x - fWidthMin;
						//pMove->x = 0.0f;
					}
					else if (pPos->z <= pPosOld->z &&  pPos->z > g_PosStone[nCntStone].Pos.z)
					{// ����
						pPos->z = g_PosStone[nCntStone].Pos.z + g_PosStone[nCntStone].MaxStone.z - fDepthMin;
					}
					else if (pPos->z >= pPosOld->z && pPos->z < g_PosStone[nCntStone].Pos.z)
					{// ��O
						pPos->z = g_PosStone[nCntStone].Pos.z + g_PosStone[nCntStone].MinStone.z - fDepthMax;
					}
				}
			}

			if (nCount == 3 + (4 * nCntStone))
			{
				g_nCntSt += 4;
				nCntStone += 1;
			}
		}
	}

		return bLand;
}
void SetStone(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType)
{
	BYTE *pVtxBuff;//���_�o�b�t�@�ւ̃|�C���^

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCntMat = 0; nCntMat < MAXSTONE; nCntMat++)
	{
		//���_�o�b�t�@�̃��b�N
		g_pMeshStone[g_PosStone[nCntMat].nType]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		if (g_PosStone[nCntMat].bUse == false)//�e���g�p���Ă��邩�ǂ���
		{
			if (nType == 0)
			{
				//�ʒu�ݒ�
				g_PosStone[nCntMat].Pos = pos;

				//�ʒu��]
				g_PosStone[nCntMat].rot = rot;

				//�^�C�v����
				g_PosStone[nCntMat].nType = nType;

				//�e�̎g�p
				g_PosStone[nCntMat].bUse = true;
				break;
			}

			else if (nType == 1)
			{
				//�ʒu�ݒ�
				g_PosStone[nCntMat].Pos = pos;

				//�ʒu��]
				g_PosStone[nCntMat].rot = rot;

				//�^�C�v����
				g_PosStone[nCntMat].nType = nType;

				//�e�̎g�p
				g_PosStone[nCntMat].bUse = true;
				break;
			}

			else if (nType == 2)
			{
				//�ʒu�ݒ�
				g_PosStone[nCntMat].Pos = pos;

				//�ʒu��]
				g_PosStone[nCntMat].rot = rot;

				//�^�C�v����
				g_PosStone[nCntMat].nType = nType;

				//�e�̎g�p
				g_PosStone[nCntMat].bUse = true;
				break;
			}

			else if (nType == 3)
			{
				//�ʒu�ݒ�
				g_PosStone[nCntMat].Pos = pos;

				//�ʒu��]
				g_PosStone[nCntMat].rot = rot;

				//�^�C�v����
				g_PosStone[nCntMat].nType = nType;

				//�e�̎g�p
				g_PosStone[nCntMat].bUse = true;
				break;
			}
		}

		//���_�o�b�t�@�̃A�����b�N
		g_pMeshStone[g_PosStone[nCntMat].nType]->UnlockVertexBuffer();
	}
}

