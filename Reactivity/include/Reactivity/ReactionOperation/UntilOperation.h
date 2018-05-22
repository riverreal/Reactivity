#ifndef _UNTIL_OPERATION_H_
#define _UNTIL_OPERATION_H_

#include <cstdint>

namespace Reactivity
{
	template <typename T>
	class UntilOperation : public ReactionOperation<T>
	{
	public:
		UntilOperation(uint32_t count);
		virtual bool Execute(T&) override;

	private:
		uint32_t m_untilCount;
		uint32_t m_counter;
	};

	template<typename T>
	inline UntilOperation<T>::UntilOperation(uint32_t count)
		:m_untilCount(count), m_counter(0)
	{
	}

	template<typename T>
	inline bool UntilOperation<T>::Execute(T& value)
	{
		if (m_untilCount == m_counter)
		{
			return false;
		}
		else
		{
			m_counter++;
			return true;
		}
	}
}

#endif //_UNTIL_OPERATION_H_