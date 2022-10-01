// insere biblioteca
#include "contador_caloriasAVL.h"

int qtd_nodosAVL(avl *arvore)
{
    if (arvore == NULL)
        return 0;
    else
        return 1 + qtd_nodosAVL(arvore->esquerda) + qtd_nodosAVL(arvore->direita);
}

// calcula a altura da arvore para depois ver se é avl
int alturaAVL(avl *arvore)
{
    int alturaEsquerda, alturaDireita;
    if (arvore == NULL)
        return 0;
    else
    {
        alturaEsquerda = alturaAVL(arvore->esquerda);
        alturaDireita = alturaAVL(arvore->direita);
        if (alturaEsquerda > alturaDireita)
        {
            return (1 + alturaEsquerda);
        }
        else
        {
            return (1 + alturaDireita);
        }
    }
}

// insere arvore avl
avl *insereArvoreAVL(avl *arvore, dados info, int *ok, int *rotacao)
{

    if (arvore == NULL)
    {
        arvore = (avl *)malloc(sizeof(avl));
        arvore->dados = info;
        arvore->esquerda = NULL;
        arvore->direita = NULL;
        arvore->altura = 0;
        arvore->fb = 0;
        *ok = 1;
        // return arvore;
    }
    else if (strcmp(info.alimentos, arvore->dados.alimentos) < 0)
    {
        arvore->esquerda = insereArvoreAVL(arvore->esquerda, info, ok, rotacao);
        if (*ok)
        {
            switch (arvore->fb)
            {
            case -1:
                arvore->fb = 0;
                *ok = 0;
                break;
            case 0:
                arvore->fb = 1;
                break;
            case 1:
                arvore = Caso1(arvore, ok, rotacao);
                break;
            }
        }
    }
    else
    {
        arvore->direita = insereArvoreAVL(arvore->direita, info, ok, rotacao);
        if (*ok)
        {
            switch (arvore->fb)
            {
            case 1:
                arvore->fb = 0;
                *ok = 0;
                break;
            case 0:
                arvore->fb = -1;
                break;
            case -1:
                arvore = Caso2(arvore, ok, rotacao);
                break;
            }
        }
    }

    // vai adicionando a altura toda vez que percorre
    arvore->altura = alturaAVL(arvore) + 1;

    // verifica se precisa rebalancear a árvore
    // arvore = balancear(arvore);

    return arvore;
}

int fatorBalanceamento(avl *arvore)
{
    return (alturaAVL(arvore->esquerda) - alturaAVL(arvore->direita));
}

/*------------------------PERCORRE A AVL------------------------*/
avl *consultaAVL(avl *arvore, char alimentosDia[50], int *comparacoes)
{
    int comparaAlimentos;

    if (arvore == NULL)
        return NULL;
    else
    {
        (*comparacoes)++;
        comparaAlimentos = strcmp(alimentosDia, arvore->dados.alimentos);
        if (comparaAlimentos == 0)
        {
            // saida(arvore, info, auxiliar, gramas, arqSaida);
            //printf("%s %d", arvore->dados.alimentos, arvore->dados.calorias);
            return arvore;
        }
        else
        {
            if (comparaAlimentos > 0)
                return consultaAVL(arvore->direita, alimentosDia, comparacoes);
            else
                return consultaAVL(arvore->esquerda, alimentosDia, comparacoes);
        }
    }
}

/*------------------------CASOS------------------------*/
// base retirada dos exemplos no Moodle da disciplina
/*-----------------------------------------------------*/

avl *Caso1(avl *arvore, int *ok, int *rotacao)
{
    avl *auxiliar;

    auxiliar = arvore->esquerda;
    if (auxiliar->fb == 1)
    {
        // printf("fazendo rotacao direita em %s\n",a->nodoInfo.alimento);
        arvore = rotacaoDireita(arvore);
        (*rotacao)++;
    }

    else
    {
        // printf("fazendo rotacao dupla direita em %s\n",a->nodoInfo.alimento);
        arvore = rotacaoDuplaDireita(arvore);
        (*rotacao)++;
    }

    arvore->fb = 0;
    *ok = 0;
    return arvore;
}

avl *Caso2(avl *arvore, int *ok, int *rotacao)
{
    avl *auxiliar;

    auxiliar = arvore->direita;
    if (auxiliar->fb == -1)
    {
        // desenha(arvore,1);
        // printf("fazendo rotacao esquerda em %s\n",arvore->dados.alimentos);
        arvore = rotacaoEsquerda(arvore);
        (*rotacao)++;
    }

    else
    {
        // desenha(arvore,1);
        // printf("fazendo rotacao dupla esquerda em %s\n",arvore->dados.alimentos);
        arvore = rotacaoDuplaEsquerda(arvore);
        (*rotacao)++;
    }

    arvore->fb = 0;
    *ok = 0;
    return arvore;
}

/*------------------------ROTAÇÕES------------------------*/
// base retirada dos exemplos no Moodle da disciplina
/*-----------------------------------------------------*/

avl *rotacaoEsquerda(avl *ponteiro)
{
    avl *auxiliar;

    auxiliar = ponteiro->direita;
    ponteiro->direita = auxiliar->esquerda;
    auxiliar->esquerda = ponteiro;
    ponteiro->fb = 0;
    ponteiro = auxiliar;

    return ponteiro;
}

avl *rotacaoDireita(avl *ponteiro)
{
    avl *auxiliar;

    auxiliar = ponteiro->esquerda;
    ponteiro->esquerda = auxiliar->direita;
    auxiliar->direita = ponteiro;
    ponteiro->fb = 0;
    ponteiro = auxiliar;

    return ponteiro;
}

avl *rotacaoDuplaEsquerda(avl *ponteiro)
{
    avl *auxiliar1, *auxiliar2;

    auxiliar1 = ponteiro->direita;
    auxiliar2 = auxiliar1->esquerda;
    auxiliar1->esquerda = auxiliar2->direita;
    auxiliar2->direita = auxiliar1;
    ponteiro->direita = auxiliar2->esquerda;
    auxiliar2->esquerda = ponteiro;

    // recalcula o fb
    if (auxiliar2->fb == -1)
        ponteiro->fb = 1;
    else
        ponteiro->fb = 0;
    if (auxiliar2->fb == 1)
        auxiliar1->fb = -1;
    else
        auxiliar1->fb = 0;
    ponteiro = auxiliar2;

    return ponteiro;
}

avl *rotacaoDuplaDireita(avl *ponteiro)
{
    avl *auxiliar1, *auxiliar2;

    auxiliar1 = ponteiro->esquerda;
    auxiliar2 = auxiliar1->direita;
    auxiliar1->direita = auxiliar2->esquerda;
    auxiliar2->esquerda = auxiliar1;
    ponteiro->esquerda = auxiliar2->direita;
    auxiliar2->direita = ponteiro;

    // recalcula o fb
    if (auxiliar2->fb == 1)
        ponteiro->fb = -1;
    else
        ponteiro->fb = 0;
    if (auxiliar2->fb == -1)
        auxiliar1->fb = 1;
    else
        auxiliar1->fb = 0;
    ponteiro = auxiliar2;

    return ponteiro;
}
