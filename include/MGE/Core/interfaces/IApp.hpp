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
#include <MGE/Core/Core_types.hpp>

namespace MGE
{

	class IApp 
	{
		public:

			/**
			* App constructor
			*/
			IApp();

			/**
			* App Deconstructor
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
			virtual void ProcessArguments(int argc, char* argv[]);

			/**
			*
			*@return Valued of the exit-code given by the application by using quit.
			*/
			int run();

			/**
			* Used to check in case the application is still running
			* @return True if the application is running or False if it still is
			*/
			bool isRunnning();

			/*
			* 
			*
			*/
			//setGraphicsRange()

			/**
       * Returns the current game loop update rate being
       * used.
       * @return update rate in Hz (updates per second)
       */
      float getUpdateRate(void) const;

      /*
       * Set the maximum number of sequential updates
       * allowed in any given game loop. If your FPS is
       * struggling, you should set theMaxUpdates to 1.
       * @param[in] theMaxUpdates range is [1,200]
       */
      //void setMaxUpdates(Uint32 theMaxUpdates);


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
      virtual void initAssetHandlers() = 0;

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
      virtual void cleanup(void) = 0;

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
		  //sf::GraphicRange              mGraphicRange;
		  /// Input manager for Render window above

	};
}

#endif /*CORE_APP_HPP*/