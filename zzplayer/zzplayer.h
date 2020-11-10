//============================================================================
//
//	ZZplayer : MPEG-I video player
// 	Copyright (C) 1999 Nicolas Vignal <nicolas.vignal@fnac.net
//
//	Requires the Qt widget libraries, available at no cost at
//      http://www.troll.no
//	
//  Author  : Nicolas Vignal
//  E-Mail  : nicolas.vignal@fnac.net
//  Home    : http://www.chez.com/tsc/zzplayer/zzplayer.html

// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//
//============================================================================

#ifndef zzplayer_h
#define zzplayer_h

#include <stdlib.h>
#include <string.h>

#include <kapp.h>
#include <ktmainwindow.h>
#include <kiconloader.h>
#include <kfiledialog.h>
#include <kmsgbox.h>
#include <kstdaccel.h>
#include <kfm.h>
#include <drag.h>
#include <qpopupmenu.h>
#include <qkeycode.h>
#include <qlabel.h>
#include <qslider.h>
#include <qtimer.h>
#include <qpixmap.h>
#include <smpeg/smpeg.h>
#include "SDL.h"


class ZZplayer : public KTMainWindow {
  Q_OBJECT

//Atributs
private :
	KToolBar   *toolBar;
	KMenuBar   *menuBar;
	QPopupMenu *option_menu;
	QPopupMenu *recentPopup;
	int saveOptionsOnExit;
	int fullScreen;
	int doubleSize;	
	int videoLoop;
	int withAudio;
	int audioVolume;
	bool SMPEG_PAUSED;
	
	QSlider *volumeSlider;
	QLabel *labelfps;

	SMPEG* mpeg;
	SMPEG_Info info;
	SDL_Surface* sdl_screen;
	enum {	TOOLBAR_FULLSCREEN,
		TOOLBAR_OPEN,
		TOOLBAR_STOP,
		TOOLBAR_PLAY,
		TOOLBAR_PAUSE};

//Methodes
public:
	ZZplayer();
	~ZZplayer();

	void loadURL( QString );
	void loadFile();
	QString fileName;

public slots:
	void slotBye();
	void slotDoubleSize();
	void slotDropAction( KDNDDropZone * );
	void slotFullScreen();
	void slotFullScreenNow();
	void slotHelpAbout();
	void slotHelpContents();
	void slotOpenFile();
	void slotOpenRecent(int id);
	void slotReadOptions();
	void slotSaveOptions();
	void slotSaveOptionsOnExit();
	void slotToolbarClicked(int);
	void slotVideoLoop();
	void slotVolumeSlider(int vol);
	void slotWithAudio();

private slots:
	void clearscreen();
	void closeFile();
	void enableVideo();
	void fps();
	void pause();
	void play();
	void playFullScreen();
	void rewind();
	void stop();
};

#endif
