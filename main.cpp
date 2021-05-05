#include <iostream>
#include "archivo.h"
#include "cabeceraEthernet.h"
#include "cabeceraIPv4.h"
#include "cabeceraICMPv4.h"
#include "cabeceraARP.h"
#include "cabeceraRARP.h"
#include "cabeceraIPv6.h"
#include "cabeceraICMPv6.h"
#include "cabeceraTCP.h"

using namespace std;

int main()
{
    Archivo archivo;
    CabeceraEthernet ce;
    vector<unsigned char> bytes;

    bytes = archivo.leerArchivo("ethernet_ipv4_tcp.bin");

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

            if (c4.getProtocol() == "TCP")
            {
                TCP TCP_header;
                string data;
                vector<unsigned char> TCP_remainder;

                data = TCP_header.toBinary(bytes);
                TCP_header.setTCPHeader(data);
                TCP_header.showTCPHeader();

                //Se leyó hasta el byte 53, por lo que se empieza en el 54
                for (int i = 54; i <= bytes.size(); i++)
                {
                    TCP_remainder.push_back(bytes[i]);
                }

                cout << "Resto de los datos: ";

                for (int i = 0; i < TCP_remainder.size(); i++)
                {
                    printf("%02X ", TCP_remainder[i]);
                }
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

        if (ce.getTipo() == "RARP")
        {
            RARP headerRARP;
            string data;

            data = headerRARP.toBinary(bytes);
            headerRARP.setRARPHeader(data);
            headerRARP.showRARPHeader();
        }

        if (ce.getTipo() == "IPv6")
        {
            IPv6 headerIPv6;
            string data;
            vector<unsigned char> ipv6_remainder;
            int x = 0;

            data = headerIPv6.toBinary(bytes);
            headerIPv6.setIPv6Header(data);
            headerIPv6.showIPv6Header();

            if (headerIPv6.getNextHeader() == "ICMPv6")
            {
                ICMPv6 headerICMPv6;
                string data;

                data = headerICMPv6.toBinary(bytes);
                headerICMPv6.setICMPv6Header(data);
                headerICMPv6.showICMPv6Header();
            }
            
            //Se leyó hasta el byte 53, por lo que se empieza en el 54
            for (int i = 54; i <= bytes.size(); i++)
            {
                ipv6_remainder.push_back(bytes[i]);
            }

            cout << "Resto de los datos: ";

            for (int i = 0; i < ipv6_remainder.size(); i++)
            {
                printf("%02X ", ipv6_remainder[i]);
            }
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
