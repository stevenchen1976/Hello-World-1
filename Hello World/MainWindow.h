////////////////////////////////////////////////////////////////////////////////
//! \file HelloWorld\MainWindow.h
//! \brief Defines the main window class
//! \date 7 March 2015
//! \author Nick Crowley
//! \copyright © Nick Crowley. All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "wtl/WTL.hpp"   // Windows Template Library

///////////////////////////////////////////////////////////////////////////////
//! \struct MainWindow - Main window class
//! 
//! \tparam ENC - Window charactrer encoding (UTF16 if unspecified)
///////////////////////////////////////////////////////////////////////////////
template <wtl::Encoding ENC = wtl::Encoding::UTF16>
struct MainWindow : wtl::WindowBase<ENC>
{
  // ------------------------ TYPES --------------------------
  
  //! \alias base - Define base type
  using base = wtl::WindowBase<ENC>;

  //! \alias wndmenu_t - Inherit window menu type
  using wndmenu_t = typename base::wndmenu_t;

  //! \alias wndclass_t - Inherit window class type
  using wndclass_t = typename base::wndclass_t;

  //! \enum ControlId - Define control Ids
  enum struct ControlId : int16
  {
    First = int16(wtl::WindowId::User),

    Goodbye = First+1,    //!< Exit button
  };
  
  //! \var encoding - Inherit window character encoding
  static constexpr wtl::Encoding  encoding = base::encoding;

  // -------------------- REPRESENTATION ---------------------
  
  wtl::Button<encoding>  GoodbyeBtn;    //!< 'Exit program' button 

  // --------------------- CONSTRUCTION ----------------------
  
  ///////////////////////////////////////////////////////////////////////////////
  // MainWindow::MainWindow
  //! Create the main window
  //! 
  //! \param[in] instance - Module handle
  ///////////////////////////////////////////////////////////////////////////////
  MainWindow(HINSTANCE instance) : base(getClass(instance)), 
                                   GoodbyeBtn(instance)
  {
    // Define Window event listeners
    this->Destroy += new wtl::DestroyWindowEventHandler<encoding>(this, &MainWindow::onDestroy);
    this->Show += new wtl::ShowWindowEventHandler<encoding>(this, &MainWindow::onShowWindow);

    // Attach Child Control event listeners
    this->GoodbyeBtn.Click += new wtl::ButtonClickEventHandler<base::encoding>(this, &MainWindow::onGoodbyeClick);

    // Define 'File' actions
    this->ActionGroups += new wtl::ActionGroup<encoding>(wtl::CommandGroupId::File, { new wtl::NewDocumentCommand<encoding>(*this),
                                                                                       new wtl::OpenDocumentCommand<encoding>(*this),
                                                                                       new wtl::SaveDocumentCommand<encoding>(*this),
                                                                                       new wtl::ExitProgramCommand<encoding>(*this) });
    // Define 'Edit' actions
    this->ActionGroups += new wtl::ActionGroup<encoding>(wtl::CommandGroupId::Edit, { new wtl::CutClipboardCommand<encoding>(),
                                                                                       new wtl::CopyClipboardCommand<encoding>(),
                                                                                       new wtl::PasteClipboardCommand<encoding>() });
    // Define 'Help' actions
    this->ActionGroups += new wtl::ActionGroup<encoding>(wtl::CommandGroupId::Help, { new wtl::AboutProgramCommand<encoding>(*this) });
  }
  
  // ------------------------ STATIC -------------------------
  
  ///////////////////////////////////////////////////////////////////////////////
  // MainWindow::getClass 
  //! Get the window class
  //! 
  //! \param[in] instance - Module handle
  //! \return wndclass_t& - Window class 
  ///////////////////////////////////////////////////////////////////////////////
  static wndclass_t& getClass(HINSTANCE instance) 
  {
    static wndclass_t wc(instance,                                              //!< Registering module
                         wtl::resource_name(L"MainWindowClass"),                //!< Class name
                         wtl::ClassStyle::HRedraw|wtl::ClassStyle::VRedraw,     //!< Styles (Redraw upon resize)
                         base::WndProc,                                         //!< Window procedure
                         wtl::ResourceIdW::npos,                                //!< Window menu 
                         wtl::HCursor(wtl::SystemCursor::Arrow),                //!< Window cursor
                         wtl::HBrush(wtl::Colour::Green),                       //!< Window background brush 
                         wtl::HIcon(wtl::SystemIcon::WinLogo),                  //!< Large window icon 
                         wtl::HIcon(wtl::SystemIcon::WinLogo));                 //!< Small window icon 

    // Return singleton
    return wc;
  }
  
  // ---------------------- ACCESSORS ------------------------

  // ----------------------- MUTATORS ------------------------
protected:
  ///////////////////////////////////////////////////////////////////////////////
  // MainWindow::onCreate
  //! Called during window creation to modify properties on the fly
  //! 
  //! \param[in] &args - Message arguments containing window creation properties 
  //! \return LResult - Message result and routing
  ///////////////////////////////////////////////////////////////////////////////
  wtl::LResult  onCreate(wtl::CreateWindowEventArgs<encoding>& args) override
  { 
    // Populate window menu
    *this->Menu += this->ActionGroups[wtl::CommandGroupId::File];
    *this->Menu += this->ActionGroups[wtl::CommandGroupId::Edit];
    *this->Menu += this->ActionGroups[wtl::CommandGroupId::Help];

    // Create 'exit' button
    GoodbyeBtn.create(*this, 
                      wtl::c_arr(L"Goodbye!"), 
                      wtl::RectL(500,50,600,100), 
                      ControlId::Goodbye, 
                      wtl::WindowStyle::ChildWindow | wtl::ButtonStyle::Centre|wtl::ButtonStyle::Notify|wtl::ButtonStyle::OwnerDraw);

    GoodbyeBtn.show(wtl::ShowWindowFlags::Show);

    // Handled
    return 0; 
  }
  
  ///////////////////////////////////////////////////////////////////////////////
  // MainWindow::onGoodbyeClick
  //! Called in response to clicking 'GoodBye' button
  //! 
  //! \param[in] &args - Message arguments
  //! \return LResult - Message result and routing
  ///////////////////////////////////////////////////////////////////////////////
  wtl::LResult  onGoodbyeClick(wtl::ButtonClickEventArgs<encoding>& args) 
  { 
    // Execute 'Exit Program' gui command
    this->execute(wtl::CommandId::App_Exit);
    
    // Handled
    return 0;     
  }

  ///////////////////////////////////////////////////////////////////////////////
  // MainWindow::onDestroy
  //! Called during window destruction
  //! 
  //! \return LResult - Message result and routing
  ///////////////////////////////////////////////////////////////////////////////
  wtl::LResult  onDestroy() 
  { 
    // Destroy children
    GoodbyeBtn.destroy();

    // Close program
    this->post<wtl::WindowMessage::QUIT>();

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
  //wtl::LResult  onOwnerDraw(wtl::OwnerDrawEventArgs<encoding>& args)
  //{
  //  if (args.Ident == ControlId::Goodbye)
  //  {
  //    args.Graphics.fill(args.Rect, wtl::StockBrush::Green);
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
  wtl::LResult  onPaint(wtl::PaintWindowEventArgs<encoding>& args) override
  {
    static int32 numEggs = wtl::Random::number(4,8);

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
  //! \return LResult - Message result and routing
  ///////////////////////////////////////////////////////////////////////////////
  wtl::LResult  onShowWindow(wtl::ShowWindowEventArgs<encoding>& args) 
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
  void  drawEasterEggs(wtl::DeviceContext& dc, wtl::PointL pt, const int32 numEggs, bool erase)
  {
    // Draw egg backgrounds
    dc += wtl::DrawingMode::Opaque;

    // [EGGS] Draw eggs with random colours
    for (int32 idx = 0; idx < numEggs; ++idx)
    {
      static constexpr wtl::Colour eggColours[] = {wtl::Colour::Beige, wtl::Colour::Honey, wtl::Colour::Gold, wtl::Colour::Green, wtl::Colour::Magenta, wtl::Colour::Rose,
                                                   wtl::Colour::Yellow, wtl::Colour::SkyBlue, wtl::Colour::Orange, wtl::Colour::Leaves, wtl::Colour::Teal};

      // Randomize egg properties
      wtl::HBrush eggBrush(wtl::random_enum<wtl::HatchStyle>(), wtl::random_element(eggColours));
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
    static const wtl::HFont largeFont = wtl::ScreenDC.getFont(wtl::c_arr("MS Shell Dlg 2"), 16, wtl::FontWeight::Bold);
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
    dc.write(wtl::c_arr("Hi Mum! Hi Dad!" "\n\n" 
                        "I love you"      "\n\n" 
                        "Happy Easter!"   "\n\n"
                        "From Nick"), signRect, wtl::DrawTextFlags::Centre); 

    // Cleanup
    dc.clear();
  }

};


#endif

