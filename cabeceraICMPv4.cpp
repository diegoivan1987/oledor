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

string CabeceraICMPv4::messageType(int type)
{
    switch (type)
    {
    case 0:
        return "Echo Reply";
        break;

    case 3:
        return "Destination Unreachable";
        break;

    case 4:
        return "Source Quench";
        break;

    case 5:
        return "Redirect";
        break;

    case 8:
        return "Echo";
        break;

    case 11:
        return "Time Exceeded";
        break;

    case 12:
        return "Parameter Problem";
        break;

    case 13:
        return "Timestamp";
        break;

    case 14:
        return "Timestamp Reply";
        break;

    case 15:
        return "Information Request";
        break;

    case 16:
        return "Information Reply";
        break;

    case 17:
        return "Addressmask";
        break;

    case 18:
        return "Addressmask Reply";
        break;

    default:
        return "Mensaje desconocido.";
        break;
    }
}

string CabeceraICMPv4::errorType(int type)
{
    switch (type)
    {
    case 0:
        return "No se puede llegar a la red.";
        break;

    case 1:
        return "No se puede llegar al host o aplicacion de destino.";
        break;

    case 2:
        return "El destino no dispone del protocolo solicitado.";
        break;

    case 3:
        return "No se puede llegar al puerto de destino o la aplicacion de destino no esta libre";
        break;
    
    case 4:
        return "Se necesita aplicar fragmentacion, pero el flag correspondiente indica lo contrario.";
        break;

    case 5:
        return "La ruta de origen no es correcta.";
        break;

    case 6:
        return "No se conoce la red de destino.";
        break;

    case 7:
        return "No se conoce el host de destino.";
        break;

    case 8:
        return "El host de origen esta aislado.";
        break;

    case 9:
        return "La comunicacion con la red de destino esta prohibida por razones administrativas.";
        break;

    case 10:
        return "La comunicacion con el host de destino esta prohibida por razones administrativas.";
        break;

    case 11:
        return "No se puede llegar a la red de destino debido al tipo de servicio.";
        break;

    case 12:
        return "No se puede llegar al host de destino debido al tipo de servicio.";
        break;
    
    default:
        return "Error desconocido.";
        break;
    }
}

void CabeceraICMPv4::setICMPv4Header(string data)
{
    //La cabecera comienza en el bit 272
    int bit = 272;

    //Tipo de mensaje informativo - 8 bits - Decimal
    string type_str;

    for (size_t i = bit; i <= 279; i++)
    {
        type_str += data[i];
        bit++;
    }

    type = binaryToDecimal(type_str);

    //Codigos de error - 8 bits - Decimal
    string error;
    for (size_t i = bit; i <= 287; i++)
    {
        error += data[i];
        bit++;
    }

    error_code = binaryToDecimal(error);

    //Checksum - 16 bits - Hexadecimal
    string checksum_str;
    for (size_t i = bit; i <= 303; i++)
    {
        checksum_str += data[i];
        bit++;
    }

    checksum = binaryToDecimal(checksum_str);
}

void CabeceraICMPv4::showICMPv4Header()
{
    cout << "       Cabecera ICMPv4" << endl;
    cout << "Tipo de mensaje informativo: " << type << " - " << messageType(type) << endl;
    cout << "Codigo de error: " << error_code << " - " << errorType(error_code) << endl;
    printf("Checksum: %02X\n", checksum);
}