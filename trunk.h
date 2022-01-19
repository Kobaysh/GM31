#pragma once

// 0から始まってダメージを受けたりガードすると数字が上がる、マックスの値になると体制を崩す
class Trunk
{
public:
	Trunk(){}
	Trunk(int maxTrunk) { InitMaxTrunk(maxTrunk); }
	~Trunk(){}

	int GetNowTrunk() { return m_nowTrunk; }
	int GetMaxTrunk() { return m_maxTrunk; }

	// 現在の体幹をセット
	void SetNowTrunk(int trunk) { m_nowTrunk = trunk; }

	// 体幹の最大値をセット
	void SetMaxTrunk(int maxTrunk) { m_maxTrunk = maxTrunk; }

	// 体幹の最大値をセット、現在の体幹を0に
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
	int m_nowTrunk;					// 体幹
	int m_maxTrunk;					// Max体幹
};