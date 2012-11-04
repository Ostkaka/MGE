/** 
* IAssetHandler Class provides handling and management of IAsset derived classes
* 
*/
#ifndef   TASSETHANDLER_HPP
	#define   TASSETHANDLER_HPP

#include <map>
#include <typeinfo>
#include <MGE/Core/interfaces/IAssetHandler.hpp>
#include <MGE/Core/Core_types.hpp>

namespace MGE
{

	template<class T>
	class TAssetHandler : public IAssetHandler
	{

	public:

		/**
		* Basic constructor
		*/
		TAssetHandler():
				IAssetHandler(typeid(T).name())
		{
		}

		/**
		* Basic deconstructor
		*/
		virtual ~TAssetHandler(){

			//Loop through all assets and try to remove them
			AssetMap::iterator iter = mAssetMap.begin();
			while(iter !=  mAssetMap.end())
			{
			
				//Get the ID of the asset and retrieve it
				const typeAssetID assetID = iter->first;
				T* asset = iter->second.asset;

				// Remove this Asset Data structure from our map
				mAssetMap.erase(iter++);

				// Release the asset
				clearAsset(assetID, asset);

				//Reset pointer
				asset=NULL;
			}
		}

		/**
    * GetReference will return the dummy asset reference address since no
    * ID was provided to find. This enables system stability since all
    * Assets will have valid addresses
    */
    T* getReference()
    {
      // Return the Dummy Asset reference
      return &mDummyAsset;
    }

		/**
		* GetReference will retrieve the asset registered under assetID
		* or load the asset if it has not been created.
		* @param[in] theAssetID to lookup for the reference
		* @return the asset found or a newly acquired asset if not found
		*/
		T* getReference(const typeAssetID assetID)
		{

			//TAsset pointer that will be created
			T * asset = NULL;

			//iterator for the asset map
			AssetMap::iterator iter;

			// Try to find the asset using the asset id specified 
			iter = mAssetMap.find(assetID);

			if(iter != mAssetMap.end())
			{
				//Get the pointer to the asset
				asset = iter->second.asset;
			}
			else //This means that the asset do not exist inside the manager, so load it!
			{
				// Create the base asset 
				asset = createAsset(assetID);

				// Insert the created asset into the assetMap
				if(NULL != asset)
				{
					// Create new asset data to hold information about the asset
					typeAssetData data;

					// Insert data for the asset
					data.asset = asset;
					data.filename = assetID;
					data.loaded = false;
					
					// Store the newly acquired asset pointer in the map
					mAssetMap.insert(AssetPair(assetID, data));

					// Load the asset
					loadAsset(assetID);
				}
			}

			// If result is NULL by this point then return the Dummy Asset instead
			if(NULL == asset)
			{
				// Get the DummyAsset pointer now
				asset = &mDummyAsset;
			}

			// Return the resulting asset
			return asset;
		}

		/**
    * IsLoaded will return true if the Resource specified by theResourceID
    * has been loaded.
    * @param[in] assetID to the Resource to determine loaded state
    * @return true if loaded, false otherwise
    */
    virtual bool isLoaded(const typeAssetID assetID) const
    {
      // Result if asset was not found
      bool succLoad = false;

      // Iterator to the asset if found
			AssetMap::const_iterator iter;

      // Try to find the asset using theAssetID as the key
      iter = mAssetMap.find(assetID);

      // Found asset? return the loaded indicator found
      if(iter != mAssetMap.end())
      {
        // Return the loaded value found
        succLoad = iter->second.loaded;
      }
      else
      {
        // Log a warning for trying to determine loaded value of an unknown asset ID
      }

      // Return the result found or the default result assigned above
      return succLoad;
    }

	  /**
    * LoadAsset is responsible for loading the asset specified by theAssetID
    * provided according to the previously registered style (see
    * GetReference and SetLoadStyle).
    * @param[in] theAssetID of the asset to load
    */
    virtual bool loadAsset(const typeAssetID theAssetID)
    {
			//Stores the result if the asset was found
			bool succLoad = false;

      // Iterator to the asset if found
      AssetMap::iterator iter;

      // Try to find the asset using theAssetID as the key
      iter = mAssetMap.find(theAssetID);

      // Found asset? return the loaded indicator found
      if(iter != mAssetMap.end())
      {
				iter->second.loaded = loadFromFile(theAssetID, *(iter->second.asset));
				succLoad = iter->second.loaded;
			}

			//Return the load result
			return succLoad;
    }

		/**
		* loadFromFile is responsible for loading theAsset from a file and must
		* be defined by the derived class since the interface for T is
		* unknown 
		* @param[in] theAssetID of the asset to be loaded
		* @param[in] theAsset pointer to load
		* @return true if the asset was successfully loaded, false otherwise
		*/
		virtual bool loadFromFile(const typeAssetID theAssetID, T& theAsset) = 0;

	protected:

		/**
		* Creates an IAsset derived asset and
		* returning it to the caller.
		* @param[in] theAssetID of the asset to acquire
		* @return a pointer to the newly created asset
		*/
		virtual T* createAsset(const typeAssetID assetID)
		{
			return new(std::nothrow) T();
		}

		/**
		* clearAsset is responsible for unloading and removing theAsset
		* specified and deleting the memory used by the asset.
		* @param[in] theAssetID of the asset to be released
		* @param[in] theAsset to be released
		*/
		virtual void clearAsset(const typeAssetID theAssetID, T* theAsset)
		{
			// Delete the memory used for the asset
			delete theAsset;
		}

	private:

		/// Structure holding information about each Resource
		struct typeAssetData {
			T*						asset;		 ///< The asset being shared
			bool					loaded;		 ///< True if the asset is loaded
			std::string   filename;  ///< Filename to use when loading this asset
		};

		//Typedef useful types for the asset manager
		typedef std::pair<const typeAssetID, typeAssetData> AssetPair;
		typedef std::map<const typeAssetID, typeAssetData> AssetMap;

		/// Map that associates asset ID's with their appropriate asset data
		AssetMap mAssetMap;
		/// Dummy asset that will be returned if an asset can't be Acquired
		T mDummyAsset;

	};

}

#endif /*TASSETHANDLER_HPP*/