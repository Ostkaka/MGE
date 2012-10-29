#include <assert.h>
#include <stddef.h>
#include <MGE/Core_include.hpp>
#include "App.hpp"

int main(){
	
	int exitCode = MGE::StatusNoError;

	MGE::IApp * app = new(std::nothrow) TestApp();


} 