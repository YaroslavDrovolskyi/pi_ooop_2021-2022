#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Tasks.h"

#include <QPushButton>
#include <QCloseEvent>
#include <string>
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    const std::string filename_tasks = "tasks.txt";
    const std::string filename_groups = "groups.txt";

    this->task_struct = new TaskStructure;
    this->task_struct->read_from_file(filename_tasks, filename_groups);
//    connect(exit_button, &QPushButton::clicked, this, &MainWindow::close_app); // object-signal-object-slot
}


void MainWindow::close_app(){
//    emit QApplication::quit();
    this->task_struct->write_in_file("tasks.txt","groups.txt");
    emit QApplication::quit();
}

MainWindow::~MainWindow(){
    delete ui;
//    delete this->main_buttons;
    delete this->task_struct;
}

/*
MainButtons::MainButtons(MainWindow *parent)
    : QWidget(parent)
{
    this->exit_btn = new QPushButton("Quit", this);
    this->exit_btn->setGeometry(0, 100, 100, 50);
    this->exit_btn->show();

    this->prev_group_btn = new QPushButton("< prev", this);
    this->prev_group_btn->setGeometry(150, 100, 100, 50);

    this->next_group_btn = new QPushButton("next >", this);
    this->next_group_btn->setGeometry(300, 100, 100, 50);

//    connect (this->exit_btn, &QPushButton::clicked, parent, parent->close_app());

}

MainButtons::~MainButtons(){
    delete this->exit_btn;
    delete this->prev_group_btn;
    delete this->next_group_btn;
}
*/

void MainWindow::closeEvent(QCloseEvent* event){ // when we close via red cross
    this->close_app();
    event->accept();
}

void MainWindow::on_exit_btn_clicked(){
    this->close_app();
}

