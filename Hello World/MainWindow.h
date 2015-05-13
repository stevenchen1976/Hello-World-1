////////////////////////////////////////////////////////////////////////////////
//! \file HelloWorld\MainWindow.h
//! \brief Defines the main window class
//! \date 7 March 2015
//! \author Nick Crowley
//! \copyright © Nick Crowley. All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "wtl/WTL.hpp"                                          //!< Windows Template Library
#include "wtl/utils/Random.hpp"                                 //!< wtl::Random
#include "wtl/windows/WindowBase.hpp"                           //!< wtl::WindowBase
#include "wtl/windows/controls/Button.hpp"                      //!< wtl::Button
#include "wtl/windows/commands/NewDocumentCommand.hpp"          //!< wtl::NewDocumentCommand
#include "wtl/windows/commands/OpenDocumentCommand.hpp"         //!< wtl::OpenDocumentCommand
#include "wtl/windows/commands/SaveDocumentCommand.hpp"         //!< wtl::SaveDocumentCommand
#include "wtl/windows/commands/CutClipboardCommand.hpp"         //!< wtl::CutClipboardCommand
#include "wtl/windows/commands/CopyClipboardCommand.hpp"        //!< wtl::CopyClipboardCommand
#include "wtl/windows/commands/PasteClipboardCommand.hpp"       //!< wtl::PasteClipboardCommand
#include "wtl/windows/commands/AboutProgramCommand.hpp"         //!< wtl::AboutProgramCommand
#include "wtl/windows/commands/ExitProgramCommand.hpp"          //!< wtl::ExitProgramCommand

using namespace wtl;
using namespace wtl::controls;
using namespace wtl::events;

//! \namespace hw1 - Hello World v1 (Drawing demonstration)
namespace hw1
{
  ///////////////////////////////////////////////////////////////////////////////
  //! \struct MainWindow - Main window class
  //! 
  //! \tparam ENC - Window charactrer encoding (UTF16 if unspecified)
  ///////////////////////////////////////////////////////////////////////////////
  template <Encoding ENC = Encoding::UTF16>
  struct MainWindow : WindowBase<ENC>
  {
    // ---------------------------------- TYPES & CONSTANTS ---------------------------------
  
    //! \alias base - Define base type
    using base = WindowBase<ENC>;
  
    //! \alias type - Define own type
    using type = MainWindow<ENC>;

    //! \alias wndmenu_t - Inherit window menu type
    using wndmenu_t = typename base::wndmenu_t;

    //! \alias wndclass_t - Inherit window class type
    using wndclass_t = typename base::wndclass_t;

    //! \var encoding - Inherit window character encoding
    static constexpr Encoding  encoding = base::encoding;
  
    //! \enum ControlId - Define control Ids
    enum class ControlId : int16
    {
      First = int16(WindowId::User),

      Goodbye = First+1,    //!< Exit button
    };
  
    /////////////////////////////////////////////////////////////////////////////////////////
    //! \struct ExitButton - Defines the 'exit' button control
    /////////////////////////////////////////////////////////////////////////////////////////
    struct ExitButton : Button<encoding>
    {
      // ---------------------------------- TYPES & CONSTANTS ---------------------------------
  
      //! \alias base - Define base type
      using base = Button<encoding>;
    
      // ----------------------------------- REPRESENTATION -----------------------------------
    
      // ------------------------------ CONSTRUCTION & DESTRUCTION ----------------------------
    
      /////////////////////////////////////////////////////////////////////////////////////////
      // ExitButton::ExitButton
      //! Creates a standard button control
      //! 
      //! \param[in] instance - Owning instance
      //! 
      //! \throw platform_error - Unrecognised system window class
      /////////////////////////////////////////////////////////////////////////////////////////
      ExitButton(::HINSTANCE instance) : base(instance)
      {
        // Properties
        this->Ident = window_id(ControlId::Goodbye);
        this->Size = SizeL(100,50);
        this->Position = PointL(500,50);
        //this->Text = c_arr("Goodbye");

        // Events
        this->Click += new ButtonClickEventHandler<base::encoding>(this, &ExitButton::onClick);
      }
      
      // ----------------------------------- STATIC METHODS -----------------------------------

      // ---------------------------------- ACCESSOR METHODS ----------------------------------

      // ----------------------------------- MUTATOR METHODS ----------------------------------

      ///////////////////////////////////////////////////////////////////////////////
      // ExitButton::onClick
      //! Exits the program
      //! 
      //! \param[in] &args - Message arguments
      //! \return LResult - Message result and routing
      ///////////////////////////////////////////////////////////////////////////////
      LResult  onClick(ButtonClickEventArgs<encoding>& args) 
      { 
        // Execute 'Exit Program' gui command
        this->execute(CommandId::App_Exit);
    
        // Handled
        return 0;     
      }

    };

    // ----------------------------------- REPRESENTATION -----------------------------------
  
    ExitButton  GoodbyeBtn;    //!< 'Exit program' button 

    // ------------------------------ CONSTRUCTION & DESTRUCTION ----------------------------
  
    ///////////////////////////////////////////////////////////////////////////////
    // MainWindow::MainWindow
    //! Create the main window
    //! 
    //! \param[in] instance - Module handle
    ///////////////////////////////////////////////////////////////////////////////
    MainWindow(::HINSTANCE instance) : base(getClass(instance)), 
                                       GoodbyeBtn(instance)
    {
      // Properties
      this->Size    = SizeL(640,480);
      this->Style   = WindowStyle::OverlappedWindow;
      this->StyleEx = WindowStyleEx::None;

      // Events
      this->Destroy += new DestroyWindowEventHandler<encoding>(this, &MainWindow::onDestroy);
      this->Show    += new ShowWindowEventHandler<encoding>(this, &MainWindow::onShowWindow);

      // Actions: File
      base::ActionGroups += new ActionGroup<encoding>(CommandGroupId::File, { new NewDocumentCommand<encoding>(*this),
                                                                              new OpenDocumentCommand<encoding>(*this),
                                                                              new SaveDocumentCommand<encoding>(*this),
                                                                              new ExitProgramCommand<encoding>(*this) });
      // Actions: Edit
      base::ActionGroups += new ActionGroup<encoding>(CommandGroupId::Edit, { new CutClipboardCommand<encoding>(),
                                                                              new CopyClipboardCommand<encoding>(),
                                                                              new PasteClipboardCommand<encoding>() });
      // Actions: Help
      base::ActionGroups += new ActionGroup<encoding>(CommandGroupId::Help, { new AboutProgramCommand<encoding>(*this) });
    }
  
    // ----------------------------------- STATIC METHODS -----------------------------------
  
    ///////////////////////////////////////////////////////////////////////////////
    // MainWindow::getClass 
    //! Get the window class
    //! 
    //! \param[in] instance - Module handle
    //! \return wndclass_t& - Window class 
    ///////////////////////////////////////////////////////////////////////////////
    static wndclass_t& getClass(::HINSTANCE instance) 
    {
      static wndclass_t wc(instance,                                    //!< Registering module
                           resource_name(L"MainWindowClass"),           //!< Class name
                           ClassStyle::HRedraw|ClassStyle::VRedraw,     //!< Styles (Redraw upon resize)
                           base::WndProc,                               //!< Window procedure
                           ResourceIdW(),                               //!< Window menu 
                           HCursor(SystemCursor::Arrow),                //!< Window cursor
                           HBrush(Colour::Green),                       //!< Window background brush 
                           HIcon(SystemIcon::WinLogo),                  //!< Large window icon 
                           HIcon(SystemIcon::WinLogo));                 //!< Small window icon 

      // Return singleton
      return wc;
    }
  
    // ---------------------------------- ACCESSOR METHODS ----------------------------------

    // ----------------------------------- MUTATOR METHODS ----------------------------------
  protected:
    ///////////////////////////////////////////////////////////////////////////////
    // MainWindow::onCreate
    //! Called during window creation to modify properties on the fly
    //! 
    //! \param[in] &args - Message arguments containing window creation properties 
    //! \return LResult - Message result and routing
    ///////////////////////////////////////////////////////////////////////////////
    LResult  onCreate(CreateWindowEventArgs<encoding>& args) override
    { 
      // Populate window menu
      this->Menu += base::ActionGroups[CommandGroupId::File];
      this->Menu += base::ActionGroups[CommandGroupId::Edit];
      this->Menu += base::ActionGroups[CommandGroupId::Help];

      // Create 'exit' button
      GoodbyeBtn.create(this, c_arr(L"Goodbye!"));  
      this->Children.insert(GoodbyeBtn);

      // Show 'exit' button
      GoodbyeBtn.show(ShowWindowFlags::Show);

      // Handled
      return 0; 
    }
  
    ///////////////////////////////////////////////////////////////////////////////
    // MainWindow::onDestroy
    //! Called during window destruction
    //! 
    //! \return LResult - Message result and routing
    ///////////////////////////////////////////////////////////////////////////////
    LResult  onDestroy() 
    { 
      // Destroy children
      GoodbyeBtn.destroy();

      // Close program
      this->post<WindowMessage::QUIT>();

      // Handled
      return 0; 
    }
  
    ///////////////////////////////////////////////////////////////////////////////
    // MainWindow::onOwnerDraw
    //! Called to paint the button
    //! 
    //! \param[in,out] args - Message arguments containing drawing data
    //! \return LResult - Message result and routing
    ///////////////////////////////////////////////////////////////////////////////
    //LResult  onOwnerDraw(OwnerDrawEventArgs<encoding>& args)
    //{
    //  if (args.Ident == ControlId::Goodbye)
    //  {
    //    args.Graphics.fill(args.Rect, StockBrush::Green);
    //  }

    //  // Handled
    //  return 0;
    //}

    ///////////////////////////////////////////////////////////////////////////////
    // MainWindow::onPaint
    //! Called to paint the client area of the window
    //! 
    //! \param[in,out] args - Message arguments containing drawing data
    //! \return LResult - Message result and routing
    ///////////////////////////////////////////////////////////////////////////////
    LResult  onPaint(PaintWindowEventArgs<encoding>& args) override
    {
      static int32 numEggs = Random::number(4,8);

      // Draw background
      args.Graphics.fill(args.Rect, StockBrush::Green);

      // Draw river
      drawRiver(args.Graphics, PointL(), args.EraseBackground);

      // Draw 'Hello World' sign
      drawSign(args.Graphics, PointL(80,80), args.EraseBackground);

      // Draw trees
      drawTree(args.Graphics, PointL(450,125), args.EraseBackground);
      drawTree(args.Graphics, PointL(350,130), args.EraseBackground);
      drawTree(args.Graphics, PointL(425,155), args.EraseBackground);
      drawTree(args.Graphics, PointL(360,180), args.EraseBackground);
      drawTree(args.Graphics, PointL(410,210), args.EraseBackground);

      // Draw 'Easter Bunny' in front of sign
      drawEasterBunny(args.Graphics, PointL(320,340), args.EraseBackground);

      // Draw 'Easter Eggs' next to easter bunny
      drawEasterEggs(args.Graphics, PointL(400, 380), numEggs, args.EraseBackground);

      // Handled
      return 0; 
    }
  
    ///////////////////////////////////////////////////////////////////////////////
    // MainWindow::onShowWindow
    //! Called when window is being shown or hidden
    //! 
    //! \param[in] &args - Message arguments 
    //! \return LResult - Message result and routing
    ///////////////////////////////////////////////////////////////////////////////
    LResult  onShowWindow(ShowWindowEventArgs<encoding>& args) 
    { 
      // Handled
      return 0; 
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
    void  drawEasterBunny(DeviceContext& dc, PointL pt, bool erase)
    {
      // Set body colour
      dc += HPen(PenStyle::Solid, 2, Colour::Brown);
      dc += StockBrush::Wheat;

      // [BODY] Medium elogated ellipse
      dc.ellipse( RectL(pt, SizeL(60,80)) );

      // [HEAD] Small circle above
      dc.ellipse( RectL(pt+PointL(10,0), SizeL(40,-40)) );
    
      // [EARS] 2x Small circles above
      dc += StockBrush::Snow;
      dc.ellipse( RectL(pt+PointL(0,-60), SizeL(20,30)) );
      dc.ellipse( RectL(pt+PointL(40,-60), SizeL(20,30)) );

      // [FEET] 2x Small circles below
      dc.ellipse( RectL(pt+PointL(0,40), SizeL(20,40)) );
      dc.ellipse( RectL(pt+PointL(40,40), SizeL(20,40)) );

      // [EYES] 2x Small circles 
      //dc += StockBrush::Red;
      dc.ellipse( RectL(pt+PointL(30,-30), SizeL(10,10)) );
      dc.ellipse( RectL(pt+PointL(15,-30), SizeL(10,10)) );

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
    void  drawEasterEggs(DeviceContext& dc, PointL pt, const int32 numEggs, bool erase)
    {
      // Draw egg backgrounds
      dc += DrawingMode::Opaque;

      // [EGGS] Draw eggs with random colours
      for (int32 idx = 0; idx < numEggs; ++idx)
      {
        static constexpr Colour eggColours[] = { Colour::Beige, Colour::Honey, Colour::Gold, Colour::Green, Colour::Magenta, Colour::Rose,
                                                 Colour::Yellow, Colour::SkyBlue, Colour::Orange, Colour::Leaves, Colour::Teal };

        // Randomize egg properties
        HBrush eggBrush(random_enum<HatchStyle>(), random_element(eggColours));
        HPen eggPen(PenStyle::Solid, 2, random_element(eggColours));
      
        // Set egg colour
        dc.setBackColour(random_element(eggColours));
        dc += eggPen;
        dc += eggBrush;

        // [EGG] Draw small oval
        dc.ellipse( RectL(pt+PointL(idx*30,0), SizeL(20,30)) );

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
    void  drawRiver(DeviceContext& dc, PointL pt, bool erase)
    {
      // Light blue river & dark highlights
      dc += HPen(PenStyle::Solid, 2, Colour::Blue);
      dc += StockBrush::Cyan;

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
    void  drawTree(DeviceContext& dc, PointL pt, bool erase)
    {
      // Set dark green outline + light green interior
      dc += HPen(PenStyle::Solid, 2, Colour::Forest);
      dc += StockBrush::Leaves;

      // [LEAVES] Small green triangle
      dc.triangle( TriangleL(pt, 50, 50) );

      // Set brown interior + black outline
      static HBrush trunkBrush(HatchStyle::ForwardDiagonal, Colour::Black);
      dc += trunkBrush;  

      // Set brown interior + black outline
      dc.setBackColour(Colour::Brown);
      dc += DrawingMode::Opaque;
    
      // [TRUNK] Small brown square
      dc.rect( RectL(pt + PointL(10,2), SizeL(30,30)) );

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
    void  drawSign(DeviceContext& dc, PointL pt, bool erase)
    {
      // Large text
      static const HFont largeFont = DeviceContext::ScreenDC.getFont(c_arr("MS Shell Dlg 2"), 16, FontWeight::Bold);
      dc += largeFont;

      // [SIGN] Black outline + brown interior
      dc += HPen(PenStyle::Solid, 2, Colour::Black);
      dc += StockBrush::Brown;

      // [SIGN] Large rectangle
      RectL signRect(pt, SizeL(200,140));
      dc.rect(signRect);
    
      // Set brown interior + black outline
      static HBrush legBrush(HatchStyle::CrossDiagonal, Colour::Black);
      dc += legBrush;  

      // Set brown interior + black outline
      dc.setBackColour(Colour::Brown);
      dc += DrawingMode::Opaque;
    
      // [LEGS] 2x small rectangles below sign
      dc.rect( RectL(pt + PointL(30,140), SizeL(40,30)) );
      dc.rect( RectL(pt + PointL(130,140), SizeL(40,30)) );

      // Transparent white text
      dc += DrawingMode::Transparent;
      dc.setTextColour(Colour::White);
    
      // [TEXT] Draw sign text
      dc.write(c_arr("Hi Mum! Hi Dad!" "\n\n" 
                     "I love you"      "\n\n" 
                     "Happy Easter!"   "\n\n"
                     "From Nick"), signRect, DrawTextFlags::Centre); 

      // Cleanup
      dc.clear();
    }

  };

} // namespace

#endif

