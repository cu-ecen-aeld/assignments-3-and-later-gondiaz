#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <syslog.h>


int main(int argc, char *argv[])
{

    openlog(NULL, 0, LOG_USER);
    syslog(LOG_INFO, "calling writer");

    if (argc != 3){
        fprintf(stderr, "Usage: %s <writefile> <writestr>\n", argv[0]);
        syslog(LOG_ERR, "Usage: %s <writefile> <writestr>\n", argv[0]);
        return 1;
    }

    char* writefile = argv[1];
    char* writestr  = argv[2];

    printf("writefile: %s\n", writefile);
    printf("writestr : %s\n", writestr);

    // create file
    int f = open(writefile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (f == -1){
        fprintf(stderr, "File %s could not be created\n", writefile);
        syslog(LOG_ERR, "File %s could not be created", writefile);
        return 1;
    }

    // write to file
    ssize_t nr = write(f, writestr, strlen(writestr));
    if (nr == -1){
        fprintf(stderr, "Cannot write into file");
        syslog(LOG_ERR, "Cannot write into file");
        return 1;
    }
    write(f, "\n", 2);

    syslog(LOG_INFO, "writer ran succesfully");
    closelog();

    return 0;
}