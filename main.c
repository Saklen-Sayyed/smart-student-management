/***************************************************************
 * Project      : Smart Student Management System
 * File Name    : main.c
 * Description  : Menu-driven Student Record Management System 
 *                implemented in C using linked lists and file I/O.
 *                Supports CRUD operations, sorting, and persistence.
 *
 * Author       : Saklen Sayyed
 * Created On   : September 2025
 * Version      : 1.0
 *
 * Compiler     : GCC / MinGW
 * Platform     : Windows
 *
 * -------------------------------------------------------------
 * Features:
 *  - Add, insert, delete, and edit student records
 *  - Search records by name or roll number
 *  - Sort records (ascending/descending)
 *  - Reverse and midpoint record display
 *  - Save and load records from text file
 *
 * -------------------------------------------------------------
 * License:
 *  MIT License (See LICENSE file for details)
 *
 * -------------------------------------------------------------
 * Notes:
 *  This project demonstrates dynamic data handling using 
 *  singly linked lists and file-based persistence — ideal 
 *  for embedded and systems programming fundamentals.
 * Author Notes:
 *	I have done this project side by side as i was learning C, 
 	It is my first programming language so there might be some 
	mistakes or code might not be that optimised i will improve 
	upon myself  
 ***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "main.h"

struct student{
	int roll;
	int math;
	int english;
	int science;
	int percentage;
	char name[NAME_SIZE];
	struct student *next;
};

struct student *head=NULL;

int main(void){
	int choice=0;
	printf("WELCOME,THIS IS THE STUDENT MANAGEMENT SYSTEM\n\n");
	speak("Welcome, This is the Student Management system");
	start:
		choice=0;
		printf("\n _______________________________________________________\n");
		printf("|                                                       |\n");
		printf("|              STUDENT MANAGEMENT SYSTEM                |\n");
		printf("|_______________________________________________________|\n");
		printf("|                                                       |\n");
		printf("|   01) Append Record.                                  |\n");
		printf("|   02) Insert Record.                                  |\n");
		printf("|   03) Display All.                                    |\n");
		printf("|   04) Edit Record.                                    |\n");
		printf("|   05) Search.                                         |\n");
		printf("|   06) Delete All.                                     |\n");
		printf("|   07) Delete.                                         |\n");
		printf("|   08) Find MidPoint.                                  |\n");
		printf("|   09) Display In Reverse.                             |\n");
		printf("|   10) Sort Record.                                    |\n");
		printf("|   11) Exit.                                           |\n");
		printf("|_______________________________________________________|\n");
		
		printf("\nENTER: ");
		
		
		scanf("%d",&choice);
		printf("===========================================================\n");
		system("cls");
		
		switch(choice){
			case 1:
				append_record();
				goto start;
			case 2:
				insert_record();
				goto start;
			case 3:
				display_all();
				goto start;
			case 4:
				edit_record();
				goto start;
			case 5:
				search_record();
				goto start;
			case 6:
				delete_all();
				goto start;
			case 7:
				delete_record();
				goto start;
			case 8:
				midpoint();
				goto start;
			case 9:
				reverse_display(head);
				goto start;
			case 10:
				sort_record();
				goto start;
			case 11:
				save_file();
				printf("Saving...\n");
				printf("Exiting....");
				speak("Thanks for using our services");
				break;
			default:
				printf("***Invalid Choice Choose Again**\n");
				goto start;
	}
}

void append_record(void){
	struct student *t=NULL;
	
	if(!head){
		head=(struct student*)malloc(sizeof(struct student));
		head->next=NULL;
		fflush(stdin);
		printf("Enter First and Last Name:");
		fgets(head->name, sizeof(head->name), stdin);
		printf("\nEnter Roll No.:");
		scanf("%d",&head->roll);
		printf("Enter Marks\nMath:");
		scanf("%d",&head->math);
		printf("Enter Marks\nEnglish:");
		scanf("%d",&head->english);
		printf("Enter Marks\nScience:");
		scanf("%d",&head->science);
		
		head->percentage=((head->math+head->english+head->science)/3);//Assuming maximum marks is hundred
		if(head->name[0]>='a' && head->name[0]<='z')
			head->name[0]=head->name[0]-32;
	}
	else{
		for(t=head;t->next;t=t->next);
		t->next=(struct student*)malloc(sizeof(struct student));
		t=t->next;
		t->next=NULL;
		fflush(stdin);
		printf("Enter First and Last Name:");
		fgets(t->name, sizeof(t->name), stdin);
		printf("Enter Roll No.:");
		scanf("%d",&t->roll);
		printf("Enter Marks\nMath:");
		scanf("%d",&t->math);
		printf("Enter Marks\nEnglish:");
		scanf("%d",&t->english);
		printf("Enter Marks\nScience:");
		scanf("%d",&t->science);
		printf("\n");
		
		t->percentage=((t->math+t->english+t->science)/3);//Assuming maximum marks is hundred
		
		if(t->name[0]>='a' && t->name[0]<='z') //Uppercasing First Lettter Of Name
			t->name[0]-=32;
	}
}

void insert_record(void){
	struct student *t=NULL;
	struct student *p=NULL;
	
	if(!head){
		printf("There is no existing record creating new record...\n");
		head=(struct student*)malloc(sizeof(struct student));
		head->next=NULL;
		fflush(stdin);
		printf("Enter First and Last Name:");
		fgets(head->name, sizeof(head->name), stdin);
		printf("\nEnter Roll No.:");
		scanf("%d",&head->roll);
		printf("Enter Marks\nMath:");
		scanf("%d",&head->math);
		printf("Enter Marks\nEnglish:");
		scanf("%d",&head->english);
		printf("Enter Marks\nScience:");
		scanf("%d",&head->science);
		
		head->percentage=((head->math+head->english+head->science)/3);//Assuming maximum marks is hundred
		if(head->name[0]>='a' && head->name[0]<='z')
			head->name[0]-=32;
	}
	else{
		t=search();
		if(!t){
			printf("Record Not Found...\n");
		}
		else{
			if(t->next!=NULL){
				p=(struct student*)malloc(sizeof(struct student));
				p->next=t->next;
				t->next=p;
				fflush(stdin);
				printf("Enter First and Last Name:");
				fgets(p->name, sizeof(p->name), stdin);
				printf("\nEnter Roll No.:");
				scanf("%d",&p->roll);
				printf("Enter Marks\nMath:");
				scanf("%d",&p->math);
				printf("Enter Marks\nEnglish:");
				scanf("%d",&p->english);
				printf("Enter Marks\nScience:");
				scanf("%d",&p->science);
				
				p->percentage=((p->math+p->english+p->science)/3);
				
				if(p->name[0]>='a' && p->name[0]<='z')
					p->name[0]-=32;
			}
			else{
				t->next=(struct student*)malloc(sizeof(struct student));
				t=t->next;
				t->next=NULL;
				fflush(stdin);
				printf("Enter First and Last Name:");
				fgets(t->name, sizeof(t->name), stdin);
				printf("\nEnter Roll No.:");
				scanf("%d",&t->roll);
				printf("Enter Marks\nMath:");
				scanf("%d",&t->math);
				printf("Enter Marks\nEnglish:");
				scanf("%d",&t->english);
				printf("Enter Marks\nScience:");
				scanf("%d",&t->science);
				
				t->percentage=((t->math+t->english+t->science)/3);
				if(t->name[0]>='a' && t->name[0]<='z')
					t->name[0]-=32;
			}
		}
	}
}

void display_all(void){
	struct student *t=NULL;
	
	if(!head){
		printf("There are no records...\n");
	}
	else{
		printf("\n ROLL  | MATH |ENG   |SCI   | PER%% | NAME               \n");
		printf("-------+------+------+------+------+--------------------\n");
		for(t=head;t;t=t->next){
			printf(" %-5d | %-5d| %-5d| %-5d| %-5d|%-20s\n",t->roll,t->math,t->english,t->science,t->percentage,t->name);
		}
		printf("\n===========================================================\n");
	}

}

void edit_record(void){
	struct student *t=NULL;
	if(!head){
		printf("There are no records...\n");
	}
	else{
		t=search();
		if(!t){
			printf("Record Not Found..");
		}
		else{
		//editing record
			fflush(stdin);
			printf("Enter First and Last Name:");
			fgets(t->name, sizeof(t->name), stdin);
			printf("Enter Roll No.:");
			scanf("%d",&t->roll);
			printf("Enter Marks\nMath:");
			scanf("%d",&t->math);
			printf("Enter Marks\nEnglish:");
			scanf("%d",&t->english);
			printf("Enter Marks\nScience:");
			scanf("%d",&t->science);
			printf("\n");
			t->percentage=((t->math+t->english+t->science)/3);//Assuming maximum marks is hundred
			
			if(t->name[0]>='a' && t->name[0]<='z')
				t->name[0]-=32;
				
			}
		}
	}
	
void search_record(void){
	struct student *t=NULL;

	if(!head){
		printf("\nThere are no existing records");
	}
	else{
		t=search();
		if(!t){
			printf("\nRecord Not Found");
			return;
		}
		else{
			printf("\nFollowing is The Searched Record:\n");
			printf("\n ROLL  | MATH |ENG   |SCI   | PER%% | NAME               \n");
			printf("-------+------+------+------+------+--------------------\n");
			printf(" %-5d | %-5d| %-5d| %-5d| %-5d|%-20s\n",t->roll,t->math,t->english,t->science,t->percentage,t->name);
		}
	}
}

struct student* search(void){
		struct student *q=NULL;
		int ch=0;
		char search_name[NAME_SIZE]={0};
		int index=0, roll_search=0;
	
	first:
		printf("\n1.Search by name\n2.search by roll no\n3.Exit\nSelect:");
		scanf("%d",&ch);
		
		if(ch==1){
			fflush(stdin);
			printf("Enter Name: ");
		//	fgets(search_name, sizeof(search_name), stdin);
		    scanf("%s",search_name);
			for(q=head;q;q=q->next){
				for(index=0;(index<NAME_SIZE);index++){
					if((search_name[index])!=(q->name[index]))
					break;
					}
			if((index==(NAME_SIZE)))
				return q;
			}
			if(!q)
			return NULL;
		}
		else if(ch==2){
			printf("Enter Roll No.:");
			scanf("%d",&roll_search);

			for(q=head;((q!=NULL)&&((roll_search)!=(q->roll)));q=q->next);
			return q;	
		}
		else if(ch==3){
			printf("Exiting......");
			return NULL;
		}
		else{
			printf("Invalid Selection please choose again....");
			goto first;
		}
}

void delete_all(void){
	struct student *t=NULL;
	unsigned short int ch=0;
	
	if(!head){
		printf("There are no existing records");
	}
	else{
		display_all();
		confirmation:
			fflush(stdin);
			printf("Are you sure you want to delete these records?:\n 1.Yes\n2.No\nAnswer:");
			scanf("%hu",&ch);
			switch(ch){
				case 1:
					printf("proceeding with deletion of all existing records...\n");
					for(t=head;t;t=t->next,free(head),head=t);
					head=NULL;
					break;
				case 2:
					printf("Halting the process of deletion....\n\n");
					break;
				default:
					printf("Invalid choice confirm again...\n\n");
					goto confirmation;
		}
	}
}

void delete_record(void){
	struct student *t=NULL;
	struct student *p=NULL;
	unsigned short int o=0;
	
	if(!head){
		printf("There are no existing records\n");
	}
	else{
		printf("Specify the record to be deleted:\n");
		t=search();
		if(t==NULL){
			printf("Record Not Found...\n");
			return;
		}
		else if(t==head){
			printf("\n ROLL  | MATH |ENG   |SCI   | PER%% | NAME               \n");
			printf("-------+------+------+------+------+--------------------\n");
			printf("Roll No: %d\nMath: %d\nEnglish:%d\nScience: %d\nPercentage: %d%\n\n",t->roll,t->math,t->english,t->science,t->percentage);
			up:
				printf("\n\nDO YOU WANT TO DELETE THIS RECORD?:\n1.Yes 2.No\n  :");
				scanf("%hu",&o);
				if(o==1){
				head=t->next;
				free(t);
				}
				else if(o==2){
					printf("\nCANCELING DELETION....\n");
					return;
				}
				else{
					printf("Invalid Choice please confirm again\n");
					goto up;
				}
		}
		else{
			printf("\n ROLL  | MATH |ENG   |SCI   | PER%% | NAME               \n");
			printf("-------+------+------+------+------+--------------------\n");
			printf(" %-5d | %-5d| %-5d| %-5d| %-5d|%-20s\n",t->roll,t->math,t->english,t->science,t->percentage,t->name);
			above:
				printf("\n\nDO YOU WANT TO DELETE THIS RECORD?:\n1.Yes 2.No\n  :");
				scanf("%hu",&o);
				if(o==1){
				for(p=head;p->next!=t;p=p->next);
				p->next=t->next;
				free(t);
				printf("Record Successfully Deleted....\n");
				}
				else if(o==2){
					printf("\nCANCELING DELETION....\n");
					return;
				}
				else{
					printf("Invalid Choice please confirm again\n");
					goto above;
				}
		}
	}
}

void midpoint(void){
	int flag=0,counter=0;
	struct student *t=NULL;
	
	if(!head){
		printf("There are no existing records");
	}
	else{
		for(t=head,flag=0;t;t=t->next,flag++);
		
		if(flag==1){
			t=head;
			printf("Only Single record is present which is as follows\n");
			printf("\n ROLL  | MATH |ENG   |SCI   | PER%% | NAME               \n");
			printf("-------+------+------+------+------+--------------------\n");
			printf(" %-5d | %-5d| %-5d| %-5d| %-5d|%-20s\n",t->roll,t->math,t->english,t->science,t->percentage,t->name);
		}
		else if((flag%2)!=0){
			for((flag/=2),t=head,counter=0;counter<flag;t=t->next,counter++);
			printf("Following is the midpoint record\n");
			printf("\n ROLL  | MATH |ENG   |SCI   | PER%% | NAME               \n");
			printf("-------+------+------+------+------+--------------------\n");
			printf(" %-5d | %-5d| %-5d| %-5d| %-5d|%-20s\n",t->roll,t->math,t->english,t->science,t->percentage,t->name);
		}
		else{
			for((flag/=2),t=head,counter=1;counter<flag;t=t->next,counter++);
			printf("As there are even number of records showing most relevent:\n");
			printf("\n ROLL  | MATH |ENG   |SCI   | PER%% | NAME               \n");
			printf("-------+------+------+------+------+--------------------\n");
			printf(" %-5d | %-5d| %-5d| %-5d| %-5d|%-20s\n",t->roll,t->math,t->english,t->science,t->percentage,t->name);
		}
	}
}

void reverse_display(struct student *t){
	
	if(!head){
		printf("There are no existing records...");
	}
	else{
		if((t->next)!=NULL){
		    reverse_display(t->next);
			printf("Name: ");
			puts(t->name);
			printf("\nRoll No: %d\nMath: %d\nEnglish:%d\nScience: %d\nPercentage: %d%\n\n",t->roll,t->math,t->english,t->science,t->percentage);
		}
		if(t==(head->next) /*&& t->next!=NULL*/){
			printf("Name: ");
			puts(head->name);
			printf("\nRoll No: %d\nMath: %d\nEnglish:%d\nScience: %d\nPercentage: %d%\n\n",head->roll,head->math,head->english,head->science,head->percentage);
		}
	}
}

void sort_record(void){
	char sortby;
	unsigned short int indx=0,indx2=0; 
	struct student *t=NULL;
	struct student *p=NULL;
	struct student *q=NULL;
	
	if(!head){
		printf("No records are present please create first....");
	}
	else if(head->next==NULL){
		printf("Single Record Cannot Be Sorted");
	}
	else{
		sort:
			printf("Sort by\n1.Name\n2.Roll Number :");
			fflush(stdin);
			scanf("%c",&sortby);
			if(sortby=='1'){
				printf("Enter Order:\n1.A-Z\n2.Z-A : ");
				fflush(stdin);
				scanf("%c",&sortby);
				if(sortby=='1'){
					indx=lastnode();
					for(t=head,p=t->next;indx>=1;indx--){
						for(t=head,q=head,p=t->next,indx2=1;indx2<indx;indx2++){
							if((t->name[0])>(p->name[0])){
								t->next=p->next;
								p->next=t;
								if(t==head){
									head=p;
									p=t->next;
									q=head;
								}
								else{
								q->next=p;
								q=p;
								p=t->next;
								}
							}
							else{
								q=t;
								t=p;
								p=p->next;
							}
						}
					}
				}
				else if(sortby=='2'){
					indx=lastnode();
					for(t=head,p=t->next;indx>=1;indx--){
						for(t=head,q=head,p=t->next,indx2=1;indx2<indx;indx2++){
							if((t->name[0])<(p->name[0])){
								t->next=p->next;
								p->next=t;
								if(t==head){
									head=p;
									p=t->next;
									q=head;
								}
								else{
								q->next=p;
								q=p;
								p=t->next;
								}
							}
							else{
								q=t;
								t=p;
								p=p->next;
							}
						}
					}
				}
				else{
					printf("Invalid Choice Specify Again\n");
					goto sort;
				}
			}
			else if(sortby=='2'){
				printf("Enter Order:\n1.Ascending\n2.Descending :");
				fflush(stdin);
				scanf("%c",&sortby);
				if(sortby=='1'){
					indx=lastnode();
					for(t=head,p=t->next;indx>=1;indx--){
						for(t=head,q=head,p=t->next,indx2=1;indx2<indx;indx2++){
							if((t->roll)>(p->roll)){
								t->next=p->next;
								p->next=t;
								if(t==head){
									head=p;
									p=t->next;
									q=head;
								}
								else{
								q->next=p;
								q=p;
								p=t->next;
								}
							}
							else{
								q=t;
								t=p;
								p=p->next;
							}
						}
					}
				}
				else if(sortby=='2'){
					indx=lastnode();
					for(t=head,p=t->next;indx>=1;indx--){
						for(t=head,q=head,p=t->next,indx2=1;indx2<indx;indx2++){
							if((t->roll)<(p->roll)){
								t->next=p->next;
								p->next=t;
								if(t==head){
									head=p;
									p=t->next;
									q=head;
								}
								else{
								q->next=p;
								q=p;
								p=t->next;
								}
							}
							else{
								q=t;
								t=p;
								p=p->next;
							}
						}
					}
				}
				else{
					printf("Invalid Choice Specify Again\n");
					goto sort;
				}
			}
		}
}

unsigned short int lastnode(void){
	struct student *t=NULL;
	unsigned short int flag=0;
	
	for(flag=0,t=head;t;t=t->next,flag++);
	return flag;
}

void save_file(void){
	FILE *fp= fopen("StudentRecord.txt","w");
	struct student *t= head;
	
	if(!fp){
		printf("FAILED TO STORE RECORDS !!!");
		return;
	}
	else{
		while(t){
			fprintf(fp,"%d %d %d %d %d %s",t->roll,t->math,t->english,t->science,t->percentage,t->name);
			t=t->next;
		}
	}
	fclose(fp);
}

void speak(const char *text){
	char command[600];
	
	snprintf(command, sizeof(command),
			"PowerShell -Command \"Add-Type -AssemblyName System.Speech;"
			"$speak=New-Object System.Speech.Synthesis.SpeechSynthesizer;"
			"$speak.Speak(\\\"%s\\\");\"",
			text);
			
	system(command);
}


