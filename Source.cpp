
#include <stdio.h>

short checkIntersectionOfTwoLineSegments(int otr1X1, int otr1Y1, int otr1X2,
                                         int otr1Y2, int otr2X1, int otr2Y1, int otr2X2, int otr2Y2)
{
    
    //сначала расставим точки по пор€дку, т.е. чтобы было otr1X1 <= otr1X2, это дл€ того
    //если пользователь ввел их не в том пор€дке, и мы расставл€ем в правильном
    if (otr1X2 < otr1X1)
    {
        
        int tmpX1 = otr1X1;
        int tmpY1 = otr1Y1;
        otr1X1 = otr1X2;
        otr1Y1 = otr1Y2;
        otr1X2 = tmpX1;
        otr1Y2 = tmpY1;
    }
    //и otr2X1 <= otr2X2 //это то же самое, только дл€ второго отрезка
    if (otr2X2 < otr2X1)
    {
        
        int tmpX1 = otr2X1;
        int tmpY1 = otr2Y1;
        otr2X1 = otr2X2;
        otr2Y1 = otr2Y2;
        otr2X2 = tmpX1;
        otr2Y2 = tmpY1;
    }
    
    //проверим существование потенциального интервала дл€ точки пересечени€ отрезков
    if (otr1X2 < otr2X1)
    {
        return 0; //значит не пересекаютс€ ибо у отрезков нету взаимной абсциссы
    }
    
    //если оба отрезка вертикальные
    if ((otr1X1 - otr1X2 == 0) && (otr2X1 - otr2X2 == 0))
    {
        
        //если они лежат на одном X
        if (otr1X1 == otr2X1)
        {
            //проверим пересекаютс€ ли они, т.е. есть ли у них общий Y
            //дл€ этого возьмЄм отрицание от случа€, когда они Ќ≈ пересекаютс€
            
            int tempGreater1;//определ€ем кака€ точка больше
            if (otr1Y1 > otr1Y2)
                tempGreater1 = otr1Y1;
            else
                tempGreater1 = otr1Y2;
            
            int tempGreater2; //определ€ем кака€ точка больше
            if (otr2Y1 > otr2Y2)
                tempGreater2 = otr2Y2;
            else
                tempGreater2 = otr2Y1;
            
            int tempLess1; //определ€ем кака€ точка меньше
            if (otr1Y1 > otr1Y2)
                tempLess1 = otr1Y2;
            else
                tempLess1 = otr1Y1;
            
            int tempLess2; //определ€ем кака€ точка меньше
            if (otr2Y1 > otr2Y2)
                tempLess2 = otr2Y1;
            else
                tempLess2 = otr2Y2;
            
            if (!((tempGreater1 < tempGreater2) || //определ€ем, пересекаютс€ ли точки
                  (tempLess1 > tempLess2)))
            {
                return 1;
            }
        }
        
        return 0;
    }
    
    //найдЄм коэффициенты уравнений, содержащих отрезки
    //f1(x) = A1*x + b1 = y
    //f2(x) = A2*x + b2 = y
    
    //если первый отрезок вертикальный
    if (otr1X1 - otr1X2 == 0)
    {
        
        //найдЄм Xa, Ya - точки пересечени€ двух пр€мых
        double Xa = otr1X1;
        double A2 = (otr2Y1 - otr2Y2) / (otr2X1 - otr2X2);
        double b2 = otr2Y1 - A2 * otr2X1;
        double Ya = A2 * Xa + b2;
        
        int tempLess1;
        if (otr1Y1 > otr1Y2)
            tempLess1 = otr1Y2;
        else
            tempLess1 = otr1Y1;
        
        int tempGreater1;
        if (otr1Y1 > otr1Y2)
            tempGreater1 = otr1Y1;
        else
            tempGreater1 = otr1Y2;
        
        if (otr2X1 <= Xa && otr2X2 >= Xa && tempLess1 <= Ya &&
            tempGreater1 >= Ya) {
            
            return 1;
        }
        
        return 0;
    }
    
    //если второй отрезок вертикальный
    if (otr2X1 - otr2X2 == 0)
    {
        
        //найдЄм Xa, Ya - точки пересечени€ двух пр€мых
        double Xa = otr2X1;
        double A1 = (otr1Y1 - otr1Y2) / (otr1X1 - otr1X2);
        double b1 = otr1Y1 - A1 * otr1X1;
        double Ya = A1 * Xa + b1;
        
        int tempLess1; //определ€ем кака€ координата у двух отрезков меньше
        if (otr2Y1 > otr2Y2)
            tempLess1 = otr2Y2;
        else
            tempLess1 = otr2Y1;
        
        int tempGreater1; //определ€ем кака€ координата у двух отрезков больше
        if (otr2Y1 > otr2Y2)
            tempGreater1 = otr2Y1;
        else
            tempGreater1 = otr2Y2;
        
        if (otr1X1 <= Xa && otr1X2 >= Xa && tempLess1 <= Ya &&  //опреде€ем, пересекаютс€ ли 2 отрезка
            tempGreater1 >= Ya)
        {
            
            return 1; //да
        }
        return 0; //нет
    }
    
    //оба отрезка невертикальные
    double A1 = (otr1Y1 - otr1Y2) / (otr1X1 - otr1X2);
    double A2 = (otr2Y1 - otr2Y2) / (otr2X1 - otr2X2);
    double b1 = otr1Y1 - A1 * otr1X1;
    double b2 = otr2Y1 - A2 * otr2X1;
    
    if (A1 == A2) {
        return 0; //отрезки параллельны
    }
    
    //Xa - абсцисса точки пересечени€ двух пр€мых
    double Xa = (b2 - b1) / (A1 - A2);
    
    int tempGreater1;
    if (otr1X1 > otr2X1)
        tempGreater1 = otr1X1;
    else
        tempGreater1 = otr2X1;
    
    int tempLess1;
    if (otr1X2 > otr2X2)
        tempLess1 = otr2X2;
    else
        tempLess1 = otr1X2;
    
    if ((Xa < tempGreater1) || (Xa > tempLess1))
    {
        return 0; //точка Xa находитс€ вне пересечени€ проекций отрезков на ось X
    }
    else
    {
        return 1;
    }
}

int main()
{
    
    int otr1X1, otr1Y1;
    int otr1X2, otr1Y2;
    int otr2X1, otr2Y1;
    int otr2X2, otr2Y2;
    printf("Input x1 y1 first point: ");
    scanf("%i%i", &otr1X1, &otr1Y1);
    printf("\nInput x2 y2 second point: ");
    scanf("%i%i", &otr1X2, &otr1Y2);
    printf("\nInput x3 y3 third point: ");
    scanf("%i%i", &otr2X1, &otr2Y1);
    printf("\nInput x4 y4 fourth point: ");
    scanf("%i%i", &otr2X2, &otr2Y2);
    short check = checkIntersectionOfTwoLineSegments(otr1X1, otr1Y1, otr1X2, otr1Y2, otr2X1, otr2Y1, otr2X2, otr2Y2);
    if (check == 1)
        printf("\nResult: Intersect\n");
    else
        printf("\nResult: Not intersect\n");
    return 0;
}
