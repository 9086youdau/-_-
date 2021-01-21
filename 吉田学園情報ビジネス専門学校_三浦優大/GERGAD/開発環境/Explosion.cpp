#include "Explosion.h"

//makuro
#define MAX_EXPLOSION_SIZE (100)
//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion;//���_�|�C���^
EXPLOSION g_aExplosion[256];//�e�̏��

HRESULT InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();


	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/explosion000.png", &g_pTextureExplosion);

	for (int nCntExplosion = 0; nCntExplosion < 256; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
		g_aExplosion[nCntExplosion].bUse = false;
	}

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 256, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffExplosion, NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntExplosion = 0; nCntExplosion < 256; nCntExplosion++)
	{

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 60, g_aExplosion[nCntExplosion].pos.y + 60, 0.0f);//2D��0.0�Œ�
		pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 60, g_aExplosion[nCntExplosion].pos.y - 60, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 60, g_aExplosion[nCntExplosion].pos.y + 60, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 60, g_aExplosion[nCntExplosion].pos.y - 60, 0.0f);


		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = g_aExplosion[nCntExplosion].col;
		pVtx[1].col = g_aExplosion[nCntExplosion].col;
		pVtx[2].col = g_aExplosion[nCntExplosion].col;
		pVtx[3].col = g_aExplosion[nCntExplosion].col;

		//���_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.125f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f, 0.0f);

		pVtx += 4;//4���_���Ƃ��炷
	}
	g_pVtxBuffExplosion->Unlock();
	return  S_OK;
}
void UninitExplosion(void)
{
	//�e�N�X�`���̊J��
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}
void UpdateExplosion(void)
{
	EXPLOSION *pExplosion;
	pExplosion = &g_aExplosion[0];
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);


	for (int nCntExplosion = 0; nCntExplosion < 256; nCntExplosion++, pExplosion++)
	{
		if (pExplosion->bUse == true)//�e���g�p���Ă��邩�ǂ���
		{
			
			////���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 60, g_aExplosion[nCntExplosion].pos.y + 60, 0.0f);//2D��0.0�Œ�
			pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 60, g_aExplosion[nCntExplosion].pos.y - 60, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 60, g_aExplosion[nCntExplosion].pos.y + 60, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 60, g_aExplosion[nCntExplosion].pos.y - 60, 0.0f);

			//��ʊO�`�F�b�N
			//if (pExplosion->pos.y < -10)
			{
				//pExplosion->bUse = false;
			}

			g_aExplosion[nCntExplosion].g_nCounterAnim++;
			if ((g_aExplosion[nCntExplosion].g_nCounterAnim % 3) == 0)
			{
				g_aExplosion[nCntExplosion].g_nPatternAnim++;
				
				g_aExplosion[nCntExplosion].g_nseetAnim = (g_aExplosion[nCntExplosion].g_nseetAnim + 1) % 10;

				pVtx[0].tex = D3DXVECTOR2(0.0f + 0.125f*g_aExplosion[nCntExplosion].g_nseetAnim, 1.0f);
				pVtx[1].tex = D3DXVECTOR2(0.0f + 0.125f*g_aExplosion[nCntExplosion].g_nseetAnim, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.125f + 0.125f*g_aExplosion[nCntExplosion].g_nseetAnim, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.125f + 0.125f*g_aExplosion[nCntExplosion].g_nseetAnim, 0.0f);
				if (g_aExplosion[nCntExplosion].g_nPatternAnim > 4)
				{
					pExplosion->bUse = false;
					g_aExplosion[nCntExplosion].g_nPatternAnim = 0;
					g_aExplosion[nCntExplosion].g_nCounterAnim = 0;
				}
			}
			
		}
		//4���_���Ƃ��炷
		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffExplosion->Unlock();
}

void DrawExplosion (void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int Count;
	Count = 0;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureExplosion);

	for (int nCntExplosion = 0; nCntExplosion < 256; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, Count, 2);
		}

		Count += 4;
	}
}
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col)//�e�̐ݒ�
{
	EXPLOSION *pBullet;
	VERTEX_2D *pVtx;

	pBullet = &g_aExplosion[0];

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntExplosion = 0; nCntExplosion < 256; nCntExplosion++, pBullet++)
	{
		if (pBullet->bUse == false)//�e���g�p���Ă��邩�ǂ���
		{
			//�ʒu�ݒ�
			g_aExplosion[nCntExplosion].pos = pos;

			g_aExplosion[nCntExplosion].col = col;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 60, g_aExplosion[nCntExplosion].pos.y + 60, 0.0f);//2D��0.0�Œ�
			pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 60, g_aExplosion[nCntExplosion].pos.y - 60, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 60, g_aExplosion[nCntExplosion].pos.y + 60, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 60, g_aExplosion[nCntExplosion].pos.y - 60, 0.0f);

			//�e�̎g�p
			pBullet->bUse = true;
			break;
		}

		//4���_���Ƃ��炷
		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffExplosion->Unlock();
}