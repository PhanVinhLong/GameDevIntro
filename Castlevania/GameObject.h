#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>

#include "define.h"
#include "Sprites.h"


using namespace std;

class CGameObject;
typedef CGameObject * LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent * LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;
	CCollisionEvent(float t, float nx, float ny, LPGAMEOBJECT obj = NULL) { this->t = t; this->nx = nx; this->ny = ny; this->obj = obj; }

	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b)
	{
		return a->t < b->t;
	}
};

class CGameObject
{
protected:

	float x;
	float y;

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	float vx;
	float vy;

	int nx;
	int ny;

	int state;

	DWORD dt;

	vector<LPANIMATION> animations;

	int id;
	int score;
	int nextItemId;
	bool isOnGround;

	DWORD stopWatchStart;

public:
	void SetPosition(float x, float y) { this->x = x; this->y = y; }
	void AddPosition(float x, float y) { this->x = this->x + x; this->y = this->y + y; }
	void SetSpeed(float vx, float vy) { this->vx = vx; this->vy = vy; }
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }
	int GetId() { return id; }

	int GetState() { return this->state; }

	void RenderBoundingBox(int alpha = 255);

	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	virtual void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT> &coEvents,
		vector<LPCOLLISIONEVENT> &coEventsResult,
		float &min_tx,
		float &min_ty,
		float &nx,
		float &ny);

	void AddAnimation(int aniId);

	CGameObject();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render() = 0;
	virtual void SetState(int state) { this->state = state; }
	virtual void ResetAnimation();
	virtual int GetScore() { return score; }
	virtual void Start() {}
	virtual void BeDamaged();
	virtual void StartStopWatch();

	int GetNx();
	int GetNy();
	int GetNextItemId();

	~CGameObject();
};

typedef CGameObject* LPGAMEOBJECT;
