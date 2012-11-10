/**
 * Provides the StringLogger class that provides logging support to a string
 */

#ifndef LOGGER_HPP
	#define LOGGER_HPP

#include <sstream>
#include <string>
#include <MGE/Core/Core_types.hpp>
#include <MGE/Core/interfaces/ILogger.hpp>

namespace MGE
{
  /// Provides a class for logging to a large string in memory
  class StringLogger : public ILogger
  {
    public:

      /**
       * StringLogger constructor
       */
      StringLogger(bool standard = false, int exitCode = StatusError);

			/**
       * StringLogger destructor
       */
      virtual ~StringLogger();

      std::string getString(void);

      virtual std::ostream& getStream();

			virtual std::ostream& getStream(SeverityType severity, 
				const std::string& sourceFile,
				int sourceLine, 
				int exitCode = StatusError);

      virtual void logMessage(const std::string& message);

      virtual void logMessage(SeverityType severity,
          const std::string& sourceFile, 
					int sourceLine,
          const std::string& message);

    protected:      

    private:
      /// Output Logger file
      std::ostringstream mStringStream;

      StringLogger(const StringLogger&);            

      StringLogger& operator=(const StringLogger&);  
  }; 
} 

#endif 