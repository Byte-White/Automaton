#pragma once
#include <utility>

template<typename T>
class UniquePtr
{
public:
	UniquePtr(T* ptr = nullptr) : m_ptr(ptr) {}
	UniquePtr(const UniquePtr&) = delete;
	UniquePtr& operator=(const UniquePtr&) = delete;
	UniquePtr(UniquePtr&& other) noexcept : m_ptr(other.m_ptr)
	{
		other.m_ptr = nullptr;
	}

	~UniquePtr()
	{
		free();
	}

	UniquePtr& operator=(UniquePtr&& other) noexcept
	{
		if (this != &other)
		{
			free();
			moveFrom(std::move(other));
		}
		return *this;
	}

	operator bool() const {
		return m_ptr;
	}

	T& operator*() {
		return *m_ptr;
	}

	T const& operator*() const {
		return *m_ptr;
	}
	T* operator->() {
		return m_ptr;
	}

	T const* operator->() const {
		return m_ptr;
	}

	T* get() {
		return m_ptr;
	}
	const T* get() const {
		return m_ptr;
	}

	T* release() {
		T* cpy = m_ptr;
		m_ptr = nullptr;
		return cpy;
	}

	void reset(T* ptr = nullptr) {
		if (m_ptr != ptr)
		{
			free();
			m_ptr = ptr;
		}
	}
private:
	T* m_ptr;

	void moveFrom(UniquePtr&& other) noexcept
	{
		m_ptr = other.m_ptr;
		other.m_ptr = nullptr;
	}

	void free()
	{
		delete m_ptr;
	}
};