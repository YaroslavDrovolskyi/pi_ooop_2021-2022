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

class MainButtons;

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

    void on_treeWidget_itemActivated(QTreeWidgetItem *item, int column);

private:
    Ui::MainWindow *ui;
//    MainButtons* main_buttons;
    TaskStructure* task_struct;

    void DisplayTaskStruct();

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
