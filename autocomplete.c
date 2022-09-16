#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "autocomplete.h"

int my_strcmp(const void *str1, const void *str2){
    return (strcmp(str1,str2));
}

void read_in_terms(struct term **terms, int *pnterms, char *filename){
    char line[200];
    FILE *fp = fopen(filename, "r");

    fgets(line, sizeof(line), fp);
    *pnterms = atoi(line);
   
    *terms = (struct term *)malloc(sizeof(struct term) * (*pnterms)); //make for enough space

    for (int i = 0; i < *pnterms; i++){
        //read file line by line
        fgets(line, sizeof(line), fp);
        
        //split string and store info into terms
        const char s[3] = "\t";
        char *token = strtok(line, s);//weight
        (*terms)[i].weight = atof(token);

        const char t[3] = "\n";
        token = strtok('\0', t);//term
        strcpy((*terms)[i].term, token);
    }
    qsort(*terms, *pnterms, sizeof(struct term), my_strcmp);
}



int lowest_match(struct term *terms, int nterms, char *substr){
    /*The function returns the index in terms of the first term in lexicographic ordering that matches the string substr.
        Assume that terms is sorted in ascending lexicographic ordering.
        */
    int index_front = 0;
    int index_back = nterms -1;
    int k = nterms/2;

    //find an index that matches the term
    while(strncmp(((terms)[k].term), substr, strlen(substr)) != 0 ){
        if (strncmp(substr, (terms)[k].term, strlen(substr)) < 0){
            index_back = k;
        }else if(strncmp(substr, (terms)[k].term, strlen(substr)) > 0){
            index_front = k;
        }

        if ((index_back - index_front == 1) && (index_back == nterms - 1)){
            k = index_back;
        }else{
            k = index_front + (index_back - index_front)/2;
        }
        if(index_front == index_back){
            return (-1);
        }
    }
    
    //find the lowest match
    while(strncmp(substr, (terms)[k].term, strlen(substr)) == 0){
        k --;
    }  
    return(k+1);
}

int highest_match(struct term *terms, int nterms, char *substr){
    /*The function returns the index in terms of the last term in lexicographic order that matches the string substr.
       Assume that terms is sorted in ascending lexicographic ordering.
        */
    int index_front = 0;
    int index_back = nterms -1;
    int k = nterms/2;

    //find an index that matches the term
    while(strncmp(((terms)[k].term), substr, strlen(substr)) != 0 ){
        if (strncmp(substr, (terms)[k].term, strlen(substr)) < 0){
            index_back = k;
        }else if(strncmp(substr, (terms)[k].term, strlen(substr)) > 0){
            index_front = k;
        }

        if ((index_back - index_front == 1) && (index_back == nterms - 1)){
            k = index_back;
        }else{
            k = index_front + (index_back - index_front)/2;
        }
        if(index_front == index_back){
            return (-1);
        }
    }
    
    //find the lowest match
    while(strncmp(substr, (terms)[k].term, strlen(substr)) == 0){
        k ++;
    }  
    return(k-1);
}


int cmpfunc (const void * a, const void * b) {
    double a_weight = ((struct term *)a) -> weight;
    double b_weight = ((struct term *)b) -> weight;

    return (b_weight - a_weight);
}

void autocomplete(struct term **answer, int *n_answer, struct term *terms, int nterms, char *substr){
    /* The function takes terms (assume it is sorted lexicographically), the number of terms nterms, 
    and the query string substr, and 1)places the answers in answer, 2)with *n_answer being the number of answers.
    3)The answers are sorted by weight.
    */

    int index_front = lowest_match(terms, nterms, substr);
    int index_back = highest_match(terms, nterms, substr);

    if (index_front == -1 || index_back == -1){
        *n_answer = 0;
    }
    else{

        *n_answer = index_back - index_front + 1;

        *answer = (struct term *)malloc(sizeof(struct term) * (*n_answer)); //make for enough space
        for(int i = 0; i < *n_answer; i++){
            strcpy((*answer)[i].term, (terms)[index_front + i].term);
            (*answer)[i].weight = (terms)[index_front + i].weight;
        }


        qsort(*answer, *n_answer, sizeof(struct term), cmpfunc);
    }
}

 