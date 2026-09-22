#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 10
#define MAX_TASKS 50
#define TAM_TEXTO 100

typedef struct {
    char username[TAM_TEXTO];
    char password[TAM_TEXTO];
} Usuario;

typedef struct {
    char usuarioOwner[TAM_TEXTO];
    char descricao[TAM_TEXTO];
} Tarefa;

// Protótipos das funções
void carregarDados();
void salvarDados();
int realizarLogin();
void realizarCadastro();
void menuTarefas(char *usuarioLogado);
void adicionarTarefa(char *usuarioLogado);
void listarTarefas(char *usuarioLogado);
void removerTarefa(char *usuarioLogado);

Usuario usuarios[MAX_USERS];
Tarefa tarefas[MAX_TASKS];
int totalUsuarios = 0;
int totalTarefas = 0;

int main() {
    carregarDados();
    int opcao;

    while (1) {
        printf("\n=================================\n");
        printf("    SISTEMA DE TAREFAS (CLI)     \n");
        printf("=================================\n");
        printf("1. Login\n");
        printf("2. Cadastrar Novo Usuario\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        if (scanf("%d", &opcao) != 1) break;
        getchar(); // Limpar buffer do teclado

        if (opcao == 1) {
            int idx = realizarLogin();
            if (idx != -1) {
                menuTarefas(usuarios[idx].username);
            }
        } else if (opcao == 2) {
            realizarCadastro();
        } else if (opcao == 0) {
            salvarDados();
            printf("\nSaindo... Dados salvos com sucesso!\n");
            break;
        } else {
            printf("\nOpcao invalida!\n");
        }
    }
    return 0;
}

void realizarCadastro() {
    if (totalUsuarios >= MAX_USERS) {
        printf("\nLimite maximo de usuarios atingido!\n");
        return;
    }

    char user[TAM_TEXTO], pass[TAM_TEXTO];
    printf("\n--- Novo Cadastro ---\n");
    printf("Digite o usuario: ");
    fgets(user, TAM_TEXTO, stdin);
    user[strcspn(user, "\n")] = 0;

    // Verificar se usuário já existe
    for (int i = 0; i < totalUsuarios; i++) {
        if (strcmp(usuarios[i].username, user) == 0) {
            printf("Erro: Usuario ja cadastrado!\n");
            return;
        }
    }

    printf("Digite a senha: ");
    fgets(pass, TAM_TEXTO, stdin);
    pass[strcspn(pass, "\n")] = 0;

    strcpy(usuarios[totalUsuarios].username, user);
    strcpy(usuarios[totalUsuarios].password, pass);
    totalUsuarios++;

    salvarDados();
    printf("Usuario cadastrado com sucesso!\n");
}

int realizarLogin() {
    char user[TAM_TEXTO], pass[TAM_TEXTO];
    printf("\n--- Login ---\n");
    printf("Usuario: ");
    fgets(user, TAM_TEXTO, stdin);
    user[strcspn(user, "\n")] = 0;

    printf("Senha: ");
    fgets(pass, TAM_TEXTO, stdin);
    pass[strcspn(pass, "\n")] = 0;

    for (int i = 0; i < totalUsuarios; i++) {
        if (strcmp(usuarios[i].username, user) == 0 && strcmp(usuarios[i].password, pass) == 0) {
            printf("\nLogin bem-sucedido! Bem-vindo(a), %s!\n", user);
            return i;
        }
    }

    printf("\nUsuario ou senha incorretos!\n");
    return -1;
}

void menuTarefas(char *usuarioLogado) {
    int opcao;
    do {
        printf("\n--- MENU DE TAREFAS (%s) ---\n", usuarioLogado);
        printf("1. Listar Minhas Tarefas\n");
        printf("2. Adicionar Tarefa\n");
        printf("3. Remover Tarefa\n");
        printf("0. Logout\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpar buffer

        switch (opcao) {
            case 1: listarTarefas(usuarioLogado); break;
            case 2: adicionarTarefa(usuarioLogado); break;
            case 3: removerTarefa(usuarioLogado); break;
            case 0: printf("\nSaindo da conta...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

void adicionarTarefa(char *usuarioLogado) {
    if (totalTarefas >= MAX_TASKS) {
        printf("\nLimite maximo de tarefas atingido!\n");
        return;
    }

    printf("\nDigite a descricao da tarefa: ");
    fgets(tarefas[totalTarefas].descricao, TAM_TEXTO, stdin);
    tarefas[totalTarefas].descricao[strcspn(tarefas[totalTarefas].descricao, "\n")] = 0;
    strcpy(tarefas[totalTarefas].usuarioOwner, usuarioLogado);

    totalTarefas++;
    salvarDados();
    printf("Tarefa adicionada com sucesso!\n");
}

void listarTarefas(char *usuarioLogado) {
    printf("\n--- Suas Tarefas ---\n");
    int contador = 0;
    for (int i = 0; i < totalTarefas; i++) {
        if (strcmp(tarefas[i].usuarioOwner, usuarioLogado) == 0) {
            printf("[%d] %s\n", i + 1, tarefas[i].descricao);
            contador++;
        }
    }
    if (contador == 0) {
        printf("Nenhuma tarefa encontrada.\n");
    }
}

void removerTarefa(char *usuarioLogado) {
    listarTarefas(usuarioLogado);
    if (totalTarefas == 0) return;

    int indice;
    printf("\nDigite o numero da tarefa que deseja remover: ");
    scanf("%d", &indice);
    getchar();

    int indiceReal = indice - 1;

    if (indiceReal >= 0 && indiceReal < totalTarefas && strcmp(tarefas[indiceReal].usuarioOwner, usuarioLogado) == 0) {
        for (int i = indiceReal; i < totalTarefas - 1; i++) {
            tarefas[i] = tarefas[i + 1];
        }
        totalTarefas--;
        salvarDados();
        printf("Tarefa removida com sucesso!\n");
    } else {
        printf("Numero de tarefa invalido!\n");
    }
}

void salvarDados() {
    FILE *fUsers = fopen("usuarios.dat", "wb");
    if (fUsers) {
        fwrite(&totalUsuarios, sizeof(int), 1, fUsers);
        fwrite(usuarios, sizeof(Usuario), totalUsuarios, fUsers);
        fclose(fUsers);
    }

    FILE *fTasks = fopen("tarefas.dat", "wb");
    if (fTasks) {
        fwrite(&totalTarefas, sizeof(int), 1, fTasks);
        fwrite(tarefas, sizeof(Tarefa), totalTarefas, fTasks);
        fclose(fTasks);
    }
}

void carregarDados() {
    FILE *fUsers = fopen("usuarios.dat", "rb");
    if (fUsers) {
        fread(&totalUsuarios, sizeof(int), 1, fUsers);
        fread(usuarios, sizeof(Usuario), totalUsuarios, fUsers);
        fclose(fUsers);
    }

    FILE *fTasks = fopen("tarefas.dat", "rb");
    if (fTasks) {
        fread(&totalTarefas, sizeof(int), 1, fTasks);
        fread(tarefas, sizeof(Tarefa), totalTarefas, fTasks);
        fclose(fTasks);
    }
}