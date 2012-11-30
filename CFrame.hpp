#ifndef CFRAME_HPP_INCLUDED
#define CFRAME_HPP_INCLUDED

/// Cframe Class Declaration
class CFrame{
	public:
        //Main Variables
        SDL_Surface *img;
        //Main Functions
        void load (char *);
        void load (char *,int,int,int);
        void unload () {SDL_FreeSurface(img);}
};
/// Cframe Class Implementation
void CFrame::load (char *path){
	img = IMG_Load(path);
    if ( img == NULL )
	{
        printf("No pude cargar gráfico: %s\n", SDL_GetError());
        exit(12);
    }
	SDL_SetColorKey(img,SDL_SRCCOLORKEY|SDL_RLEACCEL, SDL_MapRGB(img->format,255,0,255));
	img = SDL_DisplayFormat(img);
}
void CFrame::load (char *path, int r, int g, int b){
	img = IMG_Load(path);
    if ( img == NULL )
	{
        printf("No pude cargar gráfico: %s\n", SDL_GetError());
        exit(11);
    }
	SDL_SetColorKey(img,SDL_SRCCOLORKEY|SDL_RLEACCEL, SDL_MapRGB(img->format,r,g,b));
	img = SDL_DisplayFormat(img);
}
#endif // CFRAME_HPP_INCLUDED
