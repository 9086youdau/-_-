//================================================
//
//�΂̏���[stone.h]
// Author; miura yuudai
//
//================================================

#include "Item.h"
#include "input.h"
#include "camera.h"
#include "Billboard.h"
#include "bullet.h"
#include "model.h"
#include "fade.h"
#include "Timer.h"
#include "Coin.h"

//=====================
//�O���[�o���ϐ�
//=====================
//���b�V���i���_���j�ւ̃|�C���^
LPD3DXMESH g_pMeshItem = NULL;

//�}�e���A���i�ގ����j�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatItem = NULL;

DWORD g_nNumMatItem = 0;//�}�e���A���̐�
Item g_PosItem[MAXITEM];//x�t�@�C��
D3DXMATRIX g_mtxWolrdItem;//���[���h�}�g���b�N�X
int nCntScore = 0;

//====================
//���f���̏���������
//====================
void InitItem(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//x�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data/MODEL/Item000.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatItem, NULL, &g_nNumMatItem, &g_pMeshItem);

	for (int nCntMat = 0; nCntMat < MAXITEM; nCntMat++)
	{
		//�ϐ�������
		g_PosItem[nCntMat].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_PosItem[nCntMat].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_PosItem[nCntMat].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_PosItem[nCntMat].rotmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_PosItem[nCntMat].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_PosItem[nCntMat].MaxStone = D3DXVECTOR3(-100000.0f, -100000.0f, -100000.0f);
		g_PosItem[nCntMat].MinStone = D3DXVECTOR3(100000.0f, 100000.0f, 100000.0f);
		g_PosItem[nCntMat].bUse = false;
		nCntScore = 0;


		g_pMeshItem->UnlockVertexBuffer();
	}
}
//=======================
//���f���̏I������
//=======================
void UninitItem(void)
{
	//���_�̊J��
	if (g_pMeshItem != NULL)
	{
		g_pMeshItem->Release();
		g_pMeshItem = NULL;
	}

	//�ގ��̊J��
	if (g_pBuffMatItem != NULL)
	{
		g_pBuffMatItem->Release();
		g_pBuffMatItem = NULL;
	}

}
//=======================
//���f���̍X�V����
//=======================
void UpdateItem(void)
{
	int nNumVtx;//���_��
	DWORD sizeFVF;//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;//���_�o�b�t�@�ւ̃|�C���^


	for (int nCntMat = 0; nCntMat < MAXITEM; nCntMat++)
	{
		if (g_PosItem[nCntMat].bUse == true)
		{
			nNumVtx = g_pMeshItem->GetNumVertices();

			//���_�t�H�[�}�b�g�̃T�C�Y���擾
			sizeFVF = D3DXGetFVFVertexSize(g_pMeshItem->GetFVF());

			//���_�o�b�t�@�̃��b�N
			g_pMeshItem->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;//���_���W�̑��

				if (vtx.x > g_PosItem[nCntMat].MaxStone.x)
				{
					g_PosItem[nCntMat].MaxStone.x = vtx.x;
				}

				if (vtx.x < g_PosItem[nCntMat].MinStone.x)
				{
					g_PosItem[nCntMat].MinStone.x = vtx.x;
				}

				if (vtx.y > g_PosItem[nCntMat].MaxStone.y)
				{
					g_PosItem[nCntMat].MaxStone.y = vtx.y;
				}

				if (vtx.y < g_PosItem[nCntMat].MinStone.y)
				{
					g_PosItem[nCntMat].MinStone.y = vtx.y;
				}

				if (vtx.z > g_PosItem[nCntMat].MaxStone.z)
				{
					g_PosItem[nCntMat].MaxStone.z = vtx.z;
				}

				if (vtx.z < g_PosItem[nCntMat].MinStone.z)
				{
					g_PosItem[nCntMat].MinStone.z = vtx.z;
				}

				pVtxBuff += sizeFVF;//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			}
		}
	}

	if(nCntScore == 20)
	{
		SetFade(FADE_OUT, MODE_RESULT);
	}

}
//=======================
//���f���̕`�揈��
//=======================
void DrawItem(void)
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

	for (int nCntMat = 0; nCntMat < MAXITEM; nCntMat++)
	{
		if (g_PosItem[nCntMat].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWolrdItem);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_PosItem[nCntMat].rot.y, g_PosItem[nCntMat].rot.x, g_PosItem[nCntMat].rot.z);

			D3DXMatrixMultiply(&g_mtxWolrdItem, &g_mtxWolrdItem, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_PosItem[nCntMat].Pos.x, g_PosItem[nCntMat].Pos.y, g_PosItem[nCntMat].Pos.z);

			D3DXMatrixMultiply(&g_mtxWolrdItem, &g_mtxWolrdItem, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWolrdItem);

			//���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			for (int nCntMatVer = 0; nCntMatVer < (int)g_nNumMatItem; nCntMatVer++)
			{
				//�}�e���A���f�[�^�ւ̃|�C���^���擾
				pMat = (D3DXMATERIAL*)g_pBuffMatItem->GetBufferPointer();

				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMatVer].MatD3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, NULL);

				//���f���p�[�c�̕`��
				g_pMeshItem->DrawSubset(nCntMatVer);;
			}
		}
		//�ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}
Item *GetItem(void)
{
	return &g_PosItem[0];
}
//==============================================================================
// �O�ς𗘗p���������蔻��
//==============================================================================
bool CollisionVecItem(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidthMax, float fWidthMin, float fDepthMax, float fDepthMin, float fHeightMax, float fHeightMin)
{
	bool bLand = false;

	D3DXVECTOR3 pos = *pPos;// ����Ώۂ̈ʒu

	int g_nCntSt;
	int nCntStone;

	g_nCntSt = 0;
	nCntStone = 0;
	//nCntScore = 0;

	for (int nCount = 0; nCount < MAXITEM; nCount++)
	{
		//if (g_PosItem[nCount].bUse == true)
		{
			//aPos�̒l�ݒ�
			g_PosItem[nCount].aPos[0 + (nCount * 4)] = D3DXVECTOR3(g_PosItem[nCount].Pos.x + g_PosItem[nCount].MinStone.x, 0.0f, g_PosItem[nCount].Pos.z + g_PosItem[nCount].MinStone.z);
			g_PosItem[nCount].aPos[1 + (nCount * 4)] = D3DXVECTOR3(g_PosItem[nCount].Pos.x + g_PosItem[nCount].MinStone.x, 0.0f, g_PosItem[nCount].Pos.z + g_PosItem[nCount].MaxStone.z);
			g_PosItem[nCount].aPos[2 + (nCount * 4)] = D3DXVECTOR3(g_PosItem[nCount].Pos.x + g_PosItem[nCount].MaxStone.x, 0.0f, g_PosItem[nCount].Pos.z + g_PosItem[nCount].MaxStone.z);
			g_PosItem[nCount].aPos[3 + (nCount * 4)] = D3DXVECTOR3(g_PosItem[nCount].Pos.x + g_PosItem[nCount].MaxStone.x, 0.0f, g_PosItem[nCount].Pos.z + g_PosItem[nCount].MinStone.z);

			//�O�ς̎�
			g_PosItem[nCount].Vec[0 + (nCount * 4)] = g_PosItem[nCount].aPos[1 + (nCount * 4)] - g_PosItem[nCount].aPos[0 + (nCount * 4)];
			g_PosItem[nCount].Vec[1 + (nCount * 4)] = g_PosItem[nCount].aPos[2 + (nCount * 4)] - g_PosItem[nCount].aPos[1 + (nCount * 4)];
			g_PosItem[nCount].Vec[2 + (nCount * 4)] = g_PosItem[nCount].aPos[3 + (nCount * 4)] - g_PosItem[nCount].aPos[2 + (nCount * 4)];
			g_PosItem[nCount].Vec[3 + (nCount * 4)] = g_PosItem[nCount].aPos[0 + (nCount * 4)] - g_PosItem[nCount].aPos[3 + (nCount * 4)];
		}
	}

	for (int nCount = 0; nCount < MAXITEMVER; nCount++)
	{
		//�O�ς̎�2
		if (nCount == 0 + g_nCntSt)
		{
			g_PosItem[nCntStone].g_Vec[nCount] = pos + D3DXVECTOR3(fWidthMax, 0.0f, 0.0f) - g_PosItem[nCntStone].aPos[nCount];
		}
		else if (nCount == 1 + g_nCntSt)
		{
			g_PosItem[nCntStone].g_Vec[nCount] = pos + D3DXVECTOR3(0.0f, 0.0f, fDepthMin) - g_PosItem[nCntStone].aPos[nCount];
		}
		else if (nCount == 2 + g_nCntSt)
		{
			g_PosItem[nCntStone].g_Vec[nCount] = pos + D3DXVECTOR3(fWidthMin, 0.0f, 0.0f) - g_PosItem[nCntStone].aPos[nCount];
		}
		else if (nCount == 3 + g_nCntSt)
		{
			g_PosItem[nCntStone].g_Vec[nCount] = pos + D3DXVECTOR3(0.0f, 0.0f, fDepthMax) - g_PosItem[nCntStone].aPos[nCount];
		}

		g_PosItem[nCntStone].PlayerVec[nCount] = (g_PosItem[nCntStone].Vec[nCount].z * g_PosItem[nCntStone].g_Vec[nCount].x) - (g_PosItem[nCntStone].Vec[nCount].x * g_PosItem[nCntStone].g_Vec[nCount].z);

		if (pPos->y <= g_PosItem[nCntStone].Pos.y + g_PosItem[nCntStone].MaxStone.y - fHeightMin && pPos->y > g_PosItem[nCntStone].Pos.y + g_PosItem[nCntStone].MinStone.y - fHeightMax)
		{
			if (g_PosItem[nCntStone].PlayerVec[0 + (nCntStone * 4)] > 0.0f && g_PosItem[nCntStone].PlayerVec[1 + (nCntStone * 4)] > 0.0f && g_PosItem[nCntStone].PlayerVec[2 + (nCntStone * 4)] > 0.0f && g_PosItem[nCntStone].PlayerVec[3 + (nCntStone * 4)] > 0.0f)
			{
				if (g_PosItem[nCntStone].bUse == true)
				{
					g_PosItem[nCntStone].bUse = false;
					AddCoin(1);
					nCntScore++;
					for (int nCntMat = 0; nCntMat < 106; nCntMat++)
					{
						D3DXVECTOR3 pos;
						int nLife;
						D3DXVECTOR3 move;
						float fAngle;

						pos = D3DXVECTOR3(g_PosItem[nCntStone].Pos.x, g_PosItem[nCntStone].Pos.y, g_PosItem[nCntStone].Pos.z);//�ʒu
						nLife = 15 + rand() % 20;//�����������_��
						fAngle = (float)(rand() % 628 - 314) / 100.0f;//�����͈̔�
						move.x = sinf(fAngle)*2.5f;//x���̒e�̑��x
						move.y = cosf(fAngle)*2.5f;//y���̒e�̑��x
						move.z = cosf(fAngle)*2.5f;//y���̒e�̑��x
						SetBillboard(pos, nLife, move, 0);//�G�t�F�N�g����
					}
				}
			}
		}

		if (nCount == 3 + (4 * nCntStone))
		{
			g_nCntSt += 4;
			nCntStone += 1;
		}
	}
	return bLand;
}
void SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	BYTE *pVtxBuff;//���_�o�b�t�@�ւ̃|�C���^

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�̃��b�N
	g_pMeshItem->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntMat = 0; nCntMat < MAXITEM; nCntMat++)
	{
		if (g_PosItem[nCntMat].bUse == false)//�e���g�p���Ă��邩�ǂ���
		{
			//�ʒu�ݒ�
			g_PosItem[nCntMat].Pos = pos;

			//�ʒu��]
			g_PosItem[nCntMat].rot = rot;

			//�e�̎g�p
			g_PosItem[nCntMat].bUse = true;
			break;
		}
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pMeshItem->UnlockVertexBuffer();
}

