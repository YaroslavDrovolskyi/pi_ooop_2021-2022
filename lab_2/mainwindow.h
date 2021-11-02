#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QCloseEvent>

#include <QTreeWidget>

#include "Tasks.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:

    void close_app();

signals:

private slots:

    void on_exit_btn_clicked();

    void on_add_group_btn_clicked();

    void on_treeWidget_itemChanged(QTreeWidgetItem *item, int column);

    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

    void on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

    void on_add_task_btn_clicked();

    void on_del_group_btn_clicked();

    void on_del_task_btn_clicked();

private:
    Ui::MainWindow *ui;
//    MainButtons* main_buttons;
    TaskStructure* task_struct;

    void DisplayTaskStruct();

    void ReDisplayTaskStruct();

    void closeEvent(QCloseEvent* event);
};

/*
class MainButtons : public QWidget
{
    Q_OBJECT

public:
    MainButtons(MainWindow *parent = nullptr);
    ~MainButtons();

public slots:

signals:

private:
    QPushButton* exit_btn;
    QPushButton* prev_group_btn;
    QPushButton* next_group_btn;
};
*/
#endif // MAINWINDOW_H
