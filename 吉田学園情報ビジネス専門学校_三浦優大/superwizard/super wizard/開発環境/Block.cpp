//================================================
//
//�v���C���[����[Player.h]
// Author; miura yuudai
//
//================================================

#include "Block.h"
#include "Player.h"
#include "input.h"
#include "Explosion.h"
#include "bullet.h"
#include "fade.h"
#include "enemy.h"
#include "Timer.h"
#include "particle.h"
#include "effect.h"

//=========================
//�}�N����`
//=========================
#define MAX_BLOCK (256)

//================
//�O���[�o���ϐ�
//================
LPDIRECT3DTEXTURE9 g_apTextureBlock[10] = {};//�e�N�X�`���փ|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;//���_�o�b�t�@�ւ̃|�C���^
BLOCK g_aBlock[MAX_BLOCK];//�G�̏��
D3DXVECTOR3 g_rotBlock;//��]��
int g_nData = 1;
int nCountParticle;
int nCountParticleL;
int g_ppData = 0;


//==========================
//�u���b�N�̏���������
//==========================
HRESULT InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	VERTEX_2D *pVtx;

	BLOCK *pBlock;

	pBlock = &g_aBlock[0];

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/pattern-1929506_1280.png", &g_apTextureBlock[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/block000.jpg", &g_apTextureBlock[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/block200.jpg", &g_apTextureBlock[2]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/pipe000.png", &g_apTextureBlock[3]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/block400.jpg", &g_apTextureBlock[4]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/pipe000.png", &g_apTextureBlock[5]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/block400.jpg", &g_apTextureBlock[6]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/block000.jpg", &g_apTextureBlock[7]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/block000.jpg", &g_apTextureBlock[8]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/block400.jpg", &g_apTextureBlock[9]);


	//������
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].fHeight = 0.0f;
		g_aBlock[nCntBlock].fWidth = 0.0f;
		g_aBlock[nCntBlock].bUse = false;
		g_aBlock[nCntBlock].nType = 0;
		int g_nData = 0;
	}

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock,
		NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].Pos.x - pBlock->fWidth, g_aBlock[nCntBlock].Pos.y + pBlock->fHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].Pos.x - pBlock->fWidth, g_aBlock[nCntBlock].Pos.y - pBlock->fHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].Pos.x + pBlock->fWidth, g_aBlock[nCntBlock].Pos.y + pBlock->fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].Pos.x + pBlock->fWidth, g_aBlock[nCntBlock].Pos.y - pBlock->fHeight, 0.0f);

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
	g_pVtxBuffBlock->Unlock();

	return S_OK;
}

//====================
//�u���b�N�̏I������
//====================
void UninitBlock(void)
{
	for (int nCntBlock = 0; nCntBlock < 10; nCntBlock++)
	{
		//�e�N�X�`���̊J��
		if (g_apTextureBlock[nCntBlock] != NULL)
		{
			g_apTextureBlock[nCntBlock]->Release();
			g_apTextureBlock[nCntBlock] = NULL;
		}
	}

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}
}

//==================
//�u���b�N�̍X�V����
//==================
void UpdateBlock(void)
{
	BLOCK *pBlock;
	VERTEX_2D *pVtx;
	PLAYER *pPlayer;
	ITEM *pExplosion;
	BULLET *pBullet;
	ENEMY *pEnemy;

	nCountParticle++;
	nCountParticleL--;
	nCountParticleL--;
	g_ppData++;


	pBlock = &g_aBlock[0];
	pPlayer = GetPlayer();
	pExplosion = GetItem();
	pBullet = GetBullet();
	pEnemy = GetEnemy();

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	//�ʒu�X�V
	pPlayer->Pos.x += pPlayer->move.x;
	pPlayer->Pos.y += pPlayer->move.y;

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++ ,pBlock++,pExplosion++,pEnemy++,pBullet++)
	{
		if (pBlock->bUse == true)//�e���g�p���Ă��邩�ǂ���
		{
			if (GetKeyboardPress(DIK_D) == true)//�E�ɐi��
			{
				//�v���C���[���������Ƃ��u���b�N��
				pBlock->move.x -= 2.0f;

				pExplosion->move.x -= 2.0f;

				pEnemy->move.x -= 4.75f;

				pBullet->move.x -= 0.1f;
			}
			
			if (GetKeyboardPress(DIK_A) == true)//���ɐi��
			{
				//�v���C���[���������Ƃ��u���b�N��
				pBlock->move.x += 2.0f;

				pExplosion->move.x += 2.0f;

				pEnemy->move.x += 4.75f;

			}

			//��ʂ��~�܂鏈��
			//if (g_aBlock[60].Pos.x <= 0)
			//{
			//	//�v���C���[���������Ƃ��u���b�N��
			//	pBlock->move.x = 0.0f;

			//	pExplosion->move.x = 0.0f;

			//	pEnemy->move.x = 0.00f;

			//	if (GetKeyboardPress(DIK_D) == true)//�E�ɐi��
			//	{
			//		pPlayer->move.x += sinf(D3DX_PI*0.5f) * 4.0f;
			//	}
			//	if (GetKeyboardPress(DIK_A) == true)//�E�ɐi��
			//	{
			//		pPlayer->move.x += -sinf(D3DX_PI*0.5f) * 4.0f;
			//	}

			//	//�u���b�N���̏���
			//	if (pBlock->Pos.x >= pPlayer->Pos.x - pBlock->fWidth + 30 && pBlock->Pos.x <= pPlayer->Pos.x + pBlock->fWidth + 30 &&
			//		pBlock->Pos.y >= pPlayer->Pos.y - pBlock->fHeight - 10 && pBlock->Pos.y <= pPlayer->Pos.y + pBlock->fHeight - 10)
			//	{
			//		pPlayer->move.x = 0.0f;//�d�̓��Z�b�g
			//		pPlayer->Pos.x = pBlock->Pos.x - pBlock->fWidth - 30;//���̓����蔻��
			//		for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++, pExplosion++)
			//		{
			//			g_aBlock[nCntBlock].move.x -= 2.0f;
			//		}
			//		for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++, pExplosion++)
			//		{
			//			pExplosion->move.x -= 5.0f;
			//		}
			//	}
			//	//�u���b�N�E�̏���
			//	else if (pBlock->Pos.x >= pPlayer->Pos.x - pBlock->fWidth - 30 && pBlock->Pos.x <= pPlayer->Pos.x + pBlock->fWidth - 30 &&
			//			 pBlock->Pos.y >= pPlayer->Pos.y - pBlock->fHeight - 10 && pBlock->Pos.y <= pPlayer->Pos.y + pBlock->fHeight - 10)
			//	{
			//		pPlayer->move.x = 0.0f;//�d�̓��Z�b�g
			//		pPlayer->Pos.x = pBlock->Pos.x + pBlock->fWidth + 30;//�E�̓����蔻��
			//		for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++,pExplosion++)
			//		{
			//			g_aBlock[nCntBlock].move.x += 2.0f;
			//		}
			//		pExplosion->move.x -= 5.0f;
			//	}

			//}

			//�㉺����

			//�u���b�N��̏���
			if (pBlock->bUse == true)
			{
				if (pBlock->Pos.x >= pPlayer->oldPos.x - pBlock->fWidth - 20 && pBlock->Pos.x <= pPlayer->oldPos.x + pBlock->fWidth + 20 &&
					pBlock->Pos.y >= pPlayer->Pos.y - pBlock->fHeight + pPlayer->g_fLengthPlayer + 20 && pBlock->Pos.y <= pPlayer->Pos.y + pBlock->fHeight + pPlayer->g_fLengthPlayer + 20)
				{
					pPlayer->move.y = 0.0f;//�d�̓��Z�b�g
					pPlayer->Pos.y = pBlock->Pos.y - pBlock->fHeight - pPlayer->g_fLengthPlayer + 20;//��̓����蔻��
				}

				//�u���b�N���̏���
				else if (pBlock->Pos.x >= pPlayer->oldPos.x - pBlock->fWidth - 20 && pBlock->Pos.x <= pPlayer->oldPos.x + pBlock->fWidth + 20 &&
						 pBlock->Pos.y >= pPlayer->Pos.y - pBlock->fHeight - pPlayer->g_fLengthPlayer + 5 && pBlock->Pos.y <= pPlayer->Pos.y + pBlock->fHeight - pPlayer->g_fLengthPlayer + 5)
				{
					pPlayer->move.y = 0.0f;//�d�̓��Z�b�g
					pPlayer->Pos.y = pBlock->Pos.y + pBlock->fHeight + pPlayer->g_fLengthPlayer - 5;//���̓����蔻��
				}


				//���E����
				//�u���b�N���̏���
				if (pBlock->Pos.x >= pPlayer->Pos.x - pBlock->fWidth + 30 && pBlock->Pos.x <= pPlayer->Pos.x + pBlock->fWidth + 30 &&
					pBlock->Pos.y >= pPlayer->Pos.y - pBlock->fHeight - 10 && pBlock->Pos.y <= pPlayer->Pos.y + pBlock->fHeight - 10)
				{
					pPlayer->move.x = 0.0f;//�d�̓��Z�b�g
					pPlayer->Pos.x = pBlock->Pos.x - pBlock->fWidth - 30;//���̓����蔻��
					for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
					{
						g_aBlock[nCntBlock].move.x += 2.0f;
					}
				}

				//�u���b�N�E�̏���
				else if (pBlock->Pos.x >= pPlayer->Pos.x - pBlock->fWidth - 30 && pBlock->Pos.x <= pPlayer->Pos.x + pBlock->fWidth - 30 &&
						 pBlock->Pos.y >= pPlayer->Pos.y - pBlock->fHeight - 10 && pBlock->Pos.y <= pPlayer->Pos.y + pBlock->fHeight - 10)
					{
						pPlayer->move.x = 0.0f;//�d�̓��Z�b�g
						pPlayer->Pos.x = pBlock->Pos.x + pBlock->fWidth + 30;//�E�̓����蔻��
						for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
						{
							g_aBlock[nCntBlock].move.x -= 2.0f;
						}
					}

				}

			//�ʒu�X�V
			pBlock->Pos.x += pBlock->move.x;
			pBlock->Pos.y += pBlock->move.y;

			pExplosion->pos.x += pExplosion->move.x;
			pExplosion->pos.y += pExplosion->move.y;


		//�A�C�e������
			//�u���b�N�^�C�v��2�̎�
			if (pBlock->nType == 2)
			{
				if (pBlock->bUse == true)
				{
					//�u���b�N���̏���
					if (pBlock->Pos.x >= pPlayer->oldPos.x - pBlock->fWidth - 20 && pBlock->Pos.x <= pPlayer->oldPos.x + pBlock->fWidth + 20 &&
					pBlock->Pos.y >= pPlayer->Pos.y - pBlock->fHeight - pPlayer->g_fLengthPlayer + 5 && pBlock->Pos.y <= pPlayer->Pos.y + pBlock->fHeight - pPlayer->g_fLengthPlayer + 5)
					{
						pPlayer->move.y = 0.0f;//�d�̓��Z�b�g
						pPlayer->Pos.y = pBlock->Pos.y + pBlock->fHeight + pPlayer->g_fLengthPlayer - 5;//���̓����蔻��

						//�A�C�e��
						SetItem(pBlock->Pos, 1, pExplosion->move);
						
						//�u���b�N�e�N�X�`���؂�ւ�
						pBlock->nType = 4;

					}
				}
			}

			//���̏���
			if (pExplosion->nType == 4)
			{
				if (pExplosion->pos.x >= pPlayer->Pos.x - 50 && pExplosion->pos.x <= pPlayer->Pos.x + 50 &&
					pExplosion->pos.y >= pPlayer->Pos.y - 50 && pExplosion->pos.y <= pPlayer->Pos.y + 50)
				{
					pExplosion->bUse = false;
					for (int nCntBlockfalse = 0; nCntBlockfalse < 55; nCntBlockfalse++)
					{
						g_aBlock[nCntBlockfalse].bUse = false;
					}
					
						SetFade(FADE_OUT, MODE_RESULT);
					
				}
			}

			
			//�y�Ǐ���
			if (pBlock->nType == 3)
			{
				if (pBlock->Pos.x >= pPlayer->oldPos.x - pBlock->fWidth - 20 && pBlock->Pos.x <= pPlayer->oldPos.x + pBlock->fWidth + 20 &&
					pBlock->Pos.y >= pPlayer->Pos.y - pBlock->fHeight + pPlayer->g_fLengthPlayer + 15 && pBlock->Pos.y <= pPlayer->Pos.y + pBlock->fHeight + pPlayer->g_fLengthPlayer + 15)
				{
					if (GetKeyboardPress(DIK_S) == true)
					{
						pPlayer->bUse = false;
						SetFade(FADE_OUT, MODE_GAME2);
					}
				}
			}

			//�S�[���y�Ǐ���
			if (pBlock->nType == 5)
			{
				if (pBlock->Pos.x >= pPlayer->oldPos.x - pBlock->fWidth - 20 && pBlock->Pos.x <= pPlayer->oldPos.x + pBlock->fWidth + 20 &&
					pBlock->Pos.y >= pPlayer->Pos.y - pBlock->fHeight + pPlayer->g_fLengthPlayer + 15 && pBlock->Pos.y <= pPlayer->Pos.y + pBlock->fHeight + pPlayer->g_fLengthPlayer + 15)
				{
					if (GetKeyboardPress(DIK_S) == true)
					{
						SetFade(FADE_OUT, MODE_RESULT);
					}
				}
			}
			

		//�t�@�C�A�[�o�[����
		if(pBlock->nType == 6)
		{
			D3DXVECTOR3 pos;
			D3DXVECTOR3 pos2;
			int nLife;
			D3DXVECTOR3 move;
			float fAngle;
			D3DXCOLOR col;

			for (int nCntParticle = 0; nCntParticle < 30; nCntParticle++)
			{
				pos = pBlock->Pos;
				///nLife = 2 + rand() % 5;
				nLife = 5;
				col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�J���[
				fAngle = (float)(nCountParticle) / 100.0f + D3DX_PI*0.5f;
				move.x = sinf(fAngle)*55.5f;
				move.y = cosf(fAngle)*55.5f;

				SetEffect(pos, nLife, 3, move);
			}
		}
		
		if (pEnemy->nType == 0)
		{
			for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
			{
				if (g_aBlock[nCntBlock].Pos.x >= pEnemy->Pos.x - g_aBlock[nCntBlock].fWidth - 20 && g_aBlock[nCntBlock].Pos.x <= pEnemy->Pos.x + g_aBlock[nCntBlock].fWidth + 20 &&
					g_aBlock[nCntBlock].Pos.y >= pEnemy->Pos.y - g_aBlock[nCntBlock].fHeight + 40 && g_aBlock[nCntBlock].Pos.y <= pEnemy->Pos.y + g_aBlock[nCntBlock].fHeight + 40)
				{
					pEnemy->move.y = 0.0f;//�d�̓��Z�b�g
					pEnemy->Pos.y = g_aBlock[nCntBlock].Pos.y - g_aBlock[nCntBlock].fHeight - 40;//��̓����蔻��
				}

				else if (g_aBlock[nCntBlock].Pos.x >= pEnemy->Pos.x - g_aBlock[nCntBlock].fWidth - 20 && g_aBlock[nCntBlock].Pos.x <= pEnemy->Pos.x + g_aBlock[nCntBlock].fWidth + 20 &&
					g_aBlock[nCntBlock].Pos.y >= pEnemy->Pos.y - g_aBlock[nCntBlock].fHeight + 5 && g_aBlock[nCntBlock].Pos.y <= pEnemy->Pos.y + g_aBlock[nCntBlock].fHeight + 5)
				{
					pEnemy->move.y = 0.0f;//�d�̓��Z�b�g
					pEnemy->Pos.y = g_aBlock[nCntBlock].Pos.y - g_aBlock[nCntBlock].fHeight + 5;//��̓����蔻��
				}

				//���E����
				//�u���b�N���̏���
				if (g_aBlock[nCntBlock].Pos.x >= pEnemy->Pos.x - g_aBlock[nCntBlock].fWidth + 60 && g_aBlock[nCntBlock].Pos.x <= pEnemy->Pos.x + g_aBlock[nCntBlock].fWidth + 60 &&
					g_aBlock[nCntBlock].Pos.y >= pEnemy->Pos.y - g_aBlock[nCntBlock].fHeight - 90 && g_aBlock[nCntBlock].Pos.y <= pEnemy->Pos.y + g_aBlock[nCntBlock].fHeight - 90)
				{
					pEnemy->move.x = 0.0f;//�d�̓��Z�b�g
					pEnemy->Pos.x = g_aBlock[nCntBlock].Pos.x - g_aBlock[nCntBlock].fWidth - 60;//���̓����蔻��
				}

				//�u���b�N�E�̏���
				else if (g_aBlock[nCntBlock].Pos.x >= pEnemy->Pos.x - g_aBlock[nCntBlock].fWidth - 30 && g_aBlock[nCntBlock].Pos.x <= pEnemy->Pos.x + g_aBlock[nCntBlock].fWidth - 30 &&
					g_aBlock[nCntBlock].Pos.y >= pEnemy->Pos.y - g_aBlock[nCntBlock].fHeight - 90 && g_aBlock[nCntBlock].Pos.y <= pEnemy->Pos.y + g_aBlock[nCntBlock].fHeight - 90)
				{
					pEnemy->move.x = 0.0f;//�d�̓��Z�b�g
					pEnemy->Pos.x = g_aBlock[nCntBlock].Pos.x + g_aBlock[nCntBlock].fWidth + 30;//�E�̓����蔻��
				}
			}
		}

		if (pEnemy->nType == 1)
		{
			for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
			{
				if (g_aBlock[nCntBlock].Pos.x >= pEnemy->Pos.x - g_aBlock[nCntBlock].fWidth - 20 && g_aBlock[nCntBlock].Pos.x <= pEnemy->Pos.x + g_aBlock[nCntBlock].fWidth + 20 &&
					g_aBlock[nCntBlock].Pos.y >= pEnemy->Pos.y - g_aBlock[nCntBlock].fHeight + 80 && g_aBlock[nCntBlock].Pos.y <= pEnemy->Pos.y + g_aBlock[nCntBlock].fHeight + 80)
				{
					pEnemy->move.y = 0.0f;//�d�̓��Z�b�g
					pEnemy->Pos.y = g_aBlock[nCntBlock].Pos.y - g_aBlock[nCntBlock].fHeight - 80;//��̓����蔻��
				}

				//���E����
				//�u���b�N���̏���
				if (g_aBlock[nCntBlock].Pos.x >= pEnemy->Pos.x - g_aBlock[nCntBlock].fWidth + 60 && g_aBlock[nCntBlock].Pos.x <= pEnemy->Pos.x + g_aBlock[nCntBlock].fWidth + 60 &&
					g_aBlock[nCntBlock].Pos.y >= pEnemy->Pos.y - g_aBlock[nCntBlock].fHeight - 90 && g_aBlock[nCntBlock].Pos.y <= pEnemy->Pos.y + g_aBlock[nCntBlock].fHeight - 90)
				{
					pEnemy->move.x = 0.0f;//�d�̓��Z�b�g
					pEnemy->Pos.x = g_aBlock[nCntBlock].Pos.x - g_aBlock[nCntBlock].fWidth - 60;//���̓����蔻��
				}

				//�u���b�N�E�̏���
				else if (g_aBlock[nCntBlock].Pos.x >= pEnemy->Pos.x - g_aBlock[nCntBlock].fWidth - 30 && g_aBlock[nCntBlock].Pos.x <= pEnemy->Pos.x + g_aBlock[nCntBlock].fWidth - 30 &&
					g_aBlock[nCntBlock].Pos.y >= pEnemy->Pos.y - g_aBlock[nCntBlock].fHeight - 90 && g_aBlock[nCntBlock].Pos.y <= pEnemy->Pos.y + g_aBlock[nCntBlock].fHeight - 90)
				{
					pEnemy->move.x = 0.0f;//�d�̓��Z�b�g
					pEnemy->Pos.x = g_aBlock[nCntBlock].Pos.x + g_aBlock[nCntBlock].fWidth + 30;//�E�̓����蔻��
				}
			}
		}
		
		if (pEnemy->nType == 2)
		{
			for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
			{
				if (g_aBlock[nCntBlock].Pos.x >= pEnemy->Pos.x - g_aBlock[nCntBlock].fWidth - 20 && g_aBlock[nCntBlock].Pos.x <= pEnemy->Pos.x + g_aBlock[nCntBlock].fWidth + 20 &&
					g_aBlock[nCntBlock].Pos.y >= pEnemy->Pos.y - g_aBlock[nCntBlock].fHeight + 55 && g_aBlock[nCntBlock].Pos.y <= pEnemy->Pos.y + g_aBlock[nCntBlock].fHeight + 55)
				{
					pEnemy->move.y = 0.0f;//�d�̓��Z�b�g
					pEnemy->Pos.y = g_aBlock[nCntBlock].Pos.y - g_aBlock[nCntBlock].fHeight - 55;//��̓����蔻��
				}

				//���E����
				//�u���b�N���̏���
				if (g_aBlock[nCntBlock].Pos.x >= pEnemy->Pos.x - g_aBlock[nCntBlock].fWidth + 60 && g_aBlock[nCntBlock].Pos.x <= pEnemy->Pos.x + g_aBlock[nCntBlock].fWidth + 60 &&
					g_aBlock[nCntBlock].Pos.y >= pEnemy->Pos.y - g_aBlock[nCntBlock].fHeight - 90 && g_aBlock[nCntBlock].Pos.y <= pEnemy->Pos.y + g_aBlock[nCntBlock].fHeight - 90)
				{
					pEnemy->move.x = 0.0f;//�d�̓��Z�b�g
					pEnemy->Pos.x = g_aBlock[nCntBlock].Pos.x - g_aBlock[nCntBlock].fWidth - 60;//���̓����蔻��
				}

				//�u���b�N�E�̏���
				else if (g_aBlock[nCntBlock].Pos.x >= pEnemy->Pos.x - g_aBlock[nCntBlock].fWidth - 30 && g_aBlock[nCntBlock].Pos.x <= pEnemy->Pos.x + g_aBlock[nCntBlock].fWidth - 30 &&
					g_aBlock[nCntBlock].Pos.y >= pEnemy->Pos.y - g_aBlock[nCntBlock].fHeight - 90 && g_aBlock[nCntBlock].Pos.y <= pEnemy->Pos.y + g_aBlock[nCntBlock].fHeight - 90)
				{
					pEnemy->move.x = 0.0f;//�d�̓��Z�b�g
					pEnemy->Pos.x = g_aBlock[nCntBlock].Pos.x + g_aBlock[nCntBlock].fWidth + 30;//�E�̓����蔻��
				}
			}
		}


		if (pBlock->nType == 9)
		{
			D3DXVECTOR3 pos;
			D3DXVECTOR3 pos2;
			int nLife;
			D3DXVECTOR3 move;
			float fAngle;
			D3DXCOLOR col;

			for (int nCntParticle = 0; nCntParticle < 30; nCntParticle++)
			{
				pos = pBlock->Pos;
				///nLife = 2 + rand() % 5;
				nLife = 5;
				col = D3DXCOLOR(0.2f, 0.2f, 1.0f, 1.0f);//�J���[
				fAngle = (float)(nCountParticleL) / 100.0f + D3DX_PI*0.5f;
				move.x = sinf(fAngle)*55.5f;
				move.y = cosf(fAngle)*55.5f;

				SetEffect(pos, nLife, 3, move);
			}
		}

		if (pPlayer->state == PLAYERSTATE_STAR)
		{
			//�u���b�N���̏���
			if (pBlock->Pos.x >= pPlayer->Pos.x - pBlock->fWidth + 30 && pBlock->Pos.x <= pPlayer->Pos.x + pBlock->fWidth + 30 &&
				pBlock->Pos.y >= pPlayer->Pos.y - pBlock->fHeight - 10 && pBlock->Pos.y <= pPlayer->Pos.y + pBlock->fHeight - 10)
			{
				pPlayer->move.x = 0.0f;//�d�̓��Z�b�g
				pPlayer->Pos.x = pBlock->Pos.x - pBlock->fWidth - 30;//���̓����蔻��
				for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
				{
					g_aBlock[nCntBlock].move.x += 2.25f;
				}
			}

			else if (pBlock->Pos.x >= pPlayer->Pos.x - pBlock->fWidth - 30 && pBlock->Pos.x <= pPlayer->Pos.x + pBlock->fWidth - 30 &&
				pBlock->Pos.y >= pPlayer->Pos.y - pBlock->fHeight - 10 && pBlock->Pos.y <= pPlayer->Pos.y + pBlock->fHeight - 10)
			{
				pPlayer->move.x = 0.0f;//�d�̓��Z�b�g
				pPlayer->Pos.x = pBlock->Pos.x + pBlock->fWidth + 30;//�E�̓����蔻��
				for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
				{
					g_aBlock[nCntBlock].move.x -= 2.25f;
				}
			}
		}

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].Pos.x - pBlock->fWidth, g_aBlock[nCntBlock].Pos.y + pBlock->fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].Pos.x - pBlock->fWidth, g_aBlock[nCntBlock].Pos.y - pBlock->fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].Pos.x + pBlock->fWidth, g_aBlock[nCntBlock].Pos.y + pBlock->fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].Pos.x + pBlock->fWidth, g_aBlock[nCntBlock].Pos.y - pBlock->fHeight, 0.0f);
			
			// �ړ��ʂ̌���
			pBlock->move.x += (0.0f - pBlock->move.x) *0.5f;

			// �ړ��ʂ̌���
			pExplosion->move.x += (0.0f - pExplosion->move.x) *0.67f;

			// �ړ��ʂ̌���
			pEnemy->move.x += (0.0f - pEnemy->move.x) *0.4f;

			// �ړ��ʂ̌���
			pPlayer->move.x += (0.0f - pPlayer->move.x) *0.5f;

			// �ړ��ʂ̌���
			//pBullet->move.x += (0.0f - pBullet->move.x) *0.05f;

		}

		//4���_���Ƃ��炷
			pVtx += 4;
	}
		
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffBlock->Unlock();
}

//==================
//�u���b�N�̕`�揈��
//==================
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	BLOCK *pBlock;
	pBlock = &g_aBlock[0];

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);


	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++, pBlock++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTextureBlock[pBlock->nType]);

		if (g_aBlock[nCntBlock].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBlock * 4, 2);
		}
	
	}
}

//====================
//�u���b�N�ݒu����
//====================
void SetBlock(D3DXVECTOR3 pos, float fWidth, float fHeight,int nType)
{
	BLOCK *pBlock;
	VERTEX_2D *pVtx;

	pBlock = &g_aBlock[0];

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++,pBlock++)
	{
		if (pBlock->bUse == false)//�e���g�p���Ă��邩�ǂ���
		{
			if (nType == 0)
			{
				//�ʒu�ݒ�
				pBlock->Pos = pos;

				pBlock->fHeight = fHeight;

				pBlock->fWidth = fWidth;

				pBlock->nType = nType;

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

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(pBlock->Pos.x - pBlock->fWidth, pBlock->Pos.y + pBlock->fHeight, 0.0f);//2D��0.0�Œ�
				pVtx[1].pos = D3DXVECTOR3(pBlock->Pos.x - pBlock->fWidth, pBlock->Pos.y - pBlock->fHeight, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pBlock->Pos.x + pBlock->fWidth, pBlock->Pos.y + pBlock->fHeight, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pBlock->Pos.x + pBlock->fWidth, pBlock->Pos.y - pBlock->fHeight, 0.0f);

				//�e�̎g�p
				pBlock->bUse = true;
				break;
			}
			if (nType == 1)
			{
				//�ʒu�ݒ�
				pBlock->Pos = pos;

				pBlock->fHeight = fHeight;

				pBlock->fWidth = fWidth;

				pBlock->nType = nType;

				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

				//���_���̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(30.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(30.0f, 0.0f);

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(pBlock->Pos.x - pBlock->fWidth, pBlock->Pos.y + pBlock->fHeight, 0.0f);//2D��0.0�Œ�
				pVtx[1].pos = D3DXVECTOR3(pBlock->Pos.x - pBlock->fWidth, pBlock->Pos.y - pBlock->fHeight, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pBlock->Pos.x + pBlock->fWidth, pBlock->Pos.y + pBlock->fHeight, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pBlock->Pos.x + pBlock->fWidth, pBlock->Pos.y - pBlock->fHeight, 0.0f);

				//�e�̎g�p
				pBlock->bUse = true;
				break;
			}
			if (nType == 2)
			{
				//�ʒu�ݒ�
				pBlock->Pos = pos;

				pBlock->fHeight = fHeight;

				pBlock->fWidth = fWidth;

				pBlock->nType = nType;

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

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(pBlock->Pos.x - pBlock->fWidth, pBlock->Pos.y + pBlock->fHeight, 0.0f);//2D��0.0�Œ�
				pVtx[1].pos = D3DXVECTOR3(pBlock->Pos.x - pBlock->fWidth, pBlock->Pos.y - pBlock->fHeight, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pBlock->Pos.x + pBlock->fWidth, pBlock->Pos.y + pBlock->fHeight, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pBlock->Pos.x + pBlock->fWidth, pBlock->Pos.y - pBlock->fHeight, 0.0f);

				//�e�̎g�p
				pBlock->bUse = true;
				break;
			}
			if (nType == 3)
			{
				//�ʒu�ݒ�
				pBlock->Pos = pos;

				pBlock->fHeight = fHeight;

				pBlock->fWidth = fWidth;

				pBlock->nType = nType;

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

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(pBlock->Pos.x - pBlock->fWidth, pBlock->Pos.y + pBlock->fHeight, 0.0f);//2D��0.0�Œ�
				pVtx[1].pos = D3DXVECTOR3(pBlock->Pos.x - pBlock->fWidth, pBlock->Pos.y - pBlock->fHeight, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pBlock->Pos.x + pBlock->fWidth, pBlock->Pos.y + pBlock->fHeight, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pBlock->Pos.x + pBlock->fWidth, pBlock->Pos.y - pBlock->fHeight, 0.0f);

				//�e�̎g�p
				pBlock->bUse = true;
				break;
			}
			if (nType == 4)
			{
				//�ʒu�ݒ�
				pBlock->Pos = pos;

				pBlock->fHeight = fHeight;

				pBlock->fWidth = fWidth;

				pBlock->nType = nType;

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

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(pBlock->Pos.x - pBlock->fWidth, pBlock->Pos.y + pBlock->fHeight, 0.0f);//2D��0.0�Œ�
				pVtx[1].pos = D3DXVECTOR3(pBlock->Pos.x - pBlock->fWidth, pBlock->Pos.y - pBlock->fHeight, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pBlock->Pos.x + pBlock->fWidth, pBlock->Pos.y + pBlock->fHeight, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pBlock->Pos.x + pBlock->fWidth, pBlock->Pos.y - pBlock->fHeight, 0.0f);

				//�e�̎g�p
				pBlock->bUse = true;
				break;
			}
			if (nType == 5)
			{
				//�ʒu�ݒ�
				pBlock->Pos = pos;

				pBlock->fHeight = fHeight;

				pBlock->fWidth = fWidth;

				pBlock->nType = nType;

				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 0, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 0, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 0, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 0, 255);

				//���_���̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(pBlock->Pos.x - pBlock->fWidth, pBlock->Pos.y + pBlock->fHeight, 0.0f);//2D��0.0�Œ�
				pVtx[1].pos = D3DXVECTOR3(pBlock->Pos.x - pBlock->fWidth, pBlock->Pos.y - pBlock->fHeight, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pBlock->Pos.x + pBlock->fWidth, pBlock->Pos.y + pBlock->fHeight, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pBlock->Pos.x + pBlock->fWidth, pBlock->Pos.y - pBlock->fHeight, 0.0f);

				//�e�̎g�p
				pBlock->bUse = true;
				break;
			}
			if (nType == 6)
			{
				//�ʒu�ݒ�
				pBlock->Pos = pos;

				pBlock->fHeight = fHeight;

				pBlock->fWidth = fWidth;

				pBlock->nType = nType;

				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DCOLOR_RGBA(255, 0, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 0, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 0, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 0, 255, 255);

				//���_���̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(pBlock->Pos.x - pBlock->fWidth, pBlock->Pos.y + pBlock->fHeight, 0.0f);//2D��0.0�Œ�
				pVtx[1].pos = D3DXVECTOR3(pBlock->Pos.x - pBlock->fWidth, pBlock->Pos.y - pBlock->fHeight, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pBlock->Pos.x + pBlock->fWidth, pBlock->Pos.y + pBlock->fHeight, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pBlock->Pos.x + pBlock->fWidth, pBlock->Pos.y - pBlock->fHeight, 0.0f);

				//�e�̎g�p
				pBlock->bUse = true;
				break;
			}
			if (nType == 7)
			{
				//�ʒu�ݒ�
				pBlock->Pos = pos;

				pBlock->fHeight = fHeight;

				pBlock->fWidth = fWidth;

				pBlock->nType = nType;

				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

				//���_���̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 20.0f);
				pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(1.0f, 20.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(pBlock->Pos.x - pBlock->fWidth, pBlock->Pos.y + pBlock->fHeight, 0.0f);//2D��0.0�Œ�
				pVtx[1].pos = D3DXVECTOR3(pBlock->Pos.x - pBlock->fWidth, pBlock->Pos.y - pBlock->fHeight, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pBlock->Pos.x + pBlock->fWidth, pBlock->Pos.y + pBlock->fHeight, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pBlock->Pos.x + pBlock->fWidth, pBlock->Pos.y - pBlock->fHeight, 0.0f);

				//�e�̎g�p
				pBlock->bUse = true;
				break;
			}
			if (nType == 8)
			{
				//�ʒu�ݒ�
				pBlock->Pos = pos;

				pBlock->fHeight = fHeight;

				pBlock->fWidth = fWidth;

				pBlock->nType = nType;

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

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(pBlock->Pos.x - pBlock->fWidth, pBlock->Pos.y + pBlock->fHeight, 0.0f);//2D��0.0�Œ�
				pVtx[1].pos = D3DXVECTOR3(pBlock->Pos.x - pBlock->fWidth, pBlock->Pos.y - pBlock->fHeight, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pBlock->Pos.x + pBlock->fWidth, pBlock->Pos.y + pBlock->fHeight, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pBlock->Pos.x + pBlock->fWidth, pBlock->Pos.y - pBlock->fHeight, 0.0f);

				//�e�̎g�p
				pBlock->bUse = true;
				break;
			}
			if (nType == 9)
			{
				//�ʒu�ݒ�
				pBlock->Pos = pos;

				pBlock->fHeight = fHeight;

				pBlock->fWidth = fWidth;

				pBlock->nType = nType;

				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DCOLOR_RGBA(255, 0, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 0, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 0, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 0, 255, 255);

				//���_���̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(pBlock->Pos.x - pBlock->fWidth, pBlock->Pos.y + pBlock->fHeight, 0.0f);//2D��0.0�Œ�
				pVtx[1].pos = D3DXVECTOR3(pBlock->Pos.x - pBlock->fWidth, pBlock->Pos.y - pBlock->fHeight, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pBlock->Pos.x + pBlock->fWidth, pBlock->Pos.y + pBlock->fHeight, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pBlock->Pos.x + pBlock->fWidth, pBlock->Pos.y - pBlock->fHeight, 0.0f);

				//�e�̎g�p
				pBlock->bUse = true;
				break;
			}
			
		}
			//4���_���Ƃ��炷
			pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffBlock->Unlock();
}
BLOCK *GetBlock(void)
{
	return &g_aBlock[60];
}
int GetBlockNumber(void)
{
	return g_ppData;
}


