#ifndef _UNREACTABLE_H_
#define _UNREACTABLE_H_

#include <vector>
#include <functional>
#include <utility>
#include "Reaction.h"

namespace Reactivity
{
	template <typename T>
	class UnReactable
	{
	public:
		UnReactable(uint32_t id, std::vector<UnReactable<T>>& unreactables, Reaction<T> reaction)
			:m_id(id), m_unreactables(unreactables), m_reaction(std::move(reaction))
		{}
		UnReactable<T>& operator=(const UnReactable& rhs);
		Reaction<T>& GetReaction();
		void Remove();
		
	private:
		uint32_t m_id;
		std::vector<UnReactable<T>>& m_unreactables;
		Reaction<T> m_reaction;
	};

	template<typename T>
	inline UnReactable<T>& UnReactable<T>::operator=(const UnReactable & rhs)
	{
		this->m_id = rhs.m_id;
		this->m_reaction = rhs.m_reaction;
		this->m_unreactables = rhs.m_unreactables;
		return *this;
	}

	template<typename T>
	inline Reaction<T>& UnReactable<T>::GetReaction()
	{
		return m_reaction;
	}

	template<typename T>
	inline void UnReactable<T>::Remove()
	{
		if (m_unreactables.size() > 1)
		{
			uint32_t id = m_id;
			std::iter_swap(m_unreactables.begin() + id, m_unreactables.end() - 1);
			m_unreactables[id].m_id = id;
			m_unreactables.pop_back();
		}
		else
		{
			m_unreactables.clear();
		}
	}
}

#endif //_UNREACTABLE_H_