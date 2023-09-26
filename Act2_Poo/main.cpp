// Joan Aneas - Space Wars
#include <iostream>
#include <thread> // Para los "sleeps"
#include <chrono> // Para los "sleeps"
#include <cstdlib> 
#include <ctime>

//#include <locale> // UTF8
//#include <string> // Caracteres especiales

void limpiarPantalla(char juego[16][31]);
//void impPantalla(char juego[15][30], nave &jet, nave &avioneta, nave &boeing);
//void checkDerr(nave &jet, nave &avioneta, nave &boeing);

class nave {
private:
    int vidas;
    //bool estado;
    int derribos;
    int x;
    int y;

public:
    // Constructor
    nave(int totVidas, int contDerribos) {
        vidas = totVidas;
        //estado = derribado;
        derribos = contDerribos;
        x = ((rand() % 13) + 1);
        y = ((rand() % 28) + 1);
    }

    // Métodos de posición
    void setPosicionX() { x = ((rand() % 13) + 1); }
    void setPosicionY() { y = ((rand() % 28) + 1); }
    int posicionX() { return x; }
    int posicionY() { return y; }

    // Otros métodos
    void subir() {
        if (x > 1) x--;
    }
    void bajar() {
        if (x < 14) x++;
    }
    void derecha() {
        if (y < 29) y++;
    }
    void izquierda() {
        if (y > 1) y--;
    }

    // Métodos para gestionar vidas, estado y derribos
    //void setEstado(bool derribado) { estado = derribado; }
    //bool mostrarEstado() { return estado; }

    int getVidas() { return vidas; }
    void setVidas(int nuevasVidas) { vidas = nuevasVidas; }

    int getDerr() { return derribos; }
    void setDerr(int nuevosDerribos) { derribos = nuevosDerribos; }
};

void limpiarPantalla(char juego[16][31]) {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 31; j++) {
            if (i == 0 || i == 15 || j == 0 || j == 30) {
                juego[i][j] = '*'; // Establece los bordes como asteriscos
            }
            else {
                juego[i][j] = ' '; // Establece el resto como espacios en blanco
            }
        }
    }
}

void impPantalla(char juego[16][31], nave& jet, nave& avioneta, nave& boeing) {
    std::string cor = "<3";
    switch (jet.getVidas())
    {
    case 3:
        cor = "<3 <3 <3";
        break;
    case 2:
        cor = " x <3 <3";
        break;
    case 1:
        cor = " x  x <3"; // Dejamos espacios para que no se vea mas corto con menos corazones
        break;
    default:
        break;
    }
    // HUD
    printf("####################################################################");
    printf("\n#######[Space Wars][joan-aneas][v1.1][%s][Nave: Jet]##########\n", cor.c_str()); // Convierte la cadena en una de C para mostrar el <
    printf("####################################################################\n");
    printf("########################### TABLERO ################################\n");
    for (int i = 0; i <= 15; i++) {
        printf("############### ");
        for (int j = 0; j <= 30; j++) {
            bool naveDerr = true; // Variable para controlar la visibilidad de las naves

            if (i == jet.posicionX() && j == jet.posicionY()) {
                printf("x"); // Si es la casilla del jugador, imprime una x en vez de ' '.
            }
            else if (avioneta.getVidas() > 0 && i == avioneta.posicionX() && j == avioneta.posicionY()) {
                printf("a");
            }
            else if (boeing.getVidas() > 0 && i == boeing.posicionX() && j == boeing.posicionY()) {
                printf("b");
            }
            else {
                printf("%c", (naveDerr ? juego[i][j] : ' ')); // Imprime espacio en blanco si la nave no es visible
                // Aun estando "invisible", podremos derribarla, pero las posibilidades son tan bajas que lo he dejado así.
            }
    
        }
        printf(" ####################");
        printf("\n");
    }
    printf("####################################################################\n");
    printf("#######[Estado-Avioneta: %s][Vidas-Avioneta: %d]#################\n", (avioneta.getDerr() > 2) ? "Derrib" : "Activo",avioneta.getVidas());
    printf("#######[Estado-Boeing: %s][Vidas-Boeing: %d]#####################\n", (boeing.getDerr() > 2) ? "Derrib" : "Activo", boeing.getVidas());
    printf("####################################################################\n");
    printf("\nNota: Eres la 'x', 'a' es una avioneta y 'b' es un boeing, ponte en su posicion\n");
    printf("      para derribarlos (33%% posibilidades de que te derriben a ti jiji). \n\n");
}

void checkDerr(nave &jet, nave &avioneta, nave &boeing) {
    int prob = rand() % 3; // 0, 1, 2 = 33% posibilidades

    // Vs Avioneta
    if (jet.posicionX() == avioneta.posicionX() && jet.posicionY() == avioneta.posicionY()) {
        if (prob == 2) {
            system("cls");
            printf("Te han derribado! [ -1 <3 ]");
            std::this_thread::sleep_for(std::chrono::seconds(3));
            jet.setVidas(jet.getVidas() - 1);
            jet.setDerr(jet.getDerr() + 1);
            jet.setPosicionX(); // Spawn de jugador distinto después de ser derribado
            jet.setPosicionY(); // Spawn de jugador distinto después de ser derribado
        }
        else {
            system("cls");
            printf("Has derribado a la avioneta!");
            std::this_thread::sleep_for(std::chrono::seconds(3));
            //if(avioneta.getVidas() < 1) avioneta.setEstado(false);
            avioneta.setDerr(avioneta.getDerr() + 1);
            avioneta.setVidas(avioneta.getVidas() - 1);
            avioneta.setPosicionX(); // Spawn de avioneta distinto después de ser derribada
            avioneta.setPosicionY(); // Spawn de avioneta distinto después de ser derribada
        }    
    }
    // Vs Boeing
    else if (jet.posicionX() == boeing.posicionX() && jet.posicionY() == boeing.posicionY()) {
        if (prob == 2) {
            system("cls");
            printf("Te han derribado! [ -1 <3 ]");
            std::this_thread::sleep_for(std::chrono::seconds(3));
            jet.setVidas(jet.getVidas() - 1);
            jet.setDerr(jet.getDerr() + 1);
            jet.setPosicionX(); // Spawn de jugador distinto después de ser derribado
            jet.setPosicionY(); // Spawn de jugador distinto después de ser derribado
        }
        else {
            system("cls");
            printf("Has derribado al Boeing!");
            std::this_thread::sleep_for(std::chrono::seconds(3));
            //if (boeing.getVidas() < 1) boeing.setEstado(false);
            boeing.setDerr(boeing.getDerr() + 1);
            boeing.setVidas(boeing.getVidas() - 1);
            boeing.setPosicionX(); // Spawn de boeing distinto después de ser derribado
            boeing.setPosicionY(); // Spawn de boeing distinto después de ser derribado
        }
    }

    else if (avioneta.posicionX() == boeing.posicionX() && avioneta.posicionY() == boeing.posicionY()) {
        // Si da la casualidad de que coinciden en X e Y, se derriban
        if (prob == 2) {
            system("cls");
            printf("La avioneta ha derribado al boeing!");
            std::this_thread::sleep_for(std::chrono::seconds(3));
            boeing.setVidas(boeing.getVidas() - 1);
            boeing.setDerr(boeing.getDerr() + 1);
            boeing.setPosicionX(); // Spawn de jugador distinto después de ser derribado
            boeing.setPosicionY(); // Spawn de jugador distinto después de ser derribado
        }
        else {
            system("cls");
            printf("El boeing ha derribado a la avioneta!");
            std::this_thread::sleep_for(std::chrono::seconds(3));
            //avioneta.setEstado(false);
            avioneta.setVidas(avioneta.getVidas() - 1);
            avioneta.setDerr(avioneta.getDerr() + 1);
            avioneta.setPosicionX(); // Spawn de boeing distinto después de ser derribado
            avioneta.setPosicionY(); // Spawn de boeing distinto después de ser derribado
        }
    }
}

int main() {
    //std::locale::global(std::locale("es_ES.UTF-8")); 

    srand(time(0));
    char juego[16][31];
    //char opc;
    std::string opc; // Con char se produce una excepción

    nave jet(3, 0), avioneta(3, 0), boeing(3, 0);

    limpiarPantalla(juego);

    while (jet.getVidas() > 0) {
        impPantalla(juego, jet, avioneta, boeing);

        printf("Muevete con WASD: ");
        std::cin >> opc;
        switch (opc[0]) { // Indico la posición 0 porque es un string
        case 'w':
        case 'W':
            jet.subir();
            break;
        case 'a':
        case 'A':
            jet.izquierda();
            break;
        case 's':
        case 'S':
            jet.bajar();
            break;
        case 'd':
        case 'D':
            jet.derecha();
            break;
        default:
            system("cls");
            printf("[ERROR] 0003: Opcion incorrecta!");
            std::this_thread::sleep_for(std::chrono::seconds(4));
            break;
        }
        checkDerr(jet, avioneta, boeing);
        system("cls");
    }
    printf("Fin del juego.\n");
    printf("\nStats Totales:\n\nVidas Jet (jugador): %d\nDerribos Jet (jugador): %d\n", jet.getVidas(), jet.getDerr());
    printf("\nVidas Avioneta (bot): %d\nDerribos Avioneta (bot): %d\n", avioneta.getVidas(), avioneta.getDerr());
    printf("\nVidas Boeing (bot): %d\nDerribos Boeing (bot): %d\n", boeing.getVidas(), boeing.getDerr());
    return 0;
}