#include "cabeceraARP.h"

//Constructor y destructor
ARP::ARP() { }

ARP::~ARP() { }

//Conversiones
string ARP::toBinary(vector<unsigned char> bytes)
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

int ARP::binaryToDecimal(string number)
{
    int total;
    total = stoull(number, 0, 2); 
    return total;
}

string ARP::hardwareType(int type)
{
    switch (type)
    {
    case 1:
        return "Ethernet (10 Mb)";
        break;

    case 6:
        return "IEEE 802 Networks";
        break;

    case 7:
        return "ARCNET";
        break;
    
    case 15:
        return "Frame Relay";
        break;

    case 16:
        return "Asynchronous Transfer Mode ATM";
        break;

    case 17:
        return "HDLC";
        break;

    case 18:
        return "Fibre Channel";
        break;

    case 19:
        return "Asynchronous Transfer Mode ATM";
        break;

    case 20:
        return "Serial Line";
        break;

    default:
        return "Tipo desconocido";
        break;
    }
}

//Procedimiento
void ARP::setARPHeader(string data)
{
    //Despues de la cabecera ethernet se queda en el bit 112
    int bit = 112;

    //Tipo de hardware - 16 bits - decimal
    string hw_type;

    for (int i = bit; i <= 127; i++)
    {
        hw_type += data[i];
        bit++;
    }

    hardware_type = binaryToDecimal(hw_type);
}

void ARP::showARPHeader()
{
    cout << "       Cabecera ICMPv4" << endl;
    cout << "Tipo de hardware: " << hardware_type << " - " << hardwareType(hardware_type) << endl;
}