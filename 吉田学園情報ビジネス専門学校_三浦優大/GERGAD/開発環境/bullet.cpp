#include "bullet.h"
#include "Explosion.h"
#include "sound.h"
#include "effect.h"
#include "particle.h"
#include "enemy.h"
#include "Score.h"
#include "Player.h"
#include "fade.h"
#include "Hp.h"


//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexturebullet[3] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet;//���_�|�C���^
BULLET g_aBullet[702];//�e�̏��
D3DXCOLOR g_colorBullet;


HRESULT InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/10.png", &g_pTexturebullet[BULLETTYPE_ENEMY_HOMING]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/10.png", &g_pTexturebullet[BULLETTYPE_ENEMY_HOMING2]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/10.png", &g_pTexturebullet[BULLETTYPE_ENEMY_HOMING3]);

	for (int nCntBullet = 0; nCntBullet < 702; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].col = g_colorBullet;
		g_colorBullet = D3DXCOLOR(0.3f, 1.0f, 0.3f, 1.0f);
		g_aBullet[nCntBullet].nLife = 0;
		g_aBullet[nCntBullet].bUse = false;
		g_aBullet[nCntBullet].nType = BULLETTYPE_ENEMY;
	}

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 702, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffBullet, NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;

	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < 702; nCntBullet++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - MAX_SIZE, g_aBullet[nCntBullet].pos.y + MAX_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - MAX_SIZE, g_aBullet[nCntBullet].pos.y - MAX_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + MAX_SIZE, g_aBullet[nCntBullet].pos.y + MAX_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + MAX_SIZE, g_aBullet[nCntBullet].pos.y - MAX_SIZE, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		////���_�J���[�̐ݒ�
		pVtx[0].col = g_colorBullet;
		pVtx[1].col = g_colorBullet;
		pVtx[2].col = g_colorBullet;
		pVtx[3].col = g_colorBullet;

		//���_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx += 4;//4���_���Ƃ��炷
	}

	g_pVtxBuffBullet->Unlock();
	return  S_OK;
}
void UninitBullet(void)
{
	//�e�N�X�`���̊J��
	for (int nCntBullet = 0; nCntBullet < 3; nCntBullet++)
	{
		if (g_pTexturebullet[nCntBullet] != NULL)
		{
			g_pTexturebullet[nCntBullet]->Release();
			g_pTexturebullet[nCntBullet] = NULL;
		}
	}

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}
void UpdateBullet(void)
{
	BULLET *pBullet;
	ENEMY *pEnemy;
	PLAYER *pPlayer;
	EFFECT *pEffect;
	pBullet = &g_aBullet[0];
	VERTEX_2D *pVtx;
	int nLife = 10;
	

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < 702; nCntBullet++, pBullet++)
	{
		if (pBullet->bUse == true)//�e���g�p���Ă��邩�ǂ���
		{
			if (pBullet->nLife <= 50)
			{
				//�ʒu�X�V
				if (pBullet->nType == BULLETTYPE_ENEMY_HOMING2)
				{
					D3DXVECTOR3 vec;
					float fAngle;
					D3DXVECTOR3 move;
					pPlayer = GetPlayer();

					vec = pPlayer->Pos - pBullet->pos;//���ݒn����ړI�n�ւ̃x�N�g��
					fAngle = atan2f(vec.x, vec.y);//�x�N�g���̊p�x�����߂�
					move.x = sinf(fAngle) * 1.0f;//�ړ��ʂ����߂�
					move.y = cosf(fAngle) * 1.0f;//�ړ��ʂ����߂�

					pBullet->pos += move;

				}
			}
			else
			{
				pBullet->pos += pBullet->move;
			}

		D3DXVECTOR3 vec;
		float fAngle;
		D3DXVECTOR3 move;
		pPlayer = GetPlayer();

		vec = pPlayer->Pos - pBullet->pos;//���ݒn����ړI�n�ւ̃x�N�g��
		fAngle = atan2f(vec.x, vec.y);//�x�N�g���̊p�x�����߂�
		move.x = sinf(fAngle) * 1.0f;//�ړ��ʂ����߂�
		move.y = cosf(fAngle) * 1.0f;//�ړ��ʂ����߂�

		
		if (pBullet->nType == BULLETTYPE_ENEMY_HOMING)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 15, g_aBullet[nCntBullet].pos.y + 15, 0.0f);//2D��0.0�Œ�
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 15, g_aBullet[nCntBullet].pos.y - 15, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 15, g_aBullet[nCntBullet].pos.y + 15, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 15, g_aBullet[nCntBullet].pos.y - 15, 0.0f);

			pVtx[0].col = g_colorBullet = g_colorBullet = D3DXCOLOR(0.3f, 0.3f, 1.0f, 0.3f);
			pVtx[1].col = g_colorBullet = g_colorBullet = D3DXCOLOR(0.3f, 0.3f, 1.0f, 0.3f);
			pVtx[2].col = g_colorBullet = g_colorBullet = D3DXCOLOR(0.3f, 0.3f, 1.0f, 0.3f);
			pVtx[3].col = g_colorBullet = g_colorBullet = D3DXCOLOR(0.3f, 0.3f, 1.0f, 0.3f);

			//�G�t�F�N�g����
			SetEffect(pBullet->pos, nLife, move);
		}

		else if (pBullet->nType == BULLETTYPE_ENEMY_HOMING2)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 35, g_aBullet[nCntBullet].pos.y + 35, 0.0f);//2D��0.0�Œ�
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 35, g_aBullet[nCntBullet].pos.y - 35, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 35, g_aBullet[nCntBullet].pos.y + 35, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 35, g_aBullet[nCntBullet].pos.y - 35, 0.0f);

			pVtx[0].col = g_colorBullet = g_colorBullet = D3DXCOLOR(1.0f, 0.3f, 0.3f, 0.3f);
			pVtx[1].col = g_colorBullet = g_colorBullet = D3DXCOLOR(1.0f, 0.3f, 0.3f, 0.3f);
			pVtx[2].col = g_colorBullet = g_colorBullet = D3DXCOLOR(1.0f, 0.3f, 0.3f, 0.3f);
			pVtx[3].col = g_colorBullet = g_colorBullet = D3DXCOLOR(1.0f, 0.3f, 0.3f, 0.3f);

			//�G�t�F�N�g����
			SetEffect(pBullet->pos, nLife, move);
		}

		else if (pBullet->nType == BULLETTYPE_ENEMY_HOMING3)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 35, g_aBullet[nCntBullet].pos.y + 35, 0.0f);//2D��0.0�Œ�
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 35, g_aBullet[nCntBullet].pos.y - 35, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 35, g_aBullet[nCntBullet].pos.y + 35, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 35, g_aBullet[nCntBullet].pos.y - 35, 0.0f);

			pVtx[0].col = g_colorBullet = g_colorBullet = D3DXCOLOR(0.3f, 0.3f, 1.0f, 0.3f);
			pVtx[1].col = g_colorBullet = g_colorBullet = D3DXCOLOR(0.3f, 0.3f, 1.0f, 0.3f);
			pVtx[2].col = g_colorBullet = g_colorBullet = D3DXCOLOR(0.3f, 0.3f, 1.0f, 0.3f);
			pVtx[3].col = g_colorBullet = g_colorBullet = D3DXCOLOR(0.3f, 0.3f, 1.0f, 0.3f);

			//�G�t�F�N�g����
			SetEffect(pBullet->pos, nLife, move);
		}

			//�����`�F�b�N
			pBullet->nLife--;
			if (pBullet->nLife == 0)
			{
				for (int nCntAppear = 0; nCntAppear < 100; nCntAppear++)
				{
					D3DXVECTOR3 pos;
					int nLife;
					D3DXVECTOR3 move;
					float fAngle;
					pos = pBullet->pos;
					nLife = 10 + rand() % 20;
					fAngle = (float)(rand() % 628 - 314) / 20.0f;
					move.x = sinf(fAngle)*2.5f;
					move.y = cosf(fAngle)*2.5f;
					SetEffect(pos, nLife, move);
					pBullet->bUse = false;
				}
			}

			//��ʊO�`�F�b�N �����G�t�F�N�g
			if (g_aBullet[nCntBullet].pos.y + 20 >= 1030)
			{
				for (int nCntAppear = 0; nCntAppear < 100; nCntAppear++)
				{
					D3DXVECTOR3 pos;
					int nLife;
					D3DXVECTOR3 move;
					float fAngle;
					pos = pBullet->pos;
					nLife = 10 + rand() % 20;
					fAngle = (float)(rand() % 628 - 314) / 100.0f;
					move.x = sinf(fAngle)*2.5f;
					move.y = cosf(fAngle)*2.5f;
					SetEffect(pos, nLife, move);
				}
				pBullet->bUse = false;
			}
			else if (g_aBullet[nCntBullet].pos.y - 20 <= 50)
			{
				for (int nCntAppear = 0; nCntAppear < 100; nCntAppear++)
				{
					D3DXVECTOR3 pos;
					int nLife;
					D3DXVECTOR3 move;
					float fAngle;
					D3DXCOLOR col;
					col = D3DXCOLOR(0.01f, 0.01f, 1.0f, 1.0f);
					pos = pBullet->pos;
					nLife = 10 + rand() % 20;
					fAngle = (float)(rand() % 628 - 314) / 100.0f;
					move.x = sinf(fAngle)*2.5f;
					move.y = cosf(fAngle)*2.5f;
					SetEffect(pos, nLife,move);
				}
				pBullet->bUse = false;
			}

			if (g_aBullet[nCntBullet].pos.x + 20 >= 1220)
			{
				for (int nCntAppear = 0; nCntAppear < 100; nCntAppear++)
				{
					D3DXVECTOR3 pos;
					int nLife;
					D3DXVECTOR3 move;
					float fAngle;
					pos = pBullet->pos;
					nLife = 10 + rand() % 20;
					fAngle = (float)(rand() % 628 - 314) / 100.0f;
					move.x = sinf(fAngle)*2.5f;
					move.y = cosf(fAngle)*2.5f;
					SetEffect(pos, nLife, move);
				}
				pBullet->bUse = false;
			}
			else if (g_aBullet[nCntBullet].pos.x - 20 <= 50)
			{
				for (int nCntAppear = 0; nCntAppear < 100; nCntAppear++)
				{
					D3DXVECTOR3 pos;
					int nLife;
					D3DXVECTOR3 move;
					float fAngle;

					pos = pBullet->pos;
					nLife = 10 + rand() % 20;
					fAngle = (float)(rand() % 628 - 314) / 100.0f;
					move.x = sinf(fAngle)*2.5f;
					move.y = cosf(fAngle)*2.5f;
					SetEffect(pos, nLife, move);
				}
				pBullet->bUse = false;
			}
			
			pEnemy = GetEnemy();
			pPlayer = GetPlayer();
			pEffect = GetEffect();

			//�G�Ƃ̓����蔻��
				if (pBullet->nType == BULLETTYPE_ENEMY_HOMING2)//�G�l�~�[�̒e
				{
					if (pPlayer->bUse == true)
					{
						if (pBullet->pos.x >= pPlayer->Pos.x - MAX_POLYGON_SIZE && pBullet->pos.x <= pPlayer->Pos.x + MAX_POLYGON_SIZE &&
							pBullet->pos.y >= pPlayer->Pos.y - MAX_POLYGON_SIZE && pBullet->pos.y <= pPlayer->Pos.y + MAX_POLYGON_SIZE)
						{
							HitPlayer(1);
							AddHp(1);
							pBullet->bUse = false;
							for (int nCntAppear = 0; nCntAppear < 1; nCntAppear++)
							{
								D3DXVECTOR3 pos;
								int nLife;
								D3DXVECTOR3 move;
								float fAngle;
								pos = pBullet->pos;
								nLife = 10 + rand() % 20;
								fAngle = (float)(rand() % 628 - 314) / 100.0f;
								move.x = sinf(fAngle)*2.5f;
								move.y = cosf(fAngle)*2.5f;
								SetEffect(pos, nLife, move);
							}
						}
					}
				}
				for (int nCntEnemy = 0; nCntEnemy < 702; nCntEnemy++, pEnemy++)
				{
					if (pBullet->nType == BULLETTYPE_ENEMY_HOMING)//�|���S���̒e
					{
						if (pEnemy->bUse == true)
						{
							if (pBullet->pos.x >= pEnemy->Pos.x - MAX_BULLET_SIZE && pBullet->pos.x <= pEnemy->Pos.x + MAX_BULLET_SIZE &&
								pBullet->pos.y >= pEnemy->Pos.y - MAX_BULLET_SIZE && pBullet->pos.y <= pEnemy->Pos.y + MAX_BULLET_SIZE)
							{
								HitEnemy(nCntEnemy, 60);
								pBullet->bUse = false;
							}
						}
					}

				}
		}
	//4���_���Ƃ��炷
				pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffBullet->Unlock();
}

void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	int Count;
	Count = 0;
	BULLET *pBullet;
	pBullet = &g_aBullet[0];

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntBullet = 0; nCntBullet < 702; nCntBullet++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturebullet[pBullet->nType]);
		pDevice->SetTexture(0, g_pTexturebullet[pBullet[nCntBullet].nType]);

		if (g_aBullet[nCntBullet].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, 2);
		}
	}
}
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, D3DXCOLOR col, BULLETTYPE nType)//�e�̐ݒ�
{
	BULLET *pBullet;
	VERTEX_2D *pVtx;

	pBullet = &g_aBullet[0];

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet <702; nCntBullet++, pBullet++)
	{
		if(pBullet->bUse == false)//�e���g�p���Ă��邩�ǂ���
		{
			if (nType == BULLETTYPE_ENEMY_HOMING)
			{
				//�ʒu�ݒ�
				pBullet->pos = pos;

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(pBullet->pos.x - MAX_SIZE, pBullet->pos.y + MAX_SIZE, 0.0f);//2D��0.0�Œ�
				pVtx[1].pos = D3DXVECTOR3(pBullet->pos.x - MAX_SIZE, pBullet->pos.y - MAX_SIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pBullet->pos.x + MAX_SIZE, pBullet->pos.y + MAX_SIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pBullet->pos.x + MAX_SIZE, pBullet->pos.y - MAX_SIZE, 0.0f);

				//�ړ��ʂ�ݒ�
				pBullet->move = move;

				//������ݒ�
				pBullet->nLife = nLife;

				pBullet->nType = nType;

				pBullet->col = col;

				pVtx[0].col = g_colorBullet = g_colorBullet = D3DXCOLOR(1.0f, 1.0f, 0.3f, 0.3f);
				pVtx[1].col = g_colorBullet = g_colorBullet = D3DXCOLOR(1.0f, 1.0f, 0.3f, 0.3f);
				pVtx[2].col = g_colorBullet = g_colorBullet = D3DXCOLOR(1.0f, 1.0f, 0.3f, 0.3f);
				pVtx[3].col = g_colorBullet = g_colorBullet = D3DXCOLOR(1.0f, 1.0f, 0.3f, 0.3f);

				//�e�̎g�p
				pBullet->bUse = true;
				//AddScore(10);
				break;
			}
			else if (nType == BULLETTYPE_ENEMY_HOMING2)
			{
				//�ʒu�ݒ�
				pBullet->pos = pos;

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(pBullet->pos.x - MAX_SIZE, pBullet->pos.y + MAX_SIZE, 0.0f);//2D��0.0�Œ�
				pVtx[1].pos = D3DXVECTOR3(pBullet->pos.x - MAX_SIZE, pBullet->pos.y - MAX_SIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pBullet->pos.x + MAX_SIZE, pBullet->pos.y + MAX_SIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pBullet->pos.x + MAX_SIZE, pBullet->pos.y - MAX_SIZE, 0.0f);

				//�ړ��ʂ�ݒ�
				pBullet->move = move;

				//������ݒ�
				pBullet->nLife = nLife;

				pBullet->nType = nType;

				pBullet->col = col;

				pVtx[0].col = g_colorBullet = g_colorBullet = D3DXCOLOR(1.0f, 0.3f, 1.0f, 1.0f);
				pVtx[1].col = g_colorBullet = g_colorBullet = D3DXCOLOR(1.0f, 0.3f, 1.0f, 1.0f);
				pVtx[2].col = g_colorBullet = g_colorBullet = D3DXCOLOR(1.0f, 0.3f, 1.0f, 1.0f);
				pVtx[3].col = g_colorBullet = g_colorBullet = D3DXCOLOR(1.0f, 0.3f, 1.0f, 1.0f);

				//�e�̎g�p
				pBullet->bUse = true;
				break;
			}
			else if (nType == BULLETTYPE_ENEMY_HOMING3)
			{
				//�ʒu�ݒ�
				pBullet->pos = pos;

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(pBullet->pos.x - MAX_SIZE, pBullet->pos.y + MAX_SIZE, 0.0f);//2D��0.0�Œ�
				pVtx[1].pos = D3DXVECTOR3(pBullet->pos.x - MAX_SIZE, pBullet->pos.y - MAX_SIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pBullet->pos.x + MAX_SIZE, pBullet->pos.y + MAX_SIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pBullet->pos.x + MAX_SIZE, pBullet->pos.y - MAX_SIZE, 0.0f);

				//�ړ��ʂ�ݒ�
				pBullet->move = move;

				//������ݒ�
				pBullet->nLife = nLife;

				pBullet->nType = nType;

				pBullet->col = col;
				pVtx[0].col = g_colorBullet = g_colorBullet = D3DXCOLOR(1.0f, 0.3f, 1.0f, 1.0f);
				pVtx[1].col = g_colorBullet = g_colorBullet = D3DXCOLOR(1.0f, 0.3f, 1.0f, 1.0f);
				pVtx[2].col = g_colorBullet = g_colorBullet = D3DXCOLOR(1.0f, 0.3f, 1.0f, 1.0f);
				pVtx[3].col = g_colorBullet = g_colorBullet = D3DXCOLOR(1.0f, 0.3f, 1.0f, 1.0f);

				//�e�̎g�p
				pBullet->bUse = true;
				break;
			}
		}

		//4���_���Ƃ��炷
		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffBullet->Unlock();
}

