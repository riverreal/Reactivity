#ifndef _REACTION_OPERATOR_H_
#define _REACTION_OPERATOR_H_

namespace Reactivity
{
	//Mostly for filtering purposes
	template <typename T>
	class ReactionOperation
	{
	public:
		virtual ~ReactionOperation() {}
		virtual bool Execute(T&) = 0;
	};
}

#endif //_REACTION_OPERATOR_H_