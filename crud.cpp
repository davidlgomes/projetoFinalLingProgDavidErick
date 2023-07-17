#include <iostream>
#include <sqlite3.h>
#include "componente.h"
#include "crud.h"
using namespace std;
int Crud::adicionarComponente() {
    Componente componente;
    sqlite3* db;
    char* errMsg = nullptr;

    // Abra o banco de dados ou crie um novo arquivo caso não exista
    int rc = sqlite3_open("banco_de_dados.db", &db);

    if (rc != SQLITE_OK) {
        // Lida com erros na abertura do banco de dados
        cout << "Erro ao abrir o banco de dados: " << sqlite3_errmsg(db) << endl;
        return 1;
    }

    // Dados do novo componente
    int idComponente;
    string partNumber;
    string categoria;
    int quantidade;
    int fornecedorId;
    string dataCompra;
    int estoqueId;

    // Captura dos dados do novo componente
    cout << "ID do componente: " << componente.idComponente << endl;
    cout << "Part Number: " << componente.partNumber << endl;
    cout << "Categoria: " << componente.categoria << endl;
    cout << "Quantidade: " << componente.quantidade << endl;
    cout << "Fornecedor: " << componente.fornecedorId << endl;
    cout << "data de compra: " << componente.dataCompra << endl;
    cout << "Estoque: " << componente.estoqueId << endl;
    
    cout << "Informe a quantidade do componente: ";
    cin >> quantidade;

    cout << "Informe o ID do fornecedor: ";
    cin >> fornecedorId;

    cout << "Informe a data de compra do componente: ";
    cin >> dataCompra;

    cout << "Informe o ID do estoque: ";
    cin >> estoqueId;

    // Monta o SQL para inserir o novo componente
    string sql = "INSERT INTO Componente (idComponente, partNumber, categoria, quantidade, Fornecedor_idFornecedor, dataCompra, Estoque_idEstoque) VALUES (" +
        to_string(idComponente) + ", '" + partNumber + "', '" + categoria + "', " + to_string(quantidade) + ", " +
        to_string(fornecedorId) + ", '" + dataCompra + "', " + to_string(estoqueId) + ");";

    // Execute o script SQL
    rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);

    if (rc != SQLITE_OK) {
        // Lida com erros na execução do script SQL
        cout << "Erro ao adicionar o componente: " << errMsg << endl;
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 1;
    }

    // Feche a conexão com o banco de dados
    sqlite3_close(db);

    cout << "Componente adicionado com sucesso." << endl;
    return 0;
}