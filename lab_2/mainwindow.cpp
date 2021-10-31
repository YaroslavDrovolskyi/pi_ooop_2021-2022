#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Tasks.h"

#include <QPushButton>
#include <QCloseEvent>
#include <string>
//#include <QTreeWidget>


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    const std::string filename_tasks = "tasks.txt";
    const std::string filename_groups = "groups.txt";

    this->task_struct = new TaskStructure;
    this->task_struct->read_from_file(filename_tasks, filename_groups);

    DisplayTaskStruct();
}


void MainWindow::close_app(){
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

void MainWindow::DisplayTaskStruct(){
//    this->ui->treeWidget->setColumnCount(5);
    /*
    for (TaskGroup& group : task_struct){

        QTreeWidgetItem* root = new QTreeWidgetItem(ui->treeWidget);
        root->setText(0, group.get_title());
        ui->treeWidget->addTopLevelItem(root);

        for(Task& task : group){
            QTreeWidgetItem* child = new QTreeWidgetItem();
            child->setText(task.get_title());
            root->addChild(child);
        }
    }
    */
    ui->treeWidget->header()->setMinimumSectionSize(100);
    ui->treeWidget->header()->resizeSection(1, 250 /*width*/);
//    ui->treeWidget->setRowHeight(0, 40);
//    ui->treeWidget->resizeColumnsToContents();
    for(std::size_t i = 0; i < 5; i++){

        std::string group_title = "title_";
        group_title += std::to_string(i);
        TaskGroup group (group_title);
        std::string some_str = "rghdkfklssdf ;lzdkdkdxdf mklkgklsdfdbgjkfdkfhdkghk dfhgkldjdkjfgk fhkdjfghkfjhgklbjf nkljhrktf";

        QTreeWidgetItem* root = new QTreeWidgetItem(ui->treeWidget);
        root->setText(0, QString::fromUtf8(group.get_title().c_str(), group.get_title().size()));

        ui->treeWidget->addTopLevelItem(root);
        for(std::size_t j = 0; j < 2; j++){

            std::string task_title = "title_";
            task_title += std::to_string(j);
            Task task;
            task.title_ = task_title;


            QTreeWidgetItem* child = new QTreeWidgetItem(root); // is root needed?????
            child->setText(0, QString::fromUtf8(task.get_title().c_str(), task.get_title().size()));
            child->setText(1, QString::fromUtf8(some_str.c_str(), some_str.size()));
            child->setFlags(child->flags() | Qt::ItemIsEditable); ///////////////////////
            root->addChild(child);
        }
    }
}


void MainWindow::on_treeWidget_itemActivated(QTreeWidgetItem *item, int column){

}

