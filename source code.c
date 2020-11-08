#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int id;
    int quantity;
}books;
books InsertBook[50];
books sortedbook[50];
FILE *data;
int num;
void loading();
void insert();
int linesearch(int id, int i,int count);
void del();
void sort();
int namesearch(char *name);
void see();


int main()
{

    char exit;
    char bname[50];
    int Id;
    int temp;
    int menu;


        do{
        data =fopen("Database.txt","r+");
        if(data==NULL){
            printf("file not found");
        }
        else{
        loading();

            printf("\t\t---welcome---\n");
            printf("choose(1)to insert book\n");
            printf("choose(2)to delete book by id\n");
            printf("choose(3)to search for book by id\n");
            printf("choose(4)to search for book by name \n");
            printf("choose(5)to show books sorted by name\n");
            printf("choose(6)to show books unsorted\n");

            scanf("%d",&menu);
            switch(menu){
                case 1:
                    printf("book id: ");
                    scanf("%d",&InsertBook[num].id);
                    printf("book name: ");
                    scanf(" %[^\n]s",InsertBook[num].name);
                    printf("book quantity: ");
                    scanf("%d",&InsertBook[num].quantity);
                    insert();
                    break;
                case 2:
                    printf("enter id ");
                    scanf("%d",&Id);
                    temp=linesearch(Id,0,0);
                    if(temp==-1){
                        printf("id not found\n");
                    }
                    else {
                        del(Id);
                    }
                    break;

                case 3:
                    printf("enter id ");
                    scanf("%d",&Id);
                    temp=linesearch(Id,0,0);
                    if(temp==-1) {
                        printf("this book not exist yet\n");
                    }
                    else{
                        printf("name:%s\n", InsertBook[temp].name);
                        printf("quantity:%d\n", InsertBook[temp].quantity);
                    }
                    break;

                case 4:
                    sort();
                    printf("enter book name: ");
                    scanf(" %[^\n]s",bname);
                    temp=namesearch( bname);
                    if (temp==-1){
                        printf("not found \n");
                    }
                    else{
                        printf("book id:%d\nbook quantity:%d\n",sortedbook[temp].id,sortedbook[temp].quantity);
                    }
                    break;
                case 5:
                    sort();
                    see(sortedbook);
                    break;
                case 6:
                    see(InsertBook);
                    break;
                default:
                    printf("out of range");
                    break;
            }
            printf("do you want to do anything else ");
            scanf(" %c",&exit);
fclose(data);

        }
        }
while(strcmp(exit,"yes")==0||strcmp(exit,"Yes")==0);

    return 0;
}
void loading(){
    num=0;
    while(!feof(data)){
            fscanf(data, "%d\t", &InsertBook[num].id);
            fscanf(data, "%[^\t]s", InsertBook[num].name);
            fscanf(data, "%d\n", &InsertBook[num].quantity);
            num++;
        }

}
void insert(){
    fprintf(data,"%d\t",InsertBook[num].id);
    fprintf(data,"%s\t",InsertBook[num].name);
    fprintf(data,"%d\n",InsertBook[num].quantity);
    num++;
}
void del(int id){
    FILE  *dldat;
    dldat =fopen("Database.txt","w");
    int i,temp;
    for(i=0;i<num;i++){
        if(id==InsertBook[i].id){
            break;
        }}
    temp=num;
    while(i<temp){
        strcpy(InsertBook[i].name,InsertBook[i+1].name);
        InsertBook[i].id=InsertBook[i+1].id;
        InsertBook[i].quantity=InsertBook[i+1].quantity;
        i++;
    }
    fseek(data,0,SEEK_SET);
    for(num=0;num<temp-1;) {
        insert();
    }
    fclose(dldat);
}

int linesearch(int id,int i,int count){
    if(InsertBook[i].id==id){
        return count;
    }
    else {
        if(i>=num){
            return -1;
        } else {
            linesearch(id, i += 1, count += 1);
        }
    }
}
int namesearch(char *name){
    int low=0,max=num,mid;
    while (low<=max){
        mid=(low+max)/2;
        if(strcmp(name,sortedbook[mid].name)==0){
            return mid;
        }
        else if(strcmp(name,sortedbook[mid].name)<0){
            max=mid-1;
        }
        else if(strcmp(name,sortedbook[mid].name)>0) {
            low = mid + 1;
        }

    }
    return -1;
}
void sort(){

    int pass,i,tempid=0,tempqun=0;
    char temp[50];
    for(i=0;i<num;i++){
        strcpy(sortedbook[i].name,InsertBook[i].name);
        sortedbook[i].id=InsertBook[i].id;
        sortedbook[i].quantity=InsertBook[i].quantity;
    }
    for(pass=0;pass<num-1;pass++){
        for(i=0;i<num-1;i++){
            if(strcmp(sortedbook[i].name,sortedbook[i+1].name)>=1){
                strcpy(temp,sortedbook[i].name);
                strcpy(sortedbook[i].name,sortedbook[i+1].name);
                strcpy(sortedbook[i+1].name,temp);

                tempid=sortedbook[i].id;
                sortedbook[i].id=sortedbook[i+1].id;
                sortedbook[i+1].id=tempid;

                tempqun=sortedbook[i].quantity;
                sortedbook[i].quantity=sortedbook[i+1].quantity;
                sortedbook[i+1].quantity=tempqun;

            }
        }
    }
}
void see(books *arr){
    int u;
    for(u=0;u<num;u++){

        printf("book id:%d\n",arr[u].id);
        printf("book name:%s\n",arr[u].name);
        printf("book quantity:%d\n",arr[u].quantity);

    }
}
