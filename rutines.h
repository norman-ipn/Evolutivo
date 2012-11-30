#ifndef RUTINES_H_INCLUDED
#define RUTINES_H_INCLUDED

///FUNCIONES///
int loadImage(char*,class CFrame*,class CSprite*,int);
int loadFramesFromFP(class CFrame*, class FilePlayer*,int);
void loadSprites(class CFrame*,class player*,int);
int loadFrameFromDF(int,char*,class CFrame*,class CSprite*,int);

///*****************************************************
///                 Funciones y rutinas                *
///*****************************************************

int loadImage(char * dir, CFrame *Fimage, CSprite *Simage){
	Fimage->load(dir);
	    if (!Fimage->img){
	        printf("Unable to load image: %s\n", SDL_GetError());	// los errores se guardan en un archivo txt junto al programa
	        return 13;
		}
	Simage->addframe((Fimage));
	Simage->setx(0);
	Simage->sety(0);
    return 0;
}
int loadImageRGB(char *dir, int r, int g, int b, CFrame *Fimage, CSprite *Simage){
	Fimage->load(dir,r,g,b);
	    if (!Fimage->img){
	        printf("Unable to load image: %s\n", SDL_GetError());	// los errores se guardan en un archivo txt junto al programa
	        return 13;
		}
	Simage->addframe((Fimage));
	Simage->setx(0);
	Simage->sety(0);
    return 0;
}
int loadFramesFromFP(CFrame *Frames, FilePlayer *fp, int total){
	for(int i=0; i<total; i++){
        Frames[i].load(fp->getDirFrame(i));
            if (!Frames[i].img){
                printf("Unable to load image: %s\n", SDL_GetError());	// los errores se guardan en un archivo txt junto al programa
                return 99;
            }
	}
    return 1;
}

int loadFramesFromDF(CFrame *Frames, DataFile *df, int total){
	for(int i=0; i<total; i++){
    Frames[i].load(df->getDir(i));
        if (!Frames[i].img){
            printf("Unable to load image: %s\n", SDL_GetError());	// los errores se guardan en un archivo txt junto al programa
            return 99;
        }
	}
    return 1;
}
int loadFrameFromDF(int i, char *dir, CFrame *Frame,CSprite *sprite){
class DataFile df;

    df.setFileName(dir);
    if(!df.loadFile()) exit(93);

    Frame->load(df.getDir(i));
    if (!Frame->img){
        printf("Unable to load image: %s\n", SDL_GetError());
        exit(94);
    }
    sprite->addframe((Frame));
    df.~DataFile();
    return 1;
}

void loadSprites(CFrame *Frames,player *playerX, int total){
    for(int i=0; i < total; i++)
        playerX->spritePJ->addframe((Frames)+i);
}
void loadCsprites(CFrame *Frames,CSprite *sprite, int total){
    for(int i=0; i < total; i++)
        sprite->addframe((Frames)+i);
}
void resetSprites(CSprite *sprite, int total){
    for(int i=0; i < total; i++)
        sprite->resetS();
}
#endif // RUTINES_H_INCLUDED
