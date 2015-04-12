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

//! \struct HelloWorldApp - Hello world
struct HelloWorldApp : wtl::MessageThread<wtl::Encoding::UTF16, MainWindow>
{
  // ------------------------ TYPES --------------------------

  //! \alias base - Define base type
  using base = wtl::MessageThread<wtl::Encoding::UTF16, MainWindow>;

  // --------------------- CONSTRUCTION ----------------------

  ///////////////////////////////////////////////////////////////////////////////
  // HelloWorldApp::HelloWorldApp
  //! Creates the Hellow World application
  //! 
  //! \param[in] instance - Instance handle
  ///////////////////////////////////////////////////////////////////////////////
  HelloWorldApp(HINSTANCE instance) : base(instance)
  {
  }

  // ---------------------- ACCESSORS ------------------------

  // ----------------------- MUTATORS ------------------------  
protected:
  ///////////////////////////////////////////////////////////////////////////////
  // HelloWorldApp::onThreadStart
  //! Called once upon startup to create the main window
  //! 
  //! \throw wtl::platform_error - Unable to create window
  ///////////////////////////////////////////////////////////////////////////////
  virtual void onThreadStart()
  {
    static const wtl::PointL initial(50,50);            //!< Initial window position
    static const wtl::SizeL  size(640,480);             //!< Initial window size
    static const wchar_t     title[] = L"Hello World";  //!< Window title

    // Create window
    Window.create(Instance, wtl::WindowStyle::OverlappedWindow, wtl::zero<wtl::WindowStyleEx>::value, wtl::cstr(L"Hello World"), wtl::RectL(initial,size), nullptr, nullptr);
  }

  // -------------------- REPRESENTATION ---------------------
};

#endif

