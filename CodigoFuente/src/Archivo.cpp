#include "Archivo.h"

Archivo::Archivo()
{

}

vector<unsigned char> Archivo::leerArchivo(string nomArchivo){

    cout << endl << endl;
    ifstream miArchivo(nomArchivo);
    string linea;

    if(miArchivo){
        cout << "Archivo abierto: " << nomArchivo << endl;
        while(getline(miArchivo, linea)){
            for(size_t i = 0; i < linea.size(); i++){
                //printf("%02X ", (unsigned char)linea[i]);
                bytes.push_back((unsigned char)linea[i]);
            }
        }
        miArchivo.close();
    }else{
        cout<<"Archivo no encontrado"<<endl;
    }

    return bytes;
}
