#include <iostream>
#include "./sqlite3/sqlite-autoconf-3360000/sqlite3.h"
#include "criarTabela.h"

using namespace std;

int Tabela::criarTabela() {
    sqlite3* db;
    char* errMsg = nullptr;

    // Abra o banco de dados ou crie um novo arquivo caso não exista
    int rc = sqlite3_open("banco_de_dados.db", &db);

    if (rc != SQLITE_OK) {
        // Lida com erros na abertura do banco de dados
        cout << "Erro ao abrir o banco de dados: " << sqlite3_errmsg(db) << endl;
        return 1;
    }

    // Execute o script SQL
    const char* sqlScript = R"(
        -- -----------------------------------------------------
        -- Database mydb
        -- -----------------------------------------------------
        PRAGMA foreign_keys = off;

        -- -----------------------------------------------------
        -- Table Componente
        -- -----------------------------------------------------
        DROP TABLE IF EXISTS Componente;
        CREATE TABLE Componente (
            idComponente INTEGER PRIMARY KEY,
            partNumber TEXT NOT NULL,
            categoria TEXT NOT NULL,
            quantidade INTEGER NOT NULL,
            Fornecedor_idFornecedor INTEGER NOT NULL,
            dataCompra DATE NOT NULL,
            Estoque_idEstoque INTEGER NOT NULL
        );

        -- -----------------------------------------------------
        -- Table Estoque
        -- -----------------------------------------------------
        DROP TABLE IF EXISTS Estoque;
        CREATE TABLE Estoque (
            idEstoque INTEGER PRIMARY KEY,
            endereco TEXT NOT NULL,
            Fornecedor_idFornecedor INTEGER NOT NULL,
            Fornecedor_nome TEXT NOT NULL
        );

        -- -----------------------------------------------------
        -- Table Fornecedor
        -- -----------------------------------------------------
        DROP TABLE IF EXISTS Fornecedor;
        CREATE TABLE Fornecedor (
            idFornecedor INTEGER PRIMARY KEY,
            nome TEXT NOT NULL,
            CNPJ TEXT NOT NULL
        );

        PRAGMA foreign_keys = on;
    )";

    rc = sqlite3_exec(db, sqlScript, nullptr, nullptr, &errMsg);

    if (rc != SQLITE_OK) {
        // Lida com erros na execução do script SQL
        cout << "Erro ao executar o script SQL: " << errMsg << endl;
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 1;
    }

    // Feche a conexão com o banco de dados
    sqlite3_close(db);

    cout << "Script SQL executado com sucesso." << endl;
    return 0;
}
