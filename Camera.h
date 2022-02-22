#pragma once
#include "gameObject.h"

// カメラクラス
class Camera : public GameObject
{

protected:
	XMFLOAT3 m_Target;						// ターゲット
	bool m_IsActive;						// 使用可能か
	bool m_IsMovable;						// 移動可能か
	bool m_IsLock;							// ロックオン中か
	XMFLOAT4X4 m_ViewMatrix;				// ビューマトリクス
	XMFLOAT4X4 m_ProjectionMatrix;			// プロジェクションマトリクス
	XMFLOAT3 m_Move;						// 移動方向
	XMFLOAT3* m_LockTargetPos;				// ターゲット座標
											
	static float m_RoutationalSpeed;		// 回転速度
	float m_MoveSpeed;						// 移動速度
	const static float m_CameraSpeedFirst;	// カメラ初期速度
	const static float m_AtLength;			// ターゲットまでの距離
public:
	Camera():m_IsMovable(false),m_IsActive(false){}
	Camera(bool movable):m_IsMovable(movable),m_IsActive(false){}
	Camera(bool active, bool movable):m_IsActive(active),m_IsMovable(movable){}
	virtual void Init();
	virtual void Init(bool active, bool movable = false);
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

	// 使用可能か
	virtual bool GetIsActive() { return m_IsActive; }

	// 移動可能か
	virtual bool GetMovable() { return m_IsMovable; }

	// 使用可能セッター
	virtual void SetIsActive(bool active) { m_IsActive = active; }

	// 移動可能セッター
	virtual void SetMovable(bool movable) { m_IsMovable = movable; }

	// 使用可能&移動可能セッター
	virtual void SetActiveMovable(bool set) { SetIsActive(set); SetMovable(set); }

	// ビューマトリクスゲッター
	virtual XMFLOAT4X4* GetView() { return &m_ViewMatrix; }

	// 視錘台カリング
	virtual bool CheckView(XMFLOAT3 pos, XMFLOAT3 scale = XMFLOAT3(1.0f,1.0f,1.0f));
	
	// 移動方向ゲッター
	virtual XMFLOAT3* GetMove() { return &m_Move; }

	// 移動速度ゲッター
	virtual float GetSpeed();

	// プレイヤーと同時に移動可能状態を変更
	virtual void ChangeMovableWithPlayer();

	// プレイヤーと同時に移動可能状態を変更
	virtual void ChangeMovableWithPlayer(bool movable);

	// 方向変更
	virtual void ChangeDir(float angle, bool isRight);

	// ロックオン座標セッター
	void SetLockTarget(XMFLOAT3* pos) { m_LockTargetPos = pos; }

	// ロックオン状態セッター
	void SetIsLock(bool lock) { m_IsLock = lock; }
	
	// ロックオン状態ゲッター
	bool GetIsLock(){return m_IsLock;}
};

