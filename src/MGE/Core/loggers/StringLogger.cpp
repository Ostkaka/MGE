/**
 * Provides the StringLogger class that provides logging support to a string
 */

#include <MGE/Core/loggers/StringLogger.hpp>

namespace MGE
{
	
	StringLogger::StringLogger( bool standard /*= false*/, int exitCode /*= StatusError*/ ):
	ILogger(standard,exitCode)
	{
	}

	StringLogger::~StringLogger()
	{
	}

	std::string StringLogger::getString( void )
	{
		if(isActive())
		{
			return mStringStream.str();
		}
		else
		{
			return "";
		}
	}

	std::ostream& StringLogger::getStream()
	{
		std::ostream* anResult = &gNullStream;
		if(isActive())
		{
			anResult = &mStringStream;      
		}
		return *anResult;
	}

	std::ostream& StringLogger::getStream( SeverityType severity, 
		const std::string& sourceFile, 
		int sourceLine, 
		int exitCode /*= StatusError*/ )
	{
		std::ostream* anResult = &gNullStream;
		if(isActive())
		{
			anResult = &mStringStream;
			writeTag(mStringStream, severity, sourceFile, sourceLine);
		}
		return *anResult;
	}

	void StringLogger::logMessage( const std::string& message )
	{
		if(isActive())
		{
			mStringStream << message << std::endl;
		}
	}

	void StringLogger::logMessage( SeverityType theSeverity, const std::string& sourceFile, int sourceLine, const std::string& message )
	{
		if(isActive())
		{
			writeTag(mStringStream, theSeverity, sourceFile, sourceLine);
			mStringStream << message << std::endl;
		}
	}
}
