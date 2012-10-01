/*
* This is a useless header for an iapp interface
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

			/*
			* App constructor
			*/
			IApp();

			/**
			* App Deconstructor
			*/
			~IApp();

			/**
			* Returns a random number
			*/
			int getNumber();

		protected:
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