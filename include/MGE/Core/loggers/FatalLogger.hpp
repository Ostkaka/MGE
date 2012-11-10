/*
* Logs fatal messages
*/

#ifndef FATALLOGGER_HPP
	#define FATALLOGGER_HPP

#include <MGE/Core/Core_types.hpp>
#include <MGE/Core/loggers/StringLogger.hpp>

namespace MGE
{
  /// Provides the class used by the Fatal logging macros
  class FatalLogger : public StringLogger
  {
    public:

      /**
       * FatalLogger constructor will write a tag line to the string log using
       * the information provided.
       * @param[in] theSeverity for this message to be logged
       * @param[in] theSourceFile where the Log macro was called from
       * @param[in] theSourceLine number where the Log macro was called from
       * @param[in] theExitCode value to use when exiting the application
       */
			FatalLogger(SeverityType severity,
				const std::string& sourceFile, 
				int sourceLine, 
				int exitCode = StatusError);

      /**
       * FatalLogger deconstructor
       */
      virtual ~FatalLogger();

    protected:

    private:
  }; 
} 

#endif /*FATALLOGGER_HPP*/