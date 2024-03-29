#pragma once

//============================================================================
// declarations
//============================================================================

#define APP_NAME "Matilda"
#define APP_DESCR "Matilda CNC Editor"

#define APP_MAINT "Boris Berkhin"
#define APP_VENDOR "Matilda"
#define APP_COPYRIGTH " 2019 Boris Berkhin"
#define APP_LICENCE "Freeware"
#define APP_GCMCAUTHOR "Bertho Stultiens"
#define APP_GCMCHOMEPAGE "http://www.vagrearg.org"
#define APP_GCMCHOMEPAGEURL "http://www.vagrearg.org"

#define APP_VERSION_MAJOR  0
#define APP_VERSION_MINOR  1
#define APP_VERSION_REVISION 259
#define APP_VERSION_EXTSTR  L"beta"
#define APP_VERSION_RESSTRING "0.1.259"
#define APP_VERSION  wxString::Format(L"%d.%d.%d %s",APP_VERSION_MAJOR,APP_VERSION_MINOR,APP_VERSION_REVISION,APP_VERSION_EXTSTR)
#define APP_BUILD __DATE__

#define APP_WEBSITE "matildacnc.com"
#define APP_WEBSITETEXT "https://matildacnc.com"
#define APP_WEBSITEURL "https://matildacnc.com"
//#define APP_EMAILURL "mailto:bberkhin@matildacnc.com"
#define APP_EMAILTEXT  "bberkhin@matildacnc.com"
#define APP_EMAILURL (wxString::Format(L"mailto:bberkhin@matildacnc.com?subject=%s%%20%s", wxString(APP_NAME), wxString(APP_VERSION)))

#define NONAME _("<untitled>")
#define WXSTRINGCOPYRIGHT wxString(wxString((wchar_t)0xA9) + APP_COPYRIGTH)

#define HELP_GCMC L"/gcmchelp"
#define HELP_GCODE L"/gcodehelp"
#define HELP_EDITOR L"/editorhelp"
#define HELP_DOWNLOAD L"#download"
#define HELP_FEEDBACK L"#contacts"
