//ATABERK TÜRK ATAG
//2015915

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct match{//for matching the given data for encoding process
    int person;
    char matches[100];
    int numOfItems;
}MATCH;

typedef struct fixations{//while taking the fixation data i use this
    int fixID;
    int xCoordinate;
    int yCoordinate;
    int duration;
}FIX;

typedef struct aoi{//while taking the aois data i use this
    char elementName;
    int topLeftX;
    int width;
    int bottomRightY;
    int height;
}AOI;

struct graphHead{
    int count;
    struct graphVertex *first;
};

struct graphVertex{
    struct graphVertex *next;
    char data[100];
    int inDegree;
    int outDegree;
    int processed;
    struct graphArc *firstArc;
};

struct graphArc{
    struct graphVertex *destination;
    struct graphArc *nextArc;
};

struct graphHead *createGraph(void){//creating the empty graph
    struct graphHead *head = (struct graphHead *)malloc(sizeof(struct graphHead));
    head->count = 0;
    head->first = NULL;
    return head;
}

void insertVertex(struct graphHead *head, MATCH dataIn){//Inserting the vertex
    struct graphVertex *vertex = (struct graphVertex *)malloc(sizeof(struct graphVertex));
    vertex->next = NULL;
    strcpy(vertex->data,dataIn.matches);
    vertex->inDegree = 0;
    vertex->outDegree = 0;
    vertex->processed = 0;
    vertex->firstArc = NULL;
    head->count++;
    if(head->first == NULL){
        head->first = vertex;
    }
    else{
        struct graphVertex *temp=head->first;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = vertex;
    }
}

void displayGraph(struct graphHead *head){//print fucntion
    struct graphVertex *tempVertex = NULL;
    struct graphArc *tempArc = NULL;
    tempVertex = head->first;

    while(tempVertex != NULL){
        printf("Data: %s \n",tempVertex->data);
        tempArc = tempVertex->firstArc;
        while(tempArc != NULL){
            printf("Destination Data: %s \n", tempArc->destination->data);
            tempArc = tempArc->nextArc;   
        }
        tempVertex = tempVertex->next;
    }
}

struct graphHead *insertArc(struct graphHead *head, char *fromKey, char *toKey){//inserting edges
    struct graphArc *arc = (struct graphArc*)malloc(sizeof(struct graphArc)); 
    struct graphVertex *fromVertex = NULL;
    struct graphVertex *toVertex = NULL;
    fromVertex = head->first;
    while(fromVertex != NULL && strcmp(fromVertex->data,fromKey) != 0){
        fromVertex = fromVertex->next;
    }

    if(fromVertex == NULL){
        return 0; //just an eror
    }

    toVertex = head->first;
    while(toVertex != NULL && strcmp(toVertex->data,toKey) != 0){
        toVertex = toVertex->next;
    }

    if(toVertex == NULL){
        return 0;//just an eror
    }

    fromVertex->outDegree++;
    toVertex->inDegree++;

    arc->destination = toVertex;
    arc->nextArc = NULL;

    if(fromVertex->firstArc == NULL){
        fromVertex->firstArc = arc;
    }
    else{
        struct graphArc *tempArc = fromVertex->firstArc;
        while(tempArc->nextArc != NULL){
            tempArc = tempArc->nextArc;
        }
        tempArc->nextArc = arc;
    }
    return head;
}

int line_counter(char *filename){//Helper: this function counts the number of lines in the file.
    FILE *infile;
    char ch;
    int line_count=0;
    infile = fopen(filename,"r");
    if(infile == NULL){
        printf("Eror while reading lines");
        exit(0);
    }
    ch = fgetc(infile);
    while(ch != EOF){
        if(ch == '\n'){
            line_count += 1;
        }
        ch=fgetc(infile);
    }
    fclose(infile);
    return line_count;
}

MATCH *scanpath(AOI *file_AOI, FIX *file_FIX, int lineofAOI, int lineofFIX){//Creating the scanpath of given data
    int x_Coordinate,y_Coordinate;
    int numofMatch=0;
    char ch;
    int index=0;
    MATCH *matchedElements = (MATCH *)malloc(sizeof(MATCH));

    for(int i = 0; i < lineofFIX +1; i++){
        if(file_FIX[i].fixID == 0){
            numofMatch++;
            matchedElements = (MATCH *)realloc(matchedElements,numofMatch*sizeof(MATCH));
            matchedElements[numofMatch-1].person = numofMatch;
            index = 0;
            //printf("HERE");
        }
        for(int j = 0;j < lineofAOI+1; j++){
            x_Coordinate = file_AOI[j].topLeftX + file_AOI[j].width;//total x which is x coordinate's maximum reachable position
            y_Coordinate = file_AOI[j].bottomRightY + file_AOI[j].height;//total y which is y coordinate's maximum reachable position
            if(file_FIX[i].xCoordinate > file_AOI[j].topLeftX && file_FIX[i].yCoordinate > file_AOI[j].bottomRightY){
                if(file_FIX[i].xCoordinate < x_Coordinate && file_FIX[i].yCoordinate < y_Coordinate){
                    ch = file_AOI[j].elementName;
                    break;
                }
            }
        }
        matchedElements[numofMatch-1].matches[index] = ch;
        matchedElements[numofMatch-1].numOfItems = index+1;
        index++;
        
    }
    /*for(int k = 0; k<numofMatch;k++){//check whether matches are correctly inserted
        //printf("HERE!!!!!!!!!!!!");
        printf("%d, %s\n",matchedElements[k].person,matchedElements[k].matches);
    }*/

    return matchedElements;
}


struct graphHead *createVertices(char *filename1, char *filename2){//creating the vertices with given files.
    struct graphHead *head = createGraph();
    int numofAOI,numofFIX,numofPeople;
    int n=0;
    int m=0;
    AOI *file_AOI = (AOI *)malloc(sizeof(AOI));
    FIX *file_FIX = (FIX *)malloc(sizeof(FIX));
    numofAOI = line_counter(filename1);
    numofFIX = line_counter(filename2);
    MATCH *characters = (MATCH*)malloc(sizeof(MATCH));

    FILE *infile;

    infile = fopen(filename1,"r");
    for(int i = 0;i < numofAOI+1; i++){
        n = n+1;
        file_AOI = (AOI *)realloc(file_AOI,n*sizeof(AOI));
        fscanf(infile,"%c %d %d %d %d\n",&file_AOI[i].elementName,&file_AOI[i].topLeftX,&file_AOI[i].width,&file_AOI[i].bottomRightY,&file_AOI[i].height);
    }
    fclose(infile);
    /*for(int i = 0;i < numofAOI +1; i++){ //This checks reading is succesful or not
        printf("%c,%d,%d,%d,%d\n",file_AOI[i].elementName,file_AOI[i].topLeftX,file_AOI[i].width,file_AOI[i].bottomRightY,file_AOI[i].height);
    }*/
    infile = fopen(filename2,"r");
    for(int j = 0;j < numofFIX+1; j++){
        m = m+1;
        file_FIX = (FIX *)realloc(file_FIX,m*sizeof(FIX));
        fscanf(infile,"%d %d %d %d\n",&file_FIX[j].fixID,&file_FIX[j].xCoordinate,&file_FIX[j].yCoordinate,&file_FIX[j].duration);
    }
    fclose(infile);
    /*for(int j = 0;j < numofFIX +1; j++){ //This checks reading is succesful or not
        printf("%d,%d,%d,%d\n",file_FIX[j].fixID,file_FIX[j].xCoordinate,file_FIX[j].yCoordinate,file_FIX[j].duration);
    }*/
    characters = scanpath(file_AOI,file_FIX,numofAOI,numofFIX);

    /*for(int k = 0; characters[k].person > 0;k++){//Checks the characters array correctly returned or not.
        //printf("BURAD!!!!!!!!!!!!");
        printf("%d, %s, %d\n",characters[k].person,characters[k].matches,characters[k].numOfItems);
    }*/

    int k=0;
    while(k == characters[k].person - 1){
        insertVertex(head,characters[k]);//yada kisi sayisinida yollayabiliriz
        k++;
    }

    //displayGraph(head);//check for vertexes.


    return head;
}



struct graphHead *createEdges(struct graphHead* graph){//Creating the edges with given graph which is created in createVertex
    char S1[100], S2[100];
    int checker = 0;
    int numOfDATA = 0;
    struct graphVertex *tempvertex = graph->first;

    //LCS part
    while(numOfDATA < graph->count-1){
        strcpy(S1,tempvertex->data);
        tempvertex = tempvertex->next;
        if(tempvertex != NULL){
            strcpy(S2,tempvertex->data);
        }
        else{
            checker = 1;
        }
        int m = strlen(S1);
        int n = strlen(S2);
        int LCS_table[m][n];
        for(int i = 0;i < m; i++){
            for(int j = 0; j < n; j++){
                LCS_table[i][j] = 0;
            }
        }
        if((strcmp(S1,S2) != 0) && checker == 0){
            for(int i = 1; i< m;i++){
                for(int j = 1; j<n;j++){
                    if(S1[i-1] == S2[j-1]){
                        LCS_table[i][j] = LCS_table[i - 1][j - 1] + 1;
                    }
                    else if(LCS_table[i-1][j] >= LCS_table[i][j-1]){
                        LCS_table[i][j] = LCS_table[i-1][j];
                    }
                    else{
                        LCS_table[i][j] = LCS_table[i][j-1];
                    }
                }
            }
        }
        int index = LCS_table[m-1][n-1];
        char holder[index + 1];
        holder[index] = '\0';
        int total = 0;

        int k = m, l = n;
        while(k > 0 && l > 0){
            if(S1[k - 1] == S2[l - 1]){
                holder[index-1] = S1[k - 1];
                k--;
                l--;
                index--;
            }
            else if(LCS_table[k-1][l] > LCS_table[k][l-1]){
                k--;
            }
            else{
                l--;
            }
        }
        
        if(strlen(holder) >= 5){
            graph = insertArc(graph,S1,S2);
            graph = insertArc(graph,S2,S1);
        }
        numOfDATA ++;
    }
    //LCS Part finished
    return graph;
}


int main(){//main
    char filename1[10],filename2[20];
    struct graphHead *graPH;
    printf("Enter AOIs file name > ");
    scanf("%s",filename1);
    printf("Enter scanpaths file name > ");
    scanf("%s",filename2);

    graPH = createVertices(filename1,filename2);
    graPH = createEdges(graPH);
    displayGraph(graPH);

    return 0;
}