#ifndef _RESULT_H_
#define _RESULT_H_
#include "main.h"


//===============
//�\����
//=================
typedef struct
{
	int nType;
	int nData;
}RESULT;

//===============
//�v���g�^�C�v�錾
//===============
HRESULT InitResult(void);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);
void SetVertexTextureResult(int nCntResult);
#endif


