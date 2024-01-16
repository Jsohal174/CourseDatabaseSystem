#include "givenA1.h"

/* 
Task 1 
This function will take in a filename as a string and attempt to create a FILE pointer out of it.
If the file opens successfully, a FILE pointer will be returned. Otherwise, NULL. You will only
open the file for reading, not writing.
*/
FILE *openFileForReading(char fileName [MAX_STR])
{

    FILE * fptr= fopen(fileName,"r");
    return fptr;
}

/* 
Task 2 
This function must read courseNames and courseID from a text file called courses.txt to
populate the array of structs called courseInfo with course names and corresponding course
ids. 
*/
int readCourse (char fileName [MAX_STR],struct courseStruct courseInfo [NUMBER_COURSES]){
    
    int i;
    int len=0;
    FILE *fptr = openFileForReading(fileName);//Using function 1 to open the file.
    if(fptr==NULL){

        return -1;

    }
    else{

        for(i=0;i<NUMBER_COURSES;i++){
       
            fgets(courseInfo[i].courseName, MAX_STR, fptr);//Data from the file gets stored in courseInfo.courseName
            len=strlen(courseInfo[i].courseName);
            courseInfo[i].courseName[len - 1]='\0';//Since fgets places an extra newline character at the end of the input, we need to remove it.
           
        }
        
        for(i=0;i<NUMBER_COURSES;i++){    

            fscanf(fptr,"%d",&courseInfo[i].courseID); ////Data from the file gets stored in courseInfo.courseID   

        }
        return 1;

    }
    fclose(fptr);
}


/* 
Task 3 
This function is used to populate the struct profInfo with names of professors and courses they teach.
*/
int readProfAndCoursesTaught (char fileName [MAX_STR],struct profStruct profInfo [NUMBER_PROFS],struct courseStruct courseInfo [NUMBER_COURSES]){
    
    int i,j;
    char isCourseTaught[7][NUMBER_COURSES];//Created extra array to store data.
    FILE *fptr = openFileForReading(fileName);//Using function 1 to open the file.
    if(fptr==NULL){

        printf("Not able to open the file\n");
        return -1;

    }
    else{

        for(i=0;i<NUMBER_PROFS;i++){

            fgets(profInfo[i].profName,MAX_STR,fptr);//Data from the file gets stored in profInfo.profName.
            if(profInfo[i].profName[strlen(profInfo[i].profName) - 1] == '\n'){//If their is a new line character it will be removed.
                profInfo[i].profName[strlen(profInfo[i].profName) - 1] = '\0';
            }

        }
        for(i=0;i<NUMBER_PROFS;i++){

            for(j=0;j<NUMBER_COURSES;j++){

                fscanf(fptr,"%c",&isCourseTaught[i][j]);//Using isCourseTaught to store data .
                
                if(isCourseTaught[i][j] =='y'||isCourseTaught[i][j]=='Y'){//If it is y or Y profInfo.coursesTaught will be stored with course Id's.

                    profInfo[i].coursesTaught[j]=courseInfo[j].courseID; 
                    
                }

                else{

                    profInfo[i].coursesTaught[j]= -1;//Else we will store -1 in that location.

                }
                if(j == NUMBER_COURSES - 1){//this condition is to remove the newline character.
                    fscanf(fptr, "%*c");
                }
            }
        }  
    }  

    fclose(fptr);
    return 1;

} 


/* 
Task 4 
This function populates an array called profsNCourses with names of all professors who
teach n or more courses (n >= 0). It then returns the total number of professors who teach n
or more courses.
*/
int nCourses (int n,struct profStruct profInfo [NUMBER_PROFS],char profsNCourses [NUMBER_PROFS][MAX_STR]){

    int i,j;
    int profNum=0;
    for(i=0;i<NUMBER_PROFS;i++){
        strcpy(profsNCourses[i],"");//put empty string in the array
        int num =0;
        for(j=0;j<NUMBER_COURSES;j++){

            if(profInfo[i].coursesTaught[j] != -1){//Condition to check courses taught.

                num++;//Number of courses increases by one.

            }
        }

        if(num >= n){//Check condition.

                strcpy(profsNCourses[i],profInfo[i].profName);//copied the prof names into the profsNCourses array.
                profNum++;
                num++;

            }
        }
    return profNum;
    
}



/* 
Task 5 
This function, takes a course number as input, searches for its course name and stores it in
a string parameter (e.g. cNameFound). It returns 1 if the course is found, 0 otherwise. 
*/
int getCourseName (int courseNum,char cNameFound [50],struct courseStruct courseInfo [NUMBER_COURSES]){

    int i;
    for(i=0;i<NUMBER_COURSES;i++){
     
        if(courseNum==courseInfo[i].courseID){//Check if course numbers match.

            strcpy(cNameFound,courseInfo[i].courseName);
            return 1;
        }

    }
    return 0;
}

/* 
Task 6 
This function, takes a course name as input, searches for its course number and stores it in
an output int parameter (e.g. cNumFound). It returns 1 if the course is found, 0 otherwise.
*/
int getCourseNum (char cName [50],int *cNumFound,struct courseStruct courseInfo [NUMBER_COURSES]){

    int i;
    for(i=0;i<NUMBER_COURSES;i++){

        if(strcmp(cName,courseInfo[i].courseName) == 0){//Comparing the strings.

            *cNumFound = courseInfo[i].courseID;
            return 1;
        }

    }
    return 0;
}

/* 
Task 7 
This function, takes a course number as input, searches for the profs teaching it, and
populates array taughtBy with these prof names. It returns the total number of profs
teaching the course courseNum if the course is found, 0 otherwise.
*/
int profsTeachingCourse (int courseNum,struct profStruct profInfo [NUMBER_PROFS],char taughtBy [NUMBER_PROFS][MAX_STR]){
 
    int i,j;
    int profNum = 0;

    for(i=0;i<NUMBER_PROFS;i++){
        
        strcpy(taughtBy[i]," ");
        for(j=0;j<NUMBER_COURSES;j++){

            if(courseNum==profInfo[i].coursesTaught[j]){

                strcpy(taughtBy[i],profInfo[i].profName);//copy names of professors into taughtBy array.
                profNum++;

            }
        }
    }

    return profNum;
}


/*
Task 8 
This function returns the average number of courses taught by a professor. Note that since the
average is typically a float value, you must round it to the next integer when you return the value.
*/
float avgNumCourses (struct profStruct profInfo [NUMBER_PROFS]){

    int i,j;
    int num=0; 
    float avg;  

    for (i = 0; i < NUMBER_PROFS; i++){
        for (j = 0; j < NUMBER_COURSES; j++){

            if(profInfo[i].coursesTaught[j] > -1){
                num++;
            }
        }      
    }
    avg = round((float)num/NUMBER_PROFS);
    
    return avg;    
}









