#include <iostream>
#include "Archivo.h"
#include "CabeceraEthernet.h"
#include "CabeceraIPv4.h"
#include "ICMPv4.h"
#include "cabeceraARP.h"
#include "cabeceraRARP.h"
#include "cabeceraIPv6.h"
#include "cabeceraICMPv6.h"
#include "cabeceraTCP.h"
#include "cabeceraUDP.h"

using namespace std;
int main()
{
    Archivo archivo;
    CabeceraEthernet ce;
    vector<unsigned char> bytes;
    string binario;

    bytes = archivo.leerArchivo("ethernet_ipv4_udp_dns.bin");
    //Ethernet (14 bytes)
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


        //IPv4 - bit 112 a 271, <= 271 (20 bytes)
        if(ce.getTipo() == "IPv4"){
            CabeceraIPv4 c4;

            binario = c4.toBinary(bytes);
            c4.setCabeceraIPv4(binario);
            c4.mostrarCabeceraIPv4();

            //ICMPv4 - bit 272 a 303, <= 303 (4 bytes)
            if(c4.getProtocolo() == "ICMPv4"){
                ICMPv4 icmp4;
                icmp4.setICMPv4(binario);
                icmp4.mostrarICMPv4();
            }

            //TCP - bit 272 a 431, <= 431 (20 bytes)
            if (c4.getProtocolo() == "TCP")
            {
                TCP *TCP_header4 = new TCP(272);
                string data;

                data = TCP_header4->toBinary(bytes);
                TCP_header4->setTCPHeader(data);
                TCP_header4->showTCPHeader();

            }

            //UDP
            if (c4.getProtocolo() == "UDP")
            {
                UDP *UDP_header4 = new UDP(272);
                string data;

                data = UDP_header4->toBinary(bytes);
                UDP_header4->setUDPHeader(data);
                UDP_header4->showUDPHeader();
            }
            
        }

        //ARP - bit 112 a 335, <= 335 (28 bytes)
        if (ce.getTipo() == "ARP")
        {
            ARP headerARP;
            string data;

            data = headerARP.toBinary(bytes);
            headerARP.setARPHeader(data);
            headerARP.showARPHeader();

        }
        //RARP - bit 112 a 335, <= 335 (28 bytes)
        if (ce.getTipo() == "RARP")
        {
            RARP headerRARP;
            string data;

            data = headerRARP.toBinary(bytes);
            headerRARP.setRARPHeader(data);
            headerRARP.showRARPHeader();
        }
        //IPv6 - bit 112 a 431, <= 431 (40 bytes)
        if (ce.getTipo() == "IPv6")
        {
            IPv6 headerIPv6;
            string data;
            vector<unsigned char> ipv6_remainder;

            data = headerIPv6.toBinary(bytes);
            headerIPv6.setIPv6Header(data);
            headerIPv6.showIPv6Header();

            //IPv6 - bit 432 a 463, <= 463 (4 bytes)
            if (headerIPv6.getNextHeader() == "ICMPv6")
            {
                ICMPv6 headerICMPv6;
                string data;

                data = headerICMPv6.toBinary(bytes);
                headerICMPv6.setICMPv6Header(data);
                headerICMPv6.showICMPv6Header();
            }

            //TCP-IPv6 - bit 432 a 591, <= 591 (20 bytes)
            if (headerIPv6.getNextHeader() == "TCP")
            {
                TCP *TCP_header6 = new TCP(432);
                string data;

                data = TCP_header6->toBinary(bytes);
                TCP_header6->setTCPHeader(data);
                TCP_header6->showTCPHeader();
            }

            //UDP-IPv6
            if (headerIPv6.getNextHeader() == "UDP")
            {
                UDP *UDP_header6 = new UDP(432);
                string data;

                data = UDP_header6->toBinary(bytes);
                UDP_header6->setUDPHeader(data);
                UDP_header6->showUDPHeader();   
            }
        }


    }else{
        cout << "Imposible analisar los campos" << endl;
    }

    cout << endl;
    system("pause");

    return 0;
}
