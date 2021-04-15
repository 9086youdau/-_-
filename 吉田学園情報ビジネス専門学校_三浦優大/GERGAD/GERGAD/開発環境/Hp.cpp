//================================================
//
//HP����[Hp.cpp]
// Author; miura yuudai
//
//================================================

//================================================
//�w�b�_�[�ǂݍ���
//================================================
#include "Hp.h"

//================================================
//�}�N����`
//================================================
#define MAX_TYPE_HP (3)
#define MAX_HP_SIZE (30)
#define MAX_HP (2)

//==============================
//�O���[�o���ϐ�
//==============================
LPDIRECT3DTEXTURE9 g_apTextureHp = NULL;//�e�N�X�`���փ|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffHp = NULL;//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_aHp[MAX_HP];
int g_nHp;//HP�ݒ�

//=================================
//HP�̏���������
//=================================
HRESULT InitHp(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/number000.png", &g_apTextureHp);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_HP,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffHp,
		NULL)))
	{
		return E_FAIL;
	}

	//�ϐ�������
	g_nHp = 4;//�X�R�A

	//�\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	g_pVtxBuffHp->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntHp = 0; nCntHp < MAX_HP; nCntHp++)
	{
		//�����ʒu
		g_aHp[nCntHp] = D3DXVECTOR3(1800, 400, 0.0f);

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3((g_aHp[nCntHp].x - MAX_HP_SIZE) + nCntHp * 70, g_aHp[nCntHp].y + MAX_HP_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3((g_aHp[nCntHp].x - MAX_HP_SIZE) + nCntHp * 70, g_aHp[nCntHp].y - MAX_HP_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3((g_aHp[nCntHp].x + MAX_HP_SIZE) + nCntHp * 70, g_aHp[nCntHp].y + MAX_HP_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3((g_aHp[nCntHp].x + MAX_HP_SIZE) + nCntHp * 70, g_aHp[nCntHp].y - MAX_HP_SIZE, 0.0f);

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
	g_pVtxBuffHp->Unlock();

	return S_OK;
}
//=================================
//HP�̏I������
//=================================
void UninitHp(void)
{
	//�e�N�X�`���̊J��
	if (g_apTextureHp != NULL)
	{
		g_apTextureHp->Release();
		g_apTextureHp = NULL;
	}

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffHp != NULL)
	{
		g_pVtxBuffHp->Release();
		g_pVtxBuffHp = NULL;
	}
}
//=================================
//HP�̍X�V����
//=================================
void UpdateHp(void)
{
	VERTEX_2D *pVtx;

	int nNumber[1];

	//���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	g_pVtxBuffHp->Lock(0, 0, (void**)&pVtx, 0);

	//HP�̕\��
	nNumber[0] = g_nHp % 10 / 1;

	for (int nCntHp = 0; nCntHp < MAX_HP; nCntHp++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3((g_aHp[nCntHp].x - MAX_HP_SIZE) + nCntHp * 60, g_aHp[nCntHp].y + MAX_HP_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3((g_aHp[nCntHp].x - MAX_HP_SIZE) + nCntHp * 60, g_aHp[nCntHp].y - MAX_HP_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3((g_aHp[nCntHp].x + MAX_HP_SIZE) + nCntHp * 60, g_aHp[nCntHp].y + MAX_HP_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3((g_aHp[nCntHp].x + MAX_HP_SIZE) + nCntHp * 60, g_aHp[nCntHp].y - MAX_HP_SIZE, 0.0f);

		//���_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.1f*nNumber[nCntHp], 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f*nNumber[nCntHp], 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f*(nNumber[nCntHp] + 1), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f*(nNumber[nCntHp] + 1), 0.0f);

		pVtx += 4;//4���_���Ƃ��炷

	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffHp->Unlock();
}
//=================================
//HP�̕`�揈��
//=================================
void DrawHp(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffHp, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_apTextureHp);

	//�|���S���̕`��
	for (int nCntHp = 0; nCntHp < MAX_HP; nCntHp++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntHp * 4, 2);
	}

}
//=================================
//HP�̌v�Z����
//=================================
void AddHp(int nValue)
{
	g_nHp -= nValue;
}
//=================================
//HP�̐ݒ菈��
//=================================
void SetHp(void)
{
	g_nHp = 0;
}