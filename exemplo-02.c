#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct alunos {
    char nome[25];
    struct alunos* prox;
};
typedef struct alunos Classe;

/* ---------- Funções básicas ---------- */

Classe* inicializa(void) {
    return NULL;
}

static void ler_linha(char *buf, size_t tam) {
    if (fgets(buf, (int)tam, stdin) == NULL) {
        buf[0] = '\0';
        return;
    }
    /* remove \n */
    size_t n = strcspn(buf, "\n");
    buf[n] = '\0';
}

static Classe* novo_no(const char* nome) {
    Classe* no = (Classe*)malloc(sizeof(Classe));
    if (!no) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    strncpy(no->nome, nome, sizeof(no->nome) - 1);
    no->nome[sizeof(no->nome) - 1] = '\0';
    no->prox = NULL;
    return no;
}

Classe* insere_inicio(Classe* head, const char* nome) {
    Classe* no = novo_no(nome);
    no->prox = head;
    return no;
}

Classe* insere_fim(Classe* head, const char* nome) {
    Classe* no = novo_no(nome);
    if (head == NULL) return no;

    Classe* p = head;
    while (p->prox != NULL) p = p->prox;
    p->prox = no;
    return head;
}

Classe* busca(Classe* head, const char* nome) {
    for (Classe* p = head; p != NULL; p = p->prox) {
        if (strcmp(p->nome, nome) == 0) return p;
    }
    return NULL;
}

Classe* remove_nome(Classe* head, const char* nome) {
    Classe* ant = NULL;
    Classe* p = head;

    while (p != NULL && strcmp(p->nome, nome) != 0) {
        ant = p;
        p = p->prox;
    }
    if (p == NULL) return head; /* não achou */

    if (ant == NULL) head = p->prox; /* removeu o primeiro */
    else ant->prox = p->prox;

    free(p);
    return head;
}

void imprime(Classe* head) {
    if (head == NULL) {
        printf("Lista vazia (head == NULL)\n");
        return;
    }
    printf("Lista: ");
    for (Classe* p = head; p != NULL; p = p->prox) {
        printf("[%s] -> ", p->nome);
    }
    printf("NULL\n");
}

void libera(Classe* head) {
    while (head != NULL) {
        Classe* tmp = head;
        head = head->prox;
        free(tmp);
    }
}

/* ---------- Menu ---------- */

static void mostrar_menu(void) {
    printf("\n=== MENU (Lista Ligada de Alunos) ===\n");
    printf("1) Inserir no inicio\n");
    printf("2) Inserir no fim\n");
    printf("3) Buscar por nome\n");
    printf("4) Remover por nome\n");
    printf("5) Imprimir lista\n");
    printf("0) Sair\n");
    printf("Escolha: ");
}

int main(void) {
    Classe* turma = inicializa();
    char nome[25];
    int op = -1;

    do {
        mostrar_menu();

        if (scanf("%d", &op) != 1) {
            /* limpando entrada inválida */
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            op = -1;
            printf("Entrada invalida. Tente novamente.\n");
            continue;
        }

        /* consome o \n que sobrou do scanf */
        getchar();

        switch (op) {
            case 1:
                printf("Nome do aluno: ");
                ler_linha(nome, sizeof(nome));
                if (nome[0] == '\0') {
                    printf("Nome vazio. Operacao cancelada.\n");
                } else {
                    turma = insere_inicio(turma, nome);
                    printf("Inserido no inicio.\n");
                }
                break;

            case 2:
                printf("Nome do aluno: ");
                ler_linha(nome, sizeof(nome));
                if (nome[0] == '\0') {
                    printf("Nome vazio. Operacao cancelada.\n");
                } else {
                    turma = insere_fim(turma, nome);
                    printf("Inserido no fim.\n");
                }
                break;

            case 3: {
                printf("Nome para buscar: ");
                ler_linha(nome, sizeof(nome));
                Classe* p = busca(turma, nome);
                if (p) printf("Encontrado: %s\n", p->nome);
                else printf("Nao encontrado.\n");
                break;
            }

            case 4:
                printf("Nome para remover: ");
                ler_linha(nome, sizeof(nome));
                if (busca(turma, nome) == NULL) {
                    printf("Nao encontrado. Nada removido.\n");
                } else {
                    turma = remove_nome(turma, nome);
                    printf("Removido.\n");
                }
                break;

            case 5:
                imprime(turma);
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida.\n");
                break;
        }

    } while (op != 0);

    libera(turma);
    return 0;
}
