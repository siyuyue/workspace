#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "heessystemscene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void selectionChangedInScene();
    
private slots:
    void on_addButton_clicked();

    void on_nameEdit_editingFinished();

    void on_derivedEdit_editingFinished();

    void on_deleteButton_clicked();

private:
    Ui::MainWindow *ui;
    HEESSystemScene *scene;
};

#endif // MAINWINDOW_H
