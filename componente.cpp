#include <iostream>
#include "componente.h"

using namespace std;

istream& operator>>(istream& input, Componente& componente) {
    cout << "Informe o ID do componente: ";
    input >> componente.idComponente;

    cout << "Informe o part number do componente: ";
    input >> componente.partNumber;

    cout << "Informe a categoria do componente: ";
    input >> componente.categoria;

    cout << "Informe a quantidade do componente: ";
    input >> componente.quantidade;

    cout << "Informe o ID do fornecedor: ";
    input >> componente.fornecedorId;

    cout << "Informe a data de compra do componente: ";
    input >> componente.dataCompra;

    cout << "Informe o ID do estoque: ";
    input >> componente.estoqueId;

    return input;
}
