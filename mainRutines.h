#ifndef MAINRUTINES_H_INCLUDED
#define MAINRUTINES_H_INCLUDED

void selectPJmenu(SDL_Surface *, int*, int*, int*);
int Inicializar();
int playMusic(int);
int standardEvents(SDL_Event *, SDL_Surface *);

void selectPJmenu(SDL_Surface *screen, int *iPJ1, int *iPJ2, int *iBG){
        // Declaraciones para el texto
    TTF_Font *fuente;
    Ctext msj;
    char texto[1500];

    // para el menu
    class CFrame FfondoPJ, FbigImage[CANTIDAD_DE_PJS], FsmallImage[CANTIDAD_DE_PJS],FfondoMenu, Fcursor1, Fcursor2;
    class CSprite SfondoPJ2, SfondoPJ1, SbigImage1(CANTIDAD_DE_PJS), SsmallImage(CANTIDAD_DE_PJS),SfondoMenu, Scursor1, Scursor2, BGlist;
    class DataFile dfBigImage, dfBGlist;

    class FilePlayer *fpSmallImage;
    fpSmallImage = new FilePlayer;
    if(fpSmallImage == NULL) exit(357);
    int done=0, ini, total, fin, CANTIDAD_DE_FONDOS=0,parte_menu=0, PJ2x=0, PJ2y=0, PJ1x=0, PJ1y=0, selectF, setXaxis, setYaxis, addXsprite, setXsprite, addYsprite, setYsprite, w, h, addFrameX, endFrameX, frameFijo, pos=0;

    SDL_Rect rectBG;
    rectBG.w = 221;
    rectBG.h = 452;
    rectBG.x = 0;
    rectBG.y =  0;

    // para joystick
    int joyButton=0, joyx, joyy,joyx2, joyy2;
    SDL_Joystick *joy1, *joy2;
    // Activa el Joystick
    if (SDL_NumJoysticks() >= 1) {
        joy1 = SDL_JoystickOpen(0);
        SDL_JoystickEventState(SDL_ENABLE);
        if (SDL_NumJoysticks() > 1)
            joy2 = SDL_JoystickOpen(1);
    }


    if(!(fuente = TTF_OpenFont("verdana.ttf",34))){
        printf("No se pudo abrir una fuente SDL_ttf: %s\n",SDL_GetError());
        exit(72);}
    msj.setFuente(fuente);
/// Carga sprites para menu

    if(loadImage("sprites/selectPJ_menu.PNG",&FfondoMenu, &SfondoMenu)) exit(116);
    if(loadImage("sprites/cursor.PNG",&Fcursor1, &Scursor1)) exit(117);
    if(loadImage("sprites/cursor2.PNG",&Fcursor2, &Scursor2)) exit(127);

 class player fondoPJ1(&SfondoPJ1), fondoPJ2(&SfondoPJ2), smallImage(&SsmallImage);
    if(loadImage("sprites/letras_japonesas1.PNG",&FfondoPJ, &SfondoPJ1)) exit(118);
    SfondoPJ2.addframe(&FfondoPJ);

    dfBigImage.setFileName("pjs/bigimage/bigimage.dat");
    if(!dfBigImage.loadFile()) exit(90);
    if(!loadFramesFromDF(FbigImage, &dfBigImage, CANTIDAD_DE_PJS)) exit(80);
    loadCsprites(FbigImage, &SbigImage1,CANTIDAD_DE_PJS);

    fpSmallImage->setFileName("pjs/smallimage/smallimage.dat");
    if(!fpSmallImage->loadFile()) exit(91);
    if(!loadFramesFromFP(FsmallImage, fpSmallImage, CANTIDAD_DE_PJS)) exit(80);
    loadSprites(FsmallImage, &smallImage,CANTIDAD_DE_PJS);

    Scursor1.setx(165);
    Scursor1.sety(55);
    Scursor2.setx(165);
    Scursor2.sety(55);


///-----------------------------------------------------
///              Program Main Loop                     |
///-----------------------------------------------------
    msj.text("Select Player", 180, 5);

    while (!done)
    {

        ini=ResetTimeBase(ini);

    if(parte_menu == 0){

        SDL_Event event;


        while (SDL_PollEvent(&event))
        {  // Check for messages
            SDL_JoystickUpdate();
            joyx = SDL_JoystickGetAxis(joy1, 0);
            joyy = SDL_JoystickGetAxis(joy1, 1);
            if (joyy < -10)
                if(Scursor1.gety() > 55){
                    Scursor1.addy(-75);
                    PJ1y--;}
            if (joyy > 10)
                if(Scursor1.gety() < 430){
                    Scursor1.addy(75);
                    PJ1y++;}
            if (joyx < -10)
                if(Scursor1.getx() > 165){
                    Scursor1.addx(-72);
                    PJ1x--;}
            if (joyx > 10)
                if(Scursor1.getx() < 525){
                    Scursor1.addx(72);
                    PJ1x++;}

            joyx2 = SDL_JoystickGetAxis(joy2, 0);
            joyy2 = SDL_JoystickGetAxis(joy2, 1);
            if (joyy2 < -10)
                if(Scursor2.gety() > 55){
                    Scursor2.addy(-75);
                    PJ2y--;}
            if (joyy2 > 10)
                if(Scursor2.gety() < 430){
                    Scursor2.addy(75);
                    PJ2y++;}
            if (joyx2 < -10)
                if(Scursor2.getx() > 165){
                    Scursor2.addx(-72);
                    PJ2x--;}
            if (joyx2 > 10)
                if(Scursor2.getx() < 525){
                    Scursor2.addx(72);
                    PJ2x++;}

            switch (event.type){
           // Exit if the window is closed
                case SDL_QUIT:
                    done = true;
                    break;
                case (SDL_JOYBUTTONDOWN):
                    if((SDL_JoystickGetButton(joy1, 1))||(SDL_JoystickGetButton(joy1, 2)))
                        parte_menu++;
                    break;

               // Check For Keypresses
                case SDL_KEYDOWN:{ // Exit if Esc is pressed
                    standardEvents(&event, screen);
                    switch(event.key.keysym.sym){
                        default: break;

                        case (SDLK_F4):
                            //strcpy(texto,SDL_JoystickName(0));
                            joyButton=SDL_JoystickOpened(0);
                            itoa(joyButton, texto, 10);
                            msj.text(texto, 180, 5);
                            break;

                        case (SDLK_RIGHT):
                            if(Scursor1.getx() < 525){
                                Scursor1.addx(72);
                                PJ1x++;}
                            break;
                        case (SDLK_LEFT):
                            if(Scursor1.getx() > 165){
                                Scursor1.addx(-72);
                                PJ1x--;}
                            break;
                        case (SDLK_UP):
                            if(Scursor1.gety() > 55){
                                Scursor1.addy(-75);
                                PJ1y--;}
                            break;
                        case (SDLK_DOWN):
                            if(Scursor1.gety() < 430){
                                Scursor1.addy(75);
                                PJ1y++;}
                            break;
                        case (SDLK_d):
                            if(Scursor2.getx() < 525){
                                Scursor2.addx(72);
                                PJ2x++;}
                            break;
                        case (SDLK_a):
                            if(Scursor2.getx() > 165){
                                Scursor2.addx(-72);
                                PJ2x--;}
                            break;
                        case (SDLK_w):
                            if(Scursor2.gety() > 55){
                                Scursor2.addy(-75);
                                PJ2y--;}
                            break;
                        case (SDLK_s):
                            if(Scursor2.gety() < 430){
                                Scursor2.addy(75);
                                PJ2y++;}
                            break;
                        case (SDLK_RETURN):
                        case (SDLK_KP_ENTER):
                            parte_menu++;
                            break;
                    }
                    break;
                }
            } // End Switch
            *iPJ1 = PJ1x +(PJ1y*5);
            *iPJ2 = PJ2x +(PJ2y*5);
        } // End of Message Processing
///------------------------------Select players menu-----------------------------------------

    ///Animaciones
        fondoPJ1.fullAction(0, 0, 0, 0, 5, 0, 335, 175, 250, 10, 1014, 0);
        fondoPJ2.fullAction(0, 0, 0, 0, 620, 0, 335, 175, 250, 10, 1014, 0);

        SbigImage1.sety(335);

    /// DRAWING STARTS HERE
        // Clear Screen
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
		SfondoMenu.draw(screen);// Draw the Background

        SfondoPJ1.draw(screen,&fondoPJ1.rectFrame);
        SfondoPJ2.draw(screen,&fondoPJ2.rectFrame);

        SbigImage1.selframe(*iPJ1);
        SbigImage1.setx(5);
        SbigImage1.draw(screen);
        SbigImage1.selframe(*iPJ2);
        SbigImage1.setx(620);
        SbigImage1.draw(screen);

        while( strcmp( fpSmallImage->getDirFrame(pos), "a" ) != 0 ){
            fpSmallImage->getInstances(pos, &selectF, &setXaxis, &setYaxis, &addXsprite, &setXsprite, &addYsprite, &setYsprite, &w, &h, &addFrameX, &endFrameX, &frameFijo);
            smallImage.fullAction(selectF, setXaxis, setYaxis, addXsprite, setXsprite, addYsprite, setYsprite, w, h, addFrameX, endFrameX, frameFijo);
            smallImage.spritePJ->draw(screen,&smallImage.rectFrame);
            pos++;
        }
        pos = 0;

        Scursor1.draw(screen);
        Scursor2.draw(screen);

        msj.showText(screen);
    /// DRAWING ENDS HERE
    ///--------------------------END Select playter menu---------------------------------------
    }
    if(parte_menu == 1){

        fpSmallImage->~FilePlayer();
        delete(fpSmallImage);
        fondoPJ1.~player();
        fondoPJ2.~player();
    /// Carga sprites para menu2

        SfondoMenu.resetS();
        Scursor1.resetS();
        BGlist.resetS();
        if(loadImage("sprites/selectBG_menu2.PNG",&FfondoMenu, &SfondoMenu)) exit(116);
        if(loadImage("sprites/selectBG_menu3.PNG",&Fcursor1, &Scursor1)) exit(121);
        if(loadImage("PJs/BGlist/BGlist.PNG",&Fcursor2, &BGlist)) exit(122);

        BGlist.setx(300);
        BGlist.sety(73);//223

        msj.text("Select Background", 180, 5);

        parte_menu = 2;

        dfBGlist.setFileName("pjs/BGlist/BGlist.dat");
        if(!dfBGlist.loadFile()) exit(95);
        while( strcmp( dfBGlist.getDir(CANTIDAD_DE_FONDOS), "a") != 0 )
            CANTIDAD_DE_FONDOS++;
        CANTIDAD_DE_FONDOS--;   // cada vez q agreges un fondo a la lista en el BGlist.dat aca se reconocera automaticamente
        *iBG = 1;
    }
    ///-------------------------- Select Background menu --------------------------------------
    if(parte_menu == 2){

        SDL_Event event;
        SDL_JoystickUpdate();

        while (SDL_PollEvent(&event))
        {  // Check for messages

            joyx = SDL_JoystickGetAxis(joy1, 0);
            joyy = SDL_JoystickGetAxis(joy1, 1);
			if (joyy < -10)
                if(*iBG < CANTIDAD_DE_FONDOS){
                    //BGlist.addy(-150);
                    rectBG.y += 150;
                    *iBG = *iBG + 1;
                }
			if (joyy > 10)
                if(*iBG > 0){
                    //BGlist.addy(150);
                    rectBG.y -= 150;
                    *iBG = *iBG - 1;
                }

            switch (event.type){
           // Exit if the window is closed
                case SDL_QUIT:
                    done = true;
                    break;

                case (SDL_JOYBUTTONDOWN):
                    if((SDL_JoystickGetButton(joy1, 1))||(SDL_JoystickGetButton(joy1, 2)))
                        parte_menu++;
                    break;
               // Check For Keypresses
                case SDL_KEYDOWN:{ // Exit if Esc is pressed
                    standardEvents(&event, screen);
                    switch(event.key.keysym.sym){
                        default: break;
                        case (SDLK_UP):
                            if(*iBG < CANTIDAD_DE_FONDOS){
                                //BGlist.addy(-150);
                                rectBG.y += 150;
                                *iBG = *iBG + 1;
                            }
                            break;
                        case (SDLK_DOWN):
                            if(*iBG > 0){
                                //BGlist.addy(150);
                                rectBG.y -= 150;
                                *iBG = *iBG - 1;
                            }
                            break;
                        case (SDLK_RETURN):
                        case (SDLK_KP_ENTER):
                            parte_menu++;
                            break;
                    }
                }
            }
        }


        Scursor1.setx(216);
        Scursor1.sety(73);

        /// DRAWING STARTS HERE
        // Clear Screen
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
		SfondoMenu.draw(screen);// Draw the Background 1
		BGlist.draw(screen, &rectBG);
		Scursor1.draw(screen);


        msj.showText(screen);

    }
    ///----------------------------------------------------------------------------------------
    if(parte_menu == 3) done = 1;

        // Update the screen ^_^
        SDL_Flip(screen);

        do{total=CurrentTime(fin,ini);}
        while(total<80);
    }
}
int Inicializar(){

    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0 ){
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        exit(111);}
    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

        // Inicializamos SDL_ttf
    if (TTF_Init() < 0){
        printf("No se pudo iniciar SDL_ttf: %s\n",SDL_GetError());
        return 1;}
    atexit(TTF_Quit);

        // Inicializamos SDL_mixer
    if(Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 4096)) {
        printf("No se puede inicializar SDL_mixer %s\n",Mix_GetError());
        exit(1);}
    atexit(Mix_CloseAudio);
    // Fin de inicialisaciones
    Mix_AllocateChannels(2);

        // load the image Icon
 class CFrame Fdefault;
 class CSprite Sdefault;
    if(loadImage("sprites/icono.gif",&Fdefault, &Sdefault) == 1) return 15;
    SDL_WM_SetCaption("Anime Fight", 0);
    SDL_WM_SetIcon(Fdefault.img, 0);
    Sdefault.finalize();
}
int playMusic(int nTrack){
 class DataFile dfMusic;

         // Cargamos listado
    dfMusic.setFileName("pjs/Music/Music.dat");
    if(!dfMusic.loadFile()) exit(89);

    if(nTrack == -1){
        int TOTAL_TRACKS = 0;
        while( strcmp( dfMusic.getDir(TOTAL_TRACKS), "s") != 0 )
                TOTAL_TRACKS++;// cada vez q agreges un tema a la lista en el music.dat aca se reconocera automaticamente
        return TOTAL_TRACKS;
    }else{
        Mix_Music *music;
        music = Mix_LoadMUS(dfMusic.getDir(nTrack));
        if ( music == NULL ) {
            printf("No pude cargar Track: %s\n", Mix_GetError());
            exit(221);
        }
        // Reproducción del sonido.
        // Esta función devuelve el canal por el que se reproduce el sonido
        //canal = Mix_PlayChannel(-1, sonido, 0);
        //Mix_VolumeMusic(volume);

        dfMusic.~DataFile();
        return Mix_PlayMusic(music, -1);
    }
    dfMusic.~DataFile();
}

void main_menu(SDL_Surface *screen, TTF_Font *fuente){
 class CFrame fFondo, fOption1[2], fOption2[2], fOption3[2], fLife[2], fSpeed[2], fMvolume[2], fBack[2];
 class CSprite sFondo, sOption1(2), sOption2(2), sOption3(2), sLife(2), sSpeed(2), sMvolume(2), sBack(2);
 class Ctext txtLife, txtSpeed, txtMvolume;
 class KeysFile kfConfig;
 char chLife[3], chSpeed[3], chMvolume[3];
 bool done=0, menu_config = 0;
 int opc = 1,ultimaOpcion = 3;

    kfConfig.setFileName("config.dat");
    if(!kfConfig.loadFile()) exit(423);
    itoa( kfConfig.getLife(), chLife, 10);
    itoa( kfConfig.getSpeed(), chSpeed, 10);
    itoa( kfConfig.getMvolume(), chMvolume, 10);

    txtLife.setFuente(fuente);
    txtSpeed.setFuente(fuente);
    txtMvolume.setFuente(fuente);
    txtLife.text("", 0, -50);
    txtSpeed.text("", 0, -50);
    txtMvolume.text("", 0, -50);

    fOption1[0].load("sprites/Play0.png");
        if (!fOption1[0].img){printf("Unable to load image: %s\n", SDL_GetError());            exit(71);}
    fOption1[1].load("sprites/Play1.png");
        if (!fOption1[1].img){printf("Unable to load image: %s\n", SDL_GetError());            exit(71);}
    fOption2[0].load("sprites/Config0.png");
        if (!fOption2[0].img){printf("Unable to load image: %s\n", SDL_GetError());            exit(71);}
    fOption2[1].load("sprites/Config1.png");
        if (!fOption2[1].img){printf("Unable to load image: %s\n", SDL_GetError());            exit(71);}
    fOption3[0].load("sprites/Exit0.png");
        if (!fOption3[0].img){printf("Unable to load image: %s\n", SDL_GetError());            exit(71);}
    fOption3[1].load("sprites/Exit1.png");
        if (!fOption3[1].img){printf("Unable to load image: %s\n", SDL_GetError());            exit(71);}
    fLife[0].load("sprites/Life0.png");
        if (!fLife[0].img){printf("Unable to load image: %s\n", SDL_GetError());            exit(71);}
    fLife[1].load("sprites/Life1.png");
        if (!fLife[1].img){printf("Unable to load image: %s\n", SDL_GetError());            exit(71);}
    fSpeed[0].load("sprites/Speed0.png");
        if (!fSpeed[0].img){printf("Unable to load image: %s\n", SDL_GetError());            exit(71);}
    fSpeed[1].load("sprites/Speed1.png");
        if (!fSpeed[1].img){printf("Unable to load image: %s\n", SDL_GetError());            exit(71);}
    fMvolume[0].load("sprites/MusicVol0.png");
        if (!fMvolume[0].img){printf("Unable to load image: %s\n", SDL_GetError());            exit(71);}
    fMvolume[1].load("sprites/MusicVol1.png");
        if (!fMvolume[1].img){printf("Unable to load image: %s\n", SDL_GetError());            exit(71);}
    fBack[0].load("sprites/Back0.png");
        if (!fBack[0].img){printf("Unable to load image: %s\n", SDL_GetError());            exit(71);}
    fBack[1].load("sprites/Back1.png");
        if (!fBack[1].img){printf("Unable to load image: %s\n", SDL_GetError());            exit(71);}

    loadCsprites(fOption1,&sOption1, 2);
    loadCsprites(fOption2,&sOption2, 2);
    loadCsprites(fOption3,&sOption3, 2);
    loadCsprites(fLife,&sLife, 2);
    loadCsprites(fSpeed,&sSpeed, 2);
    loadCsprites(fMvolume,&sMvolume, 2);
    loadCsprites(fBack,&sBack, 2);

    loadImage("sprites/menu_blue-ichigo2.png", &fFondo, &sFondo);

    sFondo.setx(-380);
    sOption1.setx(30);
    sOption1.sety(250);
    sOption2.setx(50);
    sOption2.sety(360);
    sOption3.setx(145);
    sOption3.sety(475);

    sLife.setx(720);
    sLife.sety(610);
    sSpeed.setx(760);
    sSpeed.sety(710);
    sMvolume.setx(780);
    sMvolume.sety(810);
    sBack.setx(1000);
    sBack.sety(960);
    while(done == false){

    SDL_Event event;
    while (SDL_PollEvent(&event))
        {  // Check for messages
            switch (event.type)
            {
           // Exit if the window is closed
            case SDL_QUIT:
                done = true;
                break;

          /*  case SDL_JOYBUTTONDOWN:

                break;*/

           // Check For Keypresses
            case SDL_KEYDOWN:
                { // Exit if Esc is pressed
                    standardEvents(&event, screen);

                    switch(event.key.keysym.sym){
                        default: break;
                        case (SDLK_UP):
                            if(opc == 1)
                                opc = ultimaOpcion;
                            else
                                opc--;
                            break;
                        case (SDLK_DOWN):
                            if(opc == ultimaOpcion)
                                opc = 1;
                            else
                                opc++;
                            break;
                        case (SDLK_RETURN):
                        case (SDLK_KP_ENTER):
                            if ( menu_config == false ){
                                if(opc == 1) done=true;
                                if(opc == 2) menu_config = true;
                                if(opc == 3) exit(1);
                            }else{
                                if(opc == 1) strcpy(chLife, kfConfig.modLife());
                                if(opc == 2) strcpy(chSpeed, kfConfig.modSpeed());
                                if(opc == 3){ strcpy(chMvolume, kfConfig.modMvolume()); Mix_VolumeMusic(kfConfig.getMvolume());}
                                if(opc == 4) menu_config = false;
                            }
                            break;
                    }
                }
            } // End Switch
        } // End of Message Processing

    /// Animations

    if ( menu_config == true ){
        if(sFondo.getx() != 0){
            sFondo.addx(10);
            sOption1.addx(30);
            sOption1.addy(30);
            sOption2.addx(30);
            sOption2.addy(30);
            sOption3.addx(30);
            sOption3.addy(30);
        }else
            if( sLife.gety() != 100 ){
                sLife.addx( -30 );
                sLife.addy( -30 );
                sSpeed.addx( -30 );
                sSpeed.addy( -30 );
                sMvolume.addx( -30 );
                sMvolume.addy( -30 );
                sBack.addx( -30 );
                sBack.addy( -30 );
                if(sLife.gety() == 100){
                    txtLife.text(chLife, 345, 102);
                    txtSpeed.text(chSpeed, 465, 202);
                    txtMvolume.text(chMvolume, 580, 302);
                }
                ultimaOpcion = 4;
                opc = 1;
            }
            if(opc == 1) sLife.selframe(1);
            else  sLife.selframe(0);
            if(opc == 2) sSpeed.selframe(1);
            else  sSpeed.selframe(0);
            if(opc == 3) sMvolume.selframe(1);
            else  sMvolume.selframe(0);
            if(opc == 4) sBack.selframe(1);
            else  sBack.selframe(0);

    }else{
        if( sFondo.getx() != (-380) ){
            sFondo.addx(-10);
            sOption1.addx(-30);
            sOption1.addy(-30);
            sOption2.addx(-30);
            sOption2.addy(-30);
            sOption3.addx(-30);
            sOption3.addy(-30);
            opc = 1;
            ultimaOpcion = 3;


            if( sLife.gety() != 720 ){
                if(sLife.gety() == 100){
                    txtLife.text("", 0, -50);
                    txtSpeed.text("", 0, -50);
                    txtMvolume.text("", 0, -50);
                    opc = 1;
                }
                sLife.addx( 30 );
                sLife.addy( 30 );
                sSpeed.addx( 30 );
                sSpeed.addy( 30 );
                sMvolume.addx( 30 );
                sMvolume.addy( 30 );
                sBack.addx( 30 );
                sBack.addy( 30 );

                ultimaOpcion = 3;

            }
        }

        if(opc == 1) sOption1.selframe(1);
        else  sOption1.selframe(0);
        if(opc == 2) sOption2.selframe(1);
        else  sOption2.selframe(0);
        if(opc == 3) sOption3.selframe(1);
        else  sOption3.selframe(0);
    }

    /// DRAWING STARTS HERE
        // Clear Screen
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
		sFondo.draw(screen);// Draw the Background
        sOption1.draw(screen);
        sOption2.draw(screen);
        sOption3.draw(screen);

        sLife.draw(screen);
        sSpeed.draw(screen);
        sMvolume.draw(screen);
        sBack.draw(screen);

        txtLife.showText(screen);
        txtSpeed.showText(screen);
        txtMvolume.showText(screen);

    /// DRAWING ENDS HERE
        // Update the screen ^_^
        SDL_Flip(screen);

    }
}

int standardEvents(SDL_Event *event, SDL_Surface *screen){
int volume = Mix_VolumeMusic(-1);

    switch(event->key.keysym.sym){
        default: break;
        case (SDLK_ESCAPE):
            exit(0);
            break;

        case (SDLK_F11):
            screen = SDL_SetVideoMode(800, 600, 32,
                               SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
            break;
        case (SDLK_F12):
            screen = SDL_SetVideoMode(800, 600, 32,
                               SDL_HWSURFACE|SDL_DOUBLEBUF);
            break;
        case (SDLK_F5):
            Mix_PauseMusic();
            break;

        case (SDLK_F6):
            Mix_ResumeMusic();
            break;

        case (SDLK_F9):
            if(volume > 0)
                Mix_VolumeMusic(volume-=16);
            break;

        case (SDLK_F10):
            if(volume < 128)
                Mix_VolumeMusic(volume+=16);
            break;

    }
}
#endif // MAINRUTINES_H_INCLUDED
