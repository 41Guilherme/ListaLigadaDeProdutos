/*********************************************************************/
/**   ACH2023 - Algoritmos e Estruturas de Dados I                  **/
/**   EACH-USP - Segundo Semestre de 2021                           **/
/**   04 - Prof. Luciano Antonio Digiampietri                       **/
/**                                                                 **/
/**   EP 1 - Lista Ligada de Produtos                               **/
/**                                                                 **/
/**   Guilherme José da Silva Nascimento    NUSP 12543252           **/
/**                                                                 **/
/*********************************************************************/
#include "listadeprodutos.h"

PLISTA criarLista(){
  PLISTA res = (PLISTA) malloc(sizeof(LISTADEPRODUTOS));
  int x;
  for (x=0;x<NUMTIPOS;x++){
    res->LISTADELISTAS[x]=(PONT) malloc(sizeof(REGISTRO));
    res->LISTADELISTAS[x]->id=-1;
    res->LISTADELISTAS[x]->quantidade=0;
    res->LISTADELISTAS[x]->valorUnitario=0;
    res->LISTADELISTAS[x]->proxProd=NULL;
  }
  return res;
}


int tamanho(PLISTA l){
  int tam = 0;
  int x;
  PONT atual;
  for (x=0;x<NUMTIPOS;x++){
    atual = l->LISTADELISTAS[x]->proxProd;
    while (atual) {
      atual = atual->proxProd;
      tam++;
    }
  }
  return tam;
}

PONT buscarID(PLISTA l, int id){
  int x;
  PONT atual;
  for (x=0;x<NUMTIPOS;x++){
    atual = l->LISTADELISTAS[x]->proxProd;
    while (atual) {
      if (atual->id == id) return atual;
      atual = atual->proxProd;
    }
  }
  return NULL;
}

PONT buscarIDTipo(PLISTA l, int id, int tipo){
  if (tipo<0 || tipo>=NUMTIPOS) return NULL;
  PONT atual = l->LISTADELISTAS[tipo]->proxProd;
  while (atual) {
    if (atual->id == id) return atual;
    atual = atual->proxProd;
  }
  return NULL;
}

void exibirLog(PLISTA f){
  int numElementos = tamanho(f);
  printf("Log lista [elementos: %i]\n", numElementos);
  int x;
  PONT atual;
  for (x=0;x<NUMTIPOS;x++){
    printf("  #TIPO: %i -> ", x);
    atual = f->LISTADELISTAS[x]->proxProd;
    while (atual){
      printf(" [%i;%i;%i;$%i]", atual->id, atual->quantidade, atual->valorUnitario, atual->quantidade*atual->valorUnitario);
      atual = atual->proxProd;
    }
    printf("\n");
  }
  printf("\n");
}

int consultarValorUnitario(PLISTA l, int id){
  int x;
  PONT atual;
  for (x=0;x<NUMTIPOS;x++){
    atual = l->LISTADELISTAS[x]->proxProd;
    while (atual) {
      if (atual->id == id) return atual->valorUnitario;
      atual = atual->proxProd;
    }
  }
  return 0;
}

//Função auxiliar que devolve o tipo de Lista que se encontra um item 
int encontrarTipoPeloID(PLISTA l, int id){
  //PONT auxiliar
  PONT aux;
  for(int i = 0; i < NUMTIPOS; i++){ // Percorre todas as Listas de maneira semelhante ao exibirLog()

    aux = l->LISTADELISTAS[i]->proxProd;

    while(aux){

      // Caso encontre o id retorna o tipo da Lista (0 até 9)
      if(aux->id == id){ 
        return i;
      }
      //Caso não encontre parte para o próximo item
      aux = aux->proxProd;
    }

  }
  
}

// Função auxiliar para achar o item antecessor de outro item
PONT encontrarAntecessor(PLISTA l, int tipo, PONT item){

  //Criação de uma variavel auxiliar e da variável que receberáo antecessor
  PONT antecessor = l->LISTADELISTAS[tipo];
  PONT aux = l->LISTADELISTAS[tipo]->proxProd;
  
  // O aux sempre estará um item a frente do antecessor durante o loop
  while (aux){
    
    // Caso o item seja o aux retornará o antecessor
    if (item->id == aux->id){
      return antecessor;

    //Caso não, ambos percorrem item a frente
    }else{
      antecessor = aux; //antecessor vira o aux
      aux = aux->proxProd; //aux vira o seu proximo item
    }
  }

}

//Função de inserção de novos produtos
bool inserirNovoProduto(PLISTA l, int id, int tipo, int quantidade, int valor){
  // Verificação se os valores digitados são validos para a operação
  if (id < 0 || tipo < 0 || tipo >= 10 || quantidade <= 0 || valor <=0){
    return false;
  }
  // Busca pelo o Id 
  PONT a = (PONT) malloc(sizeof(REGISTRO));
  a = buscarID(l, id);

  // Verificação se o Id digitado já existe 
  if (a != NULL){
    return false;
  }

  // Continuação da Função após todas as validações

  // Criação do Novo Produto 
  PONT novoItem = (PONT) malloc(sizeof(REGISTRO));
  novoItem->id = id;
  novoItem->quantidade = quantidade;
  novoItem->valorUnitario = valor;
  novoItem->proxProd = NULL;
  
  // Variável auxiliar para ajudar na ordenação
  PONT aux = (PONT) malloc(sizeof(REGISTRO));

  // Começo da Lista do Tipo indicado
  PONT head = l->LISTADELISTAS[tipo];

  // Inserção caso a Lista do Tipo escolhido esteja "vazia", 
  // ou seja não há valores a serem comparados basta inserir 
  if (l->LISTADELISTAS[tipo]->proxProd == NULL){
    l->LISTADELISTAS[tipo]->proxProd = novoItem;
    return true;
  
  // Inserção buscando comparar os preços(quantidade x valor) para inserir de forma ordenada
  }else{

    // Variavel auxiliar que começa como item 1 da lista[tipo]
    aux = l->LISTADELISTAS[tipo]->proxProd;

    // Loop 'infinito' para Inserção 
    while(true){

      //Alocação do item para quando o auxiliar estiver vazio durante o loop
      if(aux == NULL){ 
        head->proxProd = novoItem;  // proxProd será null 
        novoItem->proxProd = NULL;  // pois o item ficará no fim da lista
        return true; //Quebra do Loop
      }

      int valorComparado = aux->valorUnitario * aux->quantidade; // valor de um item já dentro da lista
      int valorInserido = novoItem->valorUnitario * novoItem->quantidade; // valor do item a ser inserido na lista
      
      // Condicional para Inserção 
      if (valorComparado >= valorInserido){
        
        head->proxProd = novoItem; // Inserção do novo produto
        novoItem->proxProd = aux; // Realocação do antigo 
        return true; // quebra do loop
      
      }else{
        head = aux; // a "cabeça" vira o aux
        aux = aux->proxProd; // o aux vira o seu próximo e o loop continua 
        //a cabeça sempre será o anterior do nosso auxiliar
      }
    }
  }
}

// Função de remoção de itens do produto
bool removerItensDeUmProduto(PLISTA l, int id, int quantidade){

  // Alocando o item escolhido em "aux"
  PONT aux = (PONT) malloc(sizeof(REGISTRO));
  aux = buscarID(l , id);

  //Verificando se a operação pode ser executada
  if (aux == NULL || id < 0 || quantidade <= 0 || aux->quantidade < quantidade) {
    return false;
  }

  // Variáveis para se reinserir o produto com sua nova quantidade
  int valor = aux->valorUnitario;
  int tipo = encontrarTipoPeloID(l,id);
  int novaQuantidade = aux->quantidade - quantidade;
  
  //Exclusão do item mudando os ponteiros e liberando sua memória (A->B->C =  A->C)
  PONT antecessor = encontrarAntecessor(l,tipo, aux);
  antecessor->proxProd = aux->proxProd;
  aux = NULL;

  //Inserção do item chamando a função inserirNovoProduto()
  inserirNovoProduto(l,id,tipo,novaQuantidade,valor);
  return true;
  
}

//Função de atualização de valor de um produto
bool atualizarValorDoProduto(PLISTA l, int id, int valor){

  // Alocando o item escolhido em "aux"
  PONT aux = buscarID(l,id);

  // Verificando se a operação pode ser executada
  if (aux == NULL || id < 0 || valor <= 0) {
    return false;
  }

  // Variáveis para se reinserir o produto com seu novo valor
  int tipo = encontrarTipoPeloID(l,id);
  int quantidade = aux->quantidade; 
  
  //Exclusão do item mudando os ponteiros e liberando sua memória (A->B->C =  A->C)
  PONT antecessor = encontrarAntecessor(l,tipo, aux);
  antecessor->proxProd = aux->proxProd;
  aux = NULL;
  
  //Inserção do item chamando a função inserirNovoProduto()
  inserirNovoProduto(l,id,tipo,quantidade,valor);
  return true;
 
  
}


