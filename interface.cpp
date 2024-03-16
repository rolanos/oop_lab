#include "interface.h"


TInterface::TInterface(QWidget *parent)
    : QWidget(parent)
{
    int width= 800;
    int height =480;
    setWindowTitle("Костенко_Иванова_Будило ПР_3");
    setFixedSize(width, height);

    matrixSizeTitle = new QLabel("Размер матрицы:", this);
    matrixSizeTitle->setGeometry(width * 0.05, height * 0.07, width * 0.15, width * 0.05);
    matrixSizeField = new QLineEdit(this);
    matrixSizeField->setGeometry(width * 0.2, height * 0.07, width * 0.05, width * 0.05);
    matrixSizeField->setValidator( new QIntValidator(0, 20, this));

    matrixTitle = new QLabel("Matrix elements:", this);
    matrixTitle->setGeometry(width * 0.05, width * 0.15, width * 0.1, width * 0.05);

    matrixTable = new QTableWidget(this);
    matrixTable->setGeometry(width * 0.05, height * 0.2, width * 0.5, height * 0.4);

    transposeButton = new QPushButton("Транспонировать", this);
    transposeButton->setGeometry(width * 0.6, height * 0.2, width * 0.2, height * 0.1);

    determinantButton = new QPushButton("Детерминант", this);
    determinantButton->setGeometry(width * 0.6, height * 0.35, width * 0.2, height * 0.1);

    rankButton = new QPushButton("Ранг", this);
    rankButton->setGeometry(width * 0.6, height * 0.5, width * 0.2, height * 0.1);

    outputTitle = new QLabel("Вывод:", this);
    outputTitle->setGeometry(width * 0.05, height * 0.6, width * 0.1, width * 0.05);

    outputValue = new QLabel("dasdsa",this);
    outputValue->setGeometry(width * 0.05, height * 0.65, width * 0.1, width * 0.05);
    outputValue->setVisible(false);

    martixOutput = new QTableWidget(this);
    martixOutput->setGeometry(width * 0.05, height * 0.7, width * 0.4, height * 0.2);
    martixOutput->setVisible(false);
    //SIGNALS
    connect(matrixTable, SIGNAL(cellChanged(int, int)), this, SLOT(onMatrixChanged(int, int)));
    connect(matrixSizeField, SIGNAL(textChanged(const QString &)), this, SLOT(onMatrixSizeChanged(const QString &)));
    connect(transposeButton, SIGNAL(pressed()), this, SLOT(onTransposePressed()));
    connect(determinantButton, SIGNAL(pressed()), this, SLOT(onDeterminantPressed()));
    connect(rankButton, SIGNAL(pressed()), this, SLOT(onRankPressed()));
}

TInterface::~TInterface() {
    delete matrixSizeTitle;
    delete matrixTitle;
    delete outputTitle;
    delete outputValue;
    delete matrixSizeField;
    delete matrixTable;
    delete martixOutput;
    delete transposeButton;
    delete determinantButton;
    delete rankButton;
}

//slots
void TInterface::onMatrixSizeChanged(const QString &size) {
    int n = size.toInt();
    matrix = new Matrix(n);
    //Устанавливаем новое количество строк
    matrixTable->setRowCount(n);
    //Устанавливаем новое количество строк
    matrixTable->setColumnCount(n);
}

void TInterface::onMatrixChanged(int row,int column) {
    int size = matrixSizeField->text().toInt();
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            QTableWidgetItem* tableItem = matrixTable->item(i, j);
            if(tableItem != nullptr){
                QStringList numbers = tableItem->text().split('/');

                number buffer;
                if(numbers.length() == 2) {
                    double n = numbers[0].toDouble();
                    double d = numbers[1].toDouble();
                    buffer = number(n, d);
                    matrix->inputValue(buffer,i, j);
                }

                if(numbers.length() == 1){
                    buffer = number(numbers[0].toDouble(), 1);
                    matrix->inputValue(buffer,i, j);
                }

            }
            else{
                matrix->inputValue(number(), i, j);
            }
        }
    }
}

void TInterface::onTransposePressed() {
    Matrix transposed = matrix->calculateTranspose();
    int size = transposed.getDimension();
    outputValue->setVisible(false);
    martixOutput->setVisible(true);
    martixOutput->setRowCount(size);
    martixOutput->setColumnCount(size);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            QTableWidgetItem *item = martixOutput->item(i, j);
            if(!item){
                item = new QTableWidgetItem();
                martixOutput->setItem(i, j, item);
            }
            number num = transposed(i, j);
            num.shorten();
            item->setText(QString::fromStdString(num.toString()));
        }
    }
}

void TInterface::onDeterminantPressed() {
    martixOutput->setVisible(false);
    outputValue->setVisible(true);
    number determinant = matrix->calculateDetermenant();
    determinant.shorten();
    outputValue->setText(QString::fromStdString(determinant.toString()));
}

void TInterface::onRankPressed() {
    martixOutput->setVisible(false);
    outputValue->setVisible(true);
    int rank = matrix->getRank();

    outputValue->setText(QString::fromStdString(std::to_string(rank)));
}

number TInterface::parseTableCell(QTableWidgetItem* tableItem) {
    if(tableItem != nullptr){
        QStringList numbers = tableItem->text().split('/');
        if(numbers.length() == 2)
            return number(numbers[0].toInt(), numbers[1].toInt());
        if(numbers.length() == 1)
            return number(numbers[0].toInt(), 1);
    }
    return number();
}
