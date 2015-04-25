////////////////////////////////////////////////////////////////////////////////
//! \file HelloWorld\HelloWorldApp.h
//! \brief Defines the application 
//! \date 7 March 2015
//! \author Nick Crowley
//! \copyright © Nick Crowley. All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#ifndef HELLO_WORLD_H
#define HELLO_WORLD_H

#include "wtl/WTL.hpp"    // Windows Template Library
#include "MainWindow.h"   // Main window

///////////////////////////////////////////////////////////////////////////////
//! \struct HelloWorldApp - Encapsulates the 'Hello World' program
///////////////////////////////////////////////////////////////////////////////
template <wtl::Encoding ENC = wtl::Encoding::UTF16>
struct HelloWorldApp : wtl::Application<ENC,MainWindow<ENC>>
{
  // ------------------------ TYPES --------------------------

  //! \alias base - Define base type
  using base = wtl::Application<ENC,MainWindow<ENC>>;

  // --------------------- CONSTRUCTION ----------------------

  ///////////////////////////////////////////////////////////////////////////////
  // HelloWorldApp::HelloWorldApp
  //! Create application from handle supplied by WinMain(..)
  //!
  //! \param[in] app - Application handle
  ///////////////////////////////////////////////////////////////////////////////
  HelloWorldApp(::HMODULE app) : base(app)
  {
  }

  // ---------------------- ACCESSORS ------------------------

  // ----------------------- MUTATORS ------------------------  
protected:
  ///////////////////////////////////////////////////////////////////////////////
  // HelloWorldApp::onStart
  //! Called once upon startup to create the main window
  //! 
  //! \param[in] mode - Initial display mode
  //!
  //! \throw wtl::platform_error - Unable to create window
  ///////////////////////////////////////////////////////////////////////////////
  void onStart(wtl::ShowWindowFlags mode) override
  {
    static const wtl::PointL initial(50,50);            //!< Initial window position
    static const wtl::SizeL  size(640,480);             //!< Initial window size
    
    // Create window
    this->Window.createEx(nullptr, wtl::c_arr(L"Hello World"), wtl::RectL(initial,size), wtl::WindowStyle::OverlappedWindow); 
    
    // Show window
    this->Window.show(mode);
    this->Window.update();
  }

  // -------------------- REPRESENTATION ---------------------
};


//! \alias application_t - Define ANSI/UNICODE application type according to build settings (Size of TCHAR)
using application_t = HelloWorldApp<wtl::default_encoding<TCHAR>::value>;

#endif

