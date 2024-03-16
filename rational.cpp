#include "rational.h"
#include <cmath>
#include <string>

TRational::TRational() {
    numerator = 0;
    denominator = 1;
}

TRational::TRational(double num, double denom) : TRational() {
    if(denom == 0 ){
        numerator = num;
        denom = 1;
        shorten();
    }
    else{
        if(denom < 0 && num >= 0){
            numerator = -1 * num;
            denominator = -1 * denom;
            shorten();
        }
        else{
            numerator = num;
            denominator = denom;
        }
    }

}

double TRational::toDouble() {
        return (double)numerator/denominator;
}

string TRational::toString() {
    return std::to_string(numerator) + " / " + std::to_string(denominator);
}

void TRational::shorten() {
    int divisior = 0;
    bool isNegative = false;
    if(numerator < 0){
        isNegative = true;
        numerator = abs(numerator);
    }

    if(numerator == 0)
        return;
    while(divisior != 1) {
        divisior = getGreatestDivisior(numerator, denominator);
        numerator /= divisior;
        denominator /= divisior;
    }
    if(isNegative){
        numerator = numerator * -1;
    }
}

TRational TRational::operator*(TRational rational)
{
    TRational result = TRational();
    if (rational.denominator != 0 && denominator != 0){
        result.numerator = rational.numerator * numerator;
        result.denominator = rational.denominator * denominator;
        result.shorten();
        return result;
    }
    return *this;
}

TRational TRational::operator*(double value)
{
    TRational result = TRational();
    TRational converted = TRational::toRationalFromDouble(value, 2);

    if (denominator > 0)
        return *this * converted;

    return *this;
}

TRational TRational::operator*(int value)
{
    return *this*(double)value;
}

TRational TRational::operator/(TRational rational)
{
    TRational result = TRational();
    if (rational.numerator != 0 && denominator != 0){
        rational.flipOver();
        result = *this * rational;
        result.shorten();
        return result;
    }
    return *this;
}

TRational TRational::operator/(double value)
{
    TRational converted = TRational::toRationalFromDouble(value, 2);
    if (denominator > 0){
        return *this/converted;
    }
    return *this;
}

TRational TRational::operator+(TRational rational)
{
    TRational result = TRational(numerator, denominator);
    if (rational.denominator != 0 && denominator != 0){
        int nok = getLeastMultiple(denominator, rational.denominator);
        numerator *= (nok / denominator);
        rational.numerator *= (nok / rational.denominator);
        result.numerator = numerator + rational.numerator;
        result.denominator = nok;
        result.shorten();
        return result;
    }
    return *this;
}

TRational TRational::operator+(double value)
{
    TRational converted = TRational::toRationalFromDouble(value, 2);
    if (denominator > 0){
        return *this+converted;
    }
    return *this;
}

TRational TRational::operator-(TRational rational)
{
    TRational result = TRational(numerator, denominator);
    TRational negativeCoef = TRational(-1, 1);
    if (rational.denominator != 0 && denominator != 0){
        result =  result + negativeCoef * rational;
        return result;
    }
    return *this;
}

TRational TRational::operator-(double value)
{
    TRational converted = TRational::toRationalFromDouble(value, 2);
    if (denominator > 0){
        return *this-converted;
    }
    return *this;
}

bool TRational::operator==(const TRational& rat)
{
    if (rat.numerator == numerator && rat.denominator == denominator)
    {
        return true;
    }
    return false;
}

bool TRational::operator==(const int& rat)
{
    if ((double)rat == toDouble())
    {
        return true;
    }
    return false;
}

bool TRational::operator==(const double& r)
{
    if (toDouble() == r)
    {
        return true;
    }
    return false;
}

TRational::operator bool() const
{
    if (numerator == 0)
    {
        return false;
    }
    return true;
}

TRational::operator double() const
{
    return 0;
}

double abs(TRational rational)
{
    return fabs(rational.toDouble());
}

std::ostream& operator<<(std::ostream& output, TRational& rational) {

    output << rational.numerator << '/' << rational.denominator;
    return output;
}

//accuracy - точность
TRational TRational::toRationalFromDouble(double value, int accuracy) {
    TRational result = TRational();
    bool isNegative = value < 0;
    value = fabs(value);
    result.numerator = (int)(value * pow(10, accuracy));
    result.denominator = (int)(pow(10, accuracy));
    result.shorten();
    if (isNegative)
        result.numerator *= -1;
    return result;
}

int TRational::getGreatestDivisior(int first, int second)
{
    if (first == second)
        return first;
    if (first > second)
        return getGreatestDivisior(first-second, second);
    return getGreatestDivisior(first, second-first);
}

int TRational::getLeastMultiple(int first, int second)
{
    return (first*second)/getGreatestDivisior(first,second);
}

void TRational::flipOver()
{

    int buffer = denominator;
    if(numerator < 0)
        denominator = numerator * (-1);
    else
        denominator = numerator;
    if(numerator < 0)
        numerator = buffer * (-1);
    else
        numerator = buffer;
}
