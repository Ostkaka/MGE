/*
* Provides a class to log to file
*/

#ifndef FILELOGGER_HPP
	#define FILELOGGER_HPP

#include <fstream>
#include <string.h>
#include <MGE/Core/Core_types.hpp>
#include <MGE/Core/interfaces/ILogger.hpp>

namespace MGE
{
	/// File logging class
	class FileLogger : public ILogger
	{
	public:
		/**
		 * Logs to file "filename"
		 */
		FileLogger(const std::string& filename, bool standard = false);

		virtual ~FileLogger();

		virtual std::ostream& getStream();

		virtual std::ostream& getStream(SeverityType severity,
			const std::string& sourceFile,
			int sourceLine, 
			int exitCode = StatusError);

		virtual void logMessage(const std::string& message);

		virtual void logMessage(SeverityType severity,
			const std::string& sourceFile, 
			int theSourceLine,
			const std::string& message);

	protected:

	private:
		/// Output file
		std::ofstream			mFileStream;

		/// Private copy constructor
		FileLogger(const FileLogger&);

		/// Private operator
		FileLogger& operator=(const FileLogger&);


	};
}

#endif /*FILELOGGER_HPP*/