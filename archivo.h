#ifndef ARCHIVO_H
#define ARCHIVO_H
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;
class Archivo{
    private:
        FILE *archivo;
        vector<unsigned char> bytes;
        unsigned char c;

    public:
        vector<unsigned char> leerArchivo(string nomArchivo);
        Archivo();
};

#endif // ARCHIVO_H
