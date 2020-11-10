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



int main(int argc, char* argv[])
{
	KApplication app(argc,argv,"ZZplayer");

	// Initialisation de la SDL
	if( SDL_Init( SDL_INIT_AUDIO|SDL_INIT_VIDEO ) < 0 ){
	        fprintf( stderr, "Couldn't initialize SDL: %s\n", SDL_GetError() );
	        exit( 1 );
	}
	atexit( SDL_Quit );

	ZZplayer *player = new ZZplayer;
	if ( argc==2 ) {
		player->fileName=argv[1];		
	}
	else {
		player->fileName=kapp->kde_datadir() + "/ZZplayer/ZZplayer.mpg";
	}
	player->loadFile();
	player->show();
	return app.exec();
}

