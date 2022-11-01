#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"

#define TAM 256

int main(){
    FILE *input, *output;
    No *arvore;
    Lista lista;
    int colunas;
    char **dicionario;
    char *codificado, *decodificado;

    unsigned char *texto;
    unsigned int tabela[TAM];
    int pos;

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

    arvore = criar_arvore(&lista);
    printf("\n\tArvore de huffman\n");
    imprimir_arvore(arvore, 0);
    colunas = altura_da_arvore(arvore)+1;
    dicionario = aloca_dicionario(colunas);
    criar_dicionario(dicionario, arvore, "", colunas);
    imprimir_dicionario(dicionario);

    codificado = codificacao(dicionario, texto);
    printf("\nTexto codificado: %s\n", codificado);
    escrever_no_arquivo(texto);

    free(codificado);
   //free(decodificado);
    libera_arvore(arvore);
    libera_dicionario(dicionario);
    libera_lista(&lista);
    fclose(input);
    //fclose(output);

    return(0);
}