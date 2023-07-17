#ifndef COMPONENTE_H
#define COMPONENTE_H

#include <string>
using namespace std;
struct Componente {
    int idComponente;
    string partNumber;
    string categoria;
    int quantidade;
    int fornecedorId;
    string dataCompra;
    int estoqueId;
};
istream& operator>>(istream& input, Componente& componente);

#endif // COMPONENTE_H
