// our actions are the same as scrollbars


// ----------------------------------------------------------------------------
// FlatSlider
// ----------------------------------------------------------------------------

class FlatSlider : public wxWindow                            
{
public:
	enum { statusNone, statusHover, statusPressed };
	enum { typeVertical, typeHorisontal };
	enum { Element_None, Element_Thumb, Element_Bar_1, Element_Bar_2 };

public:
    // ctors and such
    FlatSlider();

    FlatSlider(wxWindow *parent,
             wxWindowID id,
             int value, int minValue, int maxValue,
             const wxPoint& pos = wxDefaultPosition,
             const wxSize& size = wxDefaultSize,
             long style = wxSL_HORIZONTAL);

    bool Create(wxWindow *parent,
                wxWindowID id,
                int value, int minValue, int maxValue,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxDefaultSize,
                long style = wxSL_HORIZONTAL);

    // implement base class pure virtuals
    virtual int GetValue() const ;
    virtual void SetValue(int value);

    virtual void SetRange(int minValue, int maxValue) ;
    virtual int GetMin() const { return m_min; }
    virtual int GetMax() const { return m_max; }

    virtual void SetPageSize(int pageSize) ;
    virtual int GetPageSize() const ;
    virtual int GetTickFreq() const { return m_tickFreq; }
	virtual void SetTickFreq(int freq);

      // is this a vertical slider?
    bool IsVertical() const { return m_type == typeVertical; }

    // do we have labels?
    bool HasLabels() const
        { return ((m_sliderstyle & wxSL_LABELS) != 0) &&
                 ((m_sliderstyle& (wxSL_TOP|wxSL_BOTTOM|wxSL_LEFT|wxSL_RIGHT)) != 0); }
	bool HasMinMaxLabels() const { return ((m_sliderstyle&wxSL_MIN_MAX_LABELS)!=0); }
	
    // do we have ticks?
    bool HasTicks() const
        { return ((m_sliderstyle & wxSL_TICKS) != 0) &&
                 ((m_sliderstyle & (wxSL_TOP|wxSL_BOTTOM|wxSL_LEFT|wxSL_RIGHT|wxSL_BOTH)) != 0); }


    int HitTest(const wxPoint& pt) const ;
    wxCoord ThumbPosToPixel() const ;
    int PixelToThumbPos(wxCoord x) const ;


    virtual void OnThumbDragStart(int pos) ;
    virtual void OnThumbDrag(int pos) ;
    virtual void OnThumbDragEnd(int pos) ;
    virtual void OnPageScrollStart() ;
    virtual bool OnPageScroll(int pageInc) ;

    // for wxStdSliderInputHandler
  //  wxScrollThumb& GetThumb() { return m_thumb; }

    virtual bool PerformAction(const wxString& action,
                               long numArg = 0,
                               const wxString& strArg = wxEmptyString) ;

//    static wxInputHandler *GetStdInputHandler(wxInputHandler *handlerDef);
 //   virtual wxInputHandler *DoGetStdInputHandler(wxInputHandler *handlerDef) 
   // {
     //   return GetStdInputHandler(handlerDef);
    //}

	// event handlers
	void OnSize(wxSizeEvent& event);
	void paintEvent(wxPaintEvent & evt);
	void mouseMoved(wxMouseEvent& event);
	void mouseDown(wxMouseEvent& event);
	void mouseWheelMoved(wxMouseEvent& event);
	void mouseReleased(wxMouseEvent& event);
	void rightClick(wxMouseEvent& event);
	void mouseLeftWindow(wxMouseEvent& event);
	void mouseEnterWindow(wxMouseEvent& event);
	void OnEraseBackground(wxEraseEvent& event);


protected:
    enum
    {
        INVALID_THUMB_VALUE = -0xffff
    };

     // overridden base class virtuals
    virtual wxSize DoGetBestClientSize() const ;
    virtual wxBorder GetDefaultBorder() const wxOVERRIDE { return wxBORDER_NONE; }

    
	void paintNow();
	void render(wxDC& dc);

    // common part of all ctors
    void Init();

    // normalize the value to fit in the range
    int NormalizeValue(int value) const;

    // change the value by the given increment, return true if really changed
    bool ChangeValueBy(int inc);

    // change the value to the given one
    bool ChangeValueTo(int value);

    // is the value inside the range?
    bool IsInRange(int value) { return (value >= m_min) && (value <= m_max); }

    // format the value for printing as label
    virtual wxString FormatValue(int value) const;

    // calculate max label size
    wxSize CalcLabelSize() const;

    // calculate m_rectLabel/Slider
    void CalcGeometry();

    // get the thumb size
    wxSize GetThumbSize() const;

    // get the shaft rect (uses m_rectSlider which is supposed to be calculated)
    wxRect GetShaftRect() const;

    // calc the current thumb position using the shaft rect (if the pointer is
    // NULL, we calculate it here too)
    void CalcThumbRect(const wxRect *rectShaft,
                       wxRect *rectThumbOut,
                       wxRect *rectLabelOut,
                       int value = INVALID_THUMB_VALUE) const;

    // return the slider rect calculating it if needed
    const wxRect& GetSliderRect() const;

    // refresh the current thumb position
	void DrawSliderThumb(wxDC& dc, const wxRect& rect );
	void DrawSliderTicks(wxDC& dc,const wxRect& rect,int lenThumb, int start,	int end,	int step );
private:
	wxRect GetSliderShaftRect(const wxRect& rectOrig, int lenThumb ) const;
    // get the default thumb size (without using m_thumbSize)
	wxCoord GetMouseCoord(const wxMouseEvent& event) const;
	void GetSliderLabelsSides(bool *left, bool *right) const;


    // the object which manages our thumb
  //  wxScrollThumb m_thumb;

    // the slider range and value
    int m_min,
        m_max,
        m_value;

    // the tick frequence (default is 1)
    int m_tickFreq;
    // the page increments (logical units)
    int   m_pageSize;

    // the size of the thumb (in pixels)
	int m_type;
	long m_sliderstyle;
	int m_status;
	int m_htLast;
	int m_ofsMouse;
	bool m_capture;
	bool m_dirty;
	

    // the part of the client area reserved for the label, the ticks and the
    // part for the slider itself
    wxRect m_rectLabel,
           m_rectTicks,
           m_rectSlider;

    // the state of the thumb (wxCONTROL_XXX constants sum)
    //int m_thumbFlags;

    DECLARE_EVENT_TABLE();
};

