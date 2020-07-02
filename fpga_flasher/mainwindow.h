#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QTextCodec>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_pickUtil_clicked();

    void on_btn_pickJam_clicked();

    void on_btnClear_clicked();

    void on_btnCheck_clicked();

    void on_btnProgramm_clicked();

    void on_btnVerify_clicked();

    void setStdout();

    void printStatus();

    void on_btnClearText_clicked();

    void updateTime();

private:
    Ui::MainWindow *ui;
    QProcess *m_process;
    QTimer *tmr;
    QString lblText;
    int tvar;
};
#endif // MAINWINDOW_H
