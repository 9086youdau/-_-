//-----------------------------------------------------------------
//
// ���U���g��� (bg.cpp)
// Author:miura yudai
//
//-----------------------------------------------------------------

//------------------------
//�C���N���[�h�t�@�C��
//------------------------
#include "bg.h"
#include "game.h"
#include "input.h"
#include "fade.h"
#include "cavegame.h"
#include "Player.h"
#include "Block.h"

//-----------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------
#define MAX_PATTERN     (3)										// �A�j���[�V�����p�^�[��No.�̍ő吔
#define TITLELOGO_X		(1000.0f)								// �^�C�g�����S��
#define TITLELOGO_Y		(200.0f)								// �^�C�g�����S�̍���
#define HEIGHT_Y		(500.0f * -1.0f)						// �^�C�g�����S�̏������SY���W
#define PRESSENTER_X	(800.0f)								// �v���X�G���^�[�̕�
#define PRESSENTER_Y	(300.0f)								// �v���X�G���^�[�̍���

//-----------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffbg = NULL;
LPDIRECT3DTEXTURE9 g_pTexturebg[3] = {};
D3DXVECTOR3 g_posbgLogo;						// �^�C�g�����S�̒��S���W
D3DXVECTOR3 g_posPressEnterbg;					// �v���X�G���^�[�̒��S���W
D3DXCOLOR g_bgcolor;
BG  g_abg[256];
float g_nCntbg;
int g_nCntbg2;
float nCounter;

//-----------------------------------------------------------------
// �^�C�g���̏���������
//-----------------------------------------------------------------
HRESULT InitBG(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �ϐ��̎󂯓n��
	pDevice = GetDevice();
	int nCntEnemy = GetGameNumber();
	int nCntEEnemy = GetcaveGameNumber();

	// �ϐ��̏�����
	g_posbgLogo = D3DXVECTOR3(SCREEN_WIDTH / 2, HEIGHT_Y, 0.0f);
	g_posPressEnterbg = D3DXVECTOR3(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 4), 0.0f);
	g_bgcolor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_nCntbg = 0;
	float nCounter = 0.0f;

	//�e�L�X�`���̓ǂݍ���
	if (nCntEnemy == 1)
	{
		D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/stage.png", &g_pTexturebg[1]);
	}

	if (nCntEEnemy == 1)
	{
		D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/840bfa1514e9209cf3a445f6d4502f47_t.jpeg", &g_pTexturebg[1]);
	}

	for (int nCntbg = 0; nCntbg < 256; nCntbg++)
	{
		g_abg[nCntbg].nType = 0;
	}

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_PATTERN, // �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,					// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffbg,
		NULL)))
	{
		return E_FAIL;
	}

	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffbg->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntbg = 0; nCntbg < MAX_PATTERN; nCntbg++)
	{
		// ���_���W�̐ݒ�
		SetVertexBG(nCntbg);

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[�̐ݒ�
		pVtx[0].col = g_bgcolor;
		pVtx[1].col = g_bgcolor;
		pVtx[2].col = g_bgcolor;
		pVtx[3].col = g_bgcolor;

		// �e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		// ���̍X�V
		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffbg->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------
// �^�C�g���̏I������
//-----------------------------------------------------------------
void UninitBG(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffbg != NULL)
	{
		g_pVtxBuffbg->Release();
		g_pVtxBuffbg = NULL;
	}

	// �e�N�X�`���̊J��
	for (int nCntTexture = 0; nCntTexture < 3; nCntTexture++)
	{
		if (g_pTexturebg[nCntTexture] != NULL)
		{
			g_pTexturebg[nCntTexture]->Release();
			g_pTexturebg[nCntTexture] = NULL;
		}
	}
}

//-----------------------------------------------------------------
// �^�C�g���̍X�V����
//-----------------------------------------------------------------
void UpdateBG(void)
{

	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	PLAYER *pPlayer;

	pPlayer = GetPlayer();

	BLOCK *pBlock;

	pBlock = GetBlock();

	//���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	g_pVtxBuffbg->Lock(0, 0, (void**)&pVtx, 0);

	if (GetKeyboardPress(DIK_D) == true)//�E�ɐi��
	{
		nCounter -= pBlock->move.x / 10000;
	}
	if (GetKeyboardPress(DIK_A) == true)//�E�ɐi��
	{
		nCounter -= pBlock->move.x / 10000;
	}
	

	//���_���̐ݒ�
	pVtx[4].tex = D3DXVECTOR2(0.0f + nCounter, 1.0f);
	pVtx[5].tex = D3DXVECTOR2(0.0f + nCounter, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(1.0f + nCounter, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f + nCounter, 0.0f);

	//���_���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f + nCounter, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f + nCounter, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f + nCounter, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f + nCounter, 0.0f);


	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffbg->Unlock();
}

//-----------------------------------------------------------------
// �^�C�g���̕`�揈��
//-----------------------------------------------------------------
void DrawBG(void)
{

	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �ϐ��̎󂯓n��
	pDevice = GetDevice();


	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffbg, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	for (int nCntTexture = 0; nCntTexture < 3; nCntTexture++)
	{
		pDevice->SetTexture(0, g_pTexturebg[nCntTexture]);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTexture * 4, 2);
	}

}

//-----------------------------------------------------------------
// �^�C�g����ʂɓ\��e�N�X�`���̎w��
//-----------------------------------------------------------------
void SetVertexBG(int nCntBG)
{
	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffbg->Lock(0, 0, (void**)&pVtx, 0);

	g_nCntbg2 = nCntBG;

	if (g_nCntbg2 == 0)
	{
		pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
	}

	else if (g_nCntbg2 == 1)
	{
		pVtx[4].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
		pVtx[5].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[6].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		pVtx[7].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffbg->Unlock();
}