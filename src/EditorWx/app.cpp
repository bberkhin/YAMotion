
#include "wx/wx.h"


#include "appdefs.h"
#include "appframe.h"


#include "..\..\src\stc\scintilla\include\ILexer.h"
#include "..\..\src\stc\scintilla\include\Scintilla.h"
#include "..\..\src\stc\scintilla\include\SciLexer.h"


#include "..\..\src\stc\scintilla\lexlib\LexerModule.h"
#include "..\..\src\stc\scintilla\src\Catalogue.h"

//============================================================================
// implementation
//============================================================================

class AppFrame;

//----------------------------------------------------------------------------
//
class App : public wxApp
{
	friend class AppFrame;
public:
	//! the main function called during application start
	virtual bool OnInit() wxOVERRIDE;

	//! application exit function
	virtual int OnExit() wxOVERRIDE;

private:
	//! frame window
	AppFrame* m_frame;
protected:

	wxDECLARE_EVENT_TABLE();
};

// created dynamically by wxWidgets
wxDECLARE_APP(App);


wxIMPLEMENT_APP(App);


wxBEGIN_EVENT_TABLE(App, wxApp)
wxEND_EVENT_TABLE()

//----------------------------------------------------------------------------
// App
//----------------------------------------------------------------------------
#define LINK_LEXER(lexer) extern LexerModule lexer; Catalogue::AddLexerModule(&lexer);


bool App::OnInit() {

	wxInitAllImageHandlers();

	// set application and vendor name
	SetAppName(APP_NAME);
	SetVendorName(APP_VENDOR);

	// GCode lexer
	LINK_LEXER(lmGcode)
		// create application frame
	m_frame = new AppFrame(APP_NAME);

	// open application frame
	m_frame->Layout();
	m_frame->Show(true);

	return true;
}

int App::OnExit()
{
	return 0;
}