#include <iostream>
#include <cstring> // para poder utilizar strcpy
#include <cstdlib>

using namespace std;

#include "parcial2.h"

class Punto1{
private:
    int numeroProveedor;
    char nombre[30];
    int provincia;
public:
    void Cargar(){
        cin>>numeroProveedor;
        cargarCadena(nombre,29);
        cin>>provincia;

    }

    void Mostrar(){
        cout<<numeroProveedor<<endl;
        cout<<nombre<<endl;
        cout<<provincia<<endl;
    }

int getNumeroProveedor(){return numeroProveedor;}
const char *getNombre(){return nombre;}
int getProvincia(){return provincia;}

void setNumeroProveedor(int np){numeroProveedor=np;}
void setProvincia(int np){provincia=np;}
void setNombre(const char *n){strcpy(nombre,n);}
};

class ArchivoPunto1{

 private:
        char nombre[30];
    public:
        ArchivoPunto1(const char *n){
            strcpy(nombre, n);
        }

        Punto1 leerRegistro(int pos){
            Punto1 reg;
            FILE *p=fopen(nombre,"rb");
            if(p==NULL){
                return reg;
            }
            fseek(p, pos * sizeof reg, 0);
            fread(&reg, sizeof reg, 1, p);
            fclose(p);
            return reg;
        }


        int contarRegistros(){
            FILE *p=fopen(nombre,"rb");
            if(p==NULL){
                return -1;
            }
            fseek(p, 0, 2);
            int cant=ftell(p)/sizeof(Punto1);
            fclose(p);
            return cant;
        }

    bool grabarRegistro(Punto1 obj){
    FILE *p;
    p= fopen("punto1par2.dat","ab");
    if(p ==NULL) return false;
    bool escribio = fwrite(&obj,sizeof obj,1,p);
    fclose(p);
    return escribio;
    }

    void mostrarArchivo(){
     Punto1 obj;
     FILE *p;
     p=fopen("punto1par2.dat","rb");
     if (p==NULL){
        cout << "no se pudo abrir el archivo que se creo" << endl;
        exit(1);
     }
     while(fread(&obj,sizeof obj,1,p)== true){
        obj.Mostrar();
        cout << endl;
     }
        fclose(p);
 }
};

void puntoA(){
Proveedor objProv;
ArchivoProveedores objArProv("proveedores.dat");

Compra objCom;
ArchivoCompras objArCom("compras.dat");


Punto1 objPunto1;
ArchivoPunto1 objArPun1("punto1par2.dat");

int tam1 = objArProv.contarRegistros();
int tam2 = objArCom.contarRegistros();


for(int i=0 ; i < tam1 ;i++){

       objProv =  objArProv.leerRegistro(i);
       bool  compraEnAnioActual = false;


    for(int j = 0 ; j< tam2 ; j++){
        objCom = objArCom.leerRegistro(j);

        if(objCom.getNumeroproveedor() == objProv.getNumeroProveedor()  && objCom.getFechaCompra().getAnio() == 2024){

        compraEnAnioActual = true;
        break;
        }
    }

        if(compraEnAnioActual == false){
        objPunto1.setNumeroProveedor(objProv.getNumeroProveedor());
        objPunto1.setNombre(objProv.getNombre());
        objPunto1.setProvincia(objProv.getProvincia());

    if(objArPun1.grabarRegistro(objPunto1)==false){
        cout << "No se pudo crear el archivo" << endl;
        return;
    }
    }

    }
}


void puntoB(){
Material objMat;
ArchivoMateriales objArMat("materiales.dat");

Compra objCom;
ArchivoCompras objArCom("compras.dat");



int tam1 = objArMat.contarRegistros();
int tam2 = objArCom.contarRegistros();

int vec[6] ={};


for(int i= 0 ; i< tam1 ; i++){
    objMat = objArMat.leerRegistro(i);

   for(int j=0;j<tam2;j++){
    objCom =objArCom.leerRegistro(j);

    if(objCom.getCodigoMaterial() == objMat.getCodigoMaterial()){
        vec[objMat.getTipo()-1]+=objCom.getCantidad();
    }
   }

}

 int tipoMenosMateriales ;
 int menorCantidad = 0;
 bool bandera = true;

    for (int i = 1; i < 6; i++) {
        if((bandera == true)&&(vec[i]>0)){
            menorCantidad = vec[i];
            tipoMenosMateriales =i;
            bandera = false;
        }else if(vec[i]< menorCantidad && vec[i]>0){
            menorCantidad = vec[i];
            tipoMenosMateriales = i;

        }
        }



cout << "El material menor es el numero " << tipoMenosMateriales + 1<< endl;
cout << "con la cantidad: " << menorCantidad << " de matteriales " <<endl;


}


void puntoC(){
Material objMat;
ArchivoMateriales objArMat("materiales.dat");

int buscarMaterial;


int tam = objArMat.contarRegistros();

Material *vectorDinamico = new Material[tam];

for(int i= 0 ; i< tam ; i++){
    objMat = objArMat.leerRegistro(i);

    vectorDinamico[i] = objMat;
}


cout<< "Listar los materiales del tipo: " <<endl;
cin >> buscarMaterial;
cout << endl;

for(int j=0; j<tam ;j++){
    if(buscarMaterial == vectorDinamico[j].getTipo()){
    vectorDinamico[j].Mostrar() ;
    cout <<endl;
    }
}


delete[] vectorDinamico;
}

void puntoD(){
Obra obra;
obra.setSuperficie(250);
float valorComparacion = 250; // Valor de superficie a comparar

if (obra == valorComparacion) {
    cout << "La superficie de la obra es igual a " << valorComparacion << endl;
} else {
    cout << "La superficie de la obra no es igual a " << valorComparacion << endl;
}
}

 //SOBRECARGA PUNTO D
 //   bool operator == (float sup) const {
 //   return superficie == sup;
 //   }





void Menu(){
ArchivoPunto1 obj("punto1.dat");

ArchivoCompras objCom("compras.dat");

ArchivoProveedores objPro("proveedores.dat");

ArchivoObras obr("obras.dat");

Compra com;

 while(true){
        int opc;
        system("cls");
        cout<< "MENU PRINCIPAL"<<endl;
        cout<< "--------------"<<endl;
        cout<< "1 - Generar archivo"<<endl;
        cout<< "2 - mostrar archivo nuevo "<<endl;

        cout << "3- mostrar compras"<<endl;
        cout << "4- mostrar proveedores"<<endl;
        cout << "5- cargar compra"<<endl;


        cout<< "6- Generar vector dinamico punto C" << endl;
        cout<< "7- listar obras"<<endl;
        cout<< "8- Sobrecarga puntoD"<<endl;


        cout<< "9- El tipo de material con menos cantidad de materiales(puntoB)"<<endl;




        cout<<"----------------------------------------"<<endl;
        cout<<"INGRESE LA OPCION: ";
        cin>>opc;
        system("cls");
        switch(opc){
            case 1:
               puntoA();
                break;
            case 2:
            obj.mostrarArchivo();
            break;
            case 3:
           objCom.listarCompras();
            break;
            case 4:
            objPro.listarProveedores();
            break;
            case 5:
            com.Cargar();
            objCom.grabarRegistro(com);
                break;
            case 6:
            puntoC();
            break;
            case 7:
            obr.listarObras();
            break;
            case 8:
            puntoD();
            break;
            case 9:
            puntoB();
            break;

            case 0:


                return ;
            default:
                cout<<"LA OPCION INGRESADA NO ES CORRECTA"<<endl;
                system("pause");
                break;
        }
        system("pause");
    }
}




int main()
{

Menu();



    return 0;
}
