#include <iostream>
#include <cstdlib>
#include <ctime>   
#include <queue>
#include <string>
#include <algorithm> 
#include <functional>
#include <list>

using namespace std; 

template <class T>
void my_print(const T &t)
{
	cout << t << endl;
}

int main()
{	
	srand(time(NULL));  // 用当前时间初始化计时器 
	vector<int> vi0; 
	for (int i=0; i<10000; i++)
		vi0.push_back(rand()%10000);
	
	vector<int> vi(vi0);
	list<int> li(vi0.begin(), vi0.end());
	
	
	clock_t  start, stop;
	
	// 计时1
	start = clock();
	sort(vi.begin(), vi.end());
	stop = clock(); 
	cout << "vector sort took time: " << (double) (stop-start)/CLOCKS_PER_SEC << " seconds" << endl; 
	

	// 计时2
	start = clock();
	li.sort();
	stop = clock(); 
	cout << "list sort took time: " << (double) (stop-start)/CLOCKS_PER_SEC << " seconds" << endl; 

	// 重置
	/*li.clear(); 
	for (auto it=vi0.begin(); it!=vi.end(); ++it) 
		li.push_back(*it);
	*/
	copy(vi0.begin(), vi0.end(), li.begin());

	// li中内容复制到vi中，并对vi进行排序，再将vi复制到li中
	start = clock();
	copy(li.begin(), li.end(), vi.begin());
	sort(vi.begin(), vi.end());
	copy(vi.begin(), vi.end(), li.begin());
	stop = clock();
	cout << "copy and sort method took time: " << (double) (stop-start)/CLOCKS_PER_SEC << " seconds" << endl; 


	system("pause");
	return 0;
}



