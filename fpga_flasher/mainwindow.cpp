#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setWindowIcon(QIcon(":E:/Projects/qt_projects/fpga_flasher/fpga_flasher/img/icontexto-inside-feedburner_5101.ico"));

    ui->setupUi(this);

    m_process = new QProcess(this);
    connect(m_process, SIGNAL(readyReadStandardOutput()), this, SLOT(setStdout()));
    connect(m_process, SIGNAL(stateChanged(QProcess::ProcessState)), this, SLOT(printStatus()));

    tmr = new QTimer();
    tmr->setInterval(1000);
    connect(tmr, SIGNAL(timeout()), this, SLOT(updateTime()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_pickUtil_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, QString::fromUtf8("Открыть файл"), QDir::currentPath(), "*.exe;;All files (*.*)");
    ui->lineEdit_util->setText(fileName);
}

void MainWindow::on_btn_pickJam_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, QString::fromUtf8("Открыть файл"), QDir::currentPath(), "*.jam;;All files (*.*)");
    ui->lineEdit_jam->setText(fileName);
}

void MainWindow::on_btnClear_clicked()
{
    lblText = "Стираем";
    QString qstr(ui->lineEdit_util->displayText());
    qstr += " -aERASE " + ui->lineEdit_jam->displayText();
    m_process->start(qstr);
    tmr->start();
    tvar = 0;
}

void MainWindow::on_btnCheck_clicked()
{
    lblText = "Ищем нестертое";
    QString qstr(ui->lineEdit_util->displayText());
    qstr += " -aBLANK_CHECK " + ui->lineEdit_jam->displayText();
    m_process->start(qstr);
    tmr->start();
    tvar = 0;
}

void MainWindow::on_btnProgramm_clicked()
{
    lblText = "Прошиваем";
    QString qstr(ui->lineEdit_util->displayText());
    qstr += " -aPROGRAM " + ui->lineEdit_jam->displayText();
    m_process->start(qstr);
    tmr->start();
    tvar = 0;
}

void MainWindow::on_btnVerify_clicked()
{QTextCodec *codec = QTextCodec::codecForName("IBM 866");
    lblText = "Верифицируем";
    QString qstr(ui->lineEdit_util->displayText());
    qstr += " -aVERIFY " + ui->lineEdit_jam->displayText();
    m_process->start(qstr);
    tmr->start();
    tvar = 0;
}


void MainWindow::setStdout(){
    if(QSysInfo::productType()=="windows")
        {
            QTextCodec *codec = QTextCodec::codecForName("IBM 866");
            ui->textBrowser->append(codec->toUnicode(m_process->readAllStandardOutput()));
        }
        else
            ui->textBrowser->append( m_process->readAllStandardOutput());

}

void MainWindow::on_btnClearText_clicked()
{
    ui->textBrowser->clear();
}

void MainWindow::printStatus(){
    if(m_process->state() == QProcess::Running){
        ui->label_4->setText(lblText);
        ui->label_5->setText(QString("0 sec"));
    }
    else if(m_process->state() == QProcess::NotRunning){
        ui->label_4->setText("Стоим, ничего не делаем");
        m_process->close();
        tmr->stop();
        tvar = 0;
    }
}

void MainWindow::updateTime()
{
    tvar++;
    ui->label_5->setText(QString::number(tvar) + QString(" sec"));

}

