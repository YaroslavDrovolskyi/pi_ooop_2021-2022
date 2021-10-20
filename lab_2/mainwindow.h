#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

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

private:
    Ui::MainWindow *ui;
    MainButtons* main_buttons;
};


class MainButtons : public QWidget
{
    Q_OBJECT

public:
    MainButtons(QWidget *parent = nullptr);
    ~MainButtons();

public slots:


signals:

private:
    QPushButton* exit_btn;
    QPushButton* prev_group_btn;
    QPushButton* next_group_btn;
};
#endif // MAINWINDOW_H
