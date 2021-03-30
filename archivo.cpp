#include "Archivo.h"

Archivo::Archivo() { }

vector<unsigned char> Archivo::leerArchivo(string nomArchivo)
{
    ifstream miArchivo(nomArchivo);
    
    if(miArchivo)
    {
        string linea;
        cout << "Archivo abierto: " << nomArchivo << endl;
        
        while(getline(miArchivo, linea))
        {
            for(size_t i = 0; i < linea.size(); i++)
            {
                bytes.push_back((unsigned char)linea[i]);
            }
        }
        miArchivo.close();
    }
    else
    {
        cout<<"Archivo no encontrado"<<endl;
    }

    return bytes;
}




