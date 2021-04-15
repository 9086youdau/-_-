//================================================
//
//�J��������[Camera.h]
// Author; miura yuudai
//
//================================================
#include "camera.h"
#include "input.h"
#include "model.h"
#include "gamepad.h"

//==================
//�O���[�o���ϐ�
//==================
Camera g_camera;//�J�����̏��
float g_Camera;

//=====================================
//����������
//=====================================
void InitCamera(void)
{
	g_camera.PosV = D3DXVECTOR3(100.0f, 150.0f, -200.0f);
	g_camera.PosR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.VecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_camera.moveV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.moveR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.rot.y = 0.0f;
	g_camera.fLength = 400.0f;
}
//=====================================
//�I������
//=====================================
void UninitCamera(void)
{

}
//=====================================
//�X�V����
//=====================================
void UpdateCamera(void)
{
	Player *pModel;
	pModel = GetModel();

	D3DXVECTOR3 vec;

	//�����_�ړ�
	if (IsButtonPush(KEYINFO_CAMERA_FRONT) == true)
	{
		g_camera.rot.y -= 0.05f;
		g_camera.PosV.x = g_camera.PosR.x - sinf(D3DX_PI + g_camera.rot.y) * 200;
		g_camera.PosV.z = g_camera.PosR.z + cosf(D3DX_PI + g_camera.rot.y) * 200;
	}

	if (IsButtonPush(KEYINFO_WEAPON_DROP) == true)
	{
		g_camera.rot.y += 0.05f;
		g_camera.PosV.x = g_camera.PosR.x - sinf(D3DX_PI + g_camera.rot.y) * 200;
		g_camera.PosV.z = g_camera.PosR.z + cosf(D3DX_PI + g_camera.rot.y) * 200;
	}

	// ���f���̈ʒu�֒����_��u��
	g_camera.PosV.x = pModel->pos.x + sinf(g_camera.rot.y) * -g_camera.fLength;
	g_camera.PosV.z = pModel->pos.z + cosf(g_camera.rot.y) * -g_camera.fLength;

	// �ړI�̒����_
	g_camera.PosRDest.x = pModel->pos.x - 5.0f * sinf(pModel->rotDest.y);
	g_camera.PosRDest.z = pModel->pos.z - 5.0f * cosf(pModel->rotDest.y);
	g_camera.PosRDest.y = pModel->pos.y + 70.0f;

	// �ړI�̎��_
	g_camera.PosVDest.x = pModel->pos.x - sinf(g_camera.rot.x) * g_camera.fLength;
	g_camera.PosVDest.z = pModel->pos.z - cosf(g_camera.rot.z) * g_camera.fLength;
	g_camera.PosVDest.y = pModel->pos.y + 150.0f;

	// �����_�̈ʒu�X�V
	g_camera.PosR.x += (g_camera.PosRDest.x - g_camera.PosR.x) * 0.1f;
	g_camera.PosR.z += (g_camera.PosRDest.z - g_camera.PosR.z) * 0.1f;
	g_camera.PosR.y += (g_camera.PosRDest.y - g_camera.PosR.y) * 0.1f;

	// ���_�̈ʒu�X�V
	g_camera.PosV.x += (g_camera.PosVDest.x - g_camera.PosV.x) * 0.1f;
	g_camera.PosV.z += (g_camera.PosVDest.z - g_camera.PosV.z) * 0.1f;
	g_camera.PosV.y += (g_camera.PosVDest.y - g_camera.PosV.y) * 0.1f;

	if (GetKeyboardPress(DIK_T) == true)
	{
		g_camera.PosR.y += 1.5f*cosf(D3DX_PI + g_camera.rot.y);
	}

	if (GetKeyboardPress(DIK_B) == true)
	{
		g_camera.PosR.y -= 8.5f*cosf(D3DX_PI + g_camera.rot.y);
	}
	if (GetKeyboardPress(DIK_N) == true)
	{
		g_camera.PosV.y += 1.5f*cosf(D3DX_PI + g_camera.rot.y);
	}

	if (GetKeyboardPress(DIK_Y) == true)
	{
		g_camera.PosV.y -= 1.5f*cosf(D3DX_PI + g_camera.rot.y);
	}

	//��]�p�x���Z�b�g
	if (g_camera.rot.y >= D3DX_PI)
	{
		g_camera.rot.y = -D3DX_PI;
	}

	else if (g_camera.rot.y <= -D3DX_PI)
	{
		g_camera.rot.y = D3DX_PI;
	}

	if (GetKeyboardPress(DIK_SPACE) == true)//�v���C���[�̉�]
	{
		InitCamera();
	}


	//�ʒu�X�V
	g_camera.PosV.x += g_camera.moveV.x;
	g_camera.PosV.z += g_camera.moveV.z;

	//�ʒu�X�V
	g_camera.PosR.x += g_camera.moveR.x;
	g_camera.PosR.z += g_camera.moveR.z;

	// �ړ��ʂ̌���
	g_camera.moveR.x += (0.0f - g_camera.moveR.x) *0.5f;
	g_camera.moveR.z += (0.0f - g_camera.moveR.z) *0.5f;
	
	// �ړ��ʂ̌���
	g_camera.moveV.x += (0.0f - g_camera.moveV.x) *0.5f;
	g_camera.moveV.z += (0.0f - g_camera.moveV.z) *0.5f;

}
//=====================================
//�ݒ菈��
//=====================================
void SetCamera(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,//��O
		1000.0f);//����

	//�v���W�F�N�V�����}�b�s���O�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&g_camera.mtxView,
		&g_camera.PosV,
		&g_camera.PosR,
		&g_camera.VecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
}
Camera GetCamera(void)
{
	return g_camera;
}