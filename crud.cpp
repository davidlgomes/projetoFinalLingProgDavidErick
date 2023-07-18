#include <iostream>
#include "./sqlite3/sqlite-autoconf-3360000/sqlite3.h"
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

    cout << "Informe o ID do componente:";
    cin >> idComponente;
    cout << "Informe o Part Number do componete:";
    cin >> partNumber;
    cout << "Infome a categoria do componente:";
    cin >> categoria;
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
// Atualizar informações de algum Componente    
int Crud::atualizarComponente() {
    int idComponente,atributoNovo;
    bool saida=true;
    // Solicita ao usuário o ID do componente a ser atualizado
    cout << "Informe o ID do componente que deseja atualizar: ";
    cin >> idComponente;
    
    // Abre a conexão com o banco de dados
    sqlite3* db;
    char* errMsg = nullptr;
    int rc = sqlite3_open("banco_de_dados.db", &db);

    if (rc != SQLITE_OK) {
        cout << "Erro ao abrir o banco de dados: " << sqlite3_errmsg(db) << endl;
        return 1;
    }

    // Verifica se o componente com o ID informado existe no banco de dados
    string sql = "SELECT * FROM Componente WHERE idComponente = " + to_string(idComponente) + ";";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        cout << "Erro ao buscar o componente: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return 1;
    }

    // Verifica se o componente foi encontrado
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW) {
        cout << "Componente com o ID " << idComponente << " não encontrado." << endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 1;
    }

    // Recupera as informações atuais do componente
    Componente componente;
    componente.idComponente = sqlite3_column_int(stmt, 0);
    componente.partNumber = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
    componente.categoria = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
    componente.quantidade = sqlite3_column_int(stmt, 3);
    componente.fornecedorId = sqlite3_column_int(stmt, 4);
    componente.dataCompra = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
    componente.estoqueId = sqlite3_column_int(stmt, 6);

    // Exibe as informações atuais do componente
    cout << "Informações atuais do componente:" << endl;
    cout << "ID do componente: " << componente.idComponente << endl;
    cout << "Part Number: " << componente.partNumber << endl;
    cout << "Categoria: " << componente.categoria << endl;
    cout << "Quantidade: " << componente.quantidade << endl;
    cout << "Fornecedor: " << componente.fornecedorId << endl;
    cout << "Data de compra: " << componente.dataCompra << endl;
    cout << "Estoque: " << componente.estoqueId << endl;

    // Solicita as novas informações do componente ao usuário
     while(saida==true){
        int escolha;
        string categoria;
        cout<<endl;
        cout<<"O que você deseja modificar?"<<endl<<endl;
        cout<<"1) Para mofificar o PartNumber do componente."<<endl;
        cout<<"2) Para mofificar a categoria do componente."<<endl;
        cout<<"3) Para mofificar a quantidade do componente."<<endl;
        cout<<"4) Para mofificar o ID do fornecedor do componente."<<endl;
        cout<<"5) Para mofificar a data da compra do componente."<<endl;
        cout<<"6) Para mofificar o ID do estoque."<<endl<<endl;
        cout<<"7) Para sair deste menu."<<endl;
        cin>>escolha;
        switch(escolha){
            case 1:
                cout << "Informe o PartNumber do componente: ";
                cin >> atributoNovo;
                // Monta o SQL para atualizar o componente com as novas informações
                sql = "UPDATE Componente SET partNumber = " + to_string(atributoNovo) +" WHERE idComponente = " + to_string(idComponente) + ";";
                saida=false;
                break;   
            case 2:
                cout << "Informe a nova categoria do componente: ";
                cin >> categoria;
                // Monta o SQL para atualizar o componente com as novas informações
                sql = "UPDATE Componente SET categoria = '" + categoria +"'WHERE idComponente = " + to_string(idComponente) + ";";
                saida=false;
                break;
            case 3:
                cout << "Informe a nova quantidade do componente: ";
                cin >> atributoNovo;
                // Monta o SQL para atualizar o componente com as novas informações
                sql = "UPDATE Componente SET quantidade = " + to_string(atributoNovo) +" WHERE idComponente = " + to_string(idComponente) + ";";
                saida=false;
                break;
            case 4:
                cout << "Informe o novo ID do fornecedor do componente: ";
                cin >> atributoNovo;
                // Monta o SQL para atualizar o componente com as novas informações
                sql = "UPDATE Componente SET Fornecedor_idFornecedor = " + to_string(atributoNovo) +" WHERE idComponente = " + to_string(idComponente) + ";";
                saida=false;
                break;
            case 5:
                cout << "Informe a nova data de compra do componente: ";
                cin >> atributoNovo;
                // Monta o SQL para atualizar o componente com as novas informações
                sql = "UPDATE Componente SET dataCompra = " + to_string(atributoNovo) +" WHERE idComponente = " + to_string(idComponente) + ";";
                saida=false;
                break;
            case 6:
                cout << "Informe o novo ID do estoque: ";
                cin >> atributoNovo;
                // Monta o SQL para atualizar o componente com as novas informações
                sql = "UPDATE Componente SET Estoque_idEstoque = " + to_string(atributoNovo) +" WHERE idComponente = " + to_string(idComponente) + ";";
                saida=false;
                break;
            case 7:
                saida=false;
                break;
            default:
                cout<<endl<<"Entre com algum valor válido."<<endl;
                break;
        }
     }
   
    // Executa o script SQL
    rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);

    if (rc != SQLITE_OK) {
        cout << "Erro ao atualizar o componente: " << errMsg << endl;
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 1;
    }

    // Fecha a conexão com o banco de dados
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    cout << "Componente atualizado com sucesso." << endl;
    return 0;

}

int Crud:: excluirComponente(){
    int idComponente;

    // Solicita ao usuário o ID do componente a ser excluído
    cout << endl<<"Informe o ID do componente que deseja excluir: ";
    cin >> idComponente;

    // Abre a conexão com o banco de dados
    sqlite3* db;
    char* errMsg = nullptr;
    int rc = sqlite3_open("banco_de_dados.db", &db);

    if (rc != SQLITE_OK) {
        cout << "Erro ao abrir o banco de dados: " << sqlite3_errmsg(db) << endl;
        return 1;
    }

    // Monta o SQL para excluir o componente pelo ID informado
    string sql = "DELETE FROM Componente WHERE idComponente = " + to_string(idComponente) + ";";

    // Executa o script SQL
    rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);

    if (rc != SQLITE_OK) {
        cout << "Erro ao excluir o componente: " << errMsg << endl;
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 1;
    }

    // Fecha a conexão com o banco de dados
    sqlite3_close(db);

    cout << "Componente excluído com sucesso." << endl;
    return 0;
}

int Crud::pesquisarComponente() {
    int idComponente;
    int escolha;
    // Solicita ao usuário o ID do componente a ser buscado
    cout << "Informe o ID do componente pelo qual você deseja pesquisar: ";
    cin >> idComponente;

    // Abre a conexão com o banco de dados
    sqlite3* db;
    char* errMsg = nullptr;
    int rc = sqlite3_open("banco_de_dados.db", &db);

    if (rc != SQLITE_OK) {
        cout << "Erro ao abrir o banco de dados: " << sqlite3_errmsg(db) << endl;
        return 1;
    }

    // Monta o SQL para buscar o componente pelo ID informado
    string sql = "SELECT * FROM Componente WHERE idComponente = " + to_string(idComponente) + ";";

    // Executa o script SQL
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        cout << "Erro ao buscar o componente: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return 1;
    }

    // Verifica se o componente foi encontrado
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW) {
        cout << "Componente com o ID " << idComponente << " não encontrado." << endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 1;
    }

    // Recupera as informações do componente encontrado
    Componente componente;
    componente.idComponente = sqlite3_column_int(stmt, 0);
    componente.partNumber = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
    componente.categoria = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
    componente.quantidade = sqlite3_column_int(stmt, 3);
    componente.fornecedorId = sqlite3_column_int(stmt, 4);
    componente.dataCompra = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
    componente.estoqueId = sqlite3_column_int(stmt, 6);

    // Exibe as informações do componente encontrado
    cout << "Informações do componente encontrado:" << endl;
    cout << "ID do componente: " << componente.idComponente << endl;
    cout << "Part Number: " << componente.partNumber << endl;
    cout << "Categoria: " << componente.categoria << endl;
    cout << "Quantidade: " << componente.quantidade << endl;
    cout << "Fornecedor: " << componente.fornecedorId << endl;
    cout << "Data de compra: " << componente.dataCompra << endl;
    cout << "Estoque: " << componente.estoqueId << endl;

    // Fecha a conexão com o banco de dados
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    bool saida = false;

    while(saida==false){
        
        cout<<endl<<"Deseja realizar alguma dessas funções?"<<endl;
        cout <<"1 - Adicionar componente ao estoque"<<endl;
        cout <<"2 - Atualizar um componente do estoque "<<endl;
        cout <<"3 - Remover um componente do estoque"<<endl;
        cout <<"4 - Para sair."<<endl;
        cin >> escolha;
    }
    switch (escolha)
    {
    case 1:
        adicionarComponente();
        break;
    case 2:
        atualizarComponente();
        break;
    case 3:
        excluirComponente();
        break;
    case 4:
        cout<<endl;
        saida=true;
        break;
    default:
        cout<<"Digite algum valor válido."<<endl;
        break;
    }
    return 0;
}