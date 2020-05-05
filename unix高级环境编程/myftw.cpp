#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <cstring>
#include <cstdlib>

typedef int Myfunc(const char* path, const struct stat* buf, int type);
static Myfunc myfunc;
static int myftw(char* path, Myfunc* func);
static int dopath(Myfunc* func);
static long nreg, ndir, nblk, nchr, nfifo, nslink, nsock, ntot;

#define FTW_F 1
#define FTW_D 2
#define FTW_DNR 3
#define FTW_NS 4

static char* fullpath;

int main(int argc, char* argv[])
{
  int ret;
  if (argc != 2)
  {
    printf("usage: ftw <pathname>\n");
    exit(-1);
  }
  ret = myftw(argv[1], myfunc);
  ntot = nreg + ndir + nblk + nchr + nfifo + nslink + nsock;
  if (ntot == 0)
    ntot = 1;
  printf("regular files     = %7ld %5.2f %%\n", nreg, nreg*100.0/ntot);
  printf("directories       = %7ld %5.2f %%\n", ndir, ndir*100.0/ntot);
  printf("block special     = %7ld %5.2f %%\n", nblk, nblk*100.0/ntot);
  printf("char special      = %7ld %5.2f %%\n", nchr, nchr*100.0/ntot);
  printf("FIFOs             = %7ld %5.2f %%\n", nfifo, nfifo*100.0/ntot);
  printf("symbolic links    = %7ld %5.2f %%\n", nslink, nslink*100.0/ntot);
  printf("sockets           = %7ld %5.2f %%\n", nsock, nsock*100.0/ntot);
  exit(ret);
}

static int myftw(char* path, Myfunc* func)
{
  fullpath = new char[4096];
  if (fullpath == NULL)
  {
    printf("malloc for fullpath error\n");
    return -1;
  }
  strcpy(fullpath, path);
  printf("%s\n", fullpath);
  return dopath(func);
}

static int dopath(Myfunc* func)
{
  printf("dopath %s\n", fullpath);
  struct stat buf;
  struct dirent *dirp;
  DIR *dp;
  int ret;
  char* ptr;

  // lstat 
  if (lstat(fullpath, &buf) < 0)
    return func(fullpath, &buf, FTW_NS);

  // not directory
  if (S_ISDIR(buf.st_mode) == 0)
    return func(fullpath, &buf, FTW_F);

  if ((ret = func(fullpath, &buf, FTW_D)) != 0)
    return ret;

  // directory not readable
  if ((dp = opendir(fullpath)) == NULL)
    return func(fullpath, &buf, FTW_DNR);

  // directory
  ptr = fullpath + strlen(fullpath);
  *ptr = '/';
  ptr++;
  while ((dirp = readdir(dp)) != NULL)
  {
    if (strcmp(dirp->d_name, ".") == 0 || 
          strcmp(dirp->d_name, "..") == 0)
      continue;

    strcpy(ptr, dirp->d_name);
    ret = dopath(func);
    if (ret != 0)
      break;
  }
  ptr[-1] = '\0';
  if (closedir(dp) < 0)
  {
    printf("close dir %s error\n", fullpath);
    return -1;
  }
  return ret;
}

static int myfunc(const char* path, const struct stat* buf, int type)
{
  printf("path: %s, type: %d\n", path, type);
  switch(type) 
  {
    case FTW_F:
      switch(buf->st_mode & S_IFMT)
      {
        case S_IFREG: 
          nreg++; 
          break;
        case S_IFBLK:
          nblk++;
          break;
        case S_IFCHR:
          nchr++;
          break;
        case S_IFIFO:
          nfifo++;
          break;
        case S_IFLNK:
          nslink++;
          break;
        case S_IFSOCK:
          nsock++;
          break;
        default:
          printf("unknow filetype: %d\n", type);
          return -1;
      }
      break;
    case FTW_D:
      ndir++;
      break;
    case FTW_DNR:
      printf("can't read directory %s\n", path);
      return -2;
    case FTW_NS:
      printf("stat error for %s\n", path);
      break;
    default:
      printf("unknown type: %d\n", type);
      return -3;
  }
  return 0;
}
