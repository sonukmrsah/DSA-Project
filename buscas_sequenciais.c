#include "funcionario.h"
#include "buscas_sequenciais.h"
#include "time.h"

void bases_buscas_sequenciais(FILE *employeeFile, FILE *bookFile, FILE *logFile, int tamanho_base) {
    if ((employeeFile = fopen("./bin/funcionarios.dat", "ab+")) == NULL 
        || (bookFile = fopen("./bin/books.dat", "ab+")) == NULL
        || (logFile = fopen("./bin/log.dat", "ab+")) == NULL   ) {
        printf("Erro ao abrir os arquivo binarios\n");
        exit(1);
    }

    else{
          printf("\033[H\033[J");
        criarBase_funcionarios(employeeFile, tamanho_base);
        printf("Base de dados criada com sucesso!\n");

        int random_number = rand() % 10;
        printf("Numero aleatorio de vezes que iremos procurar funcionario aleatorios: %d\n", random_number); system("pause");
        
        clock_t start = clock();
        for (int i = 0; i < random_number; i++){
            buscarFuncionario_sequencialmente(employeeFile, i, logFile);
           
            }
        
        double cpu_time_used = ((double) (clock() - start)) / CLOCKS_PER_SEC;
        printf("\nTempo total: %.2f ms\n", cpu_time_used*1000);
            

}

}


TFunc *buscarFuncionario_sequencialmente(FILE *arquivo, int codigo, FILE *logFile) {
    TFunc *funcionario = (TFunc *)malloc(sizeof(TFunc));
    int numero_iteracoes = 0;
    clock_t start_time = clock();

    rewind(arquivo); 

    while (fread(&funcionario->cod, sizeof(int), 1, arquivo) == 1) {
        numero_iteracoes++;
        if (funcionario->cod == codigo) {
            clock_t end_time = clock();
            double time_elapsed_ms = ((double)(end_time - start_time) / CLOCKS_PER_SEC) * 1000.0;

            printf("\nCodigo: %i | Iteracoes: %d | Tempo de busca: %.2f ms\n", codigo, numero_iteracoes, time_elapsed_ms);
            salvar_log_file(logFile, numero_iteracoes, time_elapsed_ms);
            imprimir_funcionario(funcionario);
            
            return funcionario;
        } else {
            fseek(arquivo, sizeof(char) * sizeof(funcionario->nome)
                            + sizeof(char) * sizeof(funcionario->cpf)
                            + sizeof(char) * sizeof(funcionario->data_nascimento)
                            + sizeof(double), SEEK_CUR);
        }
    }

    clock_t end_time = clock();
    double time_elapsed_ms = ((double)(end_time - start_time) / CLOCKS_PER_SEC) * 1000.0;
    printf("\nFuncionario com o codigo %i nao encontrado | Iteracoes: %d | Tempo de busca: %.2f ms\n", codigo, numero_iteracoes, time_elapsed_ms);
    free(funcionario);
    return NULL;
}

void salvar_log_file(FILE *out, int iteracoes, double tempo_ms) {
    TLog *e = (TLog *)malloc(sizeof(TLog));
    e->iteracoes = iteracoes;
    e->tempo_ms = tempo_ms;
    fwrite(&e->iteracoes, sizeof(int), 1, out);
    fwrite(&e->tempo_ms, sizeof(int), 1, out);
  
    free(e);
}