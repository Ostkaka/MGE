/*
* This is the abstract app class in MGE that is used for building applications
*/
#ifndef   CORE_APP_HPP
	#define   CORE_APP_HPP

#include <fstream>
#include <stddef.h>
#include <string.h>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <MGE/Core/classes/StateManager.hpp>
#include <MGE/Core/Core_types.hpp>

namespace MGE
{
	class IApp 
	{
		public:
			/**
       * IApp deconstructor
       */
      virtual ~IApp();

			/**
			* Will return the most recent created IApp based class. Used for retrieving 
			* assets among other things
			*/
			static IApp * getApp();

			/*
			* Processes the command line for arguments 
			* @param[in] argc is the number of arguments
			* @param[in] argv are the actual arguments
			*/
			virtual void processArguments(int argc, char* argv[]);

			/**
			*
			*@return Valued of the exit-code given by the application by using quit.
			*/
			int run();

			/**
			* Used to check in case the application is still running
			* @return True if the application is running or False if it still is
			*/
			bool isRunning() const;

      /**
       * SetGraphicRange will set theGraphicRange value provided if it fits
       * within the GraphicRange enumeration. It is typically called with the
       * result of CalculateRange in the InitRenderer method.
       * @param[in] theGraphicRange to set
       */
      void setGraphicRange(const GraphicRange theGraphicRange);

			/**
       * Returns the current game loop update rate being
       * used.
       * @return update rate in Hz (updates per second)
       */
      float getUpdateRate() const;

      /*
       * Set the maximum number of sequential updates
       * allowed in any given game loop. If your FPS is
       * struggling, you should set theMaxUpdates to 1.
       * @param[in] theMaxUpdates range is [1,200]
       */
      void setMaxUpdates(int newMaxUpdates);

			 /**
       * Quit will signal the Application to stop running.
       * @param[in] exitCode to use when the Run method returns
       */
			void quit(int exitCode = 1);


		protected:

      /**
       * Basic constructor
       * @param[in] Title of the window
       */
      IApp(const std::string theTitle = "MGE Application");

			/**
       * Registers custom IAssetHandler derived classes for a specific game application.
			 *
       */
      virtual void initCustomAssetHandlers() = 0;

      /**
       * Responsible for monitoring IsRunning and exiting when the
       * Application is done.
       */
      virtual void gameLoop();

      /**
       * ProcessInput is responsible for performing all input processing for
       * the game loop.
       */
      virtual void processInput(IState& theState);

      /**
       * Responsible for performing any custom last minute
       * Application cleanup steps before exiting the Application.
       */
      virtual void customCleanup() = 0;

	private:

    /**
      * calculateRange is responsible for returning the best GraphicRange
      * value to use for the given window height provided.
      * @param[in] theHeight to use as part of calculation.
      * @return a GraphicRange enum value computed
      */
		const GraphicRange calculateRange(int theHeight) const;

		/**
     * Initializes the Rendering window that
     * will be used to display the games graphics.
     */
    void initRenderer();

		/**
     * Responsible for registering and loading the
     * application configuration file (settings.cfg) 
		 */
    void initConfig();

    /**
      * Cleanup is responsible for performing any last minute Application
      * cleanup steps before exiting the Application.
      */
    void cleanup(void);

    /**
      * App copy constructor is private because we do not allow copies of
      * singleton class. Intentionally undefined.
      */
    IApp(const IApp&);               

    /**
      * Assignment operator is private because copies
      * of our Singleton class are not allowed. Intentionally undefined.
      */
    IApp& operator=(const IApp&);    

		protected:
		  ///CONSTANTS
			/// Default Video width
			static const unsigned int DEFAULT_VIDEO_WIDTH = 800;
			/// Default Video height 
			static const unsigned int DEFAULT_VIDEO_HEIGHT = 600;
			/// Default video bits per pixel (color depth) 
			static const unsigned int DEFAULT_VIDEO_BPP = 32;
			/// Default application wide settings file string
			static const char* APP_SETTINGS;

			///Variables
		  /// Title to use for Window
		  std::string               mTitle;
		  /// Video Mode to use (width, height, bpp)
		  sf::VideoMode             mVideoMode;
		  /// Render window to draw to
		  sf::RenderWindow          mWindow;
		  /// Window settings to use when creating Render window
		  sf::ContextSettings       mContextSettings;
		  /// Window style to use when creating Render window
		  unsigned long             mWindowStyle;
		  /// Recommended Graphic Range to use based on screen height
		  GraphicRange              mGraphicRange;

			/// AssetManager for managing assets
			//AssetManager              mAssetManager;
			/// PropertyManager for managing IApp properties
			//PropertyManager           mProperties;
			/// StatManager for managing game statistics
			//StatManager               mStatManager;
			/// StateManager for managing states
			StateManager              mStateManager;

		private:
			/// Static instance variables assigned at creation
			static IApp*  gApp;

			/// Exit code that is returned upon existing the application
			int						mExitCode; 

			/// TRUE if the app is still running
			bool					mRunning;

			/// Value that holds the update rate in milliseconds used for a fixed loop time
			float					mUpdateRate;

			/// Maximum sequential fixed update calls allowed to to meet minimum frame rate
			int						mMaxUpdates;

	};
}

#endif /*CORE_APP_HPP*/