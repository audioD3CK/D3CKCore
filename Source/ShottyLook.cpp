#include "ShottyLook.h"

int  ShottyLook::defaultControllHeight = 18;
int  ShottyLook::defaultControllWidth = 30;
bool ShottyLook::usePath = false;
const Colour ShottyLook::mainColour = Colour(82,81,80);//Colour(234,232,230);
const Colour ShottyLook::mainColour2 = mainColour.withMultipliedBrightness(2);//Colour(234,232,230);
const Colour ShottyLook::backgroundColour = mainColour.withMultipliedBrightness(0.5);
const Colour ShottyLook::disabledOverlay = ShottyLook::backgroundColour.withAlpha(0.75f);
const Colour ShottyLook::pressColour = Colours::black;
const Colour ShottyLook::hoverColour = Colours::grey.withMultipliedBrightness(1.5f);
const Colour ShottyLook::activeColour = Colour(108,150,196);// Colours::orange;
const Colour ShottyLook::activeColourOverlay = ShottyLook::activeColour.withAlpha(0.2f);
const Colour ShottyLook::textColour = Colours::white;
const Colour ShottyLook::textColour2 = textColour.withMultipliedBrightness(0.75);

ShottyLook::ShottyLook()
{
	button = 0;
	LookAndFeel::setDefaultLookAndFeel(this);
    setColour(TextEditor::highlightColourId, activeColour);
    setColour(ListBox::backgroundColourId, Colours::transparentBlack);
    setColour(PopupMenu::highlightedBackgroundColourId, activeColour);
    setColour(PopupMenu::highlightedTextColourId, textColour);
    setColour(PopupMenu::textColourId, textColour);
    setColour(PopupMenu::headerTextColourId, textColour);
    
    arrowDown.startNewSubPath(0, 0);
    arrowDown.lineTo(7.5, 15);
    arrowDown.lineTo(15, 0);
    arrowDown.closeSubPath();
    arrowDown = arrowDown.createPathWithRoundedCorners(5);
    
}
ShottyLook::~ShottyLook()
{
	clearSingletonInstance();
	LookAndFeel::setDefaultLookAndFeel(0);
}
/*
 Button* ShottyLook::createSliderButton(const bool isIncrement)
 {
 return LookAndFeel::createSliderButton(isIncrement);
 }
 */
void ShottyLook::drawRotarySlider(Graphics & g, int x, int y, int width, int height, float sliderPosition, const float rotaryStartAngle, const float rotaryEndAngle, Slider & slider)
{
	String text;
	g.drawRect(x,y,width,height);
	double interval = slider.getInterval();
	int digits = 2;
    
	bool d;
	double defv = slider.getDoubleClickReturnValue(d);
	double min = slider.getMinimum();
	float divider = jmax(0.0001,(slider.getMaximum() - (d ? defv : min )) * 0.75);
	float valr = (slider.getValue() - (d ? defv : min )) / divider;
	valr = abs(valr);
	g.setColour(Colours::red.withAlpha( jlimit(0.f,1.f,valr) ) );
	g.fillRect(x,y,width,height);
	g.setColour(Colours::black);
    
	if( roundDoubleToInt( interval ) && roundDoubleToInt( interval ) < interval + 0.005 && roundDoubleToInt( interval ) > interval - 0.005)
		digits = 0;
	if(slider.isMouseOverOrDragging())
		text = String(slider.getValue(),digits);
	else
		text = slider.getName();
	g.drawFittedText(text,x,y,width,height,Justification::centred,2);
    
    if(!slider.isEnabled())
    {
        g.setColour(disabledOverlay );
        g.fillRect(x,y,width,height);
        g.setColour(Colours::black);
    }
}
Font ShottyLook::getPopupMenuFont()
{
    return getOptimalFont(500, 15);
}
//void ShottyLook::getIdealPopupMenuItemSize (const String& text,const bool isSeparator,int standardMenuItemHeight,int& idealWidth, int& idealHeight)
//{
//    LookAndFeel::getIdealPopupMenuItemSize(text, isSeparator, standardMenuItemHeight, idealWidth, idealHeight);
//    idealHeight = isSeparator ? 10 : 15;
//}

void ShottyLook::drawAlertBox (Graphics& g, AlertWindow& alert, const Rectangle<int>& textArea, TextLayout& textLayout)
{
    g.fillAll(mainColour);
	textLayout.draw(g , textArea.toFloat() );
    paintBevel(g , 0, 0, alert.getWidth(), alert.getHeight());
}
void ShottyLook::drawLabel (Graphics& g, Label& label)
{
    if(!label.isBeingEdited())
    {
        g.setColour(textColour);
        drawTextIntoRect(g,label.getText(),label.getBounds().withPosition(0, 0).toFloat(),label.getJustificationType());
//        paintBevel(g, 0, 0, label.getWidth(), label.getHeight());
    }
}
void ShottyLook::drawTableHeaderColumn(Graphics&  g,const String& columnName,int columnId,int width,int height,bool isMouseOver,bool isMouseDown,int columnFlags)
{
	g.drawFittedText(columnName,0,0,width,height,Justification::left,1);
}
void ShottyLook::drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColor, bool isMouseOverButton, bool isButtonDown)
{
    button.setBufferedToImage(true);
    Colour c;
    
	
    if(button.getToggleState())
    {
		c = (activeColour );
    }
	else
    {
		c = (mainColour);
    }
    
    fillBevelBackGroud(g , 0, 0, button.getWidth(), button.getHeight(),c);
    
	g.setColour(Colours::grey.withMultipliedBrightness(1.5f));
	if(button.isConnectedOnBottom())
    {
        g.drawLine(0,button.getHeight()-1,button.getWidth(),button.getHeight()-1);
    }
	if(button.isConnectedOnTop())
    {
        g.drawLine(0,0,button.getWidth(),0);
    }
	if(button.isConnectedOnLeft())
    {
        g.drawLine(0,0,0,button.getHeight());
    }
	if(button.isConnectedOnRight())
    {
        g.drawLine(button.getWidth()-1,0,button.getWidth()-1,button.getHeight());
    }
}

void ShottyLook::fillTextEditorBackground (Graphics& g, int width, int height, TextEditor& textEditor)
{
//    g.setOpacity(1);
    g.fillAll(mainColour);
    fillBevelBackGroud(g , 0, 0, width, height);
    paintBevel(g , 0, 0, width, height,-10);
}
void ShottyLook::drawTextEditorOutline(Graphics & g, int width, int height, TextEditor & textEditor)
{
	paintBevel(g,0,0,width,height,-10);
}

void ShottyLook::drawTextIntoRect(Graphics& g, const String& text , const Rectangle<float>& rect,const Justification& justification)
{
    const Rectangle<float> padded = rect.reduced(2);

    g.setFont(getOptimalFont(jmax(padded.getWidth(), padded.getHeight()),jmin(padded.getWidth(), padded.getHeight())));
    g.setColour(Colours::white);
    
	if(padded.getHeight() > padded.getWidth())
    {
        AffineTransform t = AffineTransform::identity;
        t = t.translated(padded.getWidth(), 0).rotated(float_Pi*0.5f,padded.getWidth(),0);//.translated(rect.getX() + rect.getWidth()/2.f - 5.f, rect.getY()+ 5.f);
        g.addTransform(t);
        g.drawText(text,padded.getX(),padded.getY(),padded.getHeight(),padded.getWidth(), justification,2);
        g.addTransform(t.inverted());
    }
    else
    {
        const double lines = padded.getHeight()/.5;
        g.drawFittedText(text,padded.toType<int>(), justification, lines);
//        g.drawText(text,0,0,padded.getWidth(),padded.getHeight(), justification, true);
    }
    
}
void ShottyLook::drawDrawableButton (Graphics& g, DrawableButton& b, bool isMouseOverButton, bool isButtonDown)
{
    LookAndFeel_V2::drawDrawableButton(g, b, isMouseOverButton, isButtonDown);
    paintBevel(g, 0, 0, b.getWidth(), b.getHeight(),isButtonDown ? -10 : 10);
}

void ShottyLook::drawButtonText(Graphics& g, TextButton& button, bool isMouseOverButton, bool isButtonDown)
{
	if(isButtonDown)
    {
		g.setColour(hoverColour);
    }
	else
    {
		g.setColour(textColour);
    }
    
	drawTextIntoRect(g, button.getButtonText() , Rectangle<float>(0,0,button.getWidth(),button.getHeight()));
    
	if(!button.isEnabled())
    {
		g.fillAll(disabledOverlay);
    }
    else if(isMouseOverButton)
    {
        fillBevelBackGroud(g , 0, 0, button.getWidth(), button.getHeight(), activeColourOverlay);
    }
    
    paintBevel(g, 0, 0, button.getWidth(), button.getHeight(),isButtonDown ? -10 : 10);
}
int ShottyLook::getDefaultScrollbarWidth()
{
	return defaultControllHeight;
}
float ShottyLook::getOptimalCornerRadius(float w, float h)
{
    float r =  5;//jmin(w,h)/8;
    return r;//jlimit(5.f,10.f,r);
}
const Font ShottyLook::getOptimalFont(float w, float h)
{
    return Font(jmin(12.f,h*0.8f));
}
void ShottyLook::fillBevelBackGroud(Graphics& g,float x,float y,float w,float h, const Colour& c, float rp)
{
    float r = rp < 0 ? getOptimalCornerRadius(w, h) : rp;
    g.setColour(c);
    g.fillRoundedRectangle(x, y, w, h, r);
}
void ShottyLook::fillBevelBackGroud(Graphics& g,float x,float y,float w,float h, float rp)
{
    fillBevelBackGroud(g,x,y,w,h,mainColour,rp);
}
void ShottyLook::paintBevel(Graphics& g,float x,float y,float w,float h,float height,float rp,const Colour& c)
{
    //height = 15;
    float r = rp < 0 ? getOptimalCornerRadius(w, h) : rp;
    
    Colour dark = c.withMultipliedBrightness(0.5);
    Colour light = c.withMultipliedBrightness(1.5);
    Colour highLight = c.withMultipliedBrightness(2.f);
    
    if(height > 0 )
    {
        float h2 = jmin(h,height);
        g.setGradientFill(ColourGradient(light,0,y,dark,0,y+h,false));
        g.drawRoundedRectangle(x,y,w,h,r,1);
        
        g.setGradientFill(ColourGradient(dark.withAlpha(0.f),0, y+h-h2, dark.withAlpha(0.2f),0,y+h,false));
        g.fillRoundedRectangle(x, y, w, h, r);
        ColourGradient gradient;
        
        g.setGradientFill(ColourGradient(highLight.withAlpha(0.2f), 0 , y, highLight.withAlpha(0.f),0,y+h2,false));
        //g.setColour(mainColour.withMultipliedBrightness(2).withAlpha(0.3f));
        g.fillRoundedRectangle(x, y, w, h, r);
    }
    else
    {
        float h2 = jmin(h,(float)abs(height));
        g.setGradientFill(ColourGradient(light,0,y+h,dark,0,y,false));
        g.drawRoundedRectangle(x,y,w,h,r,1);
        g.setGradientFill(ColourGradient(dark.withAlpha(0.1f),0,y,dark.withAlpha(0.f),0,y+h2,false));
        g.fillRoundedRectangle(x, y, w, h, r);
    }
}
void ShottyLook::drawScrollbarButton(Graphics & g, ScrollBar & scrollbar, int width, int height, int buttonDirection, bool isScrollbarVertical, bool isMouseOver, bool isButtonDown)
{
	//g.drawRect(0,0,width,height);
	Path p;
    g.setColour(textColour);
	if(buttonDirection == 0)
	{
		p.startNewSubPath(width/2,0);
		p.lineTo(width,height);
		p.lineTo(0,height);
		p.closeSubPath();
	}
	else if(buttonDirection == 2)
	{
		p.startNewSubPath(0,0);
		p.lineTo(width/2,height);
		p.lineTo(width,0);
		p.closeSubPath();
	}
    p = p.createPathWithRoundedCorners(5);
	p.scaleToFit(2,2,width-4,height-4,true);
	if(isButtonDown)
	{
		g.fillPath(p);
	}
	else if(isMouseOver)
	{
		//g.setColour(hoverColour);
		g.fillPath(p);
	}
    else
        g.strokePath(p,PathStrokeType(PathStrokeType::square),AffineTransform::identity);
    paintBevel(g , 0,0 , width, height);
}
void ShottyLook::drawScrollbar(Graphics & g, ScrollBar & scrollbar, int x, int y, int width, int height, bool isScrollbarVertical, int thumbStartPosition, int thumbSize, bool isMouseOver, bool isMouseDown)
{
    g.fillAll(mainColour.darker());
    
    paintBevel(g , x, y, width, height,false);
	Rectangle<int> rect;
	if(isScrollbarVertical)
		rect.setBounds(x,thumbStartPosition,width,thumbSize);
	else
		rect.setBounds(thumbStartPosition,y,thumbSize,height);
    
	if(isMouseDown)
		g.setColour(pressColour);
    
	if(isMouseOver)
		g.setColour(hoverColour);
    
    if(isMouseDown || isMouseOver)
        g.fillRoundedRectangle(rect.toFloat(), getOptimalCornerRadius(rect.getWidth(), rect.getHeight()));//Rect(rect);
    
    fillBevelBackGroud(g, rect.getX(), rect.getY(), rect.getWidth(), rect.getHeight());
    paintBevel(g, rect.getX(), rect.getY(), rect.getWidth(), rect.getHeight());
}
int ShottyLook::getScrollbarButtonSize(ScrollBar & scrollbar)
{
	return defaultControllHeight;
}
void ShottyLook::drawComboBox(Graphics & g, int w, int h, const bool isDown, int bx, int by, int bw, int bh, ComboBox & box)
{
	//g.drawRect(0,0,w,h);
    
	Path p = arrowDown;
    p.scaleToFit(bx+1, by+1, bw-2, bh-2, true);
    
    
    //if(box.isMouseOverOrDragging())
    g.fillPath(p);
    //else
    //g.strokePath(p, PathStrokeType::rounded);  //arrowDown.get
    
	if(isDown)
	{
		g.setColour(pressColour);
		g.fillPath(p);
	}
	if(box.isMouseOverOrDragging())
	{
        g.setColour(activeColourOverlay);
        g.fillRect(bx, by, bw, bh );
        
		//g.fillPath(p);
	}
	if(!box.isEnabled())
		g.fillAll(disabledOverlay);
    
    paintBevel(g, bx, by, bw, bh);
}
void ShottyLook::drawLinearSlider(Graphics & g, int x, int y, int w, int h, float pos, float min, float max, const Slider::SliderStyle style, Slider & slider)
{
    
	if(style == Slider::TwoValueHorizontal)
	{
		for(int i = 0 ; i < 2 ; i++)
		{
			slider.setSliderSnapsToMousePosition(false);
			w = slider.getWidth();
			x = 0;
            
			int hw = 5;
			float val = i == 0 ?  slider.getMinValue() : slider.getMaxValue();
			float pos2 = ( val - slider.getMinimum()) / (slider.getMaximum() - slider.getMinimum());
			g.fillRect(roundFloatToInt( x + (w*pos2 - hw*pos2) ),y,hw,h);
			if(i == 1)
			{
				g.setColour(disabledOverlay);
				g.fillRect(x,y,w,h/2);
				g.setColour(Colours::black);
			}
			String text;
			if(slider.isMouseOverOrDragging() && slider.isEnabled())
				text = String(val,2);
			else
				text = slider.getName();
            int x2 = (w/2)*i;
            g.drawText(text,x2,y,w/2,h/2,Justification::centred,true);
            
		}
		g.drawRect(x,y,w,h);
        
		if(!slider.isEnabled())
		{
			g.setColour(disabledOverlay);
			g.fillRect(x,y,w,h);
		}
	}
	else if(style == Slider::LinearHorizontal || style == Slider::LinearBar)
	{
		slider.setSliderSnapsToMousePosition(false);
		w = slider.getWidth();
		x = 0;
        
		int hw = 5;
		float pos2 = (slider.getValue() - slider.getMinimum()) / (slider.getMaximum() - slider.getMinimum());
		g.fillRect(roundFloatToInt( x + (w*pos2 - hw*pos2) ),y,hw,h);
		g.setColour(disabledOverlay);
		g.fillRect(x,y,w,h/2);
		g.setColour(Colours::black);
		String text;
		if(slider.isMouseOverOrDragging() && slider.isEnabled())
			text = String(slider.getValue(),2);
		else
			text = slider.getName();
        
        g.drawText(text,x,y,w,h/2,Justification::centred,true);
        
		g.drawRect(x,y,w,h);
        
		if(!slider.isEnabled())
		{
			g.setColour(disabledOverlay);
			g.fillRect(x,y,w,h);
		}
	}
	else if(style == Slider::LinearVertical)
	{
		slider.setSliderSnapsToMousePosition(false);
		h += 2*y;
		y = 0;
        
		int hh = 5;
		float pos2 = (slider.getValue() - slider.getMinimum()) / (slider.getMaximum() - slider.getMinimum());
        
		g.fillRect(x,h - roundFloatToInt( y + (h * pos2 - hh *pos2) + hh ),h,hh);
		g.setColour(disabledOverlay);
		g.fillRect(x,y,w/2,h);
		g.setColour(Colours::black);
		String text;
		if(slider.isMouseOverOrDragging() && slider.isEnabled())
			text = String(slider.getValue(),2);
		else
			text = slider.getName();
		
		ShottyLook::drawTextIntoRect(g,text,Rectangle<float>(x,y,w/2,h));
        
		g.drawRect(x,y,w,h);
        
		if(!slider.isEnabled())
		{
			g.setColour(disabledOverlay);
			g.fillRect(x,y,w,h);
		}
	}
}

void ShottyLook::drawPopupMenuBackground( Graphics& g, int w, int h)
{
	g.fillAll(mainColour);
    paintBevel(g , 0, 0, w, h);
	//g.drawRect(0,0,w,h);
}

void ShottyLook::drawTreeviewPlusMinusBox (Graphics &g, int x, int y, int w, int h, bool isPlus, bool isMouseOver)
{
	g.drawRect(x,y,w,h);
	if(isMouseOver)
	{
		g.setColour(this->hoverColour);
		g.fillRect(x,y,w,h);
	}
}
void ShottyLook::drawDocumentWindowTitleBar(DocumentWindow& window,Graphics& g,int w,int h,int titleSpaceX,int  titleSpaceW,const Image* icon,bool drawTitleTextOnLeft)
{
	g.fillAll(mainColour);
    
    drawTextIntoRect(g , window.getName(), Rectangle<float>(0,0,w,h));
    paintBevel(g , 0, 0, w, h);
    
}
Button* ShottyLook::createDocumentWindowButton  (int buttonType)
{
	return new TextButton(buttonType == 4 ? "x" : buttonType == 1 ? "-" : "O", buttonType == 4 ? "close" : buttonType == 1 ? "minimize" : "maximize");
}
void ShottyLook::drawMenuBarBackground (Graphics &g,int width,int height,bool isMouseOverBar,MenuBarComponent &menuBar)
{
	g.fillAll(mainColour);
}
void ShottyLook::drawPopupMenuItem(Graphics& g, const Rectangle<int>& area,
                                   bool isSeparator, bool isActive, bool isHighlighted,
                                   bool isTicked, bool hasSubMenu,
                                   const String& text,
                                   const String& shortcutKeyText,
                                   const Drawable* icon,
                                   const Colour* textColourp)
{
    
    
   LookAndFeel_V2::drawPopupMenuItem(g, area, isSeparator, isActive, isHighlighted, isTicked
                                                     , hasSubMenu, text, shortcutKeyText, icon, textColourp);
    return;
    
    const int width = area.getWidth();
    const int height = area.getHeight();
    const float halfH = height * 0.5f;

    if (isSeparator)
    {
        const float separatorIndent = 5.5f;
        
        g.setColour (Colour (0x33000000));
        g.drawLine (separatorIndent, halfH, width - separatorIndent, halfH);
        
        g.setColour (Colour (0x66ffffff));
        g.drawLine (separatorIndent, halfH + 1.0f, width - separatorIndent, halfH + 1.0f);
    }
    else
    {
        Colour textColour  =  textColourp ?  *textColourp : ShottyLook::textColour;
        
        if (isHighlighted)
        {
            g.setColour (findColour (PopupMenu::highlightedBackgroundColourId));
            g.fillRect (1, 1, width - 2, height - 2);
            
            g.setColour (findColour (PopupMenu::highlightedTextColourId));
        }
        else
        {
            g.setColour (ShottyLook::textColour);
        }
        
        if (! isActive)
        {
            g.setOpacity (0.3f);
        }
        
        Font font (getPopupMenuFont());
        
        if (font.getHeight() > height / 1.3f)
            font.setHeight (height / 1.3f);
        
        g.setFont (font);
        
        const int leftBorder = (height * 5) / 4;
        const int rightBorder = 4;
        
        if (icon != nullptr)
        {
            icon->draw(g, 1);
//            g.drawImageWithin (*image,
//                               2, 1, leftBorder - 4, height - 2,
//                               RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize, false);
        }
        else if (isTicked)
        {
            const Path tick (getTickShape (1.0f));
            const float th = font.getAscent();
            const float ty = halfH - th * 0.5f;
            
            g.fillPath (tick, tick.getTransformToScaleToFit (2.0f, ty, (float) (leftBorder - 4),
                                                             th, true));
        }
        
        g.drawFittedText (text,
                          leftBorder, 0,
                          width - (leftBorder + rightBorder), height,
                          Justification::centredLeft, 1);
        
        if (shortcutKeyText.isNotEmpty())
        {
            Font f2 (font);
            f2.setHeight (f2.getHeight() * 0.75f);
            f2.setHorizontalScale (0.95f);
            g.setFont (f2);
            
            g.drawText (shortcutKeyText,
                        leftBorder,
                        0,
                        width - (leftBorder + rightBorder + 4),
                        height,
                        Justification::centredRight,
                        true);
        }
        
        if (hasSubMenu)
        {
            const float arrowH = 0.6f * getPopupMenuFont().getAscent();
            const float x = width - height * 0.6f;
            
            Path p;
            p.addTriangle (x, halfH - arrowH * 0.5f,
                           x, halfH + arrowH * 0.5f,
                           x + arrowH * 0.6f, halfH);
            
            g.fillPath (p);
        }
    }
}
void ShottyLook::drawMenuBarItem (Graphics &g, int width, int height, int itemIndex, const String &itemText, bool isMouseOverItem, bool isMenuOpen, bool isMouseOverBar, MenuBarComponent &menuBar)
{
	if(isMouseOverItem || isMenuOpen)
		g.fillAll(Colours::red);
	else
		g.fillAll(mainColour);
    
	g.drawFittedText(itemText,1,1,width-2,height-2,Justification::centred,2);
    
	g.drawRect(0,0,width,height);
}
int ShottyLook::getTabButtonOverlap (int tabDepth)
{
	return 0;
}
int ShottyLook::getTabButtonSpaceAroundImage()
{
	return 0;
}
void ShottyLook::drawTabButton(TabBarButton& b, Graphics& g, bool isMouseOver, bool isMouseDown)// (Graphics& g,int w, int h,const Colour& preferredColour,int tabIndex,const String& text,Button& button,TabbedButtonBar::Orientation orientation,bool isMouseOver,bool isMouseDown,bool isFrontTab)
{
	int w = b.getWidth();
	int h = b.getHeight();
	if(!b.isFrontTab())
		g.setColour(mainColour);
	else
		g.setColour(activeColour);
    
	g.fillRect(0,0,w,h);
    
	g.setColour(Colours::black);
	g.setFont(getOptimalFont(w , h  ));
	g.drawFittedText(b.getButtonText(),0,0,w,h,Justification::centred,1);
    
    paintBevel(g , 0 , 0 , w, h);
}

juce_ImplementSingleton (ShottyLook);

