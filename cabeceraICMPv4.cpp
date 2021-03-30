#include "cabeceraICMPv4.h"

//constructor y destructor
CabeceraICMPv4::CabeceraICMPv4() { }

CabeceraICMPv4::~CabeceraICMPv4() { }

string CabeceraICMPv4::toBinary(vector<unsigned char> bytes)
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

int CabeceraICMPv4::binaryToDecimal(string number)
{
    int total;
    total = stoull(number, 0, 2); 
    return total;
}

void CabeceraICMPv4::setICMPv4Header(string data)
{
    //La cabecera comienza en el bit 272
    int bit = 272;

    //Tipo de mensaje informativo - 8 bits - Decimal
    string type_str;

    for (size_t i = bit; i <= 280; i++)
    {
        type_str = data[i];
        bit++;
    }
    
    type = binaryToDecimal(type_str);
}

void CabeceraICMPv4::showICMPv4Header()
{
    cout << "       Cabecera ICMPv4" << endl;
    cout << "Tipo de mensaje informativo: " << type;
}