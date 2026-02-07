#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct alunos {
    char nome[25];
    struct alunos* prox;
};
typedef struct alunos Classe;

/* Cria uma lista vazia */
Classe* inicializa(void) {
    return NULL;
}

/* Cria um nó novo */
static Classe* novo_no(const char* nome) {
    Classe* no = (Classe*)malloc(sizeof(Classe));
    if (!no) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    /* Copia com segurança e garante '\0' no final */
    strncpy(no->nome, nome, sizeof(no->nome) - 1);
    no->nome[sizeof(no->nome) - 1] = '\0';
    no->prox = NULL;
    return no;
}

/* Insere no início (push front) */
Classe* insere_inicio(Classe* head, const char* nome) {
    Classe* no = novo_no(nome);
    no->prox = head;
    return no; /* novo head */
}

/* Insere no fim (push back) */
Classe* insere_fim(Classe* head, const char* nome) {
    Classe* no = novo_no(nome);

    if (head == NULL) return no;

    Classe* p = head;
    while (p->prox != NULL) p = p->prox;
    p->prox = no;
    return head;
}

/* Busca por nome (retorna ponteiro para o nó, ou NULL) */
Classe* busca(Classe* head, const char* nome) {
    for (Classe* p = head; p != NULL; p = p->prox) {
        if (strcmp(p->nome, nome) == 0) return p;
    }
    return NULL;
}

/* Remove o primeiro nó com o nome informado.
   Retorna o novo head (pode mudar se remover o primeiro). */
Classe* remove_nome(Classe* head, const char* nome) {
    Classe* ant = NULL;
    Classe* p = head;

    while (p != NULL && strcmp(p->nome, nome) != 0) {
        ant = p;
        p = p->prox;
    }

    if (p == NULL) {
        /* não achou */
        return head;
    }

    if (ant == NULL) {
        /* removeu o primeiro */
        head = p->prox;
    } else {
        ant->prox = p->prox;
    }

    free(p);
    return head;
}

/* Imprime a lista */
void imprime(Classe* head) {
    printf("Lista: ");
    for (Classe* p = head; p != NULL; p = p->prox) {
        printf("[%s] -> ", p->nome);
    }
    printf("NULL\n");
}

/* Libera toda a lista */
void libera(Classe* head) {
    while (head != NULL) {
        Classe* tmp = head;
        head = head->prox;
        free(tmp);
    }
}

/* Exemplo de uso */
int main(void) {
    Classe* turma = inicializa();

    turma = insere_inicio(turma, "Ana");
    turma = insere_fim(turma, "Bruno");
    turma = insere_fim(turma, "Carla");
    turma = insere_fim(turma, "Cris");
    turma = insere_fim(turma, "Cris Flores");

    imprime(turma);

    Classe* achou = busca(turma, "Bruno");
    if (achou) printf("Encontrado: %s\n", achou->nome);

    turma = remove_nome(turma, "Ana");
    imprime(turma);

    libera(turma);
    return 0;
}
