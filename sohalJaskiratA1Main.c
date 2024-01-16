#include "givenA1.h"

int main(int argc, char *argv[]){
 
   int i;
   int taskNum;
   int t2,t3,t4,t5,t6,t7,t8;
   int courseNum1,courseNum2;
   int cNumFound;
   int numCourse;
   struct courseStruct courseInfo[NUMBER_COURSES];
   struct profStruct profInfo[NUMBER_PROFS];
   char profsNCourses [NUMBER_PROFS][MAX_STR];
   char taughtBy[NUMBER_PROFS][MAX_STR];
   char cNameFound[MAX_STR];
   char userIn[MAX_STR];

   //task 2
   t2 = readCourse (argv[1],courseInfo);//Populating the courseInfo struct
   if(t2==1){
      printf("File read succesfully.\n");
   }
   else{
      printf("Not able to read the file.\n");
   }
   //task 3
   t3 = readProfAndCoursesTaught (argv[2],profInfo,courseInfo);//Populating the profInfo struct
   if(t3==1){
      printf("File read succesfully.\n");
   }
   else{
      printf("Not able to read the file.\n");
   }

   do{
      printf("To perform task 4, enter 4 : \n");
      printf("To perform task 5, enter 5 : \n");
      printf("To perform task 6, enter 6 : \n");
      printf("To perform task 7, enter 7 : \n");
      printf("To perform task 8, enter 8 : \n");
      printf("Enter a value : ");
      scanf("%d", &taskNum);

      switch(taskNum){

         case 4:

            printf("Enter number of Courses : ");
            scanf("%d",&numCourse);
            t4 = nCourses (numCourse, profInfo, profsNCourses);
            printf("Total number of professors that teach %d courses are %d\n",numCourse, t4);
            printf("The professors who teach %d courses are : \n", numCourse);
            for(i=0;i<NUMBER_COURSES;i++){

               printf("%s\n",profsNCourses[i]);

            }
            break;

         case 5: 
         
            printf("Enter a Course Number : ");
            scanf("%d",&courseNum1);
            t5 = getCourseName (courseNum1,cNameFound,courseInfo);
            if(t5==1){

               printf("The course name is : %s\n",cNameFound);
            }
            else{

               printf("Course name not found.\n");

            }
            break;

         case 6: 
            getchar();
            printf("Enter a Course Name: ");
            fgets(userIn,50,stdin);
            userIn[strlen(userIn)-1]='\0';
            t6 = getCourseNum (userIn, &cNumFound,courseInfo);
            if(t6==1){

               printf("The course number is : %d\n",cNumFound);
            }
            else{

               printf("Course number not found.\n");

            }
            break;

         case 7:

            printf("Enter a Course Number : ");
            scanf("%d",&courseNum2);
            t7 = profsTeachingCourse (courseNum2,profInfo,taughtBy);
            if(t7>0){

               printf("The total number of professors teaching the course %d are %d\n",courseNum2,t7);
               printf("The professors are : \n");
               for(i=0;i<NUMBER_PROFS;i++){

                  if(strlen(taughtBy[i])!=0){

                     printf("%s\n",taughtBy[i]);

                  }
               }
            }
            else{

               printf("This course is not taught by any professor.\n");

            }
            break;

         case 8:

            t8 = avgNumCourses (profInfo);
            printf("The average number of courses taught by the professors are: %d\n",t8);
            break;

         default:

            printf("That is an invalid choice\n");
      
      }
     
      }while(taskNum>4 && taskNum<=8);
      return 0;

}