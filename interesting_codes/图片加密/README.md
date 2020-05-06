# codec-with-image
This is codec tools about how to encode text into image and how to decode from it, witten in c++ with opencv library.

1. How to build?  
First make sure you have installed cmake(>=2.8) and opencv(3.3.1.1), then run  
cmake .
make  
Then you will find binary file ./decoder ./encoder generated.

2. How to encode or decode?  
Write the words you want to encode in ./words.txt  
Download a jpg image and rename it to ./input.jpg  
Then run ./encoder, ./output.png is generated, which is a image with encoded words inside.  
If you want to decode, just run ./decode. 3 image files will be output, words.1.png, words.2.png, and words.3.png.  
Open those files, you will find the words you encoded previously. 



