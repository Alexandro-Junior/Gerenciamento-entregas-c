#include <ctype.h> // Para usar isalpha
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura para representar uma entrega
struct Entrega {
  int IDpedido;            // Identificador único do pedido
  char produto[50];        // Nome do produto
  char destinatario[50];   // Nome do destinatário
  char cpf[12];            // CPF do destinatário
  char status[20];         // Status da entrega
  struct Entrega *proximo; // Ponteiro para o próximo pedido na lista
};

// Definição da estrutura de fila para as entregas pendentes
struct Fila {
  struct Entrega *inicio; // Ponteiro para o primeiro pedido na fila
  struct Entrega *fim;    // Ponteiro para o último pedido na fila
  int proximoID;          // Próximo ID de pedido disponível
};

// Definição da estrutura de histórico para armazenar as entregas concluídas
struct Historico {
  struct Entrega *inicio; // Ponteiro para o primeiro pedido no histórico
  struct Entrega *fim;    // Ponteiro para o último pedido no histórico
};

// Definição da estrutura para representar um entregador
struct Entregador {
  char nome[50];              // Nome do entregador
  struct Fila *filaEntregas;  // Fila de entregas atribuídas ao entregador
  struct Entregador *proximo; // Ponteiro para o próximo entregador na lista
};

// Definição da estrutura de fila para os entregadores disponíveis
struct FilaEntregadores {
  struct Entregador *inicio; // Ponteiro para o primeiro entregador na fila
  struct Entregador *fim;    // Ponteiro para o último entregador na fila
};

// Função para criar uma fila de entregas
struct Fila *criarFila() {
  struct Fila *fila =
      (struct Fila *)malloc(sizeof(struct Fila)); // Aloca memória para a fila
  fila->inicio = NULL; // Inicializa o início da fila como nulo
  fila->fim = NULL;    // Inicializa o fim da fila como nulo
  fila->proximoID = 1; // Inicializa o próximo ID de pedido como 1
  return fila;
}

// Função para criar um histórico de entregas
struct Historico *criarHistorico() {
  struct Historico *historico = (struct Historico *)malloc(
      sizeof(struct Historico)); // Aloca memória para o histórico
  historico->inicio = NULL;      // Inicializa o início do histórico como nulo
  historico->fim = NULL;         // Inicializa o fim do histórico como nulo
  return historico;
}

// Função para inserir uma entrega na fila de entregas pendentes
void inserirEntrega(struct Fila *fila, const char *produto,
                    const char *destinatario, const char *cpf) {
  // Aloca memória para a nova entrega
  struct Entrega *novaEntrega =
      (struct Entrega *)malloc(sizeof(struct Entrega));
  // Define o ID do pedido como o próximo ID disponível na fila
  novaEntrega->IDpedido = fila->proximoID++;
  // Copia as informações da entrega para a estrutura
  strcpy(novaEntrega->produto, produto);
  strcpy(novaEntrega->destinatario, destinatario);
  strcpy(novaEntrega->cpf, cpf);
  strcpy(novaEntrega->status, "Pendente"); // Define o status como "Pendente"
  novaEntrega->proximo = NULL;             // Define o próximo como nulo

  // Verifica se a fila está vazia
  if (fila->fim == NULL) {
    fila->inicio = novaEntrega; // Se estiver vazia, o início e o fim apontam
                                // para a nova entrega
    fila->fim = novaEntrega;
  } else {
    fila->fim->proximo = novaEntrega; // Se não estiver vazia, adiciona a nova
                                      // entrega ao final da fila
    fila->fim = novaEntrega;
  }
}

// Função para exibir os entregadores com suas entregas
void exibirEntregadoresFila(struct Fila *fila) {
  // Verifica se a fila de entregas está vazia
  if (fila->inicio == NULL) {
    printf("A fila de entregas está vazia.\n");
    return;
  }

  printf("Entregadores fazendo as entregas:\n");
  struct Entrega *atual = fila->inicio;
  int contador = 0;

  // Exibe as informações dos pedidos
  while (atual != NULL && contador < 3) {
    printf("Entregador %d: Entrega %d (CPF: %s)\n", contador + 1,
           atual->IDpedido, atual->cpf);
    atual = atual->proximo;
    contador++;
  }
}

// Função para exibir as entregas pendentes na fila
void exibirEntregas(struct Fila *fila) {
  // Verifica se a fila de entregas está vazia
  if (fila->inicio == NULL) {
    printf("A fila de entregas está vazia.\n");
    return;
  }

  printf("Entrega na fila:\n");
  struct Entrega *atual = fila->inicio;

  // Exibe as informações dos pedidos
  printf("ID do Pedido: %d | Produto: %s | Destinatário: %s | CPF: %s | "
         "Status: %s\n",
         atual->IDpedido, atual->produto, atual->destinatario, atual->cpf,
         atual->status);
}

// Função para exibir o histórico de entregas concluídas
void exibirHistorico(struct Historico *historico) {
  // Verifica se o histórico de entregas está vazio
  if (historico->inicio == NULL) {
    printf("O histórico de entregas está vazio.\n");
    return;
  }

  printf("Histórico de entregas:\n");
  struct Entrega *atual = historico->inicio;

  // Exibe as informações dos pedidos
  while (atual != NULL) {
    printf("ID do Pedido: %d | Produto: %s | Destinatário: %s | CPF: %s | "
           "Status: %s\n",
           atual->IDpedido, atual->produto, atual->destinatario, atual->cpf,
           atual->status);
    atual = atual->proximo;
  }
}

// Função para atualizar o status de uma entrega
void atualizarStatusEntrega(struct Fila *fila, struct Historico *historico) {
  // Verifica se a fila de entregas está vazia
  if (fila->inicio == NULL) {
    printf("A fila de entregas está vazia.\n");
    return;
  }

  int idAtualizar;
  printf("Digite o ID do pedido que deseja atualizar o status: ");
  scanf("%d", &idAtualizar);

  // Procura pelo pedido com o ID fornecido
  struct Entrega *atual = fila->inicio;
  struct Entrega *anterior = NULL;
  while (atual != NULL) {
    if (atual->IDpedido == idAtualizar) {
      int novoStatus;
      printf("Pedido encontrado. Escolha o novo status:\n");
      printf("1. Pendente\n");
      printf("2. Separado\n");
      printf("3. Em rota\n");
      printf("4. Entregue\n");
      printf("Opção: ");
      scanf("%d", &novoStatus);

      // Atualiza o status de acordo com a opção escolhida
      switch (novoStatus) {
      case 1:
        strcpy(atual->status, "Pendente");
        printf("Status atualizado para Pendente.\n");
        break;
      case 2:
        strcpy(atual->status, "Separado");
        printf("Status atualizado para Separado.\n");
        break;
      case 3:
        strcpy(atual->status, "Em rota");
        printf("Status atualizado para Em rota.\n");
        break;
      case 4:
        strcpy(atual->status, "Entregue");
        printf(
            "Status atualizado para Entregue. Movendo para o histórico...\n");

        // Remove o pedido da fila de entregas
        if (anterior == NULL) {
          fila->inicio = atual->proximo;
        } else {
          anterior->proximo = atual->proximo;
        }

        if (atual == fila->fim) {
          fila->fim = anterior;
        }

        // Adiciona o pedido ao histórico
        if (historico->inicio == NULL) {
          historico->inicio = atual;
          historico->fim = atual;
          atual->proximo = NULL;
        } else {
          historico->fim->proximo = atual;
          historico->fim = atual;
          atual->proximo = NULL;
        }

        printf("Entrega movida para o histórico com sucesso.\n");
        break;
      default:
        printf("Opção inválida.\n");
      }

      return;
    }
    anterior = atual;
    atual = atual->proximo;
  }

  printf("Pedido com o ID %d não encontrado.\n", idAtualizar);
}

// Função para criar um novo entregador
struct Entregador *criarEntregador(const char *nome) {
  // Aloca memória para o entregador
  struct Entregador *entregador =
      (struct Entregador *)malloc(sizeof(struct Entregador));
  // Copia o nome do entregador para a estrutura
  strncpy(entregador->nome, nome, sizeof(entregador->nome));
  entregador->nome[sizeof(entregador->nome) - 1] = '\0';
  entregador->filaEntregas =
      criarFila();            // Inicializa a fila de entregas do entregador
  entregador->proximo = NULL; // Inicializa o próximo entregador como nulo
  return entregador;
}

// Função para criar uma fila de entregadores
struct FilaEntregadores *criarFilaEntregadores() {
  // Aloca memória para a fila de entregadores
  struct FilaEntregadores *filaEntregadores =
      (struct FilaEntregadores *)malloc(sizeof(struct FilaEntregadores));
  // Inicializa a fila de entregadores
  filaEntregadores->inicio = NULL;
  filaEntregadores->fim = NULL;
  return filaEntregadores;
}

// Função para inserir uma entrega na fila de um entregador e na fila geral de
// entregas
void inserirEntregaEntregador(struct Entregador *entregador,
                              struct Fila *filaEntregas, const char *produto,
                              const char *destinatario, const char *cpf) {
  inserirEntrega(entregador->filaEntregas, produto, destinatario,
                 cpf); // Insere na fila do entregador
  inserirEntrega(filaEntregas, produto, destinatario,
                 cpf); // Insere na fila geral de entregas também
}

// Função para exibir os entregadores e suas entregas
void exibirEntregadores(struct FilaEntregadores *filaEntregadores,
                        int mostrarEntregas) {
  // Verifica se não há entregadores cadastrados
  if (filaEntregadores->inicio == NULL) {
    printf("Nenhum entregador cadastrado.\n");
    return;
  }

  printf("Entregadores disponíveis:\n");
  int contador = 1;
  struct Entregador *atual = filaEntregadores->inicio;

  // Exibe os entregadores e, opcionalmente, suas entregas
  while (atual != NULL) {
    printf("%d. Entregador %s\n", contador, atual->nome);
    if (mostrarEntregas) {
      printf("   Entregas do entregador %s:\n", atual->nome);
      struct Entrega *entregaAtual = atual->filaEntregas->inicio;
      while (entregaAtual != NULL) {
        printf("   ID do Pedido: %d | Produto: %s | Destinatário: %s | CPF: %s "
               "| Status: %s\n",
               entregaAtual->IDpedido, entregaAtual->produto,
               entregaAtual->destinatario, entregaAtual->cpf,
               entregaAtual->status);
        entregaAtual = entregaAtual->proximo;
      }
    }
    atual = atual->proximo;
    contador++;
  }
}

int main() {
  struct FilaEntregadores *filaEntregadores =
      criarFilaEntregadores();             // Cria a fila de entregadores
  struct Fila *filaEntregas = criarFila(); // Cria a fila de entregas pendentes
  struct Historico *historicoEntregas =
      criarHistorico(); // Cria o histórico de entregas
  int opcao;
  char nomeEntregador[50], produto[50], destinatario[50], cpf[12];

  // Loop do menu principal
  do {
    printf("\nMenu Inicial:\n");
    printf("1. Cadastrar entregador\n");
    printf("2. Inserir entrega\n");
    printf("3. Mostrar entrega\n");
    printf("4. Atualizar status de entrega\n");
    printf("5. Mostrar histórico de entregas\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    switch (opcao) {
    case 1:
      printf("Digite o nome do entregador: ");
      getchar(); // Limpa o buffer de entrada
      fgets(nomeEntregador, sizeof(nomeEntregador), stdin);
      strtok(nomeEntregador, "\n"); // Remove a quebra de linha
      struct Entregador *entregador =
          criarEntregador(nomeEntregador); // Cria um novo entregador
      // Verifica se a fila de entregadores está vazia
      if (filaEntregadores->inicio == NULL) {
        filaEntregadores->inicio = entregador;
        filaEntregadores->fim = entregador;
      } else {
        filaEntregadores->fim->proximo = entregador;
        filaEntregadores->fim = entregador;
      }
      printf("Entregador cadastrado com sucesso.\n");
      break;
    case 2:
      printf("Digite o nome do produto: ");
      getchar(); // Limpa o buffer de entrada
      fgets(produto, sizeof(produto), stdin);
      strtok(produto, "\n"); // Remove a quebra de linha
      printf("Digite o nome do destinatário: ");
      fgets(destinatario, sizeof(destinatario), stdin);
      strtok(destinatario, "\n"); // Remove a quebra de linha
      printf("Digite o CPF do destinatário: ");
      fgets(cpf, sizeof(cpf), stdin);
      strtok(cpf, "\n"); // Remove a quebra de linha
      printf("Escolha o entregador:\n");
      exibirEntregadores(filaEntregadores, 0);
      int escolha;
      printf("Escolha: ");
      scanf("%d", &escolha);
      // Insere a entrega na fila do entregador escolhido e na fila geral de
      // entregas
      if (escolha >= 1) {
        struct Entregador *entregadorEscolhido = filaEntregadores->inicio;
        for (int i = 1; i < escolha; i++) {
          entregadorEscolhido = entregadorEscolhido->proximo;
        }
        inserirEntregaEntregador(entregadorEscolhido, filaEntregas, produto,
                                 destinatario, cpf);
        printf("Entrega inserida com sucesso.\n");
      } else {
        printf("Opção inválida.\n");
      }
      break;
    case 3:
      exibirEntregas(filaEntregas);
      break;
    case 4:
      atualizarStatusEntrega(filaEntregas, historicoEntregas);
      break;
    case 5:
      exibirHistorico(historicoEntregas);
      break;
    case 0:
      printf("Encerrando o programa...\n");
      break;
    default:
      printf("Opção inválida. Por favor, escolha novamente.\n");
    }

  } while (opcao != 0);

  // Libera a memória alocada para os entregadores
  while (filaEntregadores->inicio != NULL) {
    struct Entregador *temp = filaEntregadores->inicio;
    filaEntregadores->inicio = filaEntregadores->inicio->proximo;
    free(temp);
  }
  free(filaEntregadores);

  // Libera a memória alocada para as entregas pendentes
  while (filaEntregas->inicio != NULL) {
    struct Entrega *temp = filaEntregas->inicio;
    filaEntregas->inicio = filaEntregas->inicio->proximo;
    free(temp);
  }
  free(filaEntregas);

  // Libera a memória alocada para o histórico de entregas
  while (historicoEntregas->inicio != NULL) {
    struct Entrega *temp = historicoEntregas->inicio;
    historicoEntregas->inicio = historicoEntregas->inicio->proximo;
    free(temp);
  }
  free(historicoEntregas);

  return 0;
}
