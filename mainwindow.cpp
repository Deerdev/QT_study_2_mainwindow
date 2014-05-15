//关于tr()函数//
    /*函数tr()全名是QObject::tr()，被它处理的字符串可以使用工具提取出来翻译成其他语言，也就是做国际
      化使用。这以后还会仔细讲解，只要记住，Qt 的最佳实 践：如果你想让你的程序国际化的
      话，那么，所有用户可见的字符串都要使用 QObject::tr()！但是，为什么我们没有写
      QObject::tr()，而仅仅是 tr()呢？原来，tr()函数是定义在 Object 里面的，所有使用了
      Q_OBJECT 宏的类都自动具有tr()函数。
     *tr(“hello”) 等同于 “hello”,一个转换的过程
    */


#include "mainwindow.h"
//添加头文件
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QKeySequence>
#include <QToolBar>
#include <QMessageBox>
#include <QLabel>
#include <QStatusBar>
#include <QFileDialog>                  //用于文件打开和保存的标准对话框，

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    /**************************************************************************************************************************/
    //创建动作
    openAction = new QAction(tr("&Open"),this);         //创建open动作
    openAction->setShortcut(QKeySequence::Open);        //创建open动作的快捷键，QKeySquence定义了很多快捷键
    openAction->setStatusTip(tr("Open a file."));       //添加状态栏提示语句
    openAction->setIcon(QIcon(":/images/file.png"));    //用qrc中定义的图片，字符串以：开始，后面跟着prefix，设定动作的图标
                                                        //添加图标后，菜单栏和工具栏的QAction图标自动变化
    connect(openAction, SIGNAL(triggered()),
            this, SLOT(open()));                        //添加QAction的槽函数,QAction发出triggered()信号

    /**************************************************************************************************************************/
    //添加QAction到菜单和工具条
      /*******
      * 查看API文档看addMenu()函数，添加(更多的)子菜单
      *******/
    QMenu *file = menuBar()->addMenu(tr("&File"));      //menuBar()会返回菜单栏，已存在就返回该菜单栏的指针，添加一个菜单（类型QSstring）
    file->addAction(openAction);                        //用QMenu指针添加这个QAction
    QToolBar *toolBar = addToolBar(tr("&File"));        //利用addToolBar()的返回值添加一个工具条
    toolBar->addAction(openAction);                     //添加该工具条的QAction

    /**************************************************************************************************************************/
    //添加底部状态栏
      /*************
       *Qt 提供了一个QStatusBar类来实现状态栏
       *QMainWindow 类里面就有一个 statusBar()函数，用于实现状态栏的调用。类似menuBar()函数，如果不存在状态栏，该函数会自动创建一个，如果
        已经创建则会返回这个状态栏的指针。如果你要替换掉已经存在的状态栏，需要使用QMainWindow的setStatusBar()函数。
       *在 Qt 里面，状态栏显示的信息有三种类型：临时信息、一般信息和永久信息。其中，临时信息指临时显示的信息，比如 QAction 的提示等，
        也可以设置自己的临时信息，比如程序启动之后显示 Ready，一段时间后自动消失——这个功能可以使用 QStatusBar 的showMessage()函数来实现；
        一般信息可以用来显示页码之类的；永久信息是不会消失的信息，比如可以在状态栏提示用户Caps Lock键被按下之类。
       *QStatusBar继承自QWidget，因此它可以添加其他的 QWidget。
       *QStatusBar可以添加多个QWidget,因此，我们可以构建出很复杂的状态栏。
      *************/
    msgLabel = new QLabel;                              //创建QLabel标签对象（用于显示）
    msgLabel->setMinimumSize(msgLabel->sizeHint());     //设置其大小为其本身的建议大小，可以变化
    msgLabel->setAlignment(Qt::AlignHCenter);           //设置显示规则 是 水平居中HCenter
    statusBar()->addWidget(msgLabel);                   //将QLabel添加到状态栏
    statusBar()->setStyleSheet(QString("QStatusBar::item{border: 0px}"));   //把QStatusBar的子组件的border设置为0，
                                                                              //即不显示子组件的边框，透明化
    statusBar()->setSizeGripEnabled(1);                 //设置状态栏右下角的大小控制点，true：有  |  false：没有


}

void MainWindow::open()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image File(*.jpg *.png)"));    //获取打开的文件名(包括路径)
                                                                                                                //标题：Open Image  过滤器筛选jpg和png
    if(path.length() == 0)
    {
        QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
    }
    else
    {
        QMessageBox::information(NULL, tr("Path"), tr("You selected ") + path);
    }
}

MainWindow::~MainWindow()
{

}
