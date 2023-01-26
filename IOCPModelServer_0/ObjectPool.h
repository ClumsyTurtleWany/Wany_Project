#pragma once
#include <queue>
#include <stdexcept>
#include <memory>


// Ŭ������ �޸𸮴� Virtual�� Override�� ���Ͽ� �޶� �� �� �ִ�. ������ ����ü�� Ŭ������ ������ �δ°� ����.
template<class T>
class ClassPool
{
protected:
	static const size_t DefaultChunkSize = 10;
	size_t ChunkSize;
	std::queue<std::shared_ptr<T>>	m_queue;

public:
	ClassPool(size_t chunk);
	ClassPool(const ClassPool<T>&) {};
	ClassPool<T>& operator = (ClassPool<T>&) {};

protected:
	bool Allocate();

public:
	std::shared_ptr<T> NewChunk();
	bool	DeleteChunk(std::shared_ptr<T>& chunk);

};

template <class T>
inline ClassPool<T>::ClassPool(size_t chunk)
{
	ChunkSize = chunk;
	Allocate();
}

template<class T>
inline bool ClassPool<T>::Allocate()
{
	for (size_t idx = 0; idx < ChunkSize; idx++)
	{
		m_queue.push(std::make_shared<T>());
		ChunkSize++;
	}
	return true;
}

template<class T>
inline std::shared_ptr<T> ClassPool<T>::NewChunk()
{
	if (m_queue.empty())
	{
		m_queue.push(std::make_shared<T>());
	}

	auto chunk = m_queue.front();
	m_queue.pop();
	return chunk;
}

template<class T>
inline bool ClassPool<T>::DeleteChunk(std::shared_ptr<T>& chunk)
{
	m_queue.push(chunk);
	return true;
}



// Ŭ������ �޸𸮴� Virtual�� Override�� ���Ͽ� �޶� �� �� �ִ�. ������ ����ü�� Ŭ������ ������ �δ°� ����.
template<typename T>
class ObjectPool // ����ü���� ����ϴ� ���� ����.
{
public:
	enum
	{
		POOL_MAX_SIZE = 4096,// 2^n ������ �ؾ߸� ��.
		POOL_SIZE_MASK = POOL_MAX_SIZE - 1,
	};

private:
	static void* m_Pool[POOL_MAX_SIZE];
	static long long HeadPos;
	static long long TailPos;

public:
	static void Allocation()
	{
		for (size_t idx = 0; idx < POOL_MAX_SIZE; i++)
		{
			// �޸� ���� �ּҸ� 16����Ʈ�� �����ϰڴ�. (_aligned_malloc == ���� ����, MEMORY_ALLOCATION_ALIGNMENT == 16����Ʈ)
			// m_Pool[idx] % MEMORY_ALLOCATION_ALIGNMENT == 0
			m_Pool[idx] = _aligned_malloc(sizeof(T), MEMORY_ALLOCATION_ALIGNMENT);
		}
	}
	
	static void Release()
	{
		for (size_t idx = 0; idx < POOL_MAX_SIZE; i++)
		{
			_aligned_free(m_Pool[idx]);
		}
	}

	static void* operator new (size_t size)
	{
		// ���� �迭�� ����ϱ� ���Ͽ� ����ũ�� �̿��Ͽ� ��Ʈ�������ش�.
		// POOL_MAX_SIZE = 8
		// POOL_SIZE_MASK = 7
		// POOL_SIZE_MASK = 0x0111
		// HeadPos = 0, 0x0000 & 0x0111 = 0
		// HeadPos = 1, 0x0001 & 0x0111 = 1
		// HeadPos = 2, 0x0010 & 0x0111 = 2
		// HeadPos = 3, 0x0011 & 0x0111 = 3
		// HeadPos = 4, 0x0100 & 0x0111 = 4
		// HeadPos = 5, 0x0101 & 0x0111 = 5
		// HeadPos = 6, 0x0110 & 0x0111 = 6
		// HeadPos = 7, 0x0111 & 0x0111 = 7
		// HeadPos = 8, 0x1000 & 0x0111 = 0
		// HeadPos = 9, 0x1001 & 0x0111 = 1
		size_t pos = InterlockedIncrement64(&HeadPos) - 1; // Interlocked���� �����忡�� ��ȣ�ϰ� ���� ���� ��Ŵ.
		size_t realpos = pos & POOL_SIZE_MASK;
		void* pObj = InterlockedExchangePointer(&m_Pool[realpos], nullptr); // m_Pool[realpos]�� nullptr�� �ٲٰڴ�. �ٲٱ� ���� �ּҰ� ����.
		if (pObj != nullptr)
		{
			return pObj;
		}

		return _aligned_malloc(sizeof(T), MEMORY_ALLOCATION_ALIGNMENT);
	}

	static void* operator delete (void* obj)
	{
		size_t pos = InterlockedIncrement64(&TailPos) - 1; // Interlocked���� �����忡�� ��ȣ�ϰ� ���� ���� ��Ŵ.
		size_t realpos = pos & POOL_SIZE_MASK;
		void* pObj = InterlockedExchangePointer(&m_Pool[realpos], obj); // m_Pool[realpos]�� obj�� �ٲٰڴ�. �ٲٱ� ���� �ּҰ� ����.
		if (pObj != nullptr)
		{
			// nullptr�� �ƴϸ� ��ü�� ���� ��ȯ�ȴ�. ��۸� ������. ���� ���� ����� �Ѵ�.
			_aligned_free(pObj);
		}
	}
};

template<typename T>
static void* ObjectPool<T>::m_Pool[POOL_MAX_SIZE] = {};

template<typename T>
static long long ObjectPool<T>::HeadPos(0);

template<typename T>
static long long ObjectPool<T>::TailPos(0);