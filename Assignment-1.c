#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

typedef struct Champions_Data{
    char championName[50];
    double expectedWinRate;
    int NumberOfBattles;
    int NumberOfWins;
    double ActualWinRate;
    double ExpectationSkew;

}CHAMPINFO;


CHAMPINFO *initializeChampions(char *argv,CHAMPINFO *Champs,int n){//initilizing the content of the champions.txt in to CHAMPSINFO structer
    int i;
    FILE *infile;

    infile = fopen(argv,"r");
    if (infile == NULL){
        printf("EROR");
        exit(0);
    }

    for(i = 0;i < n;i++){
        Champs = (CHAMPINFO *)realloc(Champs,(i+1)*sizeof(CHAMPINFO));
        fscanf(infile,"%s %lf\n" ,Champs[i].championName,&Champs[i].expectedWinRate);
    }

   fclose(infile);

    return Champs;
}
//char *argv[],fopen(argv[2])
void getBattleData(CHAMPINFO *Champs,char argv[],int n,int champ_line){//get battle data from the file
    char battle[10],name1[50],name2[50],name3[50];
    int i,j;
    FILE *infile;
    for(j = 0; j < champ_line;j++){
        infile = fopen(argv,"r");
        if(infile == NULL){
            printf("EROR");
            exit(0);
        }

        for(i = 0;i < n;i++){
            fscanf(infile,"%s %s %s %s \n" , battle,name1,name2,name3);
            if(strcmp(Champs[j].championName,name1) == 0 || strcmp(Champs[j].championName,name2) == 0){
                Champs[j].NumberOfBattles += 1;
            }
            if (strcmp(Champs[j].championName,name3) == 0){
                Champs[j].NumberOfWins += 1;
            }
        }
        fclose(infile);
    }
}
//char *argv[],fopen(argv[3])
void computeWinRate(CHAMPINFO *Champs,int n){//it takes CHAMPSINFO and actual size to do computations
    int i;
    float winRateRatio;
    
    for(i = 0;i < n;i++){
        Champs[i].ActualWinRate = (double)Champs[i].NumberOfWins / Champs[i].NumberOfBattles;
        winRateRatio = Champs[i].ActualWinRate / Champs[i].expectedWinRate;
        Champs[i].ExpectationSkew = winRateRatio - 1;

        if(Champs[i].ExpectationSkew < 0){
            Champs[i].ExpectationSkew = Champs[i].ExpectationSkew * -1;
        }

    }
}

void swap(CHAMPINFO *Champs,int i,int j,int n){//This is a helper function for swapping.i=HeapSize,j=largest,n=ActualSize
    CHAMPINFO temp[1];
        
    strcpy(temp[0].championName,Champs[i].championName);
    temp[0].expectedWinRate = Champs[i].expectedWinRate;
    temp[0].NumberOfBattles = Champs[i].NumberOfBattles;
    temp[0].NumberOfWins = Champs[i].NumberOfWins;
    temp[0].ActualWinRate = Champs[i].ActualWinRate;
    temp[0].ExpectationSkew = Champs[i].ExpectationSkew;
    if(i != j){
        strcpy(Champs[i].championName,Champs[j].championName);
        Champs[i].expectedWinRate = Champs[j].expectedWinRate;
        Champs[i].NumberOfBattles = Champs[j].NumberOfBattles;
        Champs[i].NumberOfWins = Champs[j].NumberOfWins;
        Champs[i].ActualWinRate = Champs[j].ActualWinRate;
        Champs[i].ExpectationSkew = Champs[j].ExpectationSkew;
    }

    strcpy(Champs[j].championName,temp[0].championName);
    Champs[j].expectedWinRate =  temp[0].expectedWinRate;
    Champs[j].NumberOfBattles =  temp[0].NumberOfBattles;
    Champs[j].NumberOfWins =  temp[0].NumberOfWins;
    Champs[j].ActualWinRate =  temp[0].ActualWinRate;
    Champs[j].ExpectationSkew =  temp[0].ExpectationSkew;

}

void Heapify(CHAMPINFO *Champs,int heapSize,int n,char *opSelect[]){
    int largest = heapSize;
    int left = 2 * heapSize + 1; 
    int right = 2 * heapSize + 2;

    if(*opSelect[1] == '1'){
        if (left < n && Champs[left].ActualWinRate > Champs[largest].ActualWinRate) {
            largest = left;
        }
        if (right < n && Champs[right].ActualWinRate > Champs[largest].ActualWinRate) {
            largest = right; 
        }
        if(largest != heapSize) {
            swap(Champs,heapSize,largest,n);
            Heapify(Champs, largest, n,opSelect);
        }
    }
    else if(*opSelect[1] == '2'){
        if (left < n && Champs[left].expectedWinRate > Champs[largest].expectedWinRate){
            largest = left; 
            }
    
        if (right < n && Champs[right].expectedWinRate > Champs[largest].expectedWinRate){
            largest = right; 
            }

        if(largest != heapSize) {
            swap(Champs,heapSize,largest,n); 
            Heapify(Champs, largest, n,opSelect);
        }
    }

    else if(*opSelect[1] == '3'){
        if (left < n && Champs[left].ExpectationSkew > Champs[largest].ExpectationSkew){
            largest = left; 
        }
        if (right < n && Champs[right].ExpectationSkew > Champs[largest].ExpectationSkew){
            largest = right; 
        }
        if(largest != heapSize) {
            //printf("HEREEEEEEE");
            swap(Champs,heapSize,largest,n); 
            Heapify(Champs, largest, n,opSelect);
        }
    }
}

void BuildHeap(CHAMPINFO *Champs,int n,char *opSelect[]){//heap sort(i am takin actual size of the CHAMPINFO and sorting criteria)
    int i;
    for(i = n/2 - 1;i >= 0;i--){
        Heapify(Champs,i,n,opSelect);
    }
}

void heapSort(CHAMPINFO *Champs,char *opSelect[],int n){//heap sort(i am takin actual size of the CHAMPINFO and sorting criteria)Sorun Burada
    int i;
    BuildHeap(Champs,n,opSelect);
    for(i = n-1 ; i >= 0 ; i--){
        swap(Champs,0,i,n);
        Heapify(Champs,0,i,opSelect);
    }
}

void printLeaderboard(CHAMPINFO *Champs,int n)//print
{
    int i;
    printf("Champion\tBattles\tWin\tAWR\tEWR\tSKEW\n");
    for(i = 0; i < n;i++){
        printf("%s\t\t%d\t%d\t%.2f\t%.2f\t%.2f\n",Champs[i].championName,Champs[i].NumberOfBattles,Champs[i].NumberOfWins,Champs[i].ActualWinRate,Champs[i].expectedWinRate,Champs[i].ExpectationSkew);
    }
}

int main(int argc, char *argv[])//main
{
    FILE *infile;

    CHAMPINFO *Champs = (CHAMPINFO*)malloc(sizeof(CHAMPINFO));
    char ch;
    int line_counter=1,i,line_counter_battle=1;
    char file2[]="battles.txt";
    char file1[]="champions.txt";
    infile = fopen(file1,"r");

    if(infile == NULL){
        printf("EROR");
        exit(0);
    }
    //Just works for counting lines
    ch=fgetc(infile);
    while(ch != EOF){
        if(ch == '\n'){
            line_counter +=1;
        }
        ch = fgetc(infile);
    }
    fclose(infile);

    Champs=initializeChampions(file1,Champs,line_counter);

    /*for(i = 0; i < line_counter;i++){
        printf("%s %.2f\n",Champs[i].championName,Champs[i].expectedWinRate);
    }After initilize i just checking everthing is okey or not*/
    
    infile = fopen(file2,"r");

    if(infile == NULL){
        printf("EROR");
        exit(0);
    }
    //just works for counting lines
    ch = fgetc(infile);
    while(ch != EOF){
        if(ch == '\n'){
            line_counter_battle +=1;
        }
        ch = fgetc(infile);
    }
    fclose(infile);

    getBattleData(Champs,file2,line_counter_battle,line_counter);
    //printf("After Get Battle Data\n");
    /*for(i = 0; i < line_counter;i++){
        printf("%s %.2f %d %d\n",Champs[i].championName,Champs[i].expectedWinRate,Champs[i].NumberOfBattles,Champs[i].NumberOfWins);
    }*///Checker again
    argv[1] = "1";
    computeWinRate(Champs,line_counter);
    heapSort(Champs,argv,line_counter);
    printLeaderboard(Champs,line_counter);

    free(Champs);

    return 0;


}
