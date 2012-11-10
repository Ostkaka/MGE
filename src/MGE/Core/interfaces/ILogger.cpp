/**
* ILogger is the interface that all the logger classes in the framework is derived from
*/
#include <MGE\Core\interfaces\ILogger.hpp>
#include <ctime>
#include <ostream>
#include <MGE/Core/interfaces/ILogger.hpp>
#include <MGE/Core/interfaces/IApp.hpp>

namespace MGE
{
	ILogger* ILogger::gInstance = NULL;
	std::onullstream ILogger::gNullStream;


	ILogger::ILogger( bool derfaultLogger/*=false*/,int exitCode /*= StatusType::StatusError*/ ):
	mActive(false),
		mExitCode(StatusError)
	{
		if(derfaultLogger)
		{
			gInstance = this;
		}

		setActive(true);
	}

	ILogger::~ILogger()
	{
		if(mActive)
		{
			setActive(false);
		}

		//Clear this as default if going out of scope
		if(gInstance == this)
		{
			gInstance=NULL;
		}

		//If we are going out of scope, remove static pointer
		if(this == gInstance)
		{
			gInstance=NULL;
		}
	}

	ILogger* ILogger::getLogger()
	{
		return gInstance;
	}

	bool ILogger::isActive()
	{
		return mActive;
	}

	void ILogger::setActive( bool active )
	{
		mActive = active;	
	}

	void ILogger::writeTag( std::ostream& ostream, SeverityType severity, const std::string& sourceFile, int sourceLine )
	{
		const struct std::tm* atm; // Pointer to Time structure
		std::time_t now;

		//Get local time
		now = std::time(NULL);
		atm = std::localtime(&now);

		//Format output of timestamp
		ostream << atm->tm_year + 1900 << "-";
		ostream.fill('0');
		ostream.width(2);
		ostream << atm->tm_mon + 1 << "-";
		ostream.fill('0');
		ostream.width(2);
		ostream << atm->tm_mday << " ";
		ostream.fill('0');
		ostream.width(2);
		ostream << atm->tm_hour + 1 << ":";
		ostream.fill('0');
		ostream.width(2);
		ostream << atm->tm_min << ":";
		ostream.fill('0');
		ostream.width(2);
		ostream << atm->tm_sec << " "; 

		// Print the log level as a single character
		switch(severity)
		{
		case SeverityInfo:
			ostream << "[Information]";
			break;
		case SeverityWarning:
			ostream << "[Warning]";
			break;
		case SeverityError:
			ostream << "[Error]";
			break;
		case SeverityFatal:
			ostream << "[Fatal]";
			break;
		default:
			ostream << "[Undefined]";
			break;
		}
		ostream << " " << sourceFile << ":" << sourceLine << " ";
	}

	void ILogger::fatalShutdown()
	{
		// Does the gApp pointer exist? then call the Quit method
		if(NULL != IApp::getApp())
		{
			IApp::getApp()->quit(mExitCode);
		}
		else
		{
			// In the event that the gApp pointer doesn't exist, perform a standard
			// exit() call to force the program to terminate.
			exit(mExitCode);
		}
	}
}