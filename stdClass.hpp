#ifndef STDCLASS_HPP_INCLUDED
#define STDCLASS_HPP_INCLUDED

class lastCombo{
 private:
    int *cola;
    int tam;

 public:
    void add(int);
    char *getList();

 lastCombo(int);
};
lastCombo::lastCombo(int t){
    cola = new int[t];
    if( cola == NULL ) exit(77);
    tam=t;
    if(cola == NULL) exit(53);
    for(int i=0; i<t; i++) cola[i]=0;
}
void lastCombo::add(int x){

    for(int i=tam-1; i>0; i--)
        cola[i]=cola[i-1]; //if(i==0) exit(444);

    cola[0] = x;

}
char *lastCombo::getList(){
 char *numeros, n[2];
 numeros = new char[tam*2];
 if( numeros == NULL ) exit(78);

    strcpy(numeros, "");
    for(int i=0; i<tam; i++){
        itoa(cola[i], n, 10);
        strcat(numeros, n);
        strcat(numeros, " ");
    }
 return numeros;
}
/// --------- Ctext
class Ctext{
 private:
    SDL_Color bgcolor,fgcolor;
    SDL_Surface *surfTexto, *surfBuffer;
    SDL_Rect rectangulo;
    TTF_Font *fuente;
    char *txt;
    int posX, posY;

 public:
    void text(char*, int, int, SDL_Surface *surface);
    void text(char*, int, int);
    void setFuente(TTF_Font *f){fuente = f;}
    int showText(SDL_Surface*);

 Ctext();
};

Ctext::Ctext(){
    // inicializa colores para el texto
    fgcolor.r=255;
    fgcolor.g=255;
    fgcolor.b=255;
    bgcolor.r=0;
    bgcolor.g=0;
    bgcolor.b=0;
    txt = "";
}

void Ctext::text(char *texto, int x, int y, SDL_Surface *surface){
    surfTexto = TTF_RenderText_Shaded(fuente,texto,fgcolor,bgcolor);
    rectangulo.x = x;
    rectangulo.y = y;
    rectangulo.w = surfTexto->w;
    rectangulo.h = surfTexto->h;
    // Usamos algun color para la transparencia del fondo
    SDL_SetColorKey(surfTexto,SDL_SRCCOLORKEY|SDL_RLEACCEL, SDL_MapRGB(surfTexto->format,0,0,0));

    SDL_BlitSurface(surfTexto,NULL,surface,&rectangulo);
}
void Ctext::text(char *texto, int x, int y){
    txt = texto;
    posX = x;
    posY = y;
}
int Ctext::showText(SDL_Surface *screen){
    if(strcmp(txt, "") == 0) return 0;
    surfTexto = TTF_RenderText_Shaded(fuente,txt,fgcolor,bgcolor);
    rectangulo.x = posX;
    rectangulo.y = posY;
    rectangulo.w = surfTexto->w;
    rectangulo.h = surfTexto->h;
    // Usamos algun color para la transparencia del fondo
    SDL_SetColorKey(surfTexto,SDL_SRCCOLORKEY|SDL_RLEACCEL, SDL_MapRGB(surfTexto->format,0,0,0));

    SDL_BlitSurface(surfTexto,NULL,screen,&rectangulo);
    return 1;
}


/// ------------- Cinput
class Cinput{
 private:
    int num;
    char valor[2];
    char nIngresado[2];
    int nFra;

 public:
    Ctext txtNum;
    int inputN();
    char inputC();
    int get(int, int);
 Cinput();
};
Cinput::Cinput(){
    txtNum.text(" ",0,0);
    num = -1;
    strcpy(nIngresado,"");
}
int Cinput::get(int x, int y){
    if((num = inputN()) != -1){
        itoa(num, valor, 10);
        txtNum.text(valor, x, y);
        return num;
    }
    return -1;

    /*
    switch(num = inputN()){
     case -1: break;
     case 0:
     case 1:
     case 2:
     case 3:
     case 4:
     case 5:
     case 6:
     case 7:
     case 8:
     case 9:
        SDL_Delay(120);
        itoa(num, valor, 10);
        strcat(nIngresado, valor);
        txtNum.text(nIngresado, 120, 0);
        if(nFra == 0)
            nFra = num;
        else
            return (nFra*10 + num);

        break;
     case 13:
            return 13;

        break;
     case 14:
        strcpy(nIngresado,"");
        nFra = 0;
        return 14;
        break;
    }
    return -1;*/
}
int Cinput::inputN(){
 Uint8 *keys;
    keys = SDL_GetKeyState(NULL);

    if((keys[SDLK_1])||(keys[SDLK_KP1]))
        return 1;
    if((keys[SDLK_2])||(keys[SDLK_KP2]))
        return 2;
    if((keys[SDLK_3])||(keys[SDLK_KP3]))
        return 3;
    if((keys[SDLK_4])||(keys[SDLK_KP4]))
        return 4;
    if((keys[SDLK_5])||(keys[SDLK_KP5]))
        return 5;
    if((keys[SDLK_6])||(keys[SDLK_KP6]))
        return 6;
    if((keys[SDLK_7])||(keys[SDLK_KP7]))
        return 7;
    if((keys[SDLK_8])||(keys[SDLK_KP8]))
        return 8;
    if((keys[SDLK_9])||(keys[SDLK_KP9]))
        return 9;
    if((keys[SDLK_0])||(keys[SDLK_KP0]))
        return 0;
    if((keys[SDLK_RETURN])||(keys[SDLK_KP_ENTER]))
        return 13;
    if(keys[SDLK_BACKSPACE])
        return 14;
    return -1;
}
char Cinput::inputC(){
 Uint8 *keys;
    keys = SDL_GetKeyState(NULL);

        if(keys[SDLK_a])
            return 'a';
        if(keys[SDLK_b])
            return 98;
        if(keys[SDLK_c])
            return 99;
        if(keys[SDLK_d])
            return 100;
        if(keys[SDLK_e])
            return 101;
        if(keys[SDLK_f])
            return 102;
        if(keys[SDLK_g])
            return 103;
        if(keys[SDLK_h])
            return 104;
        if(keys[SDLK_i])
            return 105;
        if(keys[SDLK_j])
            return 106;
        if(keys[SDLK_k])
            return 107;
        if(keys[SDLK_l])
            return 108;
        if(keys[SDLK_m])
            return 109;
        if(keys[SDLK_n])
            return 110;
        if(keys[SDLK_o])
            return 111;
        if(keys[SDLK_p])
            return 112;
        if(keys[SDLK_q])
            return 113;
        if(keys[SDLK_r])
            return 114;
        if(keys[SDLK_s])
            return 115;
        if(keys[SDLK_t])
            return 116;
        if(keys[SDLK_u])
            return 117;
        if(keys[SDLK_v])
            return 118;
        if(keys[SDLK_w])
            return 119;
        if(keys[SDLK_x])
            return 120;
        if(keys[SDLK_y])
            return 121;
        if(keys[SDLK_z])
            return 122;

        if((keys[SDLK_1])||(keys[SDLK_KP1]))
            return 49;
        if((keys[SDLK_2])||(keys[SDLK_KP2]))
            return 50;
        if((keys[SDLK_3])||(keys[SDLK_KP3]))
            return 51;
        if((keys[SDLK_4])||(keys[SDLK_KP4]))
            return 52;
        if((keys[SDLK_5])||(keys[SDLK_KP5]))
            return 53;
        if((keys[SDLK_6])||(keys[SDLK_KP6]))
            return 54;
        if((keys[SDLK_7])||(keys[SDLK_KP7]))
            return 55;
        if((keys[SDLK_8])||(keys[SDLK_KP8]))
            return 56;
        if((keys[SDLK_9])||(keys[SDLK_KP9]))
            return 57;
        if((keys[SDLK_0])||(keys[SDLK_KP0]))
            return 48;
        if((keys[SDLK_RETURN])||(keys[SDLK_KP_ENTER]))
            return 13;
        if(keys[SDLK_BACKSPACE])
            return 14;

 return -1;
}
/// ------------- CommandButton
class CommandButton{
 private:
    int cont;
    int max;

 public:
    SDL_Rect rectForma;
    CFrame icono;
    Ctext caption;

    bool clic(int, int);
    void loadIcon(char *dir){
        icono.load(dir);
        rectForma.w = icono.img->w;
        rectForma.h = icono.img->h;
        }
    void addCont(){cont++; if(cont == max) cont=0;}
    void subCont(){cont--; if(cont == -1) cont=max-1;}
    void setCont(int i){cont = i;}
    int getCont(){return cont;}
    void setMax(int m){max = m;}
    void draw(SDL_Surface*);
    void setx(int x){rectForma.x = x;}
    void sety(int y){rectForma.y = y;}
    void setCaption(char *txt,int x, int y){
        caption.text(txt, (x+rectForma.x), (y+rectForma.y));}

 CommandButton();
};

bool CommandButton::clic(int mx, int my){
    if(( mx < (rectForma.w+rectForma.x) )&&( mx > rectForma.x ))
        if(( my < (rectForma.h+rectForma.y) )&&( my > rectForma.y ))
            return true;
return false;
}

void CommandButton::draw(SDL_Surface *superficie){
	SDL_BlitSurface(icono.img,NULL,superficie,&rectForma);
	//if(caption.fuente != NULL)
        caption.showText(superficie);
}
CommandButton::CommandButton(){
 max = cont = rectForma.x = rectForma.y = 0;
}

/// ------------- Rectangulos

class Rect{
 public:
    SDL_Rect recuadro, recuadro2;
    CFrame *FrecuadroAlpha;

    void draw(SDL_Surface*);
    void alpha(SDL_Surface*);
 Rect();
};

Rect::Rect(){
    recuadro.x = 0;
    recuadro.y = 0;
    recuadro.w = 0;
    recuadro.h = 0;

    recuadro2.x = 0;
    recuadro2.y = 0;
    recuadro2.w = 0;
    recuadro2.h = 0;
}
void Rect::draw(SDL_Surface *screen){
        SDL_BlitSurface(FrecuadroAlpha->img, &recuadro2, screen, &recuadro);
}
void Rect::alpha(SDL_Surface *screen){

    SDL_FillRect(FrecuadroAlpha->img, &recuadro, SDL_MapRGB(screen->format, 0, 0, 255));
    SDL_SetAlpha(FrecuadroAlpha->img, SDL_SRCALPHA|SDL_RLEACCEL, 150);
}

/// ------------- Life

class Life{
 public:
    SDL_Rect rectPorcentaje;
    float porcentajeReal;
    int porcentajeTotal;

    void subLife(int i){
        porcentajeReal -= i;
        rectPorcentaje.w = (float)(porcentajeReal / porcentajeTotal) * 250;}
 Life(int x){porcentajeTotal=porcentajeReal=x;rectPorcentaje.w = 250; rectPorcentaje.h = 30;}
};
#endif // STDCLASS_HPP_INCLUDED
