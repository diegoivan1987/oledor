#include "cabeceraDNS.h"

//Constructor y destructor
DNS::DNS(size_t bit)
{
    this->bitAcumulador = bit;
}

DNS::~DNS() { }

//Conversiones
string DNS::toBinary(const vector<unsigned char>& bytes)
{
    string binary;
    for(size_t i = 0; i < bytes.size(); i++)
    {
        for(int j = 7; j >= 0; j--)
        {
            binary += ((bytes.at(i) & (1 << j)) ? '1' : '0');
        }
    }
    return binary;
}

int DNS::binaryToDecimal(const string& number)
{
    int total;
    total = stoull(number, 0, 2);
    return total;
}

//Procedimiento
void DNS::setDNSHeader(const string& data)
{
    int bit = bitAcumulador;
    bitAcumulador = bitAcumulador-1;
    string aux;

    //ID - 16 bits - Hexadecimal
    bitAcumulador += 16;
    for (size_t i = bit; i <= bitAcumulador; i++)
    {
        aux += data[i];
        bit++;
    }

    id = binaryToDecimal(aux);
    aux.clear();
}

void DNS::showDNSHeader()
{
    cout << "\n\n ***Cabecera UDP***" << endl;
    printf("ID: %02X\n", id);
}