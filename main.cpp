#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <conio.h>

using namespace std;

/*****************/
class Archivo{
    private:
        FILE *archivo;
        vector<unsigned char> bytes;
        unsigned char c;

    public:
        vector<unsigned char> leerArchivo(string nomArchivo);

};

vector<unsigned char> Archivo::leerArchivo(string nomArchivo){

    cout << endl << endl;
    ifstream miArchivo(nomArchivo);
    string linea;

    if(miArchivo){
        cout << "Archivo abierto: " << nomArchivo << endl;
        while(getline(miArchivo, linea)){
            for(size_t i = 0; i < linea.size(); i++){
                printf("%02X ", (unsigned char)linea[i]);
                bytes.push_back((unsigned char)linea[i]);
            }
        }
        miArchivo.close();
    }else{
        cout<<"Archivo no encontrado"<<endl;
    }

    return bytes;
}

/****************/
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

void CabeceraEthernet::setCabecera(vector<unsigned char> bytes){
    size_t i;

    for(i = 0; i < 6; i++){
        dirDestino.push_back(bytes.at(i));
    }
    for(i = i; i < 12; i++){
        dirOrigen.push_back(bytes.at(i));
    }
    for(i = i; i < 14; i++){
        tipo_long.push_back(bytes.at(i));
    }
}

void CabeceraEthernet::mostrarCampo(vector<unsigned char> campo){
    for(size_t i = 0; i < campo.size(); i++){
        printf("%02X:", campo.at(i));
    }
    printf("\n");
}

void CabeceraEthernet::setTipo(vector<unsigned char> campo){

    if(campo.at(0) == 8){
        if(campo.at(1) == 0){
            tipo = "IPv4";
        }else if(campo.at(1) == 6){
            tipo = "ARP";
        }
    }else if(campo.at(0) == 128){
        tipo = "RARP";
    }else if(campo.at(0) == 134){
        tipo = "IPv6";
    }
}

vector<unsigned char> CabeceraEthernet::getDirDestino(){
    return dirDestino;
}
vector<unsigned char> CabeceraEthernet::getDirOrigen(){
    return dirOrigen;
}
vector<unsigned char> CabeceraEthernet::getTipo_Long(){
    return tipo_long;
}
string CabeceraEthernet::getTipo(){
    return tipo;
}

/*********Main********/
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
