#include "cabeceraICMPv6.h"

//Constructor y destructor
ICMPv6::ICMPv6() { }

ICMPv6::~ICMPv6() { }

//Conversiones
string ICMPv6::toBinary(vector<unsigned char> bytes)
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

int ICMPv6::binaryToDecimal(string number)
{
    int total;

    try{
        total = stoull(number, 0, 2);
    }catch(std::invalid_argument& ia){
        cout << endl << "Wrong data composition: " << ia.what() << endl;
    }
    return total;
}

//Mensajes de error

void ICMPv6::errorType(int type, int code)
{
    switch (type)
    {
    case 1:
        cout << "       Tipo de mensaje: " << type << " - Destino inalcanzable" << endl;
        if (code == 0)
        {
            cout << "       Codigo de error: " << code << " - No existe ruta de destino" << endl;
        }
        if (code == 1)
        {
            cout << "       Codigo de error: " << code << " - Comunicacion con el destino administrativamente prohibida" << endl;
        }
        if (code == 2)
        {
            cout << "       Codigo de error: " << code << " - No asignado" << endl;
        }
        if (code == 3)
        {
            cout << "       Codigo de error: " << code << " - Direccion inalcanzable" << endl;
        }
        break;

    case 2:
        cout << "       Tipo de mensaje: " << type << " - Paquete demasiado grande" << endl;
        break;

    case 3:
        cout << "       Tipo de mensaje: " << type << " - Tiempo excedido" << endl;
        if (code == 0)
        {
            cout << "       Codigo de error: " << code << " - Limite de salto excedido" << endl;
        }
        if (code == 1)
        {
            cout << "       Codigo de error: " << code << " - Tiempo de reensamble de fragmento excedido" << endl;
        }
        break;

    case 4:
        cout << "       Tipo de mensaje: " << type << " - Problema de parametro" << endl;
        if (code == 0)
        {
            cout << "       Codigo de error: " << code << " - Campo de encabezado erroneo" << endl;
        }
        if (code == 1)
        {
            cout << "       Codigo de error: " << code << " - Tipo siguiente desconocido" << endl;
        }
        if (code == 2)
        {
            cout << "       Codigo de error: " << code << " - Opcion de IPv6 desconocida" << endl;
        }
        break;

    case 128:
        cout << "       Tipo de mensaje: " << type << " - Solicitud de eco" << endl;
        break;

    case 129:
        cout << "       Tipo de mensaje: " << type << " - Respuesta de eco" << endl;
        break;

    case 133:
        cout << "       Tipo de mensaje: " << type << " - Solicitud de router" << endl;
        break;

    case 134:
        cout << "       Tipo de mensaje: " << type << " - Anuncio del router" << endl;
        break;

    case 135:
        cout << "       Tipo de mensaje: " << type << " - Solicitud de vecino" << endl;
        break;

    case 136:
        cout << "       Tipo de mensaje: " << type << " - Anuncio del vecino" << endl;
        break;

    case 137:
        cout << "       Tipo de mensaje: " << type << " - Reorientacion del mensaje" << endl;
        break;

    default:
        cout << "       Tipo desconocido" << endl;
        break;
    }
}

//Procedimiento
void ICMPv6::setICMPv6Header(string data)
{
    //La cabecera comienza en el bit 432
    int bit = 432;

    //Tipo - 8 bits - Decimal
    string aux;

    for (size_t i = bit; i <= 439; i++)
    {
        aux += data[i];
        bit++;
    }

    type = binaryToDecimal(aux);

    //Codigo - 8 bits - Decimal
    aux.clear();

    for (size_t i = bit; i <= 447; i++)
    {
        aux += data[i];
        bit++;
    }

    code = binaryToDecimal(aux);

    //Checksum - 16 bits - Hexadecimal
    aux.clear();

    for (size_t i = bit; i <= 463; i++)
    {
        aux += data[i];
        bit++;
    }

    checksum = binaryToDecimal(aux);
}

void ICMPv6::showICMPv6Header()
{
    cout << endl << "               Cabecera ICMPv6" << endl;
    errorType(type, code);
    printf("        Checksum: %02X\n", checksum);
}
