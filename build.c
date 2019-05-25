/* 
Instructions to use this script:

1. Compile the script using gcc build.c -o build (to be done only once)
2. Use the compiled binary to build and compile your SFML Programs as follows:
   Say, your program filename is prog.cpp, then, to build and compile it do (on terminal) :
    $ ./build prog
3. The program is compiled now, run it using :
    $ ./prog
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char *argv[]){
    if (argc<2){
        printf("Please specify a filename to build\n");
        return 0;
    }
    char *filename = argv[1];
    
    char command1[60] = "g++ -c ";
    strcat(command1, filename);
    strcat(command1, ".cpp");
    
    char command2[200] = "g++ ";
    strcat(command2, filename);
    strcat(command2, ".o -o ");
    strcat(command2, filename);
    strcat(command2, " -lsfml-graphics -lsfml-window -lsfml-system -lm");

    system(command1);
    system(command2);
    printf("Source built succesfully\n");

    return 0;
}
