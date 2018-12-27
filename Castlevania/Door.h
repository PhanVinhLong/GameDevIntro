#pragma once
#include "GroundObject.h"
#include "Simon.h"

#define DOOR_BBOX_WIDTH			8
#define DOOR_BBOX_HEIGHT		48

#define DOOR_STATE_OPEN			0
#define DOOR_STATE_CLOSE		1
#define DOOR_STATE_OPENING		2
#define DOOR_STATE_CLOSING		3

#define DOOR_ANI_OPEN			1
#define DOOR_ANI_CLOSE			2
#define DOOR_ANI_OPENING		3
#define DOOR_ANI_CLOSING		4

#define DOOR_ACTION_1_TIME		1960
#define DOOR_ACTION_2_TIME		450
#define DOOR_ACTION_3_TIME		1000
#define DOOR_ACTION_4_TIME		460
#define DOOR_ACTION_5_TIME		1960

class CDoor :
	public CGroundObject
{
	DWORD action1Start;
	DWORD action2Start;
	DWORD action3Start;
	DWORD action4Start;
	DWORD action5Start;

	CViewport* viewport = CViewport::GetInstance();
	CSimon* simon = CSimon::GetInstance();
public:
	CDoor(D3DXVECTOR2 position);
	~CDoor();

	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	virtual void Render();

	void Start();
};

