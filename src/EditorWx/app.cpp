
#include "wx/wx.h"
#include "wx/intl.h"
#include "app.h"
#include "appdefs.h"
#include "appframe.h"
#include "configdata.h"
#include "standartpaths.h"
#include "environmentsimple.h"

/// RUNCH

#include "..\..\src\stc\scintilla\include\ILexer.h"
#include "..\..\src\stc\scintilla\include\Scintilla.h"
#include "..\..\src\stc\scintilla\include\SciLexer.h"


#include "..\..\src\stc\scintilla\lexlib\LexerModule.h"
#include "..\..\src\stc\scintilla\src\Catalogue.h"

//============================================================================
// implementation
//============================================================================


wxIMPLEMENT_APP(App);


wxBEGIN_EVENT_TABLE(App, wxApp)

wxEND_EVENT_TABLE()

//----------------------------------------------------------------------------
// App
//----------------------------------------------------------------------------
#define LINK_LEXER(lexer) extern LexerModule lexer; Catalogue::AddLexerModule(&lexer);


// language data
const wxLanguage g_langIds[] =
{
	wxLANGUAGE_DEFAULT,
	wxLANGUAGE_RUSSIAN,
	wxLANGUAGE_FRENCH,
/*
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
const wxString g_langNames[] =
{
	"English",
	"Russian",
	"French",
/*
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
wxCOMPILE_TIME_ASSERT(WXSIZEOF(g_langNames) == WXSIZEOF(g_langIds),
	LangArraysMismatch);

const int g_lang_count = WXSIZEOF(g_langNames);

App::~App()
{
	if (m_restart)
	{
		// argv[0] contains the full path to the executable

		wxExecuteEnv env;
		env.cwd = StandartPaths::Get()->GetRootPath().c_str();
		wxExecute(argv[0], wxEXEC_ASYNC, NULL, &env);
	}

}

bool App::OnInit() 
{
	if (!wxApp::OnInit())
		return false;

	wxConvCurrent = &wxConvUTF8;

	wxInitAllImageHandlers();
	// set application and vendor name
	SetAppName(APP_NAME);
	SetVendorName(APP_VENDOR);



	// GCode & Gcmc lexer
	LINK_LEXER(lmGcode)
	LINK_LEXER(lmGcmc)
		// create application frame

	env.reset(new EnvironmentSimple());
	ConfigData *config = new ConfigData();
	wxConfigBase::Set(config); //wxConfig
	wxLanguage m_lang = wxLANGUAGE_UNKNOWN;  // language specified by user

	if ( !config->IsFirstTimeRun() )
		m_lang = static_cast<wxLanguage>(config->GetLanguage(wxLANGUAGE_UNKNOWN));


	// Init lang	
	if (m_lang == wxLANGUAGE_UNKNOWN)
	{
		int lng = wxGetSingleChoiceIndex
		(
			_("Please choose language:"),
			_("Language"),
			g_lang_count,
			g_langNames
		);
		m_lang = lng == -1 ? wxLANGUAGE_DEFAULT : g_langIds[lng];
		config->SetLanguage(m_lang);
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
		wxLocale::AddCatalogLookupPathPrefix(wxString(".\\") + wxString(RESOURCES_DIR));

		// Initialize the catalogs we'll be using
		const wxLanguageInfo* pInfo = wxLocale::GetLanguageInfo(m_lang);
		if (!m_locale.AddCatalog("messages"))
		{
			wxMessageBox(wxString::Format(_("Couldn't find/load the 'messages' catalog for locale '%s'."),
				pInfo ? pInfo->GetLocaleName() : _("unknown")));
			config->SetLanguage(wxLANGUAGE_DEFAULT);
		}
		else // language changed
		{
			wxString loc_name = pInfo->GetLocaleName();			
			StandartPaths::Get()->SetLanguageCatalog( loc_name.BeforeFirst('-').c_str() );
		}
	}
	

	m_frame = new AppFrame(APP_NAME);
	// open application frame
	m_frame->Layout();
	m_frame->Show(true);

	return true;
}

void App::Restart()
{
	m_restart = true;
	ExitMainLoop();
}

int App::OnExit()
{
	wxConfigBase *config = wxConfigBase::Set(NULL);
	if ( config )
		delete config;
	return 0;
}


bool App::GetUptadeInfo(wxString &out)
{
	out = _("There is new version of YAMotion. A lot of new features! Be in tuch");
	return true;
}


const char *gcode_gettext(const char *s)
{	
	return wxGetTranslation(s);
}
