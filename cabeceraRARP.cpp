#include "cabeceraRARP.h"

//Constructor y destructor
RARP::RARP() { }

RARP::~RARP() { }

//Conversiones
string RARP::toBinary(vector<unsigned char> bytes)
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

int RARP::binaryToDecimal(string number)
{
    int total;
    total = stoull(number, 0, 2); 
    return total;
}

string RARP::hardwareType(int type)
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

string RARP::protocolType(int type)
{
    switch (type)
    {
    case 2048:
        return "IPv4";
        break;

    case 2054:
        return "RARP";
        break;

    case 32821:
        return "RRARP";
        break;

    case 34525:
        return "IPv6";
        break;
    
    default:
        return "Tipo desconocido";
        break;
    }
}

string RARP::opCode(int type)
{
    switch (type)
    {
    case 1:
        return "RARP Request";
        break;

    case 2:
        return "RARP Reply";
        break;

    case 3:
        return "RRARP Request";
        break;

    case 4:
        return "RRARP Reply";
        break;

    case 5:
        return "DRRARP Request";
        break;

    case 6:
        return "DRRARP Reply";
        break;

    case 7:
        return "DRRARP Error";
        break;

    case 8:
        return "InRARP Request";
        break;

    case 9:
        return "InRARP Reply";
        break;
    
    default:
        return "Tipo desconocido.";
        break;
    }
}

//Procedimiento
void RARP::setRARPHeader(string data)
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

    //Codigo de operacion - 16 bits - Decimal
    string op_code_str;
    
    for (int i = bit; i <= 175; i++)
    {
        op_code_str += data[i];
        bit++;
    }

    opcode = binaryToDecimal(op_code_str);

    //Direccion MAC del emisor - 48 bits - Hexadecimal
    string mac_source_1, mac_source_2, mac_source_3, mac_source_4, mac_source_5, mac_source_6;

    for (int i = bit; i <= 183; i++)
    {
        mac_source_1 += data[i];
        bit++;
    }

    mac_source[0] = binaryToDecimal(mac_source_1);

    for (int i = bit; i <= 191; i++)
    {
        mac_source_2 += data[i];
        bit++;
    }

    mac_source[1] = binaryToDecimal(mac_source_2);

    for (int i = bit; i <= 199; i++)
    {
        mac_source_3 += data[i];
        bit++;
    }

    mac_source[2] = binaryToDecimal(mac_source_3);
    
    for (int i = bit; i <= 207; i++)
    {
        mac_source_4 += data[i];
        bit++;
    }

    mac_source[3] = binaryToDecimal(mac_source_4);

    for (int i = bit; i <= 215; i++)
    {
        mac_source_5 += data[i];
        bit++;
    }

    mac_source[4] = binaryToDecimal(mac_source_5);

    for (int i = bit; i <= 223; i++)
    {
        mac_source_6 += data[i];
        bit++;
    }

    mac_source[5] = binaryToDecimal(mac_source_6);

    //Direccion MAC del receptor - 48 bits - Hexadecimal
    string mac_destination_1, mac_destination_2, mac_destination_3, mac_destination_4, mac_destination_5, mac_destination_6;

    for (int i = bit; i <= 231; i++)
    {
        mac_destination_1 += data[i];
        bit++;
    }

    mac_destination[0] = binaryToDecimal(mac_destination_1);

    for (int i = bit; i <= 239; i++)
    {
        mac_destination_2 += data[i];
        bit++;
    }

    mac_destination[1] = binaryToDecimal(mac_destination_2);

    for (int i = bit; i <= 247; i++)
    {
        mac_destination_3 += data[i];
        bit++;
    }

    mac_destination[2] = binaryToDecimal(mac_destination_3);
    
    for (int i = bit; i <= 255; i++)
    {
        mac_destination_4 += data[i];
        bit++;
    }

    mac_destination[3] = binaryToDecimal(mac_destination_4);

    for (int i = bit; i <= 263; i++)
    {
        mac_destination_5 += data[i];
        bit++;
    }

    mac_destination[4] = binaryToDecimal(mac_destination_5);

    for (int i = bit; i <= 271; i++)
    {
        mac_destination_6 += data[i];
        bit++;
    }

    mac_destination[5] = binaryToDecimal(mac_destination_6);

    //Direccion IP del emisor - 32 bits - Decimal
    string ip_source_1, ip_source_2, ip_source_3, ip_source_4;

    for (int i = bit; i <= 279; i++)
    {
        ip_source_1 += data[i];
        bit++;
    }

    ip_source[0] = binaryToDecimal(ip_source_1);

    for (int i = bit; i <= 287; i++)
    {
        ip_source_2 += data[i];
        bit++;
    }

    ip_source[1] = binaryToDecimal(ip_source_2);

    for (int i = bit; i <= 295; i++)
    {
        ip_source_3 += data[i];
        bit++;
    }

    ip_source[2] = binaryToDecimal(ip_source_3);

    for (int i = bit; i <= 303; i++)
    {
        ip_source_4 += data[i];
        bit++;
    }

    ip_source[3] = binaryToDecimal(ip_source_4);

    //Direccion IP del receptor - 32 bits - Decimal
    string ip_destination_1, ip_destination_2, ip_destination_3, ip_destination_4;

    for (int i = bit; i <= 311; i++)
    {
        ip_destination_1 += data[i];
        bit++;
    }

    ip_destination[0] = binaryToDecimal(ip_destination_1);

    for (int i = bit; i <= 319; i++)
    {
        ip_destination_2 += data[i];
        bit++;
    }

    ip_destination[1] = binaryToDecimal(ip_destination_2);

    for (int i = bit; i <= 327; i++)
    {
        ip_destination_3 += data[i];
        bit++;
    }

    ip_destination[2] = binaryToDecimal(ip_destination_3);

    for (int i = bit; i <= 335; i++)
    {
        ip_destination_4 += data[i];
        bit++;
    }

    ip_destination[3] = binaryToDecimal(ip_destination_4);
}

void RARP::showRARPHeader()
{
    cout << "       Cabecera RARP" << endl;
    cout << "Tipo de hardware: " << hardware_type << " - " << hardwareType(hardware_type) << endl;
    printf("Tipo de protocolo: %02X", protocol_type);
    cout << " - " << protocolType(protocol_type) << endl;
    cout << "Longitud de la direccion de hardware: " << hardware_address_length << " bytes" << endl;
    cout << "Longitud de la direccion de protocolo: " << protocol_address_length << " bytes" << endl;
    cout << "Codigo de operacion: " << opcode << " - " << opCode(opcode) << endl;
    printf("Direccion de hardware del emisor: %02X:%02X:%02X:%02X:%02X:%02X\n", mac_source[0], mac_source[1], mac_source[2], mac_source[3], mac_source[4], mac_source[5]);
    printf("Direccion de hardware del Receptor: %02X:%02X:%02X:%02X:%02X:%02X\n", mac_destination[0], mac_destination[1], mac_destination[2], mac_destination[3], mac_destination[4], mac_destination[5]);
    cout << "Direccion IP del emisor: " << ip_source[0] << "." << ip_source[1] << "." << ip_source[2] << "." << ip_source[3] << endl;
    cout << "Direccion IP del receptor: " << ip_destination[0] << "." << ip_destination[1] << "." << ip_destination[2] << "." << ip_destination[3] << endl;
}