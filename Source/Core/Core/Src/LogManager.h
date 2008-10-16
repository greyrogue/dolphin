// Copyright (C) 2003-2008 Dolphin Project.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 2.0.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License 2.0 for more details.

// A copy of the GPL 2.0 should have been included with the program.
// If not, see http://www.gnu.org/licenses/

// Official SVN repository and contact information can be found at
// http://code.google.com/p/dolphin-emu/


// Dolphin Logging framework. Needs a good ol' spring cleaning methinks.

#ifndef _LOGMANAGER_H
#define _LOGMANAGER_H

#include "Common.h"

class CLogWindow;

// should be inside the LogManager ...
struct CDebugger_Log
{
	char m_szName[128];
	char m_szShortName[32];
	char m_szFilename[256];
	bool m_bLogToFile;
	bool m_bShowInLog;
	bool m_bEnable;
	FILE *m_pFile;

	void Init();
	void Shutdown();

	// constructor
	CDebugger_Log(const char* _szShortName, const char* _szName);

	// destructor
	~CDebugger_Log();
};

class LogManager
{
	#define	MAX_MESSAGES 8000   // the old value was to large
	#define MAX_MSGLEN  256
public:

	// Message
	struct SMessage
	{
		bool m_bInUse;
		LogTypes::LOG_TYPE m_type;
		char m_szMessage[MAX_MSGLEN];
		int m_dwMsgLen;

		// constructor
		SMessage() :
		m_bInUse(false)
		{}

		// set
		void Set(LogTypes::LOG_TYPE _type, char* _szMessage)
		{
			strncpy(m_szMessage, _szMessage, MAX_MSGLEN-1);
			m_szMessage[MAX_MSGLEN-1] = 0;
			m_dwMsgLen = (int)strlen(m_szMessage);

            if (m_dwMsgLen == (MAX_MSGLEN-1))
            {
                m_szMessage[m_dwMsgLen-2] = 0xd;
                m_szMessage[m_dwMsgLen-1] = 0xa;
            }
			m_szMessage[m_dwMsgLen] = 0;

			m_type = _type;
			m_bInUse = true;
		}
		//
		static void Log(LogTypes::LOG_TYPE _type, const char *_fmt, ...);
	};
private:
	friend class CDebugger_LogWindow;
	friend class CLogWindow;
	static SMessage *m_Messages;
	static int m_nextMessages;
	static int m_activeLog;
	static bool m_bDirty;
	static bool m_bInitialized;
	static CDebugger_Log* m_Log[LogTypes::NUMBER_OF_LOGS];
public:
	static void Init();
	static void Clear(void);
	static void Shutdown();
	static void Log(LogTypes::LOG_TYPE _type, const char *_fmt, ...);
};

extern bool IsLoggingActivated();

#endif
