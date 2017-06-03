#include "mt.h"
#include <iostream>
#include <cmath>

// [PT] Caso você não queira utilizar uma versão buildada da biblioteca (linux = .so, win = .dll ou mac = .bundle)
// você pode apenas copiar os arquivos TimedQueue.cpp/.h ServerList.cpp/.h e mt.cpp/.h para o seu novo projeto.
// Não é necessário copiar o library.cpp/.h, desde que você copie a função ExecMM1 diretamente para o "MeuProjeto".cpp

// Não esqueça de incluir eles na sua compilação --> g++ MeuProjeto.cpp TimedQueue.cpp ServerList....

extern "C" {
    void Hello ();
    void Log(const char * str);
    double ExecMM1(int exponent, float interArrivalMean, float serviceRateMean, int servers, bool listQueue);
}