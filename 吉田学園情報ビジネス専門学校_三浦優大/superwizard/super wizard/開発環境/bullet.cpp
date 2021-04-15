#include "bullet.h"
#include "effect.h"
#include "Player.h"
#include "enemy.h"
#include "fade.h"


//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexturebullet[5] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet;//���_�|�C���^
BULLET g_aBullet[526];//�e�̏��
D3DXCOLOR g_colorBullet;
int nCountBullet;


HRESULT InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/fire000.png", &g_pTexturebullet[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/fire000.png", &g_pTexturebullet[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/fire000.png", &g_pTexturebullet[2]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/�n���}�[.png", &g_pTexturebullet[3]); 
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/fire000.png", &g_pTexturebullet[4]);


	for (int nCntBullet = 0; nCntBullet < 526; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_colorBullet = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		g_aBullet[nCntBullet].nLife = 0;
		g_aBullet[nCntBullet].bUse = false;
		g_aBullet[nCntBullet].nType = 0;
	}

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 526, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffBullet, NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < 526; nCntBullet++)
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
	for (int nCntBullet = 0; nCntBullet < 5; nCntBullet++)
	{
		//�e�N�X�`���̊J��
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
	pBullet = &g_aBullet[0];
	PLAYER *pPlayer;
	pPlayer = GetPlayer();
	ENEMY *pEnemy;
	pEnemy = GetEnemy();

	VERTEX_2D *pVtx;
	nCountBullet++;
	

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < 256; nCntBullet++, pBullet++)
	{
		if (pBullet->bUse == true)//�e���g�p���Ă��邩�ǂ���
		{
			pBullet->pos.x += pBullet->move.x;
			pBullet->pos.y += pBullet->move.y;

			if (pBullet->nType == 0)
			{
				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - MAX_SIZE, g_aBullet[nCntBullet].pos.y + MAX_SIZE, 0.0f);//2D��0.0�Œ�
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - MAX_SIZE, g_aBullet[nCntBullet].pos.y - MAX_SIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + MAX_SIZE, g_aBullet[nCntBullet].pos.y + MAX_SIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + MAX_SIZE, g_aBullet[nCntBullet].pos.y - MAX_SIZE, 0.0f);

				pVtx[0].col = g_colorBullet = g_colorBullet = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[1].col = g_colorBullet = g_colorBullet = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[2].col = g_colorBullet = g_colorBullet = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[3].col = g_colorBullet = g_colorBullet = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

				int nLife = 20;
				D3DXVECTOR3 move;
				float fAngle;

				fAngle = (float)(rand() % 628 - 314) / 100.0f;//�e�͈̔�
				move.x = sinf(fAngle)*5.0f;//�e�̈ړ���
				move.y = cosf(fAngle)*5.0f;//�e�̈ړ���

				SetEffect(pBullet->pos, nLife, 5, move);

			}

			else if (pBullet->nType == 1)
			{
				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 40, g_aBullet[nCntBullet].pos.y + 40, 0.0f);//2D��0.0�Œ�
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 40, g_aBullet[nCntBullet].pos.y - 40, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 40, g_aBullet[nCntBullet].pos.y + 40, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 40, g_aBullet[nCntBullet].pos.y - 40, 0.0f);

				pVtx[0].col = g_colorBullet = g_colorBullet = D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.2f);
				pVtx[1].col = g_colorBullet = g_colorBullet = D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.2f);
				pVtx[2].col = g_colorBullet = g_colorBullet = D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.2f);
				pVtx[3].col = g_colorBullet = g_colorBullet = D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.2f);

				int nLife = 20;
				D3DXVECTOR3 move;
				float fAngle;

				fAngle = (float)(rand() % 628 - 314) / 100.0f;//�e�͈̔�
				move.x = sinf(fAngle)*10.0f;//�e�̈ړ���
				move.y = cosf(fAngle)*10.0f;//�e�̈ړ���

				SetEffect(pBullet->pos, nLife, 1, move);
			}

			else if (pBullet->nType == 2)
			{
				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - MAX_SIZE, g_aBullet[nCntBullet].pos.y + MAX_SIZE, 0.0f);//2D��0.0�Œ�
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - MAX_SIZE, g_aBullet[nCntBullet].pos.y - MAX_SIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + MAX_SIZE, g_aBullet[nCntBullet].pos.y + MAX_SIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + MAX_SIZE, g_aBullet[nCntBullet].pos.y - MAX_SIZE, 0.0f);

				pVtx[0].col = g_colorBullet = g_colorBullet = D3DXCOLOR(0.2f, 1.0f, 0.2f, 0.2f);
				pVtx[1].col = g_colorBullet = g_colorBullet = D3DXCOLOR(0.2f, 1.0f, 0.2f, 0.2f);
				pVtx[2].col = g_colorBullet = g_colorBullet = D3DXCOLOR(0.2f, 1.0f, 0.2f, 0.2f);
				pVtx[3].col = g_colorBullet = g_colorBullet = D3DXCOLOR(0.2f, 1.0f, 0.2f, 0.2f);

				for (int nCntParticle = 0; nCntParticle < 10; nCntParticle++)
				{
					int nLife = 5;
					D3DXVECTOR3 move;
					float fAngle;

					fAngle = (float)(rand() % 628 - 314) / 100.0f;//�e�͈̔�
					move.x = sinf(fAngle)*10.0f;//�e�̈ړ���
					move.y = cosf(fAngle)*10.0f;//�e�̈ړ���

					SetEffect(pBullet->pos, nLife, 4, move);
				}
			}
			else if (pBullet->nType == 3)
			{
				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 55, g_aBullet[nCntBullet].pos.y + 55, 0.0f);//2D��0.0�Œ�
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 55, g_aBullet[nCntBullet].pos.y - 55, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 55, g_aBullet[nCntBullet].pos.y + 55, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 55, g_aBullet[nCntBullet].pos.y - 55, 0.0f);

				pVtx[0].col = g_colorBullet = g_colorBullet = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = g_colorBullet = g_colorBullet = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = g_colorBullet = g_colorBullet = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = g_colorBullet = g_colorBullet = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				if (pBullet->pos.x >= pPlayer->Pos.x - 30 && pBullet->pos.x <= pPlayer->Pos.x + 30 &&
					pBullet->pos.y >= pPlayer->Pos.y - 30 && pBullet->pos.y <= pPlayer->Pos.y + 30)
				{
					pPlayer->bUse = false;
					//�p�[�e�B�N������
					for (int nCntAppear = 0; nCntAppear < 10; nCntAppear++)
					{
						D3DXVECTOR3 pos;
						int nLife;
						D3DXVECTOR3 move;
						float fAngle;

						pos = pPlayer->Pos;//�ʒu
						nLife = 100 + rand() % 200;//�����������_��
						fAngle = (float)(rand() % 628 - 314) / 100.0f;//�����͈̔�
						move.x = sinf(fAngle)*1.5f;//x���̒e�̑��x
						move.y = cosf(fAngle)*1.5f;//y���̒e�̑��x
						SetEffect(pos, nLife, 0, move);//�G�t�F�N�g����
					}
					SetFade(FADE_OUT, MODE_RESULT);
				}
			}
			else if (pBullet->nType == 4)
			{
				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 30, g_aBullet[nCntBullet].pos.y + 30, 0.0f);//2D��0.0�Œ�
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 30, g_aBullet[nCntBullet].pos.y - 30, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 30, g_aBullet[nCntBullet].pos.y + 30, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 30, g_aBullet[nCntBullet].pos.y - 30, 0.0f);

				pVtx[0].col = g_colorBullet = g_colorBullet = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
				pVtx[1].col = g_colorBullet = g_colorBullet = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
				pVtx[2].col = g_colorBullet = g_colorBullet = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
				pVtx[3].col = g_colorBullet = g_colorBullet = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);

				int nLife = 20;
				D3DXVECTOR3 move;
				float fAngle;

				fAngle = (float)(rand() % 628 - 314) / 100.0f;//�e�͈̔�
				move.x = sinf(fAngle)*5.0f;//�e�̈ړ���
				move.y = cosf(fAngle)*5.0f;//�e�̈ړ���

				SetEffect(pBullet->pos, nLife, 6, pBullet->move);

				//�G�ƒe�̓����蔻��
				for (int nCntExplosion = 0; nCntExplosion < 256; nCntExplosion++, pEnemy++)
				{
					if (pEnemy->Pos.x >= pBullet->pos.x + 30 && pEnemy->Pos.x <= pBullet->pos.x + 30 &&
						pEnemy->Pos.y >= pBullet->pos.y - 30 && pEnemy->Pos.y <= pBullet->pos.y - 30)
					{
						pEnemy->bUse = false;
					}
				}
			}



			//�u���X����
			if (pBullet->nType == 3)
			{
				pBullet->move.y += 0.75f;
			}


			//�����`�F�b�N
			pBullet->nLife--;
			if (pBullet->nLife == 0)
			{
				pBullet->bUse = false;
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

	for (int nCntBullet = 0; nCntBullet < 526; nCntBullet++,pBullet++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturebullet[pBullet->nType]);

		if (g_aBullet[nCntBullet].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, 2);
		}
	}
}
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife,D3DXCOLOR col, int nType)//�e�̐ݒ�
{
	BULLET *pBullet;
	VERTEX_2D *pVtx;

	pBullet = &g_aBullet[0];
	
	// ���_�o�b�t�@�����b�N
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet <256; nCntBullet++, pBullet++)
	{
		if(pBullet->bUse == false)//�e���g�p���Ă��邩�ǂ���
		{
			if (nType == 0)
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

				pVtx[0].col = g_colorBullet = g_colorBullet = D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f);
				pVtx[1].col = g_colorBullet = g_colorBullet = D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f);
				pVtx[2].col = g_colorBullet = g_colorBullet = D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f);
				pVtx[3].col = g_colorBullet = g_colorBullet = D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f);

				//�e�̎g�p
				pBullet->bUse = true;
				break;
			}
			else if (nType == 1)
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

				pVtx[0].col = g_colorBullet = g_colorBullet = D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f);
				pVtx[1].col = g_colorBullet = g_colorBullet = D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f);
				pVtx[2].col = g_colorBullet = g_colorBullet = D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f);
				pVtx[3].col = g_colorBullet = g_colorBullet = D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f);

				//�e�̎g�p
				pBullet->bUse = true;
				break;
			}
			else if (nType == 2)
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

				pVtx[0].col = g_colorBullet = g_colorBullet = D3DXCOLOR(1.0f, 1.0f, 0.2f, 1.0f);
				pVtx[1].col = g_colorBullet = g_colorBullet = D3DXCOLOR(1.0f, 1.0f, 0.2f, 1.0f);
				pVtx[2].col = g_colorBullet = g_colorBullet = D3DXCOLOR(1.0f, 1.0f, 0.2f, 1.0f);
				pVtx[3].col = g_colorBullet = g_colorBullet = D3DXCOLOR(1.0f, 1.0f, 0.2f, 1.0f);

				//�e�̎g�p
				pBullet->bUse = true;
				break;
			}
			else if (nType == 3)
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

				pVtx[0].col = g_colorBullet = g_colorBullet = D3DXCOLOR(1.0f, 1.0f, 0.2f, 1.0f);
				pVtx[1].col = g_colorBullet = g_colorBullet = D3DXCOLOR(1.0f, 1.0f, 0.2f, 1.0f);
				pVtx[2].col = g_colorBullet = g_colorBullet = D3DXCOLOR(1.0f, 1.0f, 0.2f, 1.0f);
				pVtx[3].col = g_colorBullet = g_colorBullet = D3DXCOLOR(1.0f, 1.0f, 0.2f, 1.0f);

				//�e�̎g�p
				pBullet->bUse = true;
				break;
			}
			else if (nType == 4)
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

				pVtx[0].col = g_colorBullet = g_colorBullet = D3DXCOLOR(1.0f, 1.0f, 0.2f, 1.0f);
				pVtx[1].col = g_colorBullet = g_colorBullet = D3DXCOLOR(1.0f, 1.0f, 0.2f, 1.0f);
				pVtx[2].col = g_colorBullet = g_colorBullet = D3DXCOLOR(1.0f, 1.0f, 0.2f, 1.0f);
				pVtx[3].col = g_colorBullet = g_colorBullet = D3DXCOLOR(1.0f, 1.0f, 0.2f, 1.0f);

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
BULLET *GetBullet(void)
{
	return &g_aBullet[0];
}

