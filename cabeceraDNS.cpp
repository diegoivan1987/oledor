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

    //Banderas - 16 bits
    //QR - 1 bit - Decimal
    bitAcumulador += 1;
    aux += data[bit];
    bit++;

    QR = binaryToDecimal(aux);
    aux.clear();

    //Op Code - 4 bits - Decimal
    bitAcumulador += 4;
    for (size_t i = bit; i <= bitAcumulador; i++)
    {
        aux += data[i];
        bit++;
    }

    op_code = binaryToDecimal(aux);
    aux.clear();

    //AA - 1 bit - Decimal
    bitAcumulador += 1;
    aux += data[bit];
    bit++;

    AA = binaryToDecimal(aux);
    aux.clear();

    //TC - 1 bit - Decimal
    bitAcumulador += 1;
    aux += data[bit];
    bit++;

    TC = binaryToDecimal(aux);
    aux.clear();

    //RD - 1 bit - Decimal
    bitAcumulador += 1;
    aux += data[bit];
    bit++;

    RD = binaryToDecimal(aux);
    aux.clear();

    //RA - 1 bit - Decimal
    bitAcumulador += 1;
    aux += data[bit];
    bit++;

    RA = binaryToDecimal(aux);
    aux.clear();

    //Z - 3 bits - Decimal   
    bitAcumulador += 3;
    for (size_t i = bit; i <= bitAcumulador; i++)
    {
        aux += data[i];
        bit++;
    }

    Z = binaryToDecimal(aux);
    aux.clear();

    //Rcode - 4 bits - Decimal
    bitAcumulador += 4;
    for (size_t i = bit; i <= bitAcumulador; i++)
    {
        aux += data[i];
        bit++;
    }

    rCode = binaryToDecimal(aux);
    aux.clear();
}

void DNS::showDNSHeader()
{
    cout << "\n\n ***Cabecera UDP***" << endl;
    printf("ID: %02X\n", id);

    //Impresion de banderas
    cout << "Banderas: " << endl;
    cout << "   -QR: " << QR;

    if (QR == 0)
    {
        cout << " - Consulta" << endl;
    }

    if (QR == 1)
    {
        cout << " - Respuesta" << endl;
    }

    cout << "   -Op Code: " << op_code;

    switch (op_code)
    {
    case 0:
        cout << " - Consulta estandar (QUERY)" << endl;
        break;
    
    case 1:
        cout << " - Consulta inversa (IQUERY)" << endl;
        break;

    case 2:
        cout << " - Solicitud de estado del servidor (STATUS)" << endl;
        break;
    
    default:
        cout << " - Valor reservado" << endl;
        break;
    }

    cout << "   -AA: " << AA;

    if (AA == 0)
    {
        cout << " - Consulta" << endl;
    }

    if (AA == 1)
    {
        cout << " - Respuesta" << endl;
    }

    cout << "   -TC: " << TC;

    if (TC == 0)
    {
        cout << " - No truncado" << endl;
    }

    if (TC == 1)
    {
        cout << " - Truncado" << endl;
    }

    cout << "   -RD: " << RD;

    if (RD == 0)
    {
        cout << " - Resolucion no recursiva" << endl;
    }

    if (RD == 1)
    {
        cout << " - Resolucion recursiva" << endl;
    }

    cout << "   -RA: " << RA;

    if (RA == 0)
    {
        cout << " - No soporta resolucion recursiva" << endl;
    }

    if (RA == 1)
    {
        cout << " - Soporta resolucion recursiva" << endl;
    }

    cout << "   -Z: " << Z << endl;

    cout << "   -Rcode: " << rCode;

    switch (rCode)
    {
    case 0:
        cout << " - No hubo error" << endl;
        break;

    case 1:
        cout << " - Error de formato" << endl;
        break;

    case 2:
        cout << " - Fallo en el servidor" << endl;
        break;

    case 3:
        cout << " - Error en el nombre" << endl;
        break;

    case 4:
        cout << " - No implementado" << endl;
        break;

    case 5:
        cout << " - Rechazado" << endl;
        break;
    
    default:
        cout << " - Desconocido" << endl;
        break;
    }
}