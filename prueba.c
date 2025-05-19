#include <sys/stat.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

int RecursiveSearch(char *Dir){
    DIR *Directory;
    struct dirent *entry;
    struct stat filestat;

    printf("I am Reading %s Directory\n", Dir);

    Directory = opendir(Dir);
    if(Directory == NULL)
    {
        perror("Unable to read directory.. i'm leaving\n");
        return(1); // leave
    }

    /* Read directory entries */
    while( (entry=readdir(Directory)) )
    {
        char fullname[100];
        sprintf(fullname, "%s/%s",Dir,entry->d_name);
        stat(fullname,&filestat);
        if( S_ISDIR(filestat.st_mode) ){
            printf("%4s: %s\n","Dir",fullname);
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 )
            {
                // Recursion
                printf("\n*Entering a subDirectory*\n");
                RecursiveSearch(fullname);
                printf("\n*Leaving a subDirectory*\n");
            }
        }
        else
            printf("%4s: %s\n","File",fullname);
    }
    closedir(Directory);

    return(0);
}

int main(int ac, char **av)
{
    struct stat info;
    if (1 < ac)
    {
        RecursiveSearch(av[1]);
    }
    return 0;
}
