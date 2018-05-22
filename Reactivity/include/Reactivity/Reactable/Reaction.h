#ifndef _REACTION_H_
#define _REACTION_H_

#include "../ReactionOperation/ReactionOperation.h"

#include <vector>
#include <functional>
#include <memory>

namespace Reactivity
{
	template <typename T>
	class Reaction
	{
	public:
		Reaction(std::function<void(T&)> cb);
		~Reaction() {
			Clear();
		};
		//void AddOperator(std::unique_ptr<ReactionOperation<T>> op);
		void AddOperations(std::vector<ReactionOperation<T>*> operations);
		void React(T&);
		void Clear();

	private:
		std::vector<ReactionOperation<T>*> m_operations;
		std::function<void(T&)> m_reactionCB;
	};

	template<typename T>
	inline Reaction<T>::Reaction(std::function<void(T&)> cb)
		:m_reactionCB(cb)
	{
	}
	/*
	template<typename T>
	inline void Reaction<T>::AddOperator(std::unique_ptr<ReactionOperation<T>> op)
	{
		//m_operators.push_back(std::move(op));
	}
	*/
	template<typename T>
	inline void Reaction<T>::AddOperations(std::vector<ReactionOperation<T>*> operations)
	{
		Clear();
		m_operations = operations;
	}
	
	template<typename T>
	inline void Reaction<T>::React(T& value)
	{
		for (auto& oper : m_operations)
		{
			if (oper->Execute(value) == false)
			{
				return;
			}
		}

		m_reactionCB(value);
	}
	template<typename T>
	inline void Reaction<T>::Clear()
	{
		for (int i = 0; i < m_operations.size(); ++i)
		{
			delete m_operations[i];
		}

		m_operations.clear();
	}
}

#endif //_REACTION_H_