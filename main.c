#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"

#define TAM 256

int main(){
    FILE *input, *output;
    No *arvore, *arvore_descompactacao;
    Lista lista, lista_descompactacao;
    int colunas;
    char **dicionario;
    char *codificado, *decodificado;

    unsigned char *texto;
    unsigned int tabela[TAM];
    int pos;
    int op;

    input = fopen("texto.txt","r");
            fseek(input, 0, SEEK_END);
            pos = ftell(input);
            texto = malloc(pos*sizeof(unsigned char));
            fseek(input, 0, SEEK_SET);
            fread(texto, 1, pos, input);
            
            iniciar_tabela_freq(tabela);
            preencher_tabela_freq(tabela, texto);
            imprimir_tabela_freq(tabela);

            inicializa_lista(&lista);
            preencher_lista(&lista, tabela);
            imprimir_lista(&lista);
            int tamanho_tabela;
            tamanho_tabela = (sizeof(tabela)/256)-1;

            arvore = criar_arvore(&lista);
            printf("\n\tArvore de huffman\n");
            imprimir_arvore(arvore, 0);
            colunas = altura_da_arvore(arvore)+1;
            dicionario = aloca_dicionario(colunas);
            criar_dicionario(dicionario, arvore, "", colunas);
            imprimir_dicionario(dicionario);

            codificado = codificacao(dicionario, texto);

    do{
        printf("\nDigite a opcao que deseja ");
        printf("\n 1 - Comprimir arquivo");
        printf("\n 2 - Descomprimir arquivo");
        printf("\n 3 - Sair\n");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            compactacao(codificado, tamanho_tabela, tabela); //compacta o arquivo e ja cria o cabeçalho
            break;
        case 2:
            descompactar(arvore_descompactacao);
            break;
        default:
            free(codificado);
            libera_arvore(arvore);
            libera_dicionario(dicionario);
            libera_lista(&lista);
            fclose(input);
            break;
        }
    }while(op != 3);

    
    return(0);
}