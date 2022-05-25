#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <string> 
#include <chrono>
using namespace std;


/*template <class TimeT = std::chrono::milliseconds,
    class ClockT = std::chrono::steady_clock>
    struct measure
{
    template<class F, class ...Args>
    static auto duration(F&& func, Args&&... args)
    {
        auto start = ClockT::now();
        std::invoke(std::forward<F>(func), std::forward<Args>(args)...);
        return std::chrono::duration_cast<TimeT>(ClockT::now() - start);
    }
};
*/

struct Nodo
{
    Nodo(int x, int y)
    {
        posx = x;
        posy = y;
    }
    int posx, posy;
    Nodo* contiguos[4] = { nullptr, nullptr, nullptr, nullptr };
};

struct Laberinto {
    Nodo* ini = nullptr;
    Nodo* fin = nullptr;
    int ancho, largo;
    Laberinto(vector<vector<string>> data, int a, int l) {
        ancho = a;
        largo = l;

        vector<Nodo*> nodos_tope(a);

        for (int i = 1; i < largo - 1; i++) {
            bool prev = false;
            bool act = false;
            bool sig = data[i][1] != "#";

            Nodo* nodo_izq = nullptr;

            for (int j = 1; j < ancho - 1; j++) {

                prev = act;
                act = sig;
                sig = data[i][j + 1] != "#";
                Nodo* n = nullptr;

                if (i == 1 || j == 1) {
                    if (data[i][j - 1] == "x") {  //si la entrada está a la izquierda
                        ini = new Nodo(i, j - 1);
                        nodo_izq = ini;
                        prev = true;
                    }
                    else if (data[i - 1][j] == "x") { //si la entrada está arriba
                        ini = new Nodo(i - 1, j);
                        nodos_tope[j] = ini;
                    }

                    if (data[i][j - 1] == "y") {  //si la salida está a la izquierda
                        fin = new Nodo(i, j - 1);
                        nodo_izq = fin;
                        prev = true;
                    }
                    else if (data[i - 1][j] == "y") { //si la salida está arriba
                        fin = new Nodo(i - 1, j);
                        nodos_tope[j] = fin;
                    }
                }
                if (!act) //estamos en pared
                    continue;
                if (prev) {
                    if (sig) { //. . .
                        if (data[i - 1][j] != "#" || data[i + 1][j] != "#") { //si hay decisión en este punto (seguir o ir hacia arriba/abajo)
                            n = new Nodo(i, j);
                            (*nodo_izq).contiguos[1] = n;
                            (*n).contiguos[3] = nodo_izq;
                            nodo_izq = n;
                        }
                    }
                    else { //. . # final de pasillo
                        n = new Nodo(i, j);
                        if (nodo_izq) {
                            (*nodo_izq).contiguos[1] = n;
                            (*n).contiguos[3] = nodo_izq;
                            nodo_izq = nullptr;
                        }
                    }
                }
                else {
                    if (sig) { //# . . inicio de pasillo
                        n = new Nodo(i, j);
                        nodo_izq = n;
                    }
                    else { // # . #
                        if (data[i - 1][j] != "." || data[i + 1][j] != ".") { //sin salida
                            n = new Nodo(i, j);
                        }
                    }
                }

                if (n) {
                    if (data[i - 1][j] != "#") { //si hay camino hacia arriba
                        Nodo* t = nodos_tope[j];
                        if (t) {
                            (*t).contiguos[2] = n;
                            (*n).contiguos[0] = t;
                        }
                    }
                    if (data[i + 1][j] != "#") {
                        nodos_tope[j] = n;
                    }
                    else {
                        nodos_tope[j] = nullptr;
                    }
                }
                if (i == largo - 2 || j == ancho - 2) {
                    if (data[i][j + 1] == "x") { //si la entrada está a la derecha
                        n = ini = new Nodo(i, j + 1);
                        (*nodo_izq).contiguos[1] = n;
                        (*n).contiguos[3] = nodo_izq;
                        nodo_izq = nullptr;

                    }
                    else if (data[i + 1][j] == "x") { //si la entrada está abajo
                        ini = new Nodo(i + 1, j);
                        Nodo* t = nodos_tope[j];
                        (*t).contiguos[2] = ini;
                        (*ini).contiguos[0] = t;
                    }
                    if (data[i][j + 1] == "y") { //si la salida está a la derecha
                        fin = new Nodo(i, j + 1);
                        if (nodo_izq) {
                            (*nodo_izq).contiguos[1] = fin;
                            (*fin).contiguos[3] = nodo_izq;
                            nodo_izq = nullptr;
                        }

                    }
                    else if (data[i + 1][j] == "y") { //si la salida está abajo
                        fin = new Nodo(i + 1, j);
                        Nodo* t = nodos_tope[j];
                        if (t) {
                            (*t).contiguos[2] = fin;
                            (*fin).contiguos[0] = t;
                        }
                    }
                }
            }
        }
    }
};

int GetLines(string file)
{
    ifstream archivo(file);
    return std::count(std::istreambuf_iterator<char>(archivo),
        std::istreambuf_iterator<char>(), '\n') + 1;
}

int GetColumns(string archivo) {
    ifstream file(archivo);
    string line;
    getline(file, line);
    return line.size();
}

void MatrixDeTxt(vector<vector<string>>& mat, string path, int f, int c)
{

    ifstream is(path);
    if (is)
    {
        int length = (f + 1) * c - 1;

        //Crear char* para el contenido
        char* buffer = new char[length];

        //Leer caracteres
        is.read(buffer, length);

        //Convertir char* a vector<string>
        vector<string> temp1;
        for (auto i = 0; i < length; i++)
        {
            if (buffer[i] == '\n')
            {
                mat.push_back(temp1);
                temp1.clear();
            }
            else
            {
                string aux = "";
                temp1.push_back(aux += buffer[i]);
            }

        }
        mat.push_back(temp1);
        delete[] buffer;

        is.close();
    }
}

void PrintMatrix(int f, int c, vector<vector<string>> mat) {
    for (int i = 0; i < f; i++) {
        for (int j = 0; j < c; j++) {
            cout << mat[i][j] << "\t";
        }
        cout << endl;
    }
}


/*
deque<Nodo*> resolverBFS(Laberinto lab) {
    Nodo* ini = lab.ini;
    Nodo* fin = lab.fin;
    int ancho = lab.ancho;
    int largo = lab.largo;
    deque<Nodo*> cola;
    cola.push_back(ini);
    vector<Nodo*> prev(largo * ancho, nullptr);
    vector<bool> visitado(largo * ancho);
    Nodo* actual;
    visitado[(*ini).posx * ancho + (*ini).posy] = true;

    while (!cola.empty()) {
        actual = cola.back();
        cola.pop_back();

        if (actual == fin)
            break;

        for (int i = 0; i < 4; i++) {
            Nodo* c = (*actual).contiguos[i];
            if (c) {
                int pos = (*c).posx * ancho + (*c).posy;
                if (!visitado[pos]) {
                    cola.push_front(c);
                    visitado[pos] = true;
                    prev[pos] = actual;
                }
            }
        }
    }
    cola.clear();
    actual = fin;
    while (actual) { //rellena cola desde el final
        cola.push_front(actual);
        actual = prev[(*actual).posx * ancho + (*actual).posy];
    }
    return cola;
}*/

deque<Nodo*> resolver(Laberinto lab) {
    Nodo* ini = lab.ini;
    Nodo* fin = lab.fin;
    int ancho = lab.ancho;
    int largo = lab.largo;
    deque<Nodo*> pila;
    pila.push_back(ini);
    vector<Nodo*> prev(largo * ancho, nullptr);
    vector<bool> visitado(largo * ancho);
    Nodo* actual;

    while (!pila.empty()) {
        actual = pila.back();
        pila.pop_back();

        if (actual == fin)
            break;

        visitado[(*actual).posx * ancho + (*actual).posy] = true;

        for (int i = 0; i < 4; i++) {
            Nodo* c = (*actual).contiguos[i];
            if (c) {
                int pos = (*c).posx * ancho + (*c).posy;
                if (!visitado[pos]) {
                    pila.push_back(c);
                    prev[pos] = actual;
                }
            }
        }
    }
    pila.clear();
    actual = fin;
    while (actual) { //rellena cola desde el final
        pila.push_front(actual);
        actual = prev[(*actual).posx * ancho + (*actual).posy];
    }
    return pila;
}

void trazar(vector<vector<string>>& A, deque<Nodo*> d) {
    int num = 1;
    int si = d.size() - 1;
    for (int i = 1; i < si; i++) {
        Nodo* a = d[i];
        Nodo* b = d[i + 1];

        if ((*a).posx == (*b).posx) {
            for (int j = (*a).posy; j != (*b).posy; j = ((*a).posy < (*b).posy) ? j + 1 : j - 1) {
                string str((to_string(num)).c_str());
                A[(*a).posx][j] = str;
                num++;
            }
        }
        else if ((*a).posy == (*b).posy) {
            for (int j = (*a).posx; j != (*b).posx; j = ((*a).posx < (*b).posx) ? j + 1 : j - 1) {
                string str((to_string(num)).c_str());
                A[j][(*a).posy] = str;
                num++;
            }
        }
    }
}

template <class TimeT = std::chrono::milliseconds,
    class ClockT = std::chrono::steady_clock>
    double maze_5(string text)
{
    auto start = ClockT::now();
    vector<vector<string>> A;
    int l = GetLines(text);
    int a = GetColumns(text);
    MatrixDeTxt(A, text, l, a);
    Laberinto lab(A, a, l);
    trazar(A, resolver(lab));

    ofstream bd;
    bd.open("file.txt");
    /*
    if (bd.is_open())
        for (int i = 0; i < l; i++) {
            for (int j = 0; j < a; j++) {
                bd << A[i][j] << "\t";
            }
            bd << endl;
        }

    else cout << "ERROR";
    */
    PrintMatrix(l, a, A);
    return std::chrono::duration<double, std::milli>(ClockT::now() - start).count();

}


/*void P3G3(string text) {
    cout << endl << "F runtime=" << measure<>::duration(maze, text).count() << "ms";
}*/