// -*- C++ -*- backward compatiblity header.
// Copyright (C) 1994 Free Software Foundation

#ifndef __COMPLEX_H__
#include <complex>
#endif

namespace std{
	template<typename T>
	void swap(T &a,T &b)
	{
		T temp(a);
		a = b;
		b = temp;
	}
}

class WidgetImpl{
public:
	...
private:
	/*包含了Widget的真正数据*/
	std::vector<double> v;	//可能有许多数据，意味着复制时间很长
};

class Widget{
public:
	Widget(const Widget &rhs);
	Widget& operator=(const Widget &rhs)
	{
		...
		*pImpl1 = *(rhs.pImpl);  //复制Widget时，令它复制其WidgetImpl对象
		...
	}
	...
private:
	WidgetImpl *pImpl;	//指针，所指对象内含Widget真正数据
};

namespace std{
	template<>
	void swap<Widget>(Widget &a,Widget &b)
	{
		//访问私有成员，不能通过编译
		swap(a.pImpl,b.pImpl);
	}
}

class Widget{
public:
	...
	void swap(Widget &other)
	{
		using std::swap;			//令std::swap在此函数内可用
		swap(pImpl,other.pImpl);
	}
	...
};

namespace std{
	template<>
	void swap<Widget>(Widget &a,Widget &b)
	{
		a.swap(b);
	}
}

template<typename T>
class WidgetImpl {...};

template<typename T>
class Widget {...};

namespace std{
	template<typename T>
	void swap<Widget<T>>(Widget<T> &a,Widget<T> &b)
	{
		a.swap(b);
	}
}

namespace std{
	template<typename T>
	void swap(Widget<T> &a,Widget<T> &b)
	{
		a.swap(b);
	}
}

namespace WidgetStuff{
	...
	template<typename T>
	class WidgetImpl {...};

	template<typename T>
	class Widget {...};
	...
	template<typename T>
	void swap(Widget<T> &a,Widget<T> &b)
	{
		a.swap(b);
	}
}