#include "queue.h"
#include "stack.h"

#define N 9
#define TIME 1000

int pins[N] = {12,10,9,11,5,8,7,6,4};//DEPENDS ON THE CIRCUIT DESING
void end_anim();
void blink_led(int v);
int create_map_and_aux(int**d_map,int **aux,int size);
void bft(int g[][N],int s);
void dft(int g[][N],int s);
void setup() {
  int i;
  for(i=0;i<N;i++)
    pinMode(pins[i],OUTPUT);
    
  int adjMatrix[N][N] = {
//    0  1  2  3  4  5  6  7  8
/*0*/{0, 1, 0, 1, 1, 0, 0, 0, 0},
/*1*/{0, 0, 1, 0, 1, 0, 0, 0, 0},
/*2*/{0, 0, 0, 0, 0, 1, 0, 0, 0},
/*3*/{0, 0, 0, 0, 1, 0, 1, 0, 0},
/*4*/{0, 0, 0, 0, 0, 1, 0, 0, 0},
/*5*/{0, 0, 0, 0, 0, 0, 0, 0, 0},
/*6*/{0, 0, 0, 0, 1, 0, 0, 1, 0},
/*7*/{0, 0, 0, 0, 0, 1, 0, 0, 1},
/*8*/{0, 0, 0, 0, 0, 0, 0, 0, 0},
  };
  delay(TIME);
  for(i=0;i<N;i++){//run the simulation for each node 1 by 1
    bft(adjMatrix,i);
    delay(TIME/2);
    end_anim();
    delay(TIME * 2);
    dft(adjMatrix,i);
    delay(TIME/2);
    end_anim();
    delay(TIME*5);
  }
}

void loop(){
}

void end_anim(){
  int i,j;
  delay(TIME/2);
  for(i=0;i<5;i++){//blink all at once 3 times
    for(j=0;j<N;j++){
      digitalWrite(pins[j],0);
    }
    delay(TIME/10);
    for(j=0;j<N;j++){
      digitalWrite(pins[j],1);
    }
    delay(TIME/10);
  }
  for(i=0;i<N;i++){
    digitalWrite(pins[i],0);
  }
}

void blink_led(int v){
  int i;
  delay((TIME/4)*3);
  for(i=0;i<v;i++){
    digitalWrite(pins[v],1);
    delay(((TIME/4)*3)/10);
    digitalWrite(pins[v],0);
    delay(((TIME/4)*3)/10);
  }
  digitalWrite(pins[v],1);
}

int create_map_and_aux(int**d_map,int **aux,int size){
  int i;
  int *a = malloc(size*sizeof(int));
  int *d = calloc(size,sizeof(int));//allocates and sets all elements to 0

  if(d==NULL||a==NULL)
    return -1;
  for(i=0;i<size;i++){
    a[i]=i;
  }

  *aux = a;
  *d_map = d;

  return 1;
}

void bft(int g[][N],int s){
  LINKED_QUEUE LQ = linked_queue_init();
  int v=0,w,*d_map,*auxillary;
  //I am using an auxillary array to hold the vertex values in integer form.
  //As we are passing them to a void * the other method of creating a int tmp for every vertex is a bit painful
  //Also if we directly insert w to our structure it will get the same variable's address over and over again
  
  if(create_map_and_aux(&d_map,&auxillary,N)==-1)//Null Check inside
    exit(-99);
  linked_queue_enqueue(LQ,&auxillary[s]);
  d_map[s]=1;

  while(!linked_queue_is_empty(LQ)){
    v = *(int *)linked_queue_dequeue(LQ);
    blink_led(v);
    for(w=0;w<N;w++){
      if(g[v][w]==1){
        if(d_map[w]!=1){
          linked_queue_enqueue(LQ,&auxillary[w]);
          d_map[w]=1;
        }
      }
    }

  }
  free(auxillary);
  free(d_map);
  linked_queue_free(LQ);
}




void dft(int g[][N],int s){
  LINKED_STACK LS = linked_stack_init();
  int v=0,w=0,*d_map,*auxillary;
  //I am using an auxillary array to hold the vertex values in integer form.
  //As we are passing them to a void * the other method of creating a int tmp for every vertex is a bit painful
  //Also if we directly insert w to our structure it will get the same variable's address over and over again which won't work

  if(create_map_and_aux(&d_map,&auxillary,N)==-1)//Null Check inside
    exit(-101);

  linked_stack_push(LS,&auxillary[s]);
  d_map[s]=1;

  while(!linked_stack_is_empty(LS)){
    v = *(int *)linked_stack_pop(LS);
    blink_led(v);
    for(w=0;w<N;w++){
      if(g[v][w]==1){
        if(d_map[w]!=1){
          linked_stack_push(LS,&auxillary[w]);
          d_map[w]=1;
        }
      }
    }
  }
  free(auxillary);
  free(d_map);
  linked_stack_free(LS);
}
