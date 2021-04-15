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

string ARP::protocolType(int type)
{
    switch (type)
    {
    case 2048:
        return "IPv4";
        break;

    case 2054:
        return "ARP";
        break;

    case 32821:
        return "RARP";
        break;

    case 34525:
        return "IPv6";
        break;
    
    default:
        return "Tipo desconocido";
        break;
    }
}

string ARP::opCode(int type)
{
    switch (type)
    {
    case 1:
        return "ARP Request";
        break;

    case 2:
        return "ARP Reply";
        break;

    case 3:
        return "RARP Request";
        break;

    case 4:
        return "RARP Reply";
        break;

    case 5:
        return "DRARP Request";
        break;

    case 6:
        return "DRARP Reply";
        break;

    case 7:
        return "DRARP Error";
        break;

    case 8:
        return "InARP Request";
        break;

    case 9:
        return "InARP Reply";
        break;
    
    default:
        return "Tipo desconocido.";
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

    //Tipo de protocolo - 16 bits - Hexadecimal
    string protocol;

    for (int i = bit; i <= 143; i++)
    {
        protocol += data[i];
        bit++;
    }

    protocol_type = binaryToDecimal(protocol);

    //Longitud de direccion de hardware - 8 bits - Decimal
    string hw_length;

    for (int i = bit; i <= 151; i++)
    {
        hw_length += data[i];
        bit++;
    }

    hardware_address_length = binaryToDecimal(hw_length);

    //Longitud de la direccion de protocolo - 8 bits - Decimal
    string protocol_length;

    for (int i = bit; i <= 159; i++)
    {
        protocol_length += data[i];
        bit++;
    }

    protocol_address_length = binaryToDecimal(protocol_length);

    //codigo de operacion - 16 bits - Decimal
    string op_code_str;
    
    for (int i = bit; i <= 175; i++)
    {
        op_code_str += data[i];
        bit++;
    }

    opcode = binaryToDecimal(op_code_str);
}

void ARP::showARPHeader()
{
    cout << "       Cabecera ARP" << endl;
    cout << "Tipo de hardware: " << hardware_type << " - " << hardwareType(hardware_type) << endl;
    printf("Tipo de protocolo: %02X", protocol_type);
    cout << " - " << protocolType(protocol_type) << endl;
    cout << "Longitud de la direccion de hardware: " << hardware_address_length << " bytes" << endl;
    cout << "Longitud de la direccion de protocolo: " << protocol_address_length << " bytes" << endl;
    cout << "Codigo de operacion: " << opcode << " - " << opCode(opcode) << endl;
}