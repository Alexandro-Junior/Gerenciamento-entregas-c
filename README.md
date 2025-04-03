# Gerenciamento de Entregas

## Descrição
Este projeto implementa um sistema de gerenciamento de entregas utilizando filas encadeadas em C. Ele permite cadastrar pedidos, associá-los a entregadores, atualizar status das entregas e manter um histórico de pedidos concluídos.

## Funcionalidades
- Cadastro de entregas com ID único, produto, destinatário, CPF e status.
- Cadastro de entregadores e gerenciamento das suas entregas.
- Atualização do status da entrega.
- Transferência de pedidos para o histórico quando entregues.
- Exibição de entregadores e suas entregas.
- Exibição de histórico de entregas concluídas.

## Estruturas Utilizadas
### 1. `struct Entrega`
Representa um pedido de entrega, contendo:
- `IDpedido` - Identificador único.
- `produto` - Nome do produto.
- `destinatario` - Nome do destinatário.
- `cpf` - CPF do destinatário.
- `status` - Status atual da entrega.
- `proximo` - Ponteiro para a próxima entrega na fila.

### 2. `struct Fila`
Fila de entregas pendentes, contendo:
- `inicio` - Primeiro pedido na fila.
- `fim` - Último pedido na fila.
- `proximoID` - Contador para gerar IDs únicos.

### 3. `struct Historico`
Armazena as entregas concluídas.
- `inicio` - Primeiro pedido concluído.
- `fim` - Último pedido concluído.

### 4. `struct Entregador`
Representa um entregador, contendo:
- `nome` - Nome do entregador.
- `filaEntregas` - Fila de entregas atribuídas.
- `proximo` - Ponteiro para o próximo entregador.

### 5. `struct FilaEntregadores`
Fila de entregadores cadastrados.
- `inicio` - Primeiro entregador na fila.
- `fim` - Último entregador na fila.

## Funções Principais
- `criarFila()` - Cria e inicializa uma fila de entregas.
- `criarHistorico()` - Cria e inicializa um histórico de entregas.
- `inserirEntrega()` - Adiciona um pedido na fila de entregas.
- `exibirEntregas()` - Mostra as entregas pendentes.
- `atualizarStatusEntrega()` - Atualiza o status de um pedido.
- `exibirHistorico()` - Mostra as entregas concluídas.
- `criarEntregador()` - Cria um novo entregador.
- `criarFilaEntregadores()` - Cria a fila de entregadores.
- `inserirEntregaEntregador()` - Associa um pedido a um entregador.
- `exibirEntregadores()` - Lista os entregadores cadastrados.

## Como Executar
1. Compile o código com um compilador C, como `gcc`:
   ```sh
   gcc -o entregas entregas.c
   ```
2. Execute o programa:
   ```sh
   ./entregas
   ```
3. Utilize o menu interativo para cadastrar pedidos, entregadores e gerenciar as entregas.

## Possíveis Melhorias
- Persistência dos dados em arquivos.
- Interface gráfica ou API para acesso remoto.
- Melhor distribuição das entregas entre os entregadores.

## Autor
Este projeto foi desenvolvido para aprimorar conceitos de Estrutura de Dados em C.

