#ifndef _TAKE_OPERATION_H_
#define _TAKE_OPERATION_H_

#include "ReactionOperation.h"

#include <cstdint>

namespace Reactivity
{
	template <typename T>
	class TakeOperation : public ReactionOperation<T>
	{
	public:
		TakeOperation(uint32_t count);
		virtual bool Execute(T&) override;

	private:
		uint32_t m_takeCount;
		uint32_t m_counter;
	};

	template<typename T>
	inline TakeOperation<T>::TakeOperation(uint32_t count)
		:m_takeCount(count), m_counter(0)
	{
	}

	template<typename T>
	inline bool TakeOperation<T>::Execute(T& value)
	{
		if (m_takeCount == m_counter)
		{
			return true;
		}
		else
		{
			m_counter++;
			return false;
		}
	}
}

#endif //_TAKE_OPERATION_H_