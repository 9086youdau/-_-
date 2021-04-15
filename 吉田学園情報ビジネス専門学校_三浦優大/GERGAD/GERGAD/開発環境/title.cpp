//================================================
//
//�^�C�g������[title.cpp]
// Author; miura yuudai
//
//================================================

//================================================
//�w�b�_�[�ǂݍ���
//================================================
#include "title.h"
#include "fade.h"
#include "input.h"

//==================================
//�O���[�o���ϐ�
//==================================
LPDIRECT3DTEXTURE9 g_pTextureTitle[3] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;//���_���
TITLE g_Title[3];
D3DXCOLOR g_colorTitle;
D3DXCOLOR g_colorTitlelogo;
TITLE g_PosTitle;
TITLE g_PosEnter;
TITLETYPE g_cnt;
int g_nCntTitle;//�J�E���g�v�Z


//============================================
//�^�C�g���̏���������
//============================================
HRESULT InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();


	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ranking.png", &g_pTextureTitle[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/title.png", &g_pTextureTitle[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/press_enter.png", &g_pTextureTitle[2]);

	for (int nCount = 0; nCount < 3; nCount++)
	{
		g_PosTitle.Pos = D3DXVECTOR3(850.0f, 350.0f, 0.0f);
		g_PosEnter.Pos = D3DXVECTOR3(850.0f, 800.0f, 0.0f);
		g_Title[nCount].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_colorTitle = D3DXCOLOR(0.5f, 1.0f, 1.0f, 1.0f);
		g_colorTitlelogo = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Title[nCount].nType = 0;
		g_Title[nCount].bUse = false;
	}

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 3,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCounter = 0; nCounter < 3; nCounter++)
	{
		//���_���W�̐ݒ�
		SetTitle(nCounter);

        //rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = g_colorTitle;
		pVtx[1].col = g_colorTitle;
		pVtx[2].col = g_colorTitle;
		pVtx[3].col = g_colorTitle;

		//���_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);


		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffTitle->Unlock();

	return S_OK;
}
//============================================
//�^�C�g���̏I������
//============================================
void UninitTitle(void)
{
	//�e�N�X�`���̊J��
	for (int nCount = 0; nCount < 3; nCount++)
	{
		if (g_pTextureTitle[nCount] != NULL)
		{
			g_pTextureTitle[nCount]->Release();
			g_pTextureTitle[nCount] = NULL;
		}
	}

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}

}
//============================================
//�^�C�g���̍X�V����
//============================================
void UpdateTitle(void)
{
	VERTEX_2D *pVtx;

	g_nCntTitle++;

	//���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);


	if (GetKeyboardPress(DIK_RETURN) == true)
	{
		SetFade(FADE_OUT, MODE_TUTORIAL);
	}

	if (g_nCntTitle % 60 == 0)//�Ԋu
	{
		g_colorTitlelogo.a = 0.0f;
	}

	else if (g_nCntTitle % 30 == 0 && g_nCntTitle % 60)//�Ԋu
	{
		g_colorTitlelogo.a = 1.0f;
	}

	float fAnglee;
	fAnglee = (float)(rand() % 628 - 314) / 100.0f;

	g_PosTitle.Pos.x += sinf(fAnglee) * 0.5f;
	g_PosTitle.Pos.y += cosf(fAnglee) * 0.5f;

	//���_���W�̐ݒ�
	pVtx[4].pos = D3DXVECTOR3(g_PosTitle.Pos.x - (900 / 2), g_PosTitle.Pos.y + (300 / 2), 0.0f);//2D��0.0�Œ�
	pVtx[5].pos = D3DXVECTOR3(g_PosTitle.Pos.x - (900 / 2), g_PosTitle.Pos.y - (300 / 2), 0.0f);
	pVtx[6].pos = D3DXVECTOR3(g_PosTitle.Pos.x + (1200 / 2), g_PosTitle.Pos.y + (300 / 2), 0.0f);
	pVtx[7].pos = D3DXVECTOR3(g_PosTitle.Pos.x + (1200 / 2), g_PosTitle.Pos.y - (300 / 2), 0.0f);//2D��0.0�Œ�

	//���_���W�̐ݒ�
	pVtx[8].col = g_colorTitlelogo;//2D��0.0�Œ�
	pVtx[9].col = g_colorTitlelogo;
	pVtx[10].col = g_colorTitlelogo;
	pVtx[11].col = g_colorTitlelogo;//2D��0.0�Œ�

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffTitle->Unlock();
}

//============================================
//�^�C�g���̕`�揈��
//============================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (int nCount = 0; nCount < 3; nCount++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTitle[nCount]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
	}
}
//============================================
//�^�C�g���̐ݒ菈��
//============================================
void SetTitle(int nCount)
{
	TITLE *pTitle;
	VERTEX_2D *pVtx;

	pTitle = &g_Title[0];

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

		if (nCount == 0)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);//2D��0.0�Œ�
			pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);//2D��0.0�Œ�
		}

		else if (nCount == 1)
		{
			//���_���W�̐ݒ�
			pVtx[4].pos = D3DXVECTOR3(g_PosTitle.Pos.x - (1300 / 2), g_PosTitle.Pos.y + (500 / 2), 0.0f);//2D��0.0�Œ�
			pVtx[5].pos = D3DXVECTOR3(g_PosTitle.Pos.x - (1300 / 2), g_PosTitle.Pos.y - (500 / 2), 0.0f);
			pVtx[6].pos = D3DXVECTOR3(g_PosTitle.Pos.x + (1600 / 2), g_PosTitle.Pos.y + (500 / 2), 0.0f);
			pVtx[7].pos = D3DXVECTOR3(g_PosTitle.Pos.x + (1600 / 2), g_PosTitle.Pos.y - (500 / 2), 0.0f);//2D��0.0�Œ�

		}

		else if (nCount == 2)
		{
			//���_���W�̐ݒ�
			pVtx[8].pos = D3DXVECTOR3(g_PosEnter.Pos.x - (300 / 2), g_PosEnter.Pos.y + (200 / 2), 0.0f);//2D��0.0�Œ�
			pVtx[9].pos = D3DXVECTOR3(g_PosEnter.Pos.x - (300 / 2), g_PosEnter.Pos.y - (200 / 2), 0.0f);
			pVtx[10].pos = D3DXVECTOR3(g_PosEnter.Pos.x + (600 / 2), g_PosEnter.Pos.y + (200 / 2), 0.0f);
			pVtx[11].pos = D3DXVECTOR3(g_PosEnter.Pos.x + (600 / 2), g_PosEnter.Pos.y - (200 / 2), 0.0f);//2D��0.0�Œ�
		}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffTitle->Unlock();
}
