#pragma once
#include "main.h"

class OBB
{
protected:
	XMFLOAT3 m_pos;				// �ʒu
	XMFLOAT3 m_normaDirect[3];	// �����x�N�g��
	float m_fLength[3];			// �e�������̒���

public:
	enum OBB_Direction {
		OBB_DX,
		OBB_DY,
		OBB_DZ,
	};
	XMFLOAT3 GetDirect(OBB_Direction elem) { return m_normaDirect[elem]; }
	float GetLen_W(OBB_Direction elem) { return m_fLength[elem]; }
	XMFLOAT3 GetPos_W() { return m_pos; }

	static bool ColOBBs(OBB &obb1, OBB &obb2);
};