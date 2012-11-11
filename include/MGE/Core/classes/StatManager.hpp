/*
* Class that handles statistical information about the applicaiton such
* as framerates and updates per second.
*/

#ifndef STATMANAGER_HPP
	#define STATMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <MGE/Core/Core_types.hpp>

//#define PRINT_COUT_ONLY

namespace MGE
{
	class StatManager 
	{
	public:
		/**
		 * Basic cosntructor
		 */
		StatManager();

		/**
		 * Basic deconstructor
		 */
		virtual ~StatManager();

		/**
		 * Inits the statmanager by loading resource such as fonts
		 */
		void init();

		/*
		* Unloads assets and dumps statistical information in the log file
		*/
		void deInit();

		/**
		 *  Retuns tru if the statistics are being displayed
		 */
		bool isShowing();

		/**
		 * Use to disable or enable rendering of statistics
		 */
		void setShow(bool show);

		/**
		 * Returns the number of updates that have been done since last second
		 */
		int getUpdates();

		/**
		 * Retuns the number of frames that have been done since since last second
		 */
		int getFrames();

		/**
		 * Register the app pointer to the statmanager
		 */
		void registerApp(IApp * app);

		/**
		 * Handles the fixed update calls to the statmanager
		 */
		void updateFixed();

		/**
		 * Draw handles rendering of statistics and updating variables such as FPS
		 */
		void draw();

	private:
		//////////////////////////////////////////////////////////////////////////
		// Variables
		//////////////////////////////////////////////////////////////////////////
		// Pointer to IApp class
		IApp *				mApp;
		bool					mShow;
		
		//Default font for displaying FPS and UPS
		sf::Font			mDefaultFont;

		/// Variables for displaying FPS
		int						mFrames;
		sf::Clock			mFrameClock;
		sf::Text* 		mFPS;

		/// Variables for displaying UPS
		int						mUpdates;
		sf::Clock			mUpdateClock;
		sf::Text*			mUPS;

		/// Copy and assignment private due disallow copies
		StatManager(const StatManager&);
		StatManager& operator=(const StatManager&);

	};
}


#endif