//================================================
//
//�G�t�F�N�g����[Player.h]
// Author; miura yuudai
//
//================================================
#include "effect.h"
#include "Player.h"
#include "enemy.h"


//�}�N����`
#define MAX_EFFECT_SIZE (30)//�G�t�F�N�g�̃T�C�Y
#define MAX_EFFECT (3056)//�z��

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureEffect[7] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect;//���_�|�C���^
EFFECT g_aEffect[MAX_EFFECT];//�e�̏��
D3DXCOLOR g_colorEffect;

//==================
//�G�t�F�N�g�̏���������
//==================
HRESULT InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect000.jpg", &g_pTextureEffect[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect000.jpg", &g_pTextureEffect[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect000.jpg", &g_pTextureEffect[2]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/fire.png", &g_pTextureEffect[3]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect000.jpg", &g_pTextureEffect[4]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect000.jpg", &g_pTextureEffect[5]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect000.jpg", &g_pTextureEffect[6]);
	

	//������
	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].col = g_colorEffect;
		g_aEffect[nCntEffect].bUse = false;
		g_colorEffect = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		g_aEffect[nCntEffect].nLife= 0;
	}

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EFFECT, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffEffect, NULL)))
	{
		return E_FAIL;
	}

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

	return  S_OK;
}

//====================
//�G�t�F�N�g�̏I������
//====================
void UninitEffect(void)
{
	for (int nCount = 0; nCount < 7; nCount++)
	{
		//�e�N�X�`���̊J��
		if (g_pTextureEffect[nCount] != NULL)
		{
			g_pTextureEffect[nCount]->Release();
			g_pTextureEffect[nCount] = NULL;
		}
	}
	
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}

//====================
//�G�t�F�N�g�̍X�V����
//====================
void UpdateEffect(void)
{
	EFFECT *pEffect;
	pEffect = &g_aEffect[0];
	VERTEX_2D *pVtx;
	PLAYER *pPlayer;
	pPlayer = GetPlayer();
	ENEMY *pEnemy;
	pEnemy = GetEnemy();

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pEffect++)
	{
		if (pEffect->bUse == true)//�G�t�F�N�g���g�p���Ă��邩�ǂ���
		{
			pEffect->pos += pEffect->move;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(pEffect->pos.x - MAX_EFFECT_SIZE, pEffect->pos.y + MAX_EFFECT_SIZE, 0.0f);//2D��0.0�Œ�
			pVtx[1].pos = D3DXVECTOR3(pEffect->pos.x - MAX_EFFECT_SIZE, pEffect->pos.y - MAX_EFFECT_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(pEffect->pos.x + MAX_EFFECT_SIZE, pEffect->pos.y + MAX_EFFECT_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(pEffect->pos.x + MAX_EFFECT_SIZE, pEffect->pos.y - MAX_EFFECT_SIZE, 0.0f);

			//�����`�F�b�N
			pEffect->nLife--;
			if (pEffect->nLife == 0)//������0�ɂȂ�����
			{
				pEffect->bUse = false;//�g�p���Ȃ�
			}
			if (pEffect->pos.x <= 0)//������0�ɂȂ�����
			{
				pEffect->bUse = false;//�g�p���Ȃ�
			}

			

			if (pEffect->nType == 5)
			{
				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(pEffect->pos.x - 90, pEffect->pos.y + 90, 0.0f);//2D��0.0�Œ�
				pVtx[1].pos = D3DXVECTOR3(pEffect->pos.x - 90, pEffect->pos.y - 90, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pEffect->pos.x + 90, pEffect->pos.y + 90, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pEffect->pos.x + 90, pEffect->pos.y - 90, 0.0f);


			}

			if (pEffect->nType == 6)
			{
				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(pEffect->pos.x - 30, pEffect->pos.y + 30, 0.0f);//2D��0.0�Œ�
				pVtx[1].pos = D3DXVECTOR3(pEffect->pos.x - 30, pEffect->pos.y - 30, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pEffect->pos.x + 30, pEffect->pos.y + 30, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pEffect->pos.x + 30, pEffect->pos.y - 30, 0.0f);

			}

			if (pEffect->nType == 1)
			{
				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(pEffect->pos.x - 50, pEffect->pos.y + 50, 0.0f);//2D��0.0�Œ�
				pVtx[1].pos = D3DXVECTOR3(pEffect->pos.x - 50, pEffect->pos.y - 50, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pEffect->pos.x + 50, pEffect->pos.y + 50, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pEffect->pos.x + 50, pEffect->pos.y - 50, 0.0f);
			}


			//�����蔻��
			if (pEffect->nType == 4)
			{
				if (pEffect->pos.x >= pEnemy->Pos.x - 20 && pEffect->pos.x <= pEnemy->Pos.x + 20 &&
					pEffect->pos.y >= pEnemy->Pos.y - 20 && pEffect->pos.y <= pEnemy->Pos.y + 20)
				{
					pEnemy->bUse = false;
					//�p�[�e�B�N������
					for (int nCntAppear = 0; nCntAppear < 1; nCntAppear++)
					{
						D3DXVECTOR3 pos;
						int nLife;
						D3DXVECTOR3 move;
						float fAngle;

						pos = pEnemy->Pos;//�ʒu
						nLife = 100 + rand() % 200;//�����������_��
						fAngle = (float)(rand() % 628 - 314) / 100.0f;//�����͈̔�
						move.x = sinf(fAngle)*1.5f;//x���̒e�̑��x
						move.y = cosf(fAngle)*1.5f;//y���̒e�̑��x
						SetEffect(pos, nLife, 0, move);//�G�t�F�N�g����
					}
				}
			}
			if (pEffect->nType == 3)
			{
				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(pEffect->pos.x - 40, pEffect->pos.y + 40, 0.0f);//2D��0.0�Œ�
				pVtx[1].pos = D3DXVECTOR3(pEffect->pos.x - 40, pEffect->pos.y - 40, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pEffect->pos.x + 40, pEffect->pos.y + 40, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pEffect->pos.x + 40, pEffect->pos.y - 40, 0.0f);
			}

		}
			//4���_���Ƃ��炷
			pVtx += 4;
	}


	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();
}

//====================
//�G�t�F�N�g�̕`�揈��
//====================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;

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
		//pDevice->SetTexture(0, g_pTextureEffect[pEffect->nType]);

		pDevice->SetTexture(0, g_pTextureEffect[g_aEffect[nCntEffect].nType]);
	
		if (g_aEffect[nCntEffect].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEffect*4, 2);
		}
	}

	//�����_�[�X�e�[�g�̐ݒ�(���ɖ߂��j
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//================
//�G�t�F�N�g�̐ݒ�
//================
void SetEffect(D3DXVECTOR3 pos,int nLife, int nType, D3DXVECTOR3 move)
{
	EFFECT *pEffect;
	VERTEX_2D *pVtx;

	pEffect = &g_aEffect[0];

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pEffect++)
	{
		if (pEffect->bUse == false)//�e���g�p���Ă��邩�ǂ���
		{
			if (nType == 0)
			{
				//�ʒu�ݒ�
				pEffect->pos = pos;

				pEffect->nLife = nLife;

				pEffect->nType = nType;
				
				pEffect->move = move;

				pVtx[0].col = g_colorEffect = g_colorEffect = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f);
				pVtx[1].col = g_colorEffect = g_colorEffect = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f);
				pVtx[2].col = g_colorEffect = g_colorEffect = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f);
				pVtx[3].col = g_colorEffect = g_colorEffect = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f);


				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(pEffect->pos.x - MAX_EFFECT_SIZE, pEffect->pos.y + MAX_EFFECT_SIZE, 0.0f);//2D��0.0�Œ�
				pVtx[1].pos = D3DXVECTOR3(pEffect->pos.x - MAX_EFFECT_SIZE, pEffect->pos.y - MAX_EFFECT_SIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pEffect->pos.x + MAX_EFFECT_SIZE, pEffect->pos.y + MAX_EFFECT_SIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pEffect->pos.x + MAX_EFFECT_SIZE, pEffect->pos.y - MAX_EFFECT_SIZE, 0.0f);

				//�e�̎g�p
				pEffect->bUse = true;
				break;
			}
			else if (nType == 1)
			{
				//�ʒu�ݒ�
				pEffect->pos = pos;

				pEffect->nLife = nLife;


				pEffect->nType = nType;

				pEffect->move = move;


				pVtx[0].col = g_colorEffect  = D3DXCOLOR(0.1f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = g_colorEffect  = D3DXCOLOR(0.1f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = g_colorEffect  = D3DXCOLOR(0.1f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = g_colorEffect  = D3DXCOLOR(0.1f, 1.0f, 1.0f, 1.0f);


				/*float fAngle;
				fAngle = (float)(rand() % 314 - 157) / 100.0f + D3DX_PI*0.5f;*/

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(pEffect->pos.x - MAX_EFFECT_SIZE, pEffect->pos.y + MAX_EFFECT_SIZE, 0.0f);//2D��0.0�Œ�
				pVtx[1].pos = D3DXVECTOR3(pEffect->pos.x - MAX_EFFECT_SIZE, pEffect->pos.y - MAX_EFFECT_SIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pEffect->pos.x + MAX_EFFECT_SIZE, pEffect->pos.y + MAX_EFFECT_SIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pEffect->pos.x + MAX_EFFECT_SIZE, pEffect->pos.y - MAX_EFFECT_SIZE, 0.0f);

				//�e�̎g�p
				pEffect->bUse = true;
				break;
			}
			else if (nType == 2)
			{
				//�ʒu�ݒ�
				pEffect->pos = pos;

				pEffect->nLife = nLife;

				pEffect->nType = nType;

				pEffect->move = move;

				pVtx[0].col = g_colorEffect = g_colorEffect = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f);
				pVtx[1].col = g_colorEffect = g_colorEffect = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f);
				pVtx[2].col = g_colorEffect = g_colorEffect = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f);
				pVtx[3].col = g_colorEffect = g_colorEffect = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f);


				/*float fAngle;
				fAngle = (float)(rand() % 314 - 157) / 100.0f + D3DX_PI*0.5f;*/

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(pEffect->pos.x - MAX_EFFECT_SIZE, pEffect->pos.y + MAX_EFFECT_SIZE, 0.0f);//2D��0.0�Œ�
				pVtx[1].pos = D3DXVECTOR3(pEffect->pos.x - MAX_EFFECT_SIZE, pEffect->pos.y - MAX_EFFECT_SIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pEffect->pos.x + MAX_EFFECT_SIZE, pEffect->pos.y + MAX_EFFECT_SIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pEffect->pos.x + MAX_EFFECT_SIZE, pEffect->pos.y - MAX_EFFECT_SIZE, 0.0f);

				//�e�̎g�p
				pEffect->bUse = true;
				break;
			}
			else if (nType == 3)
			{
				//�ʒu�ݒ�
				pEffect->pos = pos;

				pEffect->nLife = nLife;

				pEffect->nType = nType;

				pEffect->move = move;


				pVtx[0].col = g_colorEffect = g_colorEffect = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f);
				pVtx[1].col = g_colorEffect = g_colorEffect = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f);
				pVtx[2].col = g_colorEffect = g_colorEffect = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f);
				pVtx[3].col = g_colorEffect = g_colorEffect = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f);


				/*float fAngle;
				fAngle = (float)(rand() % 314 - 157) / 100.0f + D3DX_PI*0.5f;*/

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(pEffect->pos.x - MAX_EFFECT_SIZE, pEffect->pos.y + MAX_EFFECT_SIZE, 0.0f);//2D��0.0�Œ�
				pVtx[1].pos = D3DXVECTOR3(pEffect->pos.x - MAX_EFFECT_SIZE, pEffect->pos.y - MAX_EFFECT_SIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pEffect->pos.x + MAX_EFFECT_SIZE, pEffect->pos.y + MAX_EFFECT_SIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pEffect->pos.x + MAX_EFFECT_SIZE, pEffect->pos.y - MAX_EFFECT_SIZE, 0.0f);

				//�e�̎g�p
				pEffect->bUse = true;
				break;
			}
			else if (nType == 4)
			{
				//�ʒu�ݒ�
				pEffect->pos = pos;

				pEffect->nLife = nLife;

				pEffect->nType = nType;

				pEffect->move = move;


				pVtx[0].col = g_colorEffect = g_colorEffect = D3DXCOLOR(0.1f, 1.0f, 0.1f, 1.0f);
				pVtx[1].col = g_colorEffect = g_colorEffect = D3DXCOLOR(0.1f, 1.0f, 0.1f, 1.0f);
				pVtx[2].col = g_colorEffect = g_colorEffect = D3DXCOLOR(0.1f, 1.0f, 0.1f, 1.0f);
				pVtx[3].col = g_colorEffect = g_colorEffect = D3DXCOLOR(0.1f, 1.0f, 0.1f, 1.0f);


				/*float fAngle;
				fAngle = (float)(rand() % 314 - 157) / 100.0f + D3DX_PI*0.5f;*/

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(pEffect->pos.x - MAX_EFFECT_SIZE, pEffect->pos.y + MAX_EFFECT_SIZE, 0.0f);//2D��0.0�Œ�
				pVtx[1].pos = D3DXVECTOR3(pEffect->pos.x - MAX_EFFECT_SIZE, pEffect->pos.y - MAX_EFFECT_SIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pEffect->pos.x + MAX_EFFECT_SIZE, pEffect->pos.y + MAX_EFFECT_SIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pEffect->pos.x + MAX_EFFECT_SIZE, pEffect->pos.y - MAX_EFFECT_SIZE, 0.0f);

				//�e�̎g�p
				pEffect->bUse = true;
				break;
			}
			else if (nType == 5)
			{
				//�ʒu�ݒ�
				pEffect->pos = pos;

				pEffect->nLife = nLife;

				pEffect->nType = nType;

				pEffect->move = move;


				pVtx[0].col = g_colorEffect = g_colorEffect = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f);
				pVtx[1].col = g_colorEffect = g_colorEffect = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f);
				pVtx[2].col = g_colorEffect = g_colorEffect = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f);
				pVtx[3].col = g_colorEffect = g_colorEffect = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f);


				/*float fAngle;
				fAngle = (float)(rand() % 314 - 157) / 100.0f + D3DX_PI*0.5f;*/

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(pEffect->pos.x - MAX_EFFECT_SIZE, pEffect->pos.y + MAX_EFFECT_SIZE, 0.0f);//2D��0.0�Œ�
				pVtx[1].pos = D3DXVECTOR3(pEffect->pos.x - MAX_EFFECT_SIZE, pEffect->pos.y - MAX_EFFECT_SIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pEffect->pos.x + MAX_EFFECT_SIZE, pEffect->pos.y + MAX_EFFECT_SIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pEffect->pos.x + MAX_EFFECT_SIZE, pEffect->pos.y - MAX_EFFECT_SIZE, 0.0f);

				//�e�̎g�p
				pEffect->bUse = true;
				break;
			}
		else if (nType == 6)
		{
			//�ʒu�ݒ�
			pEffect->pos = pos;

			pEffect->nLife = nLife;

			pEffect->nType = nType;

			pEffect->move = move;


			pVtx[0].col = g_colorEffect = g_colorEffect = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f);
			pVtx[1].col = g_colorEffect = g_colorEffect = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f);
			pVtx[2].col = g_colorEffect = g_colorEffect = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f);
			pVtx[3].col = g_colorEffect = g_colorEffect = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f);


			/*float fAngle;
			fAngle = (float)(rand() % 314 - 157) / 100.0f + D3DX_PI*0.5f;*/

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(pEffect->pos.x - MAX_EFFECT_SIZE, pEffect->pos.y + MAX_EFFECT_SIZE, 0.0f);//2D��0.0�Œ�
			pVtx[1].pos = D3DXVECTOR3(pEffect->pos.x - MAX_EFFECT_SIZE, pEffect->pos.y - MAX_EFFECT_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(pEffect->pos.x + MAX_EFFECT_SIZE, pEffect->pos.y + MAX_EFFECT_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(pEffect->pos.x + MAX_EFFECT_SIZE, pEffect->pos.y - MAX_EFFECT_SIZE, 0.0f);

			//�e�̎g�p
			pEffect->bUse = true;
			break;
		}
	}

		//4���_���Ƃ��炷
		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();
}
EFFECT *GetEffect(void)
{
	return &g_aEffect[0];
}
