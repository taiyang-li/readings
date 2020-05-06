#include <iostream>
#include <vector>
#include <algorithm>
#include <dirent.h>
#include <opencv/cv.h>
#include <opencv2/highgui/highgui.hpp> 

using namespace std;

class Dir_Service                                                                  
{                                                                                  
    private:                                                                           
        bool _is_closed;                                                               
        string _dir;                                                                   
        DIR* _dp;                                                                      

    public:                                                                            
        Dir_Service(const string& dir);                                                
        ~Dir_Service();                                                                

        bool open();                                                                   
        bool close();                                                                  
        void read(vector<string>& filenames);                                          
};                   

Dir_Service::Dir_Service(const string& dir) : 
    _is_closed(false), _dir(dir), _dp(NULL)
{
}

Dir_Service::~Dir_Service()
{
    close();
}

bool Dir_Service::open()
{
    if ((_dp = opendir(_dir.c_str())) == NULL)
    {   
        return false;
    }   

    return true;
}

bool Dir_Service::close()
{   
    if(!_is_closed)
    {   
        int ret = closedir(_dp);
        _is_closed = true;
    }
    return true;
}

void Dir_Service::read(vector<string>& filenames)
{
    filenames.clear();
    struct dirent* dirp;
    while((dirp = readdir(_dp)) != NULL)
    {
        string filename(dirp->d_name);
        if (filename != "." && filename != "..")
        {
            filenames.push_back(filename);
        }
    }
}

int main()
{
    // get files
    vector<string> files;
    Dir_Service dir("/mnt/sandisk");
    dir.open();
    dir.read(files);
    dir.close();
    sort(files.begin(), files.end());

    // init video
    CvSize size = cvSize(720, 480); 
    double fps = 15;
    // CvVideoWriter *writer = cvCreateVideoWriter("/home/myvideo.avi", CV_FOURCC('P', 'I', 'M', '1'), fps, size); 
    CvVideoWriter *writer = cvCreateVideoWriter("/home/myvideo.avi", CV_FOURCC('M','J','P','G'), fps, size); 
    cvNamedWindow("avi");

    IplImage *dst = cvCreateImage(size,8,3);
    IplImage *src;

    for(vector<string>::iterator it = files.begin(); it != files.end(); it++)
    {
        string cname = "/mnt/sandisk/" + *it; 
        cout << cname << endl;
        src = cvLoadImage(cname.c_str());  
        cvResize(src, dst, CV_INTER_LINEAR);
        // cvShowImage("avi", dst);  

        cvWriteFrame(writer, dst); 
        cvReleaseImage(&src);
    }

    cvReleaseVideoWriter(&writer); 
    cvReleaseImage(&dst);
    return 0;
}
