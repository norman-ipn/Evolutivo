/// File Player Class
float FilePlayer_version = 2.02;

// TODO (Haunter#1#): mostrar un numero de full action especifico
// TODO (Haunter#2#): poner 0, 'a' o 's' en los campos sin utilizar


//#include <stdio.h>
#include <conio.h>
#include <iomanip.h>
#include <string.h>
#include <iostream.h>

struct ColitionRect{
    int activo;
    int x;
    int y;
    int w;
    int h;
};

struct FullActionFile{
    char nombreAccion[15];
    int selectF;
    int setXaxis;
    int setYaxis;
    int addXsprite;
    int setXsprite;
    int addYsprite;
    int setYsprite;
    int w;
    int h;
    int addFrameX;
    int endFrameX;
    int frameFijo;
};

struct Sprite{
    char frames[100];// path de 100 caracteres
    ColitionRect atackCR[25][6]; //cuadros rojos
    ColitionRect vulnerableCR[25][6]; //cuadros azules

    ColitionRect *getCRa(){return &atackCR[0][0];};
    ColitionRect *getCRv(){return &vulnerableCR[0][0];};
};
class FilePlayer{
    private:
        float fileVersion;
        char fileName[100];
		char nombre[20];
		Sprite spr[90];
		FullActionFile FAF[100];
    public:
        void crear();
        int menuFAF(int pos);
        int setCero(int pos);
        int mostrar();
        int modifFAF();
        int modifCR();
        int modifDir();
        int modifAxis();
        int actualizar();
        ColitionRect *getCRa(int s){return spr[s].getCRa();};
        ColitionRect *getCRv(int s){return spr[s].getCRv();};
        void getCRa(int s, int f, int c, ColitionRect *cr){
            cr->activo = spr[s].atackCR[f][c].activo;
            cr->x = spr[s].atackCR[f][c].x;
            cr->y = spr[s].atackCR[f][c].y;
            cr->w = spr[s].atackCR[f][c].w;
            cr->h = spr[s].atackCR[f][c].h;
            }
        void getCRv(int s, int f, int c, ColitionRect *cr){
            cr->activo = spr[s].vulnerableCR[f][c].activo;
            cr->x = spr[s].vulnerableCR[f][c].x;
            cr->y = spr[s].vulnerableCR[f][c].y;
            cr->w = spr[s].vulnerableCR[f][c].w;
            cr->h = spr[s].vulnerableCR[f][c].h;
            }
        char *getDirFrame(int i){return spr[i].frames;};
        char *getNombre(){return nombre;};
        void setNombre(char *n){strcpy(nombre, n);};
        char *getFileName(){return fileName;};
        void setFileName(char *n){strcpy(fileName, n);};
        int setFileName_and_load();
        void getInstances(int, int*, int*, int*, int*, int*, int*, int*, int*, int*, int*, int*, int*);
        void getCR(int, int, int, bool, ColitionRect*);
        void setCR(int, int, int, bool, ColitionRect*);
        int loadFile();
        void saveFile();
    ~FilePlayer(){};
};

void FilePlayer::getCR(int i, int a, int e, bool RedBlue, ColitionRect *CR){

    if(RedBlue){
        CR->activo = spr[i].atackCR[a][e].activo;
        CR->x = spr[i].atackCR[a][e].x;
        CR->y = spr[i].atackCR[a][e].y;
        CR->w = spr[i].atackCR[a][e].w;
        CR->h = spr[i].atackCR[a][e].h;
    }else{
        CR->activo = spr[i].vulnerableCR[a][e].activo;
        CR->x = spr[i].vulnerableCR[a][e].x;
        CR->y = spr[i].vulnerableCR[a][e].y;
        CR->w = spr[i].vulnerableCR[a][e].w;
        CR->h = spr[i].vulnerableCR[a][e].h;
    }
}
void FilePlayer::setCR(int i, int a, int e, bool RedBlue, ColitionRect *CR){

    if(RedBlue){
        spr[i].atackCR[a][e].activo = CR->activo;
        spr[i].atackCR[a][e].x = CR->x;
        spr[i].atackCR[a][e].y = CR->y;
        spr[i].atackCR[a][e].w = CR->w;
        spr[i].atackCR[a][e].h = CR->h;
    }else{
        spr[i].vulnerableCR[a][e].activo = CR->activo;
        spr[i].vulnerableCR[a][e].x = CR->x;
        spr[i].vulnerableCR[a][e].y = CR->y;
        spr[i].vulnerableCR[a][e].w = CR->w;
        spr[i].vulnerableCR[a][e].h = CR->h;
    }
}
void FilePlayer::getInstances(int i, int *selectF, int *setXaxis, int *setYaxis, int *addXsprite, int *setXsprite, int *addYsprite, int *setYsprite, int *w, int *h, int *addFrameX, int *endFrameX, int *frameFijo){

    *selectF = FAF[i].selectF;
    *setXaxis =FAF[i].setXaxis;
    *setYaxis =FAF[i].setYaxis;
    *addXsprite = FAF[i].addXsprite;
    *setXsprite = FAF[i].setXsprite;
    *addYsprite = FAF[i].addYsprite;
    *setYsprite = FAF[i].setYsprite;
    *w = FAF[i].w;
    *h = FAF[i].h;
    *addFrameX = FAF[i].addFrameX;
    *endFrameX = FAF[i].endFrameX;
    *frameFijo = FAF[i].frameFijo;
}

int FilePlayer::menuFAF(int i){
    int opc;
    int a=0;
    while(a==0)
		{
		system("cls");
		cout<<"**********************************************"<<endl;
		cout<<"Menu de moficacion de registros de Fullaction"<<endl;
		cout<<"**********************************************"<<endl<<endl;
		cout<<"(0) - Tira de frames"<<endl;
		cout<<"(1) - Axis de X"<<endl;
	    cout<<"(2) - Axis de Y"<<endl;
		cout<<"(3) - Desplazamiento del sprite en X"<<endl;
		cout<<"(4) - Setear el sprite en X posicion"<<endl;
		cout<<"(5) - Desplazamiento del sprite en Y"<<endl;
	    cout<<"(6) - Setear el sprite en Y posicion"<<endl;
		cout<<"(7) - Ancho del frame"<<endl;
		cout<<"(8) - Alto del frame"<<endl;
		cout<<"(9) - Desplazamiento X al siguiente frame"<<endl;
		cout<<"(Q) - Final de la tira de Frames (X)"<<endl;
		cout<<"(W) - La animacion se queda en un frame fijo (1/0)"<<endl;
		cout<<"(ESC) Salir."<<endl;
		cout<<"Ingrese la opci¢n: "<<endl;
		opc = getch();
		switch(opc)
			{
			 case 48: cout<<"\nTira de frames: "<<FAF[i].selectF<<"\nNuevo dato: ";
                        cin>>FAF[i].selectF;
                        while((FAF[i].selectF<0)||(FAF[i].selectF>90)){
            cout<<"\nEl valor que ingreso esta fuera de los parámetros, ingreselo nuevamente: ";
            cin>>FAF[i].selectF;}
                        break;
			 case 49: cout<<"\nAxis X: "<<FAF[i].setXaxis<<"\nNuevo dato: ";
                        cin>>FAF[i].setXaxis;
                        while((FAF[i].setXaxis<25)||(FAF[i].setXaxis>200)){
            cout<<"\nEl valor que ingreso esta fuera de los parámetros, ingreselo nuevamente: ";
            cin>>FAF[i].setXaxis;}
                        break;
			 case 50: cout<<"\nAxis Y: "<<FAF[i].setYaxis<<"\nNuevo dato: ";
                        cin>>FAF[i].setYaxis;
                        while((FAF[i].setYaxis<50)||(FAF[i].setYaxis>250)){
            cout<<"\nEl valor que ingreso esta fuera de los parámetros, ingreselo nuevamente: ";
            cin>>FAF[i].setYaxis;}
                        break;
			 case 51: cout<<"\nDesplazamiento del sprite en X: "<<FAF[i].addXsprite<<"\nNuevo dato: ";
                        cin>>FAF[i].addXsprite;
                        while((FAF[i].addXsprite<-1000)||(FAF[i].addXsprite>1000)){
            cout<<"\nEl valor que ingreso esta fuera de los parámetros, ingreselo nuevamente: ";
            cin>>FAF[i].addXsprite;}
                        break;
			 case 52:cout<<"\nSetear el sprite en X posicion: "<<FAF[i].setXsprite<<"\nNuevo dato: ";
                        cin>>FAF[i].setXsprite;
                        while((FAF[i].setXsprite<0)||(FAF[i].setXsprite>800)){
            cout<<"\nEl valor que ingreso esta fuera de los parámetros, ingreselo nuevamente: ";
            cin>>FAF[i].setXsprite;}
                        break;
			 case 53: cout<<"\nDesplazamiento del sprite en Y: "<<FAF[i].addYsprite<<"\nNuevo dato: ";
                        cin>>FAF[i].addYsprite;
                        while((FAF[i].addYsprite<-100)||(FAF[i].addYsprite>640)){
            cout<<"\nEl valor que ingreso esta fuera de los parámetros, ingreselo nuevamente: ";
            cin>>FAF[i].addYsprite;}
                        break;
			 case 54: cout<<"\nSetear el sprite en Y posicion: "<<FAF[i].setYsprite<<"\nNuevo dato: ";
                        cin>>FAF[i].setYsprite;
                        while((FAF[i].setYsprite<-100)||(FAF[i].setYsprite>640)){
            cout<<"\nEl valor que ingreso esta fuera de los parámetros, ingreselo nuevamente: ";
            cin>>FAF[i].setYsprite;}
                        break;
			 case 55: cout<<"\nAncho del frame (W): "<<FAF[i].w<<"\nNuevo dato: ";
                        cin>>FAF[i].w;
                        while((FAF[i].w<0)||(FAF[i].w>500)){
            cout<<"\nEl valor que ingreso esta fuera de los parámetros, ingreselo nuevamente: ";
            cin>>FAF[i].w;}
                        break;
             case 56:cout<<"\nAlto del frame (H): "<<FAF[i].h<<"\nNuevo dato: ";
                    cin>>FAF[i].h;
                    while((FAF[i].h<0)||(FAF[i].h>500)){
            cout<<"\nEl valor que ingreso esta fuera de los parámetros, ingreselo nuevamente: ";
            cin>>FAF[i].h;}
                        break;
			 case 57: cout<<"\nDesplazamiendo X al sig. frame: "<<FAF[i].addFrameX<<"\nNuevo dato: ";
                        cin>>FAF[i].addFrameX;
                        while((FAF[i].addFrameX<0)||(FAF[i].addFrameX>800)){
            cout<<"\nEl valor que ingreso esta fuera de los parámetros, ingreselo nuevamente: ";
            cin>>FAF[i].addFrameX;}
                        break;
			 case 113: cout<<"\nFinal de la tira de frames(X): "<<FAF[i].endFrameX<<"\nNuevo dato: ";
                        cin>>FAF[i].endFrameX;
                        while((FAF[i].endFrameX<0)||(FAF[i].endFrameX>10000)){
            cout<<"\nEl valor que ingreso esta fuera de los parámetros, ingreselo nuevamente: ";
            cin>>FAF[i].endFrameX;}
                        break;
			 case 119: cout<<"\nLa animacion se queda en un frame fijo (1/0): "<<FAF[i].frameFijo<<"\nNuevo dato: ";
                        cin>>FAF[i].frameFijo;
                        while((FAF[i].frameFijo<0)||(FAF[i].frameFijo>10000)){
            cout<<"\nEl valor que ingreso esta fuera de los parámetros, ingreselo nuevamente: ";
            cin>>FAF[i].frameFijo;}

			 case 27: a=1;
                      break;
			 default: cout<<"Opci¢n incorrecta. Presione una tecla para continuar";
                    getch();
                    break;
			}
		}
}

int FilePlayer::setCero(int i){
    FAF[i].selectF=88;
    FAF[i].setXaxis=0;
    FAF[i].setYaxis=0;
    FAF[i].addXsprite=0;
    FAF[i].setXsprite=0;
    FAF[i].addYsprite=0;
    FAF[i].setYsprite=0;
    FAF[i].w=0;
    FAF[i].h=0;
    FAF[i].addFrameX=0;
    FAF[i].endFrameX=0;
    FAF[i].frameFijo=0;
    return 0;
}

void FilePlayer::saveFile()
	{
	FILE *p;
	p=fopen(fileName,"wb");
	if(p==NULL){cout<<"\nNo se pudo guardar el archivo ("<<fileName<<"), intentelo nuevamente.";}
	fwrite(this,sizeof *this,1,p);
	fclose(p);
	}

int FilePlayer::loadFile()
	{
	int x;
	FILE *p;

	p=fopen(fileName,"rb");
	if(p==NULL)
		{
		return 0;
		}
	fseek(p,0,0);
	x=fread(this,sizeof *this,1,p);
	fclose(p);
	return x;
}
int FilePlayer::setFileName_and_load(){
	system("cls");
	cout<<"Ingrese nombre del PJ: ";
	cin>>nombre;
    strcpy(fileName, "../PJs/");
    strcat(fileName, nombre);
    strcat(fileName, "/");
    strcat(fileName, nombre);
    strcat(fileName, ".dat");
    if(!loadFile()){
        cout<<"\nNo se pudo abrir el archivo ("<<fileName<<"), intentelo nuevamente.";
        getch();
        return 0;
    }
    return 1;
}
int FilePlayer::mostrar(){
 int i = 0, keyPressed = 0;

    if(!setFileName_and_load()) return 0;

    system("cls");cout<<endl;
    cout<<setprecision(3);
    cout<<"Este archivo fue creado con la version de FilePlayerMaker: "<<fileVersion;
    cout<<"\nDireccion del archivo: "<<fileName;
    cout<<"\nPersonaje: "<<nombre;
    cout<<"\n\nDirecciones de los frames:\n";

    do{
        cout<<"Frame "<<i<<": "<<spr[i].frames<<endl;
        i++;
        if((i == 20)||(i == 40)||(i == 60)||(i == 80)){cout<<"\nPresione cualquier tecla para continuar.\n";getch();}
    }while((strcmp(spr[i].frames, "no hay mas direcciones") != 0)&&(i < 90));
    cout<<"\nPresione cualquier tecla para continuar.";
    getch();

    i = 0;
    cout<<"\nPara salir presione ESC\nInstancias para FullAction: ";
    do{
        cout<<"\n\nNumero: "<<i;
        cout<<"\nAccion: "<<FAF[i].nombreAccion;
        cout<<"\nTira de frames: "<<FAF[i].selectF;
        cout<<"\nAxis X: "<<FAF[i].setXaxis;
        cout<<"\nAxis Y: "<<FAF[i].setYaxis;
        cout<<"\nDesplasamiente del sprite en X: "<<FAF[i].addXsprite;
        cout<<"\nSetear sprite en posicion X: "<<FAF[i].setXsprite;
        cout<<"\nDesplasamiente del sprite en Y: "<<FAF[i].addYsprite;
        cout<<"\nSetear sprite en posicion Y: "<<FAF[i].setYsprite;
        cout<<"\nAncho del frame (W): "<<FAF[i].w;
        cout<<"\nAlto del frame (H): "<<FAF[i].h;
        cout<<"\nDesplasamiendo X al sig. frame: "<<FAF[i].addFrameX;
        cout<<"\nFinal de la tira de frames(X): "<<FAF[i].endFrameX;
        cout<<"\nLa animacion se queda en un frame fijo (1/0): "<<FAF[i].frameFijo;
        keyPressed = getch();
        i++;
        if(i == 100) cout<<"\n\nFin de instancias.";
        if(keyPressed == 97) cin>>i;
    }while((keyPressed != 27)&&(i<100));
    cout<<"\n\nPresione cualquier tecla para continuar.\n";
    getch();
    return 0;
}
void FilePlayer::crear(){
 int i = 0;
    system("cls");cout<<endl;
    fileVersion = FilePlayer_version;     // << modificar # a medida avance de version
    cout<<"Nombre del PJ: ";
    cin>>nombre;
    strcpy(fileName, "../PJs/");
    strcat(fileName, nombre);
    strcat(fileName, "/");
    strcat(fileName, nombre);
    strcat(fileName, ".dat");
    cout<<"\nIngrese las direcciones de los sprites del PJ (0 para salir)\n";

    do{
        cout<<"Frame "<<i<<": ";
        cin>>(spr[i].frames);
        i++;
    }while(strcmp(spr[i-1].frames, "0") != 0);
    strcpy(spr[i-1].frames, "no hay mas direcciones");
    saveFile();
}
int FilePlayer::modifFAF(){
 int i = 0, dato, check, j;
 char nuevoDato[20];
 system("cls");cout<<endl;
    if(!setFileName_and_load())return 0;
    while(1){
        cout<<"****************************************************************"<<endl;
        cout<<"- Igrese -1 para salir."<<endl;
        cout<<"****************************************************************"<<endl;
        cout<<"- Ingrese -2 para modificar el FullAction de un PJ entero."<<endl;
        cout<<"****************************************************************"<<endl<<endl;
        cout<<"Ingrese la posicion del vector que quiere modificar: ";
        cin>>i;
        if(i == -1) break;
        if(i == -2){
            cout<<"Ingrese la posicion desde la cual quiere setear todo en '0':"<<endl;
            cin>>dato;
            while((dato<0)||(dato>90)){
                cout<<"El valor que ingreso no puede ser procesado, ingreselo nuevamente: ";
                cin>>dato;
            }
            cout<<"Esta seguro de que desea realizar esta accion? (1= si/0= no):"<<endl;
            cin>>check;
            while((check!=0)&&(check!=1)){
                cout<<"El valor que ingreso no puede ser procesado, ingreselo nuevamente: ";
                cin>>check;
            }
            if(check == 1){
                for(j=dato;j<=101;j++){
                    setCero(j);
            }break;}
            else{
                continue;}
            }

        cout<<"\n\nNumero: "<<i;
        cout<<"\nAccion: "<<FAF[i].nombreAccion<<endl;

        cout<<"***********************************************************************"<<endl;
        cout<<"Si desea modificar esta accion Ingrese 's'."<<endl;
        cout<<"***********************************************************************"<<endl;
        cout<<"Si desea settear todos los valores en '0' o equivalente ingrese 'c'."<<endl;
        cout<<"***********************************************************************"<<endl;
        cout<<"Si desea modificar algun valor en particular, ingrese 'm'."<<endl;
        cout<<"***********************************************************************"<<endl;
        cout<<"Si desea salir, ingrese 'n'."<<endl;
        cin>>nuevoDato;

        if(strcmp(nuevoDato, "m") == 0){
            menuFAF(i);
            break;}

        if(strcmp(nuevoDato, "c") == 0){
            setCero(i);
            break;}

        if(strcmp(nuevoDato, "n") == 0) continue; //vuelve al inicio del while

        cout<<"\nDesea cambiarle el nombre? s/n: ";
        cin>>nuevoDato;
        if(strcmp(nuevoDato, "s") == 0){
            cout<<"\nNuevo nombre de la accion: ";
            cin>>nuevoDato;
            strcpy(FAF[i].nombreAccion, nuevoDato);
        }
        cout<<"\nTira de frames: "<<FAF[i].selectF<<"\nNuevo dato: ";
        cin>>FAF[i].selectF;
        while((FAF[i].selectF<0)||(FAF[i].selectF>90)){
            cout<<"\nEl valor que ingreso esta fuera de los parámetros, ingreselo nuevamente: ";
            cin>>FAF[i].selectF;}
        cout<<"\nAxis X: "<<FAF[i].setXaxis<<"\nNuevo dato: ";
        cin>>FAF[i].setXaxis;
        while((FAF[i].setXaxis<(-200))||(FAF[i].setXaxis>200)){
            cout<<"\nEl valor que ingreso esta fuera de los parámetros, ingreselo nuevamente: ";
            cin>>FAF[i].setXaxis;}
        cout<<"\nAxis Y: "<<FAF[i].setYaxis<<"\nNuevo dato: ";
        cin>>FAF[i].setYaxis;
        while((FAF[i].setYaxis<(-200))||(FAF[i].setYaxis>250)){
            cout<<"\nEl valor que ingreso esta fuera de los parámetros, ingreselo nuevamente: ";
            cin>>FAF[i].setYaxis;}
        cout<<"\nDesplazamiento del sprite en X: "<<FAF[i].addXsprite<<"\nNuevo dato: ";
        cin>>FAF[i].addXsprite;
        while((FAF[i].addXsprite<-1000)||(FAF[i].addXsprite>1000)){
            cout<<"\nEl valor que ingreso esta fuera de los parámetros, ingreselo nuevamente: ";
            cin>>FAF[i].addXsprite;}
        cout<<"\nSetear el sprite en X posicion: "<<FAF[i].setXsprite<<"\nNuevo dato: ";
        cin>>FAF[i].setXsprite;
        while((FAF[i].setXsprite<0)||(FAF[i].setXsprite>800)){
            cout<<"\nEl valor que ingreso esta fuera de los parámetros, ingreselo nuevamente: ";
            cin>>FAF[i].setXsprite;}
        cout<<"\nDesplazamiento del sprite en Y: "<<FAF[i].addYsprite<<"\nNuevo dato: ";
        cin>>FAF[i].addYsprite;
        while((FAF[i].addYsprite<-100)||(FAF[i].addYsprite>640)){
            cout<<"\nEl valor que ingreso esta fuera de los parámetros, ingreselo nuevamente: ";
            cin>>FAF[i].addYsprite;}
        cout<<"\nSetear el sprite en Y posicion: "<<FAF[i].setYsprite<<"\nNuevo dato: ";
        cin>>FAF[i].setYsprite;
        while((FAF[i].setYsprite<-100)||(FAF[i].setYsprite>640)){
            cout<<"\nEl valor que ingreso esta fuera de los parámetros, ingreselo nuevamente: ";
            cin>>FAF[i].setYsprite;}
        cout<<"\nAncho del frame (W): "<<FAF[i].w<<"\nNuevo dato: ";
        cin>>FAF[i].w;
        while((FAF[i].w<0)||(FAF[i].w>500)){
            cout<<"\nEl valor que ingreso esta fuera de los parámetros, ingreselo nuevamente: ";
            cin>>FAF[i].w;}
        cout<<"\nAlto del frame (H): "<<FAF[i].h<<"\nNuevo dato: ";
        cin>>FAF[i].h;
        while((FAF[i].h<0)||(FAF[i].h>500)){
            cout<<"\nEl valor que ingreso esta fuera de los parámetros, ingreselo nuevamente: ";
            cin>>FAF[i].h;}
        cout<<"\nDesplasamiendo X al sig. frame: "<<FAF[i].addFrameX<<"\nNuevo dato: ";
        cin>>FAF[i].addFrameX;
        while((FAF[i].addFrameX<0)||(FAF[i].addFrameX>800)){
            cout<<"\nEl valor que ingreso esta fuera de los parámetros, ingreselo nuevamente: ";
            cin>>FAF[i].addFrameX;}
        cout<<"\nFinal de la tira de frames(X): "<<FAF[i].endFrameX<<"\nNuevo dato: ";
        cin>>FAF[i].endFrameX;
        while((FAF[i].endFrameX<0)||(FAF[i].endFrameX>10000)){
            cout<<"\nEl valor que ingreso esta fuera de los parámetros, ingreselo nuevamente: ";
            cin>>FAF[i].endFrameX;}
        cout<<"\nLa animacion se queda en un frame fijo (1/0): "<<FAF[i].frameFijo<<"\nNuevo dato: ";
        cin>>FAF[i].frameFijo;
        while((FAF[i].frameFijo<0)||(FAF[i].frameFijo>10000)){
            cout<<"\nEl valor que ingreso esta fuera de los parámetros, ingreselo nuevamente: ";
            cin>>FAF[i].frameFijo;}
        }

    saveFile();
    puts("\nArchivo modificado con exito");
    getch();
    return 0;
}
int FilePlayer::modifCR(){
 int i = 0, a, e;
 char letra, nuevoDato[20];

 system("cls");cout<<endl;

    if(!setFileName_and_load()) return 0;

    cout<<"Nombre del PJ: "<<nombre;

    do{
        cout<<"\n\n- Igrese -1 para salir.\n\nIngrese la posicion del vector que quiere modificar(0 a 29): ";
        cin>>i;
        if(i == -1) break;
        cout<<"\n\nNumero: "<<i;
        cout<<endl<<spr[i].frames;
        cout<<"\n\nDesea modificar las colisiones para este sprite? s/n: ";
        cin>>letra;
        if(letra == 'n') continue; //vuelve al inicio del while

        cout<<"Desea modificar un cuadro de ataque o de vulnerabilid(a a v): ";
        cin>>letra;
        cout<<"Numero de cuadro dentro del sprite(0 a 9): ";
        cin>>a;
        cout<<"Numero de Colition Rect (0 a 5): ";
        cin>>e;
        if(letra == 'a'){
            cout<<"\natackCR.\n Activo: "<<spr[i].atackCR[a][e].activo;
            cout<<"\n X: "<<spr[i].atackCR[a][e].x;
            cout<<"\n Y: "<<spr[i].atackCR[a][e].y;
            cout<<"\n W: "<<spr[i].atackCR[a][e].w;
            cout<<"\n H: "<<spr[i].atackCR[a][e].h;

            cout<<"\nDesea modificar? s/n: ";
            cin>>nuevoDato;
            if(strcmp(nuevoDato, "s") == 0){

                cout<<"\n\nNuevos valores.\n Activo: ";
                cin>>spr[i].atackCR[a][e].activo;
                cout<<" X: ";
                cin>>spr[i].atackCR[a][e].x;
                cout<<" Y: ";
                cin>>spr[i].atackCR[a][e].y;
                cout<<" W: ";
                cin>>spr[i].atackCR[a][e].w;
                cout<<" H: ";
                cin>>spr[i].atackCR[a][e].h;
            }
            continue;
        }if(letra == 'v'){
            cout<<"\nvulnerableCR.\n Activo: "<<spr[i].vulnerableCR[a][e].activo;
            cout<<"\n X: "<<spr[i].vulnerableCR[a][e].x;
            cout<<"\n Y: "<<spr[i].vulnerableCR[a][e].y;
            cout<<"\n W: "<<spr[i].vulnerableCR[a][e].w;
            cout<<"\n H: "<<spr[i].vulnerableCR[a][e].h;

            cout<<"\nDesea modificar? s/n: ";
            cin>>nuevoDato;
            if(strcmp(nuevoDato, "s") == 0){
                cout<<"\n\nNuevos valores.\n Activo: ";
                cin>>spr[i].vulnerableCR[a][e].activo;
                cout<<" X: ";
                cin>>spr[i].vulnerableCR[a][e].x;
                cout<<" Y: ";
                cin>>spr[i].vulnerableCR[a][e].y;
                cout<<" W: ";
                cin>>spr[i].vulnerableCR[a][e].w;
                cout<<" H: ";
                cin>>spr[i].vulnerableCR[a][e].h;
            }
            continue;
        }
        cout<<"\nIngreso una letra equivocada.";
    }while(1);
    saveFile();
    return 0;
}

int FilePlayer::modifDir(){
 int i = 0, dato, check, j;
 char valor[0];
 char nuevoDato[100];
 system("cls");cout<<endl;

    if(!setFileName_and_load()) return 0;

    cout<<"Nombre del PJ: "<<nombre<<endl;

    do{
        cout<<"*****************************************************************************"<<endl;
        cout<<"- Ingrese -1 para salir."<<endl;
        cout<<"*****************************************************************************"<<endl;
        cout<<"- Ingrese 0 en el campo \"Nueva direccion\" para conservar la vieja direccion."<<endl;
        cout<<"*****************************************************************************"<<endl;
        cout<<"- Ingrese -2 si desea poner en default varias direcciones de sprites."<<endl;
        cout<<"*****************************************************************************"<<endl<<endl;
        cout<<"- Ingrese la opcion deseada o el numero de cuadro (frame) a modificar: ";
        cin>>i;
        if(i == -1) break;
        if(i == -2){
            system("cls");
            cout<<"Ingrese desde que posicion desea modificar las direcciones: "<<endl;
            cin>>dato;
            cout<<"Ingrese el valor que desea que se ponga en las variables ('a' o 's')"<<endl;
            cin>>valor;
            cout<<"Esta seguro de que desea realizar esta accion? (1= si/0= no)"<<endl;
            cin>>check;
            if(check == 1){
                for(j=dato;j<=90;j++)
                    strcpy(spr[j].frames, valor);

                cout<<"Archivo modificado exitosamente";
                getch();
                saveFile();
                getch();
                break;
            }else
                break;

        }
        cout<<"\nPosicion "<<i<<endl;
        cout<<"\nDireccion actual: "<<spr[i].frames<<endl;
        cout<<"\nIngrese la Nueva direccion: ";
        cin>>nuevoDato;
        if(strcmp(nuevoDato, "0") != 0) strcpy(spr[i].frames, nuevoDato);
        cout<<"Ok\n";
    }while(1);
    saveFile();
    return 0;
}

int FilePlayer::modifAxis(){
 int i = 0;
 char nuevoDato[20];
 system("cls");cout<<endl;

    if(!setFileName_and_load())return 0;

    while(1){
        cout<<"\n\n- Igrese -1 para salir.\n\nIngrese la posicion del vector que quiere modificar: ";
        cin>>i;
        if(i == -1) break;
        cout<<"\n\nNumero: "<<i;
        cout<<"\nAccion: "<<FAF[i].nombreAccion;

        cout<<"\nEs esta la accion que desea modificar? s/n: ";
        cin>>nuevoDato;
        if(strcmp(nuevoDato, "n") == 0) continue; //vuelve al inicio del while

        cout<<"\nAxis X: "<<FAF[i].setXaxis<<"\nNuevo dato: ";
        cin>>FAF[i].setXaxis;
        cout<<"\nAxis Y: "<<FAF[i].setYaxis<<"\nNuevo dato: ";
        cin>>FAF[i].setYaxis;
    }
    saveFile();
    puts("\nArchivo modificado con exito");
    getch();
    return 0;
}
///*****************************
struct OLD_Sprite{
    char frames[100];// path de 100 caracteres
    ColitionRect atackCR[10][6]; //cuadros rojos
    ColitionRect vulnerableCR[10][6]; //cuadros azules

    ColitionRect *getCRa(){return &atackCR[0][0];};
    ColitionRect *getCRv(){return &vulnerableCR[0][0];};
};
class OLD_FilePlayer{
    public:
        float fileVersion;
        char fileName[100];
		char nombre[20];
		OLD_Sprite spr[30];
		FullActionFile FAF[30];

        int setFileName_and_load();
        int loadFile();
        char *getFileName(){return fileName;};

};
int OLD_FilePlayer::loadFile()
	{
	int x;
	FILE *p;

	p=fopen(fileName,"rb");
	if(p==NULL)
		{
		return 0;
		}
	fseek(p,0,0);
	x=fread(this,sizeof *this,1,p);
	fclose(p);
	return x;
}
int OLD_FilePlayer::setFileName_and_load(){
	system("cls");
	cout<<"Ingrese nombre del PJ: ";
	cin>>nombre;
    strcpy(fileName, "../PJs/");
    strcat(fileName, nombre);
    strcat(fileName, "/");
    strcat(fileName, nombre);
    strcat(fileName, ".dat");
    if(!loadFile()){
        cout<<"\nNo se pudo abrir el archivo ("<<fileName<<"), intentelo nuevamente.";
        getch();
        return 0;
    }
    return 1;
}
///******************************************
int FilePlayer::actualizar(){
 int i = 0, fin;
 OLD_FilePlayer fp; // cambiar a clase vieja

    cout<<endl;
    cout<<"Se hara una actualizacion de un FilePlayer a la version: "<<FilePlayer_version;
    fileVersion = FilePlayer_version;     // << modificar # a medida avance de version
    if(!fp.setFileName_and_load())return 0;
    setFileName(fp.getFileName());
    cout<<"\nHasta que numero de vector se debe compiar las direcciones de los sprites (-1 para salir): ";
    cin>>fin;
    if(fin == -1) return 0;
    do{
        cout<<"Frame "<<i<<": "<<fp.spr[i].frames;
        strcpy(spr[i].frames, fp.spr[i].frames);
        i++;
        if(i == fin) break;
        if(i == 20){cout<<"\nPresione cualquier tecla para continuar.\n";getch();}
    }while(strcmp(spr[i-1].frames, "no hay mas direcciones") != 0);
///////////////FAF
 i = 0;
 cout<<endl;

    do{
        cout<<"\n\nNumero: "<<i;
        cout<<"\nAccion: "<<fp.FAF[i].nombreAccion;
        strcpy(FAF[i].nombreAccion, fp.FAF[i].nombreAccion);

        cout<<"\nTira de frames: "<<fp.FAF[i].selectF;
        FAF[i].selectF = fp.FAF[i].selectF;;

        cout<<"\nAxis X: "<<fp.FAF[i].setXaxis;
        FAF[i].setXaxis = fp.FAF[i].setXaxis;
        cout<<"\nAxis Y: "<<fp.FAF[i].setYaxis;
        FAF[i].setYaxis = fp.FAF[i].setYaxis;

        cout<<"\nDesplasamiente del sprite en X: "<<fp.FAF[i].addXsprite;
        FAF[i].addXsprite = fp.FAF[i].addXsprite;
        cout<<"\nSetear el sprite en X posicion: "<<fp.FAF[i].setXsprite;
        FAF[i].setXsprite = fp.FAF[i].setXsprite;
        cout<<"\nDesplasamiente del sprite en Y: "<<fp.FAF[i].addYsprite;
        FAF[i].addYsprite = fp.FAF[i].addYsprite;
        cout<<"\nSetear el sprite en Y posicion: "<<fp.FAF[i].setYsprite;
        FAF[i].setYsprite = fp.FAF[i].setYsprite;
        cout<<"\nAncho del frame (W): "<<fp.FAF[i].w;
        FAF[i].w = fp.FAF[i].w;
        cout<<"\nAlto del frame (H): "<<fp.FAF[i].h;
        FAF[i].h = fp.FAF[i].h;
        cout<<"\nDesplasamiendo X al sig. frame: "<<fp.FAF[i].addFrameX;
        FAF[i].addFrameX = fp.FAF[i].addFrameX;
        cout<<"\nFinal de la tira de frames(X): "<<fp.FAF[i].endFrameX;
        FAF[i].endFrameX = fp.FAF[i].endFrameX;
        cout<<"\nLa animacion se queda en un frame fijo: ";
        if(fp.FAF[i].frameFijo) cout<<"True";
        else cout<<"False";
        FAF[i].frameFijo = fp.FAF[i].frameFijo;
        i++;
    }while(i < 30);

    puts("\n\nInstancias modificadas con exito");
    getch();




//////////////////////CR
 int a, e;

 cout<<endl;
        cout<<"Copiando Colition Rects";
    for(i = 0; i < 29; i++){
        if(strcmp(fp.spr[i].frames,"no hay mas direcciones") == 0) break;

        for(a = 0; a < 10; a++){
            for(e = 0; e < 6; e++){
                spr[i].atackCR[a][e].activo = fp.spr[i].atackCR[a][e].activo;
                spr[i].atackCR[a][e].x = fp.spr[i].atackCR[a][e].x;
                spr[i].atackCR[a][e].y = fp.spr[i].atackCR[a][e].y;
                spr[i].atackCR[a][e].w = fp.spr[i].atackCR[a][e].w;
                spr[i].atackCR[a][e].h = fp.spr[i].atackCR[a][e].h;
            }
        }
        for(a = 0; a < 10; a++){
            for(e = 0; e < 6; e++){
                spr[i].vulnerableCR[a][e].activo = fp.spr[i].vulnerableCR[a][e].activo;
                spr[i].vulnerableCR[a][e].x = fp.spr[i].vulnerableCR[a][e].x;
                spr[i].vulnerableCR[a][e].y = fp.spr[i].vulnerableCR[a][e].y;
                spr[i].vulnerableCR[a][e].w = fp.spr[i].vulnerableCR[a][e].w;
                spr[i].vulnerableCR[a][e].h = fp.spr[i].vulnerableCR[a][e].h;
            }
        }
    }
    saveFile();
    puts("\n\nArchivo actualizado con exito");
    getch();
    return 0;
}
