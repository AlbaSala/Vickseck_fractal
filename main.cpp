#include <iostream>
using namespace std;
//CONSTANTS
const int MAXNIV = 6;
const int MIDA_INCORRECTA = -1;
void mostra(int** a, int sz, char c='x')
{
    //Pre: sz >=1
    //Post: mostra els elements de la matriu amb el valor 1, utilitzant el caracter entrat com a paràmetre
    for(int i=0; i<sz; i++)
    {
        for(int j=0; j<sz; j++)
        {
            if(a[i][j] == 1) cout << c;
            else cout << ' ';
        }
        cout << endl;
    }
}

int** omple(int** a, int mida, int c)
{
    //Pre:mida >= 1; Post: tots els elements de la matriu tenen el valor entrat com a paràmetre c
    for(int i=0; i<mida; i++)
    {
        for(int j=0; j<mida; j++)
        {
            a[i][j]=c;
        }
    }
    return a;
}

void pintar_bloc(int **a, int x, int y, int tbloc){
    //Pre: 0<= y,x < mida de la matriu a, tbloc <= mida de la matriu a
    //Post: pinta un bloc de mida tbloc a la matriu a, amb inici en les coordenades indicades
    for(int i=0; i<tbloc; i++){
        for(int j=0; j<tbloc; j++) a[i+x][j+y] = 1;
    }
}

int potencia(int exp, int base = 3)
{
    //Pre:exp>=0, base (per defecte 3) > 0; Post: retorna base ^ exponent
    int resultat;
    if (exp == 0) resultat = 1; //si l'exponent és 0, val 1
    else{ //Els nivells només poden ser positius i enters (validació en el moment d'entrar les dades
        resultat = base * potencia(exp-1,base);
    }
    return resultat;
}

void draw_cross(int **a, int mida, int x, int y, int tbloc){
    pintar_bloc(a, x, y+mida/3, tbloc); //braç superior
    pintar_bloc(a, x+mida/3,y,tbloc); //braç esquerre
    pintar_bloc(a,x+mida/3,y+mida/3,tbloc); //centre
    pintar_bloc(a,x+mida/3,y+2*mida/3,tbloc); //braç dret
    pintar_bloc(a,x+2*mida/3,y+mida/3,tbloc); //braç inferior
}

void vicsek(int **a, int x, int y, int mida, int nivell, int tbloc)
{
    //Pre: matriu a inicialitzada, 0<=x,y<mida, mida és la mida de la matriu (>0), nivell > 0, tbloc és la talla del bloc (>0)
    //Post: genera el fractal de vicsek
    if(nivell == 1) //nivell 1
    {
        //cas_base: dibuixa creu, un bloc a cada braç i al centre.
        //Aquesta part funciona
        draw_cross(a,mida,x,y,tbloc);
    }
    else if (nivell>1)
    {
        //Branca recursiva, nivells superiors
        //Cal millorar, funciona pel nivell 2
        vicsek(a,x+0, y+mida/3, mida/3, nivell-1, tbloc); //superior
        vicsek(a,x+mida/3, y+0, mida/3, nivell-1, tbloc); //esquerre
        vicsek(a,x+mida/3, y+mida/3, mida/3, nivell-1, tbloc); //centre
        vicsek(a,x+mida/3, y+2*mida/3, mida/3, nivell-1, tbloc);//dreta
        vicsek(a,x+2*mida/3, y+mida/3,mida/3, nivell-1, tbloc);//inferior
    }
}

int llegeix_nivell()
{
    //Pre:--; Post: retorna el nivell
    int niv;
    do
    {
        cout << "ENTRA EL NIVELL:" << endl;
        cin >> niv;
    }
    while(niv<1 or niv>MAXNIV); //si és negatiu ho supera el limit el torna a demanar
    return niv;
}

char llegeix_caracter()
{
    //Pre:--; Post: retorna el caracter
    char c;
    cout << "ENTRA EL CARACTER:" << endl;
    cin >> c;
    return c;
}

bool es_potencia(int x, int base = 3)
{
    //Pre: x > 0; Post: cert si és potencia de la base indicada (per defecte 3)
    int r = 1; //cas base
    while(r<x)
    {
        r = r*base;
    }
    return x == r; //si r és més gran que x vol dir que x no és potencia de la base
}

int llegeix_mida(int nivell)
{
    //Pre: nivell>0; Post: retorna la mida si és vàlida, altrament retorna -1, si mida == 0 s'assigna la mida minima
    int m;
    cout << "ENTRA LA MIDA (0 o una potencia de 3):" << endl;
    cin >> m;
    if(m == 0) m=potencia(nivell,3); //mida minima = 3^nivell
    else if (m>0){
            if (not es_potencia(m) or m < potencia(nivell,3)) m= -1; // si no és vàlid
    }
    return m;
}

int main()
{
    int nivell = llegeix_nivell();
    char caracter = llegeix_caracter();
    int mida = llegeix_mida(nivell);
    if(mida == MIDA_INCORRECTA)
    {
        cout << "MIDA INCORRECTA" << endl;
    }
    else
    {
        int **a = new int*[mida];
        for(int i=0; i<mida; i++) a[i] = new int[mida];
        int tbloc = mida/potencia(nivell,3);//constant
        vicsek(omple(a,mida,0),0,0,mida,nivell,tbloc);
        cout << "FRACTAL DE VICSEK:" << endl;
        mostra(a,mida,caracter);
        //Allibera memòria dinàmica
        for(int i=0; i<mida; i++) delete [] a[i];
        delete [] a;
    }
    return 0;
}
