#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
void lower_case(char s[])
{
    int i;
    for(i = 0; s[i] != '\0';i++)
    {
        if(s[i] >='A' && s[i]<='Z') {
			s[i] = s[i] + 32;
		}
			
    }
}
typedef struct {
    char id[10]; 
    char first[30]; 
    char last[30]; 
    char gender[7]; 
    char dob[20];  //Date of birth
    char Depart[15]; 
    char country [20];
}Member;  

typedef struct 
{
	char ID [10];
	char project_id [5];
	char progress [10];
}Progress;


void get_data_from_Employee_file (Member a[])
{
    FILE *EMPFILE;
    EMPFILE = fopen("Employee.csv","r");
    if (EMPFILE == NULL){
        exit (1);
    }
    char *delim = ",";
    
    char new[256];
    int i=0;
	int j=0;
    while (fgets (new,256,EMPFILE)){
    	j++;
    	int k=0;
    	if (j == 1){
    		continue;
		}
		char *category = strtok (new,delim);
		
		while (category){
			if (k == 0){
				strcpy (a[i].id , category);
			}
			if (k == 1){
				strcpy (a[i].first , category);;
			}
			if (k == 2){
				strcpy (a[i].last , category);
			}
			if (k == 3){
				strcpy (a[i].gender , category);
			}
			if (k == 4){
				strcpy (a[i].dob , category);
			}
			if (k == 5){
				strcpy (a[i].Depart , category);
			}
			if (k == 6){
				strcpy (a[i].country , category);
			}
			
			category = strtok (NULL,delim);
			k++;
		}
		i++;
    }
    fclose(EMPFILE);
}
int count_member (){
	char temp [256];
	FILE *EMPFILE;
    EMPFILE = fopen("Employee.csv","r");
	int count = 0;
	fgets (temp,256,EMPFILE);
	while (fgets(temp,256,EMPFILE)){
		count++;
	}
	fclose(EMPFILE);
	return count;
}

void get_data_from_Progress_file (Progress a[])
{
    FILE *PROGRESS;
    PROGRESS = fopen("Progress.csv","r");
    if (PROGRESS == NULL){
        exit (1);
    }
    char *delim = ",";
    
    char new[600];
    int i=0;
    int j=0;
    
    while (fgets (new,600,PROGRESS)){
    	j++;
    	int k=0;
    	if (j == 1){
    		continue;
		}
		
		char *category = strtok (new,delim);
		while (category){
			if (k == 0){
				strcpy (a[i].ID , category);
			}
			if (k == 1){
				strcpy (a[i].project_id , category);;
			}
			if (k == 2){
				strcpy (a[i].progress , category);
			}
			
			category = strtok (NULL,delim);
			k++;
		}
		i++;
    }

    fclose(PROGRESS);
}

int count_progress (){
	char temp [256];
	FILE *PROGRESS;
    PROGRESS = fopen("Progress.csv","r");
	int count = 0;
	while (fgets(temp,256,PROGRESS)){
		count++;
	}
	fclose(PROGRESS);
	return count;
}

int check_char (char s[]){
    int i,count = 0;
    for (i=0;i<strlen(s);i++){
        if (s[i] >= 'a' && s[i]<= 'z'){
            count = 1;
        }
		if (s[i] >= 'A' && s[i]<= 'Z'){
			count = 1;
		}
    }
    return count;
}
int check_space (char s[]){
    int i,n=0;
    int len = strlen(s);
    for (i=0;i<len;i++){
        if (isspace(s[i])){
            n+=1;
        }
    }
    return n;
}
int check_sign (char s[]){
	int i;
	int flag = 0;
	if (s[0] == '-'){
		flag = 1;
	}
	return flag;
	
}
//COUNT
void request_1 (Member a[], char input[]){ 
	FILE *fout;
	fout = fopen ("result.csv","w");
	char *delim = " ";
	char *token;
	token = strtok (input,delim);\
	token = strtok (NULL,delim);
	long int token_dep = atol(token);
	int i;
	int count = 0;
	for (i=0;i<count_member();i++){
		if (atol(a[i].Depart) == token_dep){

			count++;
		}

	}
	fprintf (fout,"%d",count);
	fclose (fout);
}
//HAM BAO LOI CHECK.TXT
void ERROR (){
	FILE *fcheck;
	fcheck = fopen ("check.txt","w");
	fprintf (fcheck,"wrong syntax");
	fclose (fcheck);
}
//LIST MALE/FEMALE
void request2 (Member a[], char b[]){
	FILE *fout;
	fout = fopen ("result.csv","w");
	int i;
	
	for (i=0;i<count_member();i++){
		char x[50];
		strcpy(x,a[i].gender);
		lower_case(b);
		lower_case(x);
		if (strcmp(b,x)==0){
			fprintf (fout,"%s,%s,%s,%s,%s,%s,%s",a[i].id,a[i].first,a[i].last,a[i].gender,a[i].dob,a[i].Depart,a[i].country);
			
		}
	}
	fclose (fout);
}
//REPORT
void request4 (Progress a[],char b[]){
	FILE *fout;
	fout = fopen ("result.csv","w");
	char *delim = " ";
	char *delim1 = "";
	char *token;
	token = strtok (b,delim);
	token = strtok (NULL,delim);
	double prog = atof (token);
	int i,count=-1;
	long int temp[50];
	if (prog == 0){
		fprintf (fout,"",delim);
		fclose(fout);
	}
	else{
		for(i=0;i<count_progress();i++){
		if (prog == atof(a[i].progress)){
			count++;
			temp[count] = atol(a[i].ID);
		}
	}
		int j;
		for (i=0;i<count;i++){
			for (j=i+1;j<=count;j++){
				if (temp[i] == temp[j]){
					int i1;
					for (i1=j;i1<count;i1++){
						temp[i1]  = temp[i1+1];
					}
					count--;
				}
			}	
		}
		for (i=0;i<=count;i++){
			fprintf (fout,"%li\n",temp[i]);
		}
		fclose(fout);
	}
	
}
//AVERAGE
void request5 (Progress a[], char b[]){
	FILE *fout;
	fout = fopen ("result.csv","w");
	char *delim = " ";
	char *token;
	token = strtok (b,delim);
	token = strtok (NULL,delim);
	int pro_id = atoi (token);
	int i;
	double sum=0;
	double average;
	int n = 0;
	for(i=0;i<count_progress();i++){
		if (pro_id == atoi(a[i].project_id)){
			sum += atof(a[i].progress);
			n++;
		}
	}
	if (n==0){
		fprintf (fout,"%d",n);
	}
	else{
		average = sum/n;
		fprintf (fout,"%.3f",average);
	}
	
	fclose(fout);
}
//SORT ASC
void request6_1 (Member a[]){
	FILE *fout;
	fout = fopen ("result.csv","w");
	// printf ("%d",count_member());
	int i,j;
	for (i=0;i<count_member()-1;i++){
		for (j=count_member()-1;j>i;j--){
			if (strcmp(a[j].last,a[j-1].last)<0){
				Member temp = a[j];
				a[j] =  a[j-1];
				a[j-1] = temp;
				
			}
			if (strcmp(a[j].last,a[j-1].last)==0){
				if (strcmp(a[j].first,a[j-1].first)<0){
					Member temp = a[j];
					a[j] = a[j-1];
					a[j-1] =temp;
				}
			}
		}
		
	}
	for (i=0;i<count_member();i++){
		fprintf (fout,"%s,%s,%s,%s,%s,%s,%s",a[i].id,a[i].first,a[i].last,a[i].gender,a[i].dob,a[i].Depart,a[i].country);
	}
	fclose(fout);
}
//SORT DESC
void request6_2 (Member a[]){
	FILE *fout;
	fout = fopen ("result.csv","w");
	int i,j;
	for (i=0;i<count_member()-1;i++){
		for (j=count_member()-1;j>i;j--){
			if (strcmp(a[j].last,a[j-1].last)>0){
				Member temp = a[j];
				a[j] =  a[j-1];
				a[j-1] = temp;
			}
			if (strcmp(a[j].last,a[j-1].last)==0){
				if (strcmp(a[j].first,a[j-1].first)<0){
					Member temp = a[j];
					a[j] = a[j-1];
					a[j-1] =temp;
				}
			}
		}
	}
	for (i=0;i<count_member();i++){
		fprintf (fout,"%s,%s,%s,%s,%s,%s,%s",a[i].id,a[i].first,a[i].last,a[i].gender,a[i].dob,a[i].Depart,a[i].country);
	}
	fclose(fout);
}
//DELETE ENTER SIGN
void del_Enter(char x[]){
	if(x[strlen(x)-2] == 13){
		x[strlen(x)-2] = '\0';
	}
    size_t len = strlen(x);
    if (x[len - 1] == '\n'){
        x[len - 1] = '\0';
    }
}
//COUNTRY 
void request7 (Member a[],char token2[]){
	FILE *fout;
	fout = fopen("result.csv","w");
	int i;
	for (i=0;i<count_member();i++){
		del_Enter(a[i].country);
		char e[50];
		strcpy(e, a[i].country);
		lower_case(e);
		if (strcmp(token2,e) == 0){
			fprintf (fout,"%s,%s,%s,%s,%s,%s,%s\n",a[i].id,a[i].first,a[i].last,a[i].gender,a[i].dob,a[i].Depart,a[i].country);
		}
	}
	
	fclose(fout);
}

//CHECK TEST CASE
void scan_command (Member a[],Progress b[],char token1[],char token2[],char token3 [],char input[])
{

	if (strcmp(token1,"count") ==0 ){
		if (check_space(input) >= 2){
            ERROR();
            exit(1);
        }
        else if (token3 != NULL){
			ERROR();
			exit (1);
		}
		else if (token2 == NULL){
			ERROR();
			exit (1);
		}
		else if (check_sign(token2)==1){
			ERROR();
			exit (1);
		}
		else {
			get_data_from_Employee_file(a);
			request_1(a,input);
			return;
		}

	}
	else if (strcmp(token1,"list")==0){
        if (check_space(input) >= 2){
            ERROR();
            exit(1);
        }
		else if (token3 != NULL){
			ERROR();
			exit (1);
		}
		else if(token2 == NULL){
			ERROR();
			exit(1);
		}
		else if (strcmp(token2,"male") != 0 && strcmp(token2,"female")!=0){
			ERROR();
			exit(1);
		}
		else{
			get_data_from_Employee_file(a);
			request2(a,token2);
			return;

		}
	}
	else if (strcmp(token1,"report")==0){
		if (check_space(input) >= 2){
            ERROR();
            exit(1);
        }
        else if (token3 != NULL){
			ERROR();
			exit (1);
		}
		else if(token2 == NULL){
			ERROR();
			exit(1);
		}
		else if (check_char (token2)==1){
            ERROR();
            exit(1);
        }
		else if (atof(token2) > 1 || atof (token2) < 0){
			ERROR ();
			exit (1);
		}
		else {
			get_data_from_Progress_file(b);
			request4(b,input);
			exit (1);
		}

	}
	else if (strcmp(token1,"average") == 0){
		if (check_space(input) >= 2){
            ERROR();
            exit(1);
        }
        else if (token3 != NULL){
			ERROR();
			exit (1);
		}
		else if(token2 == NULL){
			ERROR();
			exit(1);
		}
		else if (check_sign(token2)==1){
			ERROR();
			exit (1);
		}
        // else if (check_char (token2)==1){
        //     ERROR();
        //     exit(1);
        // }
		else{
			get_data_from_Progress_file(b);
			request5(b,input);
			return;
		}
	}
	else if (strcmp(token1,"sort") == 0){
		if (check_space(input) >= 2){
            ERROR();
            exit(1);
        }
        else if (token3 != NULL){
			ERROR();
			exit (1);
		}
		else if(token2 == NULL){
			ERROR();
			exit(1);
		}
		else {
			if(strcmp(token2,"asc") != 0 && strcmp(token2,"desc") != 0){
			ERROR();
			exit(1);
			}
			else if (strcmp(token2,"asc") == 0){
				get_data_from_Employee_file(a);
				request6_1(a);
				return;
			}
			else if (strcmp(token2,"desc") == 0){
				get_data_from_Employee_file(a);
				request6_2(a);
				return;
			}
		}	
	}
	else if (strcmp(token1,"country")==0){
		if (check_space(input) >= 2){
            ERROR();
            exit(1);
        }
        else if (token3 != NULL){
			ERROR();
			exit (1);
		}
		else if(token2 == NULL){
			ERROR();
			exit(1);
		}
		else {
			get_data_from_Employee_file(a);
			request7(a,token2);
			return;
		}
	}
	else {
		ERROR();
		exit(1);
	}
		
}
void main (){
	Member a[count_member()];
	Progress b[count_progress()];
	char input[100];
	char input1[50];
	fgets (input,100,stdin);
	del_Enter(input);	
	lower_case(input);
	strcpy(input1,input);
	char *token1 ;
	char *token2 ;
	char *token3 ;
	token1 = strtok (input," ");
	token2 = strtok (NULL," ");
	token3 = strtok (NULL," ");
	scan_command(a,b,token1,token2,token3,input1);
	
}