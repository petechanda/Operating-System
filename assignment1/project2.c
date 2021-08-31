//ref https://github.com/salilchhabra/multithreading-sorting-applications/blob/master/multithreading%20sorting%20application.c
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#define num 10
int array_ptr[num] = {7,12,19,3,18,4,2,6,15,8};
int temp[10];
int c[5],d[5];
int low=0,high=9,high1=4;
void *run(void *array_ptr);
void *run1(void *array_ptr);


void sort(int low, int mid, int high1) {
    int l1, l2, i;

    for(l1 = low, l2 = mid + 1, i = low; l1 <= mid && l2 <= high1; i++) {
        if(c[l1] <= c[l2])
            d[i] = c[l1++];
        else
            d[i] = c[l2++];
    }
   
    while(l1 <= mid)    
        d[i++] = c[l1++];

    while(l2 <= high1)   
        d[i++] = c[l2++];

    for(i = low; i <= high1; i++){
	    c[i] = d[i];
    }
	  
}

void mergesort(int low,int high1) {
    int mid;
   	int *elements = (int*)c; 
   	
    if(low < high1) {
        mid = (low + high1) / 2;
        mergesort(low, mid);
        mergesort(mid+1, high1);
        sort(low, mid, high1);
    } 
    else { 
        return;
    }   
}

int c1[5],d1[5];
void *merging(void * array_ptr)
{
	int id1 = 0;
    int id2 = 0;
    int k=0;
    int m=5,n=5;
    while (id1 < m && id2 < n) {
        if (c1[id1] <d1[id2]) {
            temp[k] = c1[id1];
            id1++;
        }
        else {
            temp[k] = d1[id2];
            id2++;
        }
        k++;
    }
    if (id1 >= m) {  //arrayแรกเช็คครบทุกตัวแล้ว เอาข้อมูลในarrayที่สองมาใส่ในtemp
        while (id2 < n) {
            temp[k] = d1[id2];
            id2++;
            k++;
        }
    }
    if (id2 >= n) {   //arrayที่สองเช็คครบทุกตัวแล้ว เอาข้อมูลในarrayแรกมาใส่ในtemp
        while (id1 < m){
            temp[k] = c1[id1];
            id1++;
            k++;
        }
    }
    printf("\n After merging: \n"); //แสดงtemp : array ที่ sortแล้ว
	for (id1 = 0; id1 < m + n; id1++) {
        printf("\n%d", temp[id1]);
    }
}

int main(){
	for(int i=0;i<5;i++){
	    c[i]=array_ptr[i]; //ดึงจากinput 5ตัวแรก
	}
	printf("\n 2 sorted subarray are:\n ");
	pthread_t t1,t2,t3;
	pthread_create(&t1, NULL, run, (void *)c);
    pthread_join( t1,NULL);

    for(int i=0;i<5;i++){
        printf("%d\t",c[i]);
        c1[i]=c[i]; //input 5 ตัวแรกที่ sortแล้ว
    }
    printf("\n");

    for(int i=0;i<5;i++){
		c[i]=array_ptr[i+5]; //input 5 ตัวหลัง
	}
 	pthread_create(&t2, NULL, run, (void *)c);
    pthread_join( t2,NULL);
    
    for(int i=0;i<5;i++){
        printf("%d\t",c[i]);
        d1[i]=c[i]; //input 5 ตัวหลังที่ sortแล้ว
    }
 	pthread_create(&t3, NULL, merging,(void*)array_ptr);
    pthread_join( t3,NULL);
}

void *run(void *c){
	mergesort(low,high1);
}