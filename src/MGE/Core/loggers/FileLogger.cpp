#include <MGE/Core/loggers/FileLogger.hpp>

namespace MGE
{

	FileLogger::FileLogger(const std::string& filename, bool standard /*= false*/ ):
	ILogger(standard)
	{
		mFileStream.open(filename);
		if(mFileStream.is_open())
		{
			logMessage(SeverityInfo,__FILE__,__LINE__,"FileLogger::ctor()");
		}
	}

	FileLogger::~FileLogger()
	{
		if(mFileStream.is_open())
		{
			logMessage(SeverityInfo,__FILE__,__LINE__,"FileLogger::dtor()");
				mFileStream.close();
		}
	}

	std::ostream& FileLogger::getStream()
	{
		std::ostream* result = &gNullStream;
		if(mFileStream.is_open() && isActive())
		{
			result = &mFileStream;
		}
		return *result;
	}

	std::ostream& FileLogger::getStream( SeverityType severity, const std::string& sourceFile, int sourceLine, int exitCode /*= StatusError*/ )
	{
		std::ostream * result = &gNullStream;
		if(mFileStream.is_open() && isActive())
		{
			result = &mFileStream;
			writeTag(mFileStream,severity,sourceFile,sourceLine);
		}
		return *result;
	}

	void FileLogger::logMessage(const std::string& message )
	{
		if(mFileStream.is_open() && isActive())
		{
			mFileStream << message << std::endl;
		}
	}

	void FileLogger::logMessage( SeverityType severity, const std::string& sourceFile, int theSourceLine, const std::string& message )
	{
		if(mFileStream.is_open() && isActive())
		{
			writeTag(mFileStream, severity, sourceFile, theSourceLine);
			mFileStream << message << std::endl;
		}
	}
}
