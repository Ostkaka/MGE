#include <MGE/Core_include.hpp>
#include <iostream>

int main(){

	MGE::IApp * o = new MGE::IApp();

	std::cout << o->getNumber() << std::endl;

	delete o;

} 