//================================================
//
//�v���C���[����[Player.h]
// Author; miura yuudai
//
//================================================
#include "Player.h"
#include "input.h"
#include "bg.h"
#include "Explosion.h"
#include "Block.h"
#include "bullet.h"
#include "fade.h"
#include "enemy.h"
#include "effect.h"

//==============
//�O���[�o���ϐ�
//==============
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;//�e�N�X�`�����
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;//���_���
PLAYER g_posPlayer;//�v���C���[���
D3DXVECTOR3 g_rotPlayer;//��]��
D3DXVECTOR3 g_movePlayer;//�ړ���
int g_nCnt;


//====================
//�|���S���̏���������
//====================
HRESULT InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ShipType04.png", &g_pTexturePlayer);

	//�ϐ�������
	g_posPlayer.bUse = true;
	g_posPlayer.Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_posPlayer.oldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_posPlayer.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_posPlayer.nLife = 1000;
	g_posPlayer.state = PLAYERSTATE_NOMAL;
	g_posPlayer.nCounterState = 100;//���G����
	g_posPlayer.nCounterStateStar = 1000;
	g_posPlayer.g_nCounterAnim = 0;
	g_posPlayer.g_nPatternAnim = 0;
	g_posPlayer.g_nseetAnim = 0;
	g_posPlayer.g_fAnglePlayer = 0;
	g_posPlayer.g_fLengthPlayer = 0;
	int g_nCnt = 0;


	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//�v���C���[�̏����ʒu
	g_posPlayer.Pos = D3DXVECTOR3(400, 800, 0.0f);

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
	pVtx[0].tex = D3DXVECTOR2(0.25f, 0.5f);
	pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.5f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.5f, 0.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffPlayer->Unlock();

	return S_OK;
}

//==================
//�v���C���[�̏I������
//==================
void UninitPlayer(void)
{
	//�e�N�X�`���̊J��
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}

}
//==================
//�v���C���[�̍X�V����
//==================
void UpdatePlayer(void)
{
	VERTEX_2D *pVtx;

	PLAYER *pPlayer;
	ITEM * pExplosion;
	BLOCK *pBlock;
	ENEMY *pEnemy;
	EFFECT *pEffect;
	BULLET *pBullet;

	pPlayer = GetPlayer();
	pExplosion = GetItem();
	pBlock = GetBlock();
	pEnemy = GetEnemy();
	pEffect = GetEffect();
	pBullet = GetBullet();
	g_nCnt++;

	//���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

		if (pPlayer->bUse == true)//�g�p���Ă��邩
		{
			g_posPlayer.oldPos.x = g_posPlayer.Pos.x;
			g_posPlayer.oldPos.y = g_posPlayer.Pos.y;

			if (g_posPlayer.state == PLAYERSTATE_NOMAL)
			{
				//�Ίp���̒���
				g_posPlayer.g_fLengthPlayer = sqrtf(40 * 40 + 50 * 50);

				//�Ίp���̊p�x
				g_posPlayer.g_fAnglePlayer = atan2f(40, 50);

				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

				for (int nCntEnemy = 0; nCntEnemy < 256; nCntEnemy++, pEnemy++)
				{
					//���S����
					if (pPlayer->Pos.x >= pEnemy->Pos.x - 50 && pPlayer->Pos.x <= pEnemy->Pos.x + 50 &&
						pPlayer->Pos.y >= pEnemy->Pos.y - 50 && pPlayer->Pos.y <= pEnemy->Pos.y + 50)
					{
						//�p�[�e�B�N������
						for (int nCntAppear = 0; nCntAppear < 2; nCntAppear++)
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
						pPlayer->bUse = false;
						pBlock->move.x = 0.0f;
						pPlayer->move.x = 0.0f;
						SetFade(FADE_OUT, MODE_RESULT);
					}
				}
				//���S����
				if (pEffect->nType == 3)
				{
					if (pEffect->bUse == true)
					{
						for (int nCntEnemy = 0; nCntEnemy < 256; nCntEnemy++, pEffect++)
						{
							if (pPlayer->Pos.x >= pEffect->pos.x - 30 && pPlayer->Pos.x <= pEffect->pos.x + 30 &&
								pPlayer->Pos.y >= pEffect->pos.y - 30 && pPlayer->Pos.y <= pEffect->pos.y + 30)
							{
								pPlayer->bUse = false;
								//�p�[�e�B�N������
								for (int nCntAppear = 0; nCntAppear < 5; nCntAppear++)
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
								pBlock->move.x = 0.0f;
								pPlayer->move.x = 0.0f;
								SetFade(FADE_OUT, MODE_RESULT);
							}
						}
					}
				}
				//���S����
				if (pBullet->nType == 0)
				{
					if (pBullet->bUse == true)
					{
						for (int nCntEnemy = 0; nCntEnemy < 256; nCntEnemy++, pBullet++)
						{
							if (pPlayer->Pos.x >= pBullet->pos.x - 90 && pPlayer->Pos.x <= pBullet->pos.x + 90 &&
								pPlayer->Pos.y >= pBullet->pos.y - 90 && pPlayer->Pos.y <= pBullet->pos.y + 90)
							{
								pPlayer->bUse = false;
								//�p�[�e�B�N������
								for (int nCntAppear = 0; nCntAppear < 5; nCntAppear++)
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
								pBlock->move.x = 0.0f;
								pPlayer->move.x = 0.0f;
								SetFade(FADE_OUT, MODE_RESULT);
							}
						}
					}
				}
			}

			if (g_posPlayer.state == PLAYERSTATE_DAMAGE)
			{
				//���G���Ԃɓ˓�
				if (pEnemy->bUse == true)
				{
					for (int nCntEnemy = 0; nCntEnemy < 256; nCntEnemy++, pEnemy++)
					{
						if (pPlayer->oldPos.x >= pEnemy->Pos.x - 50 && pPlayer->oldPos.x <= pEnemy->Pos.x + 50 &&
							pPlayer->Pos.y >= pEnemy->Pos.y - 50 && pPlayer->Pos.y <= pEnemy->Pos.y + 50)
						{
							g_posPlayer.state = PLAYERSTATE_MUTEKI;
						}
					}
				}
				//���G���Ԃɓ˓�
				if (pEffect->nType == 3)
				{
					if (pEffect->bUse == true)
					{
						for (int nCntEnemy = 0; nCntEnemy < 256; nCntEnemy++, pEffect++)
						{
							if (pPlayer->Pos.x >= pEffect->pos.x - 30 && pPlayer->Pos.x <= pEffect->pos.x + 30 &&
								pPlayer->Pos.y >= pEffect->pos.y - 30 && pPlayer->Pos.y <= pEffect->pos.y + 30)
							{
								g_posPlayer.state = PLAYERSTATE_MUTEKI;
							}
						}
					}
				}
				//���G���Ԃɓ˓�
				if (pEffect->nType == 5)
				{
					if (pEffect->bUse == true)
					{
						for (int nCntEnemy = 0; nCntEnemy < 256; nCntEnemy++, pEffect++)
						{
							if (pPlayer->Pos.x >= pEffect->pos.x - 30 && pPlayer->Pos.x <= pEffect->pos.x + 30 &&
								pPlayer->Pos.y >= pEffect->pos.y - 30 && pPlayer->Pos.y <= pEffect->pos.y + 30)
							{
								g_posPlayer.state = PLAYERSTATE_MUTEKI;
							}
						}
					}
				}
			}

			if (g_posPlayer.state == PLAYERSTATE_MUTEKI)
			{
				g_posPlayer.nCounterState--;

				//�Ίp���̒���
				g_posPlayer.g_fLengthPlayer = sqrtf(40 * 40 + 40 * 40);

				//�Ίp���̊p�x
				g_posPlayer.g_fAnglePlayer = atan2f(40, 40);

				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);

				pPlayer->bUse = true;

				if (g_posPlayer.nCounterState <= 0)
				{
					g_posPlayer.state = PLAYERSTATE_NOMAL;
				}
			}

			//�t�@�C���[���
			if (g_posPlayer.state == PLAYERSTATE_FIRE)
			{
				//�Ίp���̒���
				pPlayer->g_fLengthPlayer = sqrtf(40 * 40 + 80 * 80);

				//�Ίp���̊p�x
				pPlayer->g_fAnglePlayer = atan2f(40, 70);

				//if (GetKeyboardTrigger(DIK_F) == true)//�v���C���[�̉�]
				//{
				//	//�v���C���[�̒e����
				//	for (int nCntAppear = 0; nCntAppear < 1; nCntAppear++)//�p�[�e�B�N������
				//	{
				//		D3DXVECTOR3 pos;
				//		int nLife;
				//		D3DXVECTOR3 move;
				//		float fAngle;
				//		D3DXCOLOR col;

				//		col = D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f);//�J���[
				//		pos = pPlayer->Pos;//�ʒu
				//		nLife = 100 + rand() % 200;//�����_���Ŏ���
				//		fAngle = (float)(rand() % 158 - 78) / 100.0f;//�e�͈̔�
				//		move.x = sinf(D3DX_PI*0.5)*4.0f;//�e�̈ړ���
				//		move.y = cosf(D3DX_PI*0.5)*4.0f;//�e�̈ړ���
				//		SetBullet(pos, move, nLife ,col,4);
				//	}
				//}

				//�G�ƃv���C���[�̏���
				if (pEnemy->bUse == true)
				{
					for (int nCntEnemy = 0; nCntEnemy < 256; nCntEnemy++, pEnemy++)
					{
						if (pPlayer->oldPos.x >= pEnemy->Pos.x - 50 && pPlayer->oldPos.x <= pEnemy->Pos.x + 50 &&
							pPlayer->Pos.y >= pEnemy->Pos.y - 50 && pPlayer->Pos.y <= pEnemy->Pos.y + 50)
						{
							g_posPlayer.state = PLAYERSTATE_DAMAGE;
						}
					}
				}
				
				//�v���C���[�ƃt�@�C�A�[�o�[�̔���
				if (pEffect->nType == 3)
				{
					if (pEffect->bUse == true)
					{
						for (int nCntEnemy = 0; nCntEnemy < 256; nCntEnemy++, pEffect++)
						{
							if (pPlayer->Pos.x >= pEffect->pos.x - 40 && pPlayer->Pos.x <= pEffect->pos.x + 40 &&
								pPlayer->Pos.y >= pEffect->pos.y - 40 && pPlayer->Pos.y <= pEffect->pos.y + 40)
							{
								g_posPlayer.state = PLAYERSTATE_DAMAGE;
							}
						}
					}
				}
			}

			else if (g_posPlayer.state == PLAYERSTATE_FREAZ)
			{
				//�Ίp���̒���
				pPlayer->g_fLengthPlayer = sqrtf(30 * 30 + 70 * 70);

				//�Ίp���̊p�x
				pPlayer->g_fAnglePlayer = atan2f(30, 70);

				if (GetKeyboardTrigger(DIK_F) == true)//�v���C���[�̉�]
				{
					for (int nCntAppear = 0; nCntAppear < 1; nCntAppear++)//�p�[�e�B�N������
					{
						D3DXVECTOR3 pos;
						int nLife;
						D3DXVECTOR3 move;
						float fAngle;
						D3DXCOLOR col;

						col = D3DXCOLOR(0.2f, 0.2f, 1.0f, 1.0f);//�J���[
						pos = pPlayer->Pos;//�ʒu
						nLife = 200 + rand() % 300;//�����_���Ŏ���
						fAngle = (float)(rand() % 628 - 314) / 100.0f;//�e�͈̔�
						move.x = sinf(D3DX_PI*0.5)*4.0f;//�e�̈ړ���
						move.y = cosf(D3DX_PI*0.5)*4.0f;//�e�̈ړ���
						SetBullet(pos, move, nLife, col, 1);
					}
				}
				if (pEnemy->bUse == true)
				{
					for (int nCntEnemy = 0; nCntEnemy < 256; nCntEnemy++, pEnemy++)
					{
						if (pPlayer->oldPos.x >= pEnemy->Pos.x - 50 && pPlayer->oldPos.x <= pEnemy->Pos.x + 50 &&
							pPlayer->Pos.y >= pEnemy->Pos.y - 50 && pPlayer->Pos.y <= pEnemy->Pos.y + 50)
						{
							g_posPlayer.state = PLAYERSTATE_DAMAGE;
						}
					}
				}
			}

			else if (g_posPlayer.state == PLAYERSTATE_STAR)
			{
				pPlayer->nCounterStateStar--;
				pPlayer->bUse = true;
				if (GetKeyboardPress(DIK_D) == true)//�E�ɐi��
				{
					//�ړ���
					for (int nCntExplosion = 0; nCntExplosion < 256; nCntExplosion++, pBlock++,pExplosion++)
					{
						//�v���C���[���������Ƃ��u���b�N��
						pBlock->move.x -= 2.25f;

						pExplosion->move.x -= 2.25f;
					}
				}
				if (GetKeyboardPress(DIK_A) == true)//���ɐi��
				{
					//�ړ���
					for (int nCntExplosion = 0; nCntExplosion < 256; nCntExplosion++, pBlock++, pExplosion++)
					{
						//�v���C���[���������Ƃ��u���b�N��
						pBlock->move.x += 2.25f;

						pExplosion->move.x += 2.25f;
					}
				}
				if (pPlayer->nCounterStateStar <= 0)
				{
					pPlayer->state = PLAYERSTATE_NOMAL;
				}

				D3DXVECTOR3 pos;
				int nLife;
				D3DXVECTOR3 move;
				float fAngle;
				D3DXCOLOR col;

				col = D3DXCOLOR(0.2f, 0.2f, 1.0f, 1.0f);//�J���[
				pos = pPlayer->Pos;//�ʒu
				nLife = 10 + rand() % 30;//�����_���Ŏ���
				fAngle = (float)(rand() % 628 - 314) / 100.0f;//�e�͈̔�
				move.x = sinf(fAngle)*4.0f;//�e�̈ړ���
				move.y = cosf(fAngle)*4.0f;//�e�̈ړ���
				SetEffect(pos, nLife, 0, move);
			}


			if (GetKeyboardPress(DIK_D) == true)//�E�ɐi��
			{
				//�ړ���
				//g_posPlayer.move.x += sinf(D3DX_PI*0.5f) * 1.0f;

				g_posPlayer.g_nCounterAnim++;//�A�j���[�V�������v���X����Ă���

				if ((g_posPlayer.g_nCounterAnim % 5) == 0)//10�Ŋ���؂��
				{
					g_posPlayer.g_nPatternAnim++;

					g_posPlayer.g_nseetAnim = (g_posPlayer.g_nseetAnim + 1) % 8;

					pVtx[0].tex = D3DXVECTOR2(0.0f + 0.25f*g_posPlayer.g_nseetAnim, 0.5f);
					pVtx[1].tex = D3DXVECTOR2(0.0f + 0.25f*g_posPlayer.g_nseetAnim, 0.0f);
					pVtx[2].tex = D3DXVECTOR2(0.25f + 0.25f*g_posPlayer.g_nseetAnim, 0.5f);
					pVtx[3].tex = D3DXVECTOR2(0.25f + 0.25f*g_posPlayer.g_nseetAnim, 0.0f);
				}
			}

			if (GetKeyboardPress(DIK_A) == true)//���ɐi��
			{
				//�ړ���
				//g_posPlayer.move.x += -sinf(D3DX_PI*0.5f) * 2.0f;

				g_posPlayer.g_nCounterAnim++;//�A�j���[�V�������v���X����Ă���

				if ((g_posPlayer.g_nCounterAnim % 5) == 0)//10�Ŋ���؂��
				{
					g_posPlayer.g_nPatternAnim++;

					g_posPlayer.g_nseetAnim = (g_posPlayer.g_nseetAnim + 1) % 8;

					pVtx[0].tex = D3DXVECTOR2(0.0f + 0.25f*g_posPlayer.g_nseetAnim, 1.0f);
					pVtx[1].tex = D3DXVECTOR2(0.0f + 0.25f*g_posPlayer.g_nseetAnim, 0.5f);
					pVtx[2].tex = D3DXVECTOR2(0.25f + 0.25f*g_posPlayer.g_nseetAnim, 1.0f);
					pVtx[3].tex = D3DXVECTOR2(0.25f + 0.25f*g_posPlayer.g_nseetAnim, 0.5f);
				}
			}

			if (g_posPlayer.move.y == 0.0f)
			{
				if (GetKeyboardTrigger(DIK_SPACE) == true)//�e��ł���
				{
					//���_���̐ݒ�
					pVtx[0].tex = D3DXVECTOR2(0.25f, 0.5f);
					pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
					pVtx[2].tex = D3DXVECTOR2(0.5f, 0.5f);
					pVtx[3].tex = D3DXVECTOR2(0.5f, 0.0f);

					//�ړ���
					g_posPlayer.move.y -= sinf(D3DX_PI*0.5f) * 28.5f;
				}
			}

			
			//�d��
			g_posPlayer.move.y += 1.25f;

			//�ړ��ʂ̌���
			g_posPlayer.move.x += (0.0f - g_posPlayer.move.x) *0.5f;

			//�ʒu�X�V
			g_posPlayer.Pos.x += g_posPlayer.move.x;
			g_posPlayer.Pos.y += g_posPlayer.move.y;


			if (g_posPlayer.Pos.y >= 3080)
			{
				g_posPlayer.bUse = false;
				SetFade(FADE_OUT, MODE_RESULT);
			}
		

			//�v���C���[�̒��_���W
			pVtx[0].pos.x = g_posPlayer.Pos.x + sinf(g_rotPlayer.z - g_posPlayer.g_fAnglePlayer) * g_posPlayer.g_fLengthPlayer;
			pVtx[0].pos.y = g_posPlayer.Pos.y + cosf(g_rotPlayer.z - g_posPlayer.g_fAnglePlayer) * g_posPlayer.g_fLengthPlayer;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_posPlayer.Pos.x - sinf(g_rotPlayer.z + g_posPlayer.g_fAnglePlayer) * g_posPlayer.g_fLengthPlayer;
			pVtx[1].pos.y = g_posPlayer.Pos.y - cosf(g_rotPlayer.z + g_posPlayer.g_fAnglePlayer) * g_posPlayer.g_fLengthPlayer;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_posPlayer.Pos.x + sinf(g_rotPlayer.z + g_posPlayer.g_fAnglePlayer) * g_posPlayer.g_fLengthPlayer;
			pVtx[2].pos.y = g_posPlayer.Pos.y + cosf(g_rotPlayer.z + g_posPlayer.g_fAnglePlayer) * g_posPlayer.g_fLengthPlayer;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_posPlayer.Pos.x - sinf(g_rotPlayer.z - g_posPlayer.g_fAnglePlayer) * g_posPlayer.g_fLengthPlayer;
			pVtx[3].pos.y = g_posPlayer.Pos.y - cosf(g_rotPlayer.z - g_posPlayer.g_fAnglePlayer) * g_posPlayer.g_fLengthPlayer;
			pVtx[3].pos.z = 0.0f;

		}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffPlayer->Unlock();

}

//====================
//�v���C���[�̕`�揈��
//====================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePlayer);

	if (g_posPlayer.bUse == true)//�v���C���[���g�p���Ă��邩�ǂ���
	{
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}

}
PLAYER *GetPlayer(void)
{
	return &g_posPlayer;
}
bool HitPlayer(int nDamage)
{
	PLAYER *pPlayer;
	pPlayer = &g_posPlayer;

	ITEM *pExplosion;
	pExplosion = GetItem();

	ENEMY *pEnemy;
	pEnemy = GetEnemy();

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	g_posPlayer.nLife -= nDamage;//�̗͂���_���[�W������

	if (g_posPlayer.nLife -= nDamage)//�̗͂�0�ȉ��ɂȂ�����
	{
		g_posPlayer.state = PLAYERSTATE_DAMAGE;
	}
	return false;

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffPlayer->Unlock();
}

