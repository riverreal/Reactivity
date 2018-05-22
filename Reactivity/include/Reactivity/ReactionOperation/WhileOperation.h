#ifndef _WHILE_OPERATION_H_
#define _WHILE_OPERATION_H_

#include "ReactionOperation.h"

#include <functional>

namespace Reactivity
{
	template <typename T>
	class WhileOperation : public ReactionOperation<T>
	{
	public:
		WhileOperation(std::function<bool(T&)> filter);
		virtual bool Execute(T&) override;

	private:
		std::function<bool(T&)> m_filter;
	};

	template<typename T>
	inline WhileOperation<T>::WhileOperation(std::function<bool(T&)> filter)
		:m_filter(filter)
	{
	}

	template<typename T>
	inline bool WhileOperation<T>::Execute(T& value)
	{
		return m_filter(value);
	}
}

#endif //_WHILE_OPERATION_H_