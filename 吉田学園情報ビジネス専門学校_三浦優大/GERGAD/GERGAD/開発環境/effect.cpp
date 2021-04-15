//================================================
//
//�G�t�F�N�g����[Effect.cpp]
// Author; miura yuudai
//
//================================================

//================================================
//�w�b�_�[�ǂݍ���
//================================================
#include "effect.h"
#include "Player.h"

//================================================
//�}�N����`
//================================================
#define MAX_EFFECT_SIZE (20)//�G�t�F�N�g�̃T�C�Y
#define MAX_EFFECT (7096)//�G�t�F�N�g�̍ő吔

//================================================
//�O���[�o���ϐ�
//================================================
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;//���_���
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect;//���_�|�C���^
EFFECT g_aEffect[MAX_EFFECT];//�e�̏��
D3DXCOLOR g_colorEffect;//�J���[�ݒ�

//==================================
//�G�t�F�N�g�̏���������
//==================================
HRESULT InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect000.jpg", &g_pTextureEffect);

	//�O���[�o���ϐ�������
	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].col = g_colorEffect;
		g_aEffect[nCntEffect].bUse = false;
		g_colorEffect = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		g_aEffect[nCntEffect].nLife = 0;
	}

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EFFECT, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffEffect, NULL)))
	{
		return E_FAIL;
	}

	//�\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - MAX_EFFECT_SIZE, g_aEffect[nCntEffect].pos.y + MAX_EFFECT_SIZE, 0.0f);//2D��0.0�Œ�
		pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - MAX_EFFECT_SIZE, g_aEffect[nCntEffect].pos.y - MAX_EFFECT_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + MAX_EFFECT_SIZE, g_aEffect[nCntEffect].pos.y + MAX_EFFECT_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + MAX_EFFECT_SIZE, g_aEffect[nCntEffect].pos.y - MAX_EFFECT_SIZE, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = g_colorEffect;
		pVtx[1].col = g_colorEffect;
		pVtx[2].col = g_colorEffect;
		pVtx[3].col = g_colorEffect;

		//���_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		 pVtx += 4; //4���_���Ƃ��炷
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();

	//�Ԃ�l
	return  S_OK;
}

//===========================================
//�G�t�F�N�g�̏I������
//===========================================
void UninitEffect(void)
{
	//�e�N�X�`���̊J��
	if (g_pTextureEffect != NULL)
	{
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}
	
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}

//=====================================
//�G�t�F�N�g�̍X�V����
//=====================================
void UpdateEffect(void)
{
	//�|�C���^�ϐ�
	EFFECT *pEffect;
	pEffect = &g_aEffect[0];

	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pEffect++)
	{
		if (pEffect->bUse == true)//�G�t�F�N�g���g�p���Ă��邩�ǂ���
		{
			//�ړ������̐ݒ�
			pEffect->pos += pEffect->move;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(pEffect->pos.x - MAX_EFFECT_SIZE, pEffect->pos.y + MAX_EFFECT_SIZE, 0.0f);//2D��0.0�Œ�
			pVtx[1].pos = D3DXVECTOR3(pEffect->pos.x - MAX_EFFECT_SIZE, pEffect->pos.y - MAX_EFFECT_SIZE, 0.0f);//2D��0.0�Œ�
			pVtx[2].pos = D3DXVECTOR3(pEffect->pos.x + MAX_EFFECT_SIZE, pEffect->pos.y + MAX_EFFECT_SIZE, 0.0f);//2D��0.0�Œ�
			pVtx[3].pos = D3DXVECTOR3(pEffect->pos.x + MAX_EFFECT_SIZE, pEffect->pos.y - MAX_EFFECT_SIZE, 0.0f);//2D��0.0�Œ�

			//�����`�F�b�N
			pEffect->nLife--;

			if (pEffect->nLife == 0)//������0�ɂȂ�����
			{
				pEffect->bUse = false;//false�ɂ��ď���
			}

		}
			//4���_���Ƃ��炷
			pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();
}

//========================================
//�G�t�F�N�g�̕`�揈��
//========================================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�|�C���^�ϐ�
	EFFECT *pEffect;
	pEffect = &g_aEffect[0];

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�����_�[�X�e�[�g�̐ݒ�(���Z�����j
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureEffect);
	
		//�g���Ă���Ƃ�
		if (g_aEffect[nCntEffect].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEffect*4, 2);
		}
	}

	//�����_�[�X�e�[�g�̐ݒ�(���ɖ߂��j
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//========================================
//�G�t�F�N�g�̐ݒ�
//========================================
void SetEffect(D3DXVECTOR3 pos,int nLife, D3DXVECTOR3 move)
{
	//�|�C���^�ϐ�
	EFFECT *pEffect;
	pEffect = &g_aEffect[0];

	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pEffect++)
	{
		if (pEffect->bUse == false)//�e���g�p���Ă��邩�ǂ���
		{
				//�ʒu�ݒ�
				pEffect->pos = pos;

				//�̗͐ݒ�
				pEffect->nLife = nLife;

				//�ړ��ʐݒ�
				pEffect->move = move;

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(pEffect->pos.x - MAX_EFFECT_SIZE, pEffect->pos.y + MAX_EFFECT_SIZE, 0.0f);//2D��0.0�Œ�
				pVtx[1].pos = D3DXVECTOR3(pEffect->pos.x - MAX_EFFECT_SIZE, pEffect->pos.y - MAX_EFFECT_SIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pEffect->pos.x + MAX_EFFECT_SIZE, pEffect->pos.y + MAX_EFFECT_SIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pEffect->pos.x + MAX_EFFECT_SIZE, pEffect->pos.y - MAX_EFFECT_SIZE, 0.0f);

				//�e�̎g�p
				pEffect->bUse = true;
				break;
		}
			//4���_���Ƃ��炷
			pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();
}
//========================================
//�G�t�F�N�g�̏��
//========================================
EFFECT *GetEffect(void)
{
	return &g_aEffect[0];
}
