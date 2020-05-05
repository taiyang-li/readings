#ifndef _APUE_H     
#define _APUE_H     

#define _XOPEN_SOURCE   600  /* Single UNIX Specification, Version 3 */     

#include <sys/types.h>       /* some systems still require this */     
#include <sys/stat.h>     
#include <sys/termios.h>     /* for winsize */     
#ifndef TIOCGWINSZ     
#include <sys/ioctl.h>     
#endif     
#include <stdio.h>     /* for convenience */     
#include <stdlib.h>    /* for convenience */     
#include <stddef.h>    /* for offsetof */     
#include <string.h>    /* for convenience */     
#include <unistd.h>    /* for convenience */     
#include <signal.h>    /* for SIG_ERR */     


#define MAXLINE 4096               /* max line length */     

/*  
 *   * Default file access permissions for new files.  
 *    */    
#define FILE_MODE   (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)     

/*  
 *   * Default permissions for new directories.  
 *    */    
#define DIR_MODE    (FILE_MODE | S_IXUSR | S_IXGRP | S_IXOTH)     

typedef void   Sigfunc(int);   /* for signal handlers */    

#if defined(SIG_IGN) && !defined(SIG_ERR)     
#define SIG_ERR ((Sigfunc *)-1)     
#endif     

#define min(a,b)     ((a) < (b) ? (a) : (b))     
#define max(a,b)     ((a) > (b) ? (a) : (b))     

/*  
 *   * Prototypes for our own functions.  
 *    */    
char    *path_alloc(int *);              /* Figure 2.15 */    
long     open_max(void);                 /* Figure 2.16 */    
void     clr_fl(int, int);               /* Figure 3.11 */    
void     set_fl(int, int);               /* Figure 3.11 */    
void     pr_exit(int);                   /* Figure 8.5 */    
void     pr_mask(const char *);          /* Figure 10.14 */    
Sigfunc *signal_intr(int, Sigfunc *);    /* Figure 10.19 */    

int      tty_cbreak(int);                /* Figure 18.20 */    
int      tty_raw(int);                   /* Figure 18.20 */    
int      tty_reset(int);                 /* Figure 18.20 */    
void     tty_atexit(void);               /* Figure 18.20 */    
#ifdef  ECHO    /* only if <termios.h>  has been included */     
struct termios  *tty_termios(void);      /* Figure 18.20 */    
#endif     

void     sleep_us(unsigned int);             /* Exercise 14.6 */    
ssize_t  readn(int, void *, size_t);         /* Figure 14.29 */    
ssize_t  writen(int, const void *, size_t);  /* Figure 14.29 */    
void     daemonize(const char *);            /* Figure 13.1 */    

int      s_pipe(int *);                 /* Figures 17.6 and 17.13 */    
int      recv_fd(int, ssize_t (*func)(int,    
      const void *, size_t));/* Figures 17.21 and 17.23 */    
int      send_fd(int, int);             /* Figures 17.20 and 17.22 */    
int      send_err(int, int,    
    const char *);        /* Figure 17.19 */    
int      serv_listen(const char *);     /* Figures 17.10 and 17.15 */    
int      serv_accept(int, uid_t *);     /* Figures 17.11 and 17.16 */    

int      cli_conn(const char *);        /* Figures 17.12 and 17.17 */    
int      buf_args(char *, int (*func)(int,    
      char **));            /* Figure 17.32 */    

int      ptym_open(char *, int);    /* Figures 19.8, 19.9, and 19.10 */    
int      ptys_open(char *);         /* Figures 19.8, 19.9, and 19.10 */    
#ifdef  TIOCGWINSZ     
pid_t    pty_fork(int *, char *, int, const struct termios *,    
    const struct winsize *);      /* Figure 19.11 */    
#endif     

int     lock_reg(int, int, int, off_t, int, off_t); /* Figure 14.5 */    
#define read_lock(fd, offset, whence, len) \    
lock_reg((fd), F_SETLK, F_RDLCK, (offset), (whence), (len))    
#define readw_lock(fd, offset, whence, len) \     
lock_reg((fd), F_SETLKW, F_RDLCK, (offset), (whence), (len))    
#define write_lock(fd, offset, whence, len) \     
lock_reg((fd), F_SETLK, F_WRLCK, (offset), (whence), (len))    
#define writew_lock(fd, offset, whence, len) \     
lock_reg((fd), F_SETLKW, F_WRLCK, (offset), (whence), (len))    
#define un_lock(fd, offset, whence, len) \     
lock_reg((fd), F_SETLK, F_UNLCK, (offset), (whence), (len))    

  pid_t   lock_test(int, int, off_t, int, off_t);     /* Figure 14.6 */    

#define is_read_lockable(fd, offset, whence, len) \     
(lock_test((fd), F_RDLCK, (offset), (whence), (len)) == 0)    
#define is_write_lockable(fd, offset, whence, len) \     
(lock_test((fd), F_WRLCK, (offset), (whence), (len)) == 0)    

  void    err_dump(const char *, ...);        /* Appendix B */    
  void    err_msg(const char *, ...);    
  void    err_quit(const char *, ...);    
  void    err_exit(int, const char *, ...);    
  void    err_ret(const char *, ...);    
  void    err_sys(const char *, ...);    

  void    log_msg(const char *, ...);         /* Appendix B */    
  void    log_open(const char *, int, int);    
  void    log_quit(const char *, ...);    
  void    log_ret(const char *, ...);    
  void    log_sys(const char *, ...);    

  void    TELL_WAIT(void);        /* parent/child from Section 8.9 */    
  void    TELL_PARENT(pid_t);    
  void    TELL_CHILD(pid_t);    
  void    WAIT_PARENT(void);    
  void    WAIT_CHILD(void);    

#endif  /* _APUE_H */    
