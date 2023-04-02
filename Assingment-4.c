#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

typedef struct links{
    char data[100];
    struct links *next;
}Node;

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

Node *createScanpathList(char *filename){
    Node *head=NULL, *temp, *first, *last;
    int numberOfLines = line_counter(filename);
    FILE *infile;
    int i = 0;

    infile = fopen(filename,"r");
    for(i = 0; i < numberOfLines+1 ; i++){
        temp = (Node *)malloc(sizeof(Node));
        fscanf(infile,"%s\n", temp->data);
        temp->next = NULL;

        if(head == NULL){
            head = temp;
            first = last = temp;
        }
        else{
            last->next = temp;
            last = temp;
        }
    }
    
    return head;
}



void searchPattern(Node *peopleWithAutism, Node *peopleWithoutAutism, char *pattern){//Rabin-Karp Algorithm
    int d=10,q=11;
    Node *tempWithAutism = peopleWithAutism;
    Node *tempWithoutAutism = peopleWithoutAutism;
    char swap[2];
    int index_Without=0;
    int index_With=0;

    while (tempWithAutism != NULL){
        int m_tempwithAutism = strlen(tempWithAutism->data);
        int k_pat = strlen(pattern);
        int index=0;
        int checker=0;

        int h_pat = pow(d,k_pat-1);
        h_pat = h_pat % q;
        int p_pat = 0;
        int t_tempwithAutism = 0;
        int t_tempwithoutAutism = 0;
        char container[100];
        strcpy(container,tempWithAutism->data);

        int i,j,k;

        for(i = 0;i < k_pat ; i++){
            p_pat = (d*p_pat + pattern[i]) % q;
            t_tempwithAutism = (d*t_tempwithAutism + tempWithAutism->data[i]) % q;
        }
        if(tempWithAutism != NULL){
            for(j = 0; j <= m_tempwithAutism - k_pat;j++){
                if(p_pat == t_tempwithAutism){
                    for(i = 0 ; i < k_pat ; i++){
                        if(tempWithAutism->data[j+i] != pattern[i]){
                            break;
                        }
                    }
                    if(i == k_pat){
                        if(checker>0){
                            j=j+2;
                        }
                        index = j;
                        for(k=strlen(container);k>index-1;k--){
                            container[k+1]=container[k];
                        }
                        container[index]='[';

                        index = j+strlen(pattern)+1;
                        for(k=strlen(container);k>index-1;k--){
                            container[k+1]=container[k];
                        }
                        container[index]=']';
                        checker++;
                    }
                }
                if(j < m_tempwithAutism - k_pat){
                    t_tempwithAutism = (d*(t_tempwithAutism - tempWithAutism->data[j]*h_pat) + tempWithAutism->data[j+k_pat])%q;

                    if(t_tempwithAutism < 0){
                        t_tempwithAutism = t_tempwithAutism + q;
                    }
                }

            }
        }
        strcpy(tempWithAutism->data,container);
        tempWithAutism = tempWithAutism->next;
        index_With ++ ;
        memset(container, '\0' , strlen(container));
    }


    while(tempWithoutAutism != NULL){
        int n_tempWithoutAutism = strlen(tempWithoutAutism->data);
        int k_pat = strlen(pattern);
        int index = 0;
        int checker = 0;

        int j,i,k;

        int h_pat = pow(d,k_pat-1);
        h_pat = h_pat % q;
        int p_pat = 0;
        int t_tempwithoutAutism = 0;
        char container[100];
        strcpy(container,tempWithoutAutism->data);

        for(i = 0;i < k_pat ; i++){
            p_pat = (d*p_pat + pattern[i]) % q;
            t_tempwithoutAutism = (d*t_tempwithoutAutism + tempWithoutAutism->data[i]) % q;
        }
        if(tempWithoutAutism != NULL){
            for(j = 0; j <= n_tempWithoutAutism - k_pat;j++){
                if(p_pat == t_tempwithoutAutism){
                    for(i = 0 ; i < k_pat ; i++){
                        if(tempWithoutAutism->data[j+i] != pattern[i]){
                            break;
                        }
                    }
                    if(i == k_pat){
                        if(checker>0){
                            j=j+2;
                        }
                        index = j;
                        for(k=strlen(container);k>index-1;k--){
                            container[k+1]=container[k];
                        }
                        container[index]='[';

                        index = j+strlen(pattern)+1;
                        for(k=strlen(container);k>index-1;k--){
                            container[k+1]=container[k];
                        }
                        container[index]=']';
                        checker++;
                    }
                }
                if(j < n_tempWithoutAutism - k_pat){
                    t_tempwithoutAutism = (d*(t_tempwithoutAutism - tempWithoutAutism->data[j]*h_pat) + tempWithoutAutism->data[j+k_pat])%q;

                    if(t_tempwithoutAutism < 0){
                        t_tempwithoutAutism = t_tempwithoutAutism + q;
                    }
                }
            }
        }
        strcpy(tempWithoutAutism->data,container);
        tempWithoutAutism = tempWithoutAutism->next;
        index_Without ++ ;
        memset(container, '\0' , strlen(container));
    }
}



void printer(Node *linkedlist){
    Node *temp = linkedlist;
    int printCheck = 0;
    int counter = 0;
    int patterncount = 0;
    int patterncollector[10];
    int num;
    char detect;
    int i,j,k;
    for(k=0;k<10;k++){
        patterncollector[k] = 0;
    }
    int x,y;//For finding most used AOI.
    while(temp != NULL){
        for(i=0;i<strlen(temp->data);i++){
            num = temp->data[i] - '0';
            patterncollector[num]++;
            detect = temp->data[i];
            if(detect == '['){
                if(printCheck == 0){
                    printf("\n%d. %s",counter+1,temp->data);
                }
                printCheck++;
                patterncount++;
            }
        }
        printCheck = 0;
        counter++;
        temp = temp->next;
    }
    if(patterncount == 0){
        printf("\nNone.");
    }
    else if(patterncount > 0){
        x = patterncollector[0];
        for(j = 1;j < 10;j++){
            y=patterncollector[j];
            if(y>x){
                x=j;
            }
        }
        printf("\n%d patterns detected in %d scanpaths",patterncount,counter);
        printf("\nThe most frequent AOI before the pattern is/are %d",x);
    }

}

int main(){
    char filename1[30],filename2[30],pattern[100];
    //char *deneme[] = {"6547382712384758123","3547712364687","847364537292"};
    Node *peopleWithAutism = (Node*)malloc(sizeof(Node));
    Node *peopleWithoutAutism = (Node*)malloc(sizeof(Node));
    printf("Enter the file name for people with autism:");
    scanf("%s",filename1);
    printf("Enter the file name for people without autism:");
    scanf("%s",filename2);
    printf("Enter the pattern:");
    scanf("%s",pattern);
    peopleWithAutism = createScanpathList(filename1);
    peopleWithoutAutism = createScanpathList(filename2);
    searchPattern(peopleWithAutism,peopleWithoutAutism,pattern);
    printf("\nDetected patterns for people with autism:");
    printer(peopleWithAutism);
    printf("\nDetected patterns for people without autism:");
    printer(peopleWithoutAutism);

    return 0;
}
