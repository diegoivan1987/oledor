#ifndef CABECERAETHERNET_H
#define CABECERAETHERNET_H
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <conio.h>

using namespace std;
class CabeceraEthernet{

    private:
        vector<unsigned char> dirDestino;
        vector<unsigned char> dirOrigen;
        vector<unsigned char> tipo_long;
        string tipo = "Desconocido";

    public:
        void setCabecera(vector<unsigned char> bytes);
        vector<unsigned char> getDirDestino();
        vector<unsigned char> getDirOrigen();
        vector<unsigned char> getTipo_Long();
        string getTipo();
        void mostrarCampo(vector<unsigned char> campo);
        void setTipo(vector<unsigned char> tipo);
};

#endif // CABECERAETHERNET_H
