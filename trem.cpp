#include "trem.h"
#include <QtCore>
#include <pthread.h>
#include <iostream>

#define NUMERO_TRILHOS 9

int trilho_x = 180; //comprimento do trilho x
int trilho_y = 100; //comprimento do trilho y

pthread_mutex_t mutex[NUMERO_TRILHOS];

//Construtor
Trem::Trem(int ID, int x, int y){
    this->ID = ID;
    this->x = x;
    this->y = y;
    velocidade = 100;
}

void fecharTrilho(int trilho, int &x, int &y, int x1, int y1){
    if(x == x1 && y == y1){
        pthread_mutex_lock(&mutex[trilho]);
    }
}

void liberarTrilho(int trilho, int &x, int &y, int x1, int y1){
    if(x == x1 && y == y1){
        pthread_mutex_unlock(&mutex[trilho]);
    }
}

void movimentoTrem(int ID, int &x, int &y, int tela_x, int tela_y){
    int max_x = trilho_x + tela_x;
    int max_y = trilho_y + tela_y;

    if (y == tela_y && x < max_x){ //trilho de cima

        x+=10;

        if(ID == 1){
            fecharTrilho(0, x, y, max_x-10, tela_y);
        } else if(ID == 2){
            liberarTrilho(0, x, y, tela_x+30, tela_y);
            fecharTrilho(1, x, y, max_x-10, tela_y);
        } else if(ID == 3){
            liberarTrilho(1, x, y, tela_x+30, tela_y);
        } else if(ID == 4){
            fecharTrilho(2, x, y, max_x-10, tela_y);
            liberarTrilho(3, x, y, max_x-60, tela_y);
            fecharTrilho(4, x, y, max_x-100, tela_y);
        } else if(ID == 5){
            liberarTrilho(2, x, y, tela_x+30, tela_y);
            liberarTrilho(5, x, y, max_x-60, tela_y);
            fecharTrilho(6, x, y, max_x-100, tela_y);
        }


    } else if (x == max_x && y < max_y){//trilho direito

        y+=10;

        if(ID == 1){
            fecharTrilho(3, x, y, max_x, max_y-10);
        } else if(ID == 2){
            fecharTrilho(5, x, y, max_x, max_y-10);
        } else if(ID == 4){
            liberarTrilho(4, x, y, max_x, tela_y+30);
        } else if(ID == 5){
            liberarTrilho(6, x, y, max_x, tela_y+30);
        }


    } else if (x > tela_x && y == max_y){ //trilho de baixo

        x-=10;

        if(ID == 1){
            liberarTrilho(0, x, y, max_x-30, max_y);
            liberarTrilho(3, x, y, max_x-120, max_y);
        } else if(ID == 2){
            fecharTrilho(0, x, y, tela_x+10, max_y);
            liberarTrilho(1, x, y, max_x-30, max_y);
            fecharTrilho(4, x, y, max_x-80, max_y);
            liberarTrilho(5, x, y, max_x-120, max_y);
        } else if(ID == 3){
            fecharTrilho(1, x, y, tela_x+10, max_y);
            fecharTrilho(6, x, y, max_x-80, max_y);
        } else if(ID == 4){
            liberarTrilho(2, x, y, max_x-30, max_y);
        } else if(ID == 5){
            fecharTrilho(2, x, y, tela_x+10, max_y);
        }


    } else{ //trilho esquerdo

        y-=10;

        if(ID == 2){
            liberarTrilho(4, x, y, tela_x, max_y-30);
        } else if(ID == 3){
            liberarTrilho(6, x, y, tela_x, max_y-30);
        } else if(ID == 4){
            fecharTrilho(3, x, y, tela_x, tela_y+10);
        } else if(ID == 5){
            fecharTrilho(5, x, y, tela_x, tela_y+10);
        }
    }
}

//Função a ser executada após executar trem->START
void Trem::run(){

    for(int i=0;i<NUMERO_TRILHOS;i++){
        pthread_mutex_init(&mutex[i], NULL);

    }

    while(true){

        int tela_x = 0;
        int tela_y = 0;

        switch(ID){
        case 1:     //Trem 1
            tela_x = 60;
            tela_y = 30;
            movimentoTrem(ID, x, y, tela_x, tela_y);
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 2: //Trem 2
            tela_x = 240;
            tela_y = 30;
            movimentoTrem(ID, x, y, tela_x, tela_y);
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 3: //Trem 3
            tela_x = 420;
            tela_y = 30;
            movimentoTrem(ID,x, y, tela_x, tela_y);
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 4: //Trem 4
            tela_x = 150;
            tela_y = 130;
            movimentoTrem(ID, x, y, tela_x, tela_y);
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 5: //Trem 5
            tela_x = 330;
            tela_y = 130;
            movimentoTrem(ID, x, y, tela_x, tela_y);
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        default:
            break;
        }

        int velocidadeTotal = 201;

        if(velocidade == 0){
            while(velocidade == 0){
                msleep(1);
            }
        } else {
            msleep(velocidadeTotal-velocidade);
        }
    }

    for(int i=0;i<NUMERO_TRILHOS;i++){
        pthread_mutex_destroy(&mutex[i]);
    }
}
