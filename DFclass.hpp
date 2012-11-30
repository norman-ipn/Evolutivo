#ifndef DFCLASS_HPP_INCLUDED
#define DFCLASS_HPP_INCLUDED

class DataFile{
 private:
    char direcciones[100][100];
    char fileName[20];
    char nombre[20];

 public:
    void crear();
    int clearData(char *valor, int i);
    int mostrar();
    int modifDir();
    char* getDir(int i){return direcciones[i];}
    char* getFileName(){return fileName;};
    void setFileName(char *n){strcpy(fileName, n);};
    int setFileName_and_load();
    int loadFile();
    void saveFile();
    //int copyFromFP();
 ~DataFile(){};
};

int DataFile::clearData(char *valor, int pos){
        strcpy(direcciones[pos], valor);
        return 0;
}

void DataFile::crear(){
 int i = 0;
    system("cls");cout<<endl;
    cout<<"Nombre: ";
    cin>>nombre;
    strcpy(fileName, "../PJs/");
    strcat(fileName, nombre);
    strcat(fileName, "/");
    strcat(fileName, nombre);
    strcat(fileName, ".dat");
    cout<<"\nIngrese las direcciones de los archivos (0 para salir)\n";

    do{
        cout<<"Dir "<<i<<": ";
        cin>>(direcciones[i]);
        i++;
    }while(strcmp(direcciones[i-1], "0") != 0);
    strcpy(direcciones[i-1], "no hay mas direcciones");
    saveFile();
}
void DataFile::saveFile()
	{
	FILE *p;
	p=fopen(fileName,"wb");
	if(p==NULL){cout<<"\nNo se pudo guardar el archivo ("<<fileName<<"), intentelo nuevamente.";}
	fwrite(this,sizeof *this,1,p);
	fclose(p);
	}

int DataFile::loadFile()
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
int DataFile::setFileName_and_load(){
 char nombre[20];
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
int DataFile::modifDir(){
 int i = 0, dato, check, j;
 char valor[0];
 char nuevoDato[100];
 system("cls");cout<<endl;
    if(!setFileName_and_load())return 0;
    do{
        cout<<"******************************************************************************"<<endl;
        cout<<"- Ingrese -1 para salir."<<endl;
        cout<<"******************************************************************************"<<endl;
        cout<<"- Ingrese 0 en el campo \"Nueva direccion\" para conservar la vieja direccion."<<endl;
        cout<<"******************************************************************************"<<endl;
        cout<<"- Ingrese -2 si desea poner en default varias direcciones de sprites."<<endl;
        cout<<"******************************************************************************"<<endl<<endl;
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
                for(j=dato;j<=90;j++){
                    clearData(valor, j);
                }
                cout<<"Archivo modificado exitosamente";
                saveFile();
                break;
            }else{
                break;
            }
        }
        cout<<"\nPosicion "<<i<<endl;
        cout<<"\nDireccion actual: "<<direcciones[i]<<endl;
        cout<<"\nIngrese la Nueva direccion: ";
        cin>>nuevoDato;
        if(strcmp(nuevoDato, "0") != 0) strcpy(direcciones[i], nuevoDato);
        cout<<"Ok\n";
    }while(1);
    saveFile();
    return 0;
}
int DataFile::mostrar(){
 int i = 0;

    if(!setFileName_and_load()) return 0;

    system("cls");cout<<endl;
    cout<<setprecision(3);
    cout<<"\nDireccion del archivo: "<<fileName<<endl;
    cout<<"\nNombre: "<<nombre<<endl;
    cout<<"\n\nDirecciones:\n";
    do{
        cout<<"Dir "<<i<<": "<<direcciones[i]<<endl;
        i++;
        if((i == 20)||(i == 40)||(i == 60)||(i == 80)){
            cout<<"\nPresione cualquier tecla para continuar.\n";
            getch();}
    }while((strcmp(direcciones[i], "no hay mas direcciones") != 0)&&(i < 90));
    cout<<"\nPresione cualquier tecla para continuar.";
    getch();
 return 0;
}
/*
int DataFile::copyFromFP(){
 int i = 0, fin;
 FilePlayer fp; // cambiar a clase vieja

    cout<<endl;
    cout<<"Se hara una copia de un FilePlayer a un DataFile: ";
    if(!fp.setFileName_and_load())return 0;
    setFileName(fp.getFileName());
    cout<<"\nHasta que numero de vector se debe compiar las direcciones(-1 para salir): ";
    cin>>fin;
    if(fin == -1) return 0;
    do{
        cout<<"Dir "<<i<<": "<<fp.spr[i].frames;
        strcpy(direcciones[i], fp.spr[i].frames);
        i++;
        if(i == fin) break;
        if(i == 20){cout<<"\nPresione cualquier tecla para continuar.\n";getch();}
    }while(strcmp(direcciones[i-1], "no hay mas direcciones") != 0);

    saveFile();
    puts("\n\nArchivo copiado con exito");
    getch();
}*/


class DataPassFile{
 private:
    int dato[3];
    char cadena[100];
    char fileName[25];

 public:
    char* getCadena(){return cadena;}
    char* getFileName(){return fileName;}
    void setFileName(char *n){strcpy(fileName, n);}
    void setCadena(char *n, int i){strcpy(cadena, n);}
    int loadFile();
    void saveFile();

 //DataPassFile(){dato[0]=dato[1]=dato[2]=0; strcpy(cadena[0], "");strcpy(cadena[1], "");strcpy(cadena[2], ""); strcpy(fileName, "");}
 ~DataPassFile(){};
};

void DataPassFile::saveFile()
	{
	FILE *p;
	p=fopen(fileName,"wb");
	if(p==NULL){cout<<"\nNo se pudo guardar el archivo ("<<fileName<<"), intentelo nuevamente.";}
	fwrite(this,sizeof *this,1,p);
	fclose(p);
	}

int DataPassFile::loadFile()
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
#endif // DFCLASS_HPP_INCLUDED
