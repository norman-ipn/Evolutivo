
/*
    int UP = 273;
    int DOWN = 274;
    int LEFT = 276;
    int RIGHT = 275;
    int BUTTON0 = 257;
    int BUTTON1 = 258;
    int BUTTON2 = 259;
    int BUTTON3 = 261;

    int BUTTON4;
    int BUTTON5;
    int BUTTON6;
    int BUTTON7 = 262;

    int UP = 119;
    int DOWN = 115;
    int LEFT = 97;
    int RIGHT = 100;
    int BUTTON0 = 107;
    int BUTTON1 = 106;
    int BUTTON2 = 108
    int BUTTON3 = 105;

    int BUTTON4;
    int BUTTON5;
    int BUTTON6;
    int BUTTON7 = 111;
*/
class KeysFile{
 private:
    char fileName[100];
    int DOWN;
    int UP;
    int LEFT;
    int RIGHT;
    int BUTTON0;
    int BUTTON1;
    int BUTTON2;
    int BUTTON3;
    int BUTTON4;
    int BUTTON5;
    int BUTTON6;
    int BUTTON7;

    int life;
    int speed;
    int musicVolume;
    int soundsVolume;
    int roundsDuration;
    int rounds;

 public:
    void crear();
    void saveFile();
    int menuTeclas();
    int menuModificacionTeclas();
    int loadFile();
    int setKeyfileName_and_load();
    void setFileName(char *n){strcpy(fileName, n);};
    int mostrar();

    int getDOWN(){return DOWN;}
    int getUP(){return UP;}
    int getLEFT(){return LEFT;}
    int getRIGHT(){return RIGHT;}
    int getBUTTON0(){return BUTTON0;}
    int getBUTTON1(){return BUTTON1;}
    int getBUTTON2(){return BUTTON2;}
    int getBUTTON3(){return BUTTON3;}
    int getBUTTON4(){return BUTTON4;}
    int getBUTTON5(){return BUTTON5;}
    int getBUTTON6(){return BUTTON6;}
    int getBUTTON7(){return BUTTON7;}

    int modifLife();
    int modifSpeed();
    int modifMvolume();
    int modifSvolume();
    int modifRounds();
    int modifRoundsDuration();

    int setLife(int x){life = x;}
    int setSpeed(int x){speed = x;}
    int setMvolume(int x){musicVolume = x;}
    int setSvolume(int x){soundsVolume = x;}
    int setRounds(int x){rounds = x;}
    int setRoundsDuration(int x){roundsDuration = x;}
    int getLife(){return life;}
    int getSpeed(){return speed;}
    int getMvolume(){return musicVolume;}
    int getSvolume(){return soundsVolume;}
    int getRounds(){return rounds;}
    int getRoundsDuration(){return roundsDuration;}

    char *modLife();
    char *modSpeed();
    char *modMvolume();

 ~KeysFile(){};
};

char *KeysFile::modLife()
{
    life += 50;
    if( life > 300 ) life = 50;
    strcpy( fileName, "config.dat" );
    saveFile();
    char cadena[3];
    itoa( life, cadena, 10 );
    return cadena;
}
char *KeysFile::modSpeed()
{
    speed += 10;
    if( speed > 150 ) speed = 50;
    strcpy( fileName, "config.dat" );
    saveFile();
    char cadena[3];
    itoa( speed, cadena, 10 );
    return cadena;
}
char *KeysFile::modMvolume()
{
    musicVolume += 16;
    if( musicVolume > 128 ) musicVolume = 0;
    strcpy( fileName, "config.dat" );
    saveFile();
    char cadena[3];
    itoa( musicVolume, cadena, 10 );
    return cadena;
}
int KeysFile::menuTeclas(){
    int opc;
    while(1){
        system("cls");
        cout<<"************************************************************"<<endl;
        cout<<"Menu de Teclas del juego"<<endl;
        cout<<"************************************************************"<<endl<<endl;
        cout<<"(0) - Abrir\n";
        cout<<"(1) - Crear nuevo archivo de teclas"<<endl;
        cout<<"(2) - Configuracion de teclas"<<endl;
        cout<<"(3) - Mostrar configuracion de teclas"<<endl;
        cout<<"\n(4) - Vida";
        cout<<"\n(5) - Speed";
        cout<<"\n(6) - Music Volume";
        cout<<"\n(7) - Sounds Volume";
        cout<<"\n(8) - Rounds";
        cout<<"\n(9) - Duracion de rounds";
        cout<<"\nESC - Vorver a menu principal";

        opc=getch();
        switch(opc){
            case 48: setKeyfileName_and_load(); break;
            case 49: crear(); break;
            case 50: menuModificacionTeclas(); break;
            case 51: mostrar(); break;
            case 52: modifLife(); break;
            case 53: modifSpeed(); break;
            case 54: modifMvolume(); break;
            case 55: modifSvolume(); break;
            case 56: modifRounds(); break;
            case 57: modifRoundsDuration(); break;
            case 27: return 0;
            default:
                cout<<"La opcion seleccionada es inexistente, seleccionela nuevamente: ";
                opc=getch();
        }
    }
}

int KeysFile::menuModificacionTeclas(){
    int check;
    if(!setKeyfileName_and_load())return 0;
    while(1){
        system("cls");
        cout<<"**************************************************************************"<<endl;
        cout<<"Desea modificar una tecla en particular o todas? (1= una tecla/0= todas)"<<endl;
        cout<<"Para salir ingrese -1"<<endl;
        cout<<"**************************************************************************"<<endl;
        cin>>check;
        while((check != 1) && (check != 0) && (check != -1)){
            cout<<"El dato que ingreso es incorrecto, ingreselo nuevamente: ";
            cin>>check;
        }
        if(check == 0)break;//  menuModificacionTeclas();
        if(check == 1){
            cout<<"Ingrese el valor para la accion 'UP': "<<endl;
            cin>>UP;
            cout<<"Ingrese el valor para la accion 'DOWN': "<<endl;
            cin>>DOWN;
            cout<<"Ingrese el valor para la accion 'LEFT': "<<endl;
            cin>>LEFT;
            cout<<"Ingrese el valor para la accion 'RIGHT': "<<endl;
            cin>>RIGHT;
            cout<<"Ingrese el valor para la accion 'BUTTON0': "<<endl;
            cin>>BUTTON0;
            cout<<"Ingrese el valor para la accion 'BUTTON1': "<<endl;
            cin>>BUTTON1;
            cout<<"Ingrese el valor para la accion 'BUTTON2': "<<endl;
            cin>>BUTTON2;
            cout<<"Ingrese el valor para la accion 'BUTTON3': "<<endl;
            cin>>BUTTON3;
            cout<<"Ingrese el valor para la accion 'BUTTON4': "<<endl;
            cin>>BUTTON4;
            cout<<"Ingrese el valor para la accion 'BUTTON5': "<<endl;
            cin>>BUTTON5;
            cout<<"Ingrese el valor para la accion 'BUTTON6': "<<endl;
            cin>>BUTTON6;
            cout<<"Ingrese el valor para la accion 'BUTTON7': "<<endl;
            cin>>BUTTON7;
            break;
        }
        if(check == -1){return 0;}
    }
    saveFile();
    return 0;
}

int KeysFile::loadFile(){
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

int KeysFile::setKeyfileName_and_load(){
 char nombre[20];
	system("cls");
	cout<<"Ingrese el nombre del archivo: ";
	cin>>nombre;
    strcpy(fileName, "../");
    strcat(fileName, nombre);
    strcat(fileName, ".dat");
    if(!loadFile()){
        cout<<"\nNo se pudo abrir el archivo ("<<fileName<<"), intentelo nuevamente.";
        getch();
        return 0;
    }
    return 1;
}

void KeysFile::saveFile(){
	FILE *p;
	p=fopen(fileName,"wb");
	if(p==NULL)
	    cout<<"\nNo se pudo guardar el archivo ("<<fileName<<"), intentelo nuevamente.";
    else
        fwrite(this,sizeof *this,1,p);
	fclose(p);
	}

void KeysFile::crear(){
 char nombre[20];
    int i = 0;
    system("cls");cout<<endl;
    cout<<"Nombre del archivo: ";
    cin>>nombre;
    strcpy(fileName, "../");
    strcat(fileName, nombre);
    strcat(fileName, ".dat");
    saveFile();
    cout<<"Archivo creado con exito";
    getch();
    menuModificacionTeclas();
}
int KeysFile::mostrar(){

    if(!setKeyfileName_and_load())return 0;

        system("cls");
        cout<<"**************************************************************************"<<endl;
        cout<<"para volver presione cualkier tecla"<<endl;
        cout<<"**************************************************************************"<<endl;

            cout<<"\nUP: "<<UP;
            cout<<"\nDOWN: "<<DOWN;
            cout<<"\nLEFT: "<<LEFT;
            cout<<"\nRIGHT: "<<RIGHT;
            cout<<"\nBUTTON0: "<<BUTTON0;
            cout<<"\nBUTTON1: "<<BUTTON1;
            cout<<"\nBUTTON2: "<<BUTTON2;
            cout<<"\nBUTTON3: "<<BUTTON3;
            cout<<"\nBUTTON4: "<<BUTTON4;
            cout<<"\nBUTTON5: "<<BUTTON5;
            cout<<"\nBUTTON6: "<<BUTTON6;
            cout<<"\nBUTTON7: "<<BUTTON7;
        getch();
    return 0;
}
int KeysFile::modifLife(){

    cout<<"\nLife: "<<life;
    cout<<"\n Quiere cambiar este valor? (s/n): ";

    if( getch() == 's' ){
        cout<<"s\n";
        cout<<"\nLife: ";
        cin>>life;
        saveFile();
    }
}
int KeysFile::modifSpeed(){

    cout<<"\nSpeed: "<<speed;
    cout<<"\n Quiere cambiar este valor? (s/n): ";

    if( getch() == 's' ){
        cout<<"s\n";
        cout<<"\nSpeed: ";
        cin>>speed;
        saveFile();
    }
}
int KeysFile::modifMvolume(){

    cout<<"\nMusic Volume: "<<musicVolume;
    cout<<"\n Quiere cambiar este valor? (s/n): ";

    if( getch() == 's' ){
        cout<<"s\n";
        cout<<"\nMusic Volume: ";
        cin>>musicVolume;
        saveFile();
    }
}
int KeysFile::modifSvolume(){

    cout<<"\nSounds Volume: "<<soundsVolume;
    cout<<"\n Quiere cambiar este valor? (s/n): ";

    if( getch() == 's' ){
        cout<<"s\n";
        cout<<"\nSounds Volume: ";
        cin>>soundsVolume;
        saveFile();
    }
}
int KeysFile::modifRounds(){

    cout<<"\nRounds: "<<rounds;
    cout<<"\n Quiere cambiar este valor? (s/n): ";

    if( getch() == 's' ){
        cout<<"s\n";
        cout<<"\nRounds: ";
        cin>>rounds;
        saveFile();
    }
}
int KeysFile::modifRoundsDuration(){

    cout<<"\nRounds Duration: "<<roundsDuration;
    cout<<"\n Quiere cambiar este valor? (s/n): ";

    if( getch() == 's' ){
        cout<<"s\n";
        cout<<"\nRounds Duration: ";
        cin>>roundsDuration;
        saveFile();
    }
}
