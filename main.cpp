#include <iostream>
#include "archivo.h"
#include "cabeceraEthernet.h"
#include "cabeceraIPv4.h"
#include "cabeceraICMPv4.h"
#include "cabeceraARP.h"

using namespace std;

int main()
{
    Archivo archivo;
    CabeceraEthernet ce;
    vector<unsigned char> bytes;

    bytes = archivo.leerArchivo("ethernet_arp_reply.bin");

    if(bytes.size() != 0)
    {
        ce.setCabecera(bytes);

        cout <<  endl << "       Cabecera Ethernet" << endl;
        cout << "Direccion Destino: ";
        ce.mostrarCampo(ce.getDirDestino());
        cout << "Direccion Origen: ";
        ce.mostrarCampo(ce.getDirOrigen());
        cout << "Tipo: ";
        ce.mostrarCampo(ce.getTipo_Long());

        ce.setTipo(ce.getTipo_Long());
        cout << " - " << ce.getTipo() << endl << endl;

        if(ce.getTipo() == "IPv4")
        {
            CabeceraIPv4 c4;
            string binario;

            binario = c4.toBinary(bytes);
            c4.setCabeceraIPv4(binario);
            c4.mostrarCabeceraIPv4();
            cout << endl;

            if (c4.getProtocol() == "ICMPv4")
            {
                CabeceraICMPv4 headerICMPv4;
                string data;

                data = headerICMPv4.toBinary(bytes);
                headerICMPv4.setICMPv4Header(data);
                headerICMPv4.showICMPv4Header();
            }
            
        }

        if (ce.getTipo() == "ARP")
        {
            ARP headerARP;
            string data;

            data = headerARP.toBinary(bytes);
            headerARP.setARPHeader(data);
            headerARP.showARPHeader();

        }
        
    }
    else
    {
        cout << "Imposible establecer la cabecera Ethernet" << endl;
    }

    cout << endl;
    cout << endl;
    system("pause");

    return 0;
}
