#pragma once
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define MODEL_PARTS		(16)	// ���f���p�[�c�̍ő吔
#define MAX_KEY			(8)		// �L�[���̍ő吔
#define FRAME_NUM		(50)	// �t���[���̍ő吔

//==============================================================================
// ���[�V�����̎��
//==============================================================================
typedef enum
{
	MOTIONTYPE_MODELNEUTRAL = 0,	// �j���[�g�������[�V����
	MOTIONTYPE_MODELMOVE,		// �ړ����[�V����
	MOTIONTYPE_MODELACTION,       //�A�N�V�������[�V����
	MOTIONTYPE_MODELMAX			// ���[�V�����̍ő吔
} MOTIONMODELTYPE;

//==============================================================================
// �L�[�̍\����
//==============================================================================
typedef struct
{
	float fPosX;	// �ʒuX
	float fPosY;	// �ʒuY
	float fPosZ;	// �ʒuZ
	float fRotX;	// ����X
	float fRotY;	// ����Y
	float fRotZ;	// ����Z
} KEY;

//==============================================================================
// �L�[���̍\����
//==============================================================================
typedef struct
{
	int nFrame;				// �Đ��t���[��			
	KEY aKey[MODEL_PARTS];	// �e���f���̃L�[�v�f 
} KEY_SET;

//==============================================================================
// ���[�W�������̍\����
//==============================================================================
typedef struct
{
	bool bLoop;				// ���[�v���邩
	int nNumKey;			// �L�[�̑���
	KEY_SET aKeySet[10];	// �L�[���
} MOTION_INFO;

//==============================================================================
// ���f���̍\����
//==============================================================================
typedef struct
{
	LPD3DXMESH pMeshModel;		// ���b�V���ւ̃|�C���^
	LPD3DXBUFFER pBuffMatModel;	// �}�e���A���ւ̃|�C���^
	DWORD nNumMatModel;			// �}�e���A���̐�
	LPDIRECT3DTEXTURE9 pTextureModel;//�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 pos;			// �ʒu(�I�t�Z�b�g)
	D3DXVECTOR3 rot;			// ����
	D3DXVECTOR3 posOld;			// �̂̈ʒu(�I�t�Z�b�g)
	D3DXMATRIX mtxWorld;		// ���[���h�}�g���b�N�X
	int nIdxModelParent;		// �e���f���̃C���f�b�N�X
	char aFileName[128];
	bool bUse;
	D3DXVECTOR3 g_vtxMinSord; //���f���̍ŏ��l
	D3DXVECTOR3	g_vtxMaxSord;	// ���f���̊e���W�̍ő�l
}Model;

//==============================================================================
// �v���C���[�̍\����
//==============================================================================
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posOld;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rotDest;
	int nIdx;
	Model aModel[MODEL_PARTS];					// ���f��(�p�[�c)
	int nNumModel/* = MODEL_PARTS*/;			// ���f��(�p�[�c)��
	MOTION_INFO aMotionInfo[MOTIONTYPE_MODELMAX];	// ���[�V�������
	int nNumMotion = MOTIONTYPE_MODELMAX;			// ���[�V������
	MOTIONMODELTYPE motionType;						// ���[�V�����^�C�v
	bool bLoopMotion;							// ���[�v���邩�ǂ���
	int nNumKey;								// �L�[��
	int nKey;									// �L�[��
	int nCounterMotion;							// ���[�V�����̃J�E���^�[
	D3DXVECTOR3 aPos[4];
	D3DXVECTOR3 Vec[4];
	D3DXVECTOR3 g_Vec[4];
	float PlayerVec[4];
	D3DXVECTOR3 g_vtxMinPlayer; //���f���̍ŏ��l
	D3DXVECTOR3	g_vtxMaxPlayer;	// ���f���̊e���W�̍ő�l
	bool bUse;
} Player;

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================
HRESULT InitModel(void);	// �v���C���[�̏���������
void UninitModel(void);	// �v���C���[�̏I������
void UpdateModel(void);	// �v���C���[�̍X�V����
void DrawModel(void);		// �v���C���[�̕`�揈��
Player *GetModel(void);	// �v���C���[�̎擾
void SetMotion(MOTIONMODELTYPE motionType);		// ���[�V�����̐ݒ� 
void UpdateMotion(MOTIONMODELTYPE motionType);	// ���[�V�����̍X�V
void LoadMotion(void);						// .txt�t�H���_�̓ǂݍ���
//bool CollisionVecEnemy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidthMax, float fWidthMin, float fDepthMax, float fDepthMin, float fHeightMax, float fHeightMin);//�O�ς̓����蔻��
#endif
