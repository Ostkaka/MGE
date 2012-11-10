/*
* IAssetHandler Class provides handling and management of IAsset derived classes
*/

#include <assert.h>
#include <MGE/Core/interfaces/IAssetHandler.hpp>
#include <MGE/Core/loggers/Log.hpp>

namespace MGE
{

	IAssetHandler::IAssetHandler(const typeAssetHandlerID assetHandlerID) :
	mAssetHandlerID(assetHandlerID)
	{
		ILOG() << "IAssetHandler::ctor(" << mAssetHandlerID << ")" << std::endl;
	}
	
	IAssetHandler::~IAssetHandler()
	{
		ILOG() << "IAssetHandler::dtor(" << mAssetHandlerID << ")" << std::endl;
	}

	const typeAssetHandlerID IAssetHandler::getID() const
	{
		return mAssetHandlerID;
	}
}