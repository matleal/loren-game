#include "funcoes.h"

//Cria arma
Arma criaArma(char *nome, int forca, int peso){
    Arma arma;
    strcpy(arma.nome, nome);
    arma.forca = forca;
    arma.peso = peso;
    return arma;
}
//Cria o inventario de armas, retorna NULL para começar uma lista encadeada
Arma* criaInventarioArma(){
    return NULL;
}
//Adiciona arma ao inventario, se o inventario não estiver cheio
InventarioArma* pegarArma(InventarioArma *invArma, Room *sala){
    if(inventarioCheioArma(invArma, sala)){
        printf("Seu inventario esta cheio!!\n");
        return invArma;
    }
    else{
        InventarioArma *novoInv = (InventarioArma*)malloc(sizeof(InventarioArma));
        strcpy(novoInv->arma.nome, sala->item1.nome);
        novoInv->arma.forca = sala->item1.forca;
        novoInv->arma.peso = sala->item1.peso;
        novoInv->nextSlot =  invArma;
        novoInv->prevSlot = NULL;
        if(invArma != NULL)
            invArma->prevSlot = novoInv;
        return novoInv;
    }
    return 0;
}
//Retorna 1 se o inventario estiver cheio ou 0 se haver espaço
int inventarioCheioArma(InventarioArma *invArma, Room *sala){
    int limite = 30;
    int peso = 0;
    InventarioArma *aux;

    for(aux = invArma; aux != NULL; aux = aux->nextSlot){
        peso += invArma->arma.peso;
    }
    if(peso + sala->item1.peso > limite)
        return 1;
    else
        return 0;
}
//Joga fora a arma escolhida
InventarioArma* despejaArma (InventarioArma *inv){
    int i, j = 0;
    InventarioArma* v = inv;
    printf("Qual slot deseja despejar?\n");
    printaInventarioArma(inv);
    scanf("\n%d", &i);

    while ((v != NULL) && (j != i-1)) {
        v = v->nextSlot;
        j++;
    }
    if (v == NULL) {
        return inv;
    }
    if(v->prevSlot == NULL){
        if(v->nextSlot == NULL){
            inv = NULL;
            free(v);
        }
        else
            inv = v->nextSlot;
    }
    else if(v->nextSlot == NULL){
        v->prevSlot->nextSlot = NULL;
        free(v);
    }
    else{
        v->prevSlot->nextSlot = v->nextSlot;
        v->nextSlot->prevSlot = v->prevSlot;
        free(v);
    }
    return inv;
}
//função para imprimir o inventario de armas
void printaInventarioArma(InventarioArma *invArma){
   InventarioArma *aux;
   int i = 1;

    printf("\nINVENTARIO DE ARMAS:\n");

   for(aux = invArma; aux != NULL; aux = aux->nextSlot){
       printf("__________________________________________________________________\n");
       printf("|SLOT %d: %s (forca: %d peso: %d)|\n", i, aux->arma.nome, aux->arma.forca, aux->arma.peso);
       i++;
   }
}

//Ordena inventario de armas.
InventarioArma* particioneArma(InventarioArma *esq, InventarioArma *dir){
    InventarioArma *pivo = dir;

    InventarioArma *i = esq->prevSlot;

    for(InventarioArma *j = esq; j != dir; j = j->nextSlot){
        if(j->arma.forca >= pivo->arma.forca){
            if(i == NULL){
                i = esq;
            }
            else{
                i = i->nextSlot;
            }
            //Swap
            Arma aux = i->arma;
            i->arma = j->arma;
            j->arma = aux;
        }
    }

    if(i == NULL){
        i = esq;
    }
    else{
                i = i->nextSlot;
    }

    //Swap
    Arma aux = i->arma;
    i->arma = dir->arma;
    dir->arma = aux;

    return i;
}
void _quicksortArma(InventarioArma *esq, InventarioArma *dir){
    InventarioArma *pivo;

    if(dir != NULL && esq != dir && esq != dir->nextSlot){
        pivo = particioneArma(esq, dir);
        _quicksortArma(esq, pivo->prevSlot);
        _quicksortArma(pivo->nextSlot, dir);
    }
}
void quickSortArma(InventarioArma *inv){
     InventarioArma *aux = inv;

     //Acha o ultimo nó da lista
     while(aux->nextSlot != NULL)
        aux =  aux->nextSlot;

    InventarioArma *dir = aux;

    _quicksortArma(inv, dir);
}
void ordenaArmas(InventarioArma *invArma){
    quickSortArma(invArma);
}

//Ordena inventario de armaduras.
InventarioArmadura* particioneArmaduras(InventarioArmadura *esq, InventarioArmadura *dir){
    InventarioArmadura *pivo = dir;

    InventarioArmadura *i = esq->prevSlot;

    for(InventarioArmadura *j = esq; j != dir; j = j->nextSlot){
        if(j->armadura.defesa >= pivo->armadura.defesa){
            if(i == NULL){
                i = esq;
            }
            else{
                i = i->nextSlot;
            }
            //Swap
            Armadura aux = i->armadura;
            i->armadura = j->armadura;
            j->armadura = aux;
        }
    }

    if(i == NULL){
        i = esq;
    }
    else{
        i = i->nextSlot;
    }

    //Swap
    Armadura aux = i->armadura;
    i->armadura = dir->armadura;
    dir->armadura = aux;

    return i;
}
void _quicksortArmadura(InventarioArmadura *esq, InventarioArmadura *dir){
    InventarioArmadura *pivo;

    if(dir != NULL && esq != dir && esq != dir->nextSlot){
        pivo = particioneArmaduras(esq, dir);
        _quicksortArmadura(esq, pivo->prevSlot);
        _quicksortArmadura(pivo->nextSlot, dir);
    }
}
void quickSortArmadura(InventarioArmadura *inv){
     InventarioArmadura *aux = inv;

     //Acha o ultimo nó da lista
     while(aux->nextSlot != NULL)
        aux =  aux->nextSlot;

    InventarioArma *dir = aux;

    _quicksortArmadura(inv, dir);
}
void ordenaArmaduras(InventarioArmadura *invArmadura){
    quickSortArmadura(invArmadura);
}

//Joga fora itens do inventario, ou seja desaloca aquele espaço
InventarioArmadura* despejaArmadura (InventarioArmadura *inv){
    int i, j = 0;
    InventarioArmadura* v = inv;
    printf("Qual slot deseja despejar?\n");
    printaInventarioArmadura(inv);
    scanf("\n%d", &i);

    while ((v != NULL) && (j != i-1)) {
        v = v->nextSlot;
        j++;
    }
    if (v == NULL) {
        return inv;
    }
    if(v->prevSlot == NULL){
        if(v->nextSlot == NULL){
            inv = NULL;
            free(v);
        }
        else
            inv = v->nextSlot;
    }
    else if(v->nextSlot == NULL){
        v->prevSlot->nextSlot = NULL;
        free(v);
    }
    else{
        v->prevSlot->nextSlot = v->nextSlot;
        v->nextSlot->prevSlot = v->prevSlot;
        free(v);
    }
    return inv;
}
//Imprime inventario de armaduras
void printaInventarioArmadura(InventarioArmadura *invArmadura){
   InventarioArmadura *aux;
   int i = 1;

   printf("\nINVENTARIO DE ARMADURAS:\n");

   for(aux = invArmadura; aux != NULL; aux = aux->nextSlot){
       printf("__________________________________________________________________\n");
       printf("|SLOT %d: %s (defesa: %d peso: %d)|\n", i, aux->armadura.nome, aux->armadura.defesa, aux->armadura.peso);
       i++;
   }

   printf("\n");
}
////Retorna 1 se o inventario estiver cheio ou 0 se haver espaço
int inventarioCheioArmadura(InventarioArmadura *invArmadura, Room *sala){
    int limite = 30;
    int peso = 0;
    InventarioArmadura *aux;

    for(aux = invArmadura; aux != NULL; aux = aux->nextSlot){
        peso += invArmadura->armadura.peso;
    }
    if(peso + sala->item2.peso > limite)
        return 1;
    else
        return 0;
}
//Joga fora a arma escolhida.
InventarioArmadura* pegarArmadura(InventarioArmadura *invArmadura, Room *sala){
    if(inventarioCheioArmadura(invArmadura, sala)){
        printf("Seu inventario esta cheio!!\n");
        return invArmadura;
    }
    else{
        InventarioArmadura *novoInv = (InventarioArmadura*)malloc(sizeof(InventarioArmadura));
        strcpy(novoInv->armadura.nome, sala->item2.nome);
        novoInv->armadura.defesa = sala->item2.defesa;
        novoInv->armadura.peso = sala->item2.peso;
        novoInv->nextSlot =  invArmadura;
        novoInv->prevSlot = NULL;
        if(invArmadura != NULL)
            invArmadura->prevSlot = novoInv;
        return novoInv;
    }
    return 0;
}
//Cria o inventario de armadura, retorna NULL para começar uma lista encadeada
Armadura* criarInventarioArmadura(){
    return NULL;
}
//Cria o item armadura.
Armadura criaArmadura(char *nome, int defesa, int peso){
    Armadura armadura;
    strcpy(armadura.nome, nome);
    armadura.defesa = defesa;
    armadura.peso = peso;
    return armadura;
}

//Cria salas, retorna NULL para começar uma lista
Room* criarSalas(void){
    return NULL;
}
//Adiciona salas a lista de salas
Room* insereSala(Room *room, char *description, Arma arma, Armadura armadura){
    Room *newRoom =(Room*)malloc(sizeof(Room));
    strcpy(newRoom->descricao, description);
    newRoom->nextRoom = room;
    newRoom->item1 = arma;
    newRoom->item2 = armadura;
    return newRoom;
}
//Inicializa todas as salas do game
Room* iniciaSalas(){
    Room *salas = criarSalas();


    //sala 5
    Arma cajado = criaArma("Cajado de Yu Xia", 17, 8);
    Armadura perneira = criaArmadura("Perneiras da Sombra de Shura ", 12, 11);
    salas = insereSala(salas, "Arcadia Infernal", cajado, perneira);

    //sala 4
    Arma arco = criaArma("Executor Divino", 20, 12);
    Armadura bracelete = criaArmadura("Braceletes da Névoa Sombria ", 15, 12);
    salas = insereSala(salas, "Catacumbas do Profundo", arco, bracelete);

    //Sala 3
    Arma machado = criaArma("Machado Marca do Demonio", 14, 7);
    Armadura peitoral = criaArmadura("Armadura de Poshan", 12, 8);
    salas = insereSala(salas, "Catedral do Profundo", machado, peitoral);

    //Sala 2
    Arma espada = criaArma("Espada dos Mil Cortes", 22, 5);
    Armadura elmo = criaArmadura("Elmo do Nirvana", 8, 4);
    salas = insereSala(salas, "Cemiterio das Cinzas", espada, elmo);

    //Sala 1
    Arma adagas = criaArma("Adagas do Destino Condenado", 8, 3);
    Armadura bota = criaArmadura("Botas de Asura", 9, 2);
    salas = insereSala(salas, "Portao Desalmado", adagas, bota);

    return salas;
}

//Funções para desalocar o inventario de armas.
void liberaInvArma(InventarioArma *inv){
    while(inv != NULL){
        InventarioArma *aux = inv->nextSlot;
        free(inv);
        inv = aux;
    }
}
//função para desalocar o inventario de armaduras.
void liberaInvArmadura(InventarioArmadura *inv){
    while(inv != NULL){
        InventarioArmadura *aux = inv->nextSlot;
        free(inv);
        inv = aux;
    }
}
//função para desalocar as salas.
void liberaSalas(Room *sala){
    while(sala != NULL){
        InventarioArma *aux = sala->nextRoom;
        free(sala);
        sala = aux;
    }
}

//Printa todos os comandos disponiveis no jogo.
void printaComandos(){

    printf("\n____________________________________________________________\n");
    printf("|Digite 1 para - IR PARA PROXIMA SALA                        |\n");
    printf("|Digite 2 para - SAIR                                        |\n");
    printf("|Digite 3 para - MOSTRAR INVENTARIO                          |\n");
    printf("|Digite 4 para - JOGAR UMA ARMA FORA                         |\n");
    printf("|Digite 5 para - JOGAR UMA ARMADURA FORA                     |\n");
    printf("|Digite 6 para - ORDENAR INVETARIO(ORDENADO POR FORCA/DEFESA)|\n");
    printf("|Digite 7 para - REPETIR COMANDOS                            |");
    printf("\n___________________________________________________________|\n");

}
//Chama a função para inicializar salas, inventario,itens e também recebe input do jogador.
void playGame(){

    Room *salas = iniciaSalas(); // Inicializa as salas
    InventarioArma *inventarioArma = criaInventarioArma();// Inicializa inventario de armas
    InventarioArmadura *inventarioArmadura = criarInventarioArmadura();// Inicializa inventario de armaduras

    int input = 0; // Entrada do usuario.
    int pegar = 0;
    int cont = 0;

    printf("\nVoce esta no inicio!\n");


    while(input != 2){
        printf("Digite o seu comando: ");
        scanf("%d", &input);

        if(input > 7 || input < 0){
            printf("Digite um comando correto: ");
            scanf("%d", &input);
        }

        switch(input){
            case(1):
                    printf("\n___________________________________________________________\n");
                    printf("|Voce esta em: %s|", salas->descricao);
                    printf("\n___________________________________________________________\n");
                    printf("Esses sao os itens desta sala:\n");

                    printf("\nItem 1: %s", salas->item1.nome);
                    printf("\nForca: %d \nPeso: %d", salas->item1.forca, salas->item1.peso);

                    printf("\n___________________________________________________________");

                    printf("\nItem 2: %s", salas->item2.nome);
                    printf("\nForca: %d \nPeso: %d", salas->item2.defesa, salas->item2.peso);

                    printf("\n___________________________________________________________");

                    printf("\nDeseja pegar o item: %s ?\nDigite 1 para sim e 2 para nao: ", salas->item1.nome);
                    scanf("%d", &pegar);

                    while(pegar < 1 || pegar > 2){
                        printf("\nInsira um numero correto!\n");
                        scanf("%d", &pegar);
                    }
                    if(pegar == 1){
                        inventarioArma = pegarArma(inventarioArma, salas);
                    }

                    printf("\nDeseja pegar o item: %s ?\nDigite 1 para sim e 2 para nao", salas->item2.nome);
                    scanf("%d", &pegar);
                    while(pegar < 1 || pegar > 2){
                        printf("\nInsira um numero correto!\n");
                        scanf("%d", &pegar);
                    }
                    if(pegar == 1){
                       inventarioArmadura = pegarArmadura(inventarioArmadura, salas);
                    }

                    if(cont == 4){
                        printf("\n___________________________________________________________");
                        printf("\nVoce chegou ao final, Parabens!\n");
                        printf("___________________________________________________________");
                        printf("\nEste eh seu inventario:\n");
                        printaInventarioArma(inventarioArma);
                        printaInventarioArmadura(inventarioArmadura);
                        break;
                    }

                    salas = salas->nextRoom;
                    cont++;
                    break;

            case(2):
                printf("");
                break;
            case(3):
                printaInventarioArma(inventarioArma);
                printaInventarioArmadura(inventarioArmadura);
                break;
            case(4):
                inventarioArma = despejaArma(inventarioArma);
                break;
            case(5):
                inventarioArmadura = despejaArmadura(inventarioArmadura);
                break;
            case(6):
                ordenaArmas(inventarioArma);
                ordenaArmaduras(inventarioArmadura);
                break;
            case(7):
                printaComandos();
                break;
            default:
                printf("Digite um comando correto: \n");
                break;
        }
    }
            liberaSalas(salas);
            liberaInvArma(inventarioArma);
            liberaInvArma(inventarioArmadura);
            exit(0);
}
