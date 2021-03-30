#include <iostream>
#include "archivo.h"
#include "cabeceraEthernet.h"
#include "cabeceraIPv4.h"

using namespace std;

int main()
{
    Archivo archivo;
    CabeceraEthernet ce;
    vector<unsigned char> bytes;

    bytes = archivo.leerArchivo("ethernet_ipv4_udp_dns.bin");

    if(bytes.size() != 0){
        ce.setCabecera(bytes);

        cout << endl << endl << "Direccion Destino: ";
        ce.mostrarCampo(ce.getDirDestino());
        cout << endl << "Direccion Origen: ";
        ce.mostrarCampo(ce.getDirOrigen());
        cout << endl << "Tipo: ";
        ce.mostrarCampo(ce.getTipo_Long());

        ce.setTipo(ce.getTipo_Long());
        cout << "   *" << ce.getTipo() << endl;
    }else{
        cout << "Imposible establecer la cabecera Ethernet" << endl;
    }
    cout << endl;


    if(ce.getTipo() == "IPv4"){
        CabeceraIPv4 c4;
        string binario;

        binario = c4.toBinary(bytes);
        //c4.mostrarBinario(binario);
        c4.setCabeceraIPv4(binario);
        c4.mostrarCabeceraIPv4();



    }



    system("pause");

    return 0;
}
