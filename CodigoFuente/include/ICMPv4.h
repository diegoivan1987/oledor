#ifndef ICMPV4_H
#define ICMPV4_H
#include <iostream>
#include "CabeceraIPv4.h"

using namespace std;

class ICMPv4
{
    private:
        int tipo;
        int codigo;
        int checksum;

    public:
        ICMPv4();
        void setICMPv4(string bin);
        void mostrarICMPv4();
        void setMensajeInformativo(int tipo);
        void setMensajeError(int codigo);
};

#endif

