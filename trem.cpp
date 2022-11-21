#include "trem.h"
#include <QtCore>
#include <pthread.h>

int trilho_x = 180;
int trilho_y = 100;
pthread_mutex_t mutex[7];

//Construtor
Trem::Trem(int ID, int x, int y){
    this->ID = ID;
    this->x = x;
    this->y = y;
    velocidade = 100;
}

void movimentoTrem(int ID, int &x, int &y, int tela_x, int tela_y){
    int max_x = trilho_x + tela_x;
    int max_y = trilho_y + tela_y;

    if (y == tela_y && x < max_x){ //trilho de cima

        x+=10;

        if(ID == 1){
            if(x == max_x-10 && y == tela_y){
                pthread_mutex_lock(&mutex[0]);
            }
        }

        if(ID == 2){
            if(x == tela_x+30 && y == tela_y){
                pthread_mutex_unlock(&mutex[0]);
            }

            if(x == max_x-10 && y == tela_y){
                pthread_mutex_lock(&mutex[1]);
            }
        }

        if(ID == 3){
            if(x == tela_x+30 && y == tela_y){
                pthread_mutex_unlock(&mutex[1]);
            }
        }

        if(ID == 4){
            if(x == max_x-10 && y == tela_y){
                pthread_mutex_lock(&mutex[2]);
            }

            if(x == max_x-60 && y == tela_y){
                pthread_mutex_unlock(&mutex[3]);
            }

            if(x == max_x-100 && y == tela_y){
                pthread_mutex_lock(&mutex[4]);
            }
        }

        if(ID == 5){
            if(x == tela_x+30 && y == tela_y){
                pthread_mutex_unlock(&mutex[2]);
            }

            if(x == max_x-60 && y == tela_y){
                pthread_mutex_unlock(&mutex[5]);
            }

            if(x == max_x-100 && y == tela_y){
                pthread_mutex_lock(&mutex[6]);
            }
        }

    } else if (x == max_x && y < max_y){//trilho direito

        y+=10;


        if(ID == 1){
            if(x == max_x && y == max_y-10){
                pthread_mutex_lock(&mutex[3]);
            }
        }


        if(ID == 2){
            if(x == max_x && y == max_y-10){
                pthread_mutex_lock(&mutex[5]);
            }
        }

        if(ID == 4){
            if(x == max_x && y == tela_y+30){
                pthread_mutex_unlock(&mutex[4]);
            }
        }

        if(ID == 5){
            if(x == max_x && y == tela_y+30){
                pthread_mutex_unlock(&mutex[6]);
            }
        }


    } else if (x > tela_x && y == max_y){ //trilho de baixo

        x-=10;

        if(ID == 1){
            if(x == max_x-30 && y == max_y){
                pthread_mutex_unlock(&mutex[0]);
            }

            if(x == max_x-120 && y == max_y){
                pthread_mutex_unlock(&mutex[3]);
            }
        }

        if(ID == 2){
            if(x == tela_x+10 && y == max_y){
                pthread_mutex_lock(&mutex[0]);
            }

            if(x == max_x-30 && y == max_y){
                pthread_mutex_unlock(&mutex[1]);
            }

            if(x == max_x-80 && y == max_y){
                pthread_mutex_lock(&mutex[4]);
            }

            if(x == max_x-120 && y == max_y){
                pthread_mutex_unlock(&mutex[5]);
            }
        }

        if(ID == 3){
            if(x == tela_x+10 && y == max_y){
                pthread_mutex_lock(&mutex[1]);
            }

            if(x == max_x-80 && y == max_y){
                pthread_mutex_lock(&mutex[6]);
            }
        }

        if(ID == 4){
            if(x == max_x-30 && y == max_y){
                pthread_mutex_unlock(&mutex[2]);
            }
        }

        if(ID == 5){
            if(x == tela_x+10 && y == max_y){
                pthread_mutex_lock(&mutex[2]);
            }
        }


    } else{ //trilho esquerdo

        y-=10;

        if(ID == 2){
            if(x == tela_x && y == max_y-30){
                pthread_mutex_unlock(&mutex[4]);
            }
        }

        if(ID == 3){
            if(x == tela_x && y == max_y-30){
                pthread_mutex_unlock(&mutex[6]);
            }
        }

        if(ID == 4){
            if(x == tela_x && y == tela_y+10){
                pthread_mutex_lock(&mutex[3]);
            }
        }

        if(ID == 5){
            if(x == tela_x && y == tela_y+10){
                pthread_mutex_lock(&mutex[5]);
            }
        }

    }
}

//Função a ser executada após executar trem->START
void Trem::run(){

    for(int i=0;i<7;i++){
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
        if(velocidade == 0){
            while(velocidade == 0){
                msleep(1);
            }
        } else {
            msleep(201-velocidade);
        }
    }

    for(int i=0;i<7;i++){
        pthread_mutex_destroy(&mutex[i]);
    }
}




