/*
 * lab5.c
 *
 *  Created on: Nov 15, 2017
 *      Author: Sheida
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define L 31

typedef struct info{
	char name[L];
	int id;
	int num_lap;
	float avg;
	float *time_lap;//we dont know how many it should be an array
}info_t;

info_t *readFile (int *);
void infolist(info_t *,int);
void printBest(info_t *,int);
void details(info_t *,int);

int main(void){
	info_t *athletes;
	int n,i;
	char cmd[L];

	athletes = readFile(&n);
	do{
	fprintf(stdout,"COMMAND ?:\n");
	scanf("%s",cmd);


	if (strcmp(cmd,"LIST")==0){

		infolist(athletes,n);
	}
	if (strcmp(cmd,"BEST")==0){
			printBest(athletes,n);

		}
	if (strcmp(cmd,"DETAILS")==0){
			details (athletes,n);
		}
	if (strcmp(cmd,"STOP")!=0){
			fprintf(stdout,"unknown comment");
		}

	} while (strcmp(cmd,"STOP")!=0);

	//free!!
	for(i=0;i<n;i++){
		free(athletes[i].time_lap);
	}
	free(athletes);


	fprintf(stdout,"End of Program \n");
	return EXIT_SUCCESS;
}

info_t *readFile(int *n){
	FILE *fp;
	char name[L];//fin[L];
	int i,j,id,num_laps;
	float lap_times;
	info_t *athlete;



	//fprintf(stdout,"input file name :\n");
	//scanf("%s",fin);
	fp=fopen("input.txt","r");

	if(fp==NULL){
		printf("\n ERROR, file is empty!\n");
		exit (EXIT_FAILURE);
	}

	fscanf(fp,"%d",&n);
	//malloc in sizeof n

	athlete=(info_t *)malloc(*n*sizeof(info_t));
	if(athlete ==NULL){
		printf("\n !ALLOCATION ERROR!\n");
		exit (EXIT_FAILURE);
	}
	i=0;
	while (i<*n && fscanf(fp,"%s %d %d",name,&id,&num_laps)){
		strcpy(name,athlete[i].name);
		athlete[i].id=id;
		athlete[i].num_lap=num_laps;

		//allocating our array
		athlete[i].time_lap=(float *)malloc(athlete[i].num_lap*sizeof(float));

		if(athlete[i].time_lap == NULL){
			printf("ALLOCATION ERROR (time laps)\n");
			exit (EXIT_FAILURE);
		}
		//reading the timelaps in our file
		for(j=0;j<num_laps;j++){
			fscanf(fp,"%f",&lap_times);
			athlete[i].time_lap[j]=lap_times;
			athlete[i].avg+=athlete[i].time_lap[j];
		}
		athlete[i].avg/=athlete[i].num_lap;


		//printf("%d",&avg);
	}
	i++;



	fclose(fp);

	return athlete;
}
void infolist(info_t *ath,int n){
	int i;
	fprintf(stdout,"number of athletes:%d\n",n);
	for(i=0;i<n;i++){
	fprintf(stdout,"Name : %s	 #id = %d   #Laps=%d\n",ath[i].name,ath[i].id,ath[i].num_lap);
	}

}
void printBest(info_t *ath,int n){
	float best;
	int i,index,j;
	best=ath[0].avg;
	for(i=1;i<n;i++){
		if(ath[i].avg<best){
			best=ath[i].avg;
			index=i++;
		}
	}
fprintf(stdout,"Name : %s  #id : %d  #Laps=%d \n",ath[index].name,ath[index].id,ath[index].num_lap);
fprintf(stdout,"Times :");
	for(j=0;j<ath[index].num_lap;j++){
		fprintf(stdout," %f ",ath[index].time_lap[j]);
	}
	fprintf(stdout," Best Average : %f",ath[index].avg);
}
void details (info_t *ath , int n){

	char name[L];
	int i,j;


	scanf("%s",name);

	for(i=0;i<n;i++){
		if (strcmp(ath[i].name,name)==0){
			printf(" id : %d  Laps=%d \n",ath[i].id,ath[i].num_lap);
			printf(" Times : ");
			for(j=0;j<ath[i].num_lap;j++){
				fprintf(stdout," %f ",ath[i].time_lap[j]);
			}
printf("\n");
		}

}
}







