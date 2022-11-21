#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Cria o trem com seu (ID, posição X, posição Y)
    trem1 = new Trem(1,60,30);
    trem2 = new Trem(2,240,30);
    trem3 = new Trem(3,420,30);
    trem4 = new Trem(4,150,130);
    trem5 = new Trem(5,330,130);

    /*
     * Conecta o sinal UPDATEGUI à função UPDATEINTERFACE.
     * Ou seja, sempre que o sinal UPDATEGUI foi chamado, será executada a função UPDATEINTERFACE.
     * Os 3 parâmetros INT do sinal serão utilizados na função.
     * Trem1 e Trem2 são os objetos que podem chamar o sinal. Se um outro objeto chamar o
     * sinal UPDATEGUI, não haverá execução da função UPDATEINTERFACE
     */
    connect(trem1,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem2,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem3,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem4,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem5,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
}


//Função que será executada quando o sinal UPDATEGUI for emitido
void MainWindow::updateInterface(int id, int x, int y){
    switch(id){
    case 1: //Atualiza a posição do objeto da tela (quadrado) que representa o trem1
        ui->label_trem1->setGeometry(x,y,20,20);
        break;
    case 2: //Atualiza a posição do objeto da tela (quadrado) que representa o trem2
        ui->label_trem2->setGeometry(x,y,20,20);
        break;
    case 3: //Atualiza a posição do objeto da tela (quadrado) que representa o trem2
        ui->label_trem3->setGeometry(x,y,20,20);
        break;
    case 4: //Atualiza a posição do objeto da tela (quadrado) que representa o trem2
        ui->label_trem4->setGeometry(x,y,20,20);
        break;
    case 5: //Atualiza a posição do objeto da tela (quadrado) que representa o trem2
        ui->label_trem5->setGeometry(x,y,20,20);
        break;
    default:
        break;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * Ao clicar, trens começam execução
 */
void MainWindow::on_pushButton_clicked()
{
    trem1->start();
    trem2->start();
    trem3->start();
    trem4->start();
    trem5->start();
}

/*
 * Ao clicar, trens param execução
 */
void MainWindow::on_pushButton_2_clicked()
{
    trem1->terminate();
    trem2->terminate();
    trem3->terminate();
    trem4->terminate();
    trem5->terminate();
}

void MainWindow::on_velocidade_trem1_valueChanged(int value)
{
    trem1->setVelocidade(value);
}


void MainWindow::on_velocidade_trem2_valueChanged(int value)
{
    trem2->setVelocidade(value);
}


void MainWindow::on_velocidade_trem3_valueChanged(int value)
{
    trem3->setVelocidade(value);
}


void MainWindow::on_velocidade_trem4_valueChanged(int value)
{
    trem4->setVelocidade(value);
}


void MainWindow::on_velocidade_trem5_valueChanged(int value)
{
    trem5->setVelocidade(value);
}


void MainWindow::on_zerar_trem1_clicked()
{
    trem1->setVelocidade(0);
    ui->velocidade_trem1->setValue(0);
}


void MainWindow::on_zerar_trem2_clicked()
{
    trem2->setVelocidade(0);
    ui->velocidade_trem2->setValue(0);
}


void MainWindow::on_zerar_trem3_clicked()
{
    trem3->setVelocidade(0);
    ui->velocidade_trem3->setValue(0);
}


void MainWindow::on_zerar_trem4_clicked()
{
    trem4->setVelocidade(0);
    ui->velocidade_trem4->setValue(0);
}


void MainWindow::on_zerar_trem5_clicked()
{
    trem5->setVelocidade(0);
    ui->velocidade_trem5->setValue(0);
}

