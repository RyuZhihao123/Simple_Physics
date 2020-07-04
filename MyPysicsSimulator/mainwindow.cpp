#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_glwidget = new GLWidget(ui->centralwidget);
    m_glwidget->resize(600,600);
}

MainWindow::~MainWindow()
{
    delete ui;
}

