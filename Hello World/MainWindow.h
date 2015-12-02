////////////////////////////////////////////////////////////////////////////////
//! \file HelloWorld\MainWindow.h
//! \brief Defines the main window class
//! \date 7 March 2015
//! \author Nick Crowley
//! \copyright © Nick Crowley. All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <wtl/WTL.hpp>                                          //!< Windows Template Library
#include <wtl/utils/Random.hpp>                                 //!< wtl::Random
#include <wtl/windows/Window.hpp>                               //!< wtl::Window
#include <wtl/windows/controls/Button.hpp>                      //!< wtl::Button
#include <wtl/windows/commands/NewDocumentCommand.hpp>          //!< wtl::NewDocumentCommand
#include <wtl/windows/commands/OpenDocumentCommand.hpp>         //!< wtl::OpenDocumentCommand
#include <wtl/windows/commands/SaveDocumentCommand.hpp>         //!< wtl::SaveDocumentCommand
#include <wtl/windows/commands/CutClipboardCommand.hpp>         //!< wtl::CutClipboardCommand
#include <wtl/windows/commands/CopyClipboardCommand.hpp>        //!< wtl::CopyClipboardCommand
#include <wtl/windows/commands/PasteClipboardCommand.hpp>       //!< wtl::PasteClipboardCommand
#include <wtl/windows/commands/AboutProgramCommand.hpp>         //!< wtl::AboutProgramCommand
#include <wtl/windows/commands/ExitProgramCommand.hpp>          //!< wtl::ExitProgramCommand


//! \namespace hw1 - Hello World v1 (Drawing demonstration)
namespace hw1
{
  ///////////////////////////////////////////////////////////////////////////////
  //! \struct MainWindow - Main window class
  //! 
  //! \tparam ENC - Window charactrer encoding (Default is UTF-16)
  ///////////////////////////////////////////////////////////////////////////////
  template <wtl::Encoding ENC = wtl::Encoding::UTF16>
  struct MainWindow : wtl::Window<ENC>
  {
    // ---------------------------------- TYPES & CONSTANTS ---------------------------------
  
    //! \alias base - Define base type
    using base = wtl::Window<ENC>;
  
    //! \alias type - Define own type
    using type = MainWindow<ENC>;

    //! \alias class_t - Inherit window class type
    using class_t = typename base::class_t;

    //! \var encoding - Inherit window character encoding
    static constexpr wtl::Encoding  encoding = base::encoding;
  
    //! \enum ControlId - Define control Ids
    enum class ControlId : int16_t
    {
      First = int16_t(wtl::WindowId::User),

      Goodbye = First+1,    //!< Exit button
    };
  
    // ----------------------------------- REPRESENTATION -----------------------------------
  
    wtl::Button<encoding>  Button1;    //!< 'Exit program' button 

    // ------------------------------ CONSTRUCTION & DESTRUCTION ----------------------------
  
    ///////////////////////////////////////////////////////////////////////////////
    // MainWindow::MainWindow
    //! Create the main window
    ///////////////////////////////////////////////////////////////////////////////
    MainWindow() : Button1(wtl::window_id(ControlId::Goodbye))
    {
      //! Initialize window properties
      this->Size    = wtl::SizeL(640,480);
      this->Style   = wtl::WindowStyle::OverlappedWindow;
      this->StyleEx = wtl::WindowStyleEx::None;
      this->Text    = "Hello World";
      
      //! Listen for window events
      this->Destroy += new wtl::DestroyWindowEventHandler<encoding>(this, &MainWindow::onDestroy);
      this->Show    += new wtl::ShowWindowEventHandler<encoding>(this, &MainWindow::onShowWindow);

      //! Initialize child controls
      Button1.Position  = wtl::PointL(500,20);
      Button1.Icon      = wtl::icon_resource<encoding>(wtl::CommandId::App_Exit).Handle;
      Button1.Size      = wtl::SizeL(100,50);
      Button1.Text      = "Goodbye";
      Button1.Visible   = true;
      Button1.Click    += new wtl::ButtonClickEventHandler<encoding>(this, &MainWindow::onButton1_Click);
    }
  
    // ----------------------------------- STATIC METHODS -----------------------------------
  public:
    ///////////////////////////////////////////////////////////////////////////////
    // MainWindow::registerClass 
    //! Registers the window-class 
    //! 
    //! \param[in] instance - Registering module 
    //! \return const WindowClass<encoding>& - Shared window class 
    //! 
    //! \throw wtl::platform_error - Unable to register window class
    ///////////////////////////////////////////////////////////////////////////////
    static const wtl::WindowClass<encoding>& registerClass(::HINSTANCE instance) 
    {
      static wtl::String<encoding> name("MainWindowClass");

      static wtl::WindowClass<encoding> wc(instance,                                              //!< Registering module
                                           name.c_str(),                                          //!< Class name
                                           wtl::ClassStyle::HRedraw|wtl::ClassStyle::VRedraw,     //!< Styles (Redraw upon resize)
                                           base::WndProc,                                         //!< Window procedure
                                           wtl::ResourceIdW(),                                    //!< Window menu 
                                           wtl::HCursor(wtl::SystemCursor::Arrow),                //!< Window cursor
                                           wtl::HBrush(wtl::Colour::Green),                       //!< Window background brush 
                                           wtl::HIcon(wtl::SystemIcon::WinLogo),                  //!< Large window icon 
                                           wtl::HIcon(wtl::SystemIcon::WinLogo));                 //!< Small window icon 

      // Return singleton
      return wc;
    }
  
    // ---------------------------------- ACCESSOR METHODS ----------------------------------
  public:
    /////////////////////////////////////////////////////////////////////////////////////////
    // MainWindow::wndclass const
    //! Get the window class
    //! 
    //! \return const WindowClass<encoding>& - Shared window class
    /////////////////////////////////////////////////////////////////////////////////////////
    const wtl::WindowClass<encoding>& wndclass() const override
    {
      return registerClass(nullptr);
    }
    
    // ----------------------------------- MUTATOR METHODS ----------------------------------
  private:    
    ///////////////////////////////////////////////////////////////////////////////
    // MainWindow::onButton1_Click
    //! Called to exits the program when user clicks the exit button
    //! 
    //! \param[in] args - Message arguments
    //! \return wtl::LResult - Routing indicating message was handled
    ///////////////////////////////////////////////////////////////////////////////
    wtl::LResult  onButton1_Click(wtl::ButtonClickEventArgs<encoding> args) 
    { 
      // Execute 'Exit Program' gui command
      Button1.execute(wtl::CommandId::App_Exit);
    
      // [Handled] 
      return {wtl::MsgRoute::Handled, 0}; 
    }

    ///////////////////////////////////////////////////////////////////////////////
    // MainWindow::onCreate
    //! Called during window creation to modify properties on the fly
    //! 
    //! \param[in,out] &args - Message arguments containing window creation properties 
    //! \return wtl::LResult - Message result and routing
    ///////////////////////////////////////////////////////////////////////////////
    wtl::LResult  onCreate(wtl::CreateWindowEventArgs<encoding>& args) override
    { 
      // Populate window menu
      this->Menu += base::CommandGroups[wtl::CommandGroupId::File];
      this->Menu += base::CommandGroups[wtl::CommandGroupId::Help];

      // Create 'exit' button child ctrl
      this->Children.create(Button1);

      // Show 'exit' button
      Button1.show(wtl::ShowWindowFlags::Show);
      
      // [Handled] Accept window parameters
      return {wtl::MsgRoute::Handled, 0};
    }
  
    ///////////////////////////////////////////////////////////////////////////////
    // MainWindow::onDestroy
    //! Called during window destruction
    //! 
    //! \return wtl::LResult - Routing indicating message was handled
    ///////////////////////////////////////////////////////////////////////////////
    wtl::LResult  onDestroy() 
    { 
      // Destroy children
      Button1.destroy();

      // Close program
      this->post(wtl::WindowMessage::Quit);
      
      // [Handled] 
      return {wtl::MsgRoute::Handled, 0};
    }
  
    ///////////////////////////////////////////////////////////////////////////////
    // MainWindow::onPaint
    //! Called to paint the client area of the window
    //! 
    //! \param[in,out] args - Message arguments containing drawing data
    //! \return wtl::LResult - Message result and routing
    ///////////////////////////////////////////////////////////////////////////////
    wtl::LResult  onPaint(wtl::PaintWindowEventArgs<encoding>& args) override
    {
      static int32_t numEggs = wtl::Random::number(4,8);

      // Draw background
      args.Graphics.fill(args.Rect, wtl::StockBrush::Green);

      // Draw river
      drawRiver(args.Graphics, wtl::PointL(), args.EraseBackground);

      // Draw 'Hello World' sign
      drawSign(args.Graphics, wtl::PointL(80,80), args.EraseBackground);

      // Draw trees
      drawTree(args.Graphics, wtl::PointL(450,125), args.EraseBackground);
      drawTree(args.Graphics, wtl::PointL(350,130), args.EraseBackground);
      drawTree(args.Graphics, wtl::PointL(425,155), args.EraseBackground);
      drawTree(args.Graphics, wtl::PointL(360,180), args.EraseBackground);
      drawTree(args.Graphics, wtl::PointL(410,210), args.EraseBackground);

      // Draw 'Easter Bunny' in front of sign
      drawEasterBunny(args.Graphics, wtl::PointL(320,340), args.EraseBackground);

      // Draw 'Easter Eggs' next to easter bunny
      drawEasterEggs(args.Graphics, wtl::PointL(400, 380), numEggs, args.EraseBackground);

      // Handled
      return 0; 
    }
  
    ///////////////////////////////////////////////////////////////////////////////
    // MainWindow::onShowWindow
    //! Called when window is being shown or hidden
    //! 
    //! \param[in] &args - Message arguments 
    //! \return wtl::LResult - Routing indicating message was handled
    ///////////////////////////////////////////////////////////////////////////////
    wtl::LResult  onShowWindow(wtl::ShowWindowEventArgs<encoding> args) 
    { 
      // [Handled] 
      return {wtl::MsgRoute::Handled, 0};
    }
  
  private:
    ///////////////////////////////////////////////////////////////////////////////
    // MainWindow::drawEasterBunny
    //! Draws the easter Bunny at a point
    //! 
    //! \param[in] dc - Device context
    //! \param[in] pt - Target
    //! \param[in] erase - Whether to erase before drawing
    ///////////////////////////////////////////////////////////////////////////////
    void  drawEasterBunny(wtl::DeviceContext& dc, wtl::PointL pt, bool erase)
    {
      // Set body colour
      dc += wtl::HPen(wtl::PenStyle::Solid, 2, wtl::Colour::Brown);
      dc += wtl::StockBrush::Wheat;

      // [BODY] Medium elogated ellipse
      dc.ellipse( wtl::RectL(pt, wtl::SizeL(60,80)) );

      // [HEAD] Small circle above
      dc.ellipse( wtl::RectL(pt+wtl::PointL(10,0), wtl::SizeL(40,-40)) );
    
      // [EARS] 2x Small circles above
      dc += wtl::StockBrush::Snow;
      dc.ellipse( wtl::RectL(pt+wtl::PointL(0,-60), wtl::SizeL(20,30)) );
      dc.ellipse( wtl::RectL(pt+wtl::PointL(40,-60), wtl::SizeL(20,30)) );

      // [FEET] 2x Small circles below
      dc.ellipse( wtl::RectL(pt+wtl::PointL(0,40), wtl::SizeL(20,40)) );
      dc.ellipse( wtl::RectL(pt+wtl::PointL(40,40), wtl::SizeL(20,40)) );

      // [EYES] 2x Small circles 
      //dc += wtl::StockBrush::Red;
      dc.ellipse( wtl::RectL(pt+wtl::PointL(30,-30), wtl::SizeL(10,10)) );
      dc.ellipse( wtl::RectL(pt+wtl::PointL(15,-30), wtl::SizeL(10,10)) );

      // Cleanup
      dc.clear();
    }

    ///////////////////////////////////////////////////////////////////////////////
    // MainWindow::drawEasterEggs
    //! Draws easter eggs at a point
    //! 
    //! \param[in] dc - Device context
    //! \param[in] pt - Target
    //! \param[in] numEggs - Number of eggs to draw
    //! \param[in] erase - Whether to erase before drawing
    ///////////////////////////////////////////////////////////////////////////////
    void  drawEasterEggs(wtl::DeviceContext& dc, wtl::PointL pt, const int32_t numEggs, bool erase)
    {
      static constexpr wtl::HatchStyle styles[] = { wtl::HatchStyle::Horizontal, wtl::HatchStyle::Vertical, 
                                                    wtl::HatchStyle::ForwardDiagonal, wtl::HatchStyle::BackwardDiagonal, 
                                                    wtl::HatchStyle::Cross, wtl::HatchStyle::CrossDiagonal };
      // Draw egg backgrounds
      dc += wtl::DrawingMode::Opaque;

      // [EGGS] Draw eggs with random colours
      for (int32_t idx = 0; idx < numEggs; ++idx)
      {
        static constexpr wtl::Colour eggColours[] = { wtl::Colour::Beige, wtl::Colour::Honey, wtl::Colour::Gold, wtl::Colour::Green, wtl::Colour::Magenta, wtl::Colour::Rose,
                                                      wtl::Colour::Yellow, wtl::Colour::SkyBlue, wtl::Colour::Orange, wtl::Colour::Leaves, wtl::Colour::Teal };

        // Randomize egg properties
        wtl::HBrush eggBrush(wtl::random_element(styles), wtl::random_element(eggColours));
        wtl::HPen eggPen(wtl::PenStyle::Solid, 2, wtl::random_element(eggColours));
      
        // Set egg colour
        dc.setBackColour(wtl::random_element(eggColours));
        dc += eggPen;
        dc += eggBrush;

        // [EGG] Draw small oval
        dc.ellipse( wtl::RectL(pt+wtl::PointL(idx*30,0), wtl::SizeL(20,30)) );

        // Cleanup
        dc.clear();
      }
    
    
    }

    ///////////////////////////////////////////////////////////////////////////////
    // MainWindow::drawRiver
    //! Draws a river across the screen in an upward arc
    //! 
    //! \param[in] dc - Device context
    //! \param[in] pt - Ignored
    //! \param[in] erase - Whether to erase before drawing
    ///////////////////////////////////////////////////////////////////////////////
    void  drawRiver(wtl::DeviceContext& dc, wtl::PointL pt, bool erase)
    {
      // Light blue river & dark highlights
      dc += wtl::HPen(wtl::PenStyle::Solid, 2, wtl::Colour::Blue);
      dc += wtl::StockBrush::Cyan;

      ::POINT river[] = { {0, 300},   {200, 280}, {400, 260}, {640, 250},
                          {640, 300}, {480, 310}, {280, 360}, {120, 420},  {0, 430} };

      // [RIVER] Fill polygon
      dc.polygon(river);

      // Cleanup
      dc.clear();
    }
  
    ///////////////////////////////////////////////////////////////////////////////
    // MainWindow::drawTree
    //! Draws a tree at a point
    //! 
    //! \param[in] dc - Device context
    //! \param[in] pt - Target
    //! \param[in] erase - Whether to erase before drawing
    ///////////////////////////////////////////////////////////////////////////////
    void  drawTree(wtl::DeviceContext& dc, wtl::PointL pt, bool erase)
    {
      // Set dark green outline + light green interior
      dc += wtl::HPen(wtl::PenStyle::Solid, 2, wtl::Colour::Forest);
      dc += wtl::StockBrush::Leaves;

      // [LEAVES] Small green triangle
      dc.triangle( wtl::TriangleL(pt, 50, 50) );

      // Set brown interior + black outline
      static wtl::HBrush trunkBrush(wtl::HatchStyle::ForwardDiagonal, wtl::Colour::Black);
      dc += trunkBrush;  

      // Set brown interior + black outline
      dc.setBackColour(wtl::Colour::Brown);
      dc += wtl::DrawingMode::Opaque;
    
      // [TRUNK] Small brown square
      dc.rect( wtl::RectL(pt + wtl::PointL(10,2), wtl::SizeL(30,30)) );

      // Cleanup
      dc.clear();
    }
  
    ///////////////////////////////////////////////////////////////////////////////
    // MainWindow::drawSign
    //! Draws the 'Hello World' sign at a point
    //! 
    //! \param[in] dc - Device context
    //! \param[in] pt - Top left point of sign
    //! \param[in] erase - Whether to erase before drawing
    ///////////////////////////////////////////////////////////////////////////////
    void  drawSign(wtl::DeviceContext& dc, wtl::PointL pt, bool erase)
    {
      // Large text
      static const wtl::HFont largeFont = wtl::DeviceContext::ScreenDC.getFont(wtl::c_str("MS Shell Dlg 2"), 16, wtl::FontWeight::Bold);
      dc += largeFont;

      // [SIGN] Black outline + brown interior
      dc += wtl::HPen(wtl::PenStyle::Solid, 2, wtl::Colour::Black);
      dc += wtl::StockBrush::Brown;

      // [SIGN] Large rectangle
      wtl::RectL signRect(pt, wtl::SizeL(200,140));
      dc.rect(signRect);
    
      // Set brown interior + black outline
      static wtl::HBrush legBrush(wtl::HatchStyle::CrossDiagonal, wtl::Colour::Black);
      dc += legBrush;  

      // Set brown interior + black outline
      dc.setBackColour(wtl::Colour::Brown);
      dc += wtl::DrawingMode::Opaque;
    
      // [LEGS] 2x small rectangles below sign
      dc.rect( wtl::RectL(pt + wtl::PointL(30,140), wtl::SizeL(40,30)) );
      dc.rect( wtl::RectL(pt + wtl::PointL(130,140), wtl::SizeL(40,30)) );

      // Transparent white text
      dc += wtl::DrawingMode::Transparent;
      dc.setTextColour(wtl::Colour::White);
    
      // [TEXT] Draw sign text
      dc.write(wtl::c_str("\n Hello World 1"
                          "\n\n From Windows"
                          "\n\n Template Library"), signRect, wtl::DrawTextFlags::Centre); 

      // Cleanup
      dc.clear();
    }

  };

} // namespace

#endif

