#ifndef FILEPATHCONTAINER_H_
	#define FILEPATHCONTAINER_H_

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

namespace antIO{

	class FilePathContainer {

		typedef std::vector<std::string> FilePaths;

		public:
	
			FilePathContainer();
			~FilePathContainer(){};

			/**
			* Adds a path to the container
			*/
			void add(const std::string & name);

			/**
			* Clears the list of filepaths
			*/
			void clear();

			/**
			* Examine if the specified filename can be found in the paths and returns it if it is
			*/
			std::string find(const std::string & name);


		private:
	
			FilePaths mPaths;

	};

}

#endif /*FILEPATHCONTAINER_H_*/