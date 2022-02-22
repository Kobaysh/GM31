#pragma once
#include "gameObject.h"
class Camera : public GameObject
{

protected:
	XMFLOAT3 m_Target;
	//XMFLOAT3 m_Front;
	//XMFLOAT3 Right;
	//XMFLOAT3 Up;
	bool m_IsActive;
	bool m_IsMovable;
	bool m_IsLock;
	XMFLOAT4X4 m_ViewMatrix;
	XMFLOAT4X4 m_ProjectionMatrix;
	XMFLOAT3 m_Move;
	XMFLOAT3* m_LockTargetPos;

	static float m_RoutationalSpeed;
	float m_MoveSpeed;
	const static float m_CameraSpeedFirst;
	const static float m_AtLength;
public:
	Camera():m_IsMovable(false),m_IsActive(false){}
	Camera(bool movable):m_IsMovable(movable),m_IsActive(false){}
	Camera(bool active, bool movable):m_IsActive(active),m_IsMovable(movable){}
	virtual void Init();
	virtual void Init(bool active, bool movable = false);
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();
	virtual bool GetIsActive() { return m_IsActive; }
	virtual bool GetMovable() { return m_IsMovable; }
	virtual void SetIsActive(bool active) { m_IsActive = active; }
	virtual void SetMovable(bool movable) { m_IsMovable = movable; }
	virtual void SetActiveMovable(bool set) { SetIsActive(set); SetMovable(set); }
	//virtual XMFLOAT3* GetFront() { return &m_Front; }
	//virtual XMFLOAT3* GetRight() { return &Right; }
	//virtual XMFLOAT3* GetUp() { return &Up; }
	virtual XMFLOAT4X4* GetView() { return &m_ViewMatrix; }
	virtual bool CheckView(XMFLOAT3 pos, XMFLOAT3 scale = XMFLOAT3(1.0f,1.0f,1.0f));
	virtual XMFLOAT3* GetMove() { return &m_Move; }
	virtual float GetSpeed();
	virtual void ChangeMovableWithPlayer();
	virtual void ChangeMovableWithPlayer(bool movable);

	virtual void ChangeDir(float angle, bool isRight);

	void SetLockTarget(XMFLOAT3* pos) { m_LockTargetPos = pos; }
	void SetIsLock(bool lock) { m_IsLock = lock; }
	bool GetIsLock(){return m_IsLock;}
};

