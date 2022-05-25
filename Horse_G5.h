#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <time.h>
#include <ctime>
using namespace std;
using std::chrono::milliseconds;
using std::chrono::steady_clock;


class Salto_Caballo {
private:
    int N = 8; //tamaño del tablero
    int salto = 1;
    int salto_mov[8][2] = { {-2,1},{-1,2},{1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1} }; //movimientos posibles
    vector<vector<int>> tablero;
    double time;

public:
    Salto_Caballo(int N_n, int x, int y) {
        auto start = steady_clock::now();
        if (N_n <= 3) {
            cout << "No tiene solucion" << endl;
            auto end = steady_clock::now();
            std::chrono::duration<double, std::milli> float_ms = end - start;
            time = float_ms.count();
            return;
        }

        //definimos el tamaño del tablero
        N = N_n;

        //llenado del tablero con ceros
        tablero.assign(N, vector<int>(N, 0));
        //si las coordenadas iniciales no estan en el tablero
        if (x < 0 || x >= N || y < 0 || y >= N) {
            cout << "Coordenadas ingresadas fuera de rango" << endl;
            exit(1);
        }
        //en caso de que todo sea correcto comienza el movimiento
        else {
            Mover_Caballo(x, y);
        }
        Print_Tablero();

        auto end = steady_clock::now();
        std::chrono::duration<double, std::milli> float_ms = end - start;
        time = float_ms.count();
    }
    //------------------------------------------------------------------------------------------------------------
       //backtracking
    void Mover_Caballo(int x, int y) {
        if (x < 0 || x >= N || y < 0 || y >= N || tablero[x][y] != 0) {
            //en caso el movimiento se salga del tablero o esa pos del tablero ya fue accedida, regresa
            return;
        }
        tablero[x][y] = salto;
        salto++;
        //utiliza los 8 movimientos predefinidos en la clase y trata de hacerlos 
        for (int i = 0; i < 8; i++)
            Mover_Caballo(x + salto_mov[i][0], y + salto_mov[i][1]);


    }


    //------------------------------------------------------------------------------------------------------------
    void Print_Tablero() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << tablero[i][j] << "\t";
            }
            cout << "\n";
        }
    }


    //-------------------------------------------------------------------------------------
    double tiempo() {
        return time;
    }
};

double Horse_G5(int N, int x, int y) {
    Salto_Caballo caballito(N, x, y);
    return caballito.tiempo();
}