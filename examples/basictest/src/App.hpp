/*
* Test implementation of the application class
*/
#include <string>
#include <MGE/Core_include.hpp>
#include "GameState.hpp"
#include "SplashState.hpp"

using namespace MGE;

class TestApp : public IApp {

	/*
	* Fill with useless methods
	*/

public:
	TestApp(const std::string title = "TestApp");

	virtual ~TestApp();

protected:

	virtual void initCustomAssetHandlers();

	virtual void initCustomGameStates();

	virtual void handleCustomCleanup();
	
};