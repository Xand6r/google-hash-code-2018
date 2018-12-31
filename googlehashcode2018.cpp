/*rename the data-input file to aloha.txt for it to be readable*/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<ctype.h>
//object to represent position based on rectangular co-ordinates
struct vector{
	int row;
	int col;
};

//object for each cars
struct car_{
	int steps;
	int rides;
	int ridearray[516];
	struct vector current;
};

//details about each ride
struct rides{
	struct vector from;
	struct vector to;
	int start;
};

int arrayget(int index,char array[],int *pos);
void carsinit(struct car_ cars[],int carno);//initializes all cars to position 0
int finddistance(struct vector caller,struct vector car);//finds the distance between two vectors

int main(void){
	char filename[100];
	printf(">enter the name of the file(make-sure there are no spaces and add the file format if any):");
	scanf("%s",filename);
	
	FILE *pfile=NULL;
	pfile=fopen(filename,"r");//the name of the file can be changed.
	//variable declarations
	int row=0,col=0,vehicles=0,rideno=0,bonus=0,steps=0,bestcar=0;
	int d_row=0;int c_row=0;int c_col=0;
	int d_col=0,i,j,bull;int total_steps=0;
	struct vector dest;struct vector caller;
	char array[100];
	
	//read the first line of input
	int pos=0;int index=0;
	fgets(array,100,pfile);
	row=arrayget(index,array,&pos);
	index=pos;
	col=arrayget(index,array,&pos);
	index=pos;
	vehicles=arrayget(index,array,&pos);
	index=pos;
	rideno=arrayget(index,array,&pos);
	index=pos;
	bonus=arrayget(index,array,&pos);
	index=pos;
	bull=arrayget(index,array,&pos);
	//read the first line of input
	
	//declare the array of car-object
	struct car_ car[vehicles];
	carsinit(car,vehicles);
	//set all the car's location to the beginning
	
	//array for all the rides
	struct rides ride[rideno];
	
	//input the data for the rides
	for(i=0;i<rideno;i++){
		int pos=0;int index=0;
		fgets(array,100,pfile);
		ride[i].from.row=arrayget(index,array,&pos);
		index=pos;
		ride[i].from.col=arrayget(index,array,&pos);
		index=pos;
		ride[i].to.row=arrayget(index,array,&pos);
		index=pos;
		ride[i].to.col=arrayget(index,array,&pos);
		index=pos;
		ride[i].start=arrayget(index,array,&pos);
		index=pos;
		bull=arrayget(index,array,&pos);
	}
	
	//for each ride get the nearest car to it then move the car to the caller then to the destination
	for(i=0;i<rideno;i++){
		int stepstook=0;
		int bestscore=100000000;int currentscore=0;
		caller=ride[i].from;//get the position of the caller from its co-ordinates
		dest=ride[i].to;//get the destination of its caller
		
		
		//find the nearest ride to the caller and save it to c_row and c_col
		for(int v=0;v<vehicles;v++){
			currentscore=finddistance(caller,car[v].current);
			if(currentscore<bestscore){
				bestscore=currentscore;
				bestcar=v;
			}
		}
		//find the nearest ride to the caller and save it to c_row and c_col
	
	    car[bestcar].rides+=1;
	    car[bestcar].ridearray[car[bestcar].rides-1]=i;
	    stepstook+=abs(car[bestcar].current.col-caller.col)+abs(car[bestcar].current.row-caller.row);
	    //move the just gotten car from its initial position to the callers position
	    if(car[bestcar].current.col!=caller.col){
	    	if(car[bestcar].current.col<caller.col){
	    	    car[bestcar].current.col=caller.col;
		    }
		    else if(car[bestcar].current.col>caller.col){
		    	car[bestcar].current.col=caller.col;
			}
		}
		if(car[bestcar].current.row!=caller.row){
			if(car[bestcar].current.row<caller.row){
	    	    car[bestcar].current.row=caller.row;
		    }
		    else if(car[bestcar].current.row>caller.row){
		    	car[bestcar].current.row=caller.row;	
			}
		}
		
	    //move the just gotten car from its initial position to the callers position
	    
	    //check if it has reached the earliest step required to move to  destination.
		if(car[bestcar].steps<ride[i].start){
	    	stepstook+=ride[i].start;
		}	
		//check if it has reached the earliest step required to move to destination.
		stepstook+=abs(car[bestcar].current.col-dest.col)+abs(car[bestcar].current.row-dest.row);
	
		//move the car from the callers position to the final destination
		if(car[bestcar].current.col!=dest.col){
	    	if(car[bestcar].current.col<dest.col){
	    	    car[bestcar].current.col=dest.col;
		    }
		    else if(car[bestcar].current.col>dest.col){
		    	car[bestcar].current.col=dest.col;
			}
		}
		if(car[bestcar].current.row!=dest.row){
			if(car[bestcar].current.row<dest.row){
	    	    car[bestcar].current.row=dest.row;

		    }
		    else if(car[bestcar].current.row>dest.row){
		    	car[bestcar].current.row=dest.row;
			}
		}
		
		car[bestcar].steps+=stepstook;
		total_steps+=stepstook;
	    //move the car from the callers position to the final destination
		
	}
	fclose(pfile);//close the current file.
	
	pfile=fopen("output.txt","w");//open a new file to print out the output
	
	//print out the format required in the question
	for(i=0;i<vehicles;i++){
		printf("%d ",car[i].rides);//write it to screen
		fprintf(pfile,"%d ",car[i].rides);//write it to a file named output
		
		for(int j=0;j<car[i].rides;j++){
			if(car[i].ridearray[j]>=rideno){//cross-check to make sure its within the ride limit
				car[i].ridearray[j]=0;
			}
			printf("%d ",car[i].ridearray[j]);//write it to the screen
			fprintf(pfile,"%d ",car[i].ridearray[j]);//write it to a file named output
		}

		printf("\n\n\n");
		fprintf(pfile,"%s","\n");
	}
	
			
}


//function to initialize all car's values to zero
void carsinit(struct car_ cars[],int carno){
	for(int i=0;i<carno;i++){
		cars[i].steps=0;
		cars[i].current.row=0;
		cars[i].current.col=0;
		cars[i].rides=0;
		for(int j=0;j<516;j++){
			cars[i].ridearray[j]=0;
		}
	}
} 

//get integer from a char array
int arrayget(int index,char array[],int *pos){
	char buffer[10];int i=0;
	while(isdigit(array[index])){
		buffer[i]=array[index];i++;index++;
	}
	buffer[i++]='\0';
	*pos=index+1;
	return(atoi(buffer));
}

//function to return the distance between the caller and the cars position
int finddistance(struct vector caller,struct vector car){
	int distance=abs(caller.row-car.row)+abs(caller.col-car.row);
	return distance;
}
