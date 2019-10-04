#pragma once

//============================================================================
// declarations
//============================================================================

#define APP_NAME "Matilda"
#define APP_DESCR "See http://www.matildacnc.org"

#define APP_MAINT "Boris Berkhin"
#define APP_VENDOR "Matilda"
#define APP_COPYRIGTH " 2019 Boris Berkhin"
#define APP_LICENCE "Freeware"
#define APP_GCMCAUTHOR "Bertho Stultiens"
#define APP_GCMCHOMEPAGE "http://www.vagrearg.org"
#define APP_GCMCHOMEPAGEURL "http://www.vagrearg.org"

#define APP_VERSION_MAJOR  0
#define APP_VERSION_MINOR  1
#define APP_VERSION_EXTSTR  L" beta"
#define APP_VERSION  wxString::Format(L"%d.%d%s",APP_VERSION_MAJOR,APP_VERSION_MINOR,APP_VERSION_EXTSTR)
#define APP_BUILD __DATE__

#define APP_WEBSITETEXT "http://matildacnc.com"
#define APP_WEBSITEURL "http://matildacnc.com"
#define APP_EMAILURL "mailto:bberkhin@gmail.com"
#define APP_EMAILTEXT  "bberkhin@gmail.com"

#define NONAME _("<untitled>")
#define WXSTRINGCOPYRIGHT wxString(wxString((wchar_t)0xA9) + APP_COPYRIGTH)

#define HELP_GCMC L"/gcmchelp"
#define HELP_GCODE L"/gcodehelp"
#define HELP_EDITOR L"/editorhelp"
