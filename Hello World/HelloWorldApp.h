////////////////////////////////////////////////////////////////////////////////
//! \file HelloWorld\HelloWorldApp.h
//! \brief Defines the application 
//! \date 7 March 2015
//! \author Nick Crowley
//! \copyright © Nick Crowley. All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#ifndef HELLO_WORLD_H
#define HELLO_WORLD_H

//! \def _WIN32_WINNT - Define build target (Windows XP)
#define _WIN32_WINNT    _WIN32_WINNT_WINXP

#include <wtl/WTL.hpp>                        //!< Windows Template Library
#include <wtl/modules/Application.hpp>        //!< wtl::Application
#include <wtl/windows/skins/ThemedSkin.hpp>   //!< wtl::ThemedSkin
#include "MainWindow.h"                       //!< hw1::Mainwindow

///////////////////////////////////////////////////////////////////////////////
//! \namespace hw1 - Hello World v1 (Drawing demonstration)
///////////////////////////////////////////////////////////////////////////////
namespace hw1
{
  ///////////////////////////////////////////////////////////////////////////////
  //! \var encoding - Application character encoding  (Based on size of TCHAR)
  ///////////////////////////////////////////////////////////////////////////////
  constexpr wtl::Encoding encoding = wtl::default_encoding_t<::TCHAR>::value;

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
    //! \param[in] app - Application instance
    ///////////////////////////////////////////////////////////////////////////////
    HelloWorldApp(::HMODULE app) : base(app)
    {
      // Initialize default window skin
      wtl::ThemedSkin<encoding>::get();

      // Register main window class
      MainWindow<encoding>::registerClass(app);

      //! Populate the program GUI commands  ['File' command grouping]
      MainWindow<encoding>::CommandGroups += new wtl::CommandGroup<encoding>(wtl::CommandGroupId::File, 
      { 
        new wtl::ExitProgramCommand<encoding>(this->window()) 
      });
      
      //! Populate the program GUI commands  ['Help' command grouping]
      MainWindow<encoding>::CommandGroups += new wtl::CommandGroup<encoding>(wtl::CommandGroupId::Help, 
      { 
        new wtl::AboutProgramCommand<encoding>(this->window()) 
      });
    }

    // ---------------------------------- ACCESSOR METHODS ----------------------------------
    
    /////////////////////////////////////////////////////////////////////////////////////////
    // HelloWorldApp::name const 
    //! Get the application name
    //!
    //! \return String<encoding> - Full application name
    /////////////////////////////////////////////////////////////////////////////////////////
    wtl::String<encoding> name() const override
    {
      return "Hello World 1";
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////
    // HelloWorldApp::version const 
    //! Get the application version
    //!
    //! \return String<encoding> - Version string
    /////////////////////////////////////////////////////////////////////////////////////////
    wtl::String<encoding> version() const override 
    {
      return "v1.00";
    }

    // ----------------------------------- MUTATOR METHODS ----------------------------------  
  private:
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
      this->window().create();
    
      // Show window
      this->window().show(mode);
      this->window().update();
    }

    // ----------------------------------- REPRESENTATION -----------------------------------
  };

  ///////////////////////////////////////////////////////////////////////////////
  //! \alias application_t - Define ANSI/UNICODE application type according to build settings (Size of TCHAR)
  ///////////////////////////////////////////////////////////////////////////////
  using application_t = HelloWorldApp<encoding>;

} // namespace

#endif

