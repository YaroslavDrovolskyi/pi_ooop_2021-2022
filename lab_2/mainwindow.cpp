#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Tasks.h"

#include <QPushButton>
#include <QCloseEvent>
#include <string>
//#include <QTreeWidget>


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    this->setWindowTitle("Task manager");
    this->setWindowIcon(QIcon("path")); // NEED TO SET WINDOW ICON
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

void MainWindow::closeEvent(QCloseEvent* event){ // when we close via red cross
    this->close_app();
    event->accept();
}

void MainWindow::on_exit_btn_clicked(){
    this->close_app();
}

void MainWindow::DisplayTaskStruct(){
    ui->treeWidget->header()->setMinimumSectionSize(100);
    ui->treeWidget->header()->resizeSection(0, 200 /*width*/);
    ui->treeWidget->header()->resizeSection(1, 250 /*width*/);
    ui->treeWidget->header()->resizeSection(2, 200 /*width*/);
    ui->treeWidget->header()->resizeSection(3, 200 /*width*/);
//    ui->treeWidget->setRowHeight(0, 40);
//    ui->treeWidget->resizeColumnsToContents();


    for(std::size_t i = 0; i < this->task_struct->size(); i++){

        QTreeWidgetItem* root = new QTreeWidgetItem(ui->treeWidget);

        root->setText(0, QString::fromUtf8((*task_struct)[i].get_title().c_str(), (*task_struct)[i].get_title().size()));
        root->setFlags(root->flags() | Qt::ItemIsEditable);

        ui->treeWidget->addTopLevelItem(root);

        for(std::size_t j = 0; j < (*this->task_struct)[i].size(); j++){
            Task task = (*this->task_struct)[i][j];
            QTreeWidgetItem* child = new QTreeWidgetItem(root); // is root needed?????

            child->setText(0, QString::fromUtf8(task.get_title().c_str(), task.get_title().size()));
            child->setText(1, QString::fromUtf8(task.get_description().c_str(), task.get_description().size()));
            child->setText(2, QString::fromUtf8(task.get_executor().c_str(), task.get_executor().size()));
            child->setText(3, QString::number(task.get_status()));
            child->setText(4, QString::number(task.get_spent_hours()));

            child->setFlags(child->flags() | Qt::ItemIsEditable); /////////////////////// change row
            root->addChild(child);
        }
    }


}

void MainWindow::ReDisplayTaskStruct(){ // when display changes, we must call it every time we changes task structure
    this->ui->treeWidget->clear();
    DisplayTaskStruct();
}

void MainWindow::on_add_group_btn_clicked()
{
    this->task_struct->add_task_group("title"); // add in memory

    // add in widget
    QTreeWidgetItem* root = new QTreeWidgetItem(ui->treeWidget);

    root->setText(0, QString("title"));
    root->setFlags(root->flags() | Qt::ItemIsEditable);

    ui->treeWidget->addTopLevelItem(root);
}



void MainWindow::on_treeWidget_itemChanged(QTreeWidgetItem *item, int column){

    if (item == nullptr){
        return;
    }


    if (!item->parent()){ // if it is a top level item
        if (column == 0){
            int index = ui->treeWidget->indexOfTopLevelItem(item);
            assert(index > -1);

            (*this->task_struct)[index].set_title(item->text(column).toStdString());
        }
        else { // other columns in task groups must be inactive
            item->setText(column, QString(""));
        }

    }
    else{
        QTreeWidgetItem* parent = item->parent();
        assert(!parent->parent());

        int parent_index = ui->treeWidget->indexOfTopLevelItem(parent);
        assert(parent_index > -1);
        int child_index = parent->indexOfChild(item);
        assert(child_index > -1);

        if (column == 0){
            (*this->task_struct)[parent_index][child_index].set_title(item->text(column).toStdString());
        }
        else if (column == 1){
            (*this->task_struct)[parent_index][child_index].set_description(item->text(column).toStdString());
        }
        else if (column == 2){
            (*this->task_struct)[parent_index][child_index].set_executor(item->text(column).toStdString());
        }
        else if (column == 3){
            bool ok;
            int status = item->text(column).toInt(&ok);
            if (ok && status >=0 && status <= 100){
                (*this->task_struct)[parent_index][child_index].set_status(status);
            }
            else{
                item->setText(column, QString::number((*this->task_struct)[parent_index][child_index].get_status())); // write previous value (we store it in the task structure)
                // need to call other window, that warn about not correct format
            }
        }
        else if (column == 4){
            bool ok;
            int spent_hours = item->text(column).toInt(&ok);
            if (ok && spent_hours >=0){
                (*this->task_struct)[parent_index][child_index].set_spent_hours(spent_hours);
            }
            else{
                item->setText(column, QString::number((*this->task_struct)[parent_index][child_index].get_spent_hours())); // write previous value (we store it in the task structure)
                // need to call other window, that warn about not correct format
            }
        }
    }
}



void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column){

    ui->add_task_btn->setEnabled(true);

    if (!item->parent()){
        ui->del_group_btn->setEnabled(true);
        ui->del_task_btn->setEnabled(false);
    } else{
        ui->del_group_btn->setEnabled(false);
        ui->del_task_btn->setEnabled(true);
    }
}


void MainWindow::on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous){
    if (!previous){return;}

    if (current == nullptr){
        ui->del_group_btn->setEnabled(false);
        ui->add_task_btn->setEnabled(false);
        ui->del_task_btn->setEnabled(false);
    }
}


void MainWindow::on_add_task_btn_clicked(){
    QTreeWidgetItem* item = ui->treeWidget->currentItem();
    assert(item);
    if (item->parent()){ // if we clicked on the task and we want to add task in current group
        item = item->parent();
    }

    int group_index = ui->treeWidget->indexOfTopLevelItem(item);
    assert(group_index > -1);

    Task new_task = Task::get_default_task(group_index);
    this->task_struct->add_task(new_task);

    QTreeWidgetItem* child = new QTreeWidgetItem(item);

    child->setText(0, QString::fromStdString(new_task.get_title()));
    child->setText(1, QString::fromStdString(new_task.get_description()));
    child->setText(2, QString::fromStdString(new_task.get_executor()));
    child->setText(3, QString::number(new_task.get_status()));
    child->setText(4, QString::number(new_task.get_spent_hours()));

    child->setFlags(child->flags() | Qt::ItemIsEditable);
    item->addChild(child);
}


void MainWindow::on_del_group_btn_clicked()
{
    QTreeWidgetItem* item = ui->treeWidget->currentItem();
    assert(item && !item->parent());

    int index = ui->treeWidget->indexOfTopLevelItem(item);
    assert(index > -1);

    task_struct->remove_group(index); // delete from memory

    delete ui->treeWidget->takeTopLevelItem(index); // delete from widget

    ui->treeWidget->setCurrentItem(ui->treeWidget->topLevelItem(index));
}


void MainWindow::on_del_task_btn_clicked()
{
    QTreeWidgetItem* child = ui->treeWidget->currentItem();
    QTreeWidgetItem* parent = child->parent();
    assert(child && parent);



    int parent_index = ui->treeWidget->indexOfTopLevelItem(parent);
    assert(parent_index > -1);
    int child_index = parent->indexOfChild(child);
    assert(child_index > -1);

    task_struct->remove_task(parent_index, child_index); // delete from memory

    delete parent->takeChild(child_index); // delete from widget

    ui->treeWidget->setCurrentItem(parent->child(child_index)); // if we removed last task in the group, current item will be nullptr
}

