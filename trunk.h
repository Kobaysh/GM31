#pragma once

// 0から始まってダメージを受けたりガードすると数字が上がる、マックスの値になると体制を崩す
class Trunk
{
public:
	Trunk(){}
	Trunk(int maxTrunk) { InitMaxTrunk(maxTrunk); }
	~Trunk(){}

	int GetNowTrunk() { return m_NowTrunk; }
	int GetMaxTrunk() { return m_MaxTrunk; }

	// 現在の体幹をセット
	void SetNowTrunk(int trunk) { m_NowTrunk = trunk; }

	// 体幹の最大値をセット
	void SetMaxTrunk(int maxTrunk) { m_MaxTrunk = maxTrunk; }

	// 体幹の最大値をセット、現在の体幹を0に
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
	int m_NowTrunk;					// 体幹
	int m_MaxTrunk;					// Max体幹
};