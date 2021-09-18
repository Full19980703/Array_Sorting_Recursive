// problem_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <malloc.h>
#include <math.h>

float* s, * x, * mean_x;

void sortMeanAndX(int size) {
    int i = 1 , j ;
    for (i = 1; i <= size -1 ; i++) {
        for (j = i ; j <= size; j++) {
            if (x[i] >= x[j]) {
                float tmp = x[i];
                x[i] = x[j];
                x[j] = tmp;

                tmp = mean_x[i];
                mean_x[i] = mean_x[j];
                mean_x[j] = tmp;
            }
        }
    }
    return ;
}
void getMean(int order) {
    if (order == 1) {
        mean_x[1] = x[1];
        return;
    }
    else {
        getMean(order - 1);
        mean_x[order] = mean_x[order - 1] * (order - 1) / order + x[order] / order;
    }
    return;
}
void getSum(int order) {
    if (order == 1) {
        s[1] = x[1];
        return;
    }
    else {
        getSum(order - 1);
        s[order] = x[order] + s[order - 1];
    }
}
float getNumber(char* str) {
    float year ;

    sscanf_s(str, "%f", &year);
    
    return year;
}

int main()
{
    char year[1024];
    int i = 1;
    printf_s("Until Which year: ");
    scanf_s("%s", year , 10);

    int cnt = int( getNumber(year) - 2008 );

    x = (float*)malloc(sizeof(float) * (20));
    mean_x = (float*)malloc(sizeof(float) * (20));
    s = (float*)malloc(sizeof(float) * (20));

   

    char line[1024];
    FILE* fp;
    fopen_s(&fp ,"1.txt", "rb");

    //Checks if file is empty
    if (fp == NULL) {
        return 1;
    }
    char seps[] = " ";
    char* token = NULL;
    char* next_token = NULL;

    while (fgets(line, 1024, fp)) {
        char* tmpArea;
        token = strtok_s(line, seps, &next_token);
        tmpArea = token;
        
        token = strtok_s(NULL, seps, &next_token);
        i = 1;
        while ((token != NULL)){
            if (token != NULL){   
               // printf_s("%s ", token);
                x[i] = getNumber(token);
                //printf("%f\n", x[i]);
                token = strtok_s(NULL, seps, &next_token);

                i++;
                
                if (i == cnt ) break;
            }
        }
      

        getMean(cnt);

        sortMeanAndX(cnt);

        int  j = 2 ;
        printf_s("< %s > : ", tmpArea);
        float sum = 0;
        
        for (j = 1  ; j <= cnt ; j++) {
            //printf("%f %f", x[j], mean_x[j]);
            sum += (x[j] - mean_x[j]) * (x[j] - mean_x[j]);
        }
        printf_s("_____  Standard Deviation: %f\n", sqrt( sum / (cnt - 1) ) );
    }
    

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
