#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct arma{
    char nome[30];
    int forca;
    int peso;
}Arma;

typedef struct armadura{
    char nome[30];
    int defesa;
    int peso;
}Armadura;

typedef struct room{
    char descricao[100];
    Arma item1;
    Armadura item2;
    struct room* nextRoom;
}Room;

typedef struct inventarioArma{
    Arma arma;
    struct inventarioArma* nextSlot;
    struct inventarioArma* prevSlot;
}InventarioArma;

typedef struct inventarioArmadura{
    Armadura armadura;
    struct inventarioArmadura* nextSlot;   
    struct inventarioArmadura* prevSlot;   

}InventarioArmadura;

Arma criaArma(char *nome, int forca, int peso);
Arma* criaInventarioArma();
InventarioArma* pegarArma(InventarioArma *invArma, Room *sala);
int inventarioCheioArma(InventarioArma *invArma, Room *sala);
InventarioArma* despejaArma (InventarioArma *inv);
void printaInventarioArma(InventarioArma *invArma);
InventarioArma* particioneArma(InventarioArma *esq, InventarioArma *dir);
void _quicksortArma(InventarioArma *esq, InventarioArma *dir);
void quickSortArma(InventarioArma *inv);
void ordenaArmas(InventarioArma *invArma);

InventarioArmadura* particioneArmaduras(InventarioArmadura *esq, InventarioArmadura *dir);
void _quicksortArmadura(InventarioArmadura *esq, InventarioArmadura *dir);
void quickSortArmadura(InventarioArmadura *inv);
void ordenaArmaduras(InventarioArmadura *invArmadura);
InventarioArmadura* despejaArmadura (InventarioArmadura *inv);
void printaInventarioArmadura(InventarioArmadura *invArmadura);
int inventarioCheioArmadura(InventarioArmadura *invArmadura, Room *sala);
InventarioArmadura* pegarArmadura(InventarioArmadura *invArmadura, Room *sala);
Armadura* criarInventarioArmadura();

Room* criarSalas(void);
Room* insereSala(Room *room, char *description, Arma arma, Armadura armadura);
Room* iniciaSalas();

void liberaInvArma(InventarioArma *inv);
void liberaInvArmadura(InventarioArmadura *inv);
void liberaSalas(Room *sala);

void printaComandos();
void playGame();