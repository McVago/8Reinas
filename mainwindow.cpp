#include "mainwindow.h"
#include "ui_mainwindow.h"
using namespace std;

void printSolution(int board[N][N],vector<int> &posSols)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++){
            if (board[i][j] == 1)
            {
                posSols.push_back(i*8 + j);
            }
        }
    }
}
bool isSafe(int board[N][N], int row, int col)
{
    int i, j;
    for (i = 0; i < col; i++)
        if (board[row][i])
            return false;
    for (i=row, j=col; i>=0 && j>=0; i--, j--)
        if (board[i][j])
            return false;
    for (i=row, j=col; j>=0 && i<N; i++, j--)
        if (board[i][j])
            return false;

    return true;
}

bool solveNQUtil(int board[N][N], int col, vector<int> &posSols)
{
    if (col == N)
    {
        printSolution(board,posSols);
        return true;
    }
    bool res = false;
    for (int i = 0; i < N; i++)
    {
        if (isSafe(board, i, col) )
        {
            board[i][col] = 1;
            res = solveNQUtil(board, col + 1,posSols) || res;
            board[i][col] = 0;
        }
    }
    return res;
}
void solveNQ(vector<int> &posSols)
{
    int board[N][N];
    memset(board, 0, sizeof(board));

    if (solveNQUtil(board, 0,posSols) == false)
    {
        printf("Solution does not exist");
        return ;
    }

    return ;
}

void MainWindow::generateboard()
{
    QBrush blackBrush(Qt::black);
    QBrush whiteBrush(Qt::white);
    scene = new QGraphicsScene(this);
    solutionNumber = 0;
    bool color = 1;
    for (int i = 0; i<64; i++)
    {
        QGraphicsRectItem* rectangle;
        rectangle = new QGraphicsRectItem();
        rectangle->setRect((i%8)*52,(i/8)*50,52,52);

        if(color)
        {
            rectangle->setBrush(blackBrush);
            color = 0;
        }
        else
        {
            rectangle->setBrush(whiteBrush);
            color = 1;
        }
        if (i%8 == 7)
        {
            if (color)
                color = 0;
            else
                color = 1;
        }
        scene->addItem(rectangle);
    }
    ui->graphicsView->setScene(scene);
}
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    solveNQ(solutions);
    ui->setupUi(this);
    ui->spinBox->setMaximum(91);
    generateboard();
    this->setWindowTitle("8Reinitas");
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButton_clicked()
{
    scene->clear();
    generateboard();
    solutionNumber = ui->spinBox->value();
    QPixmap whiteimage("C:/Users/andho/Documents/8Queens/whitequeen.png");
    QPixmap whiteQueen = whiteimage.scaled(QSize(42,42));
    QPixmap blackimage("C:/Users/andho/Documents/8Queens/blackqueennew.png");
    QPixmap blackQueen = blackimage.scaled(QSize(42,42));
    bool color = 0;
    int solvingAux = solutionNumber*8;
    for (int i = 0; i<8; i++)
    {
        if (color)
        {
            queen = new QGraphicsPixmapItem();
            queen->setPixmap(whiteQueen);
            queen->setPos(QPointF(((solutions[solvingAux]%8)*52)+5,((solutions[solvingAux]/8)*50)+5));
            scene->addItem(queen);
            queens.push_back(queen);

        }
        else
        {
            queen = new QGraphicsPixmapItem();
            queen->setPixmap(blackQueen);
            queen->setPos(QPointF(((solutions[solvingAux]%8)*52)+5,((solutions[solvingAux]/8)*50)+5));
            scene->addItem(queen);
            queens.push_back(queen);
        }
        solvingAux++;
    }
    }

