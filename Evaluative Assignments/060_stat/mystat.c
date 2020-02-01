#include <ctype.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
//This function is for Step 4
char * time2str(const time_t * when, long ns) {
  char * ans = malloc(128 * sizeof(*ans));
  char temp1[64];
  char temp2[32];
  const struct tm * t = localtime(when);
  strftime(temp1, 512, "%Y-%m-%d %H:%M:%S", t);
  strftime(temp2, 32, "%z", t);
  snprintf(ans, 128, "%s.%09ld %s", temp1, ns, temp2);
  return ans;
}

//getType
/* This function gets the type of a file using its st_mode value */
char * getType(mode_t filemode) {
  if (S_ISBLK(filemode)) {
    char * type = strdup("block special file");
    return type;
  }
  if (S_ISCHR(filemode)) {
    char * type = strdup("character special file");
    return type;
  }
  if (S_ISDIR(filemode)) {
    char * type = strdup("directory");
    return type;
  }
  if (S_ISFIFO(filemode)) {
    char * type = strdup("fifo");
    return type;
  }
  if (S_ISLNK(filemode)) {
    char * type = strdup("symbolic link");
    return type;
  }
  if (S_ISREG(filemode)) {
    char * type = strdup("regular file");
    return type;
  }
  if (S_ISSOCK(filemode)) {
    char * type = strdup("socket");
    return type;
  }
  return NULL;
}

//checkPermissions
/*this function converts a sequence of 3 booleans (read, write and execute) to a string rwx */
char * checkPermisions(int r, int w, int x) {
  char * ans = malloc(3 * sizeof(*ans));
  ans[0] = '-';
  ans[1] = '-';
  ans[2] = '-';
  if (r) {
    ans[0] = 'r';
  }
  if (w) {
    ans[1] = 'w';
  }
  if (x) {
    ans[2] = 'x';
  }
  return ans;
}

//getPermission
/*this function will generate a human readable string describing the permissions to the file
  based on the value of st_mode*/
char * getPermission(mode_t filemode) {
  char * permission = malloc(11 * sizeof(*permission));
  //get 1st char
  switch (filemode & S_IFMT) {
    case S_IFBLK:
      permission[0] = 'b';
      break;
    case S_IFCHR:
      permission[0] = 'c';
      break;
    case S_IFDIR:
      permission[0] = 'd';
      break;
    case S_IFIFO:
      permission[0] = 'p';
      break;
    case S_IFLNK:
      permission[0] = 'l';
      break;
    case S_IFREG:
      permission[0] = '-';
      break;
    case S_IFSOCK:
      permission[0] = 's';
      break;
  }

  //get 2nd to 10th chars in blocks
  char * usr_perm =
      checkPermisions(filemode & S_IRUSR, filemode & S_IWUSR, filemode & S_IXUSR);
  for (int i = 0; i < 3; i++) {
    permission[i + 1] = usr_perm[i];
  }
  free(usr_perm);
  char * grp_perm =
      checkPermisions(filemode & S_IRGRP, filemode & S_IWGRP, filemode & S_IXGRP);
  for (int i = 0; i < 3; i++) {
    permission[i + 4] = grp_perm[i];
  }
  free(grp_perm);
  char * oth_perm =
      checkPermisions(filemode & S_IROTH, filemode & S_IWOTH, filemode & S_IXOTH);
  for (int i = 0; i < 3; i++) {
    permission[i + 7] = oth_perm[i];
  }
  free(oth_perm);
  permission[10] = '\0';
  return permission;
}

//main
/* This function will handle the arguments passed in by the user, call lstat and do the printing */
int main(int argc, char ** argv) {
  //check for correct number of args
  if (argc == 1) {
    fprintf(stderr, "mystat: missing operand\n");
    return EXIT_FAILURE;
  }
  //Loop over argv and print proprieties of all the files
  for (int i = 1; i < argc; i++) {
    struct stat buffer;
    int isGood = lstat(argv[i], &buffer);
    if (isGood != 0) {
      perror("mystat: call to lstat did not succeed");
      return EXIT_FAILURE;
    }
    //compute type of file
    char * type = getType(buffer.st_mode);
    int isDevice = 0;
    if ((!strcmp(type, "block special file")) ||
        (!strcmp(type, "character special file"))) {
      isDevice = 1;
    }
    int isLink = 0;
    char linktarget[256];
    if ((!strcmp(type, "symbolic link"))) {
      isLink = 1;
      ssize_t len = readlink(argv[i], linktarget, 256);
      if (len == -1) {
        perror("mystat: call to readlink did not succeed");
        return EXIT_FAILURE;
      }
      linktarget[len] = '\0';
    }

    //get permissions of file in a 10 char string
    char * permission = getPermission(buffer.st_mode);
    //get name of owner
    struct passwd * passwdStruct = getpwuid(buffer.st_uid);
    //get group name
    struct group * groupStruct = getgrgid(buffer.st_gid);
    //get time strings
    char * accessTimeStr = time2str(&buffer.st_atime, buffer.st_atim.tv_nsec);
    char * modifyTimeStr = time2str(&buffer.st_mtime, buffer.st_mtim.tv_nsec);
    char * changeTimeStr = time2str(&buffer.st_ctime, buffer.st_ctim.tv_nsec);
    //print file proprieties
    if (isLink == 1) {
      printf("  File: %s -> %s\n", argv[i], linktarget);
    }
    else {
      printf("  File: %s\n", argv[i]);
    }

    printf("  Size: %-10lu\tBlocks: %-10lu IO Block: %-6lu %s\n",
           buffer.st_size,
           buffer.st_blocks,
           buffer.st_blksize,
           type);
    if (isDevice == 1) {
      printf("Device: %lxh/%lud\tInode: %-10lu  Links: %-5lu Device type: %d,%d\n",
             buffer.st_dev,
             buffer.st_dev,
             buffer.st_ino,
             buffer.st_nlink,
             major(buffer.st_rdev),
             minor(buffer.st_rdev));
    }
    else {
      printf("Device: %lxh/%lud\tInode: %-10lu  Links: %lu\n",
             buffer.st_dev,
             buffer.st_dev,
             buffer.st_ino,
             buffer.st_nlink);
    }
    printf("Access: (%04o/%s)  Uid: (%5d/%8s)   Gid: (%5d/%8s)\n",
           (buffer.st_mode & ~S_IFMT),
           permission,
           buffer.st_uid,
           passwdStruct->pw_name,
           buffer.st_gid,
           groupStruct->gr_name);
    printf("Access: %s\n", accessTimeStr);
    printf("Modify: %s\n", modifyTimeStr);
    printf("Change: %s\n", changeTimeStr);
    printf(" Birth: -\n");
    //free heap
    free(type);
    free(permission);
    free(accessTimeStr);
    free(modifyTimeStr);
    free(changeTimeStr);
  }
  return EXIT_SUCCESS;
}
