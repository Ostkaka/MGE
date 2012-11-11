#include <MGE/Core/loggers/FatalLogger.hpp>

namespace MGE 
{
	FatalLogger::FatalLogger( SeverityType severity, const std::string& sourceFile, int sourceLine, int exitCode /*= StatusError*/ ):
	StringLogger(false,exitCode)
	{
		//Create tag
		writeTag(getStream(),severity,sourceFile,sourceLine);	
	}
	
	FatalLogger::~FatalLogger()
	{
		// Make sure our global logger is defined before using it
		if(MGE::ILogger::getLogger())
		{
			// Log the Fatal message string stream created
			MGE::ILogger::getLogger()->logMessage(getString().c_str());
		}
		// Call the FatalShutdown method defined in ILogger
		fatalShutdown();
	}
}