/**
 * Provides the ScopeLogger class that provides logging the Entry and Exit of
 * the scope where this class is defined using the information provided at
 * construction time.  The Exit scope will be logged with the line number of
 * the where the ScopeLogger class was defined.
 *
 */

#ifndef   SCOPELOGGER_HPP
	#define   SCOPELOGGER_HPP

#include <MGE/Core/Core_types.hpp>
#include <MGE/Core/interfaces/ILogger.hpp>

namespace MGE
{
  /// Provides a scope Entry/Result/Exit logging class
  class ScopeLogger : public ILogger
  {

    public:
      /**
       * ScopeLogger constructor will log the Entry of this scope to the global
       * logger using the information provided and keep this information around
       * for logging the Exit of the scope (see ~ScopeLogger).
       */
      ScopeLogger(SeverityType severity,
          const std::string& sourceFile, 
					int sourceLine,
          const char* scopeName = "",
					int theExitCode = StatusError);

      /**
       * ScopeLogger deconstructor
       */
      virtual ~ScopeLogger();

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
      /// The severity level defined at construction time or by the last call to
      /// the GetStream() or LogMessage() methods (see SLOGR).
      SeverityType mSeverity;
      /// The source file defined at construction time or by the last call to the
      /// GetStream() or LogMessage() methods (see SLOGR).
      std::string mSourceFile;
      /// The source line defined at construction time or by the last call to the
      /// GetStream() or LogMessage() methods (see SLOGR).
      int mSourceLine;
      /// The scope name to use when logging Result (see SLOGR) or Exit messages
      std::string mScopeName;
  }; // class ScopeLogger
} // namespace GQE

#endif // CORE_SCOPE_LOGGER_HPP_INCLUDED

