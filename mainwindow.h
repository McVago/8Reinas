#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <vector>
#include<bits/stdc++.h>
#define N 8
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void generateboard();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;
    QGraphicsPixmapItem* queen;
    std::vector<QGraphicsPixmapItem*> queens;
    std::vector<int> solutions;
    int solutionNumber;
};

#endif // MAINWINDOW_H
