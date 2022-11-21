#include "trem.h"
#include <QtCore>
#include <pthread.h>
#include <iostream>

#define NUMERO_TRILHOS 12

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

void movimentoTrem(int ID, int &x, int &y, int min_x, int min_y){
    int max_x = trilho_x + min_x;
    int max_y = trilho_y + min_y;

    if (y == min_y && x < max_x){ //trilho de cima

        x+=10;

        if(ID == 1){
            fecharTrilho(0, x, y, max_x-10, min_y);

            //tratamento deadlock
            fecharTrilho(7, x, y, max_x-30, min_y);
            fecharTrilho(9, x, y, max_x-30, min_y);
        } else if(ID == 2){
            liberarTrilho(0, x, y, min_x+30, min_y);
            fecharTrilho(1, x, y, max_x-10, min_y);

            //tratamento deadlock
            fecharTrilho(8, x, y, max_x-30, min_y);
            fecharTrilho(10, x, y, max_x-30, min_y);
        } else if(ID == 3){
            liberarTrilho(1, x, y, min_x+30, min_y);
        } else if(ID == 4){
            fecharTrilho(2, x, y, max_x-10, min_y);
            liberarTrilho(3, x, y, max_x-60, min_y);
            fecharTrilho(4, x, y, max_x-100, min_y);
        } else if(ID == 5){
            liberarTrilho(2, x, y, min_x+30, min_y);
            liberarTrilho(5, x, y, max_x-60, min_y);
            fecharTrilho(6, x, y, max_x-100, min_y);

            //tratamento deadlock
            liberarTrilho(9, x, y, min_x+30, min_y);
            liberarTrilho(10, x, y, max_x-60, min_y);
            liberarTrilho(11, x, y, min_x+30, min_y);
        }


    } else if (x == max_x && y < max_y){//trilho direito

        y+=10;

        if(ID == 1){
            fecharTrilho(3, x, y, max_x, max_y-10);
        } else if(ID == 2){
            fecharTrilho(5, x, y, max_x, max_y-10);
        } else if(ID == 4){
            liberarTrilho(4, x, y, max_x, min_y+30);

            //tratamento deadlock
            liberarTrilho(7, x, y, max_x, min_y+30);
        } else if(ID == 5){
            liberarTrilho(6, x, y, max_x, min_y+30);

            //tratamento deadlock
            liberarTrilho(8, x, y, max_x, min_y+30);
        }


    } else if (x > min_x && y == max_y){ //trilho de baixo

        x-=10;

        if(ID == 1){
            liberarTrilho(0, x, y, max_x-30, max_y);
            liberarTrilho(3, x, y, max_x-120, max_y);

            //tratamento deadlock
            liberarTrilho(7, x, y, max_x-30, max_y);
            liberarTrilho(9, x, y, max_x-120, max_y);
        } else if(ID == 2){
            fecharTrilho(0, x, y, min_x+10, max_y);
            liberarTrilho(1, x, y, max_x-30, max_y);
            fecharTrilho(4, x, y, max_x-80, max_y);
            liberarTrilho(5, x, y, max_x-120, max_y);

            //tratamento deadlock
            liberarTrilho(8, x, y, max_x-120, max_y);
            liberarTrilho(10, x, y, max_x-120, max_y);
        } else if(ID == 3){
            fecharTrilho(1, x, y, min_x+10, max_y);
            fecharTrilho(6, x, y, max_x-80, max_y);
        } else if(ID == 4){
            liberarTrilho(2, x, y, max_x-30, max_y);

            //tratamento deadlock
            liberarTrilho(11, x, y, max_x-30, max_y);
        } else if(ID == 5){
            fecharTrilho(2, x, y, min_x+10, max_y);

            //tratamento deadlock
            fecharTrilho(9, x, y, min_x+30, max_y);
            fecharTrilho(11, x, y, min_x+30, max_y);
        }


    } else{ //trilho esquerdo

        y-=10;

        if(ID == 2){
            liberarTrilho(4, x, y, min_x, max_y-30);
        } else if(ID == 3){
            liberarTrilho(6, x, y, min_x, max_y-30);
        } else if(ID == 4){
            fecharTrilho(3, x, y, min_x, min_y+10);

            //tratamento deadlock
            fecharTrilho(7, x, y, min_x, min_y+30);
            fecharTrilho(11, x, y, min_x, min_y+50);
        } else if(ID == 5){
            fecharTrilho(5, x, y, min_x, min_y+10);

            //tratamento deadlock
            fecharTrilho(8, x, y, min_x, min_y+30);
            fecharTrilho(10, x, y, min_x, min_y+10);
        }
    }
}

//Função a ser executada após executar trem->START
void Trem::run(){

    for(int i=0;i<NUMERO_TRILHOS;i++){
        pthread_mutex_init(&mutex[i], NULL);

    }

    while(true){

        int min_x = 0;
        int min_y = 0;

        switch(ID){
        case 1:     //Trem 1
            min_x = 60;
            min_y = 30;
            movimentoTrem(ID, x, y, min_x, min_y);
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 2: //Trem 2
            min_x = 240;
            min_y = 30;
            movimentoTrem(ID, x, y, min_x, min_y);
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 3: //Trem 3
            min_x = 420;
            min_y = 30;
            movimentoTrem(ID,x, y, min_x, min_y);
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 4: //Trem 4
            min_x = 150;
            min_y = 130;
            movimentoTrem(ID, x, y, min_x, min_y);
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 5: //Trem 5
            min_x = 330;
            min_y = 130;
            movimentoTrem(ID, x, y, min_x, min_y);
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
