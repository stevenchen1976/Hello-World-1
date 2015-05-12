////////////////////////////////////////////////////////////////////////////////
//! \file HelloWorld\HelloWorldApp.h
//! \brief Defines the application 
//! \date 7 March 2015
//! \author Nick Crowley
//! \copyright © Nick Crowley. All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#ifndef HELLO_WORLD_H
#define HELLO_WORLD_H

#include "wtl/WTL.hpp"                      //!< Windows Template Library
#include "wtl/modules/Application.hpp"      //!< wtl::Application
#include "MainWindow.h"                     //!< hw1::Mainwindow

using namespace wtl;

//! \namespace hw1 - Hello World v1 (Drawing demonstration)
namespace hw1
{

  ///////////////////////////////////////////////////////////////////////////////
  //! \struct HelloWorldApp - Encapsulates the 'Hello World' program
  ///////////////////////////////////////////////////////////////////////////////
  template <Encoding ENC = Encoding::UTF16>
  struct HelloWorldApp : Application<ENC,MainWindow<ENC>>
  {
    // ---------------------------------- TYPES & CONSTANTS ---------------------------------

    //! \alias base - Define base type
    using base = Application<ENC,MainWindow<ENC>>;

    // ------------------------------ CONSTRUCTION & DESTRUCTION ----------------------------

    ///////////////////////////////////////////////////////////////////////////////
    // HelloWorldApp::HelloWorldApp
    //! Create application from handle supplied by WinMain(..)
    //!
    //! \param[in] app - Application handle
    ///////////////////////////////////////////////////////////////////////////////
    HelloWorldApp(::HMODULE app) : base(app)
    {
    }

    // ---------------------------------- ACCESSOR METHODS ----------------------------------

    // ----------------------------------- MUTATOR METHODS ----------------------------------  
  protected:
    ///////////////////////////////////////////////////////////////////////////////
    // HelloWorldApp::onStart
    //! Called once upon startup to create the main window
    //! 
    //! \param[in] mode - Initial display mode
    //!
    //! \throw platform_error - Unable to create window
    ///////////////////////////////////////////////////////////////////////////////
    void onStart(ShowWindowFlags mode) override
    {
      // Create window
      this->Window.create(nullptr, c_arr(L"Hello World")); 
    
      // Show window
      this->Window.show(mode);
      this->Window.update();
    }

    // ----------------------------------- REPRESENTATION -----------------------------------
  };


  //! \alias application_t - Define ANSI/UNICODE application type according to build settings (Size of TCHAR)
  using application_t = HelloWorldApp<default_encoding<TCHAR>::value>;

} // namespace

#endif

