#include <assert.h>
#include <stddef.h>
#include <MGE/Core_include.hpp>
#include "App.hpp"

#include <stdio.h>  /* defines FILENAME_MAX */
#include <direct.h>
#define GetCurrentDir _getcwd

int main(int argc, char* argv[] ){
	
	int exitCode = MGE::StatusNoError;

	char cCurrentPath[FILENAME_MAX];

	cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */

	if(!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
	{
		return errno;
	}

	printf("The current working directory is %s", cCurrentPath);

	MGE::IApp * app = new(std::nothrow) TestApp();

	app->processArguments(argc, argv);

	exitCode = app->run();

	delete app;

	app = NULL;

	return exitCode;
} 