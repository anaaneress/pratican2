#include <stdio.h>
#include <string.h>

char cliente[50], telefone[20], pet[50], especie[20], raca[30], porte[20];
char funcionario[30];
char itens[100][50];
int quantidades[100], cont = 0;
float valores[100], total = 0;
int clienteCadastrado = 0, petCadastrado = 0;

float banho() {
    if (strcmp(porte, "pequeno") == 0) return 30;
    if (strcmp(porte, "medio") == 0) return 45;
    if (strcmp(porte, "grande") == 0) return 60;
    return 0;
}

float tosa(int op) {
    float precos[] = {25, 50, 70};
    if (op >= 1 && op <= 3) return precos[op - 1];
    return 0;
}

float veterinaria(int op) {
    float precos[] = {100, 60, 80};
    if (op >= 1 && op <= 3) return precos[op - 1];
    return 0;
}

void registrar(char nome[], int qtd, float valor) {
    if (cont < 100) {
        strcpy(itens[cont], nome);
        quantidades[cont] = qtd;
        valores[cont] = valor;
        total += valor;
        cont++;
    }
}

void cadastro() {
    int op;

    do {
        printf("\n--- cadastros ---\n1 - cliente\n2 - pet\n0 - voltar\nopcao: ");
        scanf("%d", &op);
        getchar();

        switch (op) {
            case 1:
                printf("nome do cliente: ");
                fgets(cliente, 50, stdin);
                cliente[strcspn(cliente, "\n")] = 0;

                printf("telefone: ");
                fgets(telefone, 20, stdin);
                telefone[strcspn(telefone, "\n")] = 0;

                clienteCadastrado = 1;
                printf("cliente cadastrado!\n");
                break;

            case 2:
                if (!clienteCadastrado) {
                    printf("cadastre o cliente primeiro!\n");
                    break;
                }

                printf("nome do pet: ");
                fgets(pet, 50, stdin);
                pet[strcspn(pet, "\n")] = 0;

                printf("especie: ");
                fgets(especie, 20, stdin);
                especie[strcspn(especie, "\n")] = 0;

                printf("raca: ");
                fgets(raca, 30, stdin);
                raca[strcspn(raca, "\n")] = 0;

                printf("porte (pequeno, medio ou grande): ");
                fgets(porte, 20, stdin);
                porte[strcspn(porte, "\n")] = 0;

                if (banho() == 0) {
                    printf("porte invalido!\n");
                    petCadastrado = 0;
                } else {
                    petCadastrado = 1;
                    printf("pet cadastrado!\n");
                }
                break;

            case 0:
                break;

            default:
                printf("opcao invalida!\n");
        }
    } while (op != 0);
}

void servicos() {
    int op, tipo;
    float preco;
    char nome[50];

    if (!petCadastrado) {
        printf("cadastre o cliente e o pet primeiro!\n");
        return;
    }

    do {
        printf("\n--- servicos ---\n1 - banho\n2 - tosa\n3 - veterinaria\n0 - voltar\nopcao: ");
        scanf("%d", &op);
        preco = 0;

        switch (op) {
            case 1:
                preco = banho();
                strcpy(nome, "banho");
                break;

            case 2:
                printf("1 - higienica (r$ 25)\n2 - completa (r$ 50)\n3 - na tesoura (r$ 70)\ntipo: ");
                scanf("%d", &tipo);
                preco = tosa(tipo);

                if (tipo == 1) strcpy(nome, "tosa higienica");
                else if (tipo == 2) strcpy(nome, "tosa completa");
                else if (tipo == 3) strcpy(nome, "tosa na tesoura");
                break;

            case 3:
                printf("1 - consulta (r$ 100)\n2 - vacina (r$ 60)\n3 - exame (r$ 80)\ntipo: ");
                scanf("%d", &tipo);
                preco = veterinaria(tipo);

                if (tipo == 1) strcpy(nome, "consulta");
                else if (tipo == 2) strcpy(nome, "vacina");
                else if (tipo == 3) strcpy(nome, "exame");
                break;

            case 0:
                break;

            default:
                printf("opcao invalida!\n");
        }

        if (preco > 0) {
            registrar(nome, 1, preco);
            printf("servico registrado! r$ %.2f\n", preco);
        } else if (op >= 1 && op <= 3) {
            printf("opcao invalida!\n");
        }

    } while (op != 0);
}

void produtos() {
    char nomes[3][3][50] = {
        {"racao cao", "racao gato", "petisco"},
        {"coleira", "brinquedo", "caminha"},
        {"shampoo", "sabonete", "escova"}
    };

    float precos[3][3] = {
        {120, 65, 15},
        {25, 20, 80},
        {30, 12, 15}
    };

    int categoria, produto, qtd;

    do {
        printf("\n--- produtos ---\n1 - alimentos\n2 - acessorios\n3 - higiene\n0 - voltar\ncategoria: ");
        scanf("%d", &categoria);

        if (categoria == 0) break;

        if (categoria >= 1 && categoria <= 3) {
            for (int i = 0; i < 3; i++)
                printf("%d - %s r$ %.2f\n", i + 1, nomes[categoria - 1][i], precos[categoria - 1][i]);

            printf("produto: ");
            scanf("%d", &produto);

            if (produto >= 1 && produto <= 3) {
                printf("quantidade: ");
                scanf("%d", &qtd);

                if (qtd > 0) {
                    registrar(nomes[categoria - 1][produto - 1], qtd,
                              precos[categoria - 1][produto - 1] * qtd);
                    printf("produto registrado!\n");
                } else {
                    printf("quantidade invalida!\n");
                }
            } else {
                printf("produto invalido!\n");
            }
        } else {
            printf("categoria invalida!\n");
        }

    } while (categoria != 0);
}

void comprovante() {
    if (!clienteCadastrado || !petCadastrado) {
        printf("cadastre cliente e pet primeiro!\n");
        return;
    }

    printf("\n======= comprovante =======\n");
    printf("funcionario: %s\ncliente: %s\ntelefone: %s\n", funcionario, cliente, telefone);
    printf("pet: %s\nespecie: %s\nraca: %s\nporte: %s\n", pet, especie, raca, porte);

    printf("\n--- itens ---\n");
    for (int i = 0; i < cont; i++)
        printf("%s | qtd: %d | r$ %.2f\n", itens[i], quantidades[i], valores[i]);

    printf("\ntotal: r$ %.2f\n==========================\n", total);
}

int main() {
    char usuario[30], senha[30];
    int tentativas = 0, login = 0, op;

    while (tentativas < 3 && !login) {
        printf("\nusuario: ");
        scanf("%29s", usuario);
        printf("senha: ");
        scanf("%29s", senha);

        if (strcmp(usuario, "funcionario") == 0 && strcmp(senha, "1234") == 0) {
            login = 1;
            strcpy(funcionario, usuario);
            printf("login correto!\n");
        } else {
            tentativas++;
            printf("login incorreto! tentativa %d de 3\n", tentativas);
        }
    }

    if (!login) {
        printf("acesso bloqueado!\n");
        return 0;
    }

    do {
        printf("\n===== petshop amigo fiel =====\n1 - cadastros\n2 - servicos\n3 - produtos\n4 - comprovante final\n0 - sair\nopcao: ");
        scanf("%d", &op);

        switch (op) {
            case 1: cadastro(); break;
            case 2: servicos(); break;
            case 3: produtos(); break;
            case 4: comprovante(); break;
            case 0: printf("sistema encerrado!\n"); break;
            default: printf("opcao invalida!\n");
        }
    } while (op != 0);

    return 0;
}
