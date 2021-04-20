#include "cabeceraIPv6.h"

//Constructor y destructor
IPv6::IPv6() { }

IPv6::~IPv6() { }

//Conversiones
string IPv6::toBinary(vector<unsigned char> bytes)
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

int IPv6::binaryToDecimal(string number)
{
    int total;
    total = stoull(number, 0, 2); 
    return total;
}

//Funeciones switch para los distintos atributos

//Procedimiento
void IPv6::setIPv6Header(string data)
{
    //Despues de la cabecera ethernet se queda en el bit 112
    int bit = 112;

    //Version - 4 bits - Decimal
    string ipv6_version;

    for (size_t i = bit; i <= 115; i++)
    {
        ipv6_version += data[i];
        bit++;
    }

    version = binaryToDecimal(ipv6_version);

    //Clase de trafico - 8 bits - Binario
}

void IPv6::showIPv6Header()
{
    cout << "       Cabecera IPv6" << endl;
    cout << "Version: " << version << endl;
}