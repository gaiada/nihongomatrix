/***************************************************************************
 *   Copyright (C) 2011 by Gaiada,45,69,64   *
 *   gaiada@gaiadaware   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


// SDL_Functions: Copied from gpwiki.org.
#include <cstdlib> // For some useful functions such as atexit :)
#include <stdlib.h>
#include "SDL.h" // main SDL header
#include "SDL_image.h" // image library, if your only using BMP's, get ride of this.
#include "database.h"
#include "kanji.h"
#include <iostream> 
#define true 1
#define false  0 //You might have to declaire True and False.
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 480
#define COLORKEY 255, 0, 255 //Your Transparent colour

using namespace std;
SDL_Surface *screen; //This pointer will reference the backbuffer
 
//I have set the flag SDL_SWSURFACE for a window :)
int InitVideo(Uint32 flags = SDL_DOUBLEBUF | SDL_SWSURFACE) {
  // Load SDL
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
    return false;
  }
  atexit(SDL_Quit); // Clean it up nicely :)
 
  // fullscreen can be toggled at run time :) any you might want to change the flags with params?
  //set the main screen to SCREEN_WIDTHxSCREEN_HEIGHT with a colour depth of 16:
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 16, flags);
  if (screen == NULL) {
    fprintf(stderr, "Unable to set video mode: %s\n", SDL_GetError());
    return false;
  }
  return true;
}

//--------------------------- Drawing Stuff -------------------------
SDL_Surface* LoadImage(char *file, int &exitstate) {
  SDL_Surface *tmp;
  tmp = IMG_Load(file);
  exitstate = false;
 
  if (tmp == NULL) {
    fprintf(stderr, "Error: '%s' could not be opened: %s\n", file, IMG_GetError());
  } else {
    if(SDL_SetColorKey(tmp, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(tmp->format, COLORKEY)) == -1)
    fprintf(stderr, "Warning: colorkey will not be used, reason: %s\n", SDL_GetError());
    exitstate = true;
  }
  return tmp;
}
SDL_Surface* LoadImage(string file, int &exitstate) {
	char * path = new char[file.length()+1];
	strcpy(path,file.c_str());
	return LoadImage(path,exitstate);
}

void DrawImage(SDL_Surface *srcimg, int sx, int sy, int sw, int sh, SDL_Surface *dstimg, int dx, int dy, int alpha = 255) {
  if ((srcimg == NULL) || (alpha == 0)) return; //If theres no image, or its 100% transparent.
  SDL_Rect src, dst;
 
  src.x = sx;  src.y = sy;  src.w = sw;  src.h = sh;
  dst.x = dx;  dst.y = dy;  dst.w = src.w;  dst.h = src.h;
  if (alpha != 255) SDL_SetAlpha(srcimg, SDL_SRCALPHA, alpha);
  SDL_BlitSurface(srcimg, &src, dstimg, &dst);
}

void DrawMatrix(SDL_Surface *srcimg){
	for (int x = 0;x < (screen->w - srcimg->w);x+=srcimg->w){
		for (int y = 0;y < (screen->h - srcimg->h);y+=srcimg->h){
			DrawImage(srcimg, 0,0, srcimg->w, srcimg->h, screen, x, y, 255);
		cout << "" << x <<"."<< y;
		}
		cout << endl;
	}
}


int main() {
	kanji *k = new kanji();
//	k->setByName("hachi");
	cout << "kanji  is :" << k->name << endl << "meaning is :" << k->meaning << endl;
	string path="img/" + k->grade + "/" + k->imgfile;
	int res = 0; //Results
	if (InitVideo() == false) return 1;
	SDL_Surface *kanji = LoadImage(path,res);
	if (res == false) return 1; 
	DrawMatrix(kanji);
	SDL_Flip(screen); //Refresh the screen
	SDL_Delay(7500); //Wait a bit :)
  //cleanup
  SDL_FreeSurface(kanji);
  return 0;
}
//Remember the blank line at the end! gcc always bugs me about it :)
