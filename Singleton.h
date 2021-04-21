#pragma once

//template<class T>
class Singleton
{
public:
	/*static inline T& GetInstance() {
		static T instance;
		return instance;
	}*/

	static Singleton* GetInstance() {
		return m_pInstance;
	}

	static void Create() {
		if (!m_pInstance) {
			m_pInstance = new Singleton;
		}
	}

	static void Destory() {
		delete m_pInstance;
		m_pInstance = nullptr;
	}


protected:
	static Singleton* m_pInstance;
	Singleton(){}	// 外部でのインスタンス作成は禁止
	virtual ~Singleton(){}


private:
	void operator=(const Singleton& obj){}	// 代入演算子禁止
	Singleton(const Singleton& obj){}	// コピーコンストラクタ禁止
};

