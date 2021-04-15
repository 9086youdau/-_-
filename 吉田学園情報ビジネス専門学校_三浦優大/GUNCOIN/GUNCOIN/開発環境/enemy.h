#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define ENEMY_PARTS		(16)	// ���f���p�[�c�̍ő吔
#define MAX_KEY			(8)		// �L�[���̍ő吔
#define FRAME_NUM		(50)	// �t���[���̍ő吔
#define ENEMYMMAX (56)
#define ENEMYMAXVEC (ENEMYMMAX * 4)

//==============================================================================
// ���[�V�����̎��
//==============================================================================
typedef enum
{
	MOTIONTYPE_NEUTRAL = 0,	// �j���[�g�������[�V����
	MOTIONTYPE_MOVE,		// �ړ����[�V����
	MOTIONTYPE_ACTION,       //�A�N�V�������[�V����
	MOTIONTYPE_MAX			// ���[�V�����̍ő吔
} MOTIONTYPE;

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
} ENEMYKEY;

//==============================================================================
// �L�[���̍\����
//==============================================================================
typedef struct
{
	int nFrame;				// �Đ��t���[��			
	ENEMYKEY aKey[ENEMY_PARTS];	// �e���f���̃L�[�v�f 
} ENEMYKEY_SET;

//==============================================================================
// ���[�W�������̍\����
//==============================================================================
typedef struct
{
	bool bLoop;				// ���[�v���邩
	int nNumKey;			// �L�[�̑���
	ENEMYKEY_SET aKeySet[10];	// �L�[���
} ENEMYMOTION_INFO;

//==============================================================================
// ���f���̍\����
//==============================================================================
typedef struct
{
	LPD3DXMESH pMesh;		// ���b�V���ւ̃|�C���^
	LPD3DXBUFFER pBuffMat;	// �}�e���A���ւ̃|�C���^
	DWORD nNumMat;			// �}�e���A���̐�
	LPDIRECT3DTEXTURE9 pTextureEnemy;//�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 Pos;			// �ʒu(�I�t�Z�b�g)
	D3DXVECTOR3 rot;			// ����
	D3DXMATRIX mtxWorld;		// ���[���h�}�g���b�N�X
	int nIdxModelParent;		// �e���f���̃C���f�b�N�X
	char aFileName[128];
	bool bUse;
	int nType;
}ENEMYModel;

//==============================================================================
// �v���C���[�̍\����
//==============================================================================
typedef struct
{
	D3DXVECTOR3 Pos;
	D3DXVECTOR3 OldPos;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rotDest;
	D3DXVECTOR3 rotmove;
	int nIdx;
	ENEMYModel aModel[ENEMY_PARTS];					// ���f��(�p�[�c)
	int nNumModel/* = MODEL_PARTS*/;			// ���f��(�p�[�c)��
	ENEMYMOTION_INFO aMotionInfo[MOTIONTYPE_MAX];	// ���[�V�������
	int nNumMotion = MOTIONTYPE_MAX;			// ���[�V������
	MOTIONTYPE motionType;						// ���[�V�����^�C�v
	bool bLoopMotion;							// ���[�v���邩�ǂ���
	int nNumKey;								// �L�[��
	int nKey;									// �L�[��
	int nCounterMotion;							// ���[�V�����̃J�E���^�[
	D3DXVECTOR3 aPos[ENEMYMAXVEC];
	D3DXVECTOR3 Vec[ENEMYMAXVEC];
	D3DXVECTOR3 g_Vec[ENEMYMAXVEC];
	float PlayerVec[ENEMYMAXVEC];
	D3DXVECTOR3 MinModel; //���f���̍ŏ��l
	D3DXVECTOR3	MaxModel;	// ���f���̊e���W�̍ő�l
	bool bUse;
} ENEMYPLAYER;
//==========================
//�v���g�^�C�v�錾
//==========================
void InitEnemy(void);//����������
void UninitEnemy(void);//�I������
void UpdateEnemy(void);//�X�V����
void DrawEnemy(void);//�J�����̐ݒ�,Draw�̈�ԏ�Œ�`
ENEMYPLAYER *GetEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, int nType);
void SetEnemyMotion(MOTIONTYPE motionType);		// ���[�V�����̐ݒ� 
void UpdateEnemyMotion(MOTIONTYPE motionType);	// ���[�V�����̍X�V
//bool CollisionVecModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld,float fWidthMax, float fWidthMin, float fDepthMax, float fDepthMin, float fHeightMax, float fHeightMin);
bool CollisionVecSord(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, float fWidthMax, float fWidthMin, float fDepthMax, float fDepthMin, float fHeightMax, float fHeightMin);
#endif

