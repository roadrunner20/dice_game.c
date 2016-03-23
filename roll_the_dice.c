
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/signal.h>
#include <signal.h>


int getRandomInteger(int n){
    
    return(rand() % n +1);

}

void action2(){};
void player(FILE *,char *);

int main(int argc, char *argv[]){
  		pid_t pid_1, pid_2, pid_3;
  		FILE *fp;
  		int points, points1, points2 = 0;
  		int player_result, score;
  		fp = fopen("/tmp/gamelog.txt","w+");
  		setbuf(fp,NULL);
  		printf("Please enter the wining total\n");
 													// Checking for correct input
 		if (scanf("%d", &score) != 1)
    {
        printf("You are required to enter a number.\n");
        perror("Wrong Input. Try Again.");
        exit(1);
    }
  		sleep(2);
  		
  		signal(SIGINT,SIG_IGN);                    // Ignoring Ctrl-C 
  		signal(SIGTSTP,SIG_IGN);                   // Ignoring Ctrl-Z
  		signal(SIGUSR1,action2);				// Registering user-defined signal
  			
  		printf("This is a 3-players game with a referee\n");
  
  if((pid_1=fork()) == 0) player(fp,"TOTO");
  sleep(1);
  if((pid_2=fork()) == 0) player(fp,"TITI");
  sleep(1);
  if((pid_3=fork()) == 0) player(fp,"TITO");
  sleep(1);
  

  while(1){
    printf("TOTO plays\n");
    kill(pid_1, SIGUSR1);
    pause();
    rewind(fp);
    fscanf(fp,"%d",&player_result);
    points =points + player_result;
    printf("\nReferee: Total score so far for TOTO: %d\n\n", points);
   // Checking if TOTO WON or not. Logging the details to gamelog.txt in tmp folder of working directory
   				if(points >= score)
   				{
      				printf("Referee: Game over TOTO won\n");
      				rewind(fp);
      				fprintf(fp, "%s", "TOTO WON with scores =  ");
      				fprintf(fp, "%d\n", points);
      				fprintf(fp, "%s", "TITI lost with scores =  ");
      				fprintf(fp, "%d\n", points1);
      				fprintf(fp, "%s", "TITO lost with scores =  ");
      				fprintf(fp, "%d\n", points2);
      				
     				fclose(fp);
      				exit(0);
   				}
   				
   				
    printf("TITI plays\n");
    kill(pid_2, SIGUSR1);
    pause();
    rewind(fp);
    fscanf(fp,"%d",&player_result);
    points1 =points1 + player_result;
    printf("\nReferee: Total score so far for TITI: %d\n\n", points1);
   						// Checking if TITI WON or not. Logging the details to gamelog.txt 
  			  if(points1 >= score)
  			  {
   		  			printf("Referee: Game over TITI won\n");
   		  			rewind(fp);
   		  			fprintf(fp, "%s", "TITI WON with scores =  ");
      				fprintf(fp, "%d\n", points1);
      				fprintf(fp, "%s", "TOTO lost with scores =  ");
      				fprintf(fp, "%d\n", points);
      				fprintf(fp, "%s", "TITO lost with scores =  ");
      				fprintf(fp, "%d\n", points2);
     				  fclose(fp);
     				 exit(0);
               }
               
            
    printf("TITO plays\n");
    kill(pid_3, SIGUSR1);
    pause();
    rewind(fp);
    fscanf(fp,"%d",&player_result);
    points2 =points2 + player_result;
    printf("\nReferee: Total score so far for TITO: %d\n\n", points2);
    					 // Checking if TITI WON or not. Logging the details to gamelog.txt 
   			if(points2 >= score)
   			{
      				printf("\nReferee: Game over TITO won\n");
      				rewind(fp);
   		  			fprintf(fp, "%s", "TITO WON with scores =  ");
      				fprintf(fp, "%d\n", points2);
      				fprintf(fp, "%s", "TOTO lost with scores =  ");
      				fprintf(fp, "%d\n", points);
      				fprintf(fp, "%s", "TITI lost with scores =  ");
      				fprintf(fp, "%d\n", points1);
     				fclose(fp);
      				exit(0);
    		}
  }
}


void player(FILE *fp, char *name)
{
  int points=0;
  int turn;
  srand(time(NULL));
  		while(1)
  		{
    			signal(SIGUSR1, action2); 
    			pause();
   			 	printf("%s: playing my turn\n", name);
    			turn = getRandomInteger(10);
   				rewind(fp);
    			fprintf(fp,"%d",turn);
    			printf("%s: I got %d points\n", name, turn);
    			sleep(3);
    			kill(getppid(), SIGUSR1);
  		}
}
