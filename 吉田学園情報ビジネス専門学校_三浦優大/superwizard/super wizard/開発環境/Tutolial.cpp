#include "Tutolial.h"
#include "title.h"
#include "fade.h"

//==============
//�O���[�o���ϐ�
//==============
LPDIRECT3DTEXTURE9 g_pTextureTutolial[3] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutolial = NULL;//���_���
TUTOLIAL g_Tutolial[3];
D3DXCOLOR g_colorTutolial;
TUTOLIAL g_PosTitleTutolial;
TUTOLIAL g_PosEnterTutolial;

//====================
//�|���S���̏���������
//====================
HRESULT InitTutolial(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/tutolial.png", &g_pTextureTutolial[0]);
	//D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/number000.png", &g_pTextureTutolial[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/press_enter.png", &g_pTextureTutolial[2]);

	for (int nCount = 0; nCount < 3; nCount++)
	{
		g_PosTitleTutolial.Pos = D3DXVECTOR3(850.0f, 350.0f, 0.0f);
		g_PosEnterTutolial.Pos = D3DXVECTOR3(1650.0f, 1000.0f, 0.0f);
		g_Tutolial[nCount].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_colorTutolial = D3DXCOLOR(0.5f, 1.0f, 1.0f, 1.0f);
		g_Tutolial[nCount].nType = 0;
		g_Tutolial[nCount].bUse = false;
	}

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 3,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutolial,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	g_pVtxBuffTutolial->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCounter = 0; nCounter < 3; nCounter++)
	{
		//���_���W�̐ݒ�
		SetTutolial(nCounter);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = g_colorTutolial;
		pVtx[1].col = g_colorTutolial;
		pVtx[2].col = g_colorTutolial;
		pVtx[3].col = g_colorTutolial;

		//���_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffTutolial->Unlock();

	return S_OK;
}
//==================
//�|���S���̏I������
//==================
void UninitTutolial(void)
{
	//�e�N�X�`���̊J��
	for (int nCount = 0; nCount < 3; nCount++)
	{
		if (g_pTextureTutolial[nCount] != NULL)
		{
			g_pTextureTutolial[nCount]->Release();
			g_pTextureTutolial[nCount] = NULL;
		}
	}

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffTutolial != NULL)
	{
		g_pVtxBuffTutolial->Release();
		g_pVtxBuffTutolial = NULL;
	}

}
//==================
//�|���S���̍X�V����
//==================
void UpdateTutolial(void)
{
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	g_pVtxBuffTutolial->Lock(0, 0, (void**)&pVtx, 0);

	if (GetKeyboardPress(DIK_RETURN) == true)
	{
		SetFade(FADE_OUT, MODE_GAME);
	}

	//float fAnglee;
	//fAnglee = (float)(rand() % 628 - 314) / 100.0f;

	//g_PosTitleTutolial.Pos.x += sinf(fAnglee) * 0.5f;
	//g_PosTitleTutolial.Pos.y += cosf(fAnglee) * 0.5f;

	////���_���W�̐ݒ�
	//pVtx[4].pos = D3DXVECTOR3(g_PosTitleTutolial.Pos.x - (700 / 2), g_PosTitleTutolial.Pos.y + (300 / 2), 0.0f);//2D��0.0�Œ�
	//pVtx[5].pos = D3DXVECTOR3(g_PosTitleTutolial.Pos.x - (700 / 2), g_PosTitleTutolial.Pos.y - (300 / 2), 0.0f);
	//pVtx[6].pos = D3DXVECTOR3(g_PosTitleTutolial.Pos.x + (1000 / 2), g_PosTitleTutolial.Pos.y + (300 / 2), 0.0f);
	//pVtx[7].pos = D3DXVECTOR3(g_PosTitleTutolial.Pos.x + (1000 / 2), g_PosTitleTutolial.Pos.y - (300 / 2), 0.0f);//2D��0.0�Œ�


	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffTutolial->Unlock();
}

//==================
//�|���S���̕`�揈��
//==================
void DrawTutolial(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTutolial, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCount = 0; nCount < 3; nCount++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTutolial[nCount]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
	}
}
void SetTutolial(int nCount)
{
	TUTOLIAL *pTutolial;
	VERTEX_2D *pVtx;

	pTutolial = &g_Tutolial[0];

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffTutolial->Lock(0, 0, (void**)&pVtx, 0);

	if (nCount == 0)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);//2D��0.0�Œ�
		pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);//2D��0.0�Œ�
	}

	//else if (nCount == 1)
	//{
	//	//���_���W�̐ݒ�
	//	pVtx[4].pos = D3DXVECTOR3(g_PosTitleTutolial.Pos.x - (600 / 2), g_PosTitleTutolial.Pos.y + (500 / 2), 0.0f);//2D��0.0�Œ�
	//	pVtx[5].pos = D3DXVECTOR3(g_PosTitleTutolial.Pos.x - (600 / 2), g_PosTitleTutolial.Pos.y - (500 / 2), 0.0f);
	//	pVtx[6].pos = D3DXVECTOR3(g_PosTitleTutolial.Pos.x + (1000 / 2), g_PosTitleTutolial.Pos.y + (500 / 2), 0.0f);
	//	pVtx[7].pos = D3DXVECTOR3(g_PosTitleTutolial.Pos.x + (1000 / 2), g_PosTitleTutolial.Pos.y - (500 / 2), 0.0f);//2D��0.0�Œ�

	//}

	else if (nCount == 2)
	{
		//���_���W�̐ݒ�
		pVtx[8].pos = D3DXVECTOR3(g_PosEnterTutolial.Pos.x - (100 / 2), g_PosEnterTutolial.Pos.y + (100 / 2), 0.0f);//2D��0.0�Œ�
		pVtx[9].pos = D3DXVECTOR3(g_PosEnterTutolial.Pos.x - (100 / 2), g_PosEnterTutolial.Pos.y - (100 / 2), 0.0f);
		pVtx[10].pos = D3DXVECTOR3(g_PosEnterTutolial.Pos.x + (400 / 2), g_PosEnterTutolial.Pos.y + (100 / 2), 0.0f);
		pVtx[11].pos = D3DXVECTOR3(g_PosEnterTutolial.Pos.x + (400 / 2), g_PosEnterTutolial.Pos.y - (100 / 2), 0.0f);//2D��0.0�Œ�
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffTutolial->Unlock();
}

