/**
* This is a template asset class for constructing assets. This is used buy the IAssetHandler
* class for managing resources
*/

#ifndef   TASSET_HPP
	#define   TASSET_HPP

#include <string>
#include <MGE/Core/interfaces/IApp.hpp>
#include <MGE/Core/interfaces/TAssetHandler.hpp>
#include <MGE/Core/Core_types.hpp>

namespace MGE
{

	template<class T>
	class TAsset
	{
	public:
		/*
		* Constructor of the Asset class
		* @param[in] theAssetID to use for this asset
		*/

		TAsset(const typeAssetID assetID): 
			mAssetHandler(IApp::getApp()->mAssetManager.getHandler<T>()),
			mAsset(mAssetHandler.getReference(assetID)),
			mAssetID(assetID)
		{
			//Do nothing here
		}

		/*
		* TAsset default constructor can be used if an id cannot be specified at creation
		*/
		TAsset() :
		mAssetHandler(IApp::getApp()->mAssetManager.getHandler<T>()),
		mAsset(mAssetHandler.getReference())
		{
		}

		/**
    * TAsset deconstructor
    */
    virtual ~TAsset()
    {
    }

		/**
    * GetID will return the ID being used for this asset.
    * @return the Asset ID assigned to this asset
    */
		const typeAssetID getID() const
		{
			return mAssetID;
		}

		void setID(const typeAssetID assetID)
		{
			// Make note of the new Asset ID
			mAssetID = assetID;

			// Try to obtain a reference to the new Asset from Handler
			mAsset = mAssetHandler.getReference(mAssetID);
		}

		/**
    * getAsset will return the Asset if it is available.
    * @return pointer to the Asset or Dummy asset if not existing yet
    */
		T& getAsset()
		{
			// Is asset not yet loaded, then try to load it immediately
			if(false == mAssetHandler.isLoaded(mAssetID))
			{
				// Load the asset immediately
				bool succLoad = mAssetHandler.loadAsset(mAssetID);

				// If the asset was loaded, get a reference to it now
				if(succLoad)
				{
					// Get reference to the asset immediately
					mAsset = mAssetHandler.getReference(mAssetID);
				}
			}

			// Return reference to dummy asset or loaded asset
			return *mAsset;
		}

	protected:

			/// The derived asset handler for managing this resource type
			TAssetHandler<T>&	mAssetHandler;
			/// Pointer to the asset of type T
			T *								mAsset;
			/// The string ID specified for this type of asset
			typeAssetID				mAssetID;

			
	};
}
#endif /*TASSET_HPP*/