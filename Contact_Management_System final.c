/*
Group: Da Boyz
Instructor: Dr. Sadeghi
Course: CSCI 1110-03
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

	int menu(void){
		puts("\n\n\t************************\n");
		puts("\t\tMenu\n");
		puts("\t************************\n\n");
		
		printf("[1] View All Contacts\n");
		printf("[2] Find Contact\n");
		printf("[3] Add Contact\n");
		printf("[4] Delete Contact\n");
		printf("[5] Edit Contact\n");
		//printf("[6] Add Administrator\n");
		//printf("[7] Remove Administrator\n");
		printf("[6] Exit\n\n");
		
		printf("Please choose from the provided list to proceed: ");
		int select;
		scanf("%d",&select);
		if(select>=1 && select<=8){
			return select;
		}
		else{
			system("@cls||clear");
			printf("%d is not a proper selection. Please utilize the numbers from the list.",select);
			menu();
		}
	}
	
	void view(void){
		system("@cls||clear");
		puts("\n\n\t*************\n");
		puts("\tView Contacts\n");
		puts("\t*************\n\n");
		
		FILE *viewFile;
		viewFile = fopen("CMS.txt","r");
		if(viewFile == NULL){
			printf("An error hass occured! Please reset program to try again");
			exit(1);
		}
		struct information{
			char first[15];
			char last[15];
			char email[25];
			char homeNum[15];
			char workNum[15];
		};
		
		struct information new;
		
		printf("******************************************************************************\n");
		printf("First\t\tLast\t\tEmail\t\t\t\tHome#\t\t\tWork#\n");
		printf("******************************************************************************\n");
		
		char infoString[100];
		int placement=0;
		while(fgets(infoString, sizeof(infoString),viewFile) !=NULL){
			placement++;
			if(placement == 1){
				infoString[strcspn(infoString, "\n")] = 0;
				strcpy(new.first, infoString);
			}
			else if(placement == 2){
				infoString[strcspn(infoString, "\n")] = 0;
				strcpy(new.last, infoString);
			}
			else if(placement == 3){
				infoString[strcspn(infoString, "\n")] = 0;
				strcpy(new.email, infoString);
			}
			else if(placement == 4){
				infoString[strcspn(infoString, "\n")] = 0;
				strcpy(new.homeNum, infoString);
			}
			else if(placement == 5){
				infoString[strcspn(infoString, "\n")] = 0;
				strcpy(new.workNum, infoString);
			}
			else if(placement == 6){
				printf("%-5s\t\t%-10s\t%-25s\t%-15s\t\t%-10s\n",&new.first,&new.last,&new.email,&new.homeNum,&new.workNum);
				placement = 0;
			}
		}
		fclose(viewFile);
	}
	
	int* locate(void){
		system("@cls||clear");
		puts("\n\n\t************************************\n");
		puts("\t\tLocate Contact\n");
		puts("\t************************************\n\n");
		
		static int output[2];
		printf("You can search for your item based on\n[1]first name\n[2]last name\n[3]email\n[4]home number\n[5]work number\n\nWhich one do you prefer: ");
		int searchItem;
		scanf("%d",&searchItem);
		
		
		char items[5][100]={"first name", "last name","email","homeNum","workNum"};
		printf("What is the %s?: ",items[searchItem-1]);
		char key[100];
		char input[100];
		scanf("%s", &key);
		for(int i = 0; key[i]; i++){
			key[i] = toupper(key[i]);   // toupper     
			}
		strcpy(input,key);
		strcat(key, "\n");
		
		FILE *fileFind;
		fileFind = fopen("CMS.txt","r");
		if(fileFind == NULL){
			printf("An error hass occured! Please reset program to try again");
			exit(1);
		}
		
		char findString[100];
		int line=0;
		int find=0;
		int fieldNum=0;
		while(fgets(findString, sizeof(findString),fileFind) != NULL){
			line++; fieldNum++;
			if(strcmp(findString,key) == 0 && fieldNum == searchItem){
				//printf("%s is found on line %d\n",input, line);
				find=1;
				output[0]=find;
				line=line - (searchItem -1);
				output[1]=line;
				break;
			}
			if(fieldNum == 6){
				fieldNum = 0;
			}
		}
		fclose(fileFind);
		if(find == 0){
			printf("\n%s does not exist in the contact listing\n", input);
			return output;
		}
		
		fileFind = fopen("CMS.txt","r");
		if(fileFind == NULL){
			printf("An error hass occured! Please reset program to try again");
			exit(1);
		}
		//printf("the line is %d",line);
		int placement=0;
		while(fgets(findString, sizeof(findString),fileFind) != NULL){
			placement++;
			if(placement == (line)){
				printf("\tFirst Name: %s\n",findString);
			}else if(placement == (line+1)){
				printf("\tLast Name: %s\n",findString);
			}
			else if(placement == (line+2)){
				printf("\tEmail: %s\n",findString);
			}
			else if(placement == (line+3)){
				printf("\tHome Number: %s\n",findString);
			}
			else if(placement == (line+4)){
				printf("\tWork Number: %s",findString);
			}
		}
		fclose(fileFind);
		
		return output;
	}

	void newContacts(void){
		system("@cls||clear");
		puts("\n\n\t****************\n");
		puts("\tAdd New Contacts\n");
		puts("\t****************\n\n");
		
		struct information{
			char first[15];
			char last[15];
			char email[25];
			char homeNum[15];
			char workNum[15];
		};
		struct information new;
		
		printf("To add a new user, please add the appropriate information\n");
		printf("First Name: ");
		scanf("%s",& new.first);
		for(int i = 0; new.first[i]; i++){
			new.first[i] = toupper(new.first[i]);        
			}
		printf("Last Name: ");
		scanf("%s",& new.last);
		for(int i = 0; new.last[i]; i++){
			new.last[i] = toupper(new.last[i]);        
			}
		printf("E-mail: ");
		scanf("%s",& new.email);
		for(int i = 0; new.email[i]; i++){
			new.email[i] = toupper(new.email[i]);      
			}
		printf("Home/Cell-Phone Number: ");
		scanf("%s",& new.homeNum);
		for(int i = 0; new.homeNum[i]; i++){
			new.homeNum[i] = toupper(new.homeNum[i]);       
			}
		printf("Work/Office Phone Number: ");
		scanf("%s",& new.workNum);
		for(int i = 0; new.workNum[i]; i++){
			new.workNum[i] = toupper(new.workNum[i]);       
			}
		
		FILE *contactFile;
		contactFile = fopen("CMS.txt","a");
		if(contactFile == NULL){
			printf("An error hass occured! Please reset program to try again");
			exit(1);
		}
		
		fprintf(contactFile, "%s\n%s\n%s\n%s\n%s\n-------------------------\n",&new.first,&new.last,&new.email,&new.homeNum,&new.workNum);
		fclose(contactFile);
		
		puts("Contact added successfully");
		printf("Do you wish to add another contact (y/n)?: ");
		char choice;
		getchar();
		scanf("%c",& choice);
		if(choice=='y'){
			newContacts();
		}	
	}

	void delete(void){
		int* marker=locate();
		
		int find = marker[0];
		int line = marker[1];
		
		if(find == 0){
			printf("That individual does not exist in the contact list");
		}
		else{
			FILE *originalFile=fopen("CMS.txt","r");
			FILE *temporaryFile=fopen("temporary.txt","w");
			
			if(originalFile == NULL || temporaryFile == NULL){
				printf("An error hass occured! Please reset program to try again");
				exit(1);
			}
			
			char deleteString[100];
			int placement=0;
			
			while(fgets(deleteString, sizeof(deleteString),originalFile) != NULL){
				placement++;
				if(placement !=line && placement !=(line+1) && placement !=(line+2) && placement !=(line+3) && placement !=(line+4) && placement !=(line+5)){
					fprintf(temporaryFile,"%s", deleteString);
				}
			}
			
			fclose(originalFile);
			fclose(temporaryFile);
			
			remove("CMS.txt");
			rename("temporary.txt","CMS.txt");
			
			puts("Succesfully Removed Contact");
			printf("Are there any others you wish to remove?(y/n): ");
			
			char close;
			getchar();
			scanf("%c",&close);
			if(close=='y'){
				delete();
			}
		}
		
	}

	void edit(void){
		int* marker = locate();
		
		int find=marker[0];
		int line=marker[1];
		
		if(find == 0){
			printf("That individual does not exist in the contact list");
		}
		else{
			char first[15];
			char last[15];
			char email[25];
			char homeNum[15];
			char workNum[15];
			
			printf("Please enter a change for the first name. If no change is needed re-enter original: ");
			scanf("%s",&first);
			for(int i = 0; first[i]; i++){
			first[i] = toupper(first[i]);        
				}
			printf("Please enter a change for the last name. If no change is needed re-enter original: ");
			scanf("%s",&last);
			for(int i = 0; last[i]; i++){
			last[i] = toupper(last[i]);        
				}
			printf("Please enter a change for the E-mail. If no change is needed re-enter original: ");
			scanf("%s",&email);
			for(int i = 0; email[i]; i++){
			email[i] = toupper(email[i]);        
				}
			printf("Please enter a change for the Home/Cell-Phone number. If no change is needed re-enter original: ");
			scanf("%s",&homeNum);
			for(int i = 0; homeNum[i]; i++){
			homeNum[i] = toupper(homeNum[i]);        
				}
			printf("Please enter a change for the work number. If no change is needed re-enter original: ");
			scanf("%s",&workNum);
			for(int i = 0; workNum[i]; i++){
			workNum[i] = toupper(workNum[i]);        
				}
			
			FILE *originalFile=fopen("CMS.txt","r");
			FILE *temporaryFile=fopen("temporary.txt","w");
			
			if(originalFile == NULL || temporaryFile == NULL){
				printf("An error hass occured! Please reset program to try again");
				exit(1);
			}
			
			char editString[100];
			int placement=0;
			
			while(fgets(editString, sizeof(editString),originalFile) != NULL){
				placement++;
				if(placement !=(line) && placement !=(line+1) && placement !=(line+2) && placement !=(line+3) && placement !=(line+4)){
					fprintf(temporaryFile,"%s", editString);
				}
				else if(placement == (line)){
					fprintf(temporaryFile,"%s\n",first);
				}
				else if(placement == (line+1)){
					fprintf(temporaryFile,"%s\n",last);
				}
				else if(placement == (line+2)){
					fprintf(temporaryFile,"%s\n",email);
				}
				else if(placement == (line+3)){
					fprintf(temporaryFile,"%s\n",homeNum);
				}
				else if(placement == (line+4)){
					fprintf(temporaryFile,"%s\n",workNum);
				}
			}
			
			fclose(originalFile);
			fclose(temporaryFile);
			
			remove("CMS.txt");
			rename("temporary.txt","CMS.txt");
			
			puts("\nSuccesfully Edited Contact");
			printf("Are there any others you wish to edit?(y/n): ");
			
			char close;
			getchar();
			scanf("%c",&close);
			if(close=='y'){
				edit();
			}
		}
	}

/*	void newAdmin(void){
		system("@cls||clear");
		puts("\n\n\t****************\n");
		puts("\tAdd New Admin\n");
		puts("\t****************\n\n");
		
		struct login{
			char username[15];
			char password[15];
		};
		struct login new;
		
		printf("To add a new admin, please add the appropriate information\n");
		printf("Username: ");
		scanf("%s",& new.username);
		printf("Password: ");
		scanf("%s",& new.password);
		
		
		FILE *adminFile;
		adminFile = fopen("admin.txt","a");
		if(adminFile == NULL){
			printf("An error hass occured! Please reset program to try again");
			exit(1);
		}
		
		fprintf(adminFile, "%s\n%s\n-------------------------\n",&new.username,&new.password);
		fclose(adminFile);
		
		puts("Administrator Login added successfully");
		printf("Do you wish to add another administrator (y/n)?: ");
		char choice;
		getchar();
		scanf("%c",& choice);
		if(choice=='y'){
			newAdmin();
		}	
	}

	int* findAdmin(void){
			
		static int output[2];
		
		
		printf("What is the Login ID you wish to remove?: ");
		char key[100];
		char input[100];
		scanf("%s", &key);
		strcpy(input,key);
		strcat(key, "\n");
		
		FILE *adminFind;
		adminFind = fopen("admin.txt","r");
		if(adminFind == NULL){
			printf("An error hass occured! Please reset program to try again");
			exit(1);
		}
		
		char findString[100];
		int line=0;
		int find=0;
		int fieldNum=0;
		while(fgets(findString, sizeof(findString),adminFind) != NULL){
			line++; fieldNum++;
			if(strcmp(findString,key) == 0 && fieldNum == 1){
				//printf("%s is found on line %d\n",input, line);
				find=1;
				output[0]=find;
				output[1]=line;
				break;
			}
			if(fieldNum == 3){
				fieldNum = 0;
			}
		}
		fclose(adminFind);
		if(find == 0){
			printf("\n%s does not exist in the administrator listing\n", input);
			return output;
		}
		
		adminFind = fopen("admin.txt","r");
		if(adminFind == NULL){
			printf("An error hass occured! Please reset program to try again");
			exit(1);
		}
		//printf("the line is %d",line);
		int placement=0;
		while(fgets(findString, sizeof(findString),adminFind) != NULL){
			placement++;
			
			/*if(placement == (line+1)){
				printf("\tPassword: %s\n",findString);
			}
		}
		fclose(adminFind);
		
		return output;
	}

	void removeAdmin(void){
			int* marker=findAdmin();
			
			int find = marker[0];
			int line = marker[1];
			
			if(find == 0){
				printf("That login does not exist in the contact list");
			}
			else{
				FILE *originalFile=fopen("admin.txt","r");
				FILE *temporaryFile=fopen("temp.txt","w");
				
				if(originalFile == NULL || temporaryFile == NULL){
					printf("An error hass occured! Please reset program to try again");
					exit(1);
				}
				
				char deleteString[100];
				int placement=0;
				
				while(fgets(deleteString, sizeof(deleteString),originalFile) != NULL){
					placement++;
					if(placement != line && placement !=(line+1) && placement !=(line+2)){
						fprintf(temporaryFile,"%s", deleteString);
					}
				}
				
				fclose(originalFile);
				fclose(temporaryFile);
				
				remove("admin.txt");
				rename("temp.txt","admin.txt");
				
				puts("Succesfully Removed administrator");
				printf("Are there any others you wish to remove?(y/n): ");
				
				char close;
				getchar();
				scanf("%c",&close);
				if(close=='y'){
					removeAdmin();
				}
			}
			
		}
*/
	//void login(void){
#include<conio.h>

int login(){
	
	char username[10]="Unewhaven", password[10]="admin", login[10], pass[10];
	int n=1, x, y;
	
	do{
		printf("Please enter a username: ");
		scanf("%s",login);
		
		printf("Please enter a password: ");
		scanf("%s",pass);
		
		x=strcmp(login,username);
		y=strcmp(pass,password);
		
		if(x==0 && y==0){
			printf("Login Successful\n");
			return 0;
		}
		else if (x!=0 && y==0){
			printf("Username Not Found\n",3-n);
			n++;
		}
		else if (x==0 && y!=0){
			printf("Incorrect Password\n", 3-n);
			n++;
		}
		else{
			printf("Incorrect Username and Password\n", 3-n);
			n++;
		}
		if(n>3){
			printf("To Many Incorrect Logins\nAccess Denied");
		}
	}while(n<=3);
	
}		

void main(void){
	system("@cls||clear");
	
	login();
	
	puts("\n\n\t*************************\n");
	puts("\tContact Management System\n");
	puts("\t*************************\n\n\n");
	
	int task;
	task = menu();
	
	switch (task){
		case 1:
			view();
			break;
		case 2:
			locate();
			break;
		case 3:
			newContacts();
			break;
		case 4:
			delete();
			break;
		case 5:
			edit();
			break;
		//case 6:
			//newAdmin();
			//break;
		//case 7:
			//removeAdmin();
			//break;
		case 6:
			exit(1);
	}
	
	printf("\nDo you wish to access any other parts of the Contact Management System?(y/n): ");
	char close;
	getchar();
	scanf("%c",&close);
	if(close=='y'){
		main();
	}
	else if (close=='n'){
		exit(1);
	}
}