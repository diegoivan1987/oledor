#include <iostream>
#include <string>
#include <conio.h>
#include "Archivo.h"
#include "CabeceraEthernet.h"


using namespace std;
int main()
{
    Archivo archivo;
    vector<unsigned char> bytes;

    bytes = archivo.leerArchivo("ethernet_1.bin");

    if(bytes.size() != 0){
        CabeceraEthernet ce;
        ce.setCabecera(bytes);

        cout << endl << endl << "Direccion Destino: ";
        ce.mostrarCampo(ce.getDirDestino());
        cout << endl << "Direccion Origen: ";
        ce.mostrarCampo(ce.getDirOrigen());
        cout << endl << "Tipo/Longitud: ";
        ce.mostrarCampo(ce.getTipo_Long());

        ce.setTipo(ce.getTipo_Long());
        cout << "Tipo: " << ce.getTipo() << endl;
    }else{
        cout << "Imposible establecer la cabecera Ethernet" << endl;
    }

    getch();

    return 0;
}
