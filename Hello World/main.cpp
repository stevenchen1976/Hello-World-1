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
//! \param[in] showMode - Desired display mode
////////////////////////////////////////////////////////////////////////////////
int32_t WINAPI _tWinMain(::HINSTANCE instance, ::HINSTANCE prevInstance, PWSTR cmdLine, int32_t showMode)
{
  try
  {
    hw1::application_t program(instance);
  
    // Run program and return result
    return program.run(cmdLine, wtl::enum_cast<wtl::ShowWindowFlags>(showMode));
  }
  catch (std::exception& e)
  {
    wtl::errorBox<hw1::encoding>(NULL, wtl::caught_exception("An unhandled exception caused a terminal error", HERE, e));
    return -1;
  }
}


