
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <cstdlib>
#include <stdio.h>
#include "rlutil.h"
#include <string.h>

using namespace std;
int indentificarJugada(int dados[6]);
void inventarDado(int dados[6]);
//int sumarPuntos();
void Printxy (const char *texto, int posx, int posy);
void PrintAscii (char ascii, int posx, int posy);
void Recuadro(int ancho, int alto);
void RecuadroHor (int ancho, int alto);
void RecuadroVer (int ancho, int alto);
void RecuadroVer2 (int inicioX, int ancho, int alto);
void RecuadroMenu(const char *texto, int ancho, int alto);
void RecuadroPartida(std::string jugador, int ronda, int puntajeTotal);
void mostrarPuntos (int ancho, int alto);
void puntosGanadores (string ganador[10], int puntos[10],int ancho, int alto);
void dibujarDados2 (int dado, int posx, int posy);
void borrarPantalla (int posIx, int posIy, int posFx, int posFy);
void RecuadroPartida2(std::string jugador, int ronda, int puntajeTotal, int Tirada, int puntos);
void RecuadroCambioTurno(int ronda,std::string jugador1,std::string jugador2,int TablaPuntuacion[2]);



void RecuadroCambioTurno(int ronda,std::string jugador1,std::string jugador2,int TablaPuntuacion[2]){
    //borrarPantalla(5,7,105,18);
    rlutil::cls();
    Recuadro(120,30);
    rlutil::locate(50,14);
    cout<<"Fin de la ronda nro: "<<ronda<<".";
    rlutil::locate(52,15);
    cout<<"Puntajes parciales:";
    rlutil::locate(47,16);
    cout<<jugador1<<" tiene sumados "<<TablaPuntuacion[0]<<" puntos.";
    rlutil::locate(47,17);
    cout<<jugador2<<" tiene sumados "<<TablaPuntuacion[1]<<" puntos.";
}


//TIRADA DE DADOS.

void inventarDado(int dados[6]){
    int i,ValorInventado,x=40,y=15;
    //RecuadroPartida(jugador,ronda,Puntos);
    Printxy("Ingrese uno por uno los valores que van a formar parte de la jugada inventada.",26,12);
    Printxy("Pulse ENTER para ingresar cada uno de ellos.",37,13);
    for(i=0;i<6;i++){
        rlutil::locate(x,y);
        std::cin>>ValorInventado;
        dados[i]=ValorInventado;
        x+=5;
    }
    Printxy("                                                                   ",35,10);
}

void tiradaDados (int dados[6]){

    int i;
    srand(time(0));
    for(i=0;i<6;i++){
        dados[i]=(rand()%6)+1;
        Sleep(300);
        //std::cout<<v[i];
    }
}

int identificarJugada(int dados[6]){
    int x,i,e,Acumulador,Repetidos,Puntos,ValorDado=0, Esc[6],ContadorEscalera,DadoRepetido;
    bool Trio,Sexteto,Sexteto6,Escalera=false;
    Puntos=0;
//SEXTETO6
    Acumulador=0;
    for(i=0;i<=5;i++){
        Acumulador+=dados[i];
        //cout<<"En el acumulador hay: "<<Acumulador<<endl;
    }
    if(Acumulador==36){
        Sexteto6=true;
        Puntos=0;
        Printxy("Sacaste seis 6",56,20);
        Printxy("Esta ronda no sumas.",56,21);
    }
//ESCALERA
    ContadorEscalera=0;
    for (i=0 ; i<=5 ; i++){          //CREACION DE VECTOR ESCALERA
        Esc[i]=i+1;
    }

    for(e=0;e<=5;e++){
        if(dados[e]==Esc[e]){       //COMPARACION DE ESCALERA CON DADOS
            ContadorEscalera++;
        }
    }
    if(ContadorEscalera==6){
        Escalera=true;
        Puntos=-1;
        Printxy("La jugada es escalera!",52,19);
    }
//Sexteto X (Seis dados iguales expecto en el caso del nro 6)
    Repetidos=0;
    for(ValorDado=1;ValorDado<=5;ValorDado++){
        for(i=0;i<6;i++){
            if(dados[i]==ValorDado){
                Repetidos++;
            }
            if (Repetidos==6){
                Sexteto=true;
                Puntos=(ValorDado*50);
                Printxy("La jugada es un sexteto.",50,20);
            }
        }
        Repetidos=0;
    }
//Trio X++ (TresDados o mas con el mismo valor, hasta 5)
   ValorDado=0;
   DadoRepetido=0;
   int RepetidoMax=0,CantidadDeRep=0;
    for(ValorDado=1;ValorDado<=6;ValorDado++){
        Repetidos=0;
        for(i=0;i<=5;i++){
            DadoRepetido=ValorDado;
            if(dados[i]==ValorDado){
                Repetidos++;
            }
            if(Repetidos>=3){
                RepetidoMax=ValorDado;
                CantidadDeRep=Repetidos;
            }


        }
        //cout<<"La cantidad de repetidos en el valor de dado:"<<DadoRepetido<<" . Es de :"<<Repetidos<<endl;
    }
    if (CantidadDeRep>=3&&CantidadDeRep<=5){
        Trio=true;
        Puntos=(RepetidoMax*10);
        Printxy("La jugada es un trio.",51,20);
        }
//Jugada normal
    if (Sexteto6==false&&Sexteto==false&&Escalera==false&&Trio==false){ //no tiene 3 o mas repetidos, no es trio.
        for(i=0;i<=5;i++){
            Puntos+=dados[i];
            Printxy("Jugada normal, sumas el valor de los dados.",40,20);
        }
    }

    return Puntos;
}


void Recuadro(int ancho, int alto){//RECUADRO DEL PROGRAMA

    //rlutil::setColor(rlutil::GREEN);
    PrintAscii(201,1,1);
    PrintAscii(187,ancho,1);
    PrintAscii(200,1,alto);
    PrintAscii(188,ancho,alto);

    for(int i=2 ; i<ancho ; i++){
        PrintAscii(205,i,1);
        PrintAscii(205,i,alto);
    }

    for(int i=2 ; i<alto ; i++){
        PrintAscii(186,1,i);
        PrintAscii(186,ancho,i);
    }
    //rlutil::setColor(rlutil::WHITE);
}

void RecuadroPartida(std::string jugador, int ronda, int puntajeTotal){

    //rlutil::cls();
    Recuadro(120,30);
    RecuadroHor(120,5);
    RecuadroVer(40,5);
    RecuadroVer(80,5);
    Printxy("TURNO DE ",10,3);
    std::cout<<jugador;
    Printxy("RONDA N ",55,3);
    std::cout<<ronda;
    Printxy("PUNTAJE TOTAL: ",90,3);
    std::cout<<puntajeTotal;

}

void RecuadroPartida2(std::string jugador, int ronda, int puntajeTotal, int Tirada, int puntos){

    //rlutil::cls();
    Recuadro(120,30);
    RecuadroHor(120,5);
    RecuadroVer(40,5);
    RecuadroVer(80,5);
    RecuadroHor(120,26);
    RecuadroVer2(26,60,30);
    Printxy("TURNO DE ",10,3);
    std::cout<<jugador;
    Printxy("RONDA N ",55,3);
    std::cout<<ronda;
    Printxy("PUNTAJE TOTAL: ",90,3);
    std::cout<<puntajeTotal;
    Printxy("TIRADA N: ",10,28);
    std::cout<<Tirada;
    Printxy("PUNTOS DE LA TIRADA: ",80,28);
    std::cout<<puntos;

}

void RecuadroMenu(const char *texto, int ancho, int alto){

    Recuadro(ancho,alto);
    RecuadroHor(ancho,5);
    rlutil::setColor(rlutil::MAGENTA);
    Printxy(texto,45,3);
    rlutil::setColor(rlutil::WHITE);

}



void RecuadroHor (int ancho, int alto){//HACE UNAS LINEAS HORIZONTALES EN PANTALLA

    PrintAscii(204,1,alto);
    PrintAscii(185,ancho,alto);

    for (int i=2 ; i<ancho ; i++){
        PrintAscii(205,i,alto);
    }
}

void RecuadroVer (int ancho, int alto){//HACE UNAS LINEAS VERTICALES EN PANTALLA

    PrintAscii(203,ancho,1);
    PrintAscii(202,ancho,alto);

    for (int i=2 ; i<alto ; i++){
        PrintAscii(186,ancho,i);
    }
}

void RecuadroVer2 (int inicioY, int ancho, int finalY){//HACE UNAS LINEAS VERTICALES EN PANTALLA

    PrintAscii(203,ancho,inicioY);
    PrintAscii(202,ancho,finalY);

    for (int i=1 ; i<(finalY-inicioY) ; i++){
        PrintAscii(186,ancho,inicioY+i);
    }
}

void PrintAscii (char ascii, int posx, int posy){//IMPRIME CARACTERES ASCII

    rlutil::locate(posx,posy);
    std::cout<<(char)ascii;

}

void Printxy (const char *texto, int posx, int posy){//IMPRIME TEXTO EN PANTALLA DONDE SE LE INDIQUE

    rlutil::locate(posx,posy);
    std::cout<<texto;

}

void mostrarPuntos (int ancho, int alto){

    int y=8;
    Recuadro(ancho, alto);
    RecuadroHor(ancho, 5);
    Printxy("MEJORES PUNTUACIONES", (ancho/2)-10,3);
    Printxy("NOMBRE", (ancho/2)-5,7);
    Printxy("PUNTOS", 90,7);
    for(int i=1; i<11 ; i++){
        rlutil::locate(28,y+(i*2));
        std::cout<<i;
        Printxy(": ",30,y+(i*2));
        Printxy(".....",(ancho/2)-5,y+(i*2));
        Printxy("...",91,y+(i*2));
    }
}

void puntosGanadores (string ganador[10], int puntos[10],int ancho, int alto){

    int aux, y=8, h=0;
    string nombreaux;
    for(int i=0 ; i<10 ; i++){
        for (int j=i+1; j<10 ; j++){
            if (puntos[i]<puntos[j]){
                aux=puntos[i];
                puntos[i]=puntos[j];
                puntos[j]=aux;
                nombreaux=ganador[i];
                ganador[i]=ganador[j];
                ganador[j]=nombreaux;
            }
        }
    }

    while(puntos[h]!=0){

        rlutil::locate((ancho/2)-5,y+(h*2)+2);
        std::cout<<ganador[h];
        rlutil::locate(91,y+(h*2)+2);
        std::cout<<puntos[h];
        h++;
    }

}

/*void dibujarDados (int dado, int posx, int posy){//RESIVE UN ENTERO Y DIBUJA EL DADO CORRESPONDIENTE DONDE SE LO INDIQUE

    rlutil::locate(posx+1, posy);
    for (int i=0 ; i<9 ; i++){
        std::cout << "-";
    }
    //std::cout<<std::endl;
    rlutil::locate(posx, posy+1);
    for (int i=0 ; i<6 ; i++){
        std::cout << "|";
        for (int j=0 ; j<9 ; j++){
            std::cout << " ";
        }
        std::cout << "|" << std::endl;
        rlutil::locate(posx, posy+i+1);
    }
    rlutil::locate(posx+1, posy+6);
    for (int i=0 ; i<9 ; i++){
        std::cout << "-";
    }

    rlutil::locate(posx+1, posy+2);
    switch (dado){

    case 1://DIBUJA 1
        std::cout<<"         ";
        rlutil::locate(posx+1,posy+3);
        std::cout<<"    *    ";
        rlutil::locate(posx+1,posy+4);
        std::cout<<"         ";
        break;

    case 2://DIBUJA 2
        std::cout<<"         ";
        rlutil::locate(posx+1,posy+3);
        std::cout<<"  *   *  ";
        rlutil::locate(posx+1,posy+4);
        std::cout<<"         ";
        break;

    case 3://DIBUJA 3
        std::cout<<"    *    ";
        rlutil::locate(posx+1,posy+3);
        std::cout<<"    *    ";
        rlutil::locate(posx+1,posy+4);
        std::cout<<"    *    ";
        break;

    case 4://DIBUJA 4
        std::cout<<"  *   *  ";
        rlutil::locate(posx+1,posy+3);
        std::cout<<"         ";
        rlutil::locate(posx+1,posy+4);
        std::cout<<"  *   *  ";
        break;

    case 5://DIBUJA 5
        std::cout<<"  *   *  ";
        rlutil::locate(posx+1,posy+3);
        std::cout<<"    *    ";
        rlutil::locate(posx+1,posy+4);
        std::cout<<"  *   *  ";
        break;

    case 6://DIBUJA 6
        std::cout<<"  *   *  ";
        rlutil::locate(posx+1,posy+3);
        std::cout<<"  *   *  ";
        rlutil::locate(posx+1,posy+4);
        std::cout<<"  *   *  ";
        break;

    }

}*/

void dibujarDados2 (int dado, int posx, int posy){//RESIVE UN ENTERO Y DIBUJA EL DADO CORRESPONDIENTE DONDE SE LO INDIQUE

    //rlutil::setColor(rlutil::LIGHTRED);
    for (int i=0 ; i<11 ; i++){
        PrintAscii(220,posx+i,posy);
    }
    for (int i=1 ; i<6 ; i++){
        PrintAscii(219,posx,posy+i);
        for (int j=0 ; j<9 ; j++){
            std::cout <<" ";
        }
        PrintAscii(219,posx+10,posy+i);
    }
    for (int i=0 ; i<11 ; i++){
        PrintAscii(223,posx+i,posy+6);
    }

    switch (dado){

    case 1://DIBUJA 1

        PrintAscii(223,posx+5,posy+3);
        break;

    case 2://DIBUJA 2
        PrintAscii(223,posx+3,posy+3);
        PrintAscii(223,posx+7,posy+3);
        break;

    case 3://DIBUJA 3
        PrintAscii(223,posx+5,posy+2);
        PrintAscii(223,posx+5,posy+3);
        PrintAscii(223,posx+5,posy+4);
        break;

    case 4://DIBUJA 4
        PrintAscii(223,posx+3,posy+2);
        PrintAscii(223,posx+7,posy+2);
        PrintAscii(223,posx+3,posy+4);
        PrintAscii(223,posx+7,posy+4);
        break;

    case 5://DIBUJA 5
        PrintAscii(223,posx+3,posy+2);
        PrintAscii(223,posx+7,posy+2);
        PrintAscii(223,posx+5,posy+3);
        PrintAscii(223,posx+3,posy+4);
        PrintAscii(223,posx+7,posy+4);
        break;

    case 6://DIBUJA 6
        PrintAscii(223,posx+3,posy+2);
        PrintAscii(223,posx+7,posy+2);
        PrintAscii(223,posx+3,posy+3);
        PrintAscii(223,posx+7,posy+3);
        PrintAscii(223,posx+3,posy+4);
        PrintAscii(223,posx+7,posy+4);
        break;

    }
    //rlutil::setColor(rlutil::WHITE);
}

void borrarPantalla (int posIx, int posIy, int posFx, int posFy){

    for (int i=0 ; i<posFy ; i++){
        rlutil::locate(posIx,posIy+i);
        for (int j=0 ; j<posFx ; j++){
            std::cout<<" ";
        }
    }
}

void opciones (const char* text, int posx, int posy, bool select){//SELECCION DEL MODO DE JUEGO

    if (select){
        rlutil::setBackgroundColor(rlutil::GREY);
        rlutil::setColor(rlutil::BLACK);
    }
    else{
        rlutil::setBackgroundColor(rlutil::CYAN);
        rlutil::setColor(rlutil::WHITE);
        if (posy==15||posy==16){
            rlutil::setColor(rlutil::RED);
        }
    }

    rlutil::locate(posx,posy);
    std::cout<<text;
    rlutil::setBackgroundColor(rlutil::CYAN);
    rlutil::setColor(rlutil::BLACK);
}
