/*
* IAssetHandler Class provides handling and management of IAsset derived classes
*/

#ifndef   IASSETHANDLER_HPP
	#define   IASSETHANDLER_HPP

#include <map>
#include <MGE/Core/Core_types.hpp>

namespace MGE 
{
		
	 class IAssetHandler
	 {
	
	 public:
		 /*
		 * Basic constructor
		 */
		 IAssetHandler(const typeAssetHandlerID assetHandlerID);

			/**
				* Basic deconstructor
				*/
			virtual ~IAssetHandler();

			/*
			* Returns the ID that identifies this asset handler
			* @return Returns the typeAssetHandlerID for this IAssethandler type
			*/
			const typeAssetHandlerID getID() const;

			/**
			* IsLoaded will return true if the Resource specified by theResourceID
			* has been loaded.
			* @param[in] theAssetID to the Resource to determine loaded state
			* @return true if loaded, false otherwise
			*/
			virtual bool isLoaded(const typeAssetID assetID) const = 0;

			/**
      * LoadAsset is responsible for loading the asset specified by theAssetID
      * provided according to the previously registered style (see
      * GetReference and SetLoadStyle).
      * @param[in] theAssetID of the asset to load
      */
      virtual bool loadAsset(const typeAssetID assetID) = 0;


	 private:

		 ///ID for the specified IAssetHandler
		 const typeAssetHandlerID mAssetHandlerID;

		 /*
		 * Assignment operator is private due to no copies of the class
		 */
		 IAssetHandler& operator=(const IAssetHandler&);
	 };
}
#endif /*IASSETHANDLER_HPP*/