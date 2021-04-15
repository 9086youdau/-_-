//================================================
//
//�e�̏���[Player.h]
// Author; miura yuudai
//
//================================================
#include "bullet.h"
#include "input.h"
#include "Billboard.h"

//�}�N����`
#define MAX_BULLET_SIZE (5)//�G�t�F�N�g�̃T�C�Y
#define MAX_BULLET (256)//�z��

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexturebullet = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffbullet;//���_�|�C���^
BULLET g_abullet[MAX_BULLET];//�e�̏��
D3DXCOLOR g_colorbullet;

//==================
//�e�̏���������
//==================
HRESULT InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/10.png", &g_pTexturebullet);

	//������
	for (int nCntEffect = 0; nCntEffect < MAX_BULLET; nCntEffect++)
	{
		g_abullet[nCntEffect].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_abullet[nCntEffect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_abullet[nCntEffect].bUse = false;
		g_colorbullet = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
		g_abullet[nCntEffect].nLife = 0;
	}

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffbullet, NULL)))
	{
		return E_FAIL;
	}

	VERTEX_3D *pVtx;

	BULLET *pBullet;
	pBullet = &g_abullet[0];

	//���_�o�b�t�@�����b�N
	g_pVtxBuffbullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_BULLET; nCntEffect++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(pBullet->Pos.x - MAX_BULLET_SIZE, pBullet->Pos.y + MAX_BULLET_SIZE, pBullet->Pos.z);//2D��0.0�Œ�
		pVtx[1].pos = D3DXVECTOR3(pBullet->Pos.x + MAX_BULLET_SIZE, pBullet->Pos.y + MAX_BULLET_SIZE, pBullet->Pos.z);
		pVtx[2].pos = D3DXVECTOR3(pBullet->Pos.x - MAX_BULLET_SIZE, pBullet->Pos.y - MAX_BULLET_SIZE, pBullet->Pos.z);
		pVtx[3].pos = D3DXVECTOR3(pBullet->Pos.x + MAX_BULLET_SIZE, pBullet->Pos.y - MAX_BULLET_SIZE, pBullet->Pos.z);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = g_colorbullet;
		pVtx[1].col = g_colorbullet;
		pVtx[2].col = g_colorbullet;
		pVtx[3].col = g_colorbullet;

		//���_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4; //4���_���Ƃ��炷
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffbullet->Unlock();

	return  S_OK;
}

//====================
//�e�̏I������
//====================
void UninitBullet(void)
{
	//�e�N�X�`���̊J��
	if (g_pTexturebullet != NULL)
	{
		g_pTexturebullet->Release();
		g_pTexturebullet = NULL;
	}

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffbullet != NULL)
	{
		g_pVtxBuffbullet->Release();
		g_pVtxBuffbullet = NULL;
	}
}

//====================
//�e�̍X�V����
//====================
void UpdateBullet(void)
{
	BULLET *pBullet;
	pBullet = &g_abullet[0];


	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffbullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_BULLET; nCntEffect++, pBullet++)
	{
		if (pBullet->bUse == true)//�G�t�F�N�g���g�p���Ă��邩�ǂ���
		{
			//int nLife = 20;//�����������_��

			//SetBillboard(pBullet->Pos, nLife, pBullet->move ,0)

			//�����`�F�b�N
			pBullet->nLife--;
			if (pBullet->nLife == 0)//������0�ɂȂ�����
			{
				pBullet->bUse = false;//�g�p���Ȃ�
			}

			pBullet->Pos += pBullet->move;

		}
		//4���_���Ƃ��炷
		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffbullet->Unlock();
}

//====================
//�e�̕`�揈��
//====================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	BULLET *pBullet;
	pBullet = &g_abullet[0];

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�r���[�}�g���b�N�X�擾�p
	D3DXMATRIX mtxView;

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxTrans;

	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	for (int nCntEffect = 0; nCntEffect < MAX_BULLET; nCntEffect++,pBullet++)
	{
		if (g_abullet[nCntEffect].bUse == true)
		{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&pBullet->mtxWorld);

		//�r���[�}�g���b�N�X���擾
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
		D3DXMatrixInverse(&pBullet->mtxWorld, NULL, &mtxView);//�t�s������߂�
		pBullet->mtxWorld._41 = 0.0f;
		pBullet->mtxWorld._42 = 0.0f;
		pBullet->mtxWorld._43 = 0.0f;

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, pBullet->Pos.x, pBullet->Pos.y, pBullet->Pos.z);

		D3DXMatrixMultiply(&pBullet->mtxWorld, &pBullet->mtxWorld, &mtxTrans);

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffbullet, 0, sizeof(VERTEX_3D));

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &pBullet->mtxWorld);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturebullet);

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEffect * 4, 2);

		}

	}
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

//================
//�e�̐ݒ�
//================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife)
{
	VERTEX_3D *pVtx;

	BULLET *pBullet;
	pBullet = &g_abullet[0];

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffbullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_BULLET; nCntEffect++, pBullet++)
	{
		if (pBullet->bUse == false)//�e���g�p���Ă��邩�ǂ���
		{
			//�ʒu�ݒ�
			pBullet->Pos = pos;

			pBullet->nLife = nLife;

			pBullet->move = move;

			//�e�̎g�p
			pBullet->bUse = true;
			break;
		}
		//4���_���Ƃ��炷
		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffbullet->Unlock();
}
BULLET *GetBullet(void)
{
	return &g_abullet[0];
}