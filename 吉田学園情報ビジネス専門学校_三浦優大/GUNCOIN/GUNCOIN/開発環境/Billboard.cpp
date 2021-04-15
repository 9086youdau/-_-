//================================================
//
//�G�t�F�N�g����[Player.h]
// Author; miura yuudai
//
//================================================
#include "Billboard.h"
#include "input.h"

//�}�N����`
#define MAX_EFFECT_SIZE (5)//�G�t�F�N�g�̃T�C�Y
#define MAX_EFFECT (7096)//�z��

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard;//���_�|�C���^
BILLBOARD g_abillboard[MAX_EFFECT];//�e�̏��
D3DXCOLOR g_colorBillboard;
D3DXMATRIX g_mtxWorldBillboard;//���[���h�}�g���b�N�X

//==================
//�G�t�F�N�g�̏���������
//==================
HRESULT InitBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect000.jpg", &g_abillboard[0].pTextureBillboard);

	//������
	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_abillboard[nCntEffect].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_abillboard[nCntEffect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_abillboard[nCntEffect].bUse = false;
		g_colorBillboard = D3DXCOLOR(0.2f, 0.2f, 1.0f, 1.0f);
		g_abillboard[nCntEffect].nLife = 0;
		g_abillboard[nCntEffect].nType = 0;
	}

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EFFECT, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffBillboard, NULL)))
	{
		return E_FAIL;
	}

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_abillboard[nCntEffect].Pos.x - MAX_EFFECT_SIZE, g_abillboard[nCntEffect].Pos.y + MAX_EFFECT_SIZE, g_abillboard[nCntEffect].Pos.z);//2D��0.0�Œ�
		pVtx[1].pos = D3DXVECTOR3(g_abillboard[nCntEffect].Pos.x + MAX_EFFECT_SIZE, g_abillboard[nCntEffect].Pos.y + MAX_EFFECT_SIZE, g_abillboard[nCntEffect].Pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_abillboard[nCntEffect].Pos.x - MAX_EFFECT_SIZE, g_abillboard[nCntEffect].Pos.y - MAX_EFFECT_SIZE, g_abillboard[nCntEffect].Pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_abillboard[nCntEffect].Pos.x + MAX_EFFECT_SIZE, g_abillboard[nCntEffect].Pos.y - MAX_EFFECT_SIZE, g_abillboard[nCntEffect].Pos.z);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = g_colorBillboard;
		pVtx[1].col = g_colorBillboard;
		pVtx[2].col = g_colorBillboard;
		pVtx[3].col = g_colorBillboard;

		//���_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4; //4���_���Ƃ��炷
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBillboard->Unlock();

	return  S_OK;
}

//====================
//�G�t�F�N�g�̏I������
//====================
void UninitBillboard(void)
{
	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		//�e�N�X�`���̊J��
		if (g_abillboard[nCntEffect].pTextureBillboard != NULL)
		{
			g_abillboard[nCntEffect].pTextureBillboard->Release();
			g_abillboard[nCntEffect].pTextureBillboard = NULL;
		}
	}

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}
}

//====================
//�G�t�F�N�g�̍X�V����
//====================
void UpdateBillboard(void)
{
	BILLBOARD *pBillboard;
	pBillboard = &g_abillboard[0];

	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pBillboard++)
	{
		if (pBillboard->bUse == true)//�G�t�F�N�g���g�p���Ă��邩�ǂ���
		{
			if (pBillboard->nType == 0)
			{
				pBillboard->Pos += pBillboard->move;

				pBillboard->color = g_colorBillboard;

				pBillboard->move.y += 1.0f;

				//�����`�F�b�N
				pBillboard->nLife--;
				if (pBillboard->nLife == 0)//������0�ɂȂ�����
				{
					pBillboard->bUse = false;//�g�p���Ȃ�
				}
			}
			else if (pBillboard->nType == 1)
			{
				pBillboard->Pos += pBillboard->move;

				pBillboard->color = g_colorBillboard;

				////���_���W�̐ݒ�
				//pVtx[0].pos = D3DXVECTOR3(g_abillboard[nCntEffect].Pos.x - 25, g_abillboard[nCntEffect].Pos.y + 25, g_abillboard[nCntEffect].Pos.z);//2D��0.0�Œ�
				//pVtx[1].pos = D3DXVECTOR3(g_abillboard[nCntEffect].Pos.x + 25, g_abillboard[nCntEffect].Pos.y + 25, g_abillboard[nCntEffect].Pos.z);
				//pVtx[2].pos = D3DXVECTOR3(g_abillboard[nCntEffect].Pos.x - 25, g_abillboard[nCntEffect].Pos.y - 25, g_abillboard[nCntEffect].Pos.z);
				//pVtx[3].pos = D3DXVECTOR3(g_abillboard[nCntEffect].Pos.x + 25, g_abillboard[nCntEffect].Pos.y - 25, g_abillboard[nCntEffect].Pos.z);

				//�����`�F�b�N
				pBillboard->nLife--;
				if (pBillboard->nLife == 0)//������0�ɂȂ�����
				{
					pBillboard->bUse = false;//�g�p���Ȃ�
				}
			}
		}
		//4���_���Ƃ��炷
		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffBillboard->Unlock();
}

//====================
//�G�t�F�N�g�̕`�揈��
//====================
void DrawBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	BILLBOARD *pBillboard;
	pBillboard = &g_abillboard[0];

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�r���[�}�g���b�N�X�擾�p
	D3DXMATRIX mtxView;

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxTrans;

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_abillboard[nCntEffect].bUse == true)
		{
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

			//�����_�[�X�e�[�g�̐ݒ�(���Z�����j
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldBillboard);

			//�r���[�}�g���b�N�X���擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
			D3DXMatrixInverse(&g_mtxWorldBillboard, NULL, &mtxView);//�t�s������߂�
			g_mtxWorldBillboard._41 = 0.0f;
			g_mtxWorldBillboard._42 = 0.0f;
			g_mtxWorldBillboard._43 = 0.0f;

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_abillboard[nCntEffect].Pos.x, g_abillboard[nCntEffect].Pos.y, g_abillboard[nCntEffect].Pos.z);

			D3DXMatrixMultiply(&g_mtxWorldBillboard, &g_mtxWorldBillboard, &mtxTrans);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldBillboard);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_abillboard[0].pTextureBillboard);

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEffect * 4, 2);

			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

			//�����_�[�X�e�[�g�̐ݒ�(���ɖ߂��j
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		}
	}
}

//================
//�G�t�F�N�g�̐ݒ�
//================
void SetBillboard(D3DXVECTOR3 pos, int nLife, D3DXVECTOR3 move,int nType)
{
	VERTEX_3D *pVtx;

	BILLBOARD *pBillboard;
	pBillboard = &g_abillboard[0];

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pBillboard++)
	{
		if (pBillboard->bUse == false)//�e���g�p���Ă��邩�ǂ���
		{
			if (nType == 0)
			{
				//�ʒu�ݒ�
				pBillboard->Pos = pos;

				pBillboard->nLife = nLife;

				pBillboard->move = move;

				pBillboard->nType = nType;

				//���_���W�̐ݒ�
				//pVtx[0].pos = D3DXVECTOR3(pBillboard->Pos.x - MAX_EFFECT_SIZE, pBillboard->Pos.y + MAX_EFFECT_SIZE, 0.0f);//2D��0.0�Œ�
				//pVtx[1].pos = D3DXVECTOR3(pBillboard->Pos.x + MAX_EFFECT_SIZE, pBillboard->Pos.y + MAX_EFFECT_SIZE, 0.0f);
				//pVtx[2].pos = D3DXVECTOR3(pBillboard->Pos.x - MAX_EFFECT_SIZE, pBillboard->Pos.y - MAX_EFFECT_SIZE, 0.0f);
				//pVtx[3].pos = D3DXVECTOR3(pBillboard->Pos.x + MAX_EFFECT_SIZE, pBillboard->Pos.y - MAX_EFFECT_SIZE, 0.0f);

				//�e�̎g�p
				pBillboard->bUse = true;
				break;
			}

			else if(nType == 1)
			{
				//�ʒu�ݒ�
				pBillboard->Pos = pos;

				pBillboard->nLife = nLife;

				pBillboard->move = move;

				pBillboard->nType = nType;

				//���_�J���[�̐ݒ�
				pVtx[0].col = g_colorBillboard = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[1].col = g_colorBillboard = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[2].col = g_colorBillboard = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[3].col = g_colorBillboard = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);


				//���_���W�̐ݒ�
				//pVtx[0].pos = D3DXVECTOR3(pBillboard->Pos.x - MAX_EFFECT_SIZE, pBillboard->Pos.y + MAX_EFFECT_SIZE, 0.0f);//2D��0.0�Œ�
				//pVtx[1].pos = D3DXVECTOR3(pBillboard->Pos.x + MAX_EFFECT_SIZE, pBillboard->Pos.y + MAX_EFFECT_SIZE, 0.0f);
				//pVtx[2].pos = D3DXVECTOR3(pBillboard->Pos.x - MAX_EFFECT_SIZE, pBillboard->Pos.y - MAX_EFFECT_SIZE, 0.0f);
				//pVtx[3].pos = D3DXVECTOR3(pBillboard->Pos.x + MAX_EFFECT_SIZE, pBillboard->Pos.y - MAX_EFFECT_SIZE, 0.0f);

				//�e�̎g�p
				pBillboard->bUse = true;
				break;
			}
		}
		//4���_���Ƃ��炷
		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffBillboard->Unlock();
}
BILLBOARD *GetBillboard(void)
{
	return &g_abillboard[0];
}