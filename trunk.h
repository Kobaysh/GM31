#pragma once

// 0����n�܂��ă_���[�W���󂯂���K�[�h����Ɛ������オ��A�}�b�N�X�̒l�ɂȂ�Ƒ̐������
class Trunk
{
public:
	Trunk(){}
	Trunk(int maxTrunk) { InitMaxTrunk(maxTrunk); }
	~Trunk(){}

	int GetNowTrunk() { return m_NowTrunk; }
	int GetMaxTrunk() { return m_MaxTrunk; }

	// ���݂̑̊����Z�b�g
	void SetNowTrunk(int trunk) { m_NowTrunk = trunk; }

	// �̊��̍ő�l���Z�b�g
	void SetMaxTrunk(int maxTrunk) { m_MaxTrunk = maxTrunk; }

	// �̊��̍ő�l���Z�b�g�A���݂̑̊���0��
	void InitMaxTrunk(int maxTrunk) { m_MaxTrunk = maxTrunk; m_NowTrunk = 0; }

	void ChangeNowTrunk(int changeValue){
		if(m_NowTrunk + changeValue > m_MaxTrunk){
			m_NowTrunk = m_MaxTrunk;
		}
		else if(m_NowTrunk + changeValue < 0)
		{
			m_NowTrunk = 0;
		}
		else{
			m_NowTrunk += changeValue;
		}
	}

	bool GetIsCollapsed()
	{
		return (m_NowTrunk >= m_MaxTrunk);
	}
private:
	int m_NowTrunk;					// �̊�
	int m_MaxTrunk;					// Max�̊�
};