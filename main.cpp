#include <iostream>
#include "Archivo.h"
#include "CabeceraEthernet.h"
#include "CabeceraIPv4.h"
#include "ICMPv4.h"
#include "cabeceraARP.h"
#include "cabeceraRARP.h"

using namespace std;
int main()
{
    Archivo archivo;
    CabeceraEthernet ce;
    vector<unsigned char> bytes;
    string binario;

    bytes = archivo.leerArchivo("ethernet_arp_request.bin");

    if(bytes.size() != 0){
        ce.setCabecera(bytes);
        cout << endl << "***Cabecera Ethernet***" << endl;
        cout << "Direccion Destino: ";
        ce.mostrarCampo(ce.getDirDestino());
        cout << "Direccion Origen: ";
        ce.mostrarCampo(ce.getDirOrigen());
        cout << "Tipo: ";
        ce.mostrarCampo(ce.getTipo_Long());

        ce.setTipo(ce.getTipo_Long());
        cout << "   *" << ce.getTipo() << endl;


        //IPv4 - bit 112 a 271, <= 271
        if(ce.getTipo() == "IPv4"){
            CabeceraIPv4 c4;

            binario = c4.toBinary(bytes);
            c4.setCabeceraIPv4(binario);
            c4.mostrarCabeceraIPv4();

            //ICMPv4
            if(c4.getProtocolo() == "ICMPv4"){
                ICMPv4 icmp4;
                icmp4.setICMPv4(binario);
                icmp4.mostrarICMPv4();
            }


        }

        //ARP - bit 112 a 335, <= 335
        if (ce.getTipo() == "ARP")
        {
            ARP headerARP;
            string data;

            data = headerARP.toBinary(bytes);
            headerARP.setARPHeader(data);
            headerARP.showARPHeader();

        }
        //RARP - bit 112 a 335, <= 335
        if (ce.getTipo() == "RARP")
        {
            RARP headerRARP;
            string data;

            data = headerRARP.toBinary(bytes);
            headerRARP.setRARPHeader(data);
            headerRARP.showRARPHeader();
        }


    }else{
        cout << "Imposible analisar los campos" << endl;
    }



    cout << endl;
    system("pause");

    return 0;
}
