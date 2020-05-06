#include <iostream>
#include <string>
using namespace std;

class Image
{
	public:
		Image(const string& name) : _name(name) {}
		virtual ~Image() {}
		virtual void show() {}
	protected:
		string _name;
};

class BigImage : public Image
{
	public:
		BigImage(const string& name) : Image(name) {}
		virtual ~BigImage() {}
		virtual void show()
		{
			cout << "Image name: " << _name << endl;
		}
};

class BigImageProxy : public Image
{
	private:
		BigImage* _image;
	public:
		BigImageProxy(const string& name) : Image(name), _image(NULL) {}
		virtual ~BigImageProxy()
		{
			if (_image)
				delete _image;
		}

		virtual void show()
		{
			if (_image == NULL)
			{
				_image = new BigImage(_name);
			}
			_image->show();
		}
};

int main()
{
	Image* image = new BigImageProxy("proxy.jpg");
	image->show();
	delete image;
	return 0;
}
