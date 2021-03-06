#include "CabeceraIPv4.h"

CabeceraIPv4::CabeceraIPv4()
{

}

int CabeceraIPv4::binToDecimal(string number)
{
    int total;

    try{
        total = stoull(number, 0, 2);
    }catch(std::invalid_argument& ia){
        cout << endl << "Wrong data composition: " << ia.what() << endl;
    }
    return total;
}

string CabeceraIPv4::toBinary(vector<unsigned char> bytes)
{
    string bin = "";
    int numBytes = 0;

    for(size_t i = 0; i < bytes.size(); i++){
        for(int j = 7; j >= 0; j--){
            bin += ((bytes.at(i) & (1 << j)) ? '1' : '0');
        }
        numBytes++;
    }
    return bin;
}

void CabeceraIPv4::mostrarBinario(string binario)
{
    int numBytes = 0;

    for(size_t i = 0; i < binario.size(); i++){
        cout << binario[i];
        numBytes++;
        if(numBytes == 8){
            cout << " ";
            numBytes = 0;
        }
    }
}


void CabeceraIPv4::setCabeceraIPv4(string bin)
{
    size_t bit = 112;
    //Despues de la cabecera ethernet se queda en el bit 112
     string version, cabecera ,tipoServicio ,longitud ,identificador ,flags, fragmento ,tiempo ,protocolo ,checksum;

    //Version 4 bits, decimal
    for(size_t i = bit; i <= 115; i++){
        version += bin[i];
        bit++;
    }
    versionI = binToDecimal(version);
    //Cabecera 4 bits, decimal - operacion
    for(size_t i = bit; i <= 119; i++){
        cabecera += bin[i];
        bit++;
    }
    cabeceraI = binToDecimal(cabecera);
    //tipoServicio 8 bits, binario - comprobacion
    for(size_t i = bit; i <= 127; i++){
        tipoServicio += bin[i];
        bit++;
    }
    tipoServicioS = tipoServicio;
    //longitud 16 bits, decimal
    for(size_t i = bit; i <= 143; i++){
        longitud += bin[i];
        bit++;
    }
    longitudI = binToDecimal(longitud);
    //identificador 16 bits, decimal
    for(size_t i = bit; i <= 159; i++){
        identificador += bin[i];
        bit++;
    }
    identificadorI = binToDecimal(identificador);
    //flags 3 bits, binario - comprobacion
    for(size_t i = bit; i <= 162; i++){
        flags += bin[i];
        bit++;
    }
    flagsS = flags;
    //fragmento 13 bits, decimal
    for(size_t i = bit; i <= 175; i++){
        fragmento += bin[i];
        bit++;
    }
    fragmentoI = binToDecimal(fragmento);
    //tiempo 8 bits, decimal
    for(size_t i = bit; i <= 183; i++){
        tiempo += bin[i];
        bit++;
    }
    tiempoI = binToDecimal(tiempo);
    //protocolo 8 bits, decimal - comprobacion
    for(size_t i = bit; i <= 191; i++){
        protocolo += bin[i];
        bit++;
    }
    protocoloI = binToDecimal(protocolo);
    //checksum 16 bits, hexadecimal
    for(size_t i = bit; i <= 207; i++){
        checksum += bin[i];
        bit++;
    }
    checksumI = binToDecimal(checksum);
    //dirOrigen 32 bits, decimal
    int bits = 0;
    string byte = "";
    int numBytes = 0;
    for(size_t i = bit; i <= 239; i++){
        if(bits <= 7){
            byte += bin[i];
            bits++;
            if(i == 239){
                dirOrigenA[numBytes] = binToDecimal(byte);
            }
        }else{
            dirOrigenA[numBytes] = binToDecimal(byte);
            numBytes++;
            byte = "";
            bits = 1;
            byte += bin[i];
        }
        bit++;
    }
    bits = 0;
    byte = "";
    numBytes = 0;
    //dirDestino 32 bits, decimal
    for(size_t i = bit; i <= 271; i++){
        if(bits <= 7){
            byte += bin[i];
            bits++;
            if(i == 271){
                dirDestinoA[numBytes] = binToDecimal(byte);
            }
        }else{
            dirDestinoA[numBytes] = binToDecimal(byte);
            numBytes++;
            byte = "";
            bits = 1;
            byte += bin[i];
        }
        bit++;
    }


}

void CabeceraIPv4::mostrarCabeceraIPv4()
{
    cout << endl << "   ***Cabecera IPv4***" << endl;
    cout << "   Version: " << versionI << " (IPv4)" << endl;
    cout << "   Tama???o Cabecera: " << cabeceraI << " Palabras, " << cabeceraI*32 << " bits" << endl;

    //Tipo de servicio***
    cout << "   Tipo de Servicio: " << endl;
    string desglose3 = "";
    string desglose5 = "";
    for(size_t i = 0; i < tipoServicioS.size(); i++){
        if(i <= 2){
            desglose3 += tipoServicioS[i];
        }else{
            desglose5 += tipoServicioS[i];
        }
    }
    tipoServicioDesglose_3(desglose3);
    tipoServicioDesglose_5(desglose5);

    cout << "   Longitud Total: " << longitudI <<endl;
    cout << "   Identificador: " << identificadorI <<endl;

    //Flasgs
    cout << "   Flags: " << flagsS <<endl;
    flags(flagsS);

    cout << "   Posicion Fragmento: " << fragmentoI <<endl;
    cout << "   Tiempo de vida: " << tiempoI <<endl;


    setProtocolo(protocoloI);
    cout << "   Protocolo: " << protocolo <<endl;

    printf("    Checksum: %02X\n", checksumI);
    cout << "   Direccion IP Origen: " << dirOrigenA[0] << "." << dirOrigenA[1] << "." << dirOrigenA[2] << "." << dirOrigenA[3] << endl;
    cout << "   Direccion IP Destino: " << dirDestinoA[0] << "." << dirDestinoA[1] << "." << dirDestinoA[2] << "." << dirDestinoA[3] << endl;

}

void CabeceraIPv4::tipoServicioDesglose_3(string bits)
{
    cout << "   (Desglose de 3 bits)" << endl;
    if(bits == "000"){
        cout << "       Urgencia del mensaje: De Rutina" << endl;
    }else if(bits == "001"){
        cout << "       Urgencia del mensaje: Prioritario" << endl;
    }else if(bits == "010"){
        cout << "       Urgencia del mensaje: Inmediato" << endl;
    }else if(bits == "011"){
        cout << "       Urgencia del mensaje: Relampago" << endl;
    }else if(bits == "100"){
        cout << "       Urgencia del mensaje: Invalidacion Relampago" << endl;
    }else if(bits == "101"){
        cout << "       Urgencia del mensaje: Procesando llamada critica o de emergencia" << endl;
    }else if(bits == "110"){
        cout << "       Urgencia del mensaje: Control de trabajo de internet" << endl;
    }else if(bits == "111"){
        cout << "       Urgencia del mensaje: Control de red" << endl;
    }
}

void CabeceraIPv4::tipoServicioDesglose_5(string bits)
{
    cout << "   (Desglose de 5 bits)" << endl;
    if(bits[0] == '0'){
        cout << "       Retardo: Normal" << endl;
    }else if(bits[0] == '1'){
        cout << "       Retardo: Bajo" << endl;
    }
    if(bits[1] == '0'){
        cout << "       Rendimiento: Normal" << endl;
    }else if(bits[1] == '1'){
        cout << "       Rendimiento: Alto" << endl;
    }
    if(bits[2] == '0'){
        cout << "       Fiabilidad: Normal" << endl;
    }else if(bits[2] == '1'){
        cout << "       Fiabilidad: Alta" << endl;
    }

}

void CabeceraIPv4::flags(string bits)
{
    if(bits[1] == '0'){
        cout << "       Indicador Division: Divisible" << endl;
    }else if(bits[1] == '1'){
        cout << "       Indicador Division: No Divisible" << endl;
    }

    if(bits[2] == '0'){
        cout << "       Indicador Fragmento: Ultimo Fragmento" << endl;
    }else if(bits[2] == '1'){
        cout << "       Indicador Fragmento: Fragmento Intermedio" << endl;
    }
}


void CabeceraIPv4::setProtocolo(int dato)
{
    switch(dato){
        case 1: protocolo = "ICMPv4"; break;
        case 6: protocolo = "TCP"; break;
        case 17: protocolo = "UDP"; break;
        case 58: protocolo = "ICMPv6"; break;
        case 118: protocolo = "STP"; break;
        case 121: protocolo = "SMP"; break;
        default: cout << "Valor no encontrado" << endl;
    }
}

string CabeceraIPv4::getProtocolo()
{
    return protocolo;
}



