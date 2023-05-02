# Concurrent Programming using C

## Tasks

O recurso de tasks, ou tarefas, é uma recurso elegante e eficiente de parelismo não estruturado, mantendo o parelelismo incremental e uma consistencia sequencial, utilizando o OpenMP.

## Definição

Task é uma instância específica de código executável e seu ambiente de dados

Pode-se dizer que OpenMP já possuía tasks de maneira implicita. Cada parte de um programa OpenMP já faz parte de uma ou outra tarefa. O mecanismo de tasks apenas introduz a possibilidade de criar tasks explicitamente. Por exemplo a diretiva `parallel` cria uma thread executando implicitamente uma task na região paralela.

Com a definição explícita de tasks, uma task pode ser executada por diferentes threads, se o programador assim o especificar.

Uma task explícita pode ser executada por qualquer thread em paralelo com outras tarefas, e a execução pode ser imediata ou adiada até um momento posterior

Uma vez que uma thread inicia sua execução, ela é vinculada a uma task ao qual irá executar a região da tarefa do começo ao fim.

Isso não significa que sua execução seja continua, podendo ser suspensa e retomada.

A também a possibilidade de uso de tarefas desvinculadas, a qual não apresenta o comportamento anterior.

## Diferenças entre Sections e Tasks

Enquanto as Sections são estáticas, dependentes entre si e apresentam uma quantidade maior de trabalho que é atribuída a cada thread, enquanto as taks são dinâmicas, indepedentes entre si e apresentam uma quantidade menor de trabalho que é atribuída a cada thread. Além disso as tasks podem ser usadas em regiões paralelas e não paralelas enquanto as sections só podem ser usadas em regiões paralelas.

## Quando Utilizar tasks no OpenMP

As tasks do OpenMP são utlizizadas em situações em que o trabalho a ser realizado é dividido em várias partes independentes que podem ser executadas em paralelo. Em geral, as tasks são recomendadas quando:

1. Há muitas tarefas pequenas e independentes que podem ser executadas em paralelo, em vez de um único loop grande.

1. O trabalho é dinâmico e não é possível prever qual tarefa será executada em cada momento.

1. As tarefas têm diferentes tempos de execução e precisam ser equilibradas entre as threads disponíveis.

1. É necessário especificar dependências entre tarefas para evitar condições de corrida e garantir que as tarefas sejam executadas na ordem correta.

### Exemplos de utilização

Alguns exemplos de aplicação de tasks do OpenMP incluem processamento de imagens, simulações físicas, processamento de sinais digitais, computação financeira, dentre outras aplicações que podem se beneficiar da execução paralela de tarefas independentes.

## Utilização de tasks com OpenMP

A utilização das tasks com OpenMp segue com o uso das diretivas `#pragma omp` em uma região a ser paralelizada. por exemplo:

A diretiva `task` especifica uma uma task explicita

A diretiva `taskwait` faz com que a execução da task corrente seja suspensa até que todas as suas tasks filhas sejam completadas.

A diretica `taskloop` especifica que uma ou mais iterações associadas em loop serão executadas em paralelo pela task

As tarefas também podem ser atribuídas a um grupo de tarefas usando a diretiva `taskgroup`, que especifica que todas as tarefas criadas dentro do grupo devem ser concluídas antes que o programa continue.

### Exemplo de código

No codigo abaixo é explicitado duas tarefas, cada uma delas será executada por uma thread diferente em paralelo. No final o programa imprime qual thread executal qual tarefa.

```C
#include <stdio.h>
#include <omp.h>

int main() {
    #pragma omp parallel
    {
        #pragma omp single
        {
            #pragma omp task
            {
                printf("Task 1 executed by thread %d\n", omp_get_thread_num());
            }

            #pragma omp task
            {
                printf("Task 2 executed by thread %d\n", omp_get_thread_num());
            }
        }
    }

    return 0;
}

```
