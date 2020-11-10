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


#include "zzplayer.h"
#include "zzplayer.moc"

//Constructeur
ZZplayer::ZZplayer()
{
	KStdAccel stdAccel;

	// initialisation
	sdl_screen = 0;
	mpeg = 0;
	SMPEG_PAUSED=false;

	// Impossible de changer la taille de l'appli
	setMinimumSize( 230, 91 );
	setMaximumSize( 230, 91 );


	// Le menu "fichier"
	QPopupMenu *file_menu = new QPopupMenu;
	// Les fichiers recents	
	recentPopup = new QPopupMenu();
	file_menu->insertItem(i18n("Open..."), this, SLOT(slotOpenFile()), stdAccel.open());
	file_menu->insertItem(i18n("Open Recent"), recentPopup);
	file_menu->insertSeparator();
	file_menu->insertItem(i18n("Quit"), this, SLOT(slotBye()), stdAccel.quit());
	// On connecte le recentPopup sur sa fonction
	connect(recentPopup,SIGNAL(activated(int)),SLOT(slotOpenRecent(int)));


	// Le menu options
	option_menu = new QPopupMenu();
//	fullScreen=option_menu->insertItem(i18n("Fullscreen when open"), this, SLOT(slotFullScreen()));
	doubleSize=option_menu->insertItem(i18n("Double size"), this, SLOT(slotDoubleSize()));
	videoLoop=option_menu->insertItem(i18n("Loop"), this, SLOT(slotVideoLoop()));
	withAudio=option_menu->insertItem(i18n("Audio"), this, SLOT(slotWithAudio()));
	option_menu->insertSeparator();
	option_menu->insertItem(i18n("Save options"), this, SLOT(slotSaveOptions()));
	saveOptionsOnExit=option_menu->insertItem(i18n("Save options on Exit"), this, SLOT(slotSaveOptionsOnExit()));

	// Le menu help
	QPopupMenu *help_menu = new QPopupMenu();
	help_menu->insertItem(i18n("Help contents"), this, SLOT(slotHelpContents()));
	help_menu->insertItem(i18n("About ZZplayer..."), this, SLOT(slotHelpAbout()));

	// Barre de menu
	menuBar = new KMenuBar(this, "menubar");
	menuBar->insertItem(i18n("&File"), file_menu);
	menuBar->insertItem(i18n("&Options"), option_menu);
	menuBar->insertItem(i18n("&Help"), help_menu);
	setMenu(menuBar);

	// Barre d'outil
	toolBar = new KToolBar(this);
	toolBar->insertButton(ICON("play.xpm"), TOOLBAR_PLAY, true,i18n("Play"));
	toolBar->insertButton(ICON("pause.xpm"), TOOLBAR_PAUSE, true,i18n("Pause"));
	toolBar->insertButton(ICON("stop.xpm"), TOOLBAR_STOP, true,i18n("Stop"));
	toolBar->insertButton(ICON("open.xpm"), TOOLBAR_OPEN, true,i18n("Open File"));
	toolBar->insertButton(ICON("fullscreen.xpm"), TOOLBAR_FULLSCREEN, true,i18n("Fullscreen Now"));
	// passe le bouton pause en 2 etats
	toolBar->setToggle(TOOLBAR_PAUSE,true);

	// Connexion de la barre de boutons à la méthode slotToolbarClicked
	connect(toolBar,SIGNAL(clicked(int)), this,SLOT(slotToolbarClicked(int)));
	addToolBar(toolBar);

        // zone pour le drag and drop
	KDNDDropZone * dropZone = new KDNDDropZone( this, DndURL );
	connect( dropZone, SIGNAL( dropAction( KDNDDropZone *) ),this, SLOT( slotDropAction( KDNDDropZone *) ) );
	
    	labelfps = new QLabel( i18n( " Fps : 0.00\n Frame : 00000"), this, "" );
	labelfps->setAlignment( AlignTop );
	labelfps->setFrameStyle( QFrame::Box | QFrame::Sunken );
	labelfps->setGeometry( 140, 51, 90, 40 );

	// installe un timer qui affiche les fps toute les secondes
	QTimer *internalTimer = new QTimer( this ); // create internal timer
	connect( internalTimer, SIGNAL(timeout()), SLOT(fps()) );
        internalTimer->start( 1000 );

	// Barre de volume
	volumeSlider = new QSlider(this);
	volumeSlider->setOrientation(QSlider::Horizontal);
	volumeSlider->setRange(0,100);
	volumeSlider->setSteps(1,10);
	volumeSlider->setTickmarks( QSlider::Above );
	volumeSlider->setTickInterval(10);
	volumeSlider->setTracking(true);
        connect(volumeSlider,SIGNAL(valueChanged(int)),
                 this,SLOT(slotVolumeSlider(int)) );
	volumeSlider->setGeometry(30,55,100,30);

	// Pixmap du haut parleur
	QPixmap pixsound(ICON("sound.xpm"));
	QLabel *labelsound;
	labelsound = new QLabel(this);
	labelsound->setPixmap( pixsound );	
	labelsound->setGeometry( 5, 60, 16, 22 );
	
	// Lecture des options dans le fichier de config
	slotReadOptions();
}



// Destructeur
ZZplayer::~ZZplayer()
{
	// Fermeture du fichier courant
	closeFile();
	// sauvegarde des options si la case est cochée
	if (option_menu->isItemChecked(saveOptionsOnExit)){	
		slotSaveOptions();
        }

	// destruction des barres d'outils et de menu
	delete toolBar;
	delete menuBar;
}



// ouvre un fichier de la liste
void ZZplayer::slotOpenRecent(int id) {
	loadURL(recentPopup->text(id));
}



void ZZplayer::slotDropAction( KDNDDropZone * _dropZone )
{
  // obtenir la liste des URLs déposées
  QStrList urls = _dropZone->getURLList();
  // ouvrir la première URL
  if ( urls.first() )  loadURL( urls.first() );
}



void ZZplayer::slotToolbarClicked(int item){
  switch (item) {
  case TOOLBAR_FULLSCREEN: // bouton Fullscreen
    slotFullScreenNow();
    break;
  case TOOLBAR_OPEN: // bouton Ouvrir
    slotOpenFile();
    break;
  case TOOLBAR_STOP: // bouton stop
    stop();
    break;
  case TOOLBAR_PLAY: // bouton play
    play();
    break;
  case TOOLBAR_PAUSE: // bouton rewind
    pause();
    break;
  }
}



// Slider pour le volume
void ZZplayer::slotVolumeSlider(int vol){
	audioVolume=vol;
	if (mpeg){
		SMPEG_setvolume( mpeg, audioVolume );
	}
}

// Passe la video en fullscreen maintenant
void ZZplayer::slotFullScreenNow(){
       	playFullScreen();
}



// CheckedBox pour savoir si on joue la video en fullscreen lorsqu'on appuie sur play
void ZZplayer::slotFullScreen(){
//	bool newbool = !option_menu->isItemChecked(fullScreen);
//	option_menu->setItemChecked(fullScreen , newbool);
}



// CheckedBox pour avoir l'image en taille double
void ZZplayer::slotDoubleSize(){
	bool newbool = !option_menu->isItemChecked(doubleSize);
	option_menu->setItemChecked(doubleSize , newbool);
	enableVideo();
}



// CheckedBox pour que la video boucle
void ZZplayer::slotVideoLoop(){
	bool newbool = !option_menu->isItemChecked(videoLoop);
	option_menu->setItemChecked(videoLoop , newbool);
}



// CheckedBox pour sauvegarder les options si on quit
void ZZplayer::slotSaveOptionsOnExit(){
	bool newbool = !option_menu->isItemChecked(saveOptionsOnExit);
	option_menu->setItemChecked(saveOptionsOnExit, newbool);
}



// CheckedBox pour avoir l'image sans le son
void ZZplayer::slotWithAudio(){
	bool newbool = !option_menu->isItemChecked(withAudio);
	option_menu->setItemChecked(withAudio , newbool);
}



// Lecture des options du fichier de config
void ZZplayer::slotReadOptions(){
	// Relit la dernière config
	KConfig* config = kapp->getConfig();
	// position et géométrie de la fenêtre										
	QRect* pDefaultGeom = new QRect( 0, 0, 230,91 );
	config->setGroup( "General Options" );
	QRect geom = config->readRectEntry( "Geometry", pDefaultGeom );
	this->setGeometry( geom );
	delete pDefaultGeom;
	// CheckBox saveOptionsOnExit
	option_menu->setItemChecked(saveOptionsOnExit ,config->readBoolEntry("saveOptionsOnExit" ,TRUE));
	// CheckBox doubleSize
	option_menu->setItemChecked(doubleSize ,config->readBoolEntry("doubleSize" ,FALSE));
	// CheckBox videoLoop
	option_menu->setItemChecked(videoLoop ,config->readBoolEntry("videoLoop" ,FALSE));
	// CheckBox Audio
	option_menu->setItemChecked(withAudio ,config->readBoolEntry("withAudio" ,TRUE));
	// CheckBox fullScreen
//	option_menu->setItemChecked(fullScreen ,config->readBoolEntry("fullScreen" ,FALSE));
        // Volume
        audioVolume=config->readNumEntry("audioVolume",50);


        // Fichiers recents
	int z;
	char name[16];
	QString s;

	for (z = 0; z < 5; z++) {
		sprintf(name, "Recent%d", z + 1);
		s = config->readEntry(name);
		if (!s.isEmpty()) recentPopup->insertItem(s);
	}
}



// Sauvegarde les options dans le fichier de config
void ZZplayer::slotSaveOptions(){
	int z;
	char name[16];
	
	KConfig* config = kapp->getConfig();										
	config->setGroup( "General Options" );
	config->writeEntry( "Geometry", this->geometry() );
	config->writeEntry("saveOptionsOnExit" ,option_menu->isItemChecked(saveOptionsOnExit));
	config->writeEntry("doubleSize" ,option_menu->isItemChecked(doubleSize));
//	config->writeEntry("fullScreen" ,option_menu->isItemChecked(fullScreen));
	config->writeEntry("videoLoop" ,option_menu->isItemChecked(videoLoop));
	config->writeEntry("withAudio" ,option_menu->isItemChecked(withAudio));
	config->writeEntry("audioVolume" ,audioVolume);
	// fichiers recents
	for (z = 0; z < (int) recentPopup->count(); z++) {
		sprintf(name, "Recent%d", z + 1);
		config->writeEntry(name, recentPopup->text(z));
	}
	
	config->sync();
}



// Quit l'appli
void ZZplayer::slotBye(){
	deleteAll();
	kapp->quit();
}



void ZZplayer::loadURL( QString url )
{
	if ( KFM::download( url, fileName ) ){ // télécharge le fichier
		loadFile();          // ouvre le fichier temporaire local
		KFM::removeTempFile( fileName );    // efface le fichier temporaire
	}
}



void ZZplayer::slotOpenFile(){
	fileName=KFileDialog::getOpenFileName(fileName,	"*.mpg|MPG Files (*.mpg)\n"
							"*|All Files (*)\n");
	if (!fileName.isEmpty()){
		loadFile();
	}
}



void ZZplayer::loadFile()
{
	int z;

	// fermeture du fichier courant
	closeFile();

	// Create the MPEG stream
	mpeg = SMPEG_new(fileName, &info , 1);
	if ( SMPEG_error(mpeg) ) {
		KMsgBox::message( this, fileName, SMPEG_error(mpeg) );
	        SMPEG_delete(mpeg);
	        mpeg = NULL;
        	return;
	}

	// On place le fichier dans les fichiers recents
	z = (int) recentPopup->count();
	while (z > 0) {
		z--;
		if (!strcmp(fileName, recentPopup->text(z))) recentPopup->removeItemAt(z);
	}
	recentPopup->insertItem(fileName, 0, 0);
	if (recentPopup->count() > 5) recentPopup->removeItemAt(5);
	for (z = 0; z < 5; z++) recentPopup->setId(z, z);

	// On regle le son
	volumeSlider->setValue(audioVolume);
	SMPEG_setvolume( mpeg, audioVolume);

	// initialise le mode video
       	enableVideo();
	
	SDL_WM_SetCaption(fileName,"ZZplayer Video");
	SMPEG_setdisplay(mpeg, sdl_screen, NULL, NULL);

        // lance la lecture de la video
	play();

//	if (option_menu->isItemChecked(fullScreen)){
//		playFullScreen();
//	}
}



// Ferme le fichier courant
void ZZplayer::closeFile()
{
    stop();
    if ( mpeg ) {
        SMPEG_delete( mpeg );
    }
}



 void ZZplayer::enableVideo()
{
	int statut;

	if (!mpeg)
		return;

	// sauvegarde du statut
	statut=SMPEG_status(mpeg );

	if (!SMPEG_PAUSED){	
		SMPEG_stop(mpeg);
	}	

	if (sdl_screen){
		SDL_FreeSurface(sdl_screen);
		sdl_screen=0;
	}

	// Set up video display if needed
	if ( info.has_video ) {
		if (option_menu->isItemChecked(doubleSize)){
			sdl_screen=SDL_SetVideoMode(info.width*2,info.height*2,0,SDL_HWSURFACE);
                }else {
			sdl_screen=SDL_SetVideoMode(info.width,info.height,0,SDL_HWSURFACE);
		}
        }
	if ( mpeg && sdl_screen ){
    	  	SMPEG_double(mpeg, option_menu->isItemChecked(doubleSize));
        	clearscreen();

		if (!SMPEG_PAUSED && (statut==SMPEG_PLAYING)){	
			SMPEG_play(mpeg);
		}	
	}
}



// Fullscreen
void ZZplayer::playFullScreen(){
	int statut;

	if (!mpeg)
		return;

	// sauvegarde du statut
	statut=SMPEG_status(mpeg );

	if (!SMPEG_PAUSED){	
		SMPEG_stop(mpeg);
	}	

	if (sdl_screen){
		SDL_FreeSurface(sdl_screen);
		sdl_screen=0;
	}

	// Set up video display if needed
	if ( info.has_video ) {
		if (option_menu->isItemChecked(doubleSize)){
			sdl_screen=SDL_SetVideoMode(info.width*2,info.height*2,0, SDL_FULLSCREEN | SDL_HWSURFACE);
                }else {
			sdl_screen=SDL_SetVideoMode(info.width,info.height,0, SDL_FULLSCREEN | SDL_HWSURFACE);
		}
        }
	if ( mpeg && sdl_screen ){
    	  	SMPEG_double(mpeg, option_menu->isItemChecked(doubleSize));
        	clearscreen();
	

		SMPEG_loop (mpeg, option_menu->isItemChecked(videoLoop));


		if (!SMPEG_PAUSED && (statut==SMPEG_PLAYING)){	
			SMPEG_play(mpeg);
		}	


		SDL_Event event;
		SDL_EventState (SDL_ACTIVEEVENT, SDL_IGNORE);
		SDL_EventState (SDL_MOUSEMOTION, SDL_IGNORE);
		while (!SDL_PollEvent (&event) && SMPEG_status (mpeg) == SMPEG_PLAYING)
			SDL_Delay(500);		
		SMPEG_loop (mpeg, false);
		enableVideo();
	} else {
		enableVideo();
		if (!SMPEG_PAUSED && (statut==SMPEG_PLAYING)){	
			SMPEG_play(mpeg);
		}
	}	
}



void ZZplayer::stop()
{
	if(mpeg ){
		// Stop la video
		SMPEG_stop(mpeg );
		// Rembobine
		rewind();
    	}
}



void ZZplayer::play()
{
	if( mpeg ){
        	// Set audio playback
        	SMPEG_enableaudio(mpeg, option_menu->isItemChecked(withAudio));

        	// Play the movie
		rewind();
		SMPEG_play( mpeg );
	}
}



void ZZplayer::rewind()
{
	// Enleve la pause si elle etait active
	if (SMPEG_PAUSED) {
		toolBar->toggleButton(TOOLBAR_PAUSE);
		SMPEG_PAUSED=!SMPEG_PAUSED;
	}

	if( mpeg ){
        	// Rewind the movie
        	SMPEG_rewind( mpeg );
	        clearscreen();
	}
}



void ZZplayer::pause()
{
	SMPEG_PAUSED=!SMPEG_PAUSED;
	if( mpeg ){
	        SMPEG_pause( mpeg );
	}
}



void ZZplayer::clearscreen()
{
    if ( sdl_screen ) {
        SDL_FillRect(sdl_screen,NULL,SDL_MapRGB(sdl_screen->format,0,0,0));
        SDL_UpdateRect(sdl_screen, 0, 0, 0, 0);
    }
}



void ZZplayer::slotHelpAbout()
{
	QString msg = "ZZplayer\n\n";
	msg += "Copyright (c) 1999 Nicolas Vignal <nicolas.vignal@fnac.net>\n\n";
	msg += "This program is free software; you can redistribute it\nand/or modify";
	msg += " it under the terms of the GNU General Public\nLicense as";
	msg += " published by";
	msg += " the Free Software Foundation; either\nversion 2 ";
	msg += "of the License, or (at your option) any later version.\n\n";
	msg += "The program is distributed in hopes that it will be useful,\nbut";
	msg += " WITHOUT ANY WARRANTY; without even the implied\nwarranty of";
	msg += " MERCHANTABILITY or FITNESS FOR A\nPARTICULAR PURPOSE. See the GNU";
	msg += " General Public\nLicense for more details.\n\n";

	msg += "You should have received a copy of the GNU General\nPublic License along";
	msg += " with this program.  If not, write\nto the Free Software Foundation, Inc.,";
	msg += " 675 Mass Ave,\nCambridge, MA 02139, USA.";

	KMsgBox::message( this, "About ZZplayer", msg );

}



void ZZplayer::slotHelpContents()
{
      kapp->invokeHTMLHelp("ZZplayer/zzplayer.html", "");
}



void ZZplayer::fps()
{
	QString labeltext;
	// Mise a jour de frame et Fps
	if (mpeg) {
		SMPEG_getinfo( mpeg, &info );
		if ( SMPEG_status(mpeg )==SMPEG_PLAYING){		
			labeltext.sprintf(" Fps : %.2f \n Frame : %.5i",info.current_fps,info.current_frame);
		} else {
			labeltext.sprintf(" Fps :  \n Frame : %.5i",info.current_frame);
		}
		labelfps->setText(labeltext);

		// On boucle
		if ( SMPEG_status(mpeg )==SMPEG_STOPPED && (option_menu->isItemChecked(videoLoop)) && !SMPEG_PAUSED ){		
			play();
		}
	}
}