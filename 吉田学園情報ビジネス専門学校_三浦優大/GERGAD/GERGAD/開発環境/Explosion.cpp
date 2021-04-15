//================================================
//
//�����A�j���[�V��������[Explosion.cpp]
// Author; miura yuudai
//
//================================================

//================================================
//�w�b�_�[�ǂݍ���
//================================================
#include "Explosion.h"

//================================================
//�}�N����`
//================================================
#define MAX_EXPLOSION_SIZE (60)
#define MAXEXPLOSION (256)

//================================================
//�O���[�o���ϐ�
//================================================
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;//���_���
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion;//���_�|�C���^
EXPLOSION g_aExplosion[MAXEXPLOSION];//�e�̏��

//=======================================
//�����A�j���[�V�����̏���������
//=======================================
HRESULT InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/explosion000.png", &g_pTextureExplosion);

	for (int nCntExplosion = 0; nCntExplosion < MAXEXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
		g_aExplosion[nCntExplosion].bUse = false;
	}

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAXEXPLOSION, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffExplosion, NULL)))
	{
		return E_FAIL;
	}

	//�\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N����
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntExplosion = 0; nCntExplosion < MAXEXPLOSION; nCntExplosion++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - MAX_EXPLOSION_SIZE, g_aExplosion[nCntExplosion].pos.y + MAX_EXPLOSION_SIZE, 0.0f);//2D��0.0�Œ�
		pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - MAX_EXPLOSION_SIZE, g_aExplosion[nCntExplosion].pos.y - MAX_EXPLOSION_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + MAX_EXPLOSION_SIZE, g_aExplosion[nCntExplosion].pos.y + MAX_EXPLOSION_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + MAX_EXPLOSION_SIZE, g_aExplosion[nCntExplosion].pos.y - MAX_EXPLOSION_SIZE, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = g_aExplosion[nCntExplosion].col;
		pVtx[1].col = g_aExplosion[nCntExplosion].col;
		pVtx[2].col = g_aExplosion[nCntExplosion].col;
		pVtx[3].col = g_aExplosion[nCntExplosion].col;

		//���_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.125f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f, 0.0f);

		pVtx += 4;//4���_���Ƃ��炷
	}

	//���_�����A�����b�N����
	g_pVtxBuffExplosion->Unlock();

	//�Ԃ�l
	return  S_OK;
}
//=======================================
//�����A�j���[�V�����̏I������
//=======================================
void UninitExplosion(void)
{
	//�e�N�X�`���̊J��
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}
//=======================================
//�����A�j���[�V�����̍X�V����
//=======================================
void UpdateExplosion(void)
{
	//�|�C���^�ϐ�
	EXPLOSION *pExplosion;
	pExplosion = &g_aExplosion[0];

	//�\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntExplosion = 0; nCntExplosion < MAXEXPLOSION; nCntExplosion++, pExplosion++)
	{
		if (pExplosion->bUse == true)//�A�j���[�V�������g�p���Ă��邩�ǂ���
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - MAX_EXPLOSION_SIZE, g_aExplosion[nCntExplosion].pos.y + MAX_EXPLOSION_SIZE, 0.0f);//2D��0.0�Œ�
			pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - MAX_EXPLOSION_SIZE, g_aExplosion[nCntExplosion].pos.y - MAX_EXPLOSION_SIZE, 0.0f);//2D��0.0�Œ�
			pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + MAX_EXPLOSION_SIZE, g_aExplosion[nCntExplosion].pos.y + MAX_EXPLOSION_SIZE, 0.0f);//2D��0.0�Œ�
			pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + MAX_EXPLOSION_SIZE, g_aExplosion[nCntExplosion].pos.y - MAX_EXPLOSION_SIZE, 0.0f);//2D��0.0�Œ�

			//�A�j���[�V��������
			g_aExplosion[nCntExplosion].g_nCounterAnim++;
			if ((g_aExplosion[nCntExplosion].g_nCounterAnim % 3) == 0)
			{
				g_aExplosion[nCntExplosion].g_nPatternAnim++;
				
				g_aExplosion[nCntExplosion].g_nseetAnim = (g_aExplosion[nCntExplosion].g_nseetAnim + 1) % 10;

				pVtx[0].tex = D3DXVECTOR2(0.0f + 0.125f*g_aExplosion[nCntExplosion].g_nseetAnim, 1.0f);
				pVtx[1].tex = D3DXVECTOR2(0.0f + 0.125f*g_aExplosion[nCntExplosion].g_nseetAnim, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.125f + 0.125f*g_aExplosion[nCntExplosion].g_nseetAnim, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.125f + 0.125f*g_aExplosion[nCntExplosion].g_nseetAnim, 0.0f);
				if (g_aExplosion[nCntExplosion].g_nPatternAnim > 4)
				{
					pExplosion->bUse = false;
					g_aExplosion[nCntExplosion].g_nPatternAnim = 0;//������
					g_aExplosion[nCntExplosion].g_nCounterAnim = 0;//������
				}
			}
			
		}
		//4���_���Ƃ��炷
		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffExplosion->Unlock();
}

//=======================================
//�����A�j���[�V�����̕`�揈��
//=======================================
void DrawExplosion (void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureExplosion);

	for (int nCntExplosion = 0; nCntExplosion < MAXEXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)//�g���Ă��邩
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntExplosion * 4, 2);
		}
	}
}
//=======================================
//�����A�j���[�V�����̐ݒ菈��
//=======================================
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	//�|�C���^�ϐ�
	EXPLOSION *pBullet;
	pBullet = &g_aExplosion[0];

	//�\���̂̃|�C���^
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntExplosion = 0; nCntExplosion < MAXEXPLOSION; nCntExplosion++, pBullet++)
	{
		if (pBullet->bUse == false)//�e���g�p���Ă��邩�ǂ���
		{
			//�ʒu�ݒ�
			g_aExplosion[nCntExplosion].pos = pos;

			//�J���[�ݒ�
			g_aExplosion[nCntExplosion].col = col;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - MAX_EXPLOSION_SIZE, g_aExplosion[nCntExplosion].pos.y + MAX_EXPLOSION_SIZE, 0.0f);//2D��0.0�Œ�
			pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - MAX_EXPLOSION_SIZE, g_aExplosion[nCntExplosion].pos.y - MAX_EXPLOSION_SIZE, 0.0f);//2D��0.0�Œ�
			pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + MAX_EXPLOSION_SIZE, g_aExplosion[nCntExplosion].pos.y + MAX_EXPLOSION_SIZE, 0.0f);//2D��0.0�Œ�
			pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + MAX_EXPLOSION_SIZE, g_aExplosion[nCntExplosion].pos.y - MAX_EXPLOSION_SIZE, 0.0f);//2D��0.0�Œ�

			//�e�̎g�p
			pBullet->bUse = true;
			break;
		}

		//4���_���Ƃ��炷
		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffExplosion->Unlock();
}