/*
* Bla bla bla
*/

#include <assert.h>
#include <MGE/Core/interfaces/IApp.hpp>
#include <MGE/Core/interfaces/IState.hpp>
#include <iostream>

namespace MGE 
{

	IApp::IApp(){
		std::cout << "App is created" << std::endl;
	}

	IApp::~IApp(){

	}

	int IApp::getNumber(){
		return std::rand();
	}


}