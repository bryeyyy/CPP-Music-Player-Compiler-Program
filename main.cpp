#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include <windows.h> //must enable libwnmm.a in IDE linker settings
#include <MMSystem.h>
using namespace std;
struct Node{
   string data;
   struct Node *next;
   struct Node *prev;
};
struct Node* head  = NULL;
void color(int num){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), num);
//1: Blue  2: Green  3: Cyan  4: Red  5: Purple  6: Yellow (Dark)
//7: Default white  8: Gray/Grey  9: Bright blue  10: Bright green
//11: Bright cyan  12: Bright red  13: Pink/Magenta  14: Yellow  15: Bright white
}
void addtothefront(Node** head, string newdata){
    Node* newnode = new Node();
    newnode->data = newdata;
    newnode->next = (*head);
    newnode->prev = NULL;
    if ((*head) != NULL)
        (*head)->prev= newnode;
    (*head)=newnode;
}
void deletenode(Node** head, Node* del){
    if (*head == NULL || del == NULL)
        return;
    if (*head == del)
        *head =del->next;
    if (del->next != NULL)
        del->next->prev = del->prev;
    if (del->prev != NULL)
        del->prev->next = del->next;
    free(del);
}
void delatgivenpos(Node** head, int x){
    if (*head == NULL || x <= 0)
        return;
    Node* current = *head;
    for (int i=1; current != NULL && i < x; i++)
        current=current->next;
    if (current==NULL)
        return;
        deletenode(head, current);
}
void printdll(Node* ptr){
    int i=0;
   if (ptr == NULL){
        cout<<"You have no files."<<endl;
   }
   while(ptr != NULL) {
        i++;
        color(15);
      cout<<"\n["<<i<<"]  "<< ptr->data <<" ";
      ptr = ptr->next;
   }
}
void view(Node **head, string data, int x){
        if (*head == NULL){
            color(12);
           cout<<"No files added. Return to Main Menu and add some files."<<endl;
        }
    Node* current = *head;
    int i;
    for (int i=1; current != NULL && i < x; i++)
        current=current->next;
    if (current==NULL){
            color(12);
            cout<<"You've reached the last file."<<endl;
            _Exit(0);
    }
        data=current->data;
        LPCTSTR filename = data.c_str();
        color(3);
        cout<<"Now Playing : "<<filename<<endl;
        PlaySound(TEXT(filename) , NULL , SND_ASYNC);
}
void vx(Node **head){
       PlaySound(NULL, 0, 0);
}
int findSize(struct Node *head){
   int res = 0;
   while (head != NULL)
   {
       res++;
       head = head->next;
   }
   return res;
}
void playall(Node **head, string data){
    int sizedll=findSize(*head);
    int flag=0;
     Node* current = *head;
                if (current==NULL){
                                    color(12);
                                    cout<<"You have no files."<<endl;
                    }
                else{
                        do{
                        data=current->data;
                        LPCTSTR filename = data.c_str();
                        color(3);
                        cout<<"Now Playing : "<<"["<<flag<<"]"<<filename<<endl;
                        PlaySound(TEXT(filename) , NULL , SND_SYNC) ;
                        PlaySound(NULL, 0, 0);
                        cout<<endl;
                        current=current->next;
                        flag ++;
                    }while (flag!=sizedll);
                }
}
int partition_Str(string arr[], int low, int high){
    string pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high- 1; j++)
    {
        if (arr[j]<=pivot){
            i++;
            string temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    string temp = arr[i+1];
    arr[i+1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}
void quickSort_Str(string arr[], int low, int high){
    if (low<high)
        {
        int pi = partition_Str(arr, low, high);
        quickSort_Str(arr, low, pi - 1);
        quickSort_Str(arr, pi + 1, high);
        }
}
void revtravlist(Node*ptr){
    struct Node* current=head;
    struct Node* last=NULL;
      if (current == NULL){
        color(12);
        cout<<"You have no files."<<endl;
   }
    while (current != NULL)
    {
        current->prev=current->next;
        current->next=last;
        last=current;

        current=current->prev;
    }
    head=last;
    printdll(head);
}
void arraysort(Node* head){
    int len = findSize(head);
    string arr[len];
    int index = 0;
    Node* current = head;
    while (current != NULL) {
        arr[index++] = current->data;
        current = current->next;
    }
    quickSort_Str(arr, 0, len-1);
        int i;
    while (head != NULL){
        i=1;
        delatgivenpos(&head, i);
        i++;
    }
     for (int i = 0; i < len; i++){
        addtothefront(&head, arr[i]);
     }
    revtravlist(head);
}
int search(Node** head, string z)
{

    Node* temp = *head;

    int pos = 0;

    while (temp->data != z
           && temp->next != NULL) {

        pos++;

        temp = temp->next;
    }


    if (temp->data != z){
            color(12);
        cout<<z<<" was not found on the list."<<endl;
        return -1;}


    cout<<z<<" was found on the list."<<endl;
    LPCTSTR filename = z.c_str();
    color(3);
    cout<<"Now Playing : "<<filename<<endl;
    PlaySound(TEXT(filename) , NULL , SND_ASYNC);
    return (pos + 1);
}
int main (){
   string z;
   int a, b, w, v;
   color(14);
   cout<<"|||||||||||||||||||||||||||||||||||||||||||\n|||||||||||| Wave File Player |||||||||||||\n|||||||||||||||||||||||||||||||||||||||||||"<<endl;
   do
   {
       g:
        color(11);
       cout<<"MAIN MENU\n\nChoose an Option"<<endl;
       cout<<" (1) Add a file \n (2) View Files \n (3) Delete Files \n (4) Play all \n (5) End Program"<<endl;
       cin>>a;
       switch (a)
       {
       case 1:
            cin.ignore();
            color(2);
            cout<<"Enter the file name. Place the file in to the root folder."<<endl;
            getline(cin, z);
                        if (z.find(".wav") != string::npos)
                            {
                                addtothefront(&head, z);
                                color(3);
                                cout<<"File has been added. \n\n"<<endl;
                            }
                        else
                            {
                                color(12);
                                cout<<"This program only accepts files with .wav\nReturning to Main Menu\n\n"<<endl;
                                goto g;
                            }
            break;
       case 2:
           color(15);
           cout<<"Arrange by: \n (1) Most recent files added first \n (2) Sort Alphabetically \n (3) Search and View "<<endl;
            cin>>w;
            switch (w){
            case 1:
                color(3);
                cout<<"Your files arranged from most recent: \n"<<endl;
                if (head==NULL){
                    color(12);
                    cout<<"You have no files.\nReturning to Main Menu\n"<<endl;
                    goto g;
                }
                else{
                    printdll(head);
                    goto h;
                }
                break;
            case 2:
                cout<<" Your files sorted alphabetically: \n"<<endl;
                 if (head==NULL){
                    color(12);
                    cout<<"You have no files.\nReturning to Main Menu\n"<<endl;
                    goto g;
                }
                else{
                arraysort(head);
                goto h;
                }
                break;
            case 3:
                cout<<"Looking for?"<<endl;
                cin>>z;
                cout<<endl;
                search(&head, z);
                goto g;
                break;
            default:
                color(12);
                cout<<"Not a valid action. "<<endl;
                goto g;
                break;
            }
            h:
            color(2);
            cout<<"\n\nEnter the number of the file you want to view: "<<endl;
            cin>>b;
            view(&head, z, b);
            do{
            color(11);
            cout<<"\nChoose and action"<<endl;
            cout<<" (1) Next \n (2) Previous \n (3) Stop and Return to Main Menu"<<endl;
            cin>>w;
                switch (w){
                case 1:
                    vx(&head);
                    v=b+1;
                    view(&head, z, v);
                    b=v;
                    break;
                case 2:
                    vx(&head);
                    v=b-1;
                    view(&head, z, v);
                    b=v;
                    break;
                case 3:
                    vx(&head);
                    break;
                default:
                    color(12);
                    cout<<"Not a valid action."<<endl;
                    break;
                }
            } while (w!=3);
            break;
       case 3:
            if (head==NULL){
                    color(12);
                        cout<<"You have no files.\nReturning to Main Menu\n"<<endl;
                    goto g;
                }
                else{
                    printdll(head);
                    color(12);
                    cout<<"\nDelete at a given Position : "<<endl;
                    cin>>b;
                    delatgivenpos(&head, b);
                }
            break;
        case 4:
            color(9);
            cout<<"Now playing all your files:\n"<< endl;
            playall(&head,z);
            break;
        case 5:
            color(12);
            cout<<"Program Ended. Thank You ^_^"<<endl;
            break;
        default:
            color(12);
            cout<<"Not a valid action"<<endl;
            break;
       }
   }while (a!=5);
return 0;
}
