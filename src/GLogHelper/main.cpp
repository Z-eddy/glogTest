#include <iostream>
#include "GLogHelper.h"
using std::cout;
using std::endl;
using std::ends;

int main()
{
	GLogHelper glog();
	int arr[2];
	int a = arr[5];
	LOG(INFO) << "test";
}