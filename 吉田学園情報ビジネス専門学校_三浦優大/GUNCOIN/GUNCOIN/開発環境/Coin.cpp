#include "Coin.h"
#include "fade.h"

//===========
//�}�N����`
//===========
#define MAX_TYPE_COIN (3)//�G�̎�ސ�
#define MAX_COIN_SIZE (30)

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCoin = NULL;//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_aCoin[MAX_COIN];//�G�̏��
COIN g_nCoin;//�X�R�A
int nCoin = 0;

HRESULT InitCoin(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/number000.png", &g_nCoin.g_apTextureCoin);

	//������
	nCoin = 0;
	for (int nCntTimer = 0; nCntTimer < MAX_COIN; nCntTimer++)
	{
		g_aCoin[nCntTimer] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TYPE_COIN,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCoin,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	g_pVtxBuffCoin->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTimer = 0; nCntTimer < MAX_COIN; nCntTimer++)
	{
		g_aCoin[nCntTimer] = D3DXVECTOR3(220, 50, 0.0f);

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3((g_aCoin[nCntTimer].x - MAX_COIN_SIZE) + nCntTimer * 70, g_aCoin[nCntTimer].y + MAX_COIN_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3((g_aCoin[nCntTimer].x - MAX_COIN_SIZE) + nCntTimer * 70, g_aCoin[nCntTimer].y - MAX_COIN_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3((g_aCoin[nCntTimer].x + MAX_COIN_SIZE) + nCntTimer * 70, g_aCoin[nCntTimer].y + MAX_COIN_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3((g_aCoin[nCntTimer].x + MAX_COIN_SIZE) + nCntTimer * 70, g_aCoin[nCntTimer].y - MAX_COIN_SIZE, 0.0f);

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
		pVtx[2].tex = D3DXVECTOR2(0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 0.0f);

		pVtx += 4;//4���_���Ƃ��炷
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffCoin->Unlock();

	return S_OK;
}
void UninitCoin(void)
{
	//�e�N�X�`���̊J��
	if (g_nCoin.g_apTextureCoin != NULL)
	{
		g_nCoin.g_apTextureCoin->Release();
		g_nCoin.g_apTextureCoin = NULL;
	}


	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffCoin != NULL)
	{
		g_pVtxBuffCoin->Release();
		g_pVtxBuffCoin = NULL;
	}
}
void UpdateCoin(void)
{
	VERTEX_2D *pVtx;

	int nNumber[2];

	//���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	g_pVtxBuffCoin->Lock(0, 0, (void**)&pVtx, 0);

	nNumber[0] = nCoin % 100 / 10;
	nNumber[1] = nCoin % 10 / 1;

	for (int nCntTimer = 0; nCntTimer < MAX_COIN; nCntTimer++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3((g_aCoin[nCntTimer].x - MAX_COIN_SIZE) + nCntTimer * 60, g_aCoin[nCntTimer].y + MAX_COIN_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3((g_aCoin[nCntTimer].x - MAX_COIN_SIZE) + nCntTimer * 60, g_aCoin[nCntTimer].y - MAX_COIN_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3((g_aCoin[nCntTimer].x + MAX_COIN_SIZE) + nCntTimer * 60, g_aCoin[nCntTimer].y + MAX_COIN_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3((g_aCoin[nCntTimer].x + MAX_COIN_SIZE) + nCntTimer * 60, g_aCoin[nCntTimer].y - MAX_COIN_SIZE, 0.0f);

		//���_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.1f*nNumber[nCntTimer], 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f*nNumber[nCntTimer], 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f*(nNumber[nCntTimer] + 1), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f*(nNumber[nCntTimer] + 1), 0.0f);
		pVtx += 4;//4���_���Ƃ��炷


	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffCoin->Unlock();
}
//==================
//�|���S���̕`�揈��
//==================
void DrawCoin(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffCoin, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetTexture(0, g_nCoin.g_apTextureCoin);

	//�|���S���̕`��
	for (int nCntTimer = 0; nCntTimer < MAX_COIN; nCntTimer++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTimer * 4, 2);
	}

}
void AddCoin(int nValue)
{
	nCoin += nValue;
}
COIN *GetCoin(void)
{
	return &g_nCoin;
}