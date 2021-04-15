//================================================
//
//�o�b�N�O���E���h����[BG.cpp]
// Author; miura yuudai
//
//================================================

//================================================
//�w�b�_�[�ǂݍ���
//================================================
#include "bg.h"

//============================================
//�}�N����`
//============================================
#define MAXBG (5)//�o�b�N�O���E���h�̍ő吔

//============================================
//�O���[�o���ϐ�
//============================================
LPDIRECT3DTEXTURE9 g_pTextureBG[MAXBG] = {};//�e�N�X�`�����
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG = NULL;//���_���
BG g_bg[MAXBG];//�o�b�N�O���E���h���

//========================================
//�o�b�N�O���E���h�̏���������
//========================================
HRESULT InitBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/14.png", &g_pTextureBG[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/14.png", &g_pTextureBG[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/title.png", &g_pTextureBG[2]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ShipType04.png", &g_pTextureBG[3]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/hplogo.png", &g_pTextureBG[4]);


	//�O���[�o���ϐ�������
	for (int nCount = 0; nCount < MAXBG; nCount++)
	{
		g_bg[nCount].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_bg[nCount].nType = 0;
		g_bg[nCount].bUse = false;
	}

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAXBG,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBG,
		NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);
	
	//for�����[�v
	for (int nCountBg = 0; nCountBg < MAXBG; nCountBg++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(200, 1030, 0.0f);//2D��0.0�Œ�
		pVtx[1].pos = D3DXVECTOR3(200, 50, 0.0f);//2D��0.0�Œ�
		pVtx[2].pos = D3DXVECTOR3(1220, 1030, 0.0f);//2D��0.0�Œ�
		pVtx[3].pos = D3DXVECTOR3(1220, 50, 0.0f);//2D��0.0�Œ�

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//���_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx += 4;//���_�������炷

	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBG->Unlock();

	//�Ԃ�l
	return S_OK;
}
//=================================
//�o�b�N�O���E���h�̏I������
//=================================
void UninitBG(void)
{
	for (int nCountBg = 0; nCountBg < MAXBG; nCountBg++)
	{
		//�e�N�X�`���̊J��
		if (g_pTextureBG[nCountBg] != NULL)
		{
			g_pTextureBG[nCountBg]->Release();
			g_pTextureBG[nCountBg] = NULL;
		}
	}

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffBG != NULL)
	{
		g_pVtxBuffBG->Release();
		g_pVtxBuffBG = NULL;
	}

}
//=====================================
//�o�b�N�O���E���h�̍X�V����
//=====================================
void UpdateBG(void)
{

}

//======================================
//�o�b�N�O���E���h�̕`�揈��
//======================================
void DrawBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBG, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCountBg = 0; nCountBg < MAXBG; nCountBg++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureBG[nCountBg]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCountBg * 4, 2);
	}
}
//=========================================
//�o�b�N�O���E���h�̐ݒ菈��
//=========================================
void SetBG(D3DXVECTOR3 Pos, int nType)
{
	//�|�C���^�ϐ�
	BG *pbg;
	pbg = &g_bg[0];

	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCountBg = 0; nCountBg < MAXBG; nCountBg++, pbg++)
	{
		if (g_bg[nCountBg].bUse == false)//�o�b�N�O���E���h���g�p���Ă��邩�ǂ���
		{
			if (nType == 0)//�^�C�v��0�̎�
			{
				//�ʒu�ݒ�
				g_bg[nCountBg].Pos = Pos;

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);//2D��0.0�Œ�
				pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);//2D��0.0�Œ�
				pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);//2D��0.0�Œ�
				pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);//2D��0.0�Œ�

				 //���_�J���[�̐ݒ�
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 150);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 150);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 150);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 150);

				//�^�C�v�ݒ�
				pbg->nType = nType;

				//�o�b�N�O���E���h�̎g�p
				pbg->bUse = true;
				break;
			}

			else if (nType == 1)//�^�C�v��1�̎�
			{
				//�ʒu�ݒ�
				g_bg[nCountBg].Pos = Pos;

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(50, 1030, 0.0f);//2D��0.0�Œ�
				pVtx[1].pos = D3DXVECTOR3(50, 50, 0.0f);//2D��0.0�Œ�
				pVtx[2].pos = D3DXVECTOR3(1220, 1030, 0.0f);//2D��0.0�Œ�
				pVtx[3].pos = D3DXVECTOR3(1220, 50, 0.0f);//2D��0.0�Œ�

				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

				//�^�C�v�ݒ�
				pbg->nType = nType;

				//�o�b�N�O���E���h�̎g�p
				pbg->bUse = true;
				break;
			}

			else if (nType == 2)//�^�C�v��2�̎�
			{
				//�ʒu�ݒ�
				g_bg[nCountBg].Pos = Pos;

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_bg[nCountBg].Pos.x - 150, g_bg[nCountBg].Pos.y + 100, 0.0f);//2D��0.0�Œ�
				pVtx[1].pos = D3DXVECTOR3(g_bg[nCountBg].Pos.x - 150, g_bg[nCountBg].Pos.y - 100, 0.0f);//2D��0.0�Œ�
				pVtx[2].pos = D3DXVECTOR3(g_bg[nCountBg].Pos.x + 600, g_bg[nCountBg].Pos.y + 100, 0.0f);//2D��0.0�Œ�
				pVtx[3].pos = D3DXVECTOR3(g_bg[nCountBg].Pos.x + 600, g_bg[nCountBg].Pos.y - 100, 0.0f);//2D��0.0�Œ�

				//�^�C�v�ݒ�
				pbg->nType = nType;

				//�o�b�N�O���E���h�̎g�p
				pbg->bUse = true;
				break;
			}

			else if (nType == 3)//�^�C�v��2�̎�
			{
				//�ʒu�ݒ�
				g_bg[nCountBg].Pos = Pos;

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_bg[nCountBg].Pos.x - 50, g_bg[nCountBg].Pos.y + 50, 0.0f);//2D��0.0�Œ�
				pVtx[1].pos = D3DXVECTOR3(g_bg[nCountBg].Pos.x - 50, g_bg[nCountBg].Pos.y - 50, 0.0f);//2D��0.0�Œ�
				pVtx[2].pos = D3DXVECTOR3(g_bg[nCountBg].Pos.x + 50, g_bg[nCountBg].Pos.y + 50, 0.0f);//2D��0.0�Œ�
				pVtx[3].pos = D3DXVECTOR3(g_bg[nCountBg].Pos.x + 50, g_bg[nCountBg].Pos.y - 50, 0.0f);//2D��0.0�Œ�

				//�^�C�v�ݒ�
				pbg->nType = nType;

				//�o�b�N�O���E���h�̎g�p
				pbg->bUse = true;
				break;
			}

			else if (nType == 4)//�^�C�v��2�̎�
			{
				//�ʒu�ݒ�
				g_bg[nCountBg].Pos = Pos;

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_bg[nCountBg].Pos.x - 25, g_bg[nCountBg].Pos.y + 25, 0.0f);//2D��0.0�Œ�
				pVtx[1].pos = D3DXVECTOR3(g_bg[nCountBg].Pos.x - 25, g_bg[nCountBg].Pos.y - 25, 0.0f);//2D��0.0�Œ�
				pVtx[2].pos = D3DXVECTOR3(g_bg[nCountBg].Pos.x + 25, g_bg[nCountBg].Pos.y + 25, 0.0f);//2D��0.0�Œ�
				pVtx[3].pos = D3DXVECTOR3(g_bg[nCountBg].Pos.x + 25, g_bg[nCountBg].Pos.y - 25, 0.0f);//2D��0.0�Œ�

				//�^�C�v�ݒ�
				pbg->nType = nType;

				//�o�b�N�O���E���h�̎g�p
				pbg->bUse = true;
				break;
			}
		}
		pVtx += 4;//4���_���Ƃ��炷
	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffBG->Unlock();
}

