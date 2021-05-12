#ifndef CABECERAIPV4_H
#define CABECERAIPV4_H
#include <vector>
#include <iostream>

using namespace std;

class CabeceraIPv4
{
    private:

        int versionI;
        int cabeceraI;
        string tipoServicioS;
        int longitudI;
        int identificadorI;
        string flagsS;
        int fragmentoI;
        int tiempoI;
        int protocoloI;
        string protocolo;
        int checksumI;
        int dirOrigenA[4];
        int dirDestinoA[4];

    public:
        CabeceraIPv4();
        static string toBinary(vector<unsigned char> bytes);
        void mostrarBinario(string binario);
        void setCabeceraIPv4(string bin);
        void mostrarCabeceraIPv4();
        static int binToDecimal(string bin);
        void tipoServicioDesglose_3(string bits);
        void tipoServicioDesglose_5(string bits);
        void flags(string bits);
        void setProtocolo(int dato);
        string getProtocolo();
};

#endif
