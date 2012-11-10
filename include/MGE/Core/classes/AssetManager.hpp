/**
* This manages the asset handlers for the engine
**/

#ifndef   ASSETMANAGER_HPP
	#define   ASSETMANAGER_HPP

#include <map>
#include <typeinfo>
#include <MGE/Core/interfaces/TAssetHandler.hpp>
#include <MGE/Core/Core_types.hpp>

#include <iostream>

namespace MGE 
{

	typedef std::map<const typeAssetHandlerID, IAssetHandler*> assetHandlerMap;

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

			/**
			* getHandler is responsible for returning an TAssetHandler derived
			* class that was previously registered under typeid(T).name() of the
			* T provided which can then be used to obtain Asset references by
			* Asset ID.
			*/
			template<class T>
			TAssetHandler<T>& getHandler() const
			{
				// The TAssetHandler<TYPE> derived class that will be returned
				TAssetHandler<T>* handler = NULL;

				// Iterator to the asset if found
				assetHandlerMap::const_iterator iter;

				// Try to find the asset using theAssetID as the key
				iter = mHandlers.find(typeid(T).name());

				// Found asset? increment the count and return the reference
				if(iter != mHandlers.end())
				{
					// Cast the IAssetHandler address found into TAssetHandler
					handler = static_cast<TAssetHandler<T>*>(iter->second);
				}

				// Make sure we aren't returning NULL at this point
				if(handler == NULL)
				{
					FLOG(StatusAppMissingAsset) << "AssetManager::getHandler("
						<< typeid(T).name() << ") not found!" << std::endl;
				}

				// Return the TAssetHandler addres or Null if something went wrong
				return *handler;
			}
		
			/**
			* GetHandler is responsible for returning an IAssetHandler derived
			* class that was previously registered under theAssetHandlerID provided
			* which can then be used to obtain Asset references by Asset ID.
			* @param[in] theAssetHandlerID to retrieve
			*/
			IAssetHandler& getHandler(const typeAssetHandlerID assetHandlerID) const;

			/**
			* RegisterHandler is responsible for registering an IAssetHandler
			* derived class with the AssetManager. These handlers are used to manage
			* various asset types used by game states and other entities.
			* @param[in] theAssetHandler pointer to register
			*/
			void registerHandler(IAssetHandler* assetHandler);

		private:

			///Map that holds all the asserhandlers for all the resources
			assetHandlerMap mHandlers;

			/**
			* AssetManager copy constructor is private because we do not allow copies
			* of our class
			*/
			AssetManager(const AssetManager&); // Intentionally undefined

			/**
			* Our assignment operator is private because we do not allow copies
			* of our class
			*/
			AssetManager& operator=(const AssetManager&); // Intentionally undefined

	};
}

#endif /*ASSET_MANAGER_HPP*/