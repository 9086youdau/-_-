//================================================
//
//�I�u�W�F�N�g�̏���[object.h]
// Author; miura yuudai
//
//================================================

//================================================
//�C���N���[�h�ǂݍ���
//================================================
#include "object.h"
#include "input.h"
#include "camera.h"
#include "Billboard.h"
#include "bullet.h"
#include "model.h"

//=====================
//�O���[�o���ϐ�
//=====================
//���b�V���i���_���j�ւ̃|�C���^
LPD3DXMESH g_pMeshObject[MAX_OBJECT_TYPE];
//�}�e���A���i�ގ����j�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatObject[MAX_OBJECT_TYPE];
DWORD g_nNumMatObject[MAX_OBJECT_TYPE];//�}�e���A���̐�
OBJECT g_PosObject[MAXOBJECT];//x�t�@�C��
D3DXMATRIX g_mtxWolrdObject;//���[���h�}�g���b�N�X

//======================================
//�I�u�W�F�N�g�̏���������
//======================================
void InitObject(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//x�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data/MODEL/kusa2.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatObject[0], NULL, &g_nNumMatObject[0], &g_pMeshObject[0]);
	D3DXLoadMeshFromX("data/MODEL/okimono.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatObject[1], NULL, &g_nNumMatObject[1], &g_pMeshObject[1]);

	for (int nCntMat = 0; nCntMat < MAXOBJECT; nCntMat++)
	{
		//�ϐ�������
		g_PosObject[nCntMat].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_PosObject[nCntMat].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_PosObject[nCntMat].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_PosObject[nCntMat].rotmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_PosObject[nCntMat].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_PosObject[nCntMat].MaxObject = D3DXVECTOR3(-100000.0f, -100000.0f, -100000.0f);
		g_PosObject[nCntMat].MinObject = D3DXVECTOR3(100000.0f, 100000.0f, 100000.0f);
		g_PosObject[nCntMat].bUse = false;
		g_PosObject[nCntMat].nType = 0;
	}
}
//======================================
//�I�u�W�F�N�g�̏I������
//======================================
void UninitObject(void)
{
	for (int nCntMatVer = 0; nCntMatVer < MAX_OBJECT_TYPE; nCntMatVer++)
	{
		//���_�̊J��
		if (g_pMeshObject[nCntMatVer] != NULL)
		{
			g_pMeshObject[nCntMatVer]->Release();
			g_pMeshObject[nCntMatVer] = NULL;
		}

		//�ގ��̊J��
		if (g_pBuffMatObject[nCntMatVer] != NULL)
		{
			g_pBuffMatObject[nCntMatVer]->Release();
			g_pBuffMatObject[nCntMatVer] = NULL;
		}
	}
}
//======================================
//�I�u�W�F�N�g�̍X�V����
//======================================
void UpdateObject(void)
{
	int nNumVtx;//���_��
	DWORD sizeFVF;//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;//���_�o�b�t�@�ւ̃|�C���^

	for (int nCntMat = 0; nCntMat < MAXOBJECT; nCntMat++)
	{
		nNumVtx = g_pMeshObject[g_PosObject[nCntMat].nType]->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_pMeshObject[g_PosObject[nCntMat].nType]->GetFVF());

		//���_�o�b�t�@�̃��b�N
		g_pMeshObject[g_PosObject[nCntMat].nType]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;//���_���W�̑��

			if (vtx.x > g_PosObject[nCntMat].MaxObject.x)
			{
				g_PosObject[nCntMat].MaxObject.x = vtx.x;
			}

			if (vtx.x < g_PosObject[nCntMat].MinObject.x)
			{
				g_PosObject[nCntMat].MinObject.x = vtx.x;
			}

			if (vtx.y > g_PosObject[nCntMat].MaxObject.y)
			{
				g_PosObject[nCntMat].MaxObject.y = vtx.y;
			}

			if (vtx.y < g_PosObject[nCntMat].MinObject.y)
			{
				g_PosObject[nCntMat].MinObject.y = vtx.y;
			}

			if (vtx.z > g_PosObject[nCntMat].MaxObject.z)
			{
				g_PosObject[nCntMat].MaxObject.z = vtx.z;
			}

			if (vtx.z < g_PosObject[nCntMat].MinObject.z)
			{
				g_PosObject[nCntMat].MinObject.z = vtx.z;
			}

			pVtxBuff += sizeFVF;//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		}

		g_pMeshObject[g_PosObject[nCntMat].nType]->UnlockVertexBuffer();
	}
}
//======================================
//�I�u�W�F�N�g�̕`�揈��
//======================================
void DrawObject(void)
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

	for (int nCntMat = 0; nCntMat < MAXOBJECT; nCntMat++)
	{
		for (int nCntMatVer = 0; nCntMatVer < MAX_OBJECT_TYPE; nCntMatVer++)
		{
			if (g_PosObject[nCntMat].bUse == true)
			{
				//���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_mtxWolrdObject);

				//�����𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_PosObject[nCntMat].rot.y, g_PosObject[nCntMat].rot.x, g_PosObject[nCntMat].rot.z);

				D3DXMatrixMultiply(&g_mtxWolrdObject, &g_mtxWolrdObject, &mtxRot);

				//�ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTrans, g_PosObject[nCntMat].Pos.x, g_PosObject[nCntMat].Pos.y, g_PosObject[nCntMat].Pos.z);

				D3DXMatrixMultiply(&g_mtxWolrdObject, &g_mtxWolrdObject, &mtxTrans);

				//���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_mtxWolrdObject);

				//���݂̃}�e���A�����擾
				pDevice->GetMaterial(&matDef);

				//�}�e���A���f�[�^�ւ̃|�C���^���擾
				pMat = (D3DXMATERIAL*)g_pBuffMatObject[nCntMatVer]->GetBufferPointer();

				for (int nCntMatVer = 0; nCntMatVer < (int)g_nNumMatObject; nCntMatVer++)
				{
					if (g_PosObject[nCntMat].nType == 0)
					{
						//�}�e���A���̐ݒ�
						pDevice->SetMaterial(&pMat[nCntMatVer].MatD3D);

						//�e�N�X�`���̐ݒ�
						pDevice->SetTexture(0, NULL);

						//���f���p�[�c�̕`��
						g_pMeshObject[0]->DrawSubset(nCntMatVer);
						break;
					}

					else if (g_PosObject[nCntMat].nType == 1)
					{
						//�}�e���A���̐ݒ�
						pDevice->SetMaterial(&pMat[nCntMatVer].MatD3D);

						//�e�N�X�`���̐ݒ�
						pDevice->SetTexture(0, NULL);

						//���f���p�[�c�̕`��
						g_pMeshObject[1]->DrawSubset(nCntMatVer);
						break;
					}
				}

			}
		}
	}
	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}
//======================================
//�I�u�W�F�N�g�̎󂯓n������
//======================================
OBJECT *GetObject(void)
{
	return &g_PosObject[0];
}
//==============================================================================
// �O�ς𗘗p���������蔻��
//==============================================================================
bool CollisionVecObject(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidthMax, float fWidthMin, float fDepthMax, float fDepthMin, float fHeightMax, float fHeightMin)
{
	bool bLand = false;

	D3DXVECTOR3 pos = *pPos;// ����Ώۂ̈ʒu

	int g_nCntSt;
	int nCntObject;
	int nCnt = 0;

	g_nCntSt = 0;
	nCntObject = 0;

	for (int nCount = 0; nCount < MAXOBJECT; nCount++)
	{
		if (g_PosObject[nCount].bUse == true)
		{
			//aPos�̒l�ݒ�
			g_PosObject[nCount].aPosObject[0 + (nCount * 4)] = D3DXVECTOR3(g_PosObject[nCount].Pos.x + g_PosObject[nCount].MinObject.x, 0.0f, g_PosObject[nCount].Pos.z + g_PosObject[nCount].MinObject.z);
			g_PosObject[nCount].aPosObject[1 + (nCount * 4)] = D3DXVECTOR3(g_PosObject[nCount].Pos.x + g_PosObject[nCount].MinObject.x, 0.0f, g_PosObject[nCount].Pos.z + g_PosObject[nCount].MaxObject.z);
			g_PosObject[nCount].aPosObject[2 + (nCount * 4)] = D3DXVECTOR3(g_PosObject[nCount].Pos.x + g_PosObject[nCount].MaxObject.x, 0.0f, g_PosObject[nCount].Pos.z + g_PosObject[nCount].MaxObject.z);
			g_PosObject[nCount].aPosObject[3 + (nCount * 4)] = D3DXVECTOR3(g_PosObject[nCount].Pos.x + g_PosObject[nCount].MaxObject.x, 0.0f, g_PosObject[nCount].Pos.z + g_PosObject[nCount].MinObject.z);

			//�O�ς̎�
			g_PosObject[nCount].VecObject[0 + (nCount * 4)] = g_PosObject[nCount].aPosObject[1 + (nCount * 4)] - g_PosObject[nCount].aPosObject[0 + (nCount * 4)];
			g_PosObject[nCount].VecObject[1 + (nCount * 4)] = g_PosObject[nCount].aPosObject[2 + (nCount * 4)] - g_PosObject[nCount].aPosObject[1 + (nCount * 4)];
			g_PosObject[nCount].VecObject[2 + (nCount * 4)] = g_PosObject[nCount].aPosObject[3 + (nCount * 4)] - g_PosObject[nCount].aPosObject[2 + (nCount * 4)];
			g_PosObject[nCount].VecObject[3 + (nCount * 4)] = g_PosObject[nCount].aPosObject[0 + (nCount * 4)] - g_PosObject[nCount].aPosObject[3 + (nCount * 4)];
		}
	}

	for (int nCount = 0; nCount < MAXOBJECTVER; nCount++)
	{
		if (g_PosObject[nCntObject].bUse == true)
		{
			//�O�ς̎�2
			if (nCount == 0 + g_nCntSt)
			{
				g_PosObject[nCntObject].aVecObject[nCount] = pos + D3DXVECTOR3(fWidthMax, 0.0f, 0.0f) - g_PosObject[nCntObject].aPosObject[nCount];
			}
			else if (nCount == 1 + g_nCntSt)
			{
				g_PosObject[nCntObject].aVecObject[nCount] = pos + D3DXVECTOR3(0.0f, 0.0f, fDepthMin) - g_PosObject[nCntObject].aPosObject[nCount];
			}
			else if (nCount == 2 + g_nCntSt)
			{
				g_PosObject[nCntObject].aVecObject[nCount] = pos + D3DXVECTOR3(fWidthMin, 0.0f, 0.0f) - g_PosObject[nCntObject].aPosObject[nCount];
			}
			else if (nCount == 3 + g_nCntSt)
			{
				g_PosObject[nCntObject].aVecObject[nCount] = pos + D3DXVECTOR3(0.0f, 0.0f, fDepthMax) - g_PosObject[nCntObject].aPosObject[nCount];
			}

			g_PosObject[nCntObject].ObjectVec[nCount] = (g_PosObject[nCntObject].VecObject[nCount].z * g_PosObject[nCntObject].aVecObject[nCount].x) - (g_PosObject[nCntObject].VecObject[nCount].x * g_PosObject[nCntObject].aVecObject[nCount].z);

			if (pPos->y <= g_PosObject[nCntObject].Pos.y + g_PosObject[nCntObject].MaxObject.y - fHeightMin && pPos->y > g_PosObject[nCntObject].Pos.y + g_PosObject[nCntObject].MinObject.y - fHeightMax)
			{
				if (g_PosObject[nCntObject].ObjectVec[0 + (nCntObject * 4)] > 0.0f && g_PosObject[nCntObject].ObjectVec[1 + (nCntObject * 4)] > 0.0f && g_PosObject[nCntObject].ObjectVec[2 + (nCntObject * 4)] > 0.0f && g_PosObject[nCntObject].ObjectVec[3 + (nCntObject * 4)] > 0.0f)
				{
					if (pPos->x >= pPosOld->x && pPosOld->x < g_PosObject[nCntObject].Pos.x + g_PosObject[nCntObject].MinObject.x)
					{// ����	
						pPos->x = g_PosObject[nCntObject].Pos.x + g_PosObject[nCntObject].MinObject.x - fWidthMax;
						//pMove->x = 0.0f;
					}
					else if (pPos->x <= pPosOld->x && pPosOld->x > g_PosObject[nCntObject].Pos.x + g_PosObject[nCntObject].MaxObject.x)
					{// �E��	
						pPos->x = g_PosObject[nCntObject].Pos.x + g_PosObject[nCntObject].MaxObject.x - fWidthMin;
						//pMove->x = 0.0f;
					}
					else if (pPos->z <= pPosOld->z &&  pPos->z > g_PosObject[nCntObject].Pos.z)
					{// ����
						pPos->z = g_PosObject[nCntObject].Pos.z + g_PosObject[nCntObject].MaxObject.z - fDepthMin;
					}
					else if (pPos->z >= pPosOld->z && pPos->z < g_PosObject[nCntObject].Pos.z)
					{// ��O
						pPos->z = g_PosObject[nCntObject].Pos.z + g_PosObject[nCntObject].MinObject.z - fDepthMax;
					}
				}
			}

			if (nCount == 3 + (4 * nCntObject))
			{
				g_nCntSt += 4;
				nCntObject += 1;
			}
		}
	}

		return bLand;
}
void SetObject(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType)
{
	BYTE *pVtxBuff;//���_�o�b�t�@�ւ̃|�C���^

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCntMat = 0; nCntMat < MAXOBJECT; nCntMat++)
	{
		//���_�o�b�t�@�̃��b�N
		g_pMeshObject[g_PosObject[nCntMat].nType]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		if (g_PosObject[nCntMat].bUse == false)//�e���g�p���Ă��邩�ǂ���
		{
			if (nType == 0)
			{
				//�ʒu�ݒ�
				g_PosObject[nCntMat].Pos = pos;

				//�ʒu��]
				g_PosObject[nCntMat].rot = rot;

				//�^�C�v����
				g_PosObject[nCntMat].nType = nType;

				//�e�̎g�p
				g_PosObject[nCntMat].bUse = true;
				break;
			}

			else if (nType == 1)
			{
				//�ʒu�ݒ�
				g_PosObject[nCntMat].Pos = pos;

				//�ʒu��]
				g_PosObject[nCntMat].rot = rot;

				//�^�C�v����
				g_PosObject[nCntMat].nType = nType;

				//�e�̎g�p
				g_PosObject[nCntMat].bUse = true;
				break;
			}
		}

		//���_�o�b�t�@�̃A�����b�N
		g_pMeshObject[g_PosObject[nCntMat].nType]->UnlockVertexBuffer();
	}
}

