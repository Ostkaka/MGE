/**
* ILogger is the interface that all the logger classes in the framework is derived from
*/

#ifndef   ILOGGER_HPP
	#define   ILOGGER_HPP

#include <MGE/Core/Core_types.hpp>
#include <MGE/Core/loggers/onullstream>

namespace MGE
{
	class ILogger
	{
		public:
			/// Default null stream if logger is not active
			static std::onullstream gNUllstream;
			
			/**
			 *  Basic destructor
			 */
			virtual ~ILogger();

			/**
			 * This function returns the most recent created logger 
			 * @return Pointer to the logger object derived form ILogger
			 */
			static ILogger* getLogger();

			/**
			 * Returns true if logger is active
			 * @return true if logger is active, false otherwise
			 */
			bool isActive();

			/**
			 * Set the logger's active state
			 */
			virtual void setActive(bool active);

			/**
			 * Returns the stream nessecary to log custom message
			 */
				virtual std::ostream& getStream(SeverityType severity, 
				const std::string& sourceFile,
				int sourceLine, int exitCode = StatusError) = 0;

			/**
			 * Logs a message given data
			 */
			virtual void logMessage(const std::string& logMessage) = 0;

			/**
			 * Logs a message given information 
			 */
			virtual void logMessage(SeverityType severity, 
				const std::string& sourceFile,
				int sourceLine, int exitCode = StatusError) = 0;

	protected:

		/**
		 * Default protected constructor due to singelton class
		 */
		ILogger(bool derfaultLogger=false,int exitCode = StatusError);

		/**
		 * Write tags writes a timestamp in the provided ostream given som information
		 * Check setActive before calling this to make sure to only log to active loggers.
		 */
		void writeTag(std::ostream& ostream, 
			SeverityType severity, 
			const std::string& sourceFile,
			int sourceLine);
		
		/**
		 * Called when logging a fatal sverity type
		 */
		void fatalShutdown();

	private:
		/// static logger variable to be created at construction
		static ILogger * gInstance;
		/// Holds if the logger is currently active
		bool mActive;
		/// Exit value when fatal shutdown is called
		int mExitCode; 

		/**
		 * private due to singleton class
		 */
		ILogger(const ILogger&);
	}; 
}

#endif /*ILOGGER_HPP*/