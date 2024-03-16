#ifndef TRATIONAL_H
#define TRATIONAL_H

#include<iostream>

using namespace std;

class TRational
{
    //Числитель
    int numerator;
    //Знаменатель
    unsigned int denominator;

public:
    TRational();
    TRational(double, double);

    //Приведение к double виду
    double toDouble();
    //Приведение к string виду
    string toString();
    //Сокращение дроби
    void shorten();
    //Конвертация из double в this
    static TRational toRationalFromDouble(double, int);

    TRational operator* (TRational);
    TRational operator* (double);
    TRational operator* (int);
    TRational operator/ (TRational);
    TRational operator/ (double);
    TRational operator+ (TRational);
    TRational operator+ (double);
    TRational operator- (TRational);
    TRational operator- (double);


    bool operator == (const TRational&);
    bool operator == (const double&);
    bool operator == (const int&);

    operator bool() const;
    operator double() const;

    friend double abs(TRational);
    friend ostream& operator<<(ostream&, TRational&);

private:
    //нахождение НОД
    int getGreatestDivisior(int, int);
    //нахождение НОК
    int getLeastMultiple(int, int);
    //Перевернуть дробь
    void flipOver();
};

#endif
