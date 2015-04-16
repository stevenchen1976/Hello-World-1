////////////////////////////////////////////////////////////////////////////////
//! \file HelloWorld\Main.cpp
//! \brief Entry point for Hello World program
//! \date 7 March 2015
//! \author Nick Crowley
//! \copyright © Nick Crowley. All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#include "HelloWorldApp.h"   


////////////////////////////////////////////////////////////////////////////////
// ::_tWinMain
//! Narrow/wide char entry point
//!
//! \param[in] instance - Program instance 
//! \param[in] prevInstance - Legacy
//! \param[in] cmdLine - Command line
//! \param[in] nCmdShow - Desired display mode
////////////////////////////////////////////////////////////////////////////////
int32 WINAPI _tWinMain(HINSTANCE instance, HINSTANCE prevInstance, PWSTR cmdLine, int32 nCmdShow)
{
  application_t program(instance);
  
  // Run program and return result
  return program.run();
}


