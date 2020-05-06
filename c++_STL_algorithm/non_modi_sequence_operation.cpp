#include <iostream>
#include <algorithm>

int main()
{
	int v1[10] = {1,2,2,3,4,5,5};
	int v2[2] = {2,3};
	
	int *p = std::search(v1, v1+5, v2, v2+2);
	if (p != NULL)
		std::cout << "found v2 in v1, position: " << p - v1 << std::endl;
	else
		std::cout << "canot found v2 in v1" << std::endl;

	p = std::search_n(v1, v1+10, 2, 2);
	if (p != NULL)
		std::cout << "found " << 2 << " " << 2 << " in v1" << std::endl;
		

	p = std::search_n(v1, v1+10, 2, 5);
	if (p != NULL)
		std::cout << "found " << 2 << " " << 5 << " in v1" << std::endl;

	p = std::search_n(v1, v1+10, 3, 0);
	if (p != NULL)
		std::cout << "found " << 3 << " " << 0 << " in v1" << std::endl;
	return 0;
}
