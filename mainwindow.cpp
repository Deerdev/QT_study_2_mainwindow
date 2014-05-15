#include "mainwindow.h"
//添加头文件
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QKeySequence>
#include <QToolBar>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //创建动作
    openAction = new QAction(tr("&Open"),this);         //创建open动作
    openAction->setShortcut(QKeySequence::Open);        //创建open动作的快捷键，QKeySquence定义了很多快捷键
    openAction->setStatusTip(tr("Open a file."));       //添加状态栏提示语句
    openAction->setIcon(QIcon(":/images/file.png"));    //用qrc中定义的图片，字符串以：开始，后面跟着prefix，设定动作的图标
                                                        //添加图标后，菜单栏和工具栏的QAction图标自动变化
    connect(openAction, SIGNAL(triggered()),
            this, SLOT(open()));                        //添加QAction的槽函数,QAction发出triggered()信号


    //添加QAction到菜单和工具条 //查看API文档看addMenu()函数，添加子菜单
    QMenu *file = menuBar()->addMenu(tr("&File"));      //menuBar()会返回菜单栏，已存在就返回该菜单栏的指针，添加一个菜单（类型QSstring）
    file->addAction(openAction);                        //用QMenu指针添加这个QAction
    QToolBar *toolBar = addToolBar(tr("&File"));        //利用addToolBar()的返回值添加一个工具条
    toolBar->addAction(openAction);                     //添加该工具条的QAction

}

void MainWindow::open()
{
    QMessageBox::information(NULL, tr("Open"), tr("Open a file"));
}

MainWindow::~MainWindow()
{

}
