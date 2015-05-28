////////////////////////////////////////////////////////////////////////////////
//! \file HelloWorld\Main.cpp
//! \brief Entry point for Hello World program
//! \date 7 March 2015
//! \author Nick Crowley
//! \copyright © Nick Crowley. All rights reserved.
////////////////////////////////////////////////////////////////////////////////

// Target Platform v5.01 (WindowsXP)
#include <WinSDKVer.h>
#define _WIN32_WINNT    _WIN32_WINNT_WINXP
#include <SDKDDKVer.h>

#include <WTL/WTL.hpp>
#include <WTL/traits/BuildTraits.hpp>

//! \namespace wtl - Namespace injection
namespace wtl
{
  /////////////////////////////////////////////////////////////////////////////////////////
  //! \struct build_traits<void> - Defines project build target traits 
  /////////////////////////////////////////////////////////////////////////////////////////
  template <> 
  struct build_traits<void>
  {
    // ---------------------------------- TYPES & CONSTANTS ---------------------------------
  
    //! \var target - Target operating system
    static constexpr WindowVersion  target = static_cast<WindowVersion>(_WIN32_WINNT);
    
    // ----------------------------------- REPRESENTATION -----------------------------------
  
    // ------------------------------------ CONSTRUCTION ------------------------------------
	
    DISABLE_CTOR(build_traits);     //!< Cannot instantiate

    // -------------------------------- COPY, MOVE & DESTROY --------------------------------

    DISABLE_COPY(build_traits);     //!< Cannot instantiate
    DISABLE_MOVE(build_traits);     //!< Cannot instantiate
    DISABLE_DTOR(build_traits);     //!< Cannot instantiate
  };
}



