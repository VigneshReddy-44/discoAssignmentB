#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int factorial(int n){
    if(n==1){
        return 1;
    }else{
        return n* factorial(n-1);
    }
}
int* sequencePermutationGenerator(int* sequence,int n){

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
void calculateDegreeCount(int *adj_matrix,int nodes,int *degreeCount){
    for(int i=0;i<nodes;i++){
        int * rowi=adj_matrix+(i*nodes);        //pointer to ith row
        int deg=0;
        for(int j=0;j<nodes;j++){

            if(rowi[j]==1){
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


    int* adj_matrix1=(int *)malloc((nodes1*nodes1)*sizeof (int));
    for(int i=0;i<edges1;i++){
        int ver1;
        int ver2;


        fscanf(input1,"%d %d",&ver1,&ver2);
        adj_matrix1[(ver1-1)*nodes1+(ver2-1)]=1;   // assigning edges in the adjacency matrix
        adj_matrix1[(ver2-1)*nodes1+(ver1-1)]=1;

    }




    int *degreeCount1=(int *) malloc(nodes1*sizeof (int));
    calculateDegreeCount(adj_matrix1,nodes1,degreeCount1);
    sortArray(degreeCount1,nodes1);


    fscanf(input2,"%d",&nodes2);
    fscanf(input2,"%d",&edges2);


    int* adj_matrix2=(int *)malloc((nodes2*nodes2)*sizeof (int));
    for(int i=0;i<edges2;i++){
        int ver1;
        int ver2;


        fscanf(input2,"%d %d",&ver1,&ver2);
        adj_matrix2[(ver1-1)*nodes2+(ver2-1)]=1;   // assigning edges in the adjacency matrix
        adj_matrix2[(ver2-1)*nodes2+(ver1-1)]=1;

    }




    int *degreeCount2=(int *) malloc(nodes2*sizeof (int));
    calculateDegreeCount(adj_matrix2,nodes2,degreeCount2);
    sortArray(degreeCount2,nodes2);


    if(nodes1!=nodes2 || edges1!=edges2 || (checkDegreeSequence(degreeCount1,degreeCount2,nodes1)==0)){
        printf("Not Isomorphic");
    }else{
        int* nodeSequence=(int*) malloc(nodes1*sizeof (int));
        for(int i=0;i<nodes1;i++){
            nodeSequence[i]=i+1;
        }
        int* permutations=(int *) malloc(factorial(nodes1)*sizeof(int));

        free((void*)nodeSequence);

    }

    free((void *)degreeCount1);
    free((void *)adj_matrix1);
    fclose(input1);
    free((void *)degreeCount2);
    free((void *)adj_matrix2);

    fclose(input2);
}
