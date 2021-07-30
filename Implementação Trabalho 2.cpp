#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int numAcesso = 0;
int numAcertos = 0;
int numFaltas = 0;
int numLeituras = 0;
int numEscritas = 0;
int numAcertoLeitura = 0;
int numAcertoEscrita = 0;
int numFaltaLeitura = 0;
int numFaltaEscrita = 0;

struct celula
{
    int bloco;
    int rotulo[8];
    int endereco[11];
    int validar;
    char info;
};

struct memPrincipal
{
    struct celula CELULA[2048];
};

struct celula_ch
{
    int endereco[11];
    char info;
};

struct quadro
{
    int rotulo[8];
    struct celula_ch CELULA_CACHE[8];
    int validar;
};

struct conjunto
{
    struct quadro QUADRO[2];
};

struct memCache
{
    struct conjunto CACHE[16];
};

void retornaEndereco(int a, struct memPrincipal *A)
{

    int binario[11];
    int binarioCorreto[11];

    int i, j = 0, k, cont = 0;

    for (i = 0; i < 11; i++)
    {
        binario[i] = 0;
        binarioCorreto[i] = 0;
    }

    cont = a;

    i = 0;

    while (a > 0)
    {
        binario[i] = a % 2;
        i++;
        a = a / 2;
    }

    for (i = 10; i >= 0; i--)
    {
        (*A).CELULA[cont].endereco[j] = binario[i];
        j++;
    }
}

void setInfoMemPrincipal(struct memPrincipal *A)
{
    int a = 0;
    int b = 0;

    for (int cont2 = 0; cont2 < 2048;)
    {
        for (int cont = 0; cont < 8; cont++)
        {
            (*A).CELULA[cont2].bloco = a;
            (*A).CELULA[cont2].validar = 0;
            (*A).CELULA[cont2].info = (rand() % 26) + 97;
            cont2++;
        }

        a++;
    }
}

void retornaRotulo(int a, int b, struct memPrincipal *A)
{
    int binario[11];

    int i, j = 0, k, cont = 0;

    for (i = 0; i < 11; i++)
    {
        binario[i] = 0;
    }

    cont = a;

    i = 0;

    while (b > 0)
    {
        binario[i] = b % 2;
        i++;
        b = b / 2;
    }

    for (i = 7; i >= 0; i--)
    {
        (*A).CELULA[a].rotulo[j] = binario[i];
        j++;
    }
}

void iniciaMemCache(struct memCache *B)
{

    int i;

    for (int ia = 0; ia < 16; ia++)
    {

        for (int ib = 0; ib < 2; ib++)
        {
            for (int ic = 0; ic < 8; ic++)
            {
                (*B).CACHE[ia].QUADRO[ib].CELULA_CACHE[ic].info = '0';
                (*B).CACHE[ia].QUADRO[ib].validar = 0;
                (*B).CACHE[ia].QUADRO[ib].rotulo[0] = 9;
                (*B).CACHE[ia].QUADRO[ib].rotulo[1] = 9;
                (*B).CACHE[ia].QUADRO[ib].rotulo[2] = 9;
                (*B).CACHE[ia].QUADRO[ib].rotulo[3] = 9;
                (*B).CACHE[ia].QUADRO[ib].rotulo[4] = 9;
                (*B).CACHE[ia].QUADRO[ib].rotulo[5] = 9;
                (*B).CACHE[ia].QUADRO[ib].rotulo[6] = 9;
                (*B).CACHE[ia].QUADRO[ib].rotulo[7] = 9;

                for (int kc = 0; kc < 11; kc++)
                {
                    (*B).CACHE[ia].QUADRO[ib].CELULA_CACHE[ic].endereco[kc] = 9;
                }
            }
        }
    }
}

void testaValores(struct memPrincipal MP)
{
    for (int cont = 0; cont < 2048; cont++)
    {
        printf("validar = %d - ", MP.CELULA[cont].validar);

        printf("bloco = %d - ", MP.CELULA[cont].bloco);

        printf("binario = ");
        for (int jo = 0; jo < 11; jo++)
        {
            printf("%d", MP.CELULA[cont].endereco[jo]);
        }
        printf(" - ");
        printf("conteudo = %c\n", MP.CELULA[cont].info);
        fflush(stdin);
    }
}

void testaCache(struct memCache MC)
{
    for (int ia = 0; ia < 16; ia++)
    {
        for (int ib = 0; ib < 2; ib++)
        {
            if (ib == 0)
            {
                printf("QuadroA - ");
            }
            else
            {
                printf("QuadroB - ");
            }

            for (int rot = 0; rot < 8; rot++)
            {
                printf("%d", MC.CACHE[ia].QUADRO[ib].rotulo[rot]);
            }
            printf(" -");

            for (int ic = 0; ic < 8; ic++)
            {
                printf(" %c - ", MC.CACHE[ia].QUADRO[ib].CELULA_CACHE[ic].info);
                for (int kc = 0; kc < 11; kc++)
                {
                    printf("%d", MC.CACHE[ia].QUADRO[ib].CELULA_CACHE[ic].endereco[kc]);
                }
            }
            printf(" Cnjt %d", ia);
            printf("\n");
        }
        printf("\n");
    }
}

int lerMemoriaCache(struct memCache MC, char valor, struct celula_ch *CELULA_RETORNO)

{
    for (int ia = 0; ia < 16; ia++)
    {
        for (int ib = 0; ib < 2; ib++)
        {
            for (int ic = 0; ic < 8; ic++)
            {
                if (MC.CACHE[ia].QUADRO[ib].CELULA_CACHE[ic].info == valor)
                {
                    *CELULA_RETORNO = MC.CACHE[ia].QUADRO[ib].CELULA_CACHE[ic];
                    return 1;
                }
            }
        }
    }
    return 0;
}

int lerMemoriaPrincipal(struct memPrincipal MC, char valor, struct celula *CELULA_CORRETA)
{
    for (int jc = 0; jc < 2048; jc++)
    {
        if (MC.CELULA[jc].info == valor && MC.CELULA[jc].validar == 1)
        {
            (*CELULA_CORRETA).bloco = MC.CELULA[jc].bloco;
            (*CELULA_CORRETA).info = MC.CELULA[jc].info;
            (*CELULA_CORRETA).validar = MC.CELULA[jc].validar;
            for (int ic = 0; ic < 8; ic++)
            {
                (*CELULA_CORRETA).rotulo[ic] = MC.CELULA[jc].rotulo[ic];
            }
            for (int ic = 0; ic < 11; ic++)
            {
                (*CELULA_CORRETA).endereco[ic] = MC.CELULA[jc].endereco[ic];
            }
            break;
        }
    }
}

void insereCache(struct memPrincipal MP, struct memCache *MC, struct celula CELULA)
{
    int conjunto = CELULA.bloco % 16;
    int quadro = 0;
    int aa = 0;
    for (int i = 0; i < 2048; i++)
    {
        if (MP.CELULA[i].bloco == CELULA.bloco)
        {
            for (aa = 0; aa < 2; aa++)
            {
                if ((*MC).CACHE[conjunto].QUADRO[aa].validar == 0)
                {
                    for (int celula = 0; celula < 8; celula++)
                    {
                        for (int j = 0; j < 11; j++)
                        {
                            (*MC).CACHE[conjunto].QUADRO[aa].CELULA_CACHE[celula].endereco[j] = MP.CELULA[i].endereco[j];
                        }
                        (*MC).CACHE[conjunto].QUADRO[aa].CELULA_CACHE[celula].info = MP.CELULA[i].info;
                        i++;
                    }
                    (*MC).CACHE[conjunto].QUADRO[aa].validar = 1;
                    goto rotulo;
                }
                else if ((*MC).CACHE[conjunto].QUADRO[0].validar == 1 && (*MC).CACHE[conjunto].QUADRO[1].validar == 1)
                {
                    int ale;
                    ale = rand() % 2;
                    for (int celula = 0; celula < 8; celula++)
                    {

                        for (int j = 0; j < 11; j++)
                        {
                            (*MC).CACHE[conjunto].QUADRO[ale].CELULA_CACHE[celula].endereco[j] = MP.CELULA[i].endereco[j];
                        }
                        (*MC).CACHE[conjunto].QUADRO[ale].CELULA_CACHE[celula].info = MP.CELULA[i].info;
                        i++;
                    }
                    if (ale == 0)
                    {
                        (*MC).CACHE[conjunto].QUADRO[1].validar = 0;
                    }
                    else if (ale == 1)
                    {
                        (*MC).CACHE[conjunto].QUADRO[0].validar = 0;
                    }
                    goto rotulo;
                }
            }

        rotulo:
            for (int j = 0; j < 8; j++)
            {
                (*MC).CACHE[conjunto].QUADRO[aa].rotulo[j] = CELULA.rotulo[j];
            }
        }
    }
}

int binarioParaDecimal(int *n)
{
    int dec_value = 0;

    if (n[0] == 1)
    {
        dec_value = dec_value + 1024;
    }

    if (n[1] == 1)
    {
        dec_value = dec_value + 512;
    }

    if (n[2] == 1)
    {
        dec_value = dec_value + 256;
    }

    if (n[3] == 1)
    {
        dec_value = dec_value + 128;
    }

    if (n[4] == 1)
    {
        dec_value = dec_value + 64;
    }

    if (n[5] == 1)
    {
        dec_value = dec_value + 32;
    }

    if (n[6] == 1)
    {
        dec_value = dec_value + 16;
    }

    if (n[7] == 1)
    {
        dec_value = dec_value + 8;
    }

    if (n[8] == 1)
    {
        dec_value = dec_value + 4;
    }

    if (n[9] == 1)
    {
        dec_value = dec_value + 2;
    }

    if (n[10] == 1)
    {
        dec_value = dec_value + 1;
    }

    return dec_value;
}

int alteraInfoMemorias(struct memPrincipal *MP, struct memCache *MC, struct celula CELULA, int destino)
{
    (*MP).CELULA[destino].info = CELULA.info;
    (*MP).CELULA[destino].validar = 1;

    for (int a = 0; a < 2048; a++)
    {
        if ((*MP).CELULA[a].bloco == CELULA.bloco)
        {
            (*MP).CELULA[a].validar = 1;
        }
    }

    int cont = 0;

    int conjunto = CELULA.bloco % 16;

    for (int ib = 0; ib < 2; ib++)
    {
        for (int ic = 0; ic < 8; ic++)
        {
            for (int j = 0; j < 11; j++)
            {
                if ((*MC).CACHE[conjunto].QUADRO[ib].CELULA_CACHE[ic].endereco[j] == CELULA.endereco[j])
                {
                    cont++;
                    if (cont == 11)
                    {
                        (*MC).CACHE[conjunto].QUADRO[ib].validar = 1;
                        (*MC).CACHE[conjunto].QUADRO[ib].CELULA_CACHE[ic].info = CELULA.info;
                        return 0;
                    }
                }
            }
            cont = 0;
        }
    }
}

int lerMemoriaCachebyEnd(struct memCache *MC, int *end)
{
    int cont = 0;
    for (int ia = 0; ia < 16; ia++)
    {
        for (int ib = 0; ib < 2; ib++)
        {
            for (int ic = 0; ic < 8; ic++)
            {
                for (int j = 0; j < 11; j++)
                {
                    if ((*MC).CACHE[ia].QUADRO[ib].CELULA_CACHE[ic].endereco[j] == end[j])
                    {
                        cont++;
                        if (cont == 11)
                        {
                            return 1;
                        }
                    }
                }
                cont = 0;
            }
        }
    }
    return 0;
}

int main()
{
    struct memPrincipal MP;
    struct memCache MC;
    struct celula_ch CELULA_RETORNO;
    struct celula CELULA_CORRETA;
    int OP = 0;
    int endDestino[11];
    char valor;
    for (int cont = 0; cont < 2048; cont++)
    {
        retornaEndereco(cont, &MP);
    }

    for (int cont = 0; cont < 2048;)
    {
        for (int cont1 = 0; cont1 < 256; cont1++)
        {
            for (int cont2 = 0; cont2 < 8; cont2++)
            {
                retornaRotulo(cont, cont1, &MP);
                cont++;
            }
        }
    }

    setInfoMemPrincipal(&MP);
    iniciaMemCache(&MC);
    // testaCache(MC);
    // testaValores(MP);

    while (1)
    {
        system("cls");
        printf("Trabalho feito pela dupla: Gustavo Paris e Maiki Marolli Peruzzo.\n");
        printf("1 - Ler memoria\n");
        printf("2 - Escrever memoria\n");
        printf("3 - Estatisticas\n");
        printf("Entre com sua opcao: ");
        scanf("%d", &OP);
        if (OP == 1)
        {
            fflush(stdin);
            printf("Entre com o valor que deseja procurar: ");
            scanf("%c", &valor);
            fflush(stdin);
            if (lerMemoriaCache(MC, valor, &CELULA_RETORNO))
            {
                numLeituras++;
                numAcesso++;
                numAcertoLeitura++;
                printf("O valor foi encontrado na memoria cache.\n");
                printf("%c - ", CELULA_RETORNO.info);
                for (int hj = 0; hj < 11; hj++)
                {
                    printf("%d", CELULA_RETORNO.endereco[hj]);
                }
                printf("\n");
            }
            if (!lerMemoriaCache(MC, valor, &CELULA_RETORNO))
            {
                numAcesso++;
                numFaltaLeitura++;
                numLeituras++;
                printf("O valor %c nao foi encontrado na cache. Procurando na Memoria principal.\n", valor);
                lerMemoriaPrincipal(MP, valor, &CELULA_CORRETA);
                if (CELULA_CORRETA.validar == 0)
                {
                    printf("O valor foi encontrado na memoria principal, carregamos ele na cache.\n");
                    printf("Ele esta no bloco: %d - ", CELULA_CORRETA.bloco);
                    printf("Ele possui o rotulo: ");
                    for (int ic = 0; ic < 8; ic++)
                    {
                        printf("%d", CELULA_CORRETA.rotulo[ic]);
                    }
                    printf(" - ");
                    printf("Ele esta no endereco: ");
                    for (int ic = 0; ic < 11; ic++)
                    {
                        printf("%d", CELULA_CORRETA.endereco[ic]);
                    }
                    printf(" - ");
                    printf("Ele possui o caractere: %c", CELULA_CORRETA.info);
                    printf("\n");
                    insereCache(MP, &MC, CELULA_CORRETA);
                }
                else
                {
                    printf("Nao encontramos esse valor na memoria principal.\n");
                }
            }
        }

        if (OP == 2)
        {
            fflush(stdin);
            printf("Qual caractere voce deseja inserir?\n");
            scanf("%c", &valor);
            fflush(stdin);
            printf("Em qual endereço voce deseja inserir?(Insira um espaco entre cada bit. Ex: 0 1 0 1)\n");
            for (int ah = 0; ah < 11; ah++)
            {
                scanf("%d", &endDestino[ah]);
            }
            for (int ah = 0; ah < 11; ah++)
            {
                CELULA_CORRETA.endereco[ah] = endDestino[ah];
            }
            CELULA_CORRETA.info = valor;
            int cel = binarioParaDecimal(CELULA_CORRETA.endereco);
            CELULA_CORRETA.bloco = cel / 8;
            valor = MP.CELULA[cel].info;
            for (int rot1 = 0; rot1 < 8; rot1++)
            {
                CELULA_CORRETA.rotulo[rot1] = MP.CELULA[cel].rotulo[rot1];
            }

            if (lerMemoriaCachebyEnd(&MC, CELULA_CORRETA.endereco))
            {
                numAcesso++;
                numEscritas++;
                numAcertoEscrita++;
                printf("Ja estava na cache.\n");
                alteraInfoMemorias(&MP, &MC, CELULA_CORRETA, cel);
                printf("Alteramos o valor solicitado no endereço solicitado.\n");
            }
            else if (!lerMemoriaCachebyEnd(&MC, CELULA_CORRETA.endereco))
            {
                printf("Nao encontrou na cache\n");
                numFaltaEscrita++;
                numEscritas++;
                numAcesso++;
                insereCache(MP, &MC, CELULA_CORRETA);
                printf("Carregou o bloco que o endereço pertence na cache\n");
                alteraInfoMemorias(&MP, &MC, CELULA_CORRETA, cel);
                printf("Inseriu o valor solicitado no endereço solicitado.\n");
            }
        }

        if (OP == 3)
        {
            printf("Voce escolheu para ver as estatisticas, aqui estao: \n");
            printf("Numero de Acessos = %d\n", numAcesso);
            numAcertos = numAcertoEscrita + numAcertoLeitura;
            printf("Numero de Acertos = %d\n", numAcertos);
            numFaltas = numFaltaEscrita + numFaltaLeitura;
            printf("Numero de Faltas = %d\n", numFaltas);
            printf("Numero de Leituras = %d\n", numLeituras);
            printf("Numero de Escritas = %d\n", numEscritas);
            printf("Numero de Acertos de Leitura = %d\n", numAcertoLeitura);
            printf("Numero de Acertos de Escrita = %d\n", numAcertoEscrita);
            printf("Numero de Faltas na Leitura = %d\n", numFaltaLeitura);
            printf("Numero de Faltas na Escrita = %d\n", numFaltaEscrita);
        }
        if (OP == 4)
        {
            testaCache(MC);
        }
        if (OP == 5)
        {
            testaValores(MP);
        }
        system("pause");
    }
    return 0;
}