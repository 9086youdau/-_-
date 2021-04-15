//================================================
//
//�G�t�F�N�g����[Player.h]
// Author; miura yuudai
//
//================================================
#include "particle.h"
#include "effect.h"
#include "Block.h"
#include "Player.h"

//�}�N����`
#define MAX_PARTICLE_SIZE (20)//�G�t�F�N�g�̃T�C�Y
#define MAX_PARTICLE (3056)//�z��

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureParticle = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffParticle;//���_�|�C���^
PARTICLE g_aparticle[MAX_PARTICLE];//�e�̏��
D3DXCOLOR g_colorparticle;
D3DXVECTOR3 g_posBase;
D3DXVECTOR3 g_posBase2;
//int nCountParticle;

//====================
//�p�[�e�B�N���̏�����
//====================
HRESULT InitParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect000.jpg", &g_pTextureParticle);

	//������
	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		g_aparticle[nCntParticle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aparticle[nCntParticle].bUse = false;
		g_colorparticle = D3DXCOLOR(1.0f, 0.2f, 0.2f, 0.7f);
		//g_posBase = D3DXVECTOR3(500.0f, 600.0f, 0.0f);
		//g_posBase2 = D3DXVECTOR3(800.0f, 600.0f, 0.0f);
	}

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_PARTICLE, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffParticle, NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aparticle[nCntParticle].pos.x - MAX_PARTICLE_SIZE, g_aparticle[nCntParticle].pos.y + MAX_PARTICLE_SIZE, 0.0f);//2D��0.0�Œ�
		pVtx[1].pos = D3DXVECTOR3(g_aparticle[nCntParticle].pos.x - MAX_PARTICLE_SIZE, g_aparticle[nCntParticle].pos.y - MAX_PARTICLE_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aparticle[nCntParticle].pos.x + MAX_PARTICLE_SIZE, g_aparticle[nCntParticle].pos.y + MAX_PARTICLE_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aparticle[nCntParticle].pos.x + MAX_PARTICLE_SIZE, g_aparticle[nCntParticle].pos.y - MAX_PARTICLE_SIZE, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = g_colorparticle;
		pVtx[1].col = g_colorparticle;
		pVtx[2].col = g_colorparticle;
		pVtx[3].col = g_colorparticle;

		//���_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		 pVtx += 4; //4���_���Ƃ��炷
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffParticle->Unlock();

	return  S_OK;
}

//====================
//�p�[�e�B�N���̏I������
//====================
void UninitParticle(void)
{
	//�e�N�X�`���̊J��
	if (g_pTextureParticle != NULL)
	{
		g_pTextureParticle->Release();
		g_pTextureParticle = NULL;
	}

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffParticle != NULL)
	{
		g_pVtxBuffParticle->Release();
		g_pVtxBuffParticle = NULL;
	}
}

//====================
//�p�[�e�B�N���̍X�V����
//====================
void UpdateParticle(void)
{
	PARTICLE *pParticle;
	pParticle = &g_aparticle[0];
	BLOCK *pBlock;
	pBlock = GetBlock();
	PLAYER *pPlayer;
	pPlayer = GetPlayer();

	VERTEX_2D *pVtx;

	//nCountParticle++;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++, pParticle++)
	{
		if (pParticle->bUse == true)//�p�[�e�B�N�����g�p���Ă��邩�ǂ���
		{

			//�ʒu�̍X�V
			pParticle->pos += pParticle->move;

			//pParticle->move.y += 0.1f;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(pParticle->pos.x - MAX_PARTICLE_SIZE, pParticle->pos.y + MAX_PARTICLE_SIZE, 0.0f);//2D��0.0�Œ�
			pVtx[1].pos = D3DXVECTOR3(pParticle->pos.x - MAX_PARTICLE_SIZE, pParticle->pos.y - MAX_PARTICLE_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(pParticle->pos.x + MAX_PARTICLE_SIZE, pParticle->pos.y + MAX_PARTICLE_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(pParticle->pos.x + MAX_PARTICLE_SIZE, pParticle->pos.y - MAX_PARTICLE_SIZE, 0.0f);

			//���_�J���[�̐ݒ�
			pVtx[0].col = pParticle->color;
			pVtx[1].col = pParticle->color;
			pVtx[2].col = pParticle->color;
			pVtx[3].col = pParticle->color;

			//�����`�F�b�N
			pParticle->nLife--;
			if (pParticle->nLife == 0)//������0�ɂȂ�����
			{
				pParticle->bUse = false;//�g�p���Ȃ�
			}

		}

		//4���_���Ƃ��炷
		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffParticle->Unlock();


		
			//SetEffect(pos2, nLife, 3, move)

			// ���_�o�b�t�@�����b�N
		g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

		pParticle = &g_aparticle[0];

		for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++, pParticle++)
		{
			if (pParticle->bUse == false)//�p�[�e�B�N�����g�p���Ă��邩�ǂ���
			{
				//pParticle->pos = g_posBase;

				//pParticle->fRadius = 1.0f + rand() % 20;

				////���_���W�̐ݒ�
				//pVtx[0].pos = D3DXVECTOR3(pParticle->pos.x - pParticle->fRadius, pParticle->pos.y + pParticle->fRadius, 0.0f);//2D��0.0�Œ�
				//pVtx[1].pos = D3DXVECTOR3(pParticle->pos.x - pParticle->fRadius, pParticle->pos.y - pParticle->fRadius, 0.0f);
				//pVtx[2].pos = D3DXVECTOR3(pParticle->pos.x + pParticle->fRadius, pParticle->pos.y + pParticle->fRadius, 0.0f);
				//pVtx[3].pos = D3DXVECTOR3(pParticle->pos.x + pParticle->fRadius, pParticle->pos.y - pParticle->fRadius, 0.0f);


				//pParticle->color = g_colorparticle;

				////���_�J���[�̐ݒ�
				//pVtx[0].col = pParticle->color;
				//pVtx[1].col = pParticle->color;
				//pVtx[2].col = pParticle->color;
				//pVtx[3].col = pParticle->color;

				//pParticle->nLife = 2 + rand() % 5;

				//float fAngle;

				//fAngle = (float)(nCountParticle) / 100.0f;

				//pParticle->move.x = sinf(fAngle)*40.5f;

				//pParticle->move.y = cosf(fAngle)*40.5f;


				//pParticle->bUse = true;
				//break;

			}
			//4���_���Ƃ��炷
			pVtx += 4;
		}

		//���_�o�b�t�@���A�����b�N
		g_pVtxBuffParticle->Unlock();

}

//====================
//�p�[�e�B�N���̕`�揈��
//====================
void DrawParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�����_�[�X�e�[�g�̐ݒ�(���Z�����j
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffParticle, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureParticle);

	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aparticle[nCntParticle].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntParticle *4, 2);
		}
	}

	//�����_�[�X�e�[�g�̐ݒ�(���ɖ߂��j
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//================
//�p�[�e�B�N���̐ݒ�
//================
void SetParticle(D3DXVECTOR3 pos)
{
	PARTICLE *pParticle;
	VERTEX_2D *pVtx;

	pParticle = &g_aparticle[0];

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++, pParticle++)
	{
		if (pParticle->bUse == false)//�e���g�p���Ă��邩�ǂ���
		{
			//�ʒu�ݒ�
			pParticle->pos = pos;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(pParticle->pos.x - MAX_PARTICLE_SIZE, pParticle->pos.y + MAX_PARTICLE_SIZE, 0.0f);//2D��0.0�Œ�
			pVtx[1].pos = D3DXVECTOR3(pParticle->pos.x - MAX_PARTICLE_SIZE, pParticle->pos.y - MAX_PARTICLE_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(pParticle->pos.x + MAX_PARTICLE_SIZE, pParticle->pos.y + MAX_PARTICLE_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(pParticle->pos.x + MAX_PARTICLE_SIZE, pParticle->pos.y - MAX_PARTICLE_SIZE, 0.0f);

			//�e�̎g�p
			pParticle->bUse = true;
			break;
		}

		//4���_���Ƃ��炷
		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffParticle->Unlock();
}
