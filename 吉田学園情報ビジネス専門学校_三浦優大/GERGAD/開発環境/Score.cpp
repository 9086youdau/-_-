#include "Score.h"
//makuro
#define MAX_TYPE_SCORE (3)//�G�̎�ސ�
#define MAX_SCORE_SIZE (30)

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureScore = NULL;//�e�N�X�`���փ|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_aScore[MAX_SCORE];//�G�̏��
int g_nScore = 0;//�X�R�A

HRESULT InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/number000.png", &g_apTextureScore);

	g_nScore = 0;

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 8,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemy = 0; nCntEnemy < MAX_SCORE; nCntEnemy++)
	{
		g_aScore[nCntEnemy] = D3DXVECTOR3(1390, 100, 0.0f);

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3((g_aScore[nCntEnemy].x - MAX_SCORE_SIZE) + nCntEnemy * 70, g_aScore[nCntEnemy].y + MAX_SCORE_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3((g_aScore[nCntEnemy].x - MAX_SCORE_SIZE) + nCntEnemy * 70, g_aScore[nCntEnemy].y - MAX_SCORE_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3((g_aScore[nCntEnemy].x + MAX_SCORE_SIZE) + nCntEnemy * 70, g_aScore[nCntEnemy].y + MAX_SCORE_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3((g_aScore[nCntEnemy].x + MAX_SCORE_SIZE) + nCntEnemy * 70, g_aScore[nCntEnemy].y - MAX_SCORE_SIZE, 0.0f);

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
	g_pVtxBuffScore->Unlock();

	return S_OK;
}
void UninitScore(void)
{
	//�e�N�X�`���̊J��
	for (int nCount = 0; nCount < MAX_SCORE; nCount++)
	{
		if (g_apTextureScore != NULL)
		{
			g_apTextureScore->Release();
			g_apTextureScore = NULL;
		}
	}

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}
void UpdateScore(void)
{
	VERTEX_2D *pVtx;
	int nNumber[8];
	//���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	nNumber[0] = g_nScore % 100000000 / 10000000;
	nNumber[1] = g_nScore % 10000000 / 1000000;
	nNumber[2] = g_nScore % 1000000 / 100000;
	nNumber[3] = g_nScore % 100000 / 10000;
	nNumber[4] = g_nScore % 10000 / 1000;
	nNumber[5] = g_nScore % 1000 / 100;
	nNumber[6] = g_nScore % 100 / 10;
	nNumber[7] = g_nScore % 10 / 1;

	for (int nCntEnemy = 0; nCntEnemy < MAX_SCORE; nCntEnemy++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3((g_aScore[nCntEnemy].x - MAX_SCORE_SIZE) + nCntEnemy * 60, g_aScore[nCntEnemy].y + MAX_SCORE_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3((g_aScore[nCntEnemy].x - MAX_SCORE_SIZE) + nCntEnemy * 60, g_aScore[nCntEnemy].y - MAX_SCORE_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3((g_aScore[nCntEnemy].x + MAX_SCORE_SIZE) + nCntEnemy * 60, g_aScore[nCntEnemy].y + MAX_SCORE_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3((g_aScore[nCntEnemy].x + MAX_SCORE_SIZE) + nCntEnemy * 60, g_aScore[nCntEnemy].y - MAX_SCORE_SIZE, 0.0f);

		//���_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.1f*nNumber[nCntEnemy], 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f*nNumber[nCntEnemy], 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f*(nNumber[nCntEnemy] + 1), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f*(nNumber[nCntEnemy] + 1), 0.0f);

		pVtx += 4;//4���_���Ƃ��炷

	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffScore->Unlock();
}
//==================
//�|���S���̕`�揈��
//==================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetTexture(0, g_apTextureScore);

	//�|���S���̕`��
	for (int nCutEnemy = 0; nCutEnemy < MAX_SCORE; nCutEnemy++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCutEnemy * 4, 2);
	}
	
}
void AddScore(int nValue)
{
	g_nScore += nValue;
}
void SetScore(void)
{
	g_nScore = 0;
}


