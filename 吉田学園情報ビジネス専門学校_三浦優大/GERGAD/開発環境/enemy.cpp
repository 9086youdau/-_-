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
#include "sound.h"
#include "enemy.h"
#include "particle.h"
#include "effect.h"
#include "fade.h"
#include "Score.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureEnemy[3] = {};//�e�N�X�`���փ|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;//���_�o�b�t�@�ւ̃|�C���^
ENEMY g_aEnemy[256];//�G�̏��
D3DXVECTOR3 g_rotEnemy;//�G�̃T�C�Y���
float g_fLengthEnemy;//�Ίp���̒���
float g_fAngleEnemy;//�Ίp���̊p�x
int g_nData = 1;

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
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/200.png", &g_apTextureEnemy[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/enemy001.png", &g_apTextureEnemy[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/enemy002.png", &g_apTextureEnemy[2]);

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
		g_nData = 1;
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
		pVtx[2].tex = D3DXVECTOR2(0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 0.0f);

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
	pEnemy = &g_aEnemy[0];
	pPlayer = GetPlayer();

	//���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	//�Ίp���̒���
	g_fLengthEnemy = sqrtf(MAX_ENEMY_SIZE *MAX_ENEMY_SIZE + MAX_ENEMY_SIZE * MAX_ENEMY_SIZE);
	//�Ίp���̊p�x
	g_fAngleEnemy = atan2f(MAX_ENEMY_SIZE, MAX_ENEMY_SIZE);

	for (int nCntEnemy = 0; nCntEnemy < 256; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)//�G���g�p����Ă��邩�ǂ���
		{
			g_aEnemy[nCntEnemy].g_nCounterAni++;//�A�j���[�V�������v���X����Ă���

			if ((g_aEnemy[nCntEnemy].g_nCounterAni % 10) == 0)//10�Ŋ���؂��
			{
				g_aEnemy[nCntEnemy].g_nPatternAni++;

				g_aEnemy[nCntEnemy].g_nseetAni = (g_aEnemy[nCntEnemy].g_nseetAni + 1) % 10;

				pVtx[0].tex = D3DXVECTOR2(0.0f + 0.1f*g_aEnemy[nCntEnemy].g_nseetAni, 1.0f);
				pVtx[1].tex = D3DXVECTOR2(0.0f + 0.1f*g_aEnemy[nCntEnemy].g_nseetAni, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.1f + 0.1f*g_aEnemy[nCntEnemy].g_nseetAni, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.1f + 0.1f*g_aEnemy[nCntEnemy].g_nseetAni, 0.0f);

			}

			if (g_aEnemy[nCntEnemy].g_nPatternAni % 10 == 0)//�A�j���[�V������10�̔{���̎�
			{
				for (int nCntAppear = 0; nCntAppear < 7; nCntAppear++)//�p�[�e�B�N������
				{
					D3DXVECTOR3 pos;
					int nLife;
					D3DXVECTOR3 move;
					float fAngle;
					D3DXCOLOR col;

					col = D3DXCOLOR(1.0f, 0.4f, 0.4f, 1.0f);//�J���[
					pos = pEnemy->Pos;//�ʒu
					nLife = 200 + rand() % 300;//�����_���Ŏ���
					fAngle = (float)(rand() % 628 - 314) / 100.0f;//�e�͈̔�
					move.x = sinf(fAngle)*4.0f;//�e�̈ړ���
					move.y = cosf(fAngle)*4.0f;//�e�̈ړ���
					SetBullet(pos, move, nLife, col, BULLETTYPE_ENEMY_HOMING2);//�e����
				}

				if(g_aEnemy[nCntEnemy].g_nPatternAni % 40 == 0)//�A�j���[�V������40�̔{���̎�
				{
					for (int nCntAppear = 0; nCntAppear < 2; nCntAppear++)//�p�[�e�B�N������
					{
						D3DXVECTOR3 pos;
						int nLife;
						D3DXVECTOR3 move;
						float fAngle;
						D3DXCOLOR col;

						pos = pEnemy->Pos;//�ʒu
						nLife = 550;//�����_���Ŏ���
						fAngle = (float)(rand() % 157 - 78) / 100.0f;//�e�͈̔�
						move.x = sinf(fAngle)*2.0f;//�e�̈ړ���
						move.y = cosf(fAngle)*2.0f;//�e�̈ړ���
						SetBullet(pos, move, nLife, col, BULLETTYPE_ENEMY_HOMING2);//�e����
					}
				}
			}

			if (g_aEnemy[nCntEnemy].g_nPatternAni >= 100)//�A�j���[�V������100�ɂȂ�����
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

			
			else if (pEnemy->bUse == true)
			{
				if (pPlayer->Pos.x >= pEnemy->Pos.x - MAX_BULLET_SIZE && pPlayer->Pos.x <= pEnemy->Pos.x + MAX_BULLET_SIZE &&
					pPlayer->Pos.y >= pEnemy->Pos.y - MAX_BULLET_SIZE && pPlayer->Pos.y <= pEnemy->Pos.y + MAX_BULLET_SIZE)
				{
					//�p�[�e�B�N������
					for (int nCntAppear = 0; nCntAppear < 100; nCntAppear++)
					{
						D3DXVECTOR3 pos;
						int nLife;
						D3DXVECTOR3 move;
						float fAngle;

						pos = pPlayer->Pos;//�ʒu
						nLife = 10 + rand() % 20;//�����������_��
						fAngle = (float)(rand() % 628 - 314) / 100.0f;//�����͈̔�
						move.x = sinf(fAngle)*2.5f;//x���̒e�̑��x
						move.y = cosf(fAngle)*2.5f;//y���̒e�̑��x
						SetEffect(pos, nLife, move);//�G�t�F�N�g����
					}
					pPlayer->bUse = false;
					SetFade(FADE_OUT, MODE_RESULT);
				}
			}
		}

			//�ړ����̒��_���
			pVtx[0].pos.x = g_aEnemy[nCntEnemy].Pos.x + sinf(g_rotEnemy.z - g_fAngleEnemy) * g_fLengthEnemy;
			pVtx[0].pos.y = g_aEnemy[nCntEnemy].Pos.y + cosf(g_rotEnemy.z - g_fAngleEnemy) * g_fLengthEnemy;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_aEnemy[nCntEnemy].Pos.x - sinf(g_rotEnemy.z + g_fAngleEnemy) * g_fLengthEnemy;
			pVtx[1].pos.y = g_aEnemy[nCntEnemy].Pos.y - cosf(g_rotEnemy.z + g_fAngleEnemy) * g_fLengthEnemy;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_aEnemy[nCntEnemy].Pos.x + sinf(g_rotEnemy.z + g_fAngleEnemy) * g_fLengthEnemy;
			pVtx[2].pos.y = g_aEnemy[nCntEnemy].Pos.y + cosf(g_rotEnemy.z + g_fAngleEnemy) * g_fLengthEnemy;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_aEnemy[nCntEnemy].Pos.x - sinf(g_rotEnemy.z - g_fAngleEnemy) * g_fLengthEnemy;
			pVtx[3].pos.y = g_aEnemy[nCntEnemy].Pos.y - cosf(g_rotEnemy.z - g_fAngleEnemy) * g_fLengthEnemy;
			pVtx[3].pos.z = 0.0f;

			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMYSTATE_DAMAGE:
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

	pEnemy = &g_aEnemy[0];

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemy = 0; nCntEnemy < 256; nCntEnemy++,pEnemy++)
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

//==================
//�G�l�~�[�̍\���̐ݒ�
//==================
ENEMY *GetEnemy(void) 
{
	return &g_aEnemy[0];
}

//==================
//�G�l�~�[�̒e�q�b�g���̐ݒ�
//==================
bool HitEnemy(int nIdx, int nDamage)
{
	ENEMY *pEnemy;
	pEnemy = &g_aEnemy[nIdx];
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	g_aEnemy[nIdx].nLife -= nDamage;//�̗͂���_���[�W������

	if (g_aEnemy[nIdx].nLife <= 0)//�̗͂�0�ȉ��ɂȂ�����
	{
		PlaySound(SOUND_LABEL_SE_EXPLOSION);
		AddScore(99999999);
		g_aEnemy[nIdx].bUse = false;
		g_nData--;

		for (int nCntAppear = 0; nCntAppear < 300; nCntAppear++)
		{
			D3DXVECTOR3 pos;
			int nLife;
			D3DXVECTOR3 move;
			float fAngle;

			pos = pEnemy->Pos;
			nLife = 100 + rand() % 200;
			fAngle = (float)(rand() % 628 - 314) / 100.0f;
			move.x = sinf(fAngle)*1.5f;
			move.y = cosf(fAngle)*1.5f;
			SetEffect(pos, nLife, move);
		}
			if (g_nData == 0)
			{
				SetFade(FADE_OUT, MODE_RESULT);
			}
		
		return true;
	}
	else
	{
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
