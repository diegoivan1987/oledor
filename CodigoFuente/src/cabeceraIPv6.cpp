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

    try{
        total = stoull(number, 0, 2);
    }catch(std::invalid_argument& ia){
        cout << endl << "Wrong data composition: " << ia.what() << endl;
    }
    return total;
}

//Funeciones switch para los distintos atributos
string IPv6::trafficClassPriority(string bits)
{
    if (bits == "000")
    {
        return "    De Rutina";
    }

    if (bits == "001")
    {
        return "    Prioritario";
    }

    if (bits == "010")
    {
        return "    Inmediato";
    }

    if (bits == "011")
    {
        return "    Relampago";
    }

    if (bits == "100")
    {
        return "    Invalidacion Relampago";
    }

    if (bits == "101")
    {
        return "    Procesando llamada critica o de emergencia";
    }

    if (bits == "110")
    {
        return "    Control de trabajo de internet";
    }

    if (bits == "111")
    {
        return "    Control de red";
    }
    else
    {
        return "    Prioridad desconocida";
    }
}

void IPv6::trafficClassFeatures(string bits)
{
    if(bits[0] == '0')
    {
        cout << "       -Retardo: Normal" << endl;
    }

    if(bits[0] == '1')
    {
        cout <<  "      -Retardo: Bajo" << endl;
    }

    if(bits[1] == '0')
    {
        cout << "       -Rendimiento: Normal" << endl;
    }

    if(bits[1] == '1')
    {
        cout << "       -Rendimiento: Alto" << endl;
    }

    if(bits[2] == '0')
    {
        cout << "       -Fiabilidad: Normal" << endl;
    }

    if(bits[2] == '1')
    {
        cout << "       -Fiabilidad: Alta" << endl;
    }
}

string IPv6::nextHeader(int next)
{
    switch(next)
    {
        case 1:
            return "ICMPv4";
            break;

        case 6:
            return "TCP";
            break;

        case 17:
            return "UDP";
            break;

        case 58:
            return "ICMPv6";
            break;

        case 118:
            return "STP";
            break;

        case 121:
            return "SMP";
            break;

        default:
            return "Valor no encontrado";
            break;
    }
}

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
    for (size_t i = bit; i <= 123; i++)
    {
        traffic_class += data[i];
        bit++;
    }

    //Etiqueta de flujo - 20 bits - decimal
    string ipv6_flowLabel;

    for (size_t i = bit; i <= 143; i++)
    {
        ipv6_flowLabel += data[i];
        bit++;
    }

    flow_label = binaryToDecimal(ipv6_flowLabel);

    //Tamaño de datos - 16 bits - Decimal
    string ipv6_payloadLength;

    for (size_t i = bit; i <= 159; i++)
    {
        ipv6_payloadLength += data[i];
        bit++;
    }

    payload_length = binaryToDecimal(ipv6_payloadLength);

    //Encabezado siguiente - 8 bits - Decimal
    string ipv6_nextHeader;

    for (size_t i = bit; i <= 167; i++)
    {
        ipv6_nextHeader += data[i];
        bit++;
    }

    next_header = binaryToDecimal(ipv6_nextHeader);

    //Limite de salto - 8 bits - Decimal
    string ipv6_hopLimit;

    for (size_t i = bit; i <= 175; i++)
    {
        ipv6_hopLimit += data[i];
        bit++;
    }

    hop_limit = binaryToDecimal(ipv6_hopLimit);

    //Direccion de origen - 128 bits - Hexadecimal
    string ipv6_source_aux;

    //1er byte
    for (size_t i = bit; i <= 183; i++)
    {
        ipv6_source_aux += data[i];
        bit++;
    }

    source_address[0] = binaryToDecimal(ipv6_source_aux);

    //2do byte
    ipv6_source_aux = "";
    for (size_t i = bit; i <= 191; i++)
    {
        ipv6_source_aux += data[i];
        bit++;
    }

    source_address[1] = binaryToDecimal(ipv6_source_aux);

    //3er byte
    ipv6_source_aux = "";
    for (size_t i = bit; i <= 199; i++)
    {
        ipv6_source_aux += data[i];
        bit++;
    }

    source_address[2] = binaryToDecimal(ipv6_source_aux);

    //4to byte
    ipv6_source_aux = "";
    for (size_t i = bit; i <= 207; i++)
    {
        ipv6_source_aux += data[i];
        bit++;
    }

    source_address[3] = binaryToDecimal(ipv6_source_aux);

    //5to byte
    ipv6_source_aux = "";
    for (size_t i = bit; i <= 215; i++)
    {
        ipv6_source_aux += data[i];
        bit++;
    }

    source_address[4] = binaryToDecimal(ipv6_source_aux);

    //6to byte
    ipv6_source_aux = "";
    for (size_t i = bit; i <= 223; i++)
    {
        ipv6_source_aux += data[i];
        bit++;
    }

    source_address[5] = binaryToDecimal(ipv6_source_aux);

    //7mo byte
    ipv6_source_aux = "";
    for (size_t i = bit; i <= 231; i++)
    {
        ipv6_source_aux += data[i];
        bit++;
    }

    source_address[6] = binaryToDecimal(ipv6_source_aux);

    //8vo byte
    ipv6_source_aux = "";
    for (size_t i = bit; i <= 239; i++)
    {
        ipv6_source_aux += data[i];
        bit++;
    }

    source_address[7] = binaryToDecimal(ipv6_source_aux);

    //9
    ipv6_source_aux = "";
    for (size_t i = bit; i <= 247; i++)
    {
        ipv6_source_aux += data[i];
        bit++;
    }

    source_address[8] = binaryToDecimal(ipv6_source_aux);

    //10
    ipv6_source_aux = "";
    for (size_t i = bit; i <= 255; i++)
    {
        ipv6_source_aux += data[i];
        bit++;
    }

    source_address[9] = binaryToDecimal(ipv6_source_aux);

    //11
    ipv6_source_aux = "";
    for (size_t i = bit; i <= 263; i++)
    {
        ipv6_source_aux += data[i];
        bit++;
    }

    source_address[10] = binaryToDecimal(ipv6_source_aux);

    //12
    ipv6_source_aux = "";
    for (size_t i = bit; i <= 271; i++)
    {
        ipv6_source_aux += data[i];
        bit++;
    }

    source_address[11] = binaryToDecimal(ipv6_source_aux);

    //13
    ipv6_source_aux = "";
    for (size_t i = bit; i <= 279; i++)
    {
        ipv6_source_aux += data[i];
        bit++;
    }

    source_address[12] = binaryToDecimal(ipv6_source_aux);

    //14
    ipv6_source_aux = "";
    for (size_t i = bit; i <= 287; i++)
    {
        ipv6_source_aux += data[i];
        bit++;
    }

    source_address[13] = binaryToDecimal(ipv6_source_aux);

    //15
    ipv6_source_aux = "";
    for (size_t i = bit; i <= 295; i++)
    {
        ipv6_source_aux += data[i];
        bit++;
    }

    source_address[14] = binaryToDecimal(ipv6_source_aux);

    //16
    ipv6_source_aux = "";
    for (size_t i = bit; i <= 303; i++)
    {
        ipv6_source_aux += data[i];
        bit++;
    }

    source_address[15] = binaryToDecimal(ipv6_source_aux);

    //Direccion de destino - 128 bits - Hexadecimal
    string ipv6_dest_aux;

    //1er byte
    for (size_t i = bit; i <= 311; i++)
    {
        ipv6_dest_aux += data[i];
        bit++;
    }

    destination_address[0] = binaryToDecimal(ipv6_dest_aux);

    //2do byte
    ipv6_dest_aux = "";
    for (size_t i = bit; i <= 319; i++)
    {
        ipv6_dest_aux += data[i];
        bit++;
    }

    destination_address[1] = binaryToDecimal(ipv6_dest_aux);

    //3er byte
    ipv6_dest_aux = "";
    for (size_t i = bit; i <= 327; i++)
    {
        ipv6_dest_aux += data[i];
        bit++;
    }

    destination_address[2] = binaryToDecimal(ipv6_dest_aux);

    //4to byte
    ipv6_dest_aux = "";
    for (size_t i = bit; i <= 335; i++)
    {
        ipv6_dest_aux += data[i];
        bit++;
    }

    destination_address[3] = binaryToDecimal(ipv6_dest_aux);

    //5to byte
    ipv6_dest_aux = "";
    for (size_t i = bit; i <= 343; i++)
    {
        ipv6_dest_aux += data[i];
        bit++;
    }

    destination_address[4] = binaryToDecimal(ipv6_dest_aux);

    //6to byte
    ipv6_dest_aux = "";
    for (size_t i = bit; i <= 351; i++)
    {
        ipv6_dest_aux += data[i];
        bit++;
    }

    destination_address[5] = binaryToDecimal(ipv6_dest_aux);

    //7mo byte
    ipv6_dest_aux = "";
    for (size_t i = bit; i <= 359; i++)
    {
        ipv6_dest_aux += data[i];
        bit++;
    }

    destination_address[6] = binaryToDecimal(ipv6_dest_aux);

    //8vo byte
    ipv6_dest_aux = "";
    for (size_t i = bit; i <= 367; i++)
    {
        ipv6_dest_aux += data[i];
        bit++;
    }

    destination_address[7] = binaryToDecimal(ipv6_dest_aux);

    //9
    ipv6_dest_aux = "";
    for (size_t i = bit; i <= 375; i++)
    {
        ipv6_dest_aux += data[i];
        bit++;
    }

    destination_address[8] = binaryToDecimal(ipv6_dest_aux);

    //10
    ipv6_dest_aux = "";
    for (size_t i = bit; i <= 383; i++)
    {
        ipv6_dest_aux += data[i];
        bit++;
    }

    destination_address[9] = binaryToDecimal(ipv6_dest_aux);

    //11
    ipv6_dest_aux = "";
    for (size_t i = bit; i <= 391; i++)
    {
        ipv6_dest_aux += data[i];
        bit++;
    }

    destination_address[10] = binaryToDecimal(ipv6_dest_aux);

    //12
    ipv6_dest_aux = "";
    for (size_t i = bit; i <= 399; i++)
    {
        ipv6_dest_aux += data[i];
        bit++;
    }

    destination_address[11] = binaryToDecimal(ipv6_dest_aux);

    //13
    ipv6_dest_aux = "";
    for (size_t i = bit; i <= 407; i++)
    {
        ipv6_dest_aux += data[i];
        bit++;
    }

    destination_address[12] = binaryToDecimal(ipv6_dest_aux);

    //14
    ipv6_dest_aux = "";
    for (size_t i = bit; i <= 415; i++)
    {
        ipv6_dest_aux += data[i];
        bit++;
    }

    destination_address[13] = binaryToDecimal(ipv6_dest_aux);

    //15
    ipv6_dest_aux = "";
    for (size_t i = bit; i <= 423; i++)
    {
        ipv6_dest_aux += data[i];
        bit++;
    }

    destination_address[14] = binaryToDecimal(ipv6_dest_aux);

    //16
    ipv6_dest_aux = "";
    for (size_t i = bit; i <= 431; i++)
    {
        ipv6_dest_aux += data[i];
        bit++;
    }

    destination_address[15] = binaryToDecimal(ipv6_dest_aux);
}

void IPv6::showIPv6Header()
{
    cout << "\n       ***Cabecera IPv6***" << endl;
    cout << "   Version: " << version << endl;

    string priority, features;
    for (size_t i = 0; i < traffic_class.size(); i++)
    {
        if (i <= 2)
        {
            priority += traffic_class[i];
        }
        else
        {
            features += traffic_class[i];
        }
    }

    cout << "   Prioridad: " <<  priority << " - "  << trafficClassPriority(priority) << endl;
    cout << "   Caracteristicas del servicio: " << endl;
    trafficClassFeatures(features);
    cout << "   Etiqueta de flujo: " << flow_label << endl;
    cout << "   Longitud de datos: " << payload_length << " bytes" << endl;
    next_header_aux = nextHeader(next_header);
    cout << "   Encabezado siguiente: " << next_header_aux << endl;
    cout << "   Limite de salto: " << hop_limit << endl;
    printf("    Direccion de origen: %02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X\n",
            source_address[0], source_address[1], source_address[2], source_address[3], source_address[4],
            source_address[5], source_address[6], source_address[7], source_address[8], source_address[9],
            source_address[10], source_address[11], source_address[12], source_address[13], source_address[14], source_address[15]);
    printf("    Direccion de destino: %02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X\n",
        destination_address[0], destination_address[1], destination_address[2], destination_address[3], destination_address[4],
        destination_address[5], destination_address[6], destination_address[7], destination_address[8], destination_address[9],
        destination_address[10], destination_address[11], destination_address[12], destination_address[13], destination_address[14], destination_address[15]);
}

string IPv6::getNextHeader()
{
    return next_header_aux;
}
