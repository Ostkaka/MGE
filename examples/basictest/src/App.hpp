/*
* Test implementation of the application class
*/

#include <MGE/Core_include.hpp>

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