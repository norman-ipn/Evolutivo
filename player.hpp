#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED /// version 0.9

/// Player Class Declaration
class player{
 private: // Main Variables
    SDL_Rect rectColision;
    int estadoActual; // State indicator - Switch in game Loop
    int estadoAnterior;
    bool saltoAvance;
    int cicloSalto;
    int cicloComienzo;
    bool direccion;// Side Facing Variable
    int contFrame;
    int axisXanterior;
    int axisYanterior;
    int Xanterior;
    int Yanterior;
    bool reset;

 public: // Main Functions
    // Constructor, Sets everythin in 0
 player(CSprite *sprite){spritePJ= sprite; estadoActual=estadoAnterior=saltoAvance=cicloComienzo=cicloSalto=direccion=contFrame=rectFrame.x=reset = 0;}
 ~player(){}
    class CSprite *spritePJ;

    SDL_Rect rectFrame, rectPosicion;
    struct MantieneEstado{
        bool mantieneEstado;
        int nEstado;
    }est;
    int pjAction( Life*, SDL_Joystick*, Uint8*, player*, FilePlayer *, FilePlayer*, KeysFile*);
    int getContFrame(){return contFrame;}
    void subContFrame(){contFrame--;}
    void posicionIni(bool dir, int x, int y);
    void Direccion(bool x){direccion=x;}
    bool Direccion(){return direccion;}
    void accion(int x){estadoActual=x;}
    bool colision(SDL_Rect*, SDL_Rect*, CSprite, CSprite);
    void guardarEstado(){estadoAnterior = estadoActual;}
    void guardarXY(){Xanterior=spritePJ->getx();Yanterior=spritePJ->gety();}
    void restaurarXY(int);
    int getEstadoActual(){return estadoActual;}
    int getEstadoAnterior(){return estadoAnterior;}
    bool mismoEstado(){if(estadoAnterior != estadoActual){
        rectFrame.x = 0;
        contFrame = 0;
        cicloSalto = 0;
        cicloComienzo = 0;
        return false;}
        return true;}
    bool fullAction(int, int, int, int, int, int, int, int, int, int, int, int);
    int saltar(class FilePlayer*);
    bool descender(FilePlayer*);
    bool machineStates(class FilePlayer*);
    bool colition(ColitionRect cr1,ColitionRect cr2);
    bool colitionSystem(FilePlayer*,FilePlayer*,player*);
    bool colitionSystem2(FilePlayer*,FilePlayer*,player*);
    bool blueColition(FilePlayer*,FilePlayer*,player*);
    void error(int);

};
/// Player Class Implementation
void player::restaurarXY(int posP2){
 int posP1 = spritePJ->getx();

    if(posP2 == -1)
        spritePJ->setx(Xanterior);
    else
        if(posP1 < posP2)
            spritePJ->addx(-2);
        else
            spritePJ->addx(2);
}
bool player::colition(ColitionRect cr1, ColitionRect cr2){
    int w1,h1,w2,h2,x1,y1,x2,y2;
	w1 = cr1.w;			// Colition Rect1 Width
	h1 = cr1.h;			// Colition Rect1 Height
	w2 = cr2.w;		   // Colition Rect2 Width
	h2 = cr2.h;		   // Colition Rect2 Height
	x1 = cr1.x;			// X position of Colition Rect1
	y1 = cr1.y;			// Y position of Colition Rect1
	x2 = cr2.x;		   // X position of Colition Rect2
	y2 = cr2.y;		   // Y position of Colition Rect2
	if (((x1+w1)>x2)&&((y1+h1)>y2)&&((x2+w2)>x1)&&((y2+h2)>y1))
        return true;
    else
        return false;
}
bool player::blueColition(FilePlayer *fp1, FilePlayer *fp2, player *p2){
int s1, f1, rV, rV2, s2, f2, x1, y1, x2, y2;

ColitionRect CR1, CR2;
 s1 = spritePJ->getEstado();
 x1 = spritePJ->getx();
 y1 = spritePJ->gety();
 f1 = contFrame;

 s2 = p2->spritePJ->getEstado();
 x2 = p2->spritePJ->getx();
 y2 = p2->spritePJ->gety();
 f2 = p2->getContFrame();


    for(rV=0; rV < 6; rV++)
        for(rV2=0; rV2 < 6; rV2++){
            fp1->getCRv(s1,f1,rV, &CR1);
            fp2->getCRv(s2,f2,rV2, &CR2);

            if((CR1.activo)&&(CR2.activo)){

                CR1.x += x1;
                CR1.y += y1;

                CR2.x += x2;
                CR2.y += y2;
                if(colition(CR1, CR2)) return true;
            }
        }
    return false;
}

bool player::colitionSystem2(FilePlayer *fp1, FilePlayer *fp2, player *p2){
int s1, f1, rV, rA, s2, f2, x1, y1, x2, y2;

ColitionRect CR1, CR2;
 s1 = spritePJ->getEstado();
 x1 = spritePJ->getx();
 y1 = spritePJ->gety();
 f1 = contFrame;

 s2 = p2->spritePJ->getEstado();
 x2 = p2->spritePJ->getx();
 y2 = p2->spritePJ->gety();
 f2 = p2->getContFrame();


    for(rV=0; rV < 6; rV++)
        for(rA=0; rA < 6; rA++){
            fp1->getCRv(s1,f1,rV, &CR1);
            fp2->getCRa(s2,f2,rA, &CR2);

            if((CR1.activo)&&(CR2.activo)){

                CR1.x += x1;
                CR1.y += y1;

                CR2.x += x2;
                CR2.y += y2;
                if(colition(CR1, CR2)) return true;
            }
        }
    return false;
}
bool player::colitionSystem(FilePlayer *fp1, FilePlayer *fp2, player *p2){
int s1, f1, rV, rA, s2, f2, x1, y1, x2, y2, i1,i2;

ColitionRect *CRv, *CRa, CR1, CR2;
 s1 = spritePJ->getEstado();
 x1 = spritePJ->getx();
 y1 = spritePJ->gety();
 f1 = contFrame;
 CRv = fp1->getCRv(s1);

 s2 = p2->spritePJ->getEstado();
 x2 = p2->spritePJ->getx();
 y2 = p2->spritePJ->gety();
 f2 = p2->getContFrame();
 CRa = fp2->getCRa(s2);

    for(rV=0; rV < 6; rV++)
        for(rA=0; rA < 6; rA++){
            i1 = f1*rV;
            i2 = f2*rA;
            if(( (((CRv)+f1)+rV)->activo)&&((((CRa)+f2)+rA)->activo)){



                CR1.x = (((CRv)+f1)+rV)->x + x1;
                CR1.y = (((CRv)+f1)+rV)->y + y1;
                CR1.w = (((CRv)+f1)+rV)->w;
                CR1.h = (((CRv)+f1)+rV)->h;

                CR2.x = (((CRa)+f2)+rA)->x + x2;
                CR2.y = (((CRa)+f2)+rA)->y + y2;
                CR2.w = (((CRa)+f2)+rA)->w;
                CR2.h = (((CRa)+f2)+rA)->h;

                if(colition(CR1, CR2)) return true;
            }
        }
    return false;
}
/// finalFullAction
bool player::fullAction(int selectF, int setXaxis, int setYaxis, int addXsprite, int setXsprite, int addYsprite, int setYsprite, int w, int h, int addFrameX, int endFrameX, int frameFijo){
    if(reset){
        rectFrame.x = 0;
        contFrame = 0;
        reset = false;
    }
    if(mismoEstado() == false){
        //spritePJ->setx(spritePJ->getx() + (setXaxis - axisXanterior));
        spritePJ->setx((spritePJ->getx() - setXaxis) + axisXanterior);
        spritePJ->sety((spritePJ->gety() - setYaxis) + axisYanterior);
        axisXanterior=setXaxis;
        axisYanterior=setYaxis;
    }
    if(setYsprite == 0)
        spritePJ->addy(addYsprite);
    else
        spritePJ->sety(setYsprite);
    if(setXsprite == 0)
        spritePJ->addx(addXsprite);
    else
        spritePJ->setx(setXsprite);
    if(((addYsprite != 0)&&(setYsprite != 0))||((addXsprite != 0)&&(setXsprite != 0)))
        error(selectF);

    spritePJ->selframe(selectF);
    rectFrame.h = h;
    rectFrame.w = w;
    if(rectFrame.x >= endFrameX){
        reset = true;
        //rectFrame.x = 0;
        //contFrame = 0;
        //spritePJ->sety(600 - h - 5);//resolucion(altura) - alturaPJ - distancia del piso
        return 0; //finalizo la animacion o accion (flag desactivada)
    }else
        if(frameFijo==false){
            contFrame++;
            rectFrame.x += addFrameX;
        }else{
            contFrame = frameFijo - 1;
            rectFrame.x = addFrameX;
            return 0;
        }
    return 1; //todavia no finalizo la animacion o accion (flag activa)
}

void player::posicionIni(bool dir, int x, int y)
{
    rectFrame.w = 100;
    rectFrame.h = 110;
    rectFrame.x=0;
    rectFrame.y=0;
    direccion=dir;
    spritePJ->sety(y); // posicionamos al pj Ichigo en un costado de la pantalla
    spritePJ->setx(x);
}
int player::saltar(FilePlayer *fp){
int selectF, setXaxis, setYaxis, addXsprite, setXsprite, addYsprite, setYsprite, w, h, addFrameX, endFrameX, frameFijo;

    cicloSalto++;

    /// salto con avance
    if(estadoAnterior == 1)
        saltoAvance=true; // el saltoAvance se desactiva al final de la funcion descender()

    if(saltoAvance==true)
        if(direccion==0)
            spritePJ->addx(+10);
        else
            spritePJ->addx(-10);
    ///

    if(cicloSalto < (cicloComienzo+5))
        fp->getInstances(6 +Direccion(), &selectF, &setXaxis, &setYaxis, &addXsprite, &setXsprite, &addYsprite, &setYsprite, &w, &h, &addFrameX, &endFrameX, &frameFijo);
    else
        if(cicloSalto < (cicloComienzo+10)){
            fp->getInstances(8 +Direccion(), &selectF, &setXaxis, &setYaxis, &addXsprite, &setXsprite, &addYsprite, &setYsprite, &w, &h, &addFrameX, &endFrameX, &frameFijo);
        }else{
            //if(cicloSalto < (cicloComienzo+20))
                return descender(fp);//fp->getInstances(10 +Direccion(), &selectF, &setXaxis, &setYaxis, &addXsprite, &setXsprite, &addYsprite, &setYsprite, &w, &h, &addFrameX, &endFrameX, &frameFijo);
/*
            if(spritePJ->gety() > 420){
                saltoAvance = false;
                cicloComienzo = 0;
                cicloSalto = 0;
                fullAction(selectF, setXaxis, setYaxis, addXsprite, setXsprite, addYsprite, setYsprite, w, h, addFrameX, endFrameX, frameFijo);
                return 0;
            }
     */   }
    fullAction(selectF, setXaxis, setYaxis, addXsprite, setXsprite, addYsprite, setYsprite, w, h, addFrameX, endFrameX, frameFijo);
    return 1;
}
bool player::descender(FilePlayer *fp){
int selectF, setXaxis, setYaxis, addXsprite, setXsprite, addYsprite, setYsprite, w, h, addFrameX, endFrameX, frameFijo;

    fp->getInstances(10 +Direccion(), &selectF, &setXaxis, &setYaxis, &addXsprite, &setXsprite, &addYsprite, &setYsprite, &w, &h, &addFrameX, &endFrameX, &frameFijo);
    if(spritePJ->gety() > 420){
        saltoAvance = false;
        cicloComienzo = 0;
        cicloSalto = 0;
        fullAction(selectF, setXaxis, setYaxis, addXsprite, setXsprite, addYsprite, setYsprite, w, h, addFrameX, endFrameX, frameFijo);
        return 0;
    }
    fullAction(selectF, setXaxis, setYaxis, addXsprite, setXsprite, addYsprite, setYsprite, w, h, addFrameX, endFrameX, frameFijo);
    return 1;
}
bool player::machineStates(FilePlayer *fp){
//final fullAction(selectF, setXaxis, setYaxis, addXsprite, setXsprite, addYsprite, setYsprite, w, h, addFrameX, endFrameX, bool frameFijo){
//7     fullAction(selectF, movXsprite,             movYsprite,             w, h, addFrameX, endFrameX){
//8     fullAction(selectF, movXsprite,             addYsprite,             w, h, addFrameX, endFrameX, bool frameFijo){
//9     fullAction(selectF, movXsprite,                         setYsprite, w, h, addFrameX, endFrameX, bool *flag, bool frameFijo){
int e, i, selectF, setXaxis, setYaxis, addXsprite, setXsprite, addYsprite, setYsprite, w, h, addFrameX, endFrameX, frameFijo;
 h = 110;
 i = getEstadoActual() * 2 + Direccion();
 e = (getEstadoActual() - 3 ) * 2 + 10 + Direccion();
 fp->getInstances(i, &selectF, &setXaxis, &setYaxis, &addXsprite, &setXsprite, &addYsprite, &setYsprite, &w, &h, &addFrameX, &endFrameX, &frameFijo);
    switch(getEstadoActual()){
        case 17:
            est.mantieneEstado = descender(fp);
            if(est.mantieneEstado == 0)
                return 1;
            else
                est.nEstado = getEstadoActual();
            return 0;
            break;
        case 3:
            est.mantieneEstado = saltar(fp);
            if(est.mantieneEstado == 0)
                return 1;
            else
                est.nEstado = getEstadoActual();
            return 0;
            break;
        case 0:    //de pie para los 2 lados
        case 1:
        case 2:
            fullAction(selectF, setXaxis, setYaxis, addXsprite, setXsprite, addYsprite, setYsprite, w, h, addFrameX, endFrameX, frameFijo);
            return 0;
            break;
        default:
            fp->getInstances(e, &selectF, &setXaxis, &setYaxis, &addXsprite, &setXsprite, &addYsprite, &setYsprite, &w, &h, &addFrameX, &endFrameX, &frameFijo);
            break;
    }
    est.mantieneEstado = (fullAction(selectF, setXaxis, setYaxis, addXsprite, setXsprite, addYsprite, setYsprite, w, h, addFrameX, endFrameX, frameFijo));
    if(est.mantieneEstado == 0)
        return 1;
    else
        est.nEstado = getEstadoActual();

    return 0;
}
void player::error(int selectF){
        char msjError[100];
        char valor[9];
        strcpy(msjError, "Se le dieron valores a \"setYsprite\" y \"movYsprite\" o a \"setXsprite\" y \"movXsprite\" en el sprite # ");
        itoa(selectF, valor, 10);// combierte int a char
        strcat(msjError, valor);
        strcat(msjError, ", lo cual no esta permitido.\n");
        printf(msjError, SDL_GetError());
        exit(887);
}

int player::pjAction( Life *life1, SDL_Joystick *joy, Uint8 *keys, player *p2, FilePlayer *fp2, FilePlayer *fp1, KeysFile *kf){
 int joyButton, joyx, joyy;

            /// Joystick
            joyButton = 0;
        if (SDL_NumJoysticks() >= 1) {
            joyx = SDL_JoystickGetAxis(joy, 0);
            joyy = SDL_JoystickGetAxis(joy, 1);

            if (joyy > 10) joyButton = 2;
            if (joyx < -10)
                if(spritePJ->getx() > 0){
                    joyButton = 1;
                    Direccion(1);}
            if (joyx > 10)
                if(spritePJ->getx() < 700){
                    joyButton = 1;
                    Direccion(0);}

        if(est.mantieneEstado == true){
            if(est.nEstado == 3) // air attacks
                if(SDL_JoystickGetButton(joy, 2))
                    est.nEstado = 16;
        }else{
            if(SDL_JoystickGetButton(joy, 2))
                if(getEstadoActual() == 2)
                    joyButton = 11;
                else
                    joyButton = 4;
            if(SDL_JoystickGetButton(joy, 1))
                if(getEstadoActual() == 2)
                    joyButton = (14);
                else
                    joyButton = (5);
            if(SDL_JoystickGetButton(joy, 3))
                if(getEstadoActual() == 2)
                    joyButton = (15);
                else
                    joyButton = (6);
            if(SDL_JoystickGetButton(joy, 0))
                if(getEstadoActual() == 2)
                    joyButton = (13);
                else
                    joyButton = (12);
            if(SDL_JoystickGetButton(joy, 7))
                if(joyButton == 2)
                    joyButton = 10;
                else
                    joyButton = 9;

            if (joyy < -10)
                if(joyButton == 1){
                    accion(joyButton);
                    guardarEstado();
                    joyButton = (3);}
                else
                    joyButton = (3);
        }
    }
            /// Joystick end
        accion(joyButton);

        if (keys[kf->getDOWN()]){accion(2);}
        if ((keys[kf->getLEFT()]) && (spritePJ->getx() > 0)){accion(1);Direccion(1);}
        if ((keys[kf->getRIGHT()]) && (spritePJ->getx() < 700)){accion(1);Direccion(0);}

        if(est.mantieneEstado == true){
            if(est.nEstado == 3){ // air attacks
                if (keys[kf->getBUTTON0()])
                    est.nEstado = 16;
            }
        }else{
            if (keys[kf->getBUTTON0()])
                if(getEstadoActual() == 2)
                    accion(11);
                else
                    accion(4);
            if (keys[kf->getBUTTON1()])
                if(getEstadoActual() == 2)
                    accion(14);
                else
                    accion(5);
            if (keys[kf->getBUTTON2()])
                if(getEstadoActual() == 2)
                    accion(15);
                else
                    accion(6);
            if (keys[kf->getBUTTON3()])
                if(getEstadoActual() == 2)
                    accion(13);
                else
                    accion(12);
            if (keys[kf->getBUTTON7()])
                if(getEstadoActual() == 2)
                    accion(10);
                else
                    accion(9);
            if (keys[kf->getUP()])
                if(getEstadoActual() == 1){
                    guardarEstado();
                    accion(3);}
                else
                    accion(3);
        }
        if(est.mantieneEstado) accion(est.nEstado);

        if(spritePJ->colision(&rectFrame, &p2->rectFrame, p2->spritePJ))
            if(colitionSystem2(fp1, fp2, p2)){
                life1->subLife(5);
                if(life1->rectPorcentaje.w > 0)
                    accion(7);
            }

}
#endif // PLAYER_HPP_INCLUDED
