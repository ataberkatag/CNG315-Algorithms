#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef struct {
    char studentID[4];
    char Name[40];
    char Department[4];
}studentINFO;


int hash1(int key,int Totalsize){//hash1 helper
    int n = (2 * key) % Totalsize;
    return n;
}

int hash2(int key){//hash2 helper
    int n = 7 - (key % 7);
    return n;
}

//double hashing takes table and current person and finds appropriate position and adds that student in to hash table.
bool doubleHashing(studentINFO *HashTable,studentINFO *p,int key,int Totalsize){
    int index;
    if (p == NULL)return false;
    else{
        for(int i = 0 ; i < Totalsize ; i++){
            index = (hash1(key,Totalsize)+(i * hash2(key))) % Totalsize;
            if(strcmp(HashTable[index].studentID,"0") == 0){
                HashTable[index] = *p;
                return true;
            }
        }
    }
    return false;
}

//quadratic Probing takes table and current person and finds appropriate position and adds that student in to hash table.
bool quadraticProbing(studentINFO *HashTable,studentINFO *p,int key,int Totalsize){
    int index;
    if (p == NULL)return false;
    else{
        for(int i = 0 ; i < Totalsize; i++){
            index = (hash1(key,Totalsize) + (i*i)) % Totalsize;
            if(strcmp(HashTable[index].studentID,"0") == 0){
                HashTable[index] = *p;
                return true;
            }
        }
    }
    return false;
}

//At the beginning i create a hashtable which has 0 in all the indexes.
void create_HashTable(studentINFO *HashTable,int StartIndex){
    for(int i = 0;i<StartIndex;i++){
        if(strcmp(&HashTable[i].studentID[0],"0") > 0){
            continue;
        }
        else{
            strcpy(HashTable[i].studentID,"0");
        }
    }        
}

//rehash:I create new hashtable inside this array and return it with new index.When i use reallocation i lost some of my information.
studentINFO *reHash(studentINFO *HashTable,int newSize,int opSelectForAdressing){
    studentINFO *temp = HashTable;
    int key;
    studentINFO *newHashTable = (studentINFO *) malloc (newSize * sizeof(studentINFO));
    create_HashTable(newHashTable,newSize);
    for(int i = 0;i < newSize ; i++){
        if(strcmp(temp[i].studentID,"0") != 0){
            key = (temp[i].studentID[0] - 65) + (temp[i].studentID[1] - 48) + (temp[i].studentID[2] - 48);
            if(opSelectForAdressing == 1){
                doubleHashing(newHashTable,&temp[i],key,newSize);
            }
            else{
                quadraticProbing(newHashTable,&temp[i],key,newSize);
            }
        }
    }
    free(HashTable);
    return newHashTable;
}

//i just take the table and traverse inside it.(5 does not check for id uniqueness)FIXED
int Searchastudent(studentINFO *HashTable,int Totalsize,char ID[4]){
    int n;
    for(int i = 0;i < Totalsize ; i++){
        if(strcmp(ID,HashTable[i].studentID) == 0){
            n = i+1;
            break;
        }
        else{
            n = -1;
        }
    }
    return n;
}

//print the entire table
void print_Hash(studentINFO *HashTable,int TotalIndex){
    printf("Start\n");
    for(int i = 0;i<TotalIndex;i++){
        if(strcmp(HashTable[i].studentID,"0") == 0){
            printf("\t%i\t-----\n",i);
        }
        else{
            studentINFO *temp = &HashTable[i];
            printf("\t%d\t%s\t%s\t%s\n",i,temp->studentID,temp->Name,temp->Department);
        }
    }
}

//menu
void menu_openAdressing(){
    printf("Choose 1 for double hashing\n");
    printf("Choose 2 for quadratic probing\n");
    printf("Choose:");
}

//menu
void menu_functionalities(){
    printf("\n1. Add a student\n");
    printf("2.Search for a student using ID\n");
    printf("3.Printf Table\n");
    printf("4.Exit\n");
    printf("Choose:");
}

//main Function
int main (){
    /*Example Data:
    studentINFO C = {"C12","Salley Bates","CHM"};
    studentINFO A = {"A56","Ashley Norman","MEC"};
    studentINFO Z = {"A69","Peter Holland","CNG"};
    studentINFO G = {"A00","George Martin","ASE"};
    studentINFO M = {"U11","Molly Eleanor","PSY"};*/

    int studentCounter = 0;
    float loadFactor;
    int Hash_index = 11;
    int checker = 1;
    studentINFO *HashTable = (studentINFO *) malloc (Hash_index*sizeof(studentINFO));
    create_HashTable(HashTable,Hash_index);
    printf("\t\t-----------------Your Empty Hash Table-------------------\t\t\n");
    print_Hash(HashTable,Hash_index);
    int key;
    int opSelectForAdressing;
    int opSelectForFunctionalities;
    char ID[4];
    menu_openAdressing();
    scanf("%d",&opSelectForAdressing);
    menu_functionalities();
    scanf("%d",&opSelectForFunctionalities);
    while(opSelectForFunctionalities != 4){
        switch(opSelectForFunctionalities){
            case 1:
                studentCounter += 1;
                studentINFO *Students = (studentINFO *)malloc(1*sizeof(studentINFO));
                printf("Enter unique identifier:");
                scanf("%s",Students[0].studentID);
                getchar();
                printf("Enter name:");
                scanf("%[^\n]",Students[0].Name);
                printf("Enter department:");
                scanf("%s",Students[0].Department);
                checker = Searchastudent(HashTable,Hash_index,Students[0].studentID);
                if(checker > 0){
                    printf("Id should be unique!");
                    opSelectForFunctionalities = 5;
                    studentCounter -= 1;
                }
                if(opSelectForFunctionalities == 1){
                switch(opSelectForAdressing){
                    case 1:
                        key = (Students[0].studentID[0] - 65) + (Students[0].studentID[1] - 48) + (Students[0].studentID[2] - 48);
                        doubleHashing(HashTable,&Students[0],key,Hash_index);
                        printf("\n%s has been registered.\n",Students[0].Name);
                        free(Students);
                        break;
                    case 2:
                        key = (Students[0].studentID[0] - 65) + (Students[0].studentID[1] - 48) + (Students[0].studentID[2] - 48);
                        quadraticProbing(HashTable,&Students[0],key,Hash_index);
                        printf("\n%s has been registered.\n",Students[0].Name);
                        free(Students);
                        break;
                    }
                }
                break;
            case 2:
                printf("\nEnter unique identifier:");
                scanf("%s",ID);
                checker=Searchastudent(HashTable,Hash_index,ID);
                if (checker > -1){
                    printf("Name:%s\n",HashTable[checker].Name);
                    printf("Department:%s\n",HashTable[checker].Department);
                }
                else{
                    printf("Student is not found!");
                }
                break;
            case 3:
                print_Hash(HashTable,Hash_index);
                break;
        }
        loadFactor = (studentCounter + 0.0) / (Hash_index + 0.0);
        if(loadFactor > 0.5){
            Hash_index = (Hash_index * 2) + 1;
            HashTable = reHash(HashTable,Hash_index,opSelectForAdressing);
            create_HashTable(HashTable,Hash_index);
        }
        menu_functionalities();
        scanf("%d",&opSelectForFunctionalities);
    }
    printf("\t\t-----------------Final Version of Your Hash Table-------------------\t\t\n");
    print_Hash(HashTable,Hash_index);
    return 0;


}