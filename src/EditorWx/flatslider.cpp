
#include "wx/wx.h"
#include "wx/renderer.h"
#include "prefs.h"
#include "FlatSlider.h"
// the margin between the slider and the label (FIXME: hardcoded)
static const wxCoord SLIDER_LABEL_MARGIN = 2;

static const int TUMB_SIZE = 10;
static const int BORDER_THICKNESS = 2;
//static const size_t NUM_STATUSBAR_GRIP_BANDS = 3;
//static const size_t WIDTH_STATUSBAR_GRIP_BAND = 4;
//static const size_t STATUSBAR_GRIP_SIZE = WIDTH_STATUSBAR_GRIP_BAND * NUM_STATUSBAR_GRIP_BANDS;
static const wxCoord SLIDER_MARGIN = 6; // margin around slider
//static const wxCoord SLIDER_THUMB_LENGTH = 18;
static const wxCoord SLIDER_TICK_LENGTH = 6;


#define wxACTION_SLIDER_START       wxT("start")     // to the beginning
#define wxACTION_SLIDER_END         wxT("end")       // to the end
#define wxACTION_SLIDER_LINE_UP     wxT("lineup")    // one line up/left
#define wxACTION_SLIDER_PAGE_UP     wxT("pageup")    // one page up/left
#define wxACTION_SLIDER_LINE_DOWN   wxT("linedown")  // one line down/right
#define wxACTION_SLIDER_PAGE_DOWN   wxT("pagedown")  // one page down/right
#define wxACTION_SLIDER_PAGE_CHANGE wxT("pagechange")// change page by numArg

#define wxACTION_SLIDER_THUMB_DRAG      wxT("thumbdrag")
#define wxACTION_SLIDER_THUMB_MOVE      wxT("thumbmove")
#define wxACTION_SLIDER_THUMB_RELEASE   wxT("thumbrelease")




// ============================================================================
// implementation of FlatSlider
// ============================================================================

wxBEGIN_EVENT_TABLE(FlatSlider, wxWindow)
    EVT_SIZE(FlatSlider::OnSize)
	EVT_PAINT(FlatSlider::paintEvent)
	EVT_MOTION(FlatSlider::mouseMoved)
	EVT_LEFT_DOWN(FlatSlider::mouseDown)
	EVT_LEFT_UP(FlatSlider::mouseReleased)
	EVT_RIGHT_DOWN(FlatSlider::rightClick)
	EVT_ENTER_WINDOW(FlatSlider::mouseEnterWindow)
	EVT_LEAVE_WINDOW(FlatSlider::mouseLeftWindow)
	EVT_MOUSEWHEEL(FlatSlider::mouseWheelMoved)

wxEND_EVENT_TABLE()

// ----------------------------------------------------------------------------
// FlatSlider creation
// ----------------------------------------------------------------------------

FlatSlider::FlatSlider()        
{
    Init();
}

FlatSlider::FlatSlider(wxWindow *parent,
                   wxWindowID id,
                   int value, int minValue, int maxValue,
                   const wxPoint& pos,
                   const wxSize& size,
                   long style)
{
    Init();
	m_sliderstyle = style;


    (void)Create(parent, id, value, minValue, maxValue,
                 pos, size );
}


void FlatSlider::Init()
{
    m_min =
    m_max =
    m_value = 0;

    m_tickFreq = 1;

    m_lineSize =
    m_pageSize = 0;
	m_status = 0;

	//m_thumbPosOld = 0;
	m_dirty = false;
	m_htLast = -1;
	m_ofsMouse = -1;
	m_capture = false;


    m_type = typeHorisontal;
}

bool FlatSlider::Create(wxWindow *parent,
                      wxWindowID id,
                      int value, int minValue, int maxValue,
                      const wxPoint& pos,
                      const wxSize& size,
                      long style)
{
    if ( !wxWindow::Create(parent, id, pos, size, style) )
        return false;

    SetRange(minValue, maxValue);
    SetValue(value);

    // call this after setting the range as the best size depends (at least if
    // we have wxSL_LABELS style) on the range
    SetInitialSize(size);

   // CreateInputHandler(wxINP_HANDLER_SLIDER);

    return true;
}

// ----------------------------------------------------------------------------
// FlatSlider range and value
// ----------------------------------------------------------------------------

int FlatSlider::GetValue() const
{
    return m_value;
}

int FlatSlider::NormalizeValue(int value) const
{
    if ( value < m_min )
        return m_min;
    else if ( value > m_max )
        return m_max;
    else
        return value;
}

bool FlatSlider::ChangeValueBy(int inc)
{
    return ChangeValueTo(NormalizeValue(m_value + inc));
}

bool FlatSlider::ChangeValueTo(int value)
{
    // check if the value is going to change at all
    if (value == m_value)
        return false;

    // this method is protected and we should only call it with normalized
    // value!
    wxCHECK_MSG( IsInRange(value), false, wxT("invalid slider value") );

    // and also generate a command event for compatibility
    wxCommandEvent cmdevent( wxEVT_SLIDER, GetId() );
    cmdevent.SetInt( value );
    cmdevent.SetEventObject( this );
    GetEventHandler()->ProcessEvent(cmdevent);

    m_value = value;

    Refresh();

    return true;
}

void FlatSlider::SetValue(int value)
{
    value = NormalizeValue(value);

    if ( m_value != value )
    {
        m_value = value;

        Refresh();
    }
}

void FlatSlider::SetRange(int minValue, int maxValue)
{
    if ( minValue > maxValue )
    {
        // swap them, we always want min to be less than max
        int tmp = minValue;
        minValue = maxValue;
        maxValue = tmp;
    }

    if ( m_min != minValue || m_max != maxValue )
    {
        m_min = minValue;
        m_max = maxValue;

        // reset the value to make sure it is in the new range
        SetValue(m_value);
		
        // the size of the label rect might have changed
        if ( HasLabels() )
        {
            CalcGeometry();
        }
		
        Refresh();
    }
    //else: nothing changed
}

int FlatSlider::GetMin() const
{
    return m_min;
}

int FlatSlider::GetMax() const
{
    return m_max;
}

// ----------------------------------------------------------------------------
// FlatSlider line/page/thumb size
// ----------------------------------------------------------------------------

void FlatSlider::SetLineSize(int lineSize)
{
    wxCHECK_RET( lineSize >= 0, wxT("invalid slider line size") );

    m_lineSize = lineSize;
}

void FlatSlider::SetPageSize(int pageSize)
{
    wxCHECK_RET( pageSize >= 0, wxT("invalid slider page size") );

    m_pageSize = pageSize;
}

int FlatSlider::GetLineSize() const
{
    if ( !m_lineSize )
    {
        // the default line increment is 1
        wxConstCast(this, FlatSlider)->m_lineSize = 1;
    }

    return m_lineSize;
}

int FlatSlider::GetPageSize() const
{
    if ( !m_pageSize )
    {
        // the default page increment is m_tickFreq
        wxConstCast(this, FlatSlider)->m_pageSize = m_tickFreq;
    }

    return m_pageSize;
}


// ----------------------------------------------------------------------------
// FlatSlider ticks
// ----------------------------------------------------------------------------

void FlatSlider::SetTickFreq(int n)
{
    wxCHECK_RET (n > 0, wxT("invalid slider tick frequency"));

    if ( n != m_tickFreq )
    {
        m_tickFreq = n;

        Refresh();
    }
}

// ----------------------------------------------------------------------------
// FlatSlider geometry
// ----------------------------------------------------------------------------

wxSize FlatSlider::CalcLabelSize() const
{
    wxSize size;

    // there is no sense in trying to calc the labels size if we haven't got
    // any, the caller must check for it
    wxCHECK_MSG( HasLabels(), size, wxT("shouldn't be called") );

    wxCoord w1, h1, w2, h2;
    GetTextExtent(FormatValue(m_min), &w1, &h1);
    GetTextExtent(FormatValue(m_max), &w2, &h2);

    size.x = wxMax(w1, w2);
    size.y = wxMax(h1, h2);

    return size;
}

wxSize FlatSlider::DoGetBestClientSize() const
{
    // this dimension is completely arbitrary
    static const wxCoord SLIDER_WIDTH = 40;

    
    // first calculate the size of the slider itself: i.e. the shaft and the
    // thumb
    wxCoord height = 20;// GetRenderer()->GetSliderDim();

    wxSize size;
    if ( IsVertical() )
    {
        size.x = height;
        size.y = SLIDER_WIDTH;
    }
    else // horizontal
    {
        size.x = SLIDER_WIDTH;
        size.y = height;
    }

    // add space for ticks
    if ( HasTicks() )
    {
        wxCoord lenTick = SLIDER_TICK_LENGTH;//GetRenderer()->GetSliderTickLen();
        if (m_sliderstyle & wxSL_BOTH)
        {
            lenTick = 2 * lenTick;
        }

        if ( IsVertical() )
            size.x += lenTick;
        else
            size.y += lenTick;
    }

    // if we have the label, reserve enough space for it
    if ( HasLabels() )
    {
        wxSize sizeLabels = CalcLabelSize();

        if (m_sliderstyle & (wxSL_LEFT|wxSL_RIGHT))
        {
            size.x += sizeLabels.x + SLIDER_LABEL_MARGIN;
        }
        else if (m_sliderstyle & (wxSL_TOP|wxSL_BOTTOM))
        {
            size.y += sizeLabels.y + SLIDER_LABEL_MARGIN;
        }
    }

    return size;
}

void FlatSlider::OnSize(wxSizeEvent& event)
{
    CalcGeometry();

    event.Skip();
}

const wxRect& FlatSlider::GetSliderRect() const
{
    if ( m_rectSlider.width < 0 )
    {
        wxConstCast(this, FlatSlider)->CalcGeometry();
    }

    return m_rectSlider;
}

void FlatSlider::CalcGeometry()
{
    /*
       recalc the label and slider positions, this looks like this for
       wxSL_HORIZONTAL | wxSL_TOP slider:

       LLL             lll
       -------------------------
       |                T      |  <-- this is the slider rect
       | HHHHHHHHHHHHHHHTHHHHH |
       |                T      |
       | *  *  *  *  *  *  *  *|
       -------------------------

       LLL is m_rectLabel as calculated here and lll is the real rect used for
       label drawing in OnDraw() (TTT indicated the thumb position and *s are
       the ticks)

       in the wxSL_VERTICAL | wxSL_RIGHT case the picture is like this:

       ------ LLL
       | H  |
       | H *|
       | H  |
       | H *|
       | H  |
       | H *|
       | H  |
       |TTT*| lll
       | H  |
       | H *|
       ------
    */
    
    // initialize to the full client rect
    wxRect rectTotal = GetClientRect();
    m_rectSlider = rectTotal;
    wxSize sizeThumb = GetThumbSize();

    // Labels reduce the size of the slider rect
    if ( HasLabels() )
    {
       wxSize sizeLabels = CalcLabelSize();

        m_rectLabel = wxRect(rectTotal.GetPosition(), sizeLabels);

        if (m_sliderstyle & wxSL_TOP)
        {
            // shrink and offset the slider to the bottom
            m_rectSlider.y += sizeLabels.y + SLIDER_LABEL_MARGIN;
            m_rectSlider.height -= sizeLabels.y + SLIDER_LABEL_MARGIN;
        }
        else if (m_sliderstyle & wxSL_BOTTOM)
        {
            // shrink the slider and move the label to the bottom
            m_rectSlider.height -= sizeLabels.y + SLIDER_LABEL_MARGIN;
            m_rectLabel.y += m_rectSlider.height + SLIDER_LABEL_MARGIN;
        }
        else if (m_sliderstyle & wxSL_LEFT)
        {
            // shrink and offset the slider to the right
            m_rectSlider.x += sizeLabels.x + SLIDER_LABEL_MARGIN;
            m_rectSlider.width -= sizeLabels.x + SLIDER_LABEL_MARGIN;
        }
        else if (m_sliderstyle & wxSL_RIGHT)
        {
            // shrink the slider and move the label to the right
            m_rectSlider.width -= sizeLabels.x + SLIDER_LABEL_MARGIN;
            m_rectLabel.x += m_rectSlider.width + SLIDER_LABEL_MARGIN;
        }
    }

    // calculate ticks too
    if ( HasTicks() )
    {
        wxCoord lenTick = SLIDER_TICK_LENGTH; // GetRenderer()->GetSliderTickLen();

        // it
        m_rectTicks = GetShaftRect();

        if ( IsVertical() )
        {
            if (m_sliderstyle & (wxSL_LEFT|wxSL_BOTH))
            {
                m_rectTicks.x = m_rectSlider.x;
            }
            else
            { // wxSL_RIGHT
                m_rectTicks.x = m_rectSlider.x + m_rectSlider.width - lenTick;
            }
            m_rectTicks.width = lenTick;
        }
        else // horizontal
        {
            if (m_sliderstyle & (wxSL_TOP|wxSL_BOTH))
            {
                m_rectTicks.y = m_rectSlider.y;
            }
            else
            { // wxSL_BOTTOM
                m_rectTicks.y = m_rectSlider.y + m_rectSlider.height - lenTick;
            }
            m_rectTicks.height = lenTick;
        }
    }

    // slider is never smaller than thumb size unless rectTotal
    if ( IsVertical() )
    {
        wxCoord width = wxMin ( rectTotal.width, sizeThumb.x );
        m_rectSlider.width = wxMax ( m_rectSlider.width, width );
    }
    else
    {
        wxCoord height = wxMin ( rectTotal.height, sizeThumb.y );
        m_rectSlider.height = wxMax ( m_rectSlider.height, height );
    }
}

wxSize FlatSlider::GetDefaultThumbSize() const
{
    // Default size has no styles (arrows)
   // return GetRenderer()->GetSliderThumbSize(GetSliderRect(), 0, GetOrientation());
    return wxSize(TUMB_SIZE, TUMB_SIZE);
}

wxSize FlatSlider::GetThumbSize() const
{
    return  GetDefaultThumbSize();
        //GetRenderer()->GetSliderThumbSize(GetSliderRect(), m_thumbSize, GetOrientation());
}

// ----------------------------------------------------------------------------
// FlatSlider thumb geometry
// ----------------------------------------------------------------------------

wxRect FlatSlider::GetShaftRect() const
{
    
	return GetSliderShaftRect( m_rectSlider, TUMB_SIZE );
}

void FlatSlider::CalcThumbRect(const wxRect *rectShaftIn,
                             wxRect *rectThumbOut,
                             wxRect *rectLabelOut,
                             int value) const
{
    if ( value == INVALID_THUMB_VALUE )
    {
        // use the current if not specified
        value = m_value;
    }

    bool isVertical = IsVertical();

    wxRect rectShaft;
    if ( rectShaftIn )
    {
        rectShaft = *rectShaftIn;
    }
    else // no shaft rect provided, calc it
    {
        rectShaft = GetShaftRect();
    }

    wxCoord lenShaft,
            lenThumb;
    wxCoord *p;

    wxRect rectThumb(rectShaft.GetPosition(), GetThumbSize());
    if ( isVertical )
    {
        rectThumb.x += (rectShaft.width - rectThumb.width) / 2;

        lenThumb = rectThumb.height;
        lenShaft = rectShaft.height;
        p = &rectThumb.y;
    }
    else // horz
    {
        rectThumb.y += (rectShaft.height - rectThumb.height) / 2;

        lenThumb = rectThumb.width;
        lenShaft = rectShaft.width;
        p = &rectThumb.x;
    }

    // the thumb must always be entirely inside the shaft limits, so the max
    // position is not at lenShaft but at lenShaft - thumbSize
    if ( m_max != m_min )
    {
        if ( isVertical )
        {
            *p += ((lenShaft - lenThumb)*(m_max - value))/(m_max - m_min);
        }
        else
        { // horz
            *p += ((lenShaft - lenThumb)*(value - m_min))/(m_max - m_min);
        }
    }

    // calc the label rect
    if ( HasLabels() && rectLabelOut )
    {
        
        wxRect rectLabel = m_rectLabel;

        // centre the label relatively to the thumb position
        if (m_sliderstyle & (wxSL_TOP|wxSL_BOTTOM))
        {
			//do i t on center
			rectLabel.x = rectShaft.x + (rectShaft.width - m_rectLabel.width) / 2;
            //rectLabel.x = rectThumb.x + (rectThumb.width - m_rectLabel.width)/2;
        }
        else if (m_sliderstyle & (wxSL_LEFT|wxSL_RIGHT))
        {
            rectLabel.y = rectThumb.y + (rectThumb.height - m_rectLabel.height)/2;
        }

        *rectLabelOut = rectLabel;
    }

    if ( rectThumbOut )

        *rectThumbOut = rectThumb;
}

// ----------------------------------------------------------------------------
// FlatSlider drawing
// ----------------------------------------------------------------------------

wxString FlatSlider::FormatValue(int value) const
{
    return wxString::Format(wxT("x%d"), value);
}


void FlatSlider::GetSliderLabelsSides(bool *left, bool *right) const
{
	// should we draw ticks at all?
	if (!(m_sliderstyle & wxSL_AUTOTICKS))
	{
		*left =	*right = false;
		return;
	}

	// should we draw them on both sides?
	if (m_sliderstyle & wxSL_BOTH)
	{
		*left =	*right = true;
		return;
	}

	// we draw them on one side only, determine which one
	if (((m_sliderstyle & wxSL_TOP) && (!IsVertical()) ) ||
		((m_sliderstyle & wxSL_LEFT) && IsVertical()))
	{
		*left = true;
		*right = false;
	}
	else if (((m_sliderstyle & wxSL_BOTTOM) && (!IsVertical())) ||
		((m_sliderstyle & wxSL_RIGHT) && IsVertical()))
	{
		*left = false;
		*right = true;
	}
	else
	{
		wxFAIL_MSG("inconsistent wxSlider flags");

		*left =
			*right = false;
	}
}



wxRect FlatSlider::GetSliderShaftRect(const wxRect& rectOrig, int lenThumb ) const
{
	bool left, right;
	GetSliderLabelsSides( &left, &right);

	wxRect rect = rectOrig;

	wxSize sizeThumb = GetThumbSize();

	if ( !IsVertical() )
	{
		rect.x += SLIDER_MARGIN;
		if (left && right)
		{
			rect.y += wxMax((rect.height - 2 * BORDER_THICKNESS) / 2, sizeThumb.y / 2);
		}
		else if (left)
		{
			rect.y += wxMax((rect.height - 2 * BORDER_THICKNESS - sizeThumb.y / 2), sizeThumb.y / 2);
		}
		else
		{
			rect.y += sizeThumb.y / 2;
		}
		rect.width -= 2 * SLIDER_MARGIN;
		rect.height = 2 * BORDER_THICKNESS;
	}
	else // == wxVERTICAL
	{
		rect.y += SLIDER_MARGIN;
		if (left && right)
		{
			rect.x += wxMax((rect.width - 2 * BORDER_THICKNESS) / 2, sizeThumb.x / 2);
		}
		else if (left)
		{
			rect.x += wxMax((rect.width - 2 * BORDER_THICKNESS - sizeThumb.x / 2), sizeThumb.x / 2);
		}
		else
		{
			rect.x += sizeThumb.x / 2;
		}
		rect.width = 2 * BORDER_THICKNESS;
		rect.height -= 2 * SLIDER_MARGIN;
	}

	return rect;
}

void FlatSlider::paintEvent(wxPaintEvent & evt)
{
	// depending on your system you may need to look at double-buffered dcs
	wxPaintDC dc(this);
	render(dc);
}

void FlatSlider::paintNow()
{
	// depending on your system you may need to look at double-buffered dcs
	wxClientDC dc(this);
	render(dc);	
}


void FlatSlider::render(wxDC& dc)
{
  //  wxDC& dc = renderer->GetDC();
	ColourScheme *clrs = Preferences::Get()->GetColorScheme();

    //wxRect rectUpdate = GetUpdateClientRect();
   
	wxOrientation orient = IsVertical() ? wxVERTICAL : wxHORIZONTAL;
    
    wxSize sz = GetThumbSize();
    int len = IsVertical() ? sz.x : sz.y;

    
	wxRect rectShaft = GetSliderShaftRect(m_rectSlider, len );
	// calculate the thumb position in pixels and draw it
	wxRect rectThumb, rectLabel;
	CalcThumbRect(&rectShaft, &rectThumb, &rectLabel);

	// first draw the shaft
    //if ( rectUpdate.Intersects(rectShaft) )
    {

		dc.SetBrush(clrs->Get(ColourScheme::SLIDER_SHAFT));
		dc.SetPen(*wxTRANSPARENT_PEN);
		dc.DrawRoundedRectangle(rectShaft, 2);
		

		if (IsVertical())
			rectShaft.height = rectThumb.y;
		else
			rectShaft.width = rectThumb.x;

		dc.SetBrush(clrs->Get(ColourScheme::SLIDER_SHAFT_COLORED));
		dc.DrawRoundedRectangle(rectShaft, 2);
    }

    // then draw the ticks
    if ( HasTicks() /*&& rectUpdate.Intersects(m_rectTicks) */)
    {
        DrawSliderTicks(dc, m_rectSlider, len, m_min, m_max, m_tickFreq);
    }

    // then draw the thumb
    //if ( rectUpdate.Intersects(rectThumb) )
    {
        DrawSliderThumb(dc, rectThumb );
    }


    // finally, draw the label near the thumb
    if ( HasLabels() /*&& rectUpdate.Intersects(rectLabel) */)
    {
        // align it to be close to the shaft
        int align = 0;
        if (m_sliderstyle & wxSL_TOP)
        {
            align = wxALIGN_CENTRE_HORIZONTAL|wxALIGN_TOP;
        }
        else if (m_sliderstyle & wxSL_BOTTOM)
        {
            align = wxALIGN_CENTRE_HORIZONTAL|wxALIGN_BOTTOM;
        }
        else if (m_sliderstyle & wxSL_LEFT)
        {
            align = wxALIGN_CENTRE_VERTICAL|wxALIGN_LEFT;
        }
        else if (m_sliderstyle & wxSL_RIGHT)
        {
            align = wxALIGN_CENTRE_VERTICAL|wxALIGN_RIGHT;
        }

        dc.SetFont(GetFont());
        dc.SetTextForeground(GetForegroundColour());

        // the slider label is never drawn focused
		dc.DrawLabel(FormatValue(m_value), rectLabel, align );
    }
}

// ----------------------------------------------------------------------------
// FlatSlider input processing
// ----------------------------------------------------------------------------

bool FlatSlider::PerformAction(const wxString& action,
                             long numArg,
                             const wxString& strArg)
{
    wxEventType scrollEvent = wxEVT_NULL;
    int value;
    bool valueChanged = true;

    if ( action == wxACTION_SLIDER_START )
    {
        scrollEvent = wxEVT_SCROLL_TOP;
        value = m_min;
    }
    else if ( action == wxACTION_SLIDER_END )
    {
        scrollEvent = wxEVT_SCROLL_BOTTOM;
        value = m_max;
    }
    else if ( action == wxACTION_SLIDER_PAGE_CHANGE )
    {
        scrollEvent = wxEVT_SCROLL_CHANGED;
        value = NormalizeValue(m_value + numArg * GetPageSize());
    }
    else if ( action == wxACTION_SLIDER_LINE_UP )
    {
        scrollEvent = wxEVT_SCROLL_LINEUP;
        value = NormalizeValue(m_value + -GetLineSize());
    }
    else if ( action == wxACTION_SLIDER_LINE_DOWN )
    {
        scrollEvent = wxEVT_SCROLL_LINEDOWN;
        value = NormalizeValue(m_value + +GetLineSize());
    }
    else if ( action == wxACTION_SLIDER_PAGE_UP )
    {
        scrollEvent = wxEVT_SCROLL_PAGEUP;
        value = NormalizeValue(m_value + -GetPageSize());
    }
    else if ( action == wxACTION_SLIDER_PAGE_DOWN )
    {
        scrollEvent = wxEVT_SCROLL_PAGEDOWN;
        value = NormalizeValue(m_value + +GetPageSize());
    }
    else if ( action == wxACTION_SLIDER_THUMB_DRAG ||
                action == wxACTION_SLIDER_THUMB_MOVE )
    {
        scrollEvent = wxEVT_SCROLL_THUMBTRACK;
        value = (int)numArg;
        Refresh();
    }
    else if ( action == wxACTION_SLIDER_THUMB_RELEASE )
    {
        scrollEvent = wxEVT_SCROLL_THUMBRELEASE;
        value = (int)numArg;
    }
    else
    {
        return false;// wxControl::PerformAction(action, numArg, strArg);
    }

    // update FlatSlider current value
    if ( valueChanged )
        ChangeValueTo(value);

    // generate wxScrollEvent
    if ( scrollEvent != wxEVT_NULL )
    {
        wxScrollEvent event(scrollEvent, GetId());
        event.SetPosition(value);
        event.SetEventObject( this );
        GetEventHandler()->ProcessEvent(event);
    }

    return true;
}

/* static */
/*
wxInputHandler *FlatSlider::GetStdInputHandler(wxInputHandler *handlerDef)
{
    static wxStdSliderInputHandler s_handler(handlerDef);

    return &s_handler;
}
*/
// ----------------------------------------------------------------------------
// FlatSlider implementation of wxControlWithThumb interface
// ----------------------------------------------------------------------------

int FlatSlider::HitTest(const wxPoint& pt) const
{
    wxRect rectShaft = GetShaftRect();
    wxRect rectThumb;
    CalcThumbRect(&rectShaft, &rectThumb, NULL);

    // check for possible shaft or thumb hit
    if (!rectShaft.Contains(pt) && !rectThumb.Contains(pt))
    {
        return Element_None;
    }

    // the position to test and the start and end of the thumb
    wxCoord x, x1, x2, x3, x4;
    if (IsVertical())
    {
        x = pt.y;
        x1 = rectThumb.GetBottom();
        x2 = rectShaft.GetBottom();
        x3 = rectShaft.GetTop();
        x4 = rectThumb.GetTop();
    }
    else
    { // horz
        x = pt.x;
        x1 = rectShaft.GetLeft();
        x2 = rectThumb.GetLeft();
        x3 = rectThumb.GetRight();
        x4 = rectShaft.GetRight();
    }
    if ((x1 <= x) && (x < x2))
    {
        // or to the left
        return Element_Bar_1;
    }

    if ((x3 < x) && (x <= x4)) {
        // or to the right
        return Element_Bar_2;
    }

    // where else can it be?
    return Element_Thumb;
}

wxCoord FlatSlider::ThumbPosToPixel() const
{
    wxRect rectThumb;
    CalcThumbRect(NULL, &rectThumb, NULL);

    return IsVertical() ? rectThumb.y : rectThumb.x;
}

int FlatSlider::PixelToThumbPos(wxCoord x) const
{
    wxRect rectShaft = GetShaftRect();
    wxSize sizeThumb = GetThumbSize();

    wxCoord x0, len;
    if ( IsVertical() )
    {
        x0 = rectShaft.y;
        len = rectShaft.height - sizeThumb.y;
    }
    else // horz
    {
        x0 = rectShaft.x;
        len = rectShaft.width - sizeThumb.x;
    }

    int pos = m_min;
    if ( len > 0 )
    {
        if ( x > x0 )
        {
            pos += ((x - x0) * (m_max - m_min)) / len;
            if ( pos > m_max )
                pos = m_max;
        }
        //else: x <= x0, leave pos = min
    }

    return pos;
}

/*
void FlatSlider::SetShaftPartState(wxScrollThumb::Shaft shaftPart,
                                 int flag,
                                 bool set)
{
    // for now we ignore the flags for the shaft as no renderer uses them
    // anyhow
    if ( shaftPart == wxScrollThumb::Shaft_Thumb )
    {
        if ( set )
            m_thumbFlags |= flag;
        else
            m_thumbFlags &= ~flag;

        Refresh();
    }
}
*/
void FlatSlider::OnThumbDragStart(int pos)
{
    if (IsVertical())
    {
        PerformAction(wxACTION_SLIDER_THUMB_DRAG, m_max - pos);
    }
    else
    {
        PerformAction(wxACTION_SLIDER_THUMB_DRAG, pos);
    }
}

void FlatSlider::OnThumbDrag(int pos)
{
    if (IsVertical())
    {
        PerformAction(wxACTION_SLIDER_THUMB_MOVE, m_max - pos);
    }
    else
    {
        PerformAction(wxACTION_SLIDER_THUMB_MOVE, pos);
    }
}

void FlatSlider::OnThumbDragEnd(int pos)
{
    if (IsVertical())
    {
        PerformAction(wxACTION_SLIDER_THUMB_RELEASE, m_max - pos);
    }
    else
    {
        PerformAction(wxACTION_SLIDER_THUMB_RELEASE, pos);
    }
}

void FlatSlider::OnPageScrollStart()
{
    // we do nothing here
}

bool FlatSlider::OnPageScroll(int pageInc)
{
    int value = GetValue();
    PerformAction(wxACTION_SLIDER_PAGE_CHANGE, pageInc);

    return GetValue() != value;
}


static
void DrawLine(wxDC& dc,
	wxCoord x1, wxCoord y1,
	wxCoord x2, wxCoord y2,
	bool transpose = false)
{
	if (transpose)
		dc.DrawLine(y1, x1, y2, x2);
	else
		dc.DrawLine(x1, y1, x2, y2);
}


void FlatSlider::DrawSliderThumb(wxDC& dc,	const wxRect& rect)
{
	ColourScheme *clrs = Preferences::Get()->GetColorScheme();
	wxRect rectInt = rect;
	wxColor clr = clrs->Get(ColourScheme::SLIDER_SHAFT_COLORED);
	if ((m_status == statusPressed) || (m_status == statusHover))
		clr = clr.ChangeLightness(80);
	
	dc.SetBrush(clr);
	dc.SetPen(*wxTRANSPARENT_PEN);
	dc.DrawEllipse(rectInt);
}

void FlatSlider::DrawSliderTicks(wxDC& dc,	const wxRect& rect,	int lenThumb,int start,	int end, int step)
{
	/*    show ticks geometry

		left        right
		ticks shaft ticks
		----   XX   ----  <-- x1
		----   XX   ----
		----   XX   ----
		----   XX   ----  <-- x2

		^  ^        ^  ^
		|  |        |  |
		y3 y1       y2 y4
	*/

	// empty slider?
	if (end == start)
		return;

	bool left, right;
	GetSliderLabelsSides(&left, &right);

	bool isVertical = IsVertical();

	// default thumb size
	wxSize sizeThumb = GetThumbSize();
	wxCoord defaultLen = (IsVertical() ? sizeThumb.x : sizeThumb.y);

	// normal thumb size
	sizeThumb = GetThumbSize();
	wxCoord widthThumb = (IsVertical() ? sizeThumb.y : sizeThumb.x);

	wxRect rectShaft = GetSliderShaftRect(rect, lenThumb );

	wxCoord x1, x2, y1, y2, y3, y4, len;
	x1 = (isVertical ? rectShaft.y : rectShaft.x) + widthThumb / 2;
	x2 = (isVertical ? rectShaft.GetBottom() : rectShaft.GetRight()) - widthThumb / 2;
	y1 = (isVertical ? rectShaft.x : rectShaft.y) - defaultLen / 2;
	y2 = (isVertical ? rectShaft.GetRight() : rectShaft.GetBottom()) + defaultLen / 2;
	y3 = (isVertical ? rect.x : rect.y);
	y4 = (isVertical ? rect.GetRight() : rect.GetBottom());
	len = x2 - x1;

	wxPen m_penBlack(*wxBLACK);
	dc.SetPen(m_penBlack);

	int range = end - start;
	for (int n = 0; n < range; n += step)
	{
		wxCoord x = x1 + (len*n) / range;

		if (left && (y1 > y3))
		{
			DrawLine(dc, x, y1, x, y3, isVertical);
		}
		if (right && (y4 > y2))
		{
			DrawLine(dc, x, y2, x, y4, isVertical);
		}
	}
	// always draw the line at the end position
	if (left && (y1 > y3))
	{
		DrawLine(dc, x2, y1, x2, y3, isVertical);
	}
	if (right && (y4 > y2))
	{
		DrawLine(dc, x2, y2, x2, y4, isVertical);
	}
}



wxCoord FlatSlider::GetMouseCoord(const wxMouseEvent& event) const
{
	wxPoint pt = event.GetPosition();
	return IsVertical() ? pt.y : pt.x;
}

void FlatSlider::mouseDown(wxMouseEvent& event)
{
	CaptureMouse();
	m_capture = true;
	int ht = HitTest(event.GetPosition());

	if (ht == Element_Thumb)
	{
		m_ofsMouse = GetMouseCoord(event) - ThumbPosToPixel();
	}
	else if (ht == Element_Bar_1)  //UP
	{
		PerformAction(wxACTION_SLIDER_PAGE_CHANGE, -1);

	}
	else if (ht == Element_Bar_2) //Dawn
	{
		PerformAction(wxACTION_SLIDER_PAGE_CHANGE, +1);
	}

	m_htLast = ht;

	m_status = statusPressed;
	paintNow();
}

void FlatSlider::mouseReleased(wxMouseEvent& event)
{
	m_status = statusNone;
	if (m_capture)
	{
		ReleaseMouse();
		m_capture = false;
	}
	paintNow();
}


void FlatSlider::mouseMoved(wxMouseEvent& event)
{
	if (m_status == statusPressed)
	{
		if (m_htLast == Element_Thumb)
		{
			int thumbPos = GetMouseCoord(event) - m_ofsMouse;
			thumbPos = PixelToThumbPos(thumbPos);
			PerformAction(wxACTION_SLIDER_THUMB_MOVE, thumbPos);
		}
		return;
	}

	int ht = HitTest(event.GetPosition());
	int newstatus = statusNone;
	if (ht == Element_Thumb)
		newstatus = statusHover;

	if (newstatus != m_status)
	{
		m_status = newstatus;
		paintNow();
	}
}


// currently unused events

void FlatSlider::mouseLeftWindow(wxMouseEvent& event)
{
	if (m_status == statusPressed)
		return;
	m_status = statusNone;
	paintNow();
}

void FlatSlider::mouseEnterWindow(wxMouseEvent& event)
{
	mouseMoved(event);
}
void FlatSlider::mouseWheelMoved(wxMouseEvent& event) {}
void FlatSlider::rightClick(wxMouseEvent& event) {}
