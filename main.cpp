#include "t1.h"

using namespace std;

bool isPrime (const unsigned int &);
void bktPrimeDivisors (unsigned short &rez,
                       unsigned int *v,
                       const unsigned int &lgV,
                       const unsigned int &left,
                       const unsigned int &right,
                       const int &maxPrimeDivisors,
                       unsigned long long int prod,
                       int k,
                       int multipliedValues);

int main(){
    return 0;
}

bool isPalindrom(unsigned long long number){
    unsigned long long mirroredNumber, numberCopy;
    mirroredNumber=0; numberCopy=number;

    while (numberCopy){
        mirroredNumber=mirroredNumber*10+numberCopy%10;
        numberCopy/=10;
    }

    return (number==mirroredNumber);
}

unsigned char sumBinaryFigure(unsigned long long number){
    unsigned char sum=0;

    while (number){
        sum+=number%2;
        number/=2;
    }

    return sum;
}

bool isLeapYear(unsigned short year){
    //trebuie sa fie divizibil cu 4 dar nu si cu 100
    //sau divizibil cu 400
    if ((year%4==0 && year%100) || year%400==0)
        return true;
    return false;
}

unsigned char dayOfTheWeek(unsigned short year,
                           unsigned char month,
                           unsigned char day){
    //numarul zilei din saptamana
    int rez, h, q, y, m;

    if (month<=2){
        month+=12;
        --year;
    }

    q=(int) day;
    m=(int) month;
    y=(int) year;
    h=(q+((13*(m+1))/5)+y+y/4-y/100+y/400)%7;//zeller's congruence
    rez=((h+5)%7)+1;
    return (unsigned char)rez;
}

unsigned int fibonnaci(int index){
    unsigned int fib1, fib2, fib3;
    int i;
    for (i=fib1=fib2=fib3=1; i<index-1; ++i){
        fib3=fib1+fib2;
        fib1=fib2;
        fib2=fib3;
    }

    if (!index)
        fib3=0;

    return fib3;
}

unsigned long perfectNumbers(unsigned int number){
    //humble solution based on extraordinary research
    //heil forums
    //number>=30, macar 2 numere perfecte (6, 28)

    unsigned int prim1, prim2, p;
    unsigned long rez;

    prim2=2;

    for (p=3; 1LL * (1<<(p-1)) * ((1<<p)-1) <= number; p+=2){
        if (isPrime((1<<p)-1)){//mersenne prime => perfect number
            prim1=prim2;
            prim2=p;
        }
    }

    rez=(1<<(prim1-1)) * ((1<<prim1)-1);
    rez+=(1<<(prim2-1)) * ((1<<prim2)-1);



    /*
    unsigned long rez, nr, nrCount, sum, d;
    if (number%2==0)
        nr=number-1;
        else
        nr=number;

    for (rez=nrCount=0; nrCount<2; nr-=2){}
        sum=1;//1 sigur il divide pe nr
        for (d=2; d*d<nr; ++d)
            if (nr%d==0)
                sum+=d+nr/d;
        //daca e patrat perfect, d=nr/d, adun 1 sg. data
        if (d*d==nr)
            sum+=d;
        if (sum==nr){
            ++nrCount;
            rez+=nr;
        }
    }*/

    return rez;
}

unsigned short primeDivisors(unsigned int left, unsigned int right){

    if (left>right)
        return primeDivisors (right, left);
    if (left==right)
        return 1;

    //unsigned int nrPrime[15]={2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    //prod de nr prime pana la 29 inclusiv depaseste unsigned int (aprox 6 mld.)
    unsigned int nrPrime[MAX_ARRAY_LENGTH], lgNrPrime=0, x, d, nrPrimeDivisors;
    unsigned long long int prod;
    unsigned int maxPrimeDivisors=0, i;
    unsigned short rez=0;

    nrPrime[lgNrPrime++]=2;//primul numar prim
    for (prod=3; lgNrPrime<MAX_ARRAY_LENGTH/2; prod+=2)//prod e o var. aleatorie
        if (isPrime(prod))
            nrPrime[lgNrPrime++]=prod;

    for (prod=1, i=0; prod<=right; ++i){
        prod*=nrPrime[i];
        ++maxPrimeDivisors;
    }
    --maxPrimeDivisors;
    prod/=nrPrime[i-1];

    if (left<=prod && prod<=right){
        bktPrimeDivisors (rez, nrPrime, lgNrPrime, left, right, maxPrimeDivisors, 1, 0, 0);
        return rez;
    }

    //if not... brute

    maxPrimeDivisors=0;
    for (x=left; x<=right; ++x){
        nrPrimeDivisors=0;
        if (x%2==0)
            ++nrPrimeDivisors;
        for (d=3; d*d<x; d+=2)
            if (x%d==0){
                if (isPrime(d))
                    ++nrPrimeDivisors;
                if (isPrime(x/d))
                    ++nrPrimeDivisors;
            }
        //daca e patrat perfect, d=nr/d, adun 1 sg. data
        if (d*d==x && isPrime(d))
            ++nrPrimeDivisors;

        if (nrPrimeDivisors>maxPrimeDivisors){
            maxPrimeDivisors=nrPrimeDivisors;
            rez=1;
        }
            else
            if (nrPrimeDivisors==maxPrimeDivisors)
                ++rez;
    }


    return rez;
}

void bktPrimeDivisors (unsigned short &rez,
                       unsigned int *v,
                       const unsigned &lgV,
                       const unsigned int &left,
                       const unsigned int &right,
                       const int &maxPrimeDivisors,
                       unsigned long long int prod,
                       int k,
                       int multipliedValues){
    if (prod>right)
        return;

    if (multipliedValues==maxPrimeDivisors){
        if (left)
            rez+=(unsigned long long int)right/prod - (unsigned long long int)(left-1)/prod;
            else
            rez+=(unsigned long long int)right/prod;
        return;
    }

    unsigned int i;
    for (i=k; i<lgV; ++i){
        prod*=v[i];
        bktPrimeDivisors (rez, v, lgV, left, right, maxPrimeDivisors, prod, i+1, multipliedValues+1);
        prod/=v[i];
        }
}

matrix primeTwins(unsigned int count, unsigned int lowerBound){
    unsigned int x1, x2, x3;
    unsigned int lastPrimeX3;
    bool x1IsPrime=false, x3IsPrime=false;
    matrix rez;

    rez.lines=0;
    x2=lowerBound+2;
    if (lowerBound%2==0)
        ++x2;
    if (!count)
        return rez;

    //prima pereche o tratez separat, eventual a doua daca x3 e prim
    //ca sa am x3IsPrime calculat
    while (1){
        x1=x2-2; x3=x2+2;
        if (isPrime(x2)){
            if (isPrime(x1)){
                rez.values[rez.lines][0]=x1;
                rez.values[rez.lines][1]=x2;
                ++rez.lines;
                if (count==1)
                    break;

                x3IsPrime=isPrime (x3);
                lastPrimeX3=x3;
                if (x3IsPrime){
                    rez.values[rez.lines][0]=x2;
                    rez.values[rez.lines][1]=x3;
                    ++rez.lines;
                }
                break;
            }
            }
        x2+=4;
    }
    if (count==1)
        return rez;

    while (1){
        x2+=4;
        x1=x2-2; x3=x2+2;//x1 devine x3-ul anterior
        x1IsPrime=x3IsPrime;//incerc sa nu calculez de 2 ori acelasi lucru

        if (isPrime(x2)){
            if (lastPrimeX3!=x1)//daca x1 nu coincide cu ultimul x3 pt. care am calculat primalitatea
                x1IsPrime=isPrime (x1);
            if (x1IsPrime){
                rez.values[rez.lines][0]=x1;
                rez.values[rez.lines][1]=x2;
                ++rez.lines;
                if (rez.lines==count)
                    break;
            }

            x3IsPrime=isPrime (x3);
            if (x3IsPrime){
                rez.values[rez.lines][0]=x2;
                rez.values[rez.lines][1]=x3;
                ++rez.lines;
                lastPrimeX3=x3;
                if (rez.lines==count)
                    break;
            }
        }
    }

    return rez;
}

bool isPrime (const unsigned int &x){//multi-purpose
    unsigned int d=3;
    if (x%2==0 && x!=2)
        return false;
    if (x<2)//0, 1 nu sunt prime
        return false;
    for (d=3; d*d<=x; d+=2)
        if (x%d==0)
            return false;
    return true;
}