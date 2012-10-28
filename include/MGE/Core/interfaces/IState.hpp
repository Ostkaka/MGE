/*
* This is the abstract IState class in MGE 
*/
#ifndef   CORE_ISTATE_HPP
	#define   CORE_ISTATE_HPP

#include <MGE/Core/Core_types.hpp>

namespace MGE
{

	class IState  {
    	
		public:
			/**
			* Basic constructor
			*/
			IState(){};

			/**
			* Basic deconstructor
			*/
			~IState(){};

		protected:
	};

}

#endif /* CORE_ISTATE_HPP */
