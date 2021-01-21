//================================================
//
//�o�b�N�O���E���h����[Player.h]
// Author; miura yuudai
//
//================================================
#include "bg.h"

//==============
//�O���[�o���ϐ�
//==============
LPDIRECT3DTEXTURE9 g_pTextureBG[5] = {};//�e�N�X�`�����
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG = NULL;//���_���
BG g_bg[5];//�o�b�N�O���E���h���

//====================
//�o�b�N�O���E���h�̏���������
//====================
HRESULT InitBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	VERTEX_2D *pVtx;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/14.png", &g_pTextureBG[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/14.png", &g_pTextureBG[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/title.png", &g_pTextureBG[2]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ddd.png", &g_pTextureBG[3]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/hplogo.png", &g_pTextureBG[4]);


	//�ϐ�������
	for (int nCount = 0; nCount < 5; nCount++)
	{
		g_bg[nCount].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_bg[nCount].nType = 0;
		g_bg[nCount].bUse = false;
	}

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 5,
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
	
	for (int nCount = 0; nCount < 5; nCount++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(200, 1030, 0.0f);//2D��0.0�Œ�
		pVtx[1].pos = D3DXVECTOR3(200, 50, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(1220, 1030, 0.0f);
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

	return S_OK;
}
//==================
//�o�b�N�O���E���h�̏I������
//==================
void UninitBG(void)
{
	for (int nCount = 0; nCount < 5; nCount++)
	{
		//�e�N�X�`���̊J��
		if (g_pTextureBG[nCount] != NULL)
		{
			g_pTextureBG[nCount]->Release();
			g_pTextureBG[nCount] = NULL;
		}
	}

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffBG != NULL)
	{
		g_pVtxBuffBG->Release();
		g_pVtxBuffBG = NULL;
	}

}
//==================
//�o�b�N�O���E���h�̍X�V����
//==================
void UpdateBG(void)
{

}

//==================
//�o�b�N�O���E���h�̕`�揈��
//==================
void DrawBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBG, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCount = 0; nCount < 5; nCount++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureBG[nCount]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
	}
}
//==================
//�o�b�N�O���E���h�̐ݒ菈��
//==================
void SetBG(D3DXVECTOR3 Pos, int nType)
{
	BG *pbg;
	VERTEX_2D *pVtx;

	pbg = &g_bg[0];

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < 5; nCount++, pbg++)
	{
		if (g_bg[nCount].bUse == false)//�o�b�N�O���E���h���g�p���Ă��邩�ǂ���
		{
			if (nType == 0)//�^�C�v��0�̎�
			{
				//�ʒu�ݒ�
				g_bg[nCount].Pos = Pos;

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);//2D��0.0�Œ�
				pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
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

		if (nType == 1)//�^�C�v��1�̎�
		{
			//�ʒu�ݒ�
			g_bg[nCount].Pos = Pos;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(50, 1030, 0.0f);//2D��0.0�Œ�
			pVtx[1].pos = D3DXVECTOR3(50, 50, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(1220, 1030, 0.0f);
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

		if (nType == 2)//�^�C�v��2�̎�
		{
			//�ʒu�ݒ�
			g_bg[nCount].Pos = Pos;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_bg[nCount].Pos.x - 150, g_bg[nCount].Pos.y + 100, 0.0f);//2D��0.0�Œ�
			pVtx[1].pos = D3DXVECTOR3(g_bg[nCount].Pos.x - 150, g_bg[nCount].Pos.y - 100, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_bg[nCount].Pos.x + 600, g_bg[nCount].Pos.y + 100, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_bg[nCount].Pos.x + 600, g_bg[nCount].Pos.y - 100, 0.0f);//2D��0.0�Œ�

			//�^�C�v�ݒ�
			pbg->nType = nType;

			//�o�b�N�O���E���h�̎g�p
			pbg->bUse = true;
			break;
		}

		if (nType == 3)//�^�C�v��2�̎�
		{
			//�ʒu�ݒ�
			g_bg[nCount].Pos = Pos;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_bg[nCount].Pos.x - 150, g_bg[nCount].Pos.y + 150, 0.0f);//2D��0.0�Œ�
			pVtx[1].pos = D3DXVECTOR3(g_bg[nCount].Pos.x - 150, g_bg[nCount].Pos.y - 150, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_bg[nCount].Pos.x + 150, g_bg[nCount].Pos.y + 150, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_bg[nCount].Pos.x + 150, g_bg[nCount].Pos.y - 150, 0.0f);//2D��0.0�Œ�

			//�^�C�v�ݒ�
			pbg->nType = nType;

			//�o�b�N�O���E���h�̎g�p
			pbg->bUse = true;
			break;
		}

		if (nType == 4)//�^�C�v��2�̎�
		{
			//�ʒu�ݒ�
			g_bg[nCount].Pos = Pos;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_bg[nCount].Pos.x - 25, g_bg[nCount].Pos.y + 25, 0.0f);//2D��0.0�Œ�
			pVtx[1].pos = D3DXVECTOR3(g_bg[nCount].Pos.x - 25, g_bg[nCount].Pos.y - 25, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_bg[nCount].Pos.x + 25, g_bg[nCount].Pos.y + 25, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_bg[nCount].Pos.x + 25, g_bg[nCount].Pos.y - 25, 0.0f);//2D��0.0�Œ�

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

