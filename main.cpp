#include <iostream>
#include "criarTabela.h"
#include "crud.h"
using namespace std;
int main(){
    Crud crud;
    Tabela tabela;
    tabela.criarTabela();
    int opcoesMenu;
    bool saidaMenu = false;
    do {
        cout <<"1 - Pesquisar Item do estoque"<<endl;
        cout <<"2 - Adicionar componente ao estoque"<<endl;
        cout <<"3 - Atualizar um componente do estoque "<<endl;
        cout <<"4 - Remover um componente do estoque"<<endl;
        cout <<"5 - Help "<<endl;
        cout <<"6 - Sair "<<endl<<endl;
        cout <<">>";
        cin >> opcoesMenu;
        switch (opcoesMenu) {
            case 1:
                cout <<"1 - Pesquisar Item do estoque"<<endl<<endl;
                crud.pesquisarComponente();
                break;
            case 2:
                cout <<"2 - Adicionar componente ao estoque"<<endl<<endl;
                crud.adicionarComponente();
                break;
            case 3:
                cout <<"3 - Atualizar um componente do estoque "<<endl<<endl;
                crud.atualizarComponente();
                break;
            case 4:
                cout <<"4 - Remover um componente do estoque"<<endl<<endl;
                crud.excluirComponente();
                break;
            case 5:
                cout <<"5 - Help "<<endl<<endl;
                break;
            case 6:
                saidaMenu = true;
                break;
            default:
                cout <<"Opção Inválida!"<<endl;
                cout <<"Por favor escolher uma opção válida!"<<endl<<endl;
                break;
        }

        cin.ignore();
    } while (!saidaMenu);
    return 0;
}