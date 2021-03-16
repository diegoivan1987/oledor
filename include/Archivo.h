#ifndef ARCHIVO_H
#define ARCHIVO_H
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <conio.h>

using namespace std;
class Archivo{
    private:
        FILE *archivo;
        vector<unsigned char> bytes;
        unsigned char c;

    public:
        vector<unsigned char> leerArchivo(string nomArchivo);

};

#endif // ARCHIVO_H
