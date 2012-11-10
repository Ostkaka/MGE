#include "FilePathContainer.h"

using namespace antIO;

FilePathContainer::FilePathContainer(){
	//Add current directory
	this->mPaths.push_back("");
}

void FilePathContainer::add(const std::string & name){

	for(size_t i=0; i < mPaths.size() ; i++){
		if(mPaths[i] == name) return;
	}
	mPaths.push_back(name);
}

void FilePathContainer::clear(){
	this->mPaths.clear();
}

std::string FilePathContainer::find(const std::string & name){

	std::string path;
	std::ifstream my_file;

	for(size_t i=0; i < mPaths.size() ; i++){
		path = mPaths[i];
		path.append(name);
		my_file.open(path);
		//Examine if the specified files exist
		if (my_file.good())
		{
			my_file.close();
			return path;
		}
		my_file.close();
	}
	return std::string();
}