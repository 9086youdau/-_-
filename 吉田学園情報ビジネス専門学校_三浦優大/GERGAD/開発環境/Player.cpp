//================================================
//
//�v���C���[����[Player.h]
// Author; miura yuudai
//
//================================================
#include "Player.h"
#include "bullet.h"
#include "sound.h"
#include "effect.h"
#include "input.h"
#include "enemy.h"
#include "bullet.h"
#include "fade.h"

//==============
//�O���[�o���ϐ�
//==============
LPDIRECT3DTEXTURE9 g_pTexturePlayer[2] = {};//�e�N�X�`�����
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;//���_���
PLAYER g_posPlayer;//�v���C���[���
D3DXVECTOR3 g_rotPlayer;//��]��
D3DXVECTOR3 g_movePlayer;//�ړ���
int g_nCounterAnim;//�A�j���[�V����
int g_nPatternAnim;//�A�j���[�V����
int g_nseetAnim;//�A�j���[�V����
float g_fLengthPlayer;//�Ίp���̒���
float g_fAnglePlayer;//�Ίp���̊p�x
int g_nCnt;//�e�̃J�E���g�ϐ�
int g_aData = GetEnemyNumber();
int g_nDataa;

//====================
//�|���S���̏���������
//====================
HRESULT InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ddd.png", &g_pTexturePlayer[0]);

	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/slow.png", &g_pTexturePlayer[1]);

	//�ϐ�������
	g_nCounterAnim = 0;
	g_nPatternAnim = 0;
	g_nseetAnim = 0;
	g_posPlayer.bUse = true;
	g_posPlayer.Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_posPlayer.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_posPlayer.nLife = 4;
	g_posPlayer.nType = 0;
	g_nCnt = 0;
	g_nDataa = 1;
	g_posPlayer.state = PLAYERSTATE_NOMAL;

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
	g_posPlayer.Pos = D3DXVECTOR3(550, 770, 0.0f);

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

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffPlayer->Unlock();

	return S_OK;
}

//==================
//�v���C���[�̏I������
//==================
void UninitPlayer(void)
{
	for (int nCntPlayer = 0; nCntPlayer < 2; nCntPlayer++)
	{
		//�e�N�X�`���̊J��
		if (g_pTexturePlayer[nCntPlayer] != NULL)
		{
			g_pTexturePlayer[nCntPlayer]->Release();
			g_pTexturePlayer[nCntPlayer] = NULL;
		}
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
	BULLET pBullet;
	PLAYER *pPolygon;
	pPolygon = &g_posPlayer;
	g_nCnt++;

	//���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//�ʒu�X�V
	g_posPlayer.Pos.x += g_posPlayer.move.x;
	g_posPlayer.Pos.y += g_posPlayer.move.y;

	if (g_posPlayer.bUse == true)//�g�p���Ă��邩
	{
		//�Ίp���̒���
		g_fLengthPlayer = sqrtf(100 * 100 + 100 * 100);
		//�Ίp���̊p�x
		g_fAnglePlayer = atan2f(100, 100);

		pPolygon->nType = 0;

		if (GetKeyboardPress(DIK_D) == true)//�E�ɐi��
		{
			//�ړ���
			g_posPlayer.Pos.x += sinf(D3DX_PI*0.5f) * 5.5f;
			if (GetKeyboardPress(DIK_LSHIFT) == true)//�E�ɐi��
			{
				pPolygon->nType = 1;

				//�ړ���
				g_posPlayer.Pos.x += sinf(D3DX_PI*0.5f) * -2.5f;
			}
		}

		if (GetKeyboardPress(DIK_A) == true)//���ɐi��
		{
			//�ړ���
			g_posPlayer.Pos.x += -sinf(D3DX_PI*0.5f) * 5.5f;
			if (GetKeyboardPress(DIK_LSHIFT) == true)//�E�ɐi��
			{
				pPolygon->nType = 1;

				//�ړ���
				g_posPlayer.Pos.x += sinf(D3DX_PI*0.5f) * 2.5f;
			}
		}

		if (GetKeyboardPress(DIK_S) == true)//���ɐi��
		{
			//�ړ���
			g_posPlayer.Pos.y += sinf(D3DX_PI*0.5f) * 5.5f;
			if (GetKeyboardPress(DIK_LSHIFT) == true)//�E�ɐi��
			{
				pPolygon->nType = 1;

				//�ړ���
				g_posPlayer.Pos.y += sinf(D3DX_PI*0.5f) * -2.5f;
			}
		}

		if (GetKeyboardPress(DIK_W) == true)//��ɐi��
		{
			//�ړ���
			g_posPlayer.Pos.y += -sinf(D3DX_PI*0.5f) * 5.5f;
			if (GetKeyboardPress(DIK_LSHIFT) == true)//�E�ɐi��
			{
				pPolygon->nType = 1;

				//�ړ���
				g_posPlayer.Pos.y += sinf(D3DX_PI*0.5f) * 2.5f;
			}
		}

		if (GetKeyboardPress(DIK_K) == true)//�v���C���[�̉�]
		{
			//��]��
			g_rotPlayer.z += (D3DX_PI / 18);
			if (g_rotPlayer.z > D3DX_PI)
			{
				g_rotPlayer.z -= D3DX_PI*2.0f;
			}
		}

		if (GetKeyboardTrigger(DIK_SPACE) == true)//�e��ł���
		{
			if (GetKeyboardPress(DIK_LSHIFT) == true)//
			{
				for (int nCntAppear = 0; nCntAppear < 10; nCntAppear++)
				{
					D3DXVECTOR3 pos;
					int nLife;
					D3DXVECTOR3 move;
					D3DXCOLOR col;
					float fAngle;

					col = D3DXCOLOR(1.0f, 0.4f, 0.4f, 0.5f);//�F
					pos = g_posPlayer.Pos;//���ˈʒu
					nLife = 300;//�e�̎���
					fAngle = (float)(rand() % 628 - 314) / 100.0f;//�e�͈̔�
					move.x = sinf(fAngle)*7.5f;//�ړ���
					move.y = cosf(fAngle)*7.5f;//�ړ���
					SetBullet(pos, move, nLife, col, BULLETTYPE_ENEMY_HOMING);//�e����
				}
			}
			else if(GetKeyboardTrigger(DIK_SPACE) == true)//�e�̊Ԋu
			{
					D3DXVECTOR3 pos;
					int nLife;
					D3DXVECTOR3 move;
					D3DXCOLOR col;

					col = D3DXCOLOR(1.0f, 0.4f, 0.4f, 0.5f);//�F
					pos = g_posPlayer.Pos;//���ˈʒu
					nLife = 200;//�e�̎���
					move.x = sinf(D3DX_PI)*7.5f;//�ړ���
					move.y = cosf(D3DX_PI)*7.5f;//�ړ���
					SetBullet(pos, move, nLife, col, BULLETTYPE_ENEMY_HOMING);//�e����
			}
		}

		//��ʒ[�̔�������
		if (g_posPlayer.Pos.x + 20 >= 1220)
		{
			//�p�[�e�B�N������
			for (int nCntAppear = 0; nCntAppear < 50; nCntAppear++)
			{
				D3DXVECTOR3 pos;
				int nLife;
				D3DXVECTOR3 move;
				float fAngle;

				pos = pPolygon->Pos;//�ʒu
				nLife = 10 + rand() % 20;//�����������_��
				fAngle = (float)(rand() % 628 - 314) / 100.0f;//�����͈̔�
				move.x = sinf(fAngle)*2.5f;//x���̒e�̑��x
				move.y = cosf(fAngle)*2.5f;//y���̒e�̑��x
				SetEffect(pos, nLife, move);//�G�t�F�N�g����
			}
			pPolygon->bUse = false;//�g�p���Ă��Ȃ�
			SetFade(FADE_OUT, MODE_RESULT);
		}

		//��ʒ[�̔�������
		else if (g_posPlayer.Pos.x - 20 <= 50)
		{
			//�p�[�e�B�N������
			for (int nCntAppear = 0; nCntAppear < 50; nCntAppear++)
			{
				D3DXVECTOR3 pos;
				int nLife;
				D3DXVECTOR3 move;
				float fAngle;

				pos = pPolygon->Pos;//�ʒu
				nLife = 10 + rand() % 20;//�����������_��
				fAngle = (float)(rand() % 628 - 314) / 100.0f;//�����͈̔�
				move.x = sinf(fAngle)*2.5f;//x���̒e�̑��x
				move.y = cosf(fAngle)*2.5f;//y���̒e�̑��x
				SetEffect(pos, nLife, move);//�G�t�F�N�g����
			}
			pPolygon->bUse = false;//�g�p���Ă��Ȃ�
			if (g_aData == 1)
			{
				SetFade(FADE_OUT, MODE_RESULT);
			}
		}

		//��ʒ[�̔�������
		if (g_posPlayer.Pos.y - 30 <= 50)
		{
			//�p�[�e�B�N������
			for (int nCntAppear = 0; nCntAppear < 50; nCntAppear++)
			{
				D3DXVECTOR3 pos;
				int nLife;
				D3DXVECTOR3 move;
				float fAngle;

				pos = pPolygon->Pos;//�ʒu
				nLife = 10 + rand() % 20;//�����������_��
				fAngle = (float)(rand() % 628 - 314) / 100.0f;//�����͈̔�
				move.x = sinf(fAngle)*2.5f;//x���̒e�̑��x
				move.y = cosf(fAngle)*2.5f;//y���̒e�̑��x
				SetEffect(pos, nLife, move);//�G�t�F�N�g����
			}
			pPolygon->bUse = false;//�g�p���Ă��Ȃ�
			SetFade(FADE_OUT, MODE_RESULT);
		}

		//��ʒ[�̔�������
		else if (g_posPlayer.Pos.y + 30 >= 1030)
		{
			//�p�[�e�B�N������
			for (int nCntAppear = 0; nCntAppear < 50; nCntAppear++)
			{
				D3DXVECTOR3 pos;
				int nLife;
				D3DXVECTOR3 move;
				float fAngle;

				pos = pPolygon->Pos;//�ʒu
				nLife = 10 + rand() % 20;//�����������_��
				fAngle = (float)(rand() % 628 - 314) / 100.0f;//�����͈̔�
				move.x = sinf(fAngle)*2.5f;//x���̒e�̑��x
				move.y = cosf(fAngle)*2.5f;//y���̒e�̑��x
				SetEffect(pos, nLife, move);//�G�t�F�N�g����
			}

			pPolygon->bUse = false;//�g�p���Ă��Ȃ�
			SetFade(FADE_OUT, MODE_RESULT);
		}

		//�v���C���[�̒��_���W
		pVtx[0].pos.x = g_posPlayer.Pos.x + sinf(g_rotPlayer.z - g_fAnglePlayer) * g_fLengthPlayer;
		pVtx[0].pos.y = g_posPlayer.Pos.y + cosf(g_rotPlayer.z - g_fAnglePlayer) * g_fLengthPlayer;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_posPlayer.Pos.x - sinf(g_rotPlayer.z + g_fAnglePlayer) * g_fLengthPlayer;
		pVtx[1].pos.y = g_posPlayer.Pos.y - cosf(g_rotPlayer.z + g_fAnglePlayer) * g_fLengthPlayer;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_posPlayer.Pos.x + sinf(g_rotPlayer.z + g_fAnglePlayer) * g_fLengthPlayer;
		pVtx[2].pos.y = g_posPlayer.Pos.y + cosf(g_rotPlayer.z + g_fAnglePlayer) * g_fLengthPlayer;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_posPlayer.Pos.x - sinf(g_rotPlayer.z - g_fAnglePlayer) * g_fLengthPlayer;
		pVtx[3].pos.y = g_posPlayer.Pos.y - cosf(g_rotPlayer.z - g_fAnglePlayer) * g_fLengthPlayer;
		pVtx[3].pos.z = 0.0f;

		switch (g_posPlayer.state)
		{
		case ENEMYSTATE_DAMAGE:
			g_posPlayer.nCounterState--;
			if (g_posPlayer.nCounterState <= 0)
			{
				g_posPlayer.state = PLAYERSTATE_NOMAL;
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			}
			break;
		}
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffPlayer->Unlock();

}

//====================
//�v���C���[�̕`�揈��
//====================
void DrawPlayer(void)
{
	PLAYER *pPolygon;
	pPolygon = &g_posPlayer;

	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePlayer[pPolygon->nType]);

	if (g_posPlayer.bUse == true)//�v���C���[���g�p���Ă��邩�ǂ���
	{
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}

}

//=================
//�v���C���[�̐ݒ�
//=================
void SetPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife)
{
	PLAYER *pPolygon;
	VERTEX_2D *pVtx;

	pPolygon = &g_posPlayer;

	//���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	if (pPolygon->bUse == true)//�v���C���[���g�p���Ă��邩�ǂ���
	{
		//�ʒu�ݒ�
		g_posPlayer.Pos = pos;

		//���_���W�̐ݒ�
		pVtx[0].pos.x = g_posPlayer.Pos.x + sinf(g_rotPlayer.z - g_fAnglePlayer) * g_fLengthPlayer;
		pVtx[0].pos.y = g_posPlayer.Pos.y + cosf(g_rotPlayer.z - g_fAnglePlayer) * g_fLengthPlayer;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_posPlayer.Pos.x - sinf(g_rotPlayer.z + g_fAnglePlayer) * g_fLengthPlayer;
		pVtx[1].pos.y = g_posPlayer.Pos.y - cosf(g_rotPlayer.z + g_fAnglePlayer) * g_fLengthPlayer;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_posPlayer.Pos.x + sinf(g_rotPlayer.z + g_fAnglePlayer) * g_fLengthPlayer;
		pVtx[2].pos.y = g_posPlayer.Pos.y + cosf(g_rotPlayer.z + g_fAnglePlayer) * g_fLengthPlayer;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_posPlayer.Pos.x - sinf(g_rotPlayer.z - g_fAnglePlayer) * g_fLengthPlayer;
		pVtx[3].pos.y = g_posPlayer.Pos.y - cosf(g_rotPlayer.z - g_fAnglePlayer) * g_fLengthPlayer;
		pVtx[3].pos.z = 0.0f;


		//�e�̎g�p
		pPolygon->bUse = true;

	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffPlayer->Unlock();

}

bool HitPlayer(int nDamage)
{
	PLAYER *pPlayer;
	pPlayer = &g_posPlayer;
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	g_posPlayer.nLife -= nDamage;//�̗͂���_���[�W������

	if (g_posPlayer.nLife <= 0)//�̗͂�0�ȉ��ɂȂ�����
	{
		PlaySound(SOUND_LABEL_SE_EXPLOSION);
		g_posPlayer.bUse = false;
		g_nDataa--;

		for (int nCntAppear = 0; nCntAppear < 100; nCntAppear++)
		{
			D3DXVECTOR3 pos;
			int nLife;
			D3DXVECTOR3 move;
			float fAngle;

			pos = pPlayer->Pos;
			nLife = 100 + rand() % 200;
			fAngle = (float)(rand() % 628 - 314) / 100.0f;
			move.x = sinf(fAngle)*1.5f;
			move.y = cosf(fAngle)*1.5f;
			SetEffect(pos, nLife, move);
		}
		if (g_nDataa == 0)
		{
			SetFade(FADE_OUT, MODE_RESULT);
		}

		return true;
	}
	else
	{
		g_posPlayer.state = PLAYERSTATE_DAMAGE;
		g_posPlayer.nCounterState = 20;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);

	}
	return false;

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffPlayer->Unlock();
}

//=====================
//�\���̃v���C���[�̐ݒ�
//=====================
PLAYER *GetPlayer(void)
{
	return &g_posPlayer;
}

