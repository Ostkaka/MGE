/**
* This manages the asset handlers for the engine
**/

#include <MGE/Core/classes/AssetManager.hpp>
#include <MGE/Core/loggers/Log.hpp>
#include <iostream>

namespace MGE
{
	AssetManager::AssetManager()
	{
		ILOGM("AssetManager::ctor()");
	}

	AssetManager::~AssetManager()
	{
		ILOGM("AssetManager::dtor()");

		// Iterator to use while deleting all assets
		assetHandlerMap::iterator iter;

		// Loop through each asset handler and remove each one
		iter = mHandlers.begin();
		while(iter != mHandlers.end())
		{
			IAssetHandler* anAssetHandler = iter->second;

			// Remove this Asset Handler from our map
			mHandlers.erase(iter++);

			// Delete the Asset Handler
			delete anAssetHandler;
		}
	}

	IAssetHandler& AssetManager::getHandler(const typeAssetHandlerID assetHandlerID) const
	{
		// The IAssetHandler derived class that will be returned
		IAssetHandler* handler = NULL;

		// Iterator to the asset if found
		std::map<const typeAssetHandlerID, IAssetHandler*>::const_iterator iter;

		// Try to find the asset using theAssetID as the key
		iter = mHandlers.find(assetHandlerID);

		// Found asset? increment the count and return the reference
		if(iter != mHandlers.end())
		{
			// Return the IAssetHandler address found
			handler = iter->second;
		}

		// Make sure we aren't returning NULL at this point
		if(handler == NULL)
		{
			FLOG(StatusAppMissingAsset) << "AssetManager::GetHandler("
				<< assetHandlerID << ") not found!" << std::endl;
		}

		// Return the address to some IAssetHandler class or the DummyHandler instead
		return *handler;
	}

	void AssetManager::registerHandler(IAssetHandler* assetHandler)
	{
		// Iterator to the asset if found
		assetHandlerMap::iterator iter;

		// Make sure the Handler provided is not NULL
		if(NULL != assetHandler)
		{
			// Try to find the asset using theAssetID as the key
			iter = mHandlers.find(assetHandler->getID());

			// Found asset? increment the count and return the reference
			if(iter == mHandlers.end())
			{
				// Store the provided IAssetHandler derived class for futurn reference
				mHandlers.insert(
					std::pair<const typeAssetHandlerID, IAssetHandler*>(
					assetHandler->getID(), assetHandler));
			}
			else
			{
				// Log an error for trying to register two handlers with the same Handler ID.
				ELOG() << "AssetManager:RegisterHandler(" << assetHandler->getID()
					<< ") Handler already registered for this ID!" << std::endl;
			}
		}
		else
		{
			// Log an error for trying to register a NULL handler
			FLOG(StatusError)
				<< "AssetManager:RegisterHandler() Handler pointer provided was NULL!"
				<< std::endl;
		}
	}
}