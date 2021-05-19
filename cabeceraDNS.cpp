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
void DNS::setDNSHeader(const string& data, const vector<unsigned char>& domain_name)
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

    //Contadores
    //QDCount - 16 bits - Decimal sin signo
    bitAcumulador += 16;
    for (size_t i = bit; i <= bitAcumulador; i++)
    {
        aux += data[i];
        bit++;
    }

    QDCount = binaryToDecimal(aux);
    aux.clear();

    //ANCount - 16 bits - Decimal sin signo
    bitAcumulador += 16;
    for (size_t i = bit; i <= bitAcumulador; i++)
    {
        aux += data[i];
        bit++;
    }

    ANCount = binaryToDecimal(aux);
    aux.clear();

    //NSCount - 16 bits - Decimal sin signo
    bitAcumulador += 16;
    for (size_t i = bit; i <= bitAcumulador; i++)
    {
        aux += data[i];
        bit++;
    }

    NSCount = binaryToDecimal(aux);
    aux.clear();

    //ARCount - 16 bits - Decimal sin signo
    bitAcumulador += 16;
    for (size_t i = bit; i <= bitAcumulador; i++)
    {
        aux += data[i];
        bit++;
    }

    ARCount = binaryToDecimal(aux);
    aux.clear();

    showDNSHeader();

    //Campo de pregunta
    if (QDCount > 0)
    {
        for (size_t a = 0; a < QDCount; a++)
        {
            //Nombre de dominio - Longitud variable - La longitud total en bytes queda almacenada en i 
            unsigned char aux_char;
            int i = 0;
            aux_char = domain_name[i];
            while (aux_char != 0)
            {
                i++;
                aux_char = domain_name[i];     
            }

            //Se incrementa el contador de los bytes para tomar en cuenta la ultima posicion del nombre de dominio
            i++;
            i = i*8;
            bitAcumulador += i;
            bit += i;

            //Tipo - 16 bits - Decimal
            bitAcumulador += 16;
            for (size_t i = bit; i <= bitAcumulador; i++)
            {
                aux += data[i];
                bit++;
            }

            Qtype = binaryToDecimal(aux);
            aux.clear();

            //Clase - 16 bits - Decimal
            bitAcumulador += 16;
            for (size_t i = bit; i <= bitAcumulador; i++)
            {
                aux += data[i];
                bit++;
            }

            Qclass = binaryToDecimal(aux);
            aux.clear();

            showDNSQuestions(domain_name);
        }
    }

    //Campo de respuesta
    if (ANCount > 0)
    {
        for (size_t a = 0; a < ANCount; a++)
        {
            //Nombre de dominio - Longitud variable - La longitud total en bytes queda almacenada en i 
            unsigned char aux_char;
            int i = 0;
            aux_char = domain_name[i];
            while (aux_char != 0)
            {
                i++;
                aux_char = domain_name[i];     
            }

            //Se incrementa el contador de los bytes para tomar en cuenta la ultima posicion del nombre de dominio
            i++;
            i = i*8;
            bitAcumulador += i;
            bit += i;

            //Tipo - 16 bits - Decimal
            bitAcumulador += 16;
            for (size_t i = bit; i <= bitAcumulador; i++)
            {
                aux += data[i];
                bit++;
            }

            Atype = binaryToDecimal(aux);
            aux.clear();

            //Clase - 16 bits - Decimal
            bitAcumulador += 16;
            for (size_t i = bit; i <= bitAcumulador; i++)
            {
                aux += data[i];
                bit++;
            }

            Aclass = binaryToDecimal(aux);
            aux.clear();

            //Tiempo de vida - 32 bits - Decimal
            bitAcumulador += 32;
            for (size_t i = bit; i <= bitAcumulador; i++)
            {
                aux += data[i];
                bit++;
            }
            
            Attl = binaryToDecimal(aux);
            aux.clear();

            //Longitud de datos - 16 bits - Decimal
            bitAcumulador += 16;
            for (size_t i = bit; i <= bitAcumulador; i++)
            {
                aux += data[i];
                bit++;
            }
            
            Alength = binaryToDecimal(aux);
            aux.clear();

            //RData - Depende del tipo
            switch (Atype)
            {
            case 1:
                //Respuesta - Debe de tener una direccion IP
                bitAcumulador += 8;
                for (size_t i = bit; i <= bitAcumulador; i++)
                {
                    aux += data[i];
                    bit++;
                }

                AIP[0] = binaryToDecimal(aux);
                aux.clear();

                bitAcumulador += 8;
                for (size_t i = bit; i <= bitAcumulador; i++)
                {
                    aux += data[i];
                    bit++;
                }

                AIP[1] = binaryToDecimal(aux);
                aux.clear();

                bitAcumulador += 8;
                for (size_t i = bit; i <= bitAcumulador; i++)
                {
                    aux += data[i];
                    bit++;
                }

                AIP[2] = binaryToDecimal(aux);
                aux.clear();
                
                bitAcumulador += 8;
                for (size_t i = bit; i <= bitAcumulador; i++)
                {
                    aux += data[i];
                    bit++;
                }

                AIP[3] = binaryToDecimal(aux);
                aux.clear();
                break;

            case 15:
                //Prioridad de MX - 16 bits
                bitAcumulador += 16;
                for (size_t i = bit; i <= bitAcumulador; i++)
                {
                    aux += data[i];
                    bit++;
                }

                MXpriority = binaryToDecimal(aux);
                aux.clear();
                break;
            
            default:
                break;
            }

            showDNSAnswers(domain_name);
        }
        
    }
    
}

void DNS::showDNSHeader()
{
    cout << "\n\n ***Cabecera DNS***" << endl;
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

    cout << "Contadores: " << endl;
    cout << "   -QDCount: " << QDCount  << " entrada(s)" << endl;
    cout << "   -ANCount: " << ANCount  << " entrada(s)" << endl;
    cout << "   -NSCount: " << NSCount  << " entrada(s)" << endl;
    cout << "   -ARCount: " << ARCount  << " entrada(s)" << endl;
}

void DNS::showDNSQuestions(const vector<unsigned char>& domain_name)
{
    //Campo de pregunta
    cout << "Campo de pregunta" << endl;
    cout << "   -Nombre de dominio: ";
    if (QDCount > 0)
    {
        unsigned char aux_char;
        int i = 0;
        aux_char = domain_name[i];
        while (aux_char != 0)
        {
            i++;
            aux_char = domain_name[i];
            if (aux_char >= 97 && aux_char <=122)
            {
                cout << aux_char;
            }
            else if (aux_char != 0)
            {
                cout << ".";
            }      
        }

        cout << endl << "   -Tipo: " << Qtype << " - ";
        switch (Qtype)
        {
        case 1:
            cout << "A" << endl;
            break;

        case 5:
            cout << "CNAME" << endl;
            break;

        case 13:
            cout << "HINFO" << endl;
            break;

        case 15:
            cout << "MX" << endl;
            break;

        case 22:
            cout << "NS" << endl;
            break;

        case 23:
            cout << "NS" << endl;
            break;
        
        default:
            cout << "Valor desconocido" << endl;
            break;
        }

        cout << "   -Clase: " << Qclass << " - ";

        switch (Qclass)
        {
        case 1:
            cout << "IN" << endl;
            break;

        case 3:
            cout << "CH" << endl;
            break;
        
        default:
            cout << "Valor desconocido" << endl;
            break;
        }
    }
}

void DNS::showDNSAnswers(const vector<unsigned char>& domain_name)
{
     //Campo de respuesta
    cout << "Campo de respuesta" << endl;
    cout << "   -Nombre de dominio: ";
    if (ANCount > 0)
    {
        unsigned char aux_char;
        int i = 0;
        aux_char = domain_name[i];
        while (aux_char != 0)
        {
            i++;
            aux_char = domain_name[i];
            if (aux_char >= 97 && aux_char <=122)
            {
                cout << aux_char;
            }
            else if (aux_char != 0)
            {
                cout << ".";
            }      
        }
        i++;

        cout << endl << "   -Tipo: " << Atype << " - ";
        switch (Atype)
        {
        case 1:
            cout << "A" << endl;
            break;

        case 5:
            cout << "CNAME" << endl;
            break;

        case 13:
            cout << "HINFO" << endl;
            break;

        case 15:
            cout << "MX" << endl;
            break;

        case 22:
            cout << "NS" << endl;
            break;

        case 23:
            cout << "NS" << endl;
            break;
        
        default:
            cout << "Valor desconocido" << endl;
            break;
        }

        cout << "   -Clase: " << Aclass << " - ";

        switch (Aclass)
        {
        case 1:
            cout << "IN" << endl;
            break;

        case 3:
            cout << "CH" << endl;
            break;
        
        default:
            cout << "Valor desconocido" << endl;
            break;
        }

        cout << "   -Tiempo de vida: " << Attl << " segundos" << endl;
        cout << "   -Longitud de datos: " << Alength << " bytes" << endl;

        i = i + 10;

        cout << "   -RDATA: " << endl;
        switch (Atype)
        {
        case 1:
            cout << "       A: " << AIP[0] << "." << AIP[1] << "." << AIP[2] << "." << AIP[3];
            break;

        case 5:
            cout << "       CNAME: " ;
            unsigned char aux_char;
            aux_char = domain_name[i];
            while (aux_char != 0)
            {
                i++;
                aux_char = domain_name[i];
                if (aux_char >= 97 && aux_char <=122)
                {
                    cout << aux_char;
                }
                else if (aux_char != 0)
                {
                    cout << ".";
                }      
            }
            break;

        case 6:
            cout << "       SOA" << endl;
            break;

        case 12:
            cout << "       PTR: " << endl;
            aux_char = domain_name[i];
            while (aux_char != 0)
            {
                i++;
                aux_char = domain_name[i];
                if (aux_char >= 97 && aux_char <=122)
                {
                    cout << aux_char;
                }
                else if (aux_char != 0)
                {
                    cout << ".";
                }      
            }
            break;

        case 15:
            cout << "       MX: " << endl;
            cout << "           Prioridad: " << MXpriority << endl;
            cout << "           Nombre del ordenador: ";
            i = i + 2;
            aux_char = domain_name[i];
            while (aux_char != 0)
            {
                i++;
                aux_char = domain_name[i];
                if (aux_char >= 97 && aux_char <=122)
                {
                    cout << aux_char;
                }
                else if (aux_char != 0)
                {
                    cout << ".";
                }      
            }
            break;

        case 22:
            cout << "       NS: ";
            aux_char = domain_name[i];
            while (aux_char != 0)
            {
                i++;
                aux_char = domain_name[i];
                if (aux_char >= 97 && aux_char <=122)
                {
                    cout << aux_char;
                }
                else if (aux_char != 0)
                {
                    cout << ".";
                }      
            }
            break;

        case 23:
            cout << "       NS: ";
            aux_char = domain_name[i];
            while (aux_char != 0)
            {
                i++;
                aux_char = domain_name[i];
                if (aux_char >= 97 && aux_char <=122)
                {
                    cout << aux_char;
                }
                else if (aux_char != 0)
                {
                    cout << ".";
                }      
            }
            break;
        
        default:
            cout << "Valor desconocido" << endl;
            break;
        }

    }
}