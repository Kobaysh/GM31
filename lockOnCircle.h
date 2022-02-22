#pragma once
#include "gameObject.h"

// ロックオン表示クラス
class LockOnCircle : public GameObject
{
public:
	LockOnCircle(){}
	LockOnCircle(GameObject* obj):m_Object(obj){}
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
private:
	GameObject* m_Object;						// ロックオンオブジェクト
	ID3D11Buffer* m_VertexBuffer;				// 頂点バッファ
	static const std::string TEXTURE_FILE_NAME;	// テクスチャ名
};