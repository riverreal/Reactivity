#ifndef _REACTIVE_VARIABLE_H_
#define _REACTIVE_VARIABLE_H_

#include "Reactable.h"

namespace Reactivity
{
	template<typename T>
	class ReactiveVariable : public Reactable<T>
	{
	public:
		//Default contructor for T
		ReactiveVariable()
		{}

		//Contructor with initial value for T
		ReactiveVariable(T initialValue)
		{
			this->m_value = initialValue;
		}

		const T& GetValue();

		operator T();
		ReactiveVariable<T>& operator=(T rhs);
		ReactiveVariable<T>& operator+=(T rhs);
		ReactiveVariable<T>& operator-=(T rhs);
		ReactiveVariable<T>& operator*=(T rhs);
		ReactiveVariable<T>& operator/=(T rhs);

		friend T operator+=(T& lhs, const Reactivity::ReactiveVariable<T>& rhs)
		{
			return lhs += rhs.m_value;
		}

		friend T operator-=(T& lhs, const Reactivity::ReactiveVariable<T>& rhs)
		{
			return lhs += rhs.m_value;
		}

		friend T operator*=(T& lhs, const Reactivity::ReactiveVariable<T>& rhs)
		{
			return lhs *= rhs.m_value;
		}

		friend T operator/=(T& lhs, const Reactivity::ReactiveVariable<T>& rhs)
		{
			lhs /= rhs.m_value;
			return lhs;
		}

		friend T operator+(T lhs, const Reactivity::ReactiveVariable<T>& rhs)
		{
			lhs += rhs.m_value;
			return lhs;
		}

		friend T operator-(T lhs, const Reactivity::ReactiveVariable<T>& rhs)
		{
			lhs -= rhs.m_value;
			return lhs;
		}

		friend T operator*(T lhs, const Reactivity::ReactiveVariable<T>& rhs)
		{
			lhs *= rhs.m_value;
			return lhs;
		}

		friend T operator/(T lhs, const Reactivity::ReactiveVariable<T>& rhs)
		{
			lhs /= rhs.m_value;
			return lhs;
		}

		friend bool operator==(const Reactivity::ReactiveVariable<T>& lhs, const T& rhs)
		{
			return lhs.m_value == rhs;
		}

		friend bool operator==(const T& lhs, const Reactivity::ReactiveVariable<T>& rhs)
		{
			return lhs == rhs.m_value;
		}

		friend bool operator!=(const Reactivity::ReactiveVariable<T>& lhs, const T & rhs)
		{
			return !operator==(lhs, rhs);
		}

		friend bool operator!=(const T & lhs, const Reactivity::ReactiveVariable<T>& rhs)
		{
			return !operator==(lhs, rhs);
		}

		friend bool operator<(const Reactivity::ReactiveVariable<T>& lhs, const T & rhs)
		{
			return lhs.m_value < rhs;
		}

		friend bool operator<(const T& lhs, const Reactivity::ReactiveVariable<T>& rhs)
		{
			return lhs < rhs.m_value;
		}

		friend bool operator<=(const Reactivity::ReactiveVariable<T>& lhs, const T & rhs)
		{
			return !operator>(lhs, rhs);
		}

		friend bool operator<=(const T & lhs, const Reactivity::ReactiveVariable<T>& rhs)
		{
			return !operator>(lhs, rhs);
		}

		friend bool operator>(const Reactivity::ReactiveVariable<T>& lhs, const T & rhs)
		{
			return lhs.m_value > rhs;
		}

		friend bool operator>(const T& lhs, const Reactivity::ReactiveVariable<T>& rhs)
		{
			return lhs > rhs.m_value;
		}

		friend bool operator>=(const Reactivity::ReactiveVariable<T>& lhs, const T & rhs)
		{
			return !operator<(lhs, rhs);
		}

		friend bool operator>=(const T& lhs, const Reactivity::ReactiveVariable<T>& rhs)
		{
			return !operator<(lhs, rhs);
		}
	};

	template<typename T>
	inline const T& ReactiveVariable<T>::GetValue()
	{
		return this->m_value;
	}

	template<typename T>
	inline ReactiveVariable<T>::operator T()
	{
		return this->m_value;
	}

	template<typename T>
	inline ReactiveVariable<T>& ReactiveVariable<T>::operator=(T rhs)
	{
		this->OnChange(rhs);
		return *this;
	}

	template<typename T>
	inline ReactiveVariable<T>& ReactiveVariable<T>::operator+=(T rhs)
	{
		this->OnChange(this->m_value + rhs);
		return *this;
	}

	template<typename T>
	inline ReactiveVariable<T>& ReactiveVariable<T>::operator-=(T rhs)
	{
		this->OnChange(this->m_value - rhs);
		return *this;
	}

	template<typename T>
	inline ReactiveVariable<T>& ReactiveVariable<T>::operator*=(T rhs)
	{
		this->OnChange(this->m_value*rhs);
		return *this;
	}

	template<typename T>
	inline ReactiveVariable<T>& ReactiveVariable<T>::operator/=(T rhs)
	{
		this->OnChange(this->m_value / rhs);
		return *this;
	}
}

#endif //_REACTIVE_VARIABLE_H_