#ifndef TINTERFACE_H
#define TINTERFACE_H

#include "matrix.h"

//Интерфейсные классы
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>

class TInterface : public QWidget
{
    Q_OBJECT

    //QLabels
    QLabel *matrixSizeTitle;
    QLabel *matrixTitle;
    QLabel *outputTitle;
    QLabel *outputValue;

    //QLinesEdit
    QLineEdit *matrixSizeField;

    //Таблица(визуализация матрицы)
    QTableWidget *matrixTable;
    QTableWidget *martixOutput;

    //QPushButtons
    QPushButton* transposeButton;
    QPushButton* determinantButton;
    QPushButton* rankButton;

public:
    TInterface(QWidget *parent = nullptr);
    ~TInterface();
public slots:
    //Callback при изменении размера матрицы
    void onMatrixSizeChanged(const QString&);
    //Callback при изменении содержимого матрицы
    void onMatrixChanged(int,int);
    //Callback при нажатии на кнопку "Транспонировать"
    void onTransposePressed();
    //Callback при нажатии на кнопку "Детерминант"
    void onDeterminantPressed();
    //Callback при нажатии на кнопку "Детерминант"
    void onRankPressed();
private:
    Matrix* matrix = new Matrix();

    number parseTableCell(QTableWidgetItem*);
};
#endif // TINTERFACE_H
