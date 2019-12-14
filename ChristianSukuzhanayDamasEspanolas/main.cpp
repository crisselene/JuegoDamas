#include<iostream>//Lib. que maneja entrada y salida cout/cin
#include<exception> //Lib. que me permite abortar el juego
using namespace std;
#define ESPACIO_VACIO 1
#define FICHAS_BLANCAS 2
#define DAMAS_BLANCAS 4
#define FICHAS_NEGRAS 3
#define DAMAS_NEGRAS 5
#define FILAS 8
#define COLUMNAS 8
//contador de fichas, si alguien se queda sin fichas pierde
int contFichasBlancas=12;
int contFichasNegras=12;
int intro();// Funcion que pinta y colorea a la Universidad Europea
void intercambio(int matrix[FILAS][COLUMNAS], int filaOrigen, int colOrigen, int filaDestino, int colDestino);//Intercambia fichas
int turno(int matrix[][COLUMNAS], int jugador,int filaOrigen,int colOrigen,int filaDestino,int colDestino);//Gestiona los turno y movimientos
char simbolos(int i);//Me ayuda a rellenar mi matrix, convierte los numeros en simbolos
void tablero(int matrix[FILAS][COLUMNAS],int contFichasBlancas,int contFichasNegras);//Dibuja el tablero
int comerOtraVez(int matrix[8][8], int i, int i1, int i2, int i3, int i4, int i5, int i6, int i7);
int comprobarDiagonal(int matrix[][COLUMNAS], int jug, int filaOrigen, int colOrigen);
void convertirEnDama(int matrix[FILAS][COLUMNAS],int filaOrigen,int colOrigen,int filaDestino,int colDestino,int jugador);
int movimientoDama(int matrix[FILAS][COLUMNAS], int filaOrigen, int colOrigen, int filaDestino, int colDestino, int jugador);



int intro(){
    int op=0;
    do{
        do{
            system("CLS");
            cout<<"\t\t_____________________________________________________________________"<<endl;
            cout<<"\t\t                                                                    "<<endl;
            cout<<"\t\t UNIVERSIDAD EUROPEA - ESCUELA DE ARQUITECTURA, INGENIERIA Y DISEÑO"<<endl;
            cout<<"\t\t_____________________________________________________________________"<<endl<<endl;
            cout<<"\t\tProf.:Christian Sucuzhanay.                  Alumno : Cristina Diez"<<endl<<endl<<endl;
            cout<<"\t\t              << JUEGO DE LAS DAMAS ESPANOLAS >>"<<endl<<endl;
            cout<<"\t\t\t    ** Seleccione una opcion del menu: **"<<endl<<endl;
            cout<<"\t\t\t\t  [ 1 ] Ver reglas del juego "<<endl;
            cout<<"\t\t\t\t  [ 2 ] Jugar"<<endl;
            cout<<"\t\t\t\t  [ 0 ] SALIR"<<endl<<endl;
            cout<<"\t\t\t              Ingrese su opcion ? : ";
            cin>>op;
        } while (op<0||op>2);
        switch (op){
            case 1:
                system("CLS");
                cout<<"\t\t_____________________________________________________________________"<<endl;
                cout<<"\t\t                                                                    "<<endl;
                cout<<"\t\t UNIVERSIDAD EUROPEA - ESCUELA DE ARQUITECTURA, INGENIERIA Y DISEÑO"<<endl;
                cout<<"\t\t_____________________________________________________________________"<<endl<<endl;
                cout<<"\t\tProf.Christian Sukuzhanay                 Alumno:Cristina Diez "<<endl<<endl<<endl;
                cout<<"\t\t            << REGLAS DEL JUEGO DE LAS DAMAS ESPANOLAS >>\n";
                cout<<"\t\t           ----------------------------------------------\n\n";
                cout<<"\t\t1.- Inician el juego las fichas blancas por defecto"<<endl<<endl;
                cout<<"\t\t2.- Las fichas SOLO se mueven 1 casilla hacia ADELANTE y en DIAGONAL\n ";
                cout<<"\t\t    excepto al comer FICHA que pueden saltar\n\n";
                cout<<"\t\t3.- Las fichas SALTAN mas de una casilla  SOLO cuando haya una ficha\n ";
                cout<<"\t\t    contaria y la siguiente este vacia\n\n ";
                cout<<"\t\t4.- Gana quien coma mas fichas \n\n";
                cout<<"\t\t5.- Si pasan mas de 2 horas sin que nadie gane se declara EMPATE\n\n\n\n ";
                cout<<"\t\t\t\t PULSE [ 0 ] para SALIR: ";
                cin>>op;
                intro();
            case 2:
                break;
            case 0:
                system("CLS");
                abort();
        }
        return 0;
    }while(op!=0);
    abort();

}

int turno(int matrix[FILAS][COLUMNAS], int jugador,int filaOrigen,int colOrigen,int filaDestino,int colDestino)//Gestiona movimientos y turnos
{
    int comerFichaBlancas;
    int comerFichaNegras;


    if ((filaOrigen < 0 && FILAS <= filaOrigen) &&
        (colOrigen < 0 && COLUMNAS <= colOrigen)) { // Comprueba filas y col esten dentro del tablero
        cout << "\n No ves que el tablero no tiene esa posicion ? Estas fuera del tablero\n";
        return -1;
    }
    if ((filaDestino < 0 && FILAS <= filaDestino) &&
        (colDestino < 0 && COLUMNAS <= colDestino)) {// Comprueba filas y col esten dentro del tablero
        cout << "\n No ves que el tablero no tiene esa posicion ? Estas fuera del tablero\n";
        return -1;
    }

    if (jugador == FICHAS_BLANCAS ) {//Comprueba que muevas solo donde haya fichas blancas
        if (matrix[filaOrigen][colOrigen] != FICHAS_BLANCAS && matrix[filaOrigen][colOrigen] != DAMAS_BLANCAS) {
            cout << "\n <<< Eres CIEGO ? , No tienes fichas ** BLANCAS **  en esa posicion >>>\n";
            return -1;
        }
    } else if(jugador == FICHAS_NEGRAS ) { //Comprueba que no muevas fichas negras
        if (matrix[filaOrigen][colOrigen] != FICHAS_NEGRAS && matrix[filaOrigen][colOrigen] != DAMAS_NEGRAS) {
            cout << "\n <<< Eres CIEGO ? , No tienes fichas ** NEGRAS **  en esa posicion >>>\n";
            return -1;
        }
    }

    if (matrix[filaDestino][colDestino] != ESPACIO_VACIO) {//Comprueba que muevas solo espacios vacios.
        cout << "\nSolo puedes mover a un espacios VACIOS!! como tu cerebro, jeje";
        return -1;
    }
if(matrix[filaOrigen][colOrigen] != DAMAS_NEGRAS && matrix[filaOrigen][colOrigen] != DAMAS_BLANCAS  ) {
    if (jugador == FICHAS_BLANCAS) {//Comprueba que el movimiento de las BLANCAS no sea hacia atras
        if (filaOrigen >= filaDestino) {
            cout << "\nNo te da o que ??? No puedes mover hacia atras o quedarte en el mismo lugar\n";
            return -1;
        }
    } else if (jugador == FICHAS_NEGRAS) {//Comprueba que el movimiento de las NEGRAS no sea hacia atras
        if (filaOrigen <= filaDestino) {
            cout << "\nNo te da o que ??? No puedes mover hacia atras o quedarte en el mismo lugar\n";
            return -1;
        }
    }
    if (jugador == FICHAS_NEGRAS || jugador == FICHAS_BLANCAS) {
        //Comprueba si es un movimiento normal, una sola posicion
        if (filaOrigen - filaDestino == -1 || filaOrigen - filaDestino == 1) {
            //si llega al final se transforma en dama
            if (colOrigen - colDestino == 1 || colOrigen - colDestino == -1) {
                intercambio(matrix, filaOrigen, colOrigen, filaDestino, colDestino);
                convertirEnDama(matrix, filaOrigen, colOrigen, filaDestino, colDestino, jugador);
                return 0;
            }
        }
    }

    //Comprueba si ha comido ficha de adversario
    if (filaOrigen - filaDestino == -2 || filaOrigen - filaDestino == 2) {
        if (colOrigen - colDestino == -2 || colOrigen - colDestino == 2) {
            // Comprueba si en la posicion del salto hay ficha contraria
            if (filaOrigen < filaDestino) { // Movimiento hacia abajo
                comerFichaBlancas = filaOrigen + 1;
                contFichasNegras--;
            } else { // Movimiento hacia arriba
                comerFichaBlancas = filaOrigen - 1;
                contFichasBlancas--;
            }
            if (colOrigen < colDestino) { // Movimiento hacia abajo
                comerFichaNegras = colOrigen + 1;
            } else { // Movimiento hacia arriba
                comerFichaNegras = colOrigen - 1;

            }
            if (jugador == FICHAS_BLANCAS && matrix[comerFichaBlancas][comerFichaNegras] != FICHAS_NEGRAS
            && matrix[comerFichaBlancas][comerFichaNegras] != DAMAS_NEGRAS) {
                cout << "\nSolo puedes saltar si COMES FICHA \n" ;
                return -1;
            }
            if (jugador == FICHAS_NEGRAS && matrix[comerFichaBlancas][comerFichaNegras] != FICHAS_BLANCAS
            && matrix[comerFichaBlancas][comerFichaNegras] != DAMAS_BLANCAS) {
                cout << "\nSolo puedes saltar si COMES FICHA \n";
                return -1;
            }
            matrix[comerFichaBlancas][comerFichaNegras] = 1;
            intercambio(matrix, filaOrigen, colOrigen, filaDestino, colDestino);
            convertirEnDama(matrix, filaOrigen, colOrigen, filaDestino, colDestino, jugador);
            tablero(matrix, contFichasBlancas, contFichasNegras);
            if (comerOtraVez(matrix, jugador, filaOrigen, colOrigen, filaDestino, colDestino,
                             comerFichaBlancas,
                             comerFichaNegras, jugador) == 0) {
                return 0;
            } else {
                cout << "\nINTENTA de nuevo :\n";
            }
        }
    }
}else{
    //MOVIMIENTO DE LAS DAMAS
     movimientoDama(matrix,filaOrigen,colOrigen,filaDestino,colDestino,jugador);
}
}

int comerOtraVez(int matrix[FILAS][COLUMNAS], int jug, int filaOrigen, int colOrigen,int destinof, int destinoc,int comerFichaBlancas,
        int comerFichaNegras,int jugador) {
    int filaDestino;
    char colDestino;
    //preguntar al jugador si puede comer de nuevo
    string resp;
    cout << " Puedes comer otra vez? (S si, N no/cancelar)";
    cin >> resp;
    if (resp == "S" || resp == "s") {
        //comprobar que el jugador no miente
        if(comprobarDiagonal(matrix,jug,destinof,destinoc)==0){
            cout<<"NO MIENTASS!! No se puede comer mas con esa ficha";
            return 0;
        }else {
            int comerDos = 1; //variable que indica que es un segundo turno para comer otra vez
            //preguntar donde quiere mover
            filaOrigen = destinof;
            colOrigen = destinoc;
            cout << "Introduzca FILA 1-8 y COLUMNA a-h del destino de la ficha F" << filaOrigen << " C" << colOrigen
                 << " ,  por ejemplo 5h \n";
            cin >> filaDestino >> colDestino;//Capturo coordenada de destino Negras
            colDestino = tolower(colDestino);
            filaDestino = filaDestino - 1;
            colDestino = colDestino - 'a';
            //comprueba que el destino sea correcto
            if ((filaDestino < 0 && FILAS <= filaDestino) &&
                (colDestino < 0 && COLUMNAS <= colDestino)) {// Comprueba filas y col esten dentro del tablero
                cout << "\n No ves que el tablero no tiene esa posicion ? Estas fuera del tablero\n";
                return -1;
            }
            //Comprueba si ha comido ficha de adversario
            if (filaOrigen - filaDestino == -2 || filaOrigen - filaDestino == 2) {
                if (colOrigen - colDestino == -2 || colOrigen - colDestino == 2) {
                    // Comprueba si en la posicion del salto hay ficha contraria
                    if (filaOrigen < filaDestino) { // Movimiento hacia abajo
                        comerFichaBlancas = filaOrigen + 1;
                    } else { // Movimiento hacia arriba
                        comerFichaBlancas = filaOrigen - 1;
                        contFichasBlancas--;
                    }
                    if (colOrigen < colDestino) { // Movimiento hacia abajo
                        comerFichaNegras = colOrigen + 1;
                        contFichasNegras--;
                    } else { // Movimiento hacia arriba
                        comerFichaNegras = colOrigen - 1;
                    }
                    if (jugador == FICHAS_BLANCAS && matrix[comerFichaBlancas][comerFichaNegras] != FICHAS_NEGRAS) {
                        cout << "\nSolo puedes saltar si COMES FICHA" << comerFichaBlancas << comerFichaNegras;
                        return -1;
                    }
                    if (jugador == FICHAS_NEGRAS && matrix[comerFichaBlancas][comerFichaNegras] != FICHAS_BLANCAS) {
                        cout << "\nSolo puedes saltar si COMES FICHA \n";
                        return -1;
                    }
                    matrix[comerFichaBlancas][comerFichaNegras] = 1;
                    intercambio(matrix, filaOrigen, colOrigen, filaDestino, colDestino);
                    convertirEnDama(matrix, filaOrigen, colOrigen, filaDestino, colDestino,jugador);
                    tablero(matrix,contFichasBlancas,contFichasNegras);
                    if (comerOtraVez( matrix, jugador, filaOrigen, colOrigen, filaDestino, colDestino,
                            comerFichaBlancas,comerFichaNegras, jugador)==0){
                        return 0;
                    }
                }
            }
        }
            } else {
                //metodo que comprueba que hay en las diagonales
                int podiaComer = comprobarDiagonal(matrix, jug, destinof, destinoc);
                //si sí se podía comer se le quita la ficha
                if (podiaComer == 1) {
                    cout << "Podias comer otra vez, tu ficha sera eliminada\n";
                    if(matrix[destinof][destinoc] == FICHAS_BLANCAS){
                        contFichasBlancas--;
                    }else if(matrix[destinof][destinoc] == FICHAS_NEGRAS){
                        contFichasNegras--;
                    }
                    matrix[destinof][destinoc] = ESPACIO_VACIO;
                    tablero(matrix,contFichasBlancas,contFichasNegras);
                }
                return 0;

    }
}

int comprobarDiagonal(int matrix[FILAS][COLUMNAS], int jug, int filaOrigen, int colOrigen) {
    int fila1;//guardar fila del valor1 a comprobar si esta vacio
    int col1;//guardar columna del valor1 a comprobar si esta vacio
    int fila2;//guardar fila del valor2 a comprobar si esta vacio
    int col2;//guardar columna del valor2 a comprobar si esta vacio
    int puedeComer; //controlador de si es posible comer (1 si, 0 no)
    if (jug == FICHAS_NEGRAS) {
        fila1 = filaOrigen - 1;
        col1 = colOrigen + 1;
        fila2 = filaOrigen - 1;
        col2 = colOrigen - 1;
        if (matrix[fila1][col1] == FICHAS_BLANCAS) {
            fila1 = fila1 - 1;
            col1 = col1 + 1;
            if (matrix[fila1][col1] == ESPACIO_VACIO ) {
                puedeComer =1;
            }
        }if (matrix[fila2][col2] == FICHAS_BLANCAS) {
            fila2 = fila2 - 1;
            col2 = col2 - 1;
            if (matrix[fila2][col2] == ESPACIO_VACIO ) {
                puedeComer =1;
            }
        }
        if(puedeComer == 1)return 1;
        else return 0;
        //en el caso del turno de las blancas
    } else if (jug == FICHAS_BLANCAS) {
        fila1 = filaOrigen + 1;
        col1 = colOrigen + 1;
        fila2 = filaOrigen + 1;
        col2 = colOrigen - 1;
        //comprobar que hay una ficha negra en las diagonales para comersela
        if (matrix[fila1][col1] == FICHAS_NEGRAS) {
            fila1 = fila1 + 1;
            col1 = col1 + 1;
            //comprobar que hay un espacio vacio detras, si no no se puede comer
            if (matrix[fila1][col1] == ESPACIO_VACIO ) {
                //Retorno un uno si sí se podía saltar de nuevo
                puedeComer = 1;
            }
        }if (matrix[fila2][col2] == FICHAS_NEGRAS){
            fila2 = fila2 + 1;
            col2 = col2 - 1;
            if (matrix[fila2][col2] == ESPACIO_VACIO ) {
                //Retorno un uno si sí se podía saltar de nuevo
                puedeComer = 1;
            }
        }
        if(puedeComer == 1)return 1;
        else return 0;
    }
}

void convertirEnDama(int matrix[FILAS][COLUMNAS],int filaOrigen,int colOrigen,int filaDestino,int colDestino,int jugador){
    //si llega a la ultima fila transformar en dama
    if(filaDestino == 0 && jugador==FICHAS_NEGRAS){
        matrix[filaDestino][colDestino]=DAMAS_NEGRAS;
        cout<<"Tu ficha se convierte en una dama negra\n";
    }else if(filaDestino == 7 && jugador==FICHAS_BLANCAS){
        matrix[filaDestino][colDestino]=DAMAS_BLANCAS;
        cout<<"Tu ficha se convierte en una dama blanca\n";
    }
}

int movimientoDama(int matrix[FILAS][COLUMNAS], int filaOrigen, int colOrigen, int filaDestino, int colDestino, int jugador){
    //primero determino si el movimiento es diagonal inferior derecha,  diagonal inferior izquierda,
    // diagonal superior derecha o diagonal superior izquierda
    int fila =filaOrigen;
    int column = colOrigen;
    int jugadorEnem;
    int contadorEnem;
    if(jugador == FICHAS_NEGRAS)  jugadorEnem = FICHAS_BLANCAS, contadorEnem= contFichasBlancas;
    else jugadorEnem = FICHAS_NEGRAS,contadorEnem= contFichasNegras;
    //movimiento diagonal superior derecha
    if(filaOrigen>filaDestino && colOrigen<colDestino) {
        do {
            fila--, column++;
            //ver si hay una ficha o dama del enemigo en la casilla y si la hay comersela
            if (matrix[fila][column] == jugadorEnem || matrix[fila][column] == jugadorEnem + 2) {
                //comprobar que no hay dos fichas seguidas en la diagonal
                if(matrix[fila-1][column+1] != ESPACIO_VACIO){
                    cout<<"No puedes saltar dos fichas a la vez\n";
                    return -1;
                }else matrix[fila][column] = ESPACIO_VACIO, contadorEnem--;
            } else if (matrix[fila][column] == jugador || matrix[fila][column] == jugador + 2) {
                cout << "No puedes saltar tus propias piezas\n";
                return -1;
            }
        } while (fila!= filaDestino && column!=colDestino);
        //movimiento diagonal superior izquierda
    }else if(filaOrigen>filaDestino && colOrigen>colDestino){
        do {
            fila--, column--;
            //ver si hay una ficha o dama del enemigo en la casilla y si la hay comersela
            if (matrix[fila][column] == jugadorEnem || matrix[fila][column] == jugadorEnem+2) {
                //comprobar que no hay dos fichas seguidas en la diagonal
                if(matrix[fila-1][column-1] != ESPACIO_VACIO){
                    cout<<"No puedes saltar dos fichas a la vez\n";
                    return -1;
                }else matrix[fila][column] = ESPACIO_VACIO,contadorEnem--;
            }else  if (matrix[fila][column] == jugador || matrix[fila][column] == jugador+2) {
                cout<<"No puedes saltar tus propias piezas\n";
                return -1;
            }
        }while (fila!= filaDestino && column!=colDestino);
        //movimiento diagonal inferior izquierda
    }else if(filaOrigen<filaDestino && colOrigen>colDestino){
        do {
            fila++, column--;
            //ver si hay una ficha o dama del enemigo en la casilla y si la hay comersela
            if (matrix[fila][column] == jugadorEnem || matrix[fila][column] == jugadorEnem+2) {
                //comprobar que no hay dos fichas seguidas en la diagonal
                if(matrix[fila+1][column-1] != ESPACIO_VACIO){
                    cout<<"No puedes saltar dos fichas a la vez\n";
                    return -1;
                }else matrix[fila][column] = ESPACIO_VACIO,contadorEnem--;
            }else  if (matrix[fila][column] == jugador || matrix[fila][column] == jugador+2) {
                cout<<"No puedes saltar tus propias piezas\n";
                return -1;
            }
        }while (fila!= filaDestino && column!=colDestino);
        //movimiento diagonal inferior izquierda
    }else if(filaOrigen<filaDestino && colOrigen<colDestino){
        do {
            fila++, column++;
            //ver si hay una ficha o dama del enemigo en la casilla y si la hay comersela
            if (matrix[fila][column] == jugadorEnem || matrix[fila][column] == jugadorEnem+2) {
                //comprobar que no hay dos fichas seguidas en la diagonal
                if(matrix[fila+1][column+1] != ESPACIO_VACIO){
                    cout<<"No puedes saltar dos fichas a la vez\n";
                    return -1;
                }else matrix[fila][column] = ESPACIO_VACIO, contadorEnem--;
            }else  if (matrix[fila][column] == jugador || matrix[fila][column] == jugador+2) {
                cout<<"No puedes saltar tus propias piezas\n";
                return -1;
            }
        }while (fila!= filaDestino && column!=colDestino);
    }
    intercambio(matrix, filaOrigen, colOrigen, filaDestino, colDestino);
    if(jugador == FICHAS_NEGRAS) contFichasBlancas= contadorEnem;
    else contFichasNegras =contadorEnem;
    tablero(matrix, contFichasBlancas, contFichasNegras);
    return 0;
}

void tablero(int matrix[FILAS][COLUMNAS],int contFichasBlancas,int contFichasNegras)//Pinta tablero
{
    int pintarFilas, pintarCol;
    system("CLS");
    cout<<"\t\t_____________________________________________________________________"<<endl;
    cout<<"\t\t                                                                    "<<endl;
    cout<<"\t\t UNIVERSIDAD EUROPEA - ESCUELA DE ARQUITECTURA, INGENIERIA Y DISEÑO"<<endl;
    cout<<"\t\t_____________________________________________________________________"<<endl<<endl;
    cout<<"\t\tProf.: Christian Sucuzhanay                  Alumno: Cristina Diez"<<endl<<endl<<endl;
    cout<<"\t\t                << TABLERO DE LAS DAMAS ESPANOLAS >>"<<endl<<endl;
    cout<<"\n\t\t\t\t     b = fichas BLANCAS --> " <<contFichasBlancas;
    cout<<"\n\t\t\t\t     n = fichas NEGRAS --> " <<contFichasNegras;
    cout<<"\n\t\t\t\t     v = espacios VACIOS jugables";
    cout<<"\n\n\t\t\t\t   +---+---+---+---+---+---+---+---+\n";
    if(contFichasBlancas== 0){
        cout<<"ya no quedan fichas blancas, JUGADOR FICHAS NEGRAS HAS GANADO!!\n **********  :D  *********";
        exit(-1);
    }else if(contFichasNegras== 0){
        cout<<"ya no quedan fichas negras, JUGADOR FICHAS BLANCAS HAS GANADO!!\n **********  :D  *********";
        exit(-1);
    }
    for (pintarFilas=0; pintarFilas<FILAS; ++pintarFilas)
    {
        cout<<"\t\t\t\t"<<  pintarFilas+1  <<"  | "; // Pinto filas
        for (pintarCol=0; pintarCol<COLUMNAS; ++pintarCol)
        {
            cout<<simbolos(matrix[pintarFilas][pintarCol])<< " | " ;//Rellenamos tablero
        }
        cout<<"\n";
        cout<<"\t\t\t\t   +---+---+---+---+---+---+---+---+\n";
    }
    cout<<"\n\t\t\t\t     a   b   c   d   e   f   g   h\n\n\n";//Imprime leyenda para de colunmnas
}


void intercambio(int matrix[FILAS][COLUMNAS], int filaOrigen, int colOrigen, int filaDestino, int colDestino)//Cambia fichas en la matrix
{
    int temp;// Para almacenar mientras intercambio las coordenadas
    temp = matrix[filaOrigen][colOrigen];
    matrix[filaOrigen][colOrigen] = matrix[filaDestino][colDestino];
    matrix[filaDestino][colDestino] = temp;
}


char simbolos(int i)//Cambia letras por numeros
{
    switch(i)
    {
        case 0:
            return ' ';//no jugable
        case 1:
            return 'v';//espacio vacio
        case 2:
            return 'b';//blancas
        case 3:
            return 'n';//negras
        case 4:
            return 'B';
        case 5:
            return 'N';

    }
    return ('?');
}


int main()//Programa principal
{
    int filaOrigen, filaDestino;//Para almacernar las filas 1-8
    char colOrigen, colDestino;//Para almacenar el valor de las columnas que son a-h
    int matrix[FILAS][COLUMNAS]={//Matrix de fichas
            {0,2,0,2,0,2,0,2},
            {2,0,2,0,2,0,2,0},
            {0,2,0,2,0,2,0,2},
            {1,0,1,0,1,0,1,0},
            {0,1,0,1,0,1,0,1},
            {3,0,3,0,3,0,3,0},
            {0,3,0,3,0,3,0,3},
            {3,0,3,0,3,0,3,0}};//Tablero 0= vacio, 2=Blancas, 3=Negras
    intro();//Funcion que pinta y colorea Universidad Europea
    system("CLS");//Limpia pantalla
    for(;;)
    {//Bucle infinito para captura y validacion de coordenada de ficha
        tablero(matrix,contFichasBlancas,contFichasNegras);//Dibujo el tablero, TURNO BLANCAS, le paso la matrix d para dibujar el tablero
        while(1){//Mientras no sean validas las coordenadas no sale de este while
            cout<<"\nTURNO de las  * BLANCAS *  Ingrese FILA 1-8 y COLUMNA a-h de la ficha que desea mover, por ejemplo 3b\n";
            cin>>filaOrigen>>colOrigen;//Capturo coordenada de origen Blancas
            colOrigen = tolower(colOrigen);//Permite que el usuario meta las columnas en MAYUSCULAS o minusculas
            cout<<"Introduzca FILA 1-8 y COLUMNA a-h del destino de la ficha a mover,  por ejemplo 4a \n";
            cin>>filaDestino>>colDestino;//Capturo coordenada de destino Blancas
            colDestino = tolower(colDestino);
            if(turno(matrix, FICHAS_BLANCAS, filaOrigen-1,colOrigen - 'a',filaDestino-1,colDestino - 'a') == 0)//Compruebo que sean validos las coordenadas
                break;
            cout<<"\nINTENTA de nuevo :\n";
        }
        system("CLS");
        tablero(matrix,contFichasBlancas,contFichasNegras);//Dibujo el tablero, TURNO NEGRAS, le paso la matrix d para dibujar el tablero
        while(1){//Mientras no sean validas las coordenadas no sale de este while
            cout<<"\nTURNO de las  * NEGRAS *  Ingrese FILA 1-8 y COLUMNA a-h de la ficha que desea mover, por ejemplo 6g\n";
            cin>>filaOrigen>>colOrigen;//Capturo coordenada de origen Negras
            colOrigen = tolower(colOrigen);
            cout<<"Introduzca FILA 1-8 y COLUMNA a-h del destino de la ficha a mover,  por ejemplo 5h \n";
            cin>>filaDestino>>colDestino;//Capturo coordenada de destino Negras
            colDestino = tolower(colDestino);//Permite que el usuario meta las columnas en MAYUSCULAS o minusculas
            if(turno(matrix, FICHAS_NEGRAS, filaOrigen-1,colOrigen - 'a',filaDestino-1,colDestino - 'a') == 0)//Comprueba que sean validos las coordenadas
                break;
            cout<<"\nINTENTA de nuevo :\n";
        }
    }
}