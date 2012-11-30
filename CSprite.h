#ifndef CSPRITE_INCLUDED
#define CSPRITE_INCLUDED

/// Csprite Class Declaration
class CSprite{
    private: //Main Variables
             int posx,posy;
	         int estado;
	         int nframes;
	         int cont;
    public:
	       CFrame *sprite;
	       //Constructors
	       CSprite(int nf);
	       CSprite();
	       //Main Functions
	       void finalize();
	       int getEstado(){return estado;}
	       void addframe(CFrame *frame);
	       void selframe(int nf);
           int frames() {return nframes-1;}
           void setx(int x) {posx=x;}
	       void sety(int y) {posy=y;}
	       void addx(int c) {posx+=c;}
	       void addy(int c) {posy+=c;}
		   int getx() {return posx;}
	       int gety() {return posy;}
	       int getw() {return sprite[estado].img->w;}
	       int geth() {return sprite[estado].img->h;}
	       void draw(SDL_Surface *superficie);
	       void CSprite::draw(SDL_Surface *superficie, SDL_Rect *dest);
	       void CSprite::draw(SDL_Surface *superficie, SDL_Rect *dest,int ,int);
	       int colision(CSprite sp);
	       int colision(SDL_Rect*, CSprite, CSprite);
	       int colision(SDL_Rect*,SDL_Rect*,CSprite*);
	       void resetS(){cont = 0;estado = 0;}
};
/// CSprite Class Implementation
CSprite::CSprite(int nf){
	sprite = new CFrame[nf];
	nframes = nf;
	cont = 0;
	estado = 0;
}
CSprite::CSprite(){
    int	nf = 1;
	sprite = new CFrame[nf];
	nframes = nf;
	cont = 0;
	estado = 0;
}
void CSprite::finalize(){
	int i;
	for (i=0 ; i<=nframes-1 ; i++){sprite[i].unload();}
}
void CSprite::addframe(CFrame *frame){
	if (cont<nframes)
    {
		sprite[cont] = *frame;
		cont++;
	}
}
void CSprite::selframe(int nf){
	if (nf<=nframes)
    {
		estado = nf;
	}
}
void CSprite::draw(SDL_Surface *superficie){
	SDL_Rect dest;

	dest.x = posx;
	dest.y = posy;

	SDL_BlitSurface(sprite[estado].img,NULL,superficie,&dest);
}
void CSprite::draw(SDL_Surface *superficie, SDL_Rect *cuadroFrame){
    SDL_Rect dest;
	dest.x = posx;
	dest.y = posy;
	SDL_BlitSurface(sprite[estado].img, cuadroFrame,superficie, &dest);
}
void CSprite::draw(SDL_Surface *superficie, SDL_Rect *cuadroFrame,int x, int y){
    SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	SDL_BlitSurface(sprite[estado].img, cuadroFrame,superficie, &dest);
}
int CSprite::colision(CSprite sp){
    int w1,h1,w2,h2,x1,y1,x2,y2;
	w1 = getw();			// Sprite1 Width
	h1 = geth();			// Sprite1 Height
	w2 = sp.getw();		   // Sprite2 Width
	h2 = sp.geth();		   // Sprite2 Height
	x1 = getx();			// X position of Sprite1
	y1 = gety();			// Y position of Sprite1
	x2 = sp.getx();		   // X position of Sprite2
	y2 = sp.gety();		   // Y position of Sprite2
	if (((x1+w1)>x2)&&((y1+h1)>y2)&&((x2+w2)>x1)&&((y2+h2)>y1))
    {return true;}
    else
    {return false;}
}
int CSprite::colision(SDL_Rect *pj2, CSprite sp1, CSprite sp2){
    int w1,h1,w2,h2,x1,y1,x2,y2;
	w1 = getw();			// Sprite1 Width
	h1 = geth();			// Sprite1 Height
	w2 = pj2->w;		   // Sprite2 Width
	h2 = pj2->h;		   // Sprite2 Height
	x1 = sp1.getx();	    // X position of Sprite1
	y1 = sp1.gety();		// Y position of Sprite1
	x2 = sp2.getx();	   // X position of Sprite2
	y2 = sp2.gety();	   // Y position of Sprite2
	if (((x1+w1)>x2)&&((y1+h1)>y2)&&((x2+w2)>x1)&&((y2+h2)>y1))
    {return true;}
    else
    {return false;}
}
int CSprite::colision(SDL_Rect *p1, SDL_Rect *p2, CSprite *sp2){
    int w1,h1,w2,h2,x1,y1,x2,y2;
	w1 = p1->w;			// Sprite1 Width
	h1 = p1->h;			// Sprite1 Height
	w2 = p2->w;		   // Sprite2 Width
	h2 = p2->h;		   // Sprite2 Height
	x1 = getx();	    // X position of Sprite1
	y1 = gety();		// Y position of Sprite1
	x2 = sp2->getx();	   // X position of Sprite2
	y2 = sp2->gety();	   // Y position of Sprite2
	if (((x1+w1)>x2)&&((y1+h1)>y2)&&((x2+w2)>x1)&&((y2+h2)>y1))
    {return true;}
    else
    {return false;}
}

#endif // CSPRITE_HPP_INCLUDED
