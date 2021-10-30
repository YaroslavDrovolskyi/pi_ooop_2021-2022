#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Tasks.h"

#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    this->setFixedSize(1000, 500);
    QPushButton* exit_button = new QPushButton("Quit", this);
    exit_button->setGeometry(100, 100, 100, 50);

//    QPushButton* next_group_btn = new QPushButton("Quit", this);
//    next_group_btn->setGeometry(100, 100, 100, 50);
//    this->main_buttons = new MainButtons(this);
//    this->main_buttons->setGeometry(0, 0, 1000, 500);

    //this->ui->listView->se

    connect(exit_button, &QPushButton::clicked, this, &MainWindow::close_app); // object-signal-object-slot
}


void MainWindow::close_app(){
    emit QApplication::quit();
//    emit TaskStructure::write_in_file();
}




MainWindow::~MainWindow(){
    delete ui;
    delete this->main_buttons;
}


MainButtons::MainButtons(QWidget *parent)
    : QWidget(parent)
{
    this->exit_btn = new QPushButton("Quit", this);
    this->exit_btn->setGeometry(0, 100, 100, 50);
    this->exit_btn->show();

    this->prev_group_btn = new QPushButton("< prev", this);
    this->prev_group_btn->setGeometry(150, 100, 100, 50);

    this->next_group_btn = new QPushButton("next >", this);
    this->next_group_btn->setGeometry(300, 100, 100, 50);

    connect (this->exit_btn, &QPushButton::clicked, qApp, QApplication::quit);

//  connect(exit_button, &QPushButton::clicked, MainWindow, &MainWindow::close_app); // object-signal-object-slot
}

MainButtons::~MainButtons(){
    delete this->exit_btn;
    delete this->prev_group_btn;
    delete this->next_group_btn;
}

void MainWindow::on_pushButton_clicked()
{

}

