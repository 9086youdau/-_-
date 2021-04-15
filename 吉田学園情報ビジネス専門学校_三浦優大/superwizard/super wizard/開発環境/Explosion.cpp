#include "Explosion.h"
#include "Block.h"
#include "Player.h"
#include "Score.h"
#include "particle.h"
#include "effect.h"
#include "input.h"
#include "bullet.h"

//===========
//�}�N����`
//===========
#define MAX_ITEM (256)

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureItem[5] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem;//���_�|�C���^
ITEM g_aItem[MAX_ITEM];//�e�̏��
D3DXCOLOR g_colorItem;

HRESULT InitItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/577px-FireFlowerMK8.png", &g_pTextureItem[0]);
	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/577px-FireFlowerMK8.png", &g_pTextureItem[1]);
	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/coin000.png", &g_pTextureItem[2]);
	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/�X�^�[.png", &g_pTextureItem[3]);
	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/soad2.png", &g_pTextureItem[4]);


	for (int nCntExplosion = 0; nCntExplosion < MAX_ITEM; nCntExplosion++)
	{
		g_aItem[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntExplosion].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f); 
		g_colorItem = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		g_aItem[nCntExplosion].nType = 0;
		g_aItem[nCntExplosion].bUse = false;
		g_aItem[nCntExplosion].nLife = 0;
		g_aItem[nCntExplosion].g_nCounterAnim = 0;
		g_aItem[nCntExplosion].g_nPatternAnim = 0;
		g_aItem[nCntExplosion].g_nseetAnim = 0;
	}

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEM, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffItem, NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;

	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntExplosion = 0; nCntExplosion < MAX_ITEM; nCntExplosion++)
	{

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntExplosion].pos.x - 60, g_aItem[nCntExplosion].pos.y + 60, 0.0f);//2D��0.0�Œ�
		pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntExplosion].pos.x - 60, g_aItem[nCntExplosion].pos.y - 60, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntExplosion].pos.x + 60, g_aItem[nCntExplosion].pos.y + 60, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntExplosion].pos.x + 60, g_aItem[nCntExplosion].pos.y - 60, 0.0f);


		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = g_colorItem;
		pVtx[1].col = g_colorItem;
		pVtx[2].col = g_colorItem;
		pVtx[3].col = g_colorItem;

		//���_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx += 4;//4���_���Ƃ��炷
	}

	g_pVtxBuffItem->Unlock();

	return  S_OK;
}
void UninitItem(void)
{
	for (int nCntExplosion = 0; nCntExplosion < 5; nCntExplosion++)
	{
		//�e�N�X�`���̊J��
		if (g_pTextureItem[nCntExplosion] != NULL)
		{
			g_pTextureItem[nCntExplosion]->Release();
			g_pTextureItem[nCntExplosion] = NULL;
		}
	}
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
}
void UpdateItem(void)
{
	ITEM *pExplosion;

	pExplosion = &g_aItem[0];

	VERTEX_2D *pVtx;

	BLOCK *pBlock;

	PLAYER *pPlayer;

	pPlayer = GetPlayer();

	pBlock = GetBlock();


	// ���_�o�b�t�@�����b�N
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntExplosion = 0; nCntExplosion < MAX_ITEM; nCntExplosion++, pExplosion++,pBlock++)
	{
		if (pExplosion->bUse == true)//�e���g�p���Ă��邩�ǂ���
		{
			if (pExplosion->nType == 0)
			{
				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(pExplosion->pos.x - 30, pExplosion->pos.y + 30, 0.0f);//2D��0.0�Œ�
				pVtx[1].pos = D3DXVECTOR3(pExplosion->pos.x - 30, pExplosion->pos.y - 30, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pExplosion->pos.x + 30, pExplosion->pos.y + 30, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pExplosion->pos.x + 30, pExplosion->pos.y - 30, 0.0f);

				if (pExplosion->pos.x >= pPlayer->Pos.x - 60 && pExplosion->pos.x <= pPlayer->Pos.x + 60 &&
					pExplosion->pos.y >= pPlayer->Pos.y - 60 && pExplosion->pos.y <= pPlayer->Pos.y + 60)
				{
					//�p�[�e�B�N������
					for (int nCntAppear = 0; nCntAppear < 50; nCntAppear++)
					{
						D3DXVECTOR3 pos;
						int nLife;
						D3DXVECTOR3 move;
						float fAngle;

						pos = pPlayer->Pos;//�ʒu
						nLife = 20 + rand() % 30;//�����������_��
						fAngle = (float)(rand() % 628 - 314) / 100.0f;//�����͈̔�
						move.x = sinf(fAngle)*2.5f;//x���̒e�̑��x
						move.y = cosf(fAngle)*2.5f;//y���̒e�̑��x
						SetEffect(pos, nLife, 0, move);//�G�t�F�N�g����
					}
					HitPlayer(1);
					pPlayer->state = PLAYERSTATE_FREAZ;
					pExplosion->bUse = false;
				}

				pExplosion->move.y += sinf(D3DX_PI*0.5)*1.5f;

				if (pExplosion->pos.y <= 540)
				{
					pExplosion->move.y = 0.0f;
				}
			}

			if (pExplosion->nType == 3)
			{
				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(pExplosion->pos.x - 40, pExplosion->pos.y + 40, 0.0f);//2D��0.0�Œ�
				pVtx[1].pos = D3DXVECTOR3(pExplosion->pos.x - 40, pExplosion->pos.y - 40, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pExplosion->pos.x + 40, pExplosion->pos.y + 40, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pExplosion->pos.x + 40, pExplosion->pos.y - 40, 0.0f);

				if (pExplosion->pos.x >= pPlayer->Pos.x - 60 && pExplosion->pos.x <= pPlayer->Pos.x + 60 &&
					pExplosion->pos.y >= pPlayer->Pos.y - 60 && pExplosion->pos.y <= pPlayer->Pos.y + 60)
				{
					//�p�[�e�B�N������
					for (int nCntAppear = 0; nCntAppear < 50; nCntAppear++)
					{
						D3DXVECTOR3 pos;
						int nLife;
						D3DXVECTOR3 move;
						float fAngle;

						pos = pPlayer->Pos;//�ʒu
						nLife = 20 + rand() % 30;//�����������_��
						fAngle = (float)(rand() % 628 - 314) / 100.0f;//�����͈̔�
						move.x = sinf(fAngle)*2.5f;//x���̒e�̑��x
						move.y = cosf(fAngle)*2.5f;//y���̒e�̑��x
						SetEffect(pos, nLife, 0, move);//�G�t�F�N�g����
					}
					HitPlayer(1);
					pPlayer->state = PLAYERSTATE_STAR;
					pExplosion->bUse = false;
				}
				
				
				pExplosion->move.y += sinf(D3DX_PI*0.5)*1.5f;

				if (pExplosion->pos.y <= 540)
				{
					pExplosion->move.y = 0.0f;
				}

			}

			if (pExplosion->nType == 1)
			{
				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(pExplosion->pos.x - 30, pExplosion->pos.y + 30, 0.0f);//2D��0.0�Œ�
				pVtx[1].pos = D3DXVECTOR3(pExplosion->pos.x - 30, pExplosion->pos.y - 30, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pExplosion->pos.x + 30, pExplosion->pos.y + 30, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pExplosion->pos.x + 30, pExplosion->pos.y - 30, 0.0f);

				if (pExplosion->pos.x >= pPlayer->Pos.x - 60 && pExplosion->pos.x <= pPlayer->Pos.x + 60 &&
					pExplosion->pos.y >= pPlayer->Pos.y - 60 && pExplosion->pos.y <= pPlayer->Pos.y + 60)
				{
					//�p�[�e�B�N������
					for (int nCntAppear = 0; nCntAppear < 50; nCntAppear++)
					{
						D3DXVECTOR3 pos;
						int nLife;
						D3DXVECTOR3 move;
						float fAngle;

						pos = pPlayer->Pos;//�ʒu
						nLife = 20 + rand() % 30;//�����������_��
						fAngle = (float)(rand() % 628 - 314) / 100.0f;//�����͈̔�
						move.x = sinf(fAngle)*2.5f;//x���̒e�̑��x
						move.y = cosf(fAngle)*2.5f;//y���̒e�̑��x
						SetEffect(pos, nLife, 0, move);//�G�t�F�N�g����
					}
					HitPlayer(1);
					pPlayer->state = PLAYERSTATE_FIRE;
					pExplosion->bUse = false;
				}

				pExplosion->move.y += sinf(D3DX_PI*0.5)*1.5f;
				
				if (pExplosion->pos.y <= 540)
				{
					pExplosion->move.y = 0.0f;
				}

			}

			if (pExplosion->nType == 2)
			{
				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(pExplosion->pos.x - 30, pExplosion->pos.y + 50, 0.0f);//2D��0.0�Œ�
				pVtx[1].pos = D3DXVECTOR3(pExplosion->pos.x - 30, pExplosion->pos.y - 50, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pExplosion->pos.x + 30, pExplosion->pos.y + 50, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pExplosion->pos.x + 30, pExplosion->pos.y - 50, 0.0f);

				pExplosion->g_nCounterAnim++;//�A�j���[�V�������v���X����Ă���

				if ((pExplosion->g_nCounterAnim % 7) == 0)//10�Ŋ���؂��
				{
					pExplosion->g_nPatternAnim++;

					pExplosion->g_nseetAnim = (pExplosion->g_nseetAnim + 1) % 8;

					pVtx[0].tex = D3DXVECTOR2(0.0f + 0.25f*pExplosion->g_nseetAnim, 1.0f);
					pVtx[1].tex = D3DXVECTOR2(0.0f + 0.25f*pExplosion->g_nseetAnim, 0.0f);
					pVtx[2].tex = D3DXVECTOR2(0.25f + 0.25f*pExplosion->g_nseetAnim, 1.0f);
					pVtx[3].tex = D3DXVECTOR2(0.25f + 0.25f*pExplosion->g_nseetAnim, 0.0f);
				}

				if (pExplosion->bUse = true)
				{
					if (pExplosion->pos.x >= pPlayer->Pos.x - 50 && pExplosion->pos.x <= pPlayer->Pos.x + 50 &&
						pExplosion->pos.y >= pPlayer->Pos.y - 50 && pExplosion->pos.y <= pPlayer->Pos.y + 50)
					{
						pExplosion->bUse = false;

						//�p�[�e�B�N������
						for (int nCntAppear = 0; nCntAppear < 50; nCntAppear++)
						{
							D3DXVECTOR3 pos;
							int nLife;
							D3DXVECTOR3 move;
							float fAngle;

							pos = pExplosion->pos;//�ʒu
							nLife = 1 + rand() % 30;//�����������_��
							fAngle = (float)(rand() % 628 - 314) / 100.0f;//�����͈̔�
							move.x = sinf(fAngle)*1.5f;//x���̒e�̑��x
							move.y = cosf(fAngle)*1.5f;//y���̒e�̑��x
							SetEffect(pos, nLife, 0, move);//�G�t�F�N�g����
						}

						AddScore(100);
					}
				}
			}

			if (pExplosion->nType == 4)
			{
				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(pExplosion->pos.x - 50, pExplosion->pos.y + 50, 0.0f);//2D��0.0�Œ�
				pVtx[1].pos = D3DXVECTOR3(pExplosion->pos.x - 50, pExplosion->pos.y - 50, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pExplosion->pos.x + 50, pExplosion->pos.y + 50, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pExplosion->pos.x + 50, pExplosion->pos.y - 50, 0.0f);

				//���_�J���[�̐ݒ�
				pVtx[0].col = g_colorItem = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = g_colorItem = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = g_colorItem = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = g_colorItem = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			}

			for (int nCntExplosion = 0; nCntExplosion < MAX_ITEM; nCntExplosion++, pBlock++)
			{
				if (pBlock->Pos.x >= pPlayer->Pos.x - pBlock->fWidth + 30 && pBlock->Pos.x <= pPlayer->Pos.x + pBlock->fWidth + 30 &&
					pBlock->Pos.y >= pPlayer->Pos.y - pBlock->fHeight - 10 && pBlock->Pos.y <= pPlayer->Pos.y + pBlock->fHeight - 10)
				{
					for (int nCntExplosion = 0; nCntExplosion < MAX_ITEM; nCntExplosion++)
					{
						g_aItem[nCntExplosion].move.x += 1.33f;
					}
				}

				else if (pBlock->Pos.x >= pPlayer->Pos.x - pBlock->fWidth - 30 && pBlock->Pos.x <= pPlayer->Pos.x + pBlock->fWidth - 30 &&
						pBlock->Pos.y >= pPlayer->Pos.y - pBlock->fHeight - 10 && pBlock->Pos.y <= pPlayer->Pos.y + pBlock->fHeight - 10)
				{
					for (int nCntExplosion = 0; nCntExplosion < MAX_ITEM; nCntExplosion++)
					{
						g_aItem[nCntExplosion].move.x -= 1.33f;
					}
				}


				if (pPlayer->state == PLAYERSTATE_STAR)
				{
					if (pBlock->Pos.x >= pPlayer->Pos.x - pBlock->fWidth + 30 && pBlock->Pos.x <= pPlayer->Pos.x + pBlock->fWidth + 30 &&
						pBlock->Pos.y >= pPlayer->Pos.y - pBlock->fHeight - 10 && pBlock->Pos.y <= pPlayer->Pos.y + pBlock->fHeight - 10)
					{
						for (int nCntExplosion = 0; nCntExplosion < MAX_ITEM; nCntExplosion++)
						{
							g_aItem[nCntExplosion].move.x += 2.25f;
						}
					}
					else if (pBlock->Pos.x >= pPlayer->Pos.x - pBlock->fWidth - 30 && pBlock->Pos.x <= pPlayer->Pos.x + pBlock->fWidth - 30 &&
							pBlock->Pos.y >= pPlayer->Pos.y - pBlock->fHeight - 10 && pBlock->Pos.y <= pPlayer->Pos.y + pBlock->fHeight - 10)
					{
						for (int nCntExplosion = 0; nCntExplosion < MAX_ITEM; nCntExplosion++)
						{
							g_aItem[nCntExplosion].move.x -= 2.25f;
						}
					}
				}
			}
			
	
		//�ړ��ʂ̌���
		 pExplosion->move.y += (0.0f - pExplosion->move.y) *1.5f;

		 //�ʒu�X�V
		 pExplosion->pos.x += pExplosion->move.x;
		 pExplosion->pos.y += pExplosion->move.y;

		}
		//4���_���Ƃ��炷
		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffItem->Unlock();
}

void DrawItem (void)
{
	LPDIRECT3DDEVICE9 pDevice;

	ITEM *pExplosion;

	pExplosion = &g_aItem[0];

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntExplosion = 0; nCntExplosion < MAX_ITEM; nCntExplosion++,pExplosion++)
	{
		if (pExplosion->bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureItem[pExplosion->nType]);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntExplosion*4, 2);
		}
	}
}
void SetItem(D3DXVECTOR3 pos,int nType, D3DXVECTOR3 move)//�e�̐ݒ�
{
	VERTEX_2D *pVtx;

	ITEM *pExplosion;
	pExplosion = &g_aItem[0];

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntExplosion = 0; nCntExplosion < MAX_ITEM; nCntExplosion++, pExplosion++)
	{
		if (pExplosion->bUse == false)//�e���g�p���Ă��邩�ǂ���
		{
			if (nType == 0)
			{
				//�ʒu�ݒ�
				pExplosion->pos = pos;

				pExplosion->nType = nType;

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(pExplosion->pos.x - 60, pExplosion->pos.y + 60, 0.0f);//2D��0.0�Œ�
				pVtx[1].pos = D3DXVECTOR3(pExplosion->pos.x - 60, pExplosion->pos.y - 60, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pExplosion->pos.x + 60, pExplosion->pos.y + 60, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pExplosion->pos.x + 60, pExplosion->pos.y - 60, 0.0f);

				//���_���̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

				//���_�J���[�̐ݒ�
				pVtx[0].col = g_colorItem = D3DXCOLOR(0.5f, 0.5f, 1.0f, 1.0f);
				pVtx[1].col = g_colorItem = D3DXCOLOR(0.5f, 0.5f, 1.0f, 1.0f);
				pVtx[2].col = g_colorItem = D3DXCOLOR(0.5f, 0.5f, 1.0f, 1.0f);
				pVtx[3].col = g_colorItem = D3DXCOLOR(0.5f, 0.5f, 1.0f, 1.0f);


				//�e�̎g�p
				pExplosion->bUse = true;
				break;
			}

			else if (nType == 1)
			{
				//�ʒu�ݒ�
				pExplosion->pos = pos;

				pExplosion->nType = nType;

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(pExplosion->pos.x - 60, pExplosion->pos.y + 60, 0.0f);//2D��0.0�Œ�
				pVtx[1].pos = D3DXVECTOR3(pExplosion->pos.x - 60, pExplosion->pos.y - 60, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pExplosion->pos.x + 60, pExplosion->pos.y + 60, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pExplosion->pos.x + 60, pExplosion->pos.y - 60, 0.0f);
				
				//���_���̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

				//�e�̎g�p
				pExplosion->bUse = true;
				break;
			}

			else if (nType == 2)
			{
				//�ʒu�ݒ�
				pExplosion->pos = pos;

				pExplosion->nType = nType;

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(pExplosion->pos.x - 60, pExplosion->pos.y + 60, 0.0f);//2D��0.0�Œ�
				pVtx[1].pos = D3DXVECTOR3(pExplosion->pos.x - 60, pExplosion->pos.y - 60, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pExplosion->pos.x + 60, pExplosion->pos.y + 60, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pExplosion->pos.x + 60, pExplosion->pos.y - 60, 0.0f);

				//���_���̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

				//�e�̎g�p
				pExplosion->bUse = true;
				break;
			}
			else if (nType == 3)
			{
				//�ʒu�ݒ�
				pExplosion->pos = pos;

				pExplosion->nType = nType;

				pExplosion->move = move;

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(pExplosion->pos.x - 50, pExplosion->pos.y + 50, 0.0f);//2D��0.0�Œ�
				pVtx[1].pos = D3DXVECTOR3(pExplosion->pos.x - 50, pExplosion->pos.y - 50, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pExplosion->pos.x + 50, pExplosion->pos.y + 50, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pExplosion->pos.x + 50, pExplosion->pos.y - 50, 0.0f);

				//���_���̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

				//�e�̎g�p
				pExplosion->bUse = true;
				break;
			}
			else if (nType == 4)
			{
				//�ʒu�ݒ�
				pExplosion->pos = pos;

				pExplosion->nType = nType;

				pExplosion->move = move;

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(pExplosion->pos.x - 50, pExplosion->pos.y + 50, 0.0f);//2D��0.0�Œ�
				pVtx[1].pos = D3DXVECTOR3(pExplosion->pos.x - 50, pExplosion->pos.y - 50, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pExplosion->pos.x + 50, pExplosion->pos.y + 50, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pExplosion->pos.x + 50, pExplosion->pos.y - 50, 0.0f);

				//���_���̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

				//�e�̎g�p
				pExplosion->bUse = true;
				break;
			}
		}

		//4���_���Ƃ��炷
		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffItem->Unlock();
}
ITEM *GetItem(void)
{
	return &g_aItem[0];
}