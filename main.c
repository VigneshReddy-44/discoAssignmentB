#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool checkEquality(int **adj1,int **adj2,int nodes){
    for(int i=0;i<nodes;i++){
        for(int j=0;j<nodes;j++){
            if(adj1[i][j]!=adj2[i][j]){
                return false;
            }
        }
    }
    return true;
}

bool permutedMatrix(int* sequence,int nodes,int** adjMatrix1,int **adjMatrix2){

    int** tempMatrix2=(int **)malloc((nodes)*sizeof (int*));
    for(int i=0;i<nodes;i++){
        tempMatrix2[i]= (int *)malloc(sizeof (int)*nodes);
    }
    for(int i=0;i<nodes;i++){

        for(int j=0;j<nodes;j++){
            tempMatrix2[i][j]=adjMatrix2[sequence[i]-1][sequence[j]-1];
        }

    }
    bool b=checkEquality(adjMatrix1,tempMatrix2,nodes);



    for(int i=0;i<nodes;i++){
        free(tempMatrix2[i]);

    }
    free(tempMatrix2);
    return b;
}

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void permute(int **results, int *a, int l, int r, int *count) {
    int i;
    if (l == r) {

        for (i = 0; i <= r; i++)
            results[*count][i] = a[i];
        (*count)++;
    } else {
        for (i = l; i <= r; i++) {
            swap((a + l), (a + i));
            permute(results, a, l + 1, r, count);
            swap((a + l), (a + i)); //backtrack
        }
    }
}



int factorial(int n){
    if(n==1){
        return 1;
    }else{
        return n* factorial(n-1);
    }
}

int checkDegreeSequence(int *degreeCount1,int *degreeCount2,int n){
    for(int i=0;i<n;i++){
        if(degreeCount1[i]!=degreeCount2[i]){
            return 0;
        }
    }
    return 1;
}
void sortArray(int *a,int size){ //sort degree count
    for(int i=0;i<size;i++){
        for(int j=i+1;j<size;j++){
            if(a[j]>a[i]){
                int t=a[j];
                a[j]=a[i];
                a[i]=t;
            }
        }
    }
}
void calculateDegreeCount(int **adj_matrix,int nodes,int *degreeCount){
    for(int i=0;i<nodes;i++){
        //pointer to ith row
        int deg=0;
        for(int j=0;j<nodes;j++){

            if(adj_matrix[i][j]==1){
                if(j==i){   // self loop condition
                    deg+=2;
                }else{
                    deg+=1; // not self loop
                }
            }

        }

        degreeCount[i]=deg;

    }
}


int main(int argc,char *argv[]) {
    int nodes1,edges1,nodes2,edges2;
    FILE *input1= fopen(argv[1],"r");
    FILE *input2= fopen(argv[2],"r");
    fscanf(input1,"%d",&nodes1);
    fscanf(input1,"%d",&edges1);


    int** adj_matrix1=(int **)malloc((nodes1)*sizeof (int*));
    for(int i=0;i<nodes1;i++){
        adj_matrix1[i]= (int *)malloc(sizeof (int)*nodes1);
    }
    for(int i=0;i<edges1;i++){
        int ver1;
        int ver2;


        fscanf(input1,"%d %d",&ver1,&ver2);
        adj_matrix1[(ver1-1)][(ver2-1)]=1;   // assigning edges in the adjacency matrix
        adj_matrix1[(ver2-1)][(ver1-1)]=1;

    }




    int *degreeCount1=(int *) malloc(nodes1*sizeof (int));
    calculateDegreeCount(adj_matrix1,nodes1,degreeCount1);
    sortArray(degreeCount1,nodes1);


    fscanf(input2,"%d",&nodes2);
    fscanf(input2,"%d",&edges2);


    int** adj_matrix2=(int**)malloc((nodes2)*sizeof (int*));
    for(int i=0;i<nodes2;i++){
        adj_matrix2[i]= (int *)malloc(sizeof (int)*nodes2);
    }
    for(int i=0;i<edges2;i++){
        int ver1;
        int ver2;


        fscanf(input2,"%d %d",&ver1,&ver2);
        adj_matrix2[(ver1-1)][(ver2-1)]=1;   // assigning edges in the adjacency matrix
        adj_matrix2[(ver2-1)][(ver1-1)]=1;

    }




    int *degreeCount2=(int *) malloc(nodes2*sizeof (int));
    calculateDegreeCount(adj_matrix2,nodes2,degreeCount2);
    sortArray(degreeCount2,nodes2);


    if(nodes1!=nodes2 || edges1!=edges2 || (checkDegreeSequence(degreeCount1,degreeCount2,nodes1)==0)){
        printf("Not Isomorphic. No bijection found");
    }else{

        int* nodeSequence=(int*) malloc(nodes1*sizeof (int));
        for(int i=0;i<nodes1;i++){
            nodeSequence[i]=i+1;
        }
        int n= factorial(nodes1);
        int **permutations= (int**)malloc(sizeof (int*)*n);
        for(int i=0;i<n;i++){
            permutations[i]= (int*)malloc(sizeof (int)*nodes1);
        }
        int count = 0;
        permute(permutations, nodeSequence, 0, nodes1 - 1, &count);
        int i=0;
        for( i=0;i<count;i++){
            int* currentSequence=permutations[i];
            if(permutedMatrix(currentSequence,nodes1,adj_matrix1,adj_matrix2)==true){
                printf("Isomorphic\n");
                for(int i=0;i<nodes1;i++){
                    printf("%d %d\n",i+1,currentSequence[i]);
                }
                break;
            }

        }
        if(i==count){
            printf("Not isomorphic. No bijection found");
        }





        for (int i = 0; i < n; i++) {
            free((void *) permutations[i]);
        }
        free((void*)permutations);
        free((void*)nodeSequence);

    }

    free((void *)degreeCount1);
    for(int i=0;i<nodes1;i++){
        free((void *)adj_matrix1[i]);

    }
    free((void *)adj_matrix1);

    for(int i=0;i<nodes2;i++){
        free((void *)adj_matrix2[i]);

    }
    free((void *)adj_matrix2);

    free((void *)degreeCount2);

    fclose(input1);
    fclose(input2);
    return 0;
}
