////////////////////////////////////////////////////////////////////////////////
//! \file HelloWorld\HelloWorldApp.h
//! \brief Defines the application 
//! \date 7 March 2015
//! \author Nick Crowley
//! \copyright © Nick Crowley. All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#ifndef HELLO_WORLD_H
#define HELLO_WORLD_H

// Target Platform v5.01 (WindowsXP)
//#include <WinSDKVer.h>
#define _WIN32_WINNT    _WIN32_WINNT_WINXP
//#include <SDKDDKVer.h>

#include "wtl/WTL.hpp"                      //!< Windows Template Library
#include "wtl/modules/Application.hpp"      //!< wtl::Application
#include "MainWindow.h"                     //!< hw1::Mainwindow

//using namespace wtl;

//! \namespace hw1 - Hello World v1 (Drawing demonstration)
namespace hw1
{

  ///////////////////////////////////////////////////////////////////////////////
  //! \struct HelloWorldApp - Encapsulates the 'Hello World' program
  //! 
  //! \tparam ENC - Window charactrer encoding (Default is UTF-16)
  ///////////////////////////////////////////////////////////////////////////////
  template <wtl::Encoding ENC = wtl::Encoding::UTF16>
  struct HelloWorldApp : wtl::Application<MainWindow<ENC>>
  {
    // ---------------------------------- TYPES & CONSTANTS ---------------------------------
    
    //! \alias type - Define own type
    using type = HelloWorldApp<ENC>;
    
    //! \alias base - Define base type
    using base = wtl::Application<MainWindow<ENC>>;
    
    //! \alias char_t - Inherit character type
    using char_t = typename base::char_t;

    //! \var encoding - Define app character encoding
    static constexpr wtl::Encoding  encoding = ENC;
  
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
    
    /////////////////////////////////////////////////////////////////////////////////////////
    // HelloWorldApp::name const 
    //! Get the application name
    //!
    //! \return const char_t* - Full application name
    /////////////////////////////////////////////////////////////////////////////////////////
    const char_t* name() const override
    {
      return wtl::getValue<ENC>("Hello World 1", L"Hello World 1");
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////
    // HelloWorldApp::version const 
    //! Get the application version
    //!
    //! \return const char_t* - Version string
    /////////////////////////////////////////////////////////////////////////////////////////
    const char_t* version() const override 
    {
      return wtl::getValue<ENC>("v1.00", L"v1.00");
    }

    // ----------------------------------- MUTATOR METHODS ----------------------------------  
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
      // Create window
      this->Window.create();
    
      // Show window
      this->Window.show(mode);
      this->Window.update();
    }

    // ----------------------------------- REPRESENTATION -----------------------------------
  };


  //! \alias application_t - Define ANSI/UNICODE application type according to build settings (Size of TCHAR)
  using application_t = HelloWorldApp<wtl::default_encoding_t<::TCHAR>::value>;

} // namespace

#endif

