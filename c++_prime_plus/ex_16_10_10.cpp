// vect3.cpp -- using STL functions
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


using namespace std;


struct Review {
    string title;
    int rating;
	double price;
};

bool FillReview(Review & rr);   
void ShowReview(const Review & rr); 

void sort_review(int sort_type, vector<Review> &books); 
void sort_type_menu();

// 比较函数符
bool compare_by_title(const Review &a, const Review &b);
bool compare_by_rating(const Review &a, const Review &b);
bool compare_by_price(const Review &a, const Review &b);


int main()
{
    vector<Review> books;
    Review temp;
	int sort_type;
    while (FillReview(temp))
        books.push_back(temp);
	
    if (books.size() > 0)
    {
		sort_type_menu();
		cin >> sort_type;
		sort_review(sort_type, books);
	}
    else
        cout << "No entries. ";
    cout << "Bye.\n";
	system("pause");
    return 0;
}

bool FillReview(Review & rr)
{
    cout << "Enter book title (quit to quit): " << endl;;

    getline(cin,rr.title);   
    if (rr.title == "quit") 
        return false;
	
    cout << "Enter book rating: " << endl;
    cin >> rr.rating;
    if (!cin)
        return false;
	
	cout << "Enter book price: " << endl;
	cin >> rr.price;
	if (!cin)
		return false;

    // get rid of rest of input line 
    while (cin.get() != '\n')
        continue;
    return true;
}


void ShowReview(const Review & rr)
{
	cout << rr.rating << "\t" << rr.title << "\t" << rr.price << endl; 
}

void sort_type_menu()
{
	cout << "----- choose how to sort		-----------" << endl; 
	cout << "---   1: order by raw					---" << endl;
	cout << "---   2: order by alphabet				---" << endl;
	cout << "---   3: order by rating ascending     ---" << endl;
	cout << "---   4: order by rating descending    ---" << endl;
	cout << "---   5: order by price  ascending     ---" << endl;
	cout << "---   6: order by price  descending    ---" << endl;	
	cout << "---   0: quit                          ---" << endl;
}

// 原始顺序显示 ok
// 字母表顺序显示 ok
// 评级升序实现
// 评级降序实现
// 价格升序实现
// 价格降序实现 
void sort_review(int sort_type, vector<Review> &books)
{
	vector<Review> temp(books);
	
	switch(sort_type)
	{
	case 1:
		break;
	case 2:
		sort(temp.begin(), temp.end(), compare_by_title);
		for_each(temp.begin(), temp.end(), ShowReview);
		break;
	case 3:
		sort(temp.begin(), temp.end(), compare_by_rating);
		for_each(temp.begin(), temp.end(), ShowReview);
		break;
	case 4:
		sort(temp.begin(), temp.end(), compare_by_rating);
		for_each(temp.rbegin(), temp.rend(), ShowReview);
		break;
	case 5:
		sort(temp.begin(), temp.end(), compare_by_price);
		for_each(temp.begin(), temp.end(), ShowReview);
		break;
	case 6:
		sort(temp.begin(), temp.end(), compare_by_price);
		for_each(temp.rbegin(), temp.rend(), ShowReview);
		break;
	}
}

bool compare_by_title(const Review &a, const Review &b)
{
	return a.title.compare(b.title) < 0;
}
bool compare_by_rating(const Review &a, const Review &b)
{
	return a.rating < b.rating;
}
bool compare_by_price(const Review &a, const Review &b)
{
	return a.price < b.price;
}



