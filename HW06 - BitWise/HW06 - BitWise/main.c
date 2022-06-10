//
//  main.c
//  HW06 - BitWise
//
//  Created by Yonatan Glanzman on 09/06/2022.
//

#include <stdio.h>


int pack4Chars2Int(char c1, char c2, char c3, char c4){
    int res = 0;
    
    res|= c1;
    res = res << 8 ;
    res |= c2;
    res= res << 8;
    res |= c3;
    res = res << 8;
    res |= c4;
    return res;
}

int checkEvenParity(short input)
{
    int c = 0;

    while (input !=0 && input!=-1)
    {
        if (input & 1)
            c++;
        
        input = input >> 1;

    }
    c %= 2;
    
    if ( c == 1)
        return 0;
    else
        return 1;
}
