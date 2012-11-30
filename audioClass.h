#ifndef AUDIOCLASS_INCLUDED
#define AUDIOCLASS_INCLUDED

/// --------- SoundAction
class SoundAction{
 private:
    int canal;
    bool ready;
    DataFile dfSound;
    Mix_Chunk *sonido;

 public:
    void loadFP(char *dir){dfSound.setFileName(dir); if(!dfSound.loadFile()) exit(87);}
    void play(int);
    void setReady(bool r){ready = r;}
    void setVolume(int v){Mix_VolumeChunk(sonido, v);}

 SoundAction(int c){ready=0;canal=c;}
};

void SoundAction::play(int ns){
 char dir[100];
    if( ready == true ){
        if( ns != 0 )
            if( Mix_Playing(canal) == 0 ){
                ready = false;
                strcpy(dir, dfSound.getDir(ns));
                if(strcmp(dir, "s") != 0){
                    sonido = Mix_LoadWAV(dir);
                    if ( sonido == NULL ) {
                        printf("No pude cargar sonido: %s\n", Mix_GetError());
                        exit(224);
                    }
                    // Reproducción del sonido.
                    // Esta función devuelve el canal por el que se reproduce el sonido
                    Mix_PlayChannel(canal, sonido, 0);
                }
            }
    }
}

#endif // AUDIOCLASS_HPP_INCLUDED
