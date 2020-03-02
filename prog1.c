#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DATASIZE 3

typedef struct Packet{

    int seqno;
    char data[DATASIZE+1];

}pack;

pack *read,*trans;

int divide(char *msg){

    int i,j,np,mlen;
    mlen=strlen(msg);
    np=mlen/DATASIZE;
    if((mlen%DATASIZE)!=0)
        np++;
    read=(pack *)malloc(sizeof(pack)*np);

    for(i=0;i<np;i++){
        read[i].seqno=i;
        for(j=0;j<DATASIZE && *msg!='\0';j++,msg++)
            read[i].data[j]=*msg;
        read[i].data[j]='\0';
    }

    printf("Message has been divided in the following order:\n");
    printf("\tSequenceNumber\tData\n");
    for(i=0;i<np;i++)
        printf("\t           %d\t%s\n",read[i].seqno,read[i].data);
    return np;
}

void shuffle(int np){

    int *st;
    int i,tran;
    srand(time(0));
    st=(int *)calloc(np,sizeof(int));
    trans=(pack *)malloc(sizeof(pack)*np);

    for(i=0;i<np;){
        tran=rand()%np;
        if(st[tran]!=1){
            trans[i].seqno=read[tran].seqno;
            strcpy(trans[i].data,read[tran].data);
            st[tran]=1;
            i++;
        }

    }
    free(st);
}

void sortpackets(int np){

    int i,j;
    pack temp;

    for(i=0;i<np;i++){

        for(j=0;j<np-(i+1);j++){

            if(trans[j].seqno>trans[j+1].seqno){
                temp.seqno=trans[j].seqno;
                strcpy(temp.data,trans[j].data);
                trans[j].seqno=trans[j+1].seqno;
                strcpy(trans[j].data,trans[j+1].data);
                trans[j+1].seqno=temp.seqno;
                strcpy(trans[j+1].data,temp.data);
            }
        }
    }

}

void receive(int np){
    int i;

    printf("The packets  are received in the following order\n");
     printf("\tSequenceNumber\tData\n");
    for(i=0;i<np;i++)
        printf("\t           %d\t%s\n",trans[i].seqno,trans[i].data);
    sortpackets(np);
    printf("the Packets after sorting\n");
    for(i=0;i<np;i++)
        printf("\t           %d\t%s\n",trans[i].seqno,trans[i].data);
    sortpackets(np);
    printf("The received message is:\n");
    for(i=0;i<np;i++)
        printf("%s",trans[i].data);
}


int main()
{
    int np;
    char msg[100];
    printf("Enter the message\n");
    scanf("%[^\n]",msg);
    np=divide(msg);
    shuffle(np);
    receive(np);
    free(read);
    free(trans);
    return 0;
}
