/**
 * Provides the ScopeLogger class that provides logging the Entry and Exit of
 * the scope where this class is defined using the information provided at
 * construction time.  The Exit scope will be logged with the line number of
 * the where the ScopeLogger class was defined.
 *
 */

#include <MGE/Core/loggers/ScopeLogger.hpp>

namespace MGE
{
	ScopeLogger::ScopeLogger( SeverityType severity,const  std::string& sourceFile, 
		int sourceLine, const char* scopeName /*= ""*/, int theExitCode /*= StatusError*/ ):
		ILogger(false, theExitCode),
		mSeverity(severity),
		mSourceFile(sourceFile),
		mSourceLine(sourceLine),
		mScopeName(scopeName)
	{
		// Make sure our global logger is defined before using it
		if(MGE::ILogger::getLogger())
		{
			// Log the scope Entry with theScopeName provided to the
			// global logger (see GQE::gLogger).
			MGE::ILogger::getLogger()->getStream(mSeverity, mSourceFile, mSourceLine,
				theExitCode) << "Enter(" << scopeName << ") ";
		}
	}

	ScopeLogger::~ScopeLogger()
	{
		// Make sure our global logger is defined before using it
		if(MGE::ILogger::getLogger())
		{
			// Log the scope Exit with mScopeName provided at construction time to
			// the global logger (see GQE::gLogger).
			MGE::ILogger::getLogger()->getStream(mSeverity, mSourceFile, mSourceLine)
				<< "Exit(" << mScopeName << ")" << std::endl;
		}

		// If the severity level is Fatal then call our FatalShutdown method
		if(MGE::SeverityFatal == mSeverity)
		{
			fatalShutdown();
		}
	}

	std::ostream& ScopeLogger::getStream()
	{
		// Make sure our global logger is defined before using it
		if(MGE::ILogger::getLogger())
		{
			// Just return whatever the global logger returns for GetStream()
			return MGE::ILogger::getLogger()->getStream();
		}
		else
		{
			// If global logger doesn't exist, gNullStream will so return that
			return MGE::ILogger::gNullStream;
		}
	}

	std::ostream& ScopeLogger::getStream( SeverityType severity, const std::string& sourceFile, int sourceLine, int exitCode /*= StatusError*/ )
	{
		// Update our internal copy of the severity level, source file, and the
		// source line so our Exit entry can report the last time this method was
		// called (see SLOGR).
		mSeverity = severity;
		mSourceFile = sourceFile;
		mSourceLine = sourceLine;

		// Make sure our global logger is defined before using it
		if(MGE::ILogger::getLogger())
		{
			// Just return whatever the global logger returns for GetStream()
			return MGE::ILogger::getLogger()->getStream(severity, sourceFile,
				sourceLine, exitCode) << "Result(" << mScopeName << ") ";
		}
		else
		{
			//If global logger doesn't exist, gNullStream will so return that
			return MGE::ILogger::gNullStream;
		}
	}

	void ScopeLogger::logMessage( const std::string& message )
	{
		// Make sure our global logger is defined before using it
		if(MGE::ILogger::getLogger())
		{
			// Use the global logger to log theMessage provided
			MGE::ILogger::getLogger()->logMessage(message);
		}
	}

	void ScopeLogger::logMessage( SeverityType severity, 
		const std::string& sourceFile, 
		int sourceLine, 
		const std::string& message )
	{
		// Update our internal copy of the severity level, source file, and the
		// source line so our Exit entry can report the last time this method was
		// called (see SLOGR).
		mSeverity = severity;
		mSourceFile = sourceFile;
		mSourceLine = sourceLine
;
		// Make sure our global logger is defined before using it
		if(MGE::ILogger::getLogger())
		{
			// Use the global logger to log theMessage and other info provided
			MGE::ILogger::getLogger()->logMessage(severity, sourceFile, sourceLine,
				message);
		}
	}
}