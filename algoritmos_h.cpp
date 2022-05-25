#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <time.h>
#include <ctime>
#include "Horse_G5.h"
#include "NQueen_G5.h"
#include "Maze_G5.h"

using namespace std;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;



void Graficar(vector<int> datos, vector<double> data, string alg) {
    int x,mayor , menor, columna, columna2, columna3, columna4;
    x = 5; //cantidad de datos
    int z[5] = { datos[0], datos[1], datos[2], datos[3],datos[4]};
    //int z[3] = { 13, 15, 18 };

    mayor = datos[0];
    menor = datos[0];
    for (int i = 0; i < x; i++) {
        if (mayor < z[i]) {
            mayor = z[i];
        }

        if (menor > z[i]) {
            menor = z[i];
        }

    }

    
    columna = mayor;
    columna2 = mayor;
    columna3 = mayor;
    columna4 = mayor;

    for (; columna2>0; columna2--) {
        cout << columna2 << "\t|";
        

        for (int j = 0; j < x; j++) {
            if (z[j] >= columna3) {
                cout << "\t" << "||||" << "\t";
            }
            else {
                cout << "\t\t";
            }
        }
        columna3--;
        cout << "\n";
    }
    cout << "------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "\t";
    for(int i=1; i<=datos.size(); i++)
        cout << "\t" << alg<<i;
    cout << endl;
    cout << "------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Datos precisos:\n";
    for (int i = 1; i <= datos.size(); i++)
        cout << alg << i << ":\t" << data[i-1]<<"\n";
}




int main()
{

    //caballo
    int N, pos_x = 0, pos_y = 0;

    double t = 0;
    vector<int> tiempo_horse_int={1,1,1,1};
    vector<int> tiempo_NQueen_int = { 1,1,1,1 };
    vector<int> tiempo_laberinto_int = { 1,1,1,1 };;

    vector<double> tiempo_horse_dec = { 1,1,1,1 };
    vector<double> tiempo_NQueen_dec = { 1,1,1,1 };
    vector<double> tiempo_laberinto_dec = { 1,1,1,1 };

    
    //caballo
    cout << "Horse\n";
    double t_horse = 0;
    for (int i = 0; i < 3; i++) {
        cout << "Test "<<i+1<<":\n";
        cout << "N: ";        cin >> N;
        cout << "x: ";        cin >> pos_x;
        cout << "y: ";        cin >> pos_y;

        t = Horse_G5(N, pos_x, pos_y);
        t_horse += t;
        cout << t << " ms" << endl;
        //tiempo_horse_dec.push_back(t_horse / 3);
        //tiempo_horse_int.push_back((int)round(t_horse / 3));

    }
    cout << t_horse << endl;

    tiempo_horse_dec.push_back(t_horse / 3);
    tiempo_horse_int.push_back((int)round(t_horse/3));
    Graficar(tiempo_horse_int, tiempo_horse_dec,"HorseG");
    
    cout << "----------------------------------------------------\n";
    cout << "N_Queen\n";
    double t_queen = 0;
    //reina
    for (int i = 0; i < 3; i++) {
        cout << "Test " << i + 1 << ":\n";
        cout << "N: ";        cin >> N;
        cout << "x: ";        cin >> pos_x;
        cout << "y: ";        cin >> pos_y;
        
        t = nqueens_G5(N, pos_x, pos_y);
        t_queen += t;
        cout << t << "ms" << endl;
        //tiempo_NQueen_dec.push_back((t_queen / 3));
       // tiempo_NQueen_int.push_back((int)round(t_queen / 3));
    }


    tiempo_NQueen_dec.push_back((t_queen / 3));
    tiempo_NQueen_int.push_back((int)round(t_queen/3));

    Graficar(tiempo_NQueen_int, tiempo_NQueen_dec,"NQueenG");
    
    
  //laberintos
   /* string laberintos[5] = {"G1.txt", "G2.txt","G3.txt","G4.txt","G5.txt"};

    for (int i = 0; i < 5; i++) {

        t=maze_5(laberintos[i]);
        tiempo_laberinto_dec.push_back(t);
        tiempo_laberinto_int.push_back((int)round(t));
    }*/
    t=maze_5("tiny4.txt");
    tiempo_laberinto_dec.push_back(t);
    tiempo_laberinto_int.push_back((int)round(t));
    Graficar(tiempo_laberinto_int, tiempo_laberinto_dec, "MazeG");

}



