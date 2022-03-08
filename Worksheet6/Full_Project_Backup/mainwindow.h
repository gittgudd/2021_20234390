#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void handleCubeButton();
    void handleTetraButton();
    void toolbarButton();
    
    /*
    void shrinkFilter(bool shrinkBool);
    void clipFilter(bool clipBool);
    void sliderIntensity();
    */

   // bool shrinkBool;
   // bool clipBool;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
