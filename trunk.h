#pragma once

// 0����n�܂��ă_���[�W���󂯂���K�[�h����Ɛ������オ��A�}�b�N�X�̒l�ɂȂ�Ƒ̐������
class Trunk
{
public:
	Trunk(){}
	Trunk(int maxTrunk) { InitMaxTrunk(maxTrunk); }
	~Trunk(){}

	int GetNowTrunk() { return m_nowTrunk; }
	int GetMaxTrunk() { return m_maxTrunk; }

	// ���݂̑̊����Z�b�g
	void SetNowTrunk(int trunk) { m_nowTrunk = trunk; }

	// �̊��̍ő�l���Z�b�g
	void SetMaxTrunk(int maxTrunk) { m_maxTrunk = maxTrunk; }

	// �̊��̍ő�l���Z�b�g�A���݂̑̊���0��
	void InitMaxTrunk(int maxTrunk) { m_maxTrunk = maxTrunk; m_nowTrunk = 0; }

	void ChangeNowTrunk(int changeValue){
		if(m_nowTrunk + changeValue > m_maxTrunk){
			m_nowTrunk = m_maxTrunk;
		}
		else if(m_nowTrunk + changeValue < 0)
		{
			m_nowTrunk = 0;
		}
		else{
			m_nowTrunk += changeValue;
		}
	}

	bool GetIsCollapsed()
	{
		return (m_nowTrunk >= m_maxTrunk);
	}
private:
	int m_nowTrunk;					// �̊�
	int m_maxTrunk;					// Max�̊�
};