/**
* This manages the assehandlers for the whole engine
**/

#ifndef   ASSET_MANAGER_HPP
	#define   ASSET_MANAGER_HPP

#include <map>
#include <typeinfo>
//#include <MGE/Core/interfaces/TAssetHandler.hpp>
#include <MGE/Core/Core_types.hpp>

namespace MGE 
{

	class AssetManager {

	public:
		/**
		* Basic constructor
		*/
		AssetManager();

		/**
		* Basic destructor
		*/
		virtual ~AssetManager();

		template<class TYPE> 
		TAssetHandler<TYPE>& GetHandler() const
		{
				TAssetHandler<TYPE>* result = NULL;
				std::map<const typeAssetHandlerID, IAssetHandler*>::const_iterator iter;



		}
		
		




	};

}

#endif /*ASSET_MANAGER_HPP*/