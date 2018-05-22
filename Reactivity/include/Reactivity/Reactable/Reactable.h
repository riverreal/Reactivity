#ifndef _REACTABLE_H_
#define _REACTABLE_H_

#include <functional>
#include <vector>
#include <utility>
#include <memory>
#include <cstdint>

#include "UnReactable.h"

//Reaction Operations
#include "../ReactionOperation/WhileOperation.h"
#include "../ReactionOperation/TakeOperation.h"
#include "../ReactionOperation/UntilOperation.h"

namespace Reactivity
{
	template <typename T>
	class Reactable
	{
	public:
		Reactable()
			:m_counter(0)
		{}
		virtual ~Reactable();

		virtual UnReactable<T>& React(std::function<void(T&)> s);
		virtual void OnChange(const T& value);
		virtual void UnReact(UnReactable<T>& unreactable);
		
		//Operations
		Reactable<T>& While(std::function<bool(T&)> condition);
		Reactable<T>& Take(uint32_t count);
		Reactable<T>& Until(uint32_t count);

	protected:
		T m_value;
		std::vector<UnReactable<T>> m_unreactables;
		std::vector<ReactionOperation<T>*> m_chainedOperators;
		uint32_t m_counter;
	};

	template<typename T>
	inline Reactable<T>::~Reactable()
	{
		for (int i = 0; i < m_chainedOperators.size(); ++i)
		{
			delete m_chainedOperators[i];
		}

		m_chainedOperators.clear();
	}

	template<typename T>
	inline UnReactable<T>& Reactable<T>::React(std::function<void(T&)> s)
	{
		m_unreactables.push_back(std::move(UnReactable<T>(m_counter, m_unreactables, Reaction<T>(std::move(s)))));
		m_counter++;

		//Transfer pointer ownership to reaction so memory is freed there
		m_unreactables.back().GetReaction().AddOperations(m_chainedOperators);
		m_chainedOperators.clear();

		return m_unreactables.back();
	}

	template<typename T>
	inline void Reactable<T>::OnChange(const T& value)
	{
		m_value = value;

		for (auto& reaction : m_unreactables)
		{
			reaction.GetReaction().React(m_value);
		}
	}

	template<typename T>
	inline void Reactable<T>::UnReact(UnReactable<T>& unreactable)
	{
		unreactable.Remove();
		m_counter--;
	}

	template<typename T>
	inline Reactable<T>& Reactable<T>::While(std::function<bool(T&)> condition)
	{
		m_chainedOperators.push_back(new WhileOperation<T>(condition));
		return *this;
	}

	template<typename T>
	inline Reactable<T>& Reactable<T>::Take(uint32_t count)
	{
		m_chainedOperators.push_back(new TakeOperation<T>(count));
		return *this;
	}
	template<typename T>
	inline Reactable<T>& Reactable<T>::Until(uint32_t count)
	{
		m_chainedOperators.push_back(new UntilOperation<T>(count));
		return *this;
	}
}

#endif //_REACTABLE_H_