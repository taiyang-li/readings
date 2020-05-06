#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <stdio.h>

#include <opencv/cv.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
using namespace cv;
using namespace std;

#define _sq(x) ((x)*(x)) // square
#define _cb(x) abs((x)*(x)*(x)) // absolute value of cube
#define _cr(x) (unsigned char)(pow((x),1.0/3.0)) // cube root
#define HEIGHT 800 
#define WIDTH 1280 
#define DIM 1024
typedef unsigned char uchar;

unsigned char RD(int,int);
unsigned char GR(int,int);
unsigned char BL(int,int);
void pixel_write(int,int);

Mat img(Size(HEIGHT, WIDTH), CV_8UC(3));
int main()
{
    // 设置像素值
    cout << "start setting pixels" << endl;
    for(int j=0;j<HEIGHT;j++)
        for(int i=0;i<WIDTH;i++)
            pixel_write(i,j);

    // 显示图像
    cout << "start showing the pics" << endl;

    IplImage* img2;
    img2 = cvCreateImage(cvSize(HEIGHT, WIDTH),8,3);

    IplImage tmp = img;
    cvCopy(&tmp, img2);

    /*
    cvNamedWindow( "Image", 1 );//创建窗口
    cvShowImage( "Image", img2 );//显示图像
    cvWaitKey(0); //等待按键
    */
    
    // 保存图像 
    cout << "start save the pics" << endl;
    char* fname = "1.jpg"; 
    cvSaveImage(fname, img2);

    /*
    // 打印图像
    cout << "start print img" << endl;
    cout << img << endl;

    // 结束 
    cout << "end." << endl;
    cvDestroyWindow( "Image" );//销毁窗口
    cvReleaseImage( &img2 ); //释放图像   
    */
    return 0;
}

/*
unsigned char RD(int i,int j){
    return (char)(_sq(cos(atan2(j-HEIGHT/2,i-WIDTH/2)/2))*255);
}
 
unsigned char GR(int i,int j){
    return (char)(_sq(cos(atan2(j-HEIGHT/2,i-WIDTH/2)/2-2*acos(-1)/3))*255);
}
 
unsigned char BL(int i,int j){
    return (char)(_sq(cos(atan2(j-HEIGHT/2,i-WIDTH/2)/2+2*acos(-1)/3))*255);
}
*/

/*
unsigned char RD(int i,int j){
    float s=3./(j+99);
    float y=(j+sin((i*i+_sq(j-700)*5)/100./DIM)*35)*s;
    return (int((i+DIM)*s+y)%2+int((DIM*2-i)*s+y)%2)*127;
}

unsigned char GR(int i,int j){
    float s=3./(j+99);
    float y=(j+sin((i*i+_sq(j-700)*5)/100./DIM)*35)*s;
    return (int(5*((i+DIM)*s+y))%2+int(5*((DIM*2-i)*s+y))%2)*127;
}

unsigned char BL(int i,int j){
    float s=3./(j+99);
    float y=(j+sin((i*i+_sq(j-700)*5)/100./DIM)*35)*s;
    return (int(29*((i+DIM)*s+y))%2+int(29*((DIM*2-i)*s+y))%2)*127;
}
*/

/*
unsigned char RD(int i,int j){
    #define D DIM
    #define M m[(x+D+(d==0)-(d==2))%D][(y+D+(d==1)-(d==3))%D]
    #define R rand()%D
    #define B m[x][y]
    return(i+j)?256-(BL(i,j))/2:0;
}

unsigned char GR(int i,int j){
    #define A static int m[D][D],e,x,y,d,c[4],f,n;if(i+j<1){for(d=D*D;d;d--){m[d%D][d/D]=d%6?0:rand()%2000?1:255;}for(n=1
    return RD(i,j);
}

unsigned char BL(int i,int j){
    A;n;n++){x=R;y=R;if(B==1){f=1;for(d=0;d<4;d++){c[d]=M;f=f<c[d]?c[d]:f;}if(f>2){B=f-1;}else{++e%=4;d=e;if(!c[e]){B=0;M=1;}}}}}return m[i][j];
}
*/

/*
unsigned char RD(int i,int j){
    static double k;k+=rand()/1./RAND_MAX;int l=k;l%=512;return l>255?511-l:l;
}

unsigned char GR(int i,int j){
    static double k;k+=rand()/1./RAND_MAX;int l=k;l%=512;return l>255?511-l:l;
}

unsigned char BL(int i,int j){
    static double k;k+=rand()/1./RAND_MAX;int l=k;l%=512;return l>255?511-l:l;
}
*/

/*
unsigned char RD(int i,int j){
    return (unsigned short)sqrt((double)(_sq(i-WIDTH/2)*_sq(j-HEIGHT/2))*2.0);
}

unsigned char GR(int i,int j){
    return (unsigned short)sqrt((double)(
                (_sq(i-WIDTH/2)|_sq(j-HEIGHT/2))*
                (_sq(i-WIDTH/2)&_sq(j-HEIGHT/2))
                )); 
}

unsigned char BL(int i,int j){
    return (unsigned short)sqrt((double)(_sq(i-WIDTH/2)&_sq(j-HEIGHT/2))*2.0);
}
*/

/*
unsigned char RD(int i,int j){
        return (sqrt(_sq(73.-i)+_sq(609-j))+1)/(sqrt(abs(sin((sqrt(_sq(860.-i)+_sq(162-j)))/115.0)))+1)/200;
}

unsigned char GR(int i,int j){
        return (sqrt(_sq(160.-i)+_sq(60-j))+1)/(sqrt(abs(sin((sqrt(_sq(86.-i)+_sq(860-j)))/115.0)))+1)/200;
}

unsigned char BL(int i,int j){
        return (sqrt(_sq(844.-i)+_sq(200-j))+1)/(sqrt(abs(sin((sqrt(_sq(250.-i)+_sq(20-j)))/115.0)))+1)/200;
}
*/

void pixel_write(int i, int j){
    img.at<Vec3b>(i, j) = Vec3b(RD(i,j)&255, GR(i,j)&255, BL(i,j)&255);
}
