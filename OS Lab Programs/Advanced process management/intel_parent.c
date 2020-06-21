#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
int main()
{
    pid_t i,j,k,m;
    int c=0; // counter to limit the number of new child processes that spawn to 3 instead of endless loop
    // parent creates a child process
    j = fork();
    if( j == -1 ){ 
        perror("fork-2"); 
        exit(2); 
    }
    if( j == 0 ) // first child process
    {
        printf("first child: PID = %u \n", getpid() );
        sleep(5);
        exit(22); // first child exits after 5 seconds
    } // end of first child process block
    // parent is waiting for first child. j is the PID of first child
    k = waitpid( j, &m, WUNTRACED );
    if( k == -1 ){
        perror("wait-1"); 
        exit(3);
    } 
    printf("parent: child %u has been killed or terminated \n", k );
    while( ((WIFSTOPPED(m) != 0) ||  ( WIFEXITED(m) != 0 ) || ( WIFSIGNALED(m) != 0 )) && c<3 )
    {
        i = fork();
        if( i == -1 ){
            perror("fork-1"); 
            exit(1);
        } 
        if( i == 0 ) // 1st child process
        {
            printf("next child: PID = %u \n", getpid() );
            sleep(3);
            exit(0); // next child exits after 3 seconds
        } // end of next child process block
        c++;
        k = wait( NULL );
        if( k == -1 ){ 
            perror("wait-2"); 
            exit(4);
        } 
        printf("parent: child %u has terminated \n", k );
    }

    return 0;
}
