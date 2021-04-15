//================================================
//
//�G�̏���[enemy.cpp]
// Author; miura yuudai
//
//================================================

//================================================
//�w�b�_�[�ǂݍ���
//================================================
#include "input.h"
#include "enemy.h"
#include "bullet.h"
#include "Player.h"
#include "Explosion.h"
#include "sound.h"
#include "enemy.h"
#include "particle.h"
#include "effect.h"
#include "fade.h"
#include "Score.h"

//================================================
//�}�N����`
//================================================
#define MAX_ENEMY (256)//�G�̍ő吔
#define MAX_TYPE_ENEMY (3)//�G�̎�ސ�
#define MAX_ENEMY_SIZE (145)//�G�̃T�C�Y
#define MAX_BULLET_SIZE (80)//�e�̃T�C�Y

//================================================
//�O���[�o���ϐ�
//================================================
LPDIRECT3DTEXTURE9 g_apTextureEnemy[MAX_TYPE_ENEMY] = {};//�e�N�X�`���փ|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;//���_�o�b�t�@�ւ̃|�C���^
ENEMY g_aEnemy[MAX_ENEMY];//�G�̏��
int g_nData = 1;//�J�E���g�ϐ�

//====================================
//�G�l�~�[�̏���������
//====================================
HRESULT InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/200.png", &g_apTextureEnemy[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/enemy001.png", &g_apTextureEnemy[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/enemy002.png", &g_apTextureEnemy[2]);

	//�O���[�o���ϐ�������
	g_nData = 1;

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].nType = 0;//�G�̃^�C�v
		g_aEnemy[nCntEnemy].bUse = false;//�g���Ă��邩�ǂ���
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NOMAL;//�G�l�~�[�̏��
		g_aEnemy[nCntEnemy].nCounterState = 0;
		g_aEnemy[nCntEnemy].nLife = 1000;//�G�̗̑�
		g_aEnemy[nCntEnemy].nCounterAni = 0;//�J�E���^�[�A�j���[�V����
		g_aEnemy[nCntEnemy].nPatternAni = 0;//�p�^�[���A�j���[�V����
		g_aEnemy[nCntEnemy].nseetAni = 0;//�V�[�g�A�j���[�V����
	}

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
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

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
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
		pVtx[2].tex = D3DXVECTOR2(0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 0.0f);

		pVtx += 4;//4���_���Ƃ��炷
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffEnemy->Unlock();

	//�Ԃ�l
	return S_OK;
}

//====================================
//�G�l�~�[�̏I������
//====================================
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

//=====================================
//�G�l�~�[�̍X�V����
//=====================================
void UpdateEnemy(void)
 {
	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	//�|�C���^�ϐ�
	ENEMY *pEnemy;
	PLAYER *pPlayer;
	pEnemy = &g_aEnemy[0];
	pPlayer = GetPlayer();

	//���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	//�A�j���[�V��������
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//�Ίp���̒���
		g_aEnemy[nCntEnemy].fLengthEnemy = sqrtf(MAX_ENEMY_SIZE *MAX_ENEMY_SIZE + MAX_ENEMY_SIZE * MAX_ENEMY_SIZE);
		//�Ίp���̊p�x
		g_aEnemy[nCntEnemy].fAngleEnemy = atan2f(MAX_ENEMY_SIZE, MAX_ENEMY_SIZE);

		if (g_aEnemy[nCntEnemy].bUse == true)//�G���g�p����Ă��邩�ǂ���
		{
			g_aEnemy[nCntEnemy].nCounterAni++;//�A�j���[�V�������v���X����Ă���

			if ((g_aEnemy[nCntEnemy].nCounterAni % 10) == 0)//10�Ŋ���؂��
			{
				g_aEnemy[nCntEnemy].nPatternAni++;//�A�j���[�V�������v���X

				g_aEnemy[nCntEnemy].nseetAni = (g_aEnemy[nCntEnemy].nseetAni + 1) % 10;

				pVtx[0].tex = D3DXVECTOR2(0.0f + 0.1f*g_aEnemy[nCntEnemy].nseetAni, 1.0f);
				pVtx[1].tex = D3DXVECTOR2(0.0f + 0.1f*g_aEnemy[nCntEnemy].nseetAni, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.1f + 0.1f*g_aEnemy[nCntEnemy].nseetAni, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.1f + 0.1f*g_aEnemy[nCntEnemy].nseetAni, 0.0f);

			}

			if (g_aEnemy[nCntEnemy].nPatternAni % 10 == 0)//�A�j���[�V������10�̔{���̎�
			{
				for (int nCntAppear = 0; nCntAppear < 7; nCntAppear++)//�p�[�e�B�N������
				{
					//�ϐ�
					D3DXVECTOR3 pos;
					int nLife;
					D3DXVECTOR3 move;
					float fAngle;
					D3DXCOLOR col;

					//�ݒ�
					col = D3DXCOLOR(1.0f, 0.4f, 0.4f, 1.0f);//�J���[
					pos = pEnemy->Pos;//�ʒu
					nLife = 200 + rand() % 300;//�����_���Ŏ���
					fAngle = (float)(rand() % 628 - 314) / 100.0f;//�e�͈̔�
					move.x = sinf(fAngle)*4.0f;//�e�̈ړ���
					move.y = cosf(fAngle)*4.0f;//�e�̈ړ���
					SetBullet(pos, move, nLife, col, BULLETTYPE_ENEMY_HOMING2);//�e����
				}

				if(g_aEnemy[nCntEnemy].nPatternAni % 40 == 0)//�A�j���[�V������40�̔{���̎�
				{
					for (int nCntAppear = 0; nCntAppear < 2; nCntAppear++)//�p�[�e�B�N������
					{
						//�ϐ�
						D3DXVECTOR3 pos;
						int nLife;
						D3DXVECTOR3 move;
						float fAngle;
						D3DXCOLOR col;

						//�ݒ�
						pos = pEnemy->Pos;//�ʒu
						nLife = 550;//�����_���Ŏ���
						fAngle = (float)(rand() % 157 - 78) / 100.0f;//�e�͈̔�
						move.x = sinf(fAngle)*2.0f;//�e�̈ړ���
						move.y = cosf(fAngle)*2.0f;//�e�̈ړ���
						SetBullet(pos, move, nLife, col, BULLETTYPE_ENEMY_HOMING2);//�e����
					}
				}
			}

			if (g_aEnemy[nCntEnemy].nPatternAni >= 100)//�A�j���[�V������100�ɂȂ�����
			{
				float fAnglee;
				fAnglee = (float)(rand() % 628 - 314) / 100.0f;

				//�ʒu�X�V
				g_aEnemy[nCntEnemy].Pos.x += pEnemy->move.x;
				g_aEnemy[nCntEnemy].Pos.y += pEnemy->move.y;

				//�G�l�~�[���ړ�
				pEnemy->move.x += sinf(fAnglee) * 0.2f;
				pEnemy->move.y += cosf(fAnglee) * 0.2f;

				//��ʒ[�̏���
				if (g_aEnemy[nCntEnemy].Pos.y + 20 >= 1030)
				{
					pEnemy->move.y *= -1;
				}
				else if (g_aEnemy[nCntEnemy].Pos.y - 20 <= 50)
				{
					pEnemy->move.y *= -1;
				}

				//��ʒ[�̏���
				if (g_aEnemy[nCntEnemy].Pos.x + 20 >= 1220)
				{
					pEnemy->move.x *= -1;
				}
				else if (g_aEnemy[nCntEnemy].Pos.x - 20 <= 50)
				{
					pEnemy->move.x *= -1;
				}

			//�v���C���[�ƓG���Փ˂������̔���
			else if (pEnemy->bUse == true)
			{
				if (pPlayer->Pos.x >= pEnemy->Pos.x - MAX_BULLET_SIZE && pPlayer->Pos.x <= pEnemy->Pos.x + MAX_BULLET_SIZE &&
					pPlayer->Pos.y >= pEnemy->Pos.y - MAX_BULLET_SIZE && pPlayer->Pos.y <= pEnemy->Pos.y + MAX_BULLET_SIZE)
				{
					//�p�[�e�B�N������
					for (int nCntAppear = 0; nCntAppear < 100; nCntAppear++)
					{
						//�ϐ�
						D3DXVECTOR3 pos;
						int nLife;
						D3DXVECTOR3 move;
						float fAngle;

						//�ݒ�
						pos = pPlayer->Pos;//�ʒu
						nLife = 10 + rand() % 20;//�����������_��
						fAngle = (float)(rand() % 628 - 314) / 100.0f;//�����͈̔�
						move.x = sinf(fAngle)*2.5f;//x���̒e�̑��x
						move.y = cosf(fAngle)*2.5f;//y���̒e�̑��x
						SetEffect(pos, nLife, move);//�G�t�F�N�g����
					}
					pPlayer->bUse = false;//�g���Ă��邩
					SetFade(FADE_OUT, MODE_RESULT);//���������烊�U���g�Ƀt�F�[�h�A�E�g
				}
			}
		}

			//�ړ����̒��_���
			pVtx[0].pos.x = g_aEnemy[nCntEnemy].Pos.x + sinf(g_aEnemy[nCntEnemy].rotEnemy.z - g_aEnemy[nCntEnemy].fAngleEnemy) * g_aEnemy[nCntEnemy].fLengthEnemy;
			pVtx[0].pos.y = g_aEnemy[nCntEnemy].Pos.y + cosf(g_aEnemy[nCntEnemy].rotEnemy.z - g_aEnemy[nCntEnemy].fAngleEnemy) * g_aEnemy[nCntEnemy].fLengthEnemy;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_aEnemy[nCntEnemy].Pos.x - sinf(g_aEnemy[nCntEnemy].rotEnemy.z + g_aEnemy[nCntEnemy].fAngleEnemy) * g_aEnemy[nCntEnemy].fLengthEnemy;
			pVtx[1].pos.y = g_aEnemy[nCntEnemy].Pos.y - cosf(g_aEnemy[nCntEnemy].rotEnemy.z + g_aEnemy[nCntEnemy].fAngleEnemy) * g_aEnemy[nCntEnemy].fLengthEnemy;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_aEnemy[nCntEnemy].Pos.x + sinf(g_aEnemy[nCntEnemy].rotEnemy.z + g_aEnemy[nCntEnemy].fAngleEnemy) * g_aEnemy[nCntEnemy].fLengthEnemy;
			pVtx[2].pos.y = g_aEnemy[nCntEnemy].Pos.y + cosf(g_aEnemy[nCntEnemy].rotEnemy.z + g_aEnemy[nCntEnemy].fAngleEnemy) * g_aEnemy[nCntEnemy].fLengthEnemy;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_aEnemy[nCntEnemy].Pos.x - sinf(g_aEnemy[nCntEnemy].rotEnemy.z - g_aEnemy[nCntEnemy].fAngleEnemy) * g_aEnemy[nCntEnemy].fLengthEnemy;
			pVtx[3].pos.y = g_aEnemy[nCntEnemy].Pos.y - cosf(g_aEnemy[nCntEnemy].rotEnemy.z - g_aEnemy[nCntEnemy].fAngleEnemy) * g_aEnemy[nCntEnemy].fLengthEnemy;
			pVtx[3].pos.z = 0.0f;

			//�G�̏��
			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMYSTATE_DAMAGE://�_���[�W��ԂɂȂ�����F��ύX
				g_aEnemy[nCntEnemy].nCounterState--;
				if (g_aEnemy[nCntEnemy].nCounterState <= 0)
				{
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_NOMAL;
					//���_�J���[�̐ݒ�
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				}
				break;
			}
		}
		pVtx += 4;//4���_���Ƃ��炷
	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffEnemy->Unlock();
  }
//====================================
//�G�l�~�[�̕`�揈��
//====================================
void DrawEnemy(void)
{
	//�|�C���^�ϐ�
	ENEMY *pEnemy;
	pEnemy = &g_aEnemy[0];

	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�|���S���̕`��
	for (int nCutEnemy = 0; nCutEnemy < MAX_ENEMY; nCutEnemy++,pEnemy++)
	{
		//�e�N�X�`���ݒ�
		pDevice->SetTexture(0, g_apTextureEnemy[pEnemy->nType]);

		if(pEnemy->bUse == true)//�e���g�p���Ă��邩�ǂ���
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCutEnemy*4, 2);
		}
	}
}

//======================================
//�G�l�~�[�̐ݒ�
//======================================
void SETENEMY(D3DXVECTOR3 Pos, int nType)
{
	//�|�C���^�ϐ�
	ENEMY *pEnemy;
	pEnemy = &g_aEnemy[0];

	//�\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++,pEnemy++)
	{
		if (pEnemy->bUse == false)//�e���g�p���Ă��邩�ǂ���
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

		pVtx += 4;//4���_���Ƃ��炷
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffEnemy->Unlock();
}

//===================================
//�G�l�~�[�̍\���̐ݒ�
//===================================
ENEMY *GetEnemy(void) 
{
	return &g_aEnemy[0];
}

//==========================================
//�G�l�~�[�̒e�q�b�g���̐ݒ�
//==========================================
bool HitEnemy(int nIdx, int nDamage)
{
	//�|�C���^�ϐ�
	ENEMY *pEnemy;
	pEnemy = &g_aEnemy[nIdx];

	//�\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	g_aEnemy[nIdx].nLife -= nDamage;//�̗͂���_���[�W������

	if (g_aEnemy[nIdx].nLife <= 0)//�̗͂�0�ȉ��ɂȂ�����
	{
		PlaySound(SOUND_LABEL_SE_EXPLOSION);
		AddScore(99999999);//�X�R�A��99999999����
		g_aEnemy[nIdx].bUse = false;//true����false��
		g_nData--;//�J�E���g�ϐ�

		//�|������ɂł�G�t�F�N�g
		for (int nCntAppear = 0; nCntAppear < 300; nCntAppear++)
		{
			//�ϐ�
			D3DXVECTOR3 pos;
			int nLife;
			D3DXVECTOR3 move;
			float fAngle;

			//�ݒ�
			pos = pEnemy->Pos;
			nLife = 100 + rand() % 200;
			fAngle = (float)(rand() % 628 - 314) / 100.0f;
			move.x = sinf(fAngle)*1.5f;
			move.y = cosf(fAngle)*1.5f;
			SetEffect(pos, nLife, move);
		}
		//0�ɂȂ�����t�F�[�h�A�E�g
		if (g_nData == 0)
		{
			SetFade(FADE_OUT, MODE_RESULT);
		}
		
		return true;
	}
	else
	{
		//�G�ɒe������������100�X�R�A
			AddScore(100);
			g_aEnemy[nIdx].state = ENEMYSTATE_DAMAGE;
			g_aEnemy[nIdx].nCounterState = 10;

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);

	}
		return false;
	
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffEnemy->Unlock();
}
int GetEnemyNumber(void)
{
	return g_nData;
}
