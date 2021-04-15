//================================================
//
//�G�̏���[Player.h]
// Author; miura yuudai
//
//================================================
#include "input.h"
#include "enemy.h"
#include "bullet.h"
#include "Player.h"
#include "Explosion.h"
#include "enemy.h"
#include "particle.h"
#include "fade.h"
#include "Block.h"
#include "effect.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureEnemy[3] = {};//�e�N�X�`���փ|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;//���_�o�b�t�@�ւ̃|�C���^
ENEMY g_aEnemy[256];//�G�̏��
D3DXVECTOR3 g_rotEnemy;//�G�̃T�C�Y���
int g_nCntEnemy;

//==================
//�G�l�~�[�̏���������
//==================
HRESULT InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/enemy006.png", &g_apTextureEnemy[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/�N�b�p.png", &g_apTextureEnemy[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/hannma.png", &g_apTextureEnemy[2]);

	//������
	for (int nCntEnemy = 0; nCntEnemy < 256; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].nType = 0;
		g_aEnemy[nCntEnemy].bUse = false;
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NOMAL;
		g_aEnemy[nCntEnemy].nCounterState = 0;
		g_aEnemy[nCntEnemy].nLife = 3000;//�G�̗̑�
		g_aEnemy[nCntEnemy].g_nCounterAni = 0;
		g_aEnemy[nCntEnemy].g_nPatternAni = 0;
		g_aEnemy[nCntEnemy].g_nseetAni = 0;
		int g_nCntEnemy = 0;
	}

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 256,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemy = 0; nCntEnemy < 256; nCntEnemy++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].Pos.x - MAX_ENEMY_SIZE, g_aEnemy[nCntEnemy].Pos.y + MAX_ENEMY_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].Pos.x - MAX_ENEMY_SIZE, g_aEnemy[nCntEnemy].Pos.y - MAX_ENEMY_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].Pos.x + MAX_ENEMY_SIZE, g_aEnemy[nCntEnemy].Pos.y + MAX_ENEMY_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].Pos.x + MAX_ENEMY_SIZE, g_aEnemy[nCntEnemy].Pos.y - MAX_ENEMY_SIZE, 0.0f);

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
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx += 4;//4���_���Ƃ��炷
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffEnemy->Unlock();

	return S_OK;
}

//==================
//�G�l�~�[�̏I������
//==================
void UninitEnemy(void)
{
	//�e�N�X�`���̊J��
	for (int nCount = 0; nCount <  MAX_TYPE_ENEMY; nCount++)
	{
		if (g_apTextureEnemy[nCount] != NULL)
		{
			g_apTextureEnemy[nCount]->Release();
			g_apTextureEnemy[nCount] = NULL;
		}
	}

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}

//==================
//�G�l�~�[�̍X�V����
//==================
void UpdateEnemy(void)
 {
	VERTEX_2D *pVtx;
	ENEMY *pEnemy;
	PLAYER *pPlayer;
	BLOCK *pBlock;
	EFFECT *pEffect;
	BULLET *pBullet;
	pEnemy = &g_aEnemy[0];
	pPlayer = GetPlayer();
	pBlock = GetBlock();
	pEffect = GetEffect();
	pBullet = GetBullet();
	g_nCntEnemy++;

	//���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemy = 0; nCntEnemy < 256; nCntEnemy++,pEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)//�G���g�p����Ă��邩�ǂ���
		{
			//�Ίp���̒���
			pEnemy->g_fLengthEnemy = sqrtf(MAX_ENEMY_SIZE *MAX_ENEMY_SIZE + MAX_ENEMY_SIZE * MAX_ENEMY_SIZE);
			//�Ίp���̊p�x
			pEnemy->g_fAngleEnemy = atan2f(MAX_ENEMY_SIZE, MAX_ENEMY_SIZE);

			if (pEnemy->nType == 1)
			{
				if (g_nCntEnemy % 100 == 0)
				{
					float fAngle;
					
					fAngle = (float)(258) / 100.0f;//�e�͈̔�
					pEnemy->move.y += cosf(fAngle) * 30.5f;

				}
				float fmove;

				fmove = (float)(rand() % 78 - 39) / 100.0f;
				pEnemy->move.x -= sinf(fmove*0.5f) * 12.5f;

				if (g_nCntEnemy % 150 == 0)
				{
					int nLife;
					D3DXVECTOR3 move;
					float fAngle;
					D3DXCOLOR col;

					nLife = 2200;
					col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
					fAngle = (float)(rand() % 628 - 314) / 100.0f;//�e�͈̔�
					move.x = sinf(D3DX_PI*0.5)*-5.0f;//�e�̈ړ���
					move.y = cosf(D3DX_PI*0.5)*-5.0f;//�e�̈ړ���

					SetBullet(pEnemy->Pos, move, nLife, col, 0);

				}
			}

			if (pEnemy->nType == 0)
			{
				pEnemy->move.x -= sinf(D3DX_PI*0.5f) * 0.5f;

				//�Ίp���̒���
				pEnemy->g_fLengthEnemy = sqrtf(40 * 40 + 40 * 40);
				//�Ίp���̊p�x
				pEnemy->g_fAngleEnemy = atan2f(40, 40);

				pEnemy->g_nCounterAni++;//�A�j���[�V�������v���X����Ă���

				if ((pEnemy->g_nCounterAni % 13) == 0)//10�Ŋ���؂��
				{
					pEnemy->g_nPatternAni++;

					pEnemy->g_nseetAni = (pEnemy->g_nseetAni + 1) % 8;

					pVtx[0].tex = D3DXVECTOR2(0.0f + 0.5f*pEnemy->g_nseetAni, 1.0f);
					pVtx[1].tex = D3DXVECTOR2(0.0f + 0.5f*pEnemy->g_nseetAni, 0.0f);
					pVtx[2].tex = D3DXVECTOR2(0.5f + 0.5f*pEnemy->g_nseetAni, 1.0f);
					pVtx[3].tex = D3DXVECTOR2(0.5f + 0.5f*pEnemy->g_nseetAni, 0.0f);
				}

			}
			if (pEnemy->nType == 2)
			{
				//�Ίp���̒���
				pEnemy->g_fLengthEnemy = sqrtf(60 * 60 + 60 * 60);
				//�Ίp���̊p�x
				pEnemy->g_fAngleEnemy = atan2f(60, 60);

				pEnemy->move.x -= sinf(D3DX_PI*0.5f) * 0.2f;

				if (g_nCntEnemy % 50 == 0)
				{
					int nLife;
					D3DXVECTOR3 move;
					float fAngle;
					D3DXCOLOR col;

					nLife = 200;
					col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
					fAngle = (float)(-220) / 100.0f;//�e�͈̔�
					move.x = sinf(fAngle)*14.0f;//�e�̈ړ���
					move.y = cosf(fAngle)*14.0f;//�e�̈ړ���

					SetBullet(pEnemy->Pos, move, nLife, col, 3);

				}
			}

			//�G�l�~�[�̈ړ�����
			for (int nCntExplosion = 0; nCntExplosion < 256; nCntExplosion++, pBlock++)
			{
				if (pBlock->Pos.x >= pPlayer->Pos.x - pBlock->fWidth + 30 && pBlock->Pos.x <= pPlayer->Pos.x + pBlock->fWidth + 30 &&
					pBlock->Pos.y >= pPlayer->Pos.y - pBlock->fHeight - 10 && pBlock->Pos.y <= pPlayer->Pos.y + pBlock->fHeight - 10)
				{
					for (int nCntExplosion = 0; nCntExplosion < 256; nCntExplosion++)
					{
						g_aEnemy[nCntExplosion].move.x += 3.0f;
					}
				}

				else if (pBlock->Pos.x >= pPlayer->Pos.x - pBlock->fWidth - 30 && pBlock->Pos.x <= pPlayer->Pos.x + pBlock->fWidth - 30 &&
						pBlock->Pos.y >= pPlayer->Pos.y - pBlock->fHeight - 10 && pBlock->Pos.y <= pPlayer->Pos.y + pBlock->fHeight - 10)
				{
					for (int nCntExplosion = 0; nCntExplosion < 256; nCntExplosion++)
					{
						g_aEnemy[nCntExplosion].move.x -= 3.0f;
					}
				}
			}


			//�G�l�~�[�̏d��
			pEnemy->move.y += 3.5f;

			//�ʒu�X�V
			g_aEnemy[nCntEnemy].Pos.x += pEnemy->move.x;
			g_aEnemy[nCntEnemy].Pos.y += pEnemy->move.y;


			//�ړ��ʂ̌���
			pEnemy->move.x += (0.0f - pEnemy->move.x) *0.5f;


			//�ړ����̒��_���
			pVtx[0].pos.x = g_aEnemy[nCntEnemy].Pos.x + sinf(g_rotEnemy.z - pEnemy->g_fAngleEnemy) * pEnemy->g_fLengthEnemy;
			pVtx[0].pos.y = g_aEnemy[nCntEnemy].Pos.y + cosf(g_rotEnemy.z - pEnemy->g_fAngleEnemy) * pEnemy->g_fLengthEnemy;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_aEnemy[nCntEnemy].Pos.x - sinf(g_rotEnemy.z + pEnemy->g_fAngleEnemy) * pEnemy->g_fLengthEnemy;
			pVtx[1].pos.y = g_aEnemy[nCntEnemy].Pos.y - cosf(g_rotEnemy.z + pEnemy->g_fAngleEnemy) * pEnemy->g_fLengthEnemy;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_aEnemy[nCntEnemy].Pos.x + sinf(g_rotEnemy.z + pEnemy->g_fAngleEnemy) * pEnemy->g_fLengthEnemy;
			pVtx[2].pos.y = g_aEnemy[nCntEnemy].Pos.y + cosf(g_rotEnemy.z + pEnemy->g_fAngleEnemy) * pEnemy->g_fLengthEnemy;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_aEnemy[nCntEnemy].Pos.x - sinf(g_rotEnemy.z - pEnemy->g_fAngleEnemy) * pEnemy->g_fLengthEnemy;
			pVtx[3].pos.y = g_aEnemy[nCntEnemy].Pos.y - cosf(g_rotEnemy.z - pEnemy->g_fAngleEnemy) * pEnemy->g_fLengthEnemy;
			pVtx[3].pos.z = 0.0f;


			//switch (g_aEnemy[nCntEnemy].state)
			//{
			//case ENEMYSTATE_DAMAGE:
			//	g_aEnemy[nCntEnemy].nCounterState--;
			//	if (g_aEnemy[nCntEnemy].nCounterState <= 0)
			//	{
			//		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NOMAL;
			//		//���_�J���[�̐ݒ�
			//		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			//		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			//		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			//		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			//	}
			//	break;
			//}

			//�ړ��ʂ̌���
			//pEnemy->move.x += (0.0f - pEnemy->move.x) *0.5f;

		}
		pVtx += 4;//4���_���Ƃ��炷
	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffEnemy->Unlock();
  }
//==================
//�G�l�~�[�̕`�揈��
//==================
void DrawEnemy(void)
{
	ENEMY *pEnemy;
	LPDIRECT3DDEVICE9 pDevice;

	pEnemy = &g_aEnemy[0];

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�|���S���̕`��
	for (int nCutEnemy = 0; nCutEnemy < 256; nCutEnemy++,pEnemy++)
	{
		pDevice->SetTexture(0, g_apTextureEnemy[pEnemy->nType]);

		if(pEnemy->bUse == true)//�e���g�p���Ă��邩�ǂ���
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCutEnemy*4, 2);
		}
	}
}

//==================
//�G�l�~�[�̐ݒ�
//==================
void SETENEMY(D3DXVECTOR3 Pos, int nType)
{
	ENEMY *pEnemy;
	VERTEX_2D *pVtx;

	PLAYER *pPlayer;
	pPlayer = GetPlayer();

	pEnemy = &g_aEnemy[0];

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemy = 0; nCntEnemy < 256; nCntEnemy++,pEnemy++)
	{
		if (pEnemy->bUse == false)//�e���g�p���Ă��邩�ǂ���
		{
			if (nType == 0)
			{
				//�ʒu�ݒ�
				g_aEnemy[nCntEnemy].Pos = Pos;

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].Pos.x - MAX_ENEMY_SIZE, g_aEnemy[nCntEnemy].Pos.y + MAX_ENEMY_SIZE, 0.0f);//2D��0.0�Œ�
				pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].Pos.x - MAX_ENEMY_SIZE, g_aEnemy[nCntEnemy].Pos.y - MAX_ENEMY_SIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].Pos.x + MAX_ENEMY_SIZE, g_aEnemy[nCntEnemy].Pos.y + MAX_ENEMY_SIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].Pos.x + MAX_ENEMY_SIZE, g_aEnemy[nCntEnemy].Pos.y - MAX_ENEMY_SIZE, 0.0f);


				//�^�C�v�ݒ�
				pEnemy->nType = nType;

				//�e�̎g�p
				pEnemy->bUse = true;
				break;
			}
			else if (nType == 1)
			{
				//�ʒu�ݒ�
				g_aEnemy[nCntEnemy].Pos = Pos;

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].Pos.x - MAX_ENEMY_SIZE, g_aEnemy[nCntEnemy].Pos.y + MAX_ENEMY_SIZE, 0.0f);//2D��0.0�Œ�
				pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].Pos.x - MAX_ENEMY_SIZE, g_aEnemy[nCntEnemy].Pos.y - MAX_ENEMY_SIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].Pos.x + MAX_ENEMY_SIZE, g_aEnemy[nCntEnemy].Pos.y + MAX_ENEMY_SIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].Pos.x + MAX_ENEMY_SIZE, g_aEnemy[nCntEnemy].Pos.y - MAX_ENEMY_SIZE, 0.0f);

				//�^�C�v�ݒ�
				pEnemy->nType = nType;

				//�e�̎g�p
				pEnemy->bUse = true;
				break;
			}
			else if (nType == 2)
			{
				//�ʒu�ݒ�
				g_aEnemy[nCntEnemy].Pos = Pos;

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].Pos.x - MAX_ENEMY_SIZE, g_aEnemy[nCntEnemy].Pos.y + MAX_ENEMY_SIZE, 0.0f);//2D��0.0�Œ�
				pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].Pos.x - MAX_ENEMY_SIZE, g_aEnemy[nCntEnemy].Pos.y - MAX_ENEMY_SIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].Pos.x + MAX_ENEMY_SIZE, g_aEnemy[nCntEnemy].Pos.y + MAX_ENEMY_SIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].Pos.x + MAX_ENEMY_SIZE, g_aEnemy[nCntEnemy].Pos.y - MAX_ENEMY_SIZE, 0.0f);

				//�^�C�v�ݒ�
				pEnemy->nType = nType;

				//�e�̎g�p
				pEnemy->bUse = true;
				break;
			}
		}

		pVtx += 4;//4���_���Ƃ��炷
	}
		// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffEnemy->Unlock();
}

//==================
//�G�l�~�[�̍\���̐ݒ�
//==================
ENEMY *GetEnemy(void) 
{
	return &g_aEnemy[0];
}

////==================
////�G�l�~�[�̒e�q�b�g���̐ݒ�
////==================
//bool HitEnemy(int nIdx, int nDamage)
//{
//	ENEMY *pEnemy;
//	pEnemy = &g_aEnemy[nIdx];
//	VERTEX_2D *pVtx;
//
//	//���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
//	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
//
//	g_aEnemy[nIdx].nLife -= nDamage;//�̗͂���_���[�W������
//
//	if (g_aEnemy[nIdx].nLife <= 0)//�̗͂�0�ȉ��ɂȂ�����
//	{
//		PlaySound(SOUND_LABEL_SE_EXPLOSION);
//		AddScore(99999999);
//		g_aEnemy[nIdx].bUse = false;
//		g_nData--;
//
//		for (int nCntAppear = 0; nCntAppear < 300; nCntAppear++)
//		{
//			D3DXVECTOR3 pos;
//			int nLife;
//			D3DXVECTOR3 move;
//			float fAngle;
//
//			pos = pEnemy->Pos;
//			nLife = 100 + rand() % 200;
//			fAngle = (float)(rand() % 628 - 314) / 100.0f;
//			move.x = sinf(fAngle)*1.5f;
//			move.y = cosf(fAngle)*1.5f;
//			SetEffect(pos, nLife, 0, move);
//		}
//			if (g_nData == 0)
//			{
//				SetFade(FADE_OUT, MODE_RESULT);
//			}
//		
//		return true;
//	}
//	else
//	{
//			AddScore(99);
//			g_aEnemy[nIdx].state = ENEMYSTATE_DAMAGE;
//			g_aEnemy[nIdx].nCounterState = 10;
//
//			//���_�J���[�̐ݒ�
//			pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
//			pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
//			pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
//			pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);
//
//	}
//		return false;
//	
//	// ���_�o�b�t�@���A�����b�N
//	g_pVtxBuffEnemy->Unlock();
//}