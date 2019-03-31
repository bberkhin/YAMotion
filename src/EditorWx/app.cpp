
#include "wx/wx.h"
#include "wx/intl.h"


#include "appdefs.h"
#include "appframe.h"
#include "configdata.h"




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
	App() { m_lang = wxLANGUAGE_UNKNOWN; }

	//! the main function called during application start
	virtual bool OnInit() wxOVERRIDE;

	//! application exit function
	virtual int OnExit() wxOVERRIDE;

private:
	//! frame window
	AppFrame* m_frame;
	
protected:
	// Lang support
	wxLanguage m_lang;  // language specified by user
	wxLocale m_locale;  // locale we'll be using
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


// language data
static const wxLanguage langIds[] =
{
	wxLANGUAGE_DEFAULT,
	wxLANGUAGE_RUSSIAN,
/*
	wxLANGUAGE_FRENCH,
	wxLANGUAGE_ITALIAN,
	wxLANGUAGE_GERMAN,
	wxLANGUAGE_BULGARIAN,
	wxLANGUAGE_CZECH,
	wxLANGUAGE_POLISH,
	wxLANGUAGE_SWEDISH,
#if wxUSE_UNICODE || defined(__WXMOTIF__)
	wxLANGUAGE_JAPANESE,
#endif
#if wxUSE_UNICODE
	wxLANGUAGE_GEORGIAN,
	wxLANGUAGE_ENGLISH,
	wxLANGUAGE_ENGLISH_US,
	wxLANGUAGE_ARABIC,
	wxLANGUAGE_ARABIC_EGYPT
#endif
*/
};


// note that it makes no sense to translate these strings, they are
// shown before we set the locale anyhow
const wxString langNames[] =
{
	"English",
	"Russian"
/*
	"French",
	"Italian",
	"German",	
	"Bulgarian",
	"Czech",
	"Polish",
	"Swedish",
#if wxUSE_UNICODE || defined(__WXMOTIF__)
	"Japanese",
#endif
#if wxUSE_UNICODE
	"Georgian",
	"English",
	"English (U.S.)",
	"Arabic",
	"Arabic (Egypt)"
#endif
*/
};

// the arrays must be in sync
wxCOMPILE_TIME_ASSERT(WXSIZEOF(langNames) == WXSIZEOF(langIds),
	LangArraysMismatch);


bool App::OnInit() 
{
	if (!wxApp::OnInit())
		return false;

	wxInitAllImageHandlers();
	// set application and vendor name
	SetAppName(APP_NAME);
	SetVendorName(APP_VENDOR);



	// GCode & Gcmc lexer
	LINK_LEXER(lmGcode)
	LINK_LEXER(lmGcmc)
		// create application frame
		
	wxConfigBase::Set( new ConfigData() ); //wxConfig

// Init lang	
	if (m_lang == wxLANGUAGE_UNKNOWN)
	{
		int lng = wxGetSingleChoiceIndex
		(
			_("Please choose language:"),
			_("Language"),
			WXSIZEOF(langNames),
			langNames
		);
		m_lang = lng == -1 ? wxLANGUAGE_DEFAULT : langIds[lng];
	}

	// do nothing if system
	if (m_lang != wxLANGUAGE_DEFAULT)
	{
		// don't use wxLOCALE_LOAD_DEFAULT flag so that Init() doesn't return
	   // false just because it failed to load wxstd catalog
		if (!m_locale.Init(m_lang, wxLOCALE_DONT_LOAD_DEFAULT))
		{
			wxMessageBox(_("This language is not supported by the system."));

			// continue nevertheless
		}

		// normally this wouldn't be necessary as the catalog files would be found
		// in the default locations, but when the program is not installed the
		// catalogs are in the build directory where we wouldn't find them by
		// default
		wxLocale::AddCatalogLookupPathPrefix(".");

		// Initialize the catalogs we'll be using
		const wxLanguageInfo* pInfo = wxLocale::GetLanguageInfo(m_lang);
		if (!m_locale.AddCatalog("messages"))
		{
			wxMessageBox(_("Couldn't find/load the 'messages' catalog for locale '%s'."),
				pInfo ? pInfo->GetLocaleName() : _("unknown"));
		}
	}

	m_frame = new AppFrame(APP_NAME);
	// open application frame
	m_frame->Layout();
	m_frame->Show(true);

	return true;
}

int App::OnExit()
{
	wxConfigBase *config = wxConfigBase::Set(NULL);
	if ( config )
		delete config;
	return 0;
}

const char *gcode_gettext(const char *s)
{	
	return wxGetTranslation(s);
}
