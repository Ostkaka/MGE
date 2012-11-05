/*
* IAssetHandler Class provides handling and management of IAsset derived classes
*/

#include <assert.h>
#include <MGE/Core/interfaces/IAssetHandler.hpp>

namespace MGE
{

	IAssetHandler::IAssetHandler(const typeAssetHandlerID assetHandlerID) :
	mAssetHandlerID(assetHandlerID)
	{
	}
	
	IAssetHandler::~IAssetHandler()
	{
	}

	const typeAssetHandlerID IAssetHandler::getID() const
	{
		return mAssetHandlerID;
	}
}