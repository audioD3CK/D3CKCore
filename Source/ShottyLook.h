#pragma once
#include "JuceHeader.h"

class ShottyLook :
	public LookAndFeel_V3,
	public ReferenceCountedObject

{
protected:
    ShottyLook();
public:
    ~ShottyLook();
	juce_DeclareSingleton(ShottyLook,false);
   //button
	void drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColor, bool isMouseOverButton, bool isButtonDown)override;
    void drawButtonText(Graphics& g, TextButton& button, bool isMouseOverButton, bool isButtonDown)override;
    void drawDrawableButton (Graphics&, DrawableButton&, bool isMouseOverButton, bool isButtonDown)override;

   //combobox
	void drawComboBox(Graphics & g, int w, int h, const bool isDown, int bx, int by, int bw, int bh, ComboBox& box);
	//slider
	void drawLinearSlider(Graphics& g, int x, int y, int w, int h, float pos, float min, float max, const Slider::SliderStyle style, Slider& slider);
    void drawRotarySlider(Graphics & g, int x, int y, int width, int height, float sliderPosition, const float rotaryStartAngle, const float rotaryEndAngle, Slider & slider);
	//scrollbar
	int getScrollbarButtonSize(ScrollBar & scrollbar);
    void drawScrollbarButton(Graphics & g, ScrollBar & scrollbar, int width, int height, int buttonDirection, bool isScrollbarVertical, bool isMouseOver, bool isButtonDown);
    void drawScrollbar(Graphics & g, ScrollBar & scrollbar, int x, int y, int width, int height, bool isScrollbarVertical, int thumbStartPosition, int thumbSize, bool isMouseOver, bool isMouseDown);
    int getDefaultScrollbarWidth();
	//texteditor
	void drawTextEditorOutline(Graphics & g, int width, int height, TextEditor & textEditor);
    void fillTextEditorBackground (Graphics& g, int width, int height, TextEditor& textEditor);
    
	//tree
	void drawTreeviewPlusMinusBox (Graphics &g, int x, int y, int w, int h, bool isPlus, bool isMouseOver);
	//windows
	void drawDocumentWindowTitleBar(DocumentWindow& window,Graphics& g,int w,int h,int titleSpaceX,int  titleSpaceW,const Image* icon,bool drawTitleTextOnLeft);
	//Button* createSliderButton(const bool isIncrement);
	Button* createDocumentWindowButton  (int buttonType);
	//menu
	void drawMenuBarBackground (Graphics &g,int width,int height,bool isMouseOverBar,MenuBarComponent &menuBar);
    
	void drawPopupMenuItem(Graphics&, const Rectangle<int>& area,
                           bool isSeparator, bool isActive, bool isHighlighted,
                           bool isTicked, bool hasSubMenu,
                           const String& text,
                           const String& shortcutKeyText,
                           const Drawable* icon,
                           const Colour* textColour) override;
    
	void drawPopupMenuBackground(Graphics& g, int w, int h);
	void drawMenuBarItem (Graphics &g, int width, int height, int itemIndex, const String &itemText, bool isMouseOverItem, bool isMenuOpen, bool isMouseOverBar, MenuBarComponent &menuBar) ;

	//Table
	void drawTableHeaderColumn(Graphics&  g,const String& columnName,int columnId,int width,int height,bool isMouseOver,bool isMouseDown,int columnFlags);
		
	//Tools
	static void drawTextIntoRect(Graphics& g,const String& text , const Rectangle<float>& rect,const Justification& justification = Justification::centred);
	
    virtual void drawLabel (Graphics& g, Label& label);
	//custom paints

    virtual int getTabButtonOverlap (int tabDepth);
    virtual int getTabButtonSpaceAroundImage();

	virtual void drawTabButton(TabBarButton&, Graphics& g, bool isMouseOver, bool isMouseDown) override;// (Graphics& ,int w, int h,const Colour& preferredColour,int tabIndex,const String& text,Button& button,TabbedButtonBar::Orientation orientation,bool isMouseOver,bool isMouseDown,bool isFrontTab);
    
    static void paintBevel(Graphics& g,float x,float y,float w,float h,float height = 10.f, float radius = -1,const Colour& colour = ShottyLook::mainColour);
    static void fillBevelBackGroud(Graphics& g,float x,float y,float w,float h, float radius = -1);
    static void fillBevelBackGroud(Graphics& g,float x,float y,float w,float h,const Colour& c, float radius = -1);
    
    static float getOptimalCornerRadius(float w, float h);
    static const Font getOptimalFont(float w, float h);
    
    virtual void drawAlertBox (Graphics& g, AlertWindow& alert, const Rectangle<int>& textArea, TextLayout& textLayout);
    
    virtual Font getPopupMenuFont();

    //virtual void getIdealPopupMenuItemSize (const String& text,  bool isSeparator, int standardMenuItemHeight, int& idealWidth,  int& idealHeight );
    
	static int defaultControllHeight;
	static int defaultControllWidth;
    static bool usePath;
	Image* button;
    
    Path arrowDown;
    
    static const Colour disabledOverlay;
    static const Colour hoverColour;
    static const Colour pressColour;
    static const Colour backgroundColour;
    static const Colour mainColour;
    static const Colour mainColour2;
    static const Colour activeColour;
    static const Colour activeColourOverlay;
    static const Colour textColour;
    static const Colour textColour2;
};