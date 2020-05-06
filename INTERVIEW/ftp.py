#!/usr/bin/python  
from ftplib import FTP  
import sys,os  
f=FTP(sys.argv[1])  
sys.stdout.write("user:")  
user=sys.stdin.readline().strip()  
sys.stdout.write("password:")  
passwd=sys.stdin.readline().strip()  
if not len(user):  
    f.login()  
    print "anonymous login ok"  
else:  
    f.login(user,passwd)  
    print "login ok"  
print f.getwelcome()  
  
sys.stdout.write(">>")  
def writeline(data):  
    fd.write(data+"\n")  
type="binary"  
  
  
class DirEntry:  
    def __init__(self,line):  
        self.parts=line.split(None,8)  
    def isvalid(self):  
        return len(self.parts)>=6  
    def gettype(self):  
        return self.parts[0][0]  
    def getfilename(self):  
        if self.gettype()!='l':  
            return self.parts[-1]  
        else:  
            return self.parts[-1].split('->',1)[0]  
    def getlinkdest(self):  
        if self.gettype()=='l':  
            return self.parts[-1].split('->',1)[-1]  
        else:  
            raise RuntimeError,"getlindest() called on non-link item"  
  
class DirScanner(dict):  
    def addline(self,line):  
        obj=DirEntry(line)  
        if obj.isvalid():  
            self[obj.getfilename()]=obj  
def downloadfile(ftpobj,filename):  
    ftpobj.voidcmd("TYPE I")  
    datasock,estsize=ftpobj.ntransfercmd("RETR %s"% filename)  
    transbytes=0  
    fd=open(filename,'wb')  
    while 1:  
        buf=datasock.recv(2048)  
        if not len(buf):  
            break  
        fd.write(buf)  
        transbytes+=len(buf)  
        sys.stdout.write("%s Received %d"% (filename,transbytes))  
        if estsize:  
            sys.stdout.write("of %d bytes(%.1f%%)\r"% (estsize,100.0*float(transbytes)/float(estsize)))  
        else:  
            sys.stdout.write("bytes\r")  
        sys.stdout.flush()  
    sys.stdout.write("\n")  
    fd.close()  
    datasock.close()  
    ftpobj.voidresp()  
      
def downloaddir(ftpobj,localpath,remotepath):  
    print "*"*80  
    print "***Processing directory ",remotepath  
    print "*"*80  
    localpath=os.path.abspath(localpath)  
    oldlocaldir=os.getcwd()  
    if not os.path.isdir(localpath):  
        os.mkdir(localpath)  
    olddir=ftpobj.pwd()  
    try:  
        os.chdir(localpath)  
        ftpobj.cwd(remotepath)  
        d=DirScanner()  
        f.dir(d.addline)  
        for filename,entryobj in d.items():  
            if entryobj.gettype()=='-':  
                downloadfile(ftpobj,filename)  
            elif entryobj.gettype()=='d':  
                downloaddir(ftpobj,localpath+'/'+filename,remotepath+'/'+filename)  
            #   print "***Processing directory ",remotepath  
    finally:  
        os.chdir(oldlocaldir)  
        ftpobj.cwd(olddir)  
          
  
  
  
  
#print("\033[1;33m Hello World. \033[0m \n");  
while 1:  
    cmd=sys.stdin.readline().strip()  
    input=[]  
    input=cmd.split()  
    if input[0]=="ls":  
        count=0  
        if len(input)==1:  
            entries=[]  
            f.dir(entries.append)  
            print "%d entries"% len(entries)  
            print "-"*80  
            for entry in entries:  
                if entry[0]=='d':  
                    temp=entry.split()  
                    if count%2==0:  
                        sys.stdout.write("\033[0;32m%-50s\033[0m"% temp[8])  
                        count+=1  
                    elif count%2==1:  
                        sys.stdout.write("\033[0;32m%-50s\033[0m\n"% temp[8])  
                        count+=1  
                else:  
                    temp=entry.split()  
                    if count%2==0:  
                        sys.stdout.write("%-50s"% temp[8])  
                        count+=1  
                    elif count%2==1:  
                        sys.stdout.write("%-50s\n"% temp[8])  
                        count+=1  
            print "-"*80  
        elif len(input)==2 and input[1]=="-l":  
            entries=[]  
            f.dir(entries.append)  
            print "-"*80  
            print "%d entries"% len(entries)  
            for entry in entries:  
                if entry[0]=='d':  
                    sys.stdout.write("\033[0;32m%-50s\033[0m\n"% entry)  
                else:  
                    sys.stdout.write("%-50s\n"% entry)  
                      
                      
            print "-"*80  
    elif input[0]=="settype":  
        type=input[1]  
        if type=="binary":  
            print "type set to:",type  
        elif type=="ascll":  
            print "type set to:",type  
        else:  
            print "set usage:settype binary|ascll"  
    elif input[0]=="pwd":  
        print "current dir:",f.pwd()  
    elif input[0]=="getdir":  
        try:  
            for dir in input[1:]:  
                temp=f.pwd()  
                if temp!='/':  
                    temp=temp+'/'+dir  
                else:  
                    temp=temp+dir  
                downloaddir(f,dir,temp)  
                print "dir downloaded ok"  
        except:  
            print "this is not a correct dir"  
            continue  
    elif input[0]=="get":  
        try:  
            if type=="ascll":  
                if input[1]=="-p":  
                    if not os.path.isdir(input[2]):  
                        print "not a valid path"  
                        continue  
                    else:  
                        os.chdir(input[2])  
                        print "starting ro download...."  
                        for filename in input[3:]:  
                            fd=open(filename,'wt')  
                            f.retrlines("RETR "+filename,writeline)  
                            fd.close()  
                else:  
                    print "starting to download...."  
                    for filename in input[1:]:  
                        fd=open(filename,'wt')  
                        f.retrlines("RETR "+filename,writeline)  
                        fd.close()  
                    print "downloaded ok"  
            elif type=="binary":  
                if input[1]=="-p":  
                    if not os.path.isdir(input[2]):  
                        print "not valid dir"  
                        continue  
                    else:  
                        os.chdir(input[2])  
                          
                        print "starting to download......"  
                        f.voidcmd("TYPE I")  
                        for filename in input[3:]:  
                            #ifd=open(filename,'wb')  
                            #f.retrbinary("RETR "+filename,fd.write)  
                            #fd.close()  
                            datasock,estsize=f.ntransfercmd("RETR "+filename)  
                            transbytes=0  
                            fd=open(filename,'wb')  
                            while 1:  
                                buf=datasock.recv(2048)  
                                if not len(buf):  
                                    break  
                                fd.write(buf)  
                                transbytes+=len(buf)  
                                sys.stdout.write("Received %d"% transbytes)  
                                if estsize:  
                                    sys.stdout.write("of %d bytes(%.1f%%)\r"% (estsize,100.0*float(transbytes)/float(estsize)))  
                                else:  
                                        sys.stdout.write("bytes\r")  
                                sys.stdout.flush()  
                            sys.stdout.write("\n")  
                            fd.close()  
                            datasock.close()  
                            f.voidresp()  
      
                   
                else:  
                    print "starting to download......"  
                    f.voidcmd("TYPE I")  
                    for filename in input[1:]:  
                        #ifd=open(filename,'wb')  
                        #f.retrbinary("RETR "+filename,fd.write)  
                        #fd.close()  
                        datasock,estsize=f.ntransfercmd("RETR "+filename)  
                        transbytes=0  
                        fd=open(filename,'wb')  
                        while 1:  
                            buf=datasock.recv(2048)  
                            if not len(buf):  
                                break  
                            fd.write(buf)  
                            transbytes+=len(buf)  
                            sys.stdout.write("Received %d"% transbytes)  
                            if estsize:  
                                sys.stdout.write("of %d bytes(%.1f%%)\r"% (estsize,100.0*float(transbytes)/float(estsize)))  
                            else:  
                                    sys.stdout.write("bytes\r")  
                            sys.stdout.flush()  
                        sys.stdout.write("\n")  
                        fd.close()  
                        datasock.close()  
                        f.voidresp()  
                        print "file:"+filename+" downloaded ok"  
        except:  
               print "find a erro "  
               continue  
    elif input[0]=="cd":  
            try:  
                f.cwd(input[1])  
                print "changing directory to",input[1]  
        except:  
                print "dir does not exit"  
                continue  
    elif input[0]=="put":  
          for filename in input[1:]:  
                fd=open(filename,'rb')  
                datasock,esize=f.ntransfercmd('STOR %s'% os.path.basename(filename))  
                esize=os.stat(filename)[6]  
                transbytes=0  
                  
                while 1:  
                buf=fd.read(2048)  
                if not len(buf):  
                    break  
                datasock.sendall(buf)  
                transbytes+=len(buf)  
                sys.stdout.write("send %d of %d bytes(%.1f%%)\r"% (transbytes,esize,100.0*float(transbytes/float(esize))))  
                sys.stdout.flush()  
            datasock.close()  
            sys.stdout.write("\n")  
            fd.close()  
            f.voidresp()  
    elif input[0]=="del":  
            try:  
                for filename in input[1:]:  
                    sys.stdout.write("delete file:%s,y or n?"% filename)  
                answer=sys.stdin.readline()  
                if (answer[0]!='y'):  
                    continue  
                else:  
                        f.delete(filename)  
                        print "file:",filename," deleted"  
  
        except:  
            continue  
    elif input[0]=="rmdir":  
        for dir in input[1:]:  
            sys.stdout.write("delete dir:%s.y or n?"% dir )  
            answer=sys.stdin.readline()  
            if (answer[0]!='y'):  
                continue  
            else:  
                f.rmd(dir)  
                print "dir :%s deleted ok"% dir  
    elif input[0]=="mkdir":  
        for dir in input[1:]:  
            f.mkd(dir)  
            print "dir %s make ok"% dir  
    elif input[0]=="rename":  
        if len(input)==3:  
            f.rename(input[1],input[2])  
        else:  
            print "usage:rename filename newfilename "  
            continue  
                  
    elif input[0]=="help":  
        print "command available:"  
        sys.stdout.write("\033[0;32mls |ls -l \033[0m \n")  
        sys.stdout.write("\033[0;32mcd\033[0m dir\n")  
        sys.stdout.write("\033[0;32mget \033[0mfile1 file2 ...\n")  
        sys.stdout.write("\033[0;32msettype \033[0mbinary|ascl \n")  
        sys.stdout.write("\033[0;32mput \033[0mfile1 file2 ... \n")  
        sys.stdout.write("\033[0;32mrmdir \033[0m dir dir ...\n")  
        sys.stdout.write("\033[0;32mdel \033[0m  file1 file2...\n")  
        sys.stdout.write("\033[0;32mquit or exit\033[0m\n")  
        sys.stdout.write("\033[0;32mmkdir \033[0m dir dir ...\n")  
        sys.stdout.write("\033[0;32mrename \033[0m file newfile\n")  
        sys.stdout.write("\033[0;32mmove \033[0m file dir \n")  
        sys.stdout.write("\033[0;32mpwd\033[0m \n")  
        sys.stdout.write("\033[0;32mgetdir \033[0m dir dir... \n")  
    elif input[0]=="quit" or input[0]=="exit":  
                sys.exit(0)  
    sys.stdout.write(">>")  
