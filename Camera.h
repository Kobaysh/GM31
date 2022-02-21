#pragma once
#include "gameObject.h"
class Camera : public GameObject
{

protected:
	XMFLOAT3 m_target;
	//XMFLOAT3 m_front;
	//XMFLOAT3 Right;
	//XMFLOAT3 Up;
	bool m_isActive;
	bool m_movable;
	bool m_isLock;
	XMFLOAT4X4 m_viewMatrix;
	XMFLOAT4X4 m_projectionMatrix;
	XMFLOAT3 m_move;
	XMFLOAT3* m_lockTargetPos;

	static float m_routationalSpeed;
	float m_moveSpeed;
	const static float m_cameraSpeedFirst;
	const static float m_atLength;
public:
	Camera():m_movable(false),m_isActive(false){}
	Camera(bool movable):m_movable(movable),m_isActive(false){}
	Camera(bool active, bool movable):m_isActive(active),m_movable(movable){}
	virtual void Init();
	virtual void Init(bool active, bool movable = false);
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();
	virtual bool GetIsActive() { return m_isActive; }
	virtual bool GetMovable() { return m_movable; }
	virtual void SetIsActive(bool active) { m_isActive = active; }
	virtual void SetMovable(bool movable) { m_movable = movable; }
	virtual void SetActiveMovable(bool set) { SetIsActive(set); SetMovable(set); }
	//virtual XMFLOAT3* GetFront() { return &m_front; }
	//virtual XMFLOAT3* GetRight() { return &Right; }
	//virtual XMFLOAT3* GetUp() { return &Up; }
	virtual XMFLOAT4X4* GetView() { return &m_viewMatrix; }
	virtual bool CheckView(XMFLOAT3 pos, XMFLOAT3 scale = XMFLOAT3(1.0f,1.0f,1.0f));
	virtual XMFLOAT3* GetMove() { return &m_move; }
	virtual float GetSpeed();
	virtual void ChangeMovableWithPlayer();
	virtual void ChangeMovableWithPlayer(bool movable);

	virtual void ChangeDir(float angle, bool isRight);

	void SetLockTarget(XMFLOAT3* pos) { m_lockTargetPos = pos; }
	void SetIsLock(bool lock) { m_isLock = lock; }
	bool GetIsLock(){return m_isLock;}
};

