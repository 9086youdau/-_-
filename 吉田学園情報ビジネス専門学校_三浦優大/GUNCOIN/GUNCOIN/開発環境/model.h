#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define MODEL_PARTS		(16)	// ���f���p�[�c�̍ő吔
#define MAX_KEY			(8)		// �L�[���̍ő吔
#define FRAME_NUM		(50)	// �t���[���̍ő吔
#define MODEL_TEX_NUM	(8)		// ���f���̃e�N�X�`����
#define MBF_NEU_MOVE	(3)		// ���[�V�����u�����h�t���[���F�j���[�g��������ړ�
#define MBF_MOVE_NEU	(15)	// ���[�V�����u�����h�t���[���F�ړ�����j���[�g����
#define MBF_NEU_ACT		(15)	// ���[�V�����u�����h�t���[���F�j���[�g��������A�N�V����
#define MBF_ACT_NEU		(40)	// ���[�V�����u�����h�t���[���F�A�N�V��������j���[�g����
#define MBF_LND_NEU		(20)	// ���[�V�����u�����h�t���[���F���n����j���[�g����

//==============================================================================
// ���[�V�����̎��
//==============================================================================
typedef enum
{
	MOTIONTYPE_MODELNEUTRAL = 0,	// �j���[�g�������[�V����
	MOTIONTYPE_MODELMOVE,		// �ړ����[�V����
	MOTIONTYPE_MODELACTION,       //�A�N�V�������[�V����
	MOTIONTYPE_JUMP,
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

// �ߐڍU���̎��
typedef enum
{
	SHORT_SLASH = 0,		// ��
	SHORT_MAX
}ShortRange;

//==============================================================================
// ����ۗ̕L���
//==============================================================================
typedef enum
{
	WEAPON_NONE = 0,	// �f��
	WEAPON_MAX
}Weapon;

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
	D3DXVECTOR3 posReset;	
	D3DXVECTOR3 posMemo;								// �ۑ��p�ʒu���
	D3DXVECTOR3 rotMemo;								// �ۑ��p�p�x���
}Model;

//==============================================================================
// �ߐڍU���̍\����
//==============================================================================
typedef struct
{
	D3DXVECTOR3 pos;				// �ʒu
	D3DXVECTOR3 rot;				// ����
	D3DXMATRIX mtxWorld;			// �����蔻��̃}�g���b�N�X
	int nParts;						// ��������p�[�c�ԍ�
	float fRadius;					// ���蔼�a
	int nStartFrame;				// �J�n�t���[��
	int nEndFrame;					// �I���t���[��
	int nCntFrameTotal;				// �U���t���[����
	bool bUse;						// �U���̗L����
	float fGetDamage[4];
} Attack;

// �U������
typedef struct
{
	int nParts;
	int nStartFrame;
	int nEndFrame;
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 posold;		//�ߋ��̈ʒu
	D3DXVECTOR3 rot;		// �p�x
	D3DXCOLOR col;			// �F	
	D3DXVECTOR3 move;		// �ʒu
	D3DXMATRIX mtxWorld;	// ���[���h�}�g���b�N�X
	LPD3DXMESH pMeshSphere;
	LPD3DXBUFFER pBuffMatSphere;	// �}�e���A���ւ̃|�C���^
	float fRadius;
	int nSlice;
	int nStack;
	int nCntFrameTotal;		// �U���t���[����
	bool bUse;				// �g�p���
	D3DXVECTOR3 vtxMinSphere; //���f���̍ŏ��l
	D3DXVECTOR3	vtxMaxSphere;	// ���f���̊e���W�̍ő�l
	D3DXVECTOR3 aPosSph[4];
	D3DXVECTOR3 VecSph[4];
	float SphVec[4];
} AttackSphere;

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
	AttackSphere as;
	bool bUse;
	float fOutRadius;							// �v���C���[�̊O���a
	float fHeight;								// �v���C���[�̍���
	int nFrameTotal[MOTIONTYPE_MODELMAX];			// �e���[�V�����̍��v�t���[����
	bool bMotionChange;							// ���[�V�����ω����̔���
	int nBrendFrame;							// ���[�V�����u�����h���̃t���[����
	MOTIONMODELTYPE motionTypeOld;					// ���O�̃��[�V�����^�C�v
	ShortRange sr;								// �ߐڍU���̎��
	int nMoveCnt;								// �ړ����[�V�����J�E���g
	Attack attack;
	Weapon weapon;
} Player;

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================
HRESULT InitModel(void);	// �v���C���[�̏���������
void UninitModel(void);	// �v���C���[�̏I������
void UpdateModel(void);	// �v���C���[�̍X�V����
void DrawModel(void);		// �v���C���[�̕`�揈��
Player *GetModel(void);	// �v���C���[�̎擾
void UpdateMotion(MOTIONMODELTYPE motionType);	// ���[�V�����̍X�V
void LoadMotion(void);						// .txt�t�H���_�̓ǂݍ���
void AttackParts(void);
//bool CollisionVecSph(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidthMax, float fWidthMin, float fDepthMax, float fDepthMin, float fHeightMax, float fHeightMin);
//bool CollisionVecEnemy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidthMax, float fWidthMin, float fDepthMax, float fDepthMin, float fHeightMax, float fHeightMin);//�O�ς̓����蔻��
#endif
