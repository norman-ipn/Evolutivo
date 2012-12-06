#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>        // Libreria SDL
#include <SDL_ttf.h>    // Soporte texto TTF
#include <SDL_mixer.h>  // Audio mp3
#include <SDL_image.h>  // Foto png 
#include "stdClass.h"
#include "player.h"
#include "audioClass.h"
#include "rutines.h"
#include "mainRutines.h"
#include "tiempo.h"
#include "CFrame.h"
#include "CSprite.h"

#define Pantalla_X   640    // Pixels ancho pantalla.
#define Pantalla_Y   480    // Pixels alto  pantalla.
#define Pantalla_bpp  16    // Bits por Pixels.
#define Pantalla_Ventana  SDL_SWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE
#define Pantalla_Completa SDL_SWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN
#define Volumen_Musica 64   // Valores de 0 a 128.
#define Volumen_Sonido 64   // Valores de 0 a 128.
#define Frames_Segundo 20   // Son los fotogramas por segundo.

SDL_Surface *pantalla;      // Es la superficie principal o pantalla.
SDL_Event    evento;        // Eventos, teclado, ratón...
SDL_Rect     rect;          // Estructura Rectángulo.
Uint8       *teclas;        // Teclas pulsadas.
  
// Funciones SDL ---------------------------------------------------------------
void Inicia_SDL( const char *nombre_ventana );
SDL_Surface *Carga_Imagen( const char *nombre_archivo );
SDL_Surface *Carga_Imagen_Color( const char *nombre_archivo, Uint8 r, Uint8 g, Uint8 b );
SDL_Surface *Carga_Imagen_Alpha( const char *nombre_archivo );
TTF_Font *Carga_TTF( const char *nombre_archivo, Uint8 altura );
//void Escribe( int x, int y, TTF_Font *fuente, SDL_Color color, const char *texto );
//void Escribe_Fondo( int x, int y, TTF_Font *fuente, SDL_Color c_t, SDL_Color c_f, const char *texto );
void Icono_Ventana( const char *nombre_archivo, Uint8 r, Uint8 g, Uint8 b );
Mix_Music *Carga_Musica( const char *nombre_archivo );
Mix_Chunk *Carga_Sonido( const char *nombre_archivo, Uint8 volumen );
void Espera_Frames( void );
void Pinta_Rectangulo( SDL_Surface *imagen, int x, int y, int ancho, int alto, SDL_Color color );

// -----------------------------------------------------------------------------
// MAIN FUNCION PRINCIPAL ------------------------------------------------------
// -----------------------------------------------------------------------------
int main(int argc, char *argv[])
{

  Inicia_SDL( "Juego de peleas Evolutivo" );
  Icono_Ventana( "Imagen/mi_icono.png", 255, 0, 255 );
  
  // carga la fuente de letra  y el tamaño -------------------------------------
  TTF_Font *fuente = Carga_TTF( "Fuente/fontTTF.ttf", 20 );
  
  // Creamos colores. ----------------------------------------------------------
  SDL_Color blanco = { 255, 255, 255 };
  SDL_Color rojo   = { 255,   0,   0 };
  SDL_Color negro  = {   0,   0,   0 };
  SDL_Color verde  = {   0, 255,   0 };
   
  // Cargamos la imágen del cursor. --------------------------------------------
//  SDL_Surface *imagen_cursor = Carga_Imagen_Alpha( ".\\Imagen\\cursor.png" );
//  SDL_ShowCursor( SDL_DISABLE ); // No mostrar el cursor genérico windows.

  // Cargamos la imágen de fondo -----------------------------------------------
  SDL_Surface *imagen_fondo  = Carga_Imagen( "Imagen/fondo.png" );

  // Cargamos la imágen del sprite ---------------------------------------------
  SDL_Surface *imagen_sprite = Carga_Imagen_Color( "Imagen/luchador.bmp", 255, 255, 255 );

  // Cargamos un Sonido. -------------------------------------------------------
  Mix_Chunk *sonido = Carga_Sonido( "Sonido/explosion.wav", 128 );
  int canal_sonido = 0;
  // Cargamos la Música. -------------------------------------------------------
  Mix_Music *musica = Carga_Musica( "Musica/musica.mid" );
  // Reproducción la música, devuelve el canal por el que se reproduce. --------                
  int canal_musica = Mix_PlayMusic( musica, -1 );

  // Variables Locales ---------------------------------------------------------
  int terminar = 0;
  int x  = ( Pantalla_X / 2 ) - ( imagen_sprite->w / 2 );
  int y  = ( Pantalla_Y / 2 ) - ( imagen_sprite->h / 2 );
  int xm = 320, ym = 240;
  char texto[80];
  char caracter;

  while( !terminar )    // Bucle principal del programa
  {  
  
    while(SDL_PollEvent(&evento)) 
    {

       switch( evento.type )
       {
          case SDL_QUIT:
             terminar = 1;  
		     break;
		     
          case SDL_VIDEORESIZE:
             pantalla = SDL_SetVideoMode( Pantalla_X, Pantalla_Y, Pantalla_bpp, Pantalla_Completa );
  
          case SDL_KEYDOWN:
             caracter = evento.key.keysym.unicode;
             if(evento.key.keysym.sym == SDLK_ESCAPE ) terminar = 1;
             if(evento.key.keysym.sym == SDLK_F1 )
                pantalla = SDL_SetVideoMode( Pantalla_X, Pantalla_Y, Pantalla_bpp, Pantalla_Ventana );
             if(evento.key.keysym.sym == SDLK_w  ) y -= 12;
             if(evento.key.keysym.sym == SDLK_s  ) y += 12;
             if(evento.key.keysym.sym == SDLK_a  ) x -= 12;
             if(evento.key.keysym.sym == SDLK_d  ) x += 12;
             break;
             
          case SDL_KEYUP:
             break;
             
          case SDL_MOUSEMOTION:
             xm = evento.motion.x;
             ym = evento.motion.y; 
		     break;
		     
          case SDL_MOUSEBUTTONDOWN:
             switch (evento.button.button)
             {
                case SDL_BUTTON_LEFT:
                   x  = xm;
                   y  = ym; 
		           break;
		           
		        case SDL_BUTTON_RIGHT:
                   // Reproducción del sonido, devuelve el canal por el que se reproduce.
                   canal_sonido = Mix_PlayChannel( -1, sonido, 0);      
		           break;
		           
                default:
                   break;
		     }
             break;
             
          case SDL_MOUSEBUTTONUP:
		     break;	
		     
          default:
             break;
       }
    }

    teclas  = SDL_GetKeyState(NULL);
    if( teclas[SDLK_UP]    ) y -= 15;
    if( teclas[SDLK_DOWN]  ) y += 15;
    if( teclas[SDLK_LEFT]  ) x -= 15;
    if( teclas[SDLK_RIGHT] ) x += 15;

    // Dibujamos el fondo
    rect = (SDL_Rect) {0,0, 0,0};
    SDL_BlitSurface(imagen_fondo, NULL, pantalla, &rect);
  
    // Pintamos un Rectángulo
//    Pinta_Rectangulo( pantalla, 500, 100, 50, 50, verde );
  
    // Escribimos unos textos.
//    sprintf( texto, "%s %d - %d", "Coordenadas X, Y:", xm, ym ); 
//    Escribe_Fondo( 50, 10, fuente, negro, blanco, texto );
//    
//    TTF_SetFontStyle( fuente, TTF_STYLE_BOLD );      // Negrita
//    Escribe( 50, 50, fuente, rojo, "Pulsa \"w a s d\" para mover el copo de nieve." );
//    
//    TTF_SetFontStyle( fuente, TTF_STYLE_ITALIC  );   // Cursiva
//    Escribe( 50, 80, fuente, rojo, "Pulsa los cursores para mover el copo de nieve." ); 
//    
//    TTF_SetFontStyle( fuente, TTF_STYLE_UNDERLINE ); // Subrayada    
//    Escribe( 50,110, fuente, rojo, "Pulsa botón izquierdo para situar el copo de nieve." ); 
//    
//    TTF_SetFontStyle( fuente, TTF_STYLE_NORMAL );    // Normal       
//    Escribe( 50,140, fuente, rojo, "Pulsa botón derecho para escuchar una explosión." ); 
//    
//    Escribe_Fondo( 50, 200, fuente, blanco, negro, "Pulsa \"F1\" para minimizar la ventana." );
//    
//    Escribe( 50,250, fuente, rojo, "Pulsa \"Esc\" o cierra la ventana para salir." );  
//      
//    sprintf( texto, "%s %c -> %d", "Tecla pulsada:", caracter, caracter ); 
//    Escribe_Fondo( 50, 300, fuente, negro, blanco, texto );
//    
//    sprintf( texto, "%s %f", "Tiempo:", (float)SDL_GetTicks()/1000 ); 
//    Escribe_Fondo( 50, 330, fuente, negro, blanco, texto );

    
    // Dibujamos el muñeco
    rect = (SDL_Rect) { x - ( imagen_sprite->w / 2 ), y - ( imagen_sprite->h / 2 ), 0, 0 };
    
    // int SDL_SetAlpha(SDL_Surface *surface, Uint32 flag, Uint8 alpha);
    SDL_SetAlpha( imagen_sprite, SDL_SRCALPHA|SDL_RLEACCEL, 127 + ( rand() % 127 ) );
    SDL_BlitSurface(imagen_sprite, NULL, pantalla, &rect);

    // Dibujamos el cursor del ratón
//    rect = (SDL_Rect) {xm -1, ym -9, 0, 0};
//    SDL_BlitSurface( imagen_cursor, NULL, pantalla, &rect );


    SDL_Flip( pantalla );
    
    Espera_Frames(); 
  
  }


  Mix_HaltChannel(-1);                  // para todos los canales
  Mix_HaltMusic();                      // paramos la música
  Mix_FreeMusic(musica);                // Liberar recursos
  Mix_FreeChunk(sonido);                // Liberar recursos
  SDL_FreeSurface(pantalla);            // Liberar memoria pantalla
//  SDL_FreeSurface(imagen_cursor);
  SDL_FreeSurface(imagen_fondo);
  SDL_FreeSurface(imagen_sprite);
  TTF_CloseFont(fuente);                // Liberar fuente texto
  
  TTF_Quit();                           // Cerrar TTF
  Mix_CloseAudio();                     // Cerrar Mix_Audio
  SDL_Quit();                           // Cerrar SDL
  printf("\nTodo ha salido bien.\n");

  // system("PAUSE");
  return EXIT_SUCCESS;

}


// -----------------------------------------------------------------------------
// Inicia la libreria SDL ------------------------------------------------------
// -----------------------------------------------------------------------------
void Inicia_SDL( const char *nombre_ventana )
{
   atexit( SDL_Quit ); 
   if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) == -1){
      printf("No se pudo iniciar la libreria SDL: %s\n", SDL_GetError());
      exit(1);
   }
   SDL_EnableUNICODE(1);     // Necesario para leer los carácteres del teclado.
   // ---------------------------------------------------------------------------
   // Inicializando la Patalla --------------------------------------------------
   // --------------------------------------------------------------------------- 
   // SDL_Surface *SDL_SetVideoMode( int width, int height, int bpp, Uint32 flags );
   //
   // int width, int height: son el ancho y alto (medido en pixeles) del modo de 
   //                        video que queremos iniciar. 
   // int bpp: es el número de bits por pixel que queremos, puede ser 8, 16, 24 
   //          o 32 bits, siendo el más utilizado el de 16 bits. 
   // Uint32 flags:
   // SDL_SWSURFACE  Crea la superficie en la memoria del sistema (RAM).
   // SDL_HWSURFACE  Crea la superficie en la memoria de video (Tarjeta de video).
   // SDL_ASYNCBLIT  Habilita el uso del volcado asíncrono a la superficie de visualización. 
   //                Esto provocará usualmente la ralentización del volcado en máquinas de 
   //                una única CPU, pero puede aumentar la velocidad en sistemas SMP.
   // SDL_ANYFORMAT  Normalmente, si una superficie de video de la profundidad requerida (bpp) no está disponible,
   //                SDL emulará una con una superficie en sombras (shadow surface). Pasando SDL_ANYFORMAT se 
   //                evita esto y causa que SDL use la superficie de vídeo, independiente de la profundidad.
   // SDL_HWPALETTE  Permite el acceso exclusivo a la paleta. Sin este flag no siempre podrás obtener colores 
   //                utilizando las funciones SDL_SetColors() y SDL_SetPalette().
   // SDL_DOUBLEBUF  Habilita la utilización de búfer doble. Una llamada a SDL_Flip() intercambiará los búferes y 
   //                actualizará la pantalla. Si la utilización de búfer doble no se encuentra habilitada, 
   //                entonces SDL_Flip() simplemente realizará un SDL_UpdateRect() en toda la pantalla
   // SDL_FULLSCREEN SDL intentará usar el modo a pantalla completa. Esto no siempre es posible.
   // SDL_OPENGL     Crea un contexto de renderizado OpenGL. Se deben haber establecido previamente los atributos
   //                OpenGL con SDL_GL_SetAttribute().
   // SDL_OPENGLBLIT Como el anterior pero permite operaciones de volcado normales.
   // SDL_RESIZABLE  Crea una ventana de tamaño modificable. Si la ventana cambia de tamaño se generará el evento 
   //                SDL_VIDEORESIZE y se puede llamar nuevamente a la función SDL_SetVideMode(), para cambiar al 
   //                nuevo tamaño.
   // SDL_NOFRAME    Si es posible, SDL crea un ventana sin barra de título u otras decoraciones. El modo 
   //                FullScreen activa automáticamente este flag.
   // 
   pantalla = SDL_SetVideoMode( Pantalla_X, Pantalla_Y, Pantalla_bpp, Pantalla_Ventana );
   if(!pantalla){
      printf("No se pudo iniciar el modo de pantalla: %s\n", SDL_GetError());
      exit(1);
   }
   SDL_WM_SetCaption( nombre_ventana, NULL );    // Pone nombre a la ventana.
   // ---------------------------------------------------------------------------
   // Inicializamos SDL_mixer ---------------------------------------------------
   // ---------------------------------------------------------------------------
   // int Mix_OpenAudio(int frequency, Uint16 format, int channels, int chunksize)
   //
   // freq: La frecuencia (en Hertzios) de reproducción del sample. Valores habituales son:
   //       11025 (calidad telefónica), 22050 (calidad radiofónica) o 44100 (calidad CD).   
   // format:  
   //   AUDIO_U8 Sample de 8 bits sin signo
   //   AUDIO_S8 Sample de 8 bits con signo
   //   AUDIO_U16 o AUDIO_U16LSB Sample de 16 bits sin signo en formato little-endian.
   //   AUDIO_S16 o AUDIO_S16LSB Sample de 16 bits con signo en formato little-endian.
   //   AUDIO_U16MSB Sample de 16 bits sin signo en formato big-endian.
   //   AUDIO_S16MSB Sample de 16 bits con signo en formato big-endian.
   //   AUDIO_U16SYS AUDIO_U16LSB o
   //   AUDIO_U16MSB dependiendo del peso de tu sistema (big o little endían)
   //   AUDIO_S16SYS AUDIO_S16LSB o
   //   AUDIO_S16MSB dependiendo del peso de tu sistema (big o little endían)
   // channels:  Número de canales de audio. Pueden ser 1 para mono y 2 para estereo.   
   // chunksize: El valor habitual es 4096 según la documentación oficial de SDL.
   // Ejemplo:   Mix_OpenAudio( 22050, AUDIO_S16, 2, 4096)
   // int Mix_AllocateChannels(int numchannels)
   //   Lo normal es que le pasemos tantos canales como sonidos simultáneos queramos
   //   poder reproducir. Te aconsejo que no te quedes corto. Por otro lado, mientras más
   //   canales, más recursos requeríra el audio.
   // --------------------------------------------------------------------------- 
   atexit( Mix_CloseAudio );  
   if ( Mix_OpenAudio( 22050, AUDIO_S16, 2, 4096) == -1){
      printf("No se puede inicializar SDL_mixer %s\n",Mix_GetError());
      exit(1);
   }
   Mix_Volume( -1,  Volumen_Sonido ); // De 0 a 128.
   Mix_VolumeMusic( Volumen_Musica ); // De 0 a 128.
   // ---------------------------------------------------------------------------
   // Inicializamos SDL_ttf -----------------------------------------------------
   // ---------------------------------------------------------------------------
   atexit( TTF_Quit );
   if ( TTF_Init() < 0 ) {
      printf("No se pudo iniciar SDL_ttf: %s\n",SDL_GetError());
      exit(1);
   }
}
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
// Carga una imagen sin transparencias -----------------------------------------
// -----------------------------------------------------------------------------
SDL_Surface *Carga_Imagen( const char *nombre_archivo )
{
   // Puede manejar ficheros en formato BMP, PNM, XPM, LBM, PCX, GIF, JPG, PNG y TGA.        
   SDL_Surface *tmp, *bmp;
   tmp = IMG_Load( nombre_archivo );
   if( !tmp )
   {
    printf("No se pudo cargar %s \n", nombre_archivo);
    exit(1);
   }
   bmp = SDL_DisplayFormat( tmp );
   SDL_FreeSurface( tmp );
   if( !bmp )
   {
    printf("No se pudo DisplayFormat %s \n", nombre_archivo);
    exit(1);
   }
   return bmp;
}
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
// Carga una imagen con un color transparente ----------------------------------
// -----------------------------------------------------------------------------
SDL_Surface *Carga_Imagen_Color( const char *nombre_archivo, Uint8 r, Uint8 g, Uint8 b )
{
   // Puede manejar ficheros en formato BMP, PNM, XPM, LBM, PCX, GIF, JPG, PNG y TGA.             
   SDL_Surface *tmp, *bmp;
   tmp = IMG_Load( nombre_archivo );
   if( !tmp )
   {
    printf("No se pudo cargar %s \n", nombre_archivo);
    exit(1);
   }
   SDL_SetColorKey( tmp, SDL_SRCCOLORKEY|SDL_RLEACCEL, SDL_MapRGB( tmp->format, r, g, b));
   bmp = SDL_DisplayFormat( tmp );
   SDL_FreeSurface( tmp );
   if( !bmp )
   {
    printf("No se pudo DisplayFormat %s \n", nombre_archivo);
    exit(1);
   }
   return bmp;
}
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
// Carga una imagen con transparencias en el canal Alpha -----------------------
// -----------------------------------------------------------------------------
SDL_Surface *Carga_Imagen_Alpha( const char *nombre_archivo )
{
   // Puede manejar ficheros en formato BMP, PNM, XPM, LBM, PCX, GIF, JPG, PNG y TGA.             
   SDL_Surface *tmp, *bmp;
   tmp = IMG_Load( nombre_archivo );
   if( !tmp )
   {
    printf("No se pudo cargar %s \n", nombre_archivo);
    exit(1);
   }
   bmp = SDL_DisplayFormatAlpha( tmp );
   SDL_FreeSurface( tmp );
   if( !bmp ){
      printf("No se pudo DisplayFormat %s \n", nombre_archivo);
      exit(1);
   }
   return bmp;
}
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
// Carga Fuente de texto TTF ---------------------------------------------------
// -----------------------------------------------------------------------------
TTF_Font *Carga_TTF( const char *nombre_archivo, Uint8 altura )
{    
   TTF_Font *tmp;
   tmp = TTF_OpenFont( nombre_archivo, altura );     
   if( !tmp ){
      printf("No se pudo cargar %s \n", nombre_archivo);
      exit(1);
   }
   return tmp;
   // int TTF_GetFontStyle(TTF_Font *font)
   // int TTF_SetFontStyle(TTF_Font *font, int style)
   // Los posibles estilos son:
   // TTF_STYLE_BOLD      para estilo negrita
   // TTF_STYLE_ITALIC    para estilo itálica.
   // TTF_STYLE_UNDERLINE para estilo subrayado. 
   // TTF_STYLE_NORMAL    El estado normal es
}
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
// Escribe un Texto con una Fuente y un Color dados. ---------------------------
// -----------------------------------------------------------------------------
void Escribe( int x, int y, TTF_Font *fuente, SDL_Color color, const char *texto )
{
    SDL_Surface *tmp; SDL_Rect  tmp_rect;
    // sprintf( texto, "%s %s %d", texto_A, texto_B, numero ); 
	tmp = TTF_RenderText_Blended( fuente, texto, color );
    tmp_rect.x = x;      tmp_rect.y = y; 
	tmp_rect.w = tmp->w; tmp_rect.h = tmp->h;
	SDL_BlitSurface( tmp, NULL, pantalla, &tmp_rect);
    SDL_FreeSurface( tmp );
}
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
// Escribe un Texto con una Fuente y dos Colores dados. ------------------------
// -----------------------------------------------------------------------------
void Escribe_Fondo( int x, int y, TTF_Font *fuente, SDL_Color c_t, SDL_Color c_f, const char *texto )
{
    SDL_Surface *tmp; SDL_Rect  tmp_rect;
    // sprintf( texto, "%s %s %d", texto_A, texto_B, numero ); 
	tmp = TTF_RenderText_Shaded( fuente, texto, c_t, c_f );
    tmp_rect.x = x;      tmp_rect.y = y; 
	tmp_rect.w = tmp->w; tmp_rect.h = tmp->h;
	SDL_BlitSurface( tmp, NULL, pantalla, &tmp_rect);
    SDL_FreeSurface( tmp );
}
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
// Carga el Icono de la Ventana 32 x 32 Pixels ---------------------------------
// -----------------------------------------------------------------------------
void Icono_Ventana( const char *nombre_archivo, Uint8 r, Uint8 g, Uint8 b )
{
  SDL_Surface *imagen_icono;
  imagen_icono = Carga_Imagen_Color( nombre_archivo, r, g, b );
  SDL_WM_SetIcon( imagen_icono, NULL);
}
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
// Carga una Música ------------------------------------------------------------
// -----------------------------------------------------------------------------
Mix_Music *Carga_Musica( const char *nombre_archivo )
{     
   Mix_Music *tmp = NULL;
      
   tmp = Mix_LoadMUS( nombre_archivo );

   if ( tmp == NULL ){
      printf("No puede cargar musica %s: %s\n", nombre_archivo, Mix_GetError());
      exit(1);
   }
   return tmp;
   
   // Mix_Music *Mix_LoadMUS( const char *file )
   // void Mix_FreeMusic( Mix_Music )
   // int Mix_PlayMusic( Mix_Music *music, int loops )
   // int Mix_FadeInMusic( Mix_Music *music, int loops, int ms )
   // int Mix_VolumeMusic( int volume )
   // void Mix_PauseMusic()
   // void Mix_ResumeMusic()
   // int Mix_HaltMusic()
   // int Mix_FadeOutMusic(int ms)   
}
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
// Carga un Sonido  ------------------------------------------------------------
// -----------------------------------------------------------------------------
Mix_Chunk *Carga_Sonido( const char *nombre_archivo, Uint8 volumen )
{
  Mix_Chunk *tmp;
  tmp = Mix_LoadWAV( nombre_archivo );
  if ( tmp == NULL )
  {
     printf("No pude cargar sonido %s: %s\n", nombre_archivo, Mix_GetError());
     exit(1);
  }
  Mix_VolumeChunk( tmp, volumen ); // De 0 a 128
  return tmp;
  // Mix_Chunk *Mix_LoadWAV(char *file)
  // void Mix_FreeChunk( Mix_Chunk *chunk) 
  // int Mix_VolumeChunk( Mix_Chunk *chunk, int volume )    // rango de 0 a 128.
  // int Mix_PlayChannel( int channel, Mix_Chunk *chunk, int loops )  
  // int Mix_PlayChannelTimed( int channel, Mix_Chunk *chunk, int loops, int ticks)
  // int Mix_FadeInChannel( int channel, Mix_Chunk *chunk, int loops, int ms)
  // int Mix_FadeInChannelTimed( int channel, Mix_Chunk *chunk, int loops, int ms, int ticks)
  // void Mix_Pause( int channel )
  // void Mix_Resume( int channel )
  // int Mix_HaltChannel( int channel )
  // int Mix_FadeOutChannel( int channel, int ms ) 
  // int Mix_Playing( int channel )  // Si está sonando 1, 0 si no.
  // int Mix_Paused( int channel )   // Si está pausada 0, 1 si está sonando.
  // void Mix_RewindMusic() // Su misisón es volver la reproducción de la música al principio.
  // int Mix_SetMusicPosition( double position )  
  //     La función nos permite situar la posición de reproducción en el lugar
  //     deseado. La posición dependerá directamente del formato del archivo de música,
  //     pudiendo ser el tiempo en milisegundo para archivos de música digitalizada o la posición
  //    del patrón o el compás si es un archivo MOD o MIDI.
  // Int Mix_PlayingMusic()
  // Int Mix_PausedMusic()
  // Mix_MusicType Mix_GetMusicType(const Mix_Music *music)
  //     Mix_MusicType puede tomar los siguientes valores: 
  //       MUS_WAV,
  //       MUS_MOD
  //       MUS_MID 
  //       MUS_OGG 
  //       MUS_MP3  Si el valor devuelto es 
  //       MUS_NONE significa que no hay ninguna música en reproducción. 
  //       MUS_CMD  significa que la reproducción la está llevando un reproductor externo.
}
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
// Espera el tiempo sobrante ---------------------------------------------------
// -----------------------------------------------------------------------------
void Espera_Frames( void )
{
  static const unsigned int frames = (unsigned int )( 1000 / Frames_Segundo ); // Son los fotogramas por segundo.
  static unsigned int tiempo = 0;
  tiempo = SDL_GetTicks() + frames ;         // Se inicia la cuenta de tiempo.
  unsigned int t_espera      = tiempo - SDL_GetTicks();
  if ( t_espera > 0 && t_espera <= frames ) SDL_Delay( t_espera );
  tiempo += frames;
}
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
// Pinta un Rectángulo ---------------------------------------------------------
// -----------------------------------------------------------------------------
void Pinta_Rectangulo( SDL_Surface *imagen, int x, int y, int ancho, int alto, SDL_Color color )
{
  // int SDL_FillRect(SDL_Surface *dst, SDL_Rect *dstrect, Uint32 color);
  SDL_Rect dest;
  dest.x = x;
  dest.y = y;
  dest.w = ancho;
  dest.h = alto;
  SDL_FillRect( imagen, &dest, SDL_MapRGB( imagen->format, color.r, color.g, color.b ) );
}
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------



//----------------------------------------------------------------
// ESTRUCTURAS SDL
//
// Pero primero tenemos que ver las Estructuras que la forman...
//
// Uint8  -> unsigned char a  8 bit (1 byte)
// Uint16 -> unsigned int  a 16 bit (2 byte)
// Uint32 -> unsigned int  a 32 bit (4 byte)
// Uint64 -> unsigned int  a 64 bit (8 byte)
// Sint8  -> signed   char a  8 bit (1 byte)
// Sint16 -> signed   int  a 16 bit (2 byte)
// Sint32 -> signed   int  a 32 bit (4 byte)
// Sint64 -> signed   int  a 64 bit (8 byte)
//
// ESTRUCTURA RECTANGULO
//
// typedef struct {
//   Sint16 x, y;         x,y posicion en pantalla
//   Uint16 w, h;         w - Ancho h - Alto
// } SDL_Rect;     
// ----------------------------------------------------------------
// ESTRUCTURA COLOR
//
// typedef struct{
//   Uint8 r;             intensidad de la componente roja.
//   Uint8 g;             intensidad de la componente verde.
//   Uint8 b;             intensidad de la componente azul.
//   Uint8 unused;        unused: no utilizado.
// } SDL_Color;
//------------------------------------------------------------------------------------------------------------
// ESTRUCTURA PALETTE
//
// typedef struct{
//   int ncolors;          número de colores usados en la paleta.
//   SDL_Color *colors;    puntero a la estructura COLOR
// } SDL_Palette;
//
// La paleta es solo usada en los modos de 8 bits por pixel, es decir los modos que funcionan a 256 colores.
//------------------------------------------------------------------------------------------------------------
// ESTRUCTURA PIXEL
//
// typedef struct{
//   SDL_Palette *palette;                  
//   Uint8 BitsPerPixel;
//   Uint8 BytesPerPixel;
//   Uint32 Rmask, Gmask, Bmask, Amask;
//   Uint8 Rshift, Gshift, Bshift, Ashift;
//   Uint8 Rloss, Gloss, Bloss, Aloss;
//   Uint32 colorkey;
//   Uint8 alpha;
// } SDL_PixelFormat;
//
// palette: puntero a estructura PALETTE. Vale NULL si los bits por pixel son superiores a 8. Esto se debe a 
//          que los modos de 16, 24 y 32 bits no utilizan paleta.
// BitsPerPixel: es el número de bits usado para representar cada pixel en la superficie. 
//               Usualmente es 8, 16, 24 o 32 bits.
// BytesPerPixel: Como el anterior pero ahora medido en bytes. Pueden ser 1, 2, 3 o 4 bytes.
// Rmask, Gmask, Bmask, Amask: mascaras binarias usadas para obtener los valores de cada componente del color
//                             (rojo, verde, azul o alpha).
// Rshift, Gshift, Bshift, Ashift: desplazamiento binario hacia la izquierda de cada componente de color en 
//                                 el valor del pixel.
// Rloss, Gloss, Bloss, Aloss: pérdida de precisión de cada componente de color (2[RGBA]loss).
// colorkey: aquí se almacena el color que es transparente en la superficie. Es usado cuando no queremos que 
// cierto color de la superficie se muestra. Esto lo utilizaremos más adelante cuando trabajemos con sprites.
// alpha: valor alpha de la superficie.
//---------------------------------------------------------------------------------------------------
// ESTRUCTURA DE UNA SURFACE - SUPERFICIE
//
// typedef struct SDL_Surface 
// {
//  Uint32 flags;                     /* solo lectura */
//  SDL_PixelFormat *format;          /* solo lectura */
//  int w, h;                         /* solo lectura */
//  Uint16 pitch;                     /* solo lectura */
//  void *pixels;                     /* lectura y escritura */
//                                    /* clipping information */
//  SDL_Rect clip_rect;               /* solo lectura */
//  int refcount;                     /* Read-mostly */
// } SDL_Surface;
//
// flags: son unos flags que indican el tipo de superficie, más adelante veremos estos tipos.
// format: un puntero a una estructura que indica el formato de cada pixel, ya lo veremos.
// w, h: ancho y alto de la superficie.
// pitch: corresponde a la longitud de una línea de escaneo (scanline) de la superficie, medido en bytes.
// pixels: puntero al comienzo de los datos (pixeles) de la superficie.
// clip_rect: estructura que indica el área (un simple rectángulo) de clipping de la superficie, también la veremos muy luego.
// refcount: contador de referencia, usado cuando se libera la superficie.
//
// Todos los campos anteriores son de solo lectura. En el único que se puede escribir es en el puntero pixels. 
// Este será usado más adelante para colocar pixeles en una superficie.
//---------------------------------------------------------------
// 
//   SDL_Rect rect;
//   SDL_Surface *imagen;
//   SDL_Surface *screen;
//     
//  EJEMPLOS:
//   SDL_Surface *image;
//   SDL_rect dest;
//	 dest.x = 100;
//   dest.y = 100;
//	 dest.w = image->w;
//	 dest.h = image->h;
//
//-------------------------------------------------------------------------------
//
// ESTRUCTURA EVENTO - Event
//
// typedef union
// {
//   Uint8 type;                        
//   SDL_ActiveEvent active;            SDL_KEYDOWN: cuando se presiona una tecla
//   SDL_KeyboardEvent key;             SDL_KEYUP:   cuando se suelta la tecla
//   SDL_MouseMotionEvent motion;       SDL_MOUSEMOTION: cuando se mueve el ratón
//   SDL_MouseButtonEvent button;       SDL_MOUSEBUTTONDOWN: presiona un botón del ratón
//   SDL_JoyAxisEvent jaxis;            SDL_MOUSEBUTTONUP: cuando se suelta un botón del ratón
//   SDL_JoyBallEvent jball;            SDL_JOYAXISMOTION: cuando se mueven los ejes del joystick
//   SDL_JoyHatEvent jhat;              SDL_JOYBUTTONDOWN: cuando se presiona un botón del joystick
//   SDL_JoyButtonEvent jbutton;        SDL_JOYBUTTONUP:   cuando se suelta un botón del joystick
//   SDL_ResizeEvent resize;
//   SDL_ExposeEvent expose;
//   SDL_QuitEvent quit;
//   SDL_UserEvent user;
//   SDL_SywWMEvent syswm;
// } SDL_Event;
// ----------------------------------------------------------------
//
// COMPROBACION DE EVENTOS
//
//  SDL_Event event;
//  int done = 0;
//  Uint8 *keystate;  // puntero que recoge el valor de la tecla pulsada
//
//  while (done == 0) 
//  {
//  
//    // dibujar Fondo
//    // dibujar sprites
//    // SDL_Flip(screen); // Refresco pantalla
//
//    keystate = SDL_GetKeyState(NULL);
//    if ( keystate[SDLK_UP] )    ; // Arribanave
//    if ( keystate[SDLK_DOWN] )  ; // Abajpnave
//    if ( keystate[SDLK_LEFT] )  ; // Izquierda 
//    if ( keystate[SDLK_RIGHT] ) ; // Derecha 
//
//    // Comprobando teclas para opciones
//    while (SDL_PollEvent(&event)) 
//    {
//      // Cerrar la ventana - código que se ejecuta al cerrar la ventana
//      if (event.type == SDL_QUIT) { done = 1; }
//      
//      // Pulsando una tecla
//      if (event.type == SDL_KEYDOWN)
//      {
//        if (event.key.keysym.sym == SDLK_ESCAPE) done = 1;  
//      }
//    }
//  }
//
//
//  SDL_FreeSurface(imagen);            // Liberar memoria imagen
//  SDL_FreeSurface(screen);            // Liberar memoria pantalla
//  SDL_Quit();                         // Cerrar SDL
//  printf("\nTodo ha salido bien.\n");
//  return 0;
//
// } // Fin del Programa
//
// ----------------------------------------------------------------
//
// SDL_GetKeyState(NULL); que nos devuelve un Uint8 con el código de la tecla pulsada.
// event.key.keysym.sym
// ---------------------
// SDLK_BACKSPACE: retroceso
// SDLK_TAB: tabulador
// SDLK_CLEAR: clear
// SDLK_RETURN: return
// SDLK_PAUSE: pausa
// SDLK_ESCAPE: escape
// SDLK_SPACE: espacio
// SDLK_EXCLAIM: ’!’ exclamación
// SDLK_QUOTEDBL: ’"’ dobles comillas
// SDLK_HASH: ’#’ hash
// SDLK_DOLLAR: ’$’ dollar
// SDLK_AMPERSAND: ’&’ ampersand
// SDLK_QUOTE: ”’ comillas simples
// SDLK_LEFTPAREN: ’(’ paréntesis izquierdo
// SDLK_RIGHTPAREN: ’)’ paréntesis derecho
// SDLK_ASTERISK: ’*’ asterisco
// SDLK_PLUS: ’+’ signo de suma
// SDLK_COMMA: ’,’ coma
// SDLK_MINUS: ’-’ signo menos
// SDLK_PERIOD: ’.’ periodo
// SDLK_SLASH: ’/ barra derecha
// SDLK_0: ’0’ número 0. Todos los números hasta el 9 llevan la misma forma.
// SDLK_COLON: ’:’ dos puntos
// SDLK_SEMICOLON: ’;’ punto y coma
// SDLK_LESS: ’<’ signo menor que
// SDLK_EQUALS: ’=’ signo igual
// SDLK_GREATER: ’>’ signo mayor que
// SDLK_QUESTION: ’?’ signo de interrogación
// SDLK_AT: ’@’ arroba
// SDLK_LEFTBRACKET: ’[’ corchete izquierdo
// SDLK_BACKSLASH: ’\’ barra izquierda
// SDLK_RIGHTBRACKET: ’]’ corchete derecho
// SDLK_CARET: ’^’ caret
// SDLK_UNDERSCORE: ’_’ guión bajo
// SDLK_BACKQUOTE: ’‘’ grave
// SDLK_a: ’a’ a. Todas las letras llevan la misma forma.
// SDLK_DELETE: ’^?’ delete
// SDLK_KP0: keypad 0. Todos los números del keypad hasta el 9 llevan la misma forma.
// SDLK_KP_PERIOD: ’.’ periodo del keypad
// SDLK_KP_DIVIDE: ’/’ división del keypad
// SDLK_KP_MULTIPLY: ’*’ multiplicación del keypad
// SDLK_KP_MINUS: ’-’ signo menos del keypad
// SDLK_KP_PLUS: ’+’ signo más del keypad
// SDLK_KP_ENTER: ’\r’ enter del keypad
// SDLK_KP_EQUALS: ’=’ signo igual del keypad
// SDLK_UP: cursor arriba
// SDLK_DOWN: cursor abajo
// SDLK_RIGHT: cursor derecha
// SDLK_LEFT: cursor izquierda
// SDLK_INSERT: tecla insert
// SDLK_HOME: tecla inicio
// SDLK_END: tecla fin
// SDLK_PAGEUP: tecla avanzar página
// SDLK_PAGEDOWN: tecla retroceder página
// SDLK_F1: F1. Todas las funciones "F" llevan la misma forma.
// SDLK_NUMLOCK: bloqueo numérico
// SDLK_CAPSLOCK: bloqueo mayúsculas
// SDLK_SCROLLOCK: scrollock
// SDLK_RSHIFT: shift derecho
// SDLK_LSHIFT: shift izquierdo
// SDLK_RCTRL: ctrl derecho
// SDLK_LCTRL: ctrl izquierdo
// SDLK_RALT: alt derecho
// SDLK_LALT: alt izquierdo
// SDLK_RMETA: meta derecho
// SDLK_RMETA: meta derecho
// SDLK_LMETA: meta izquierdo
// SDLK_LSUPER: tecla windows izquierda
// SDLK_RSUPER: tecla windows derecha
// SDLK_MODE: mode shift
// SDLK_HELP: ayuda
// SDLK_PRINT: imprimir
// SDLK_SYSREQ: SysRq
// SDLK_BREAK: break
// SDLK_MENU: menu
// SDLK_POWER: power
// SDLK_EURO: euro
//
// -----------------------------------------------------------------------------
