#include <iostream>
#include "GLogHelper.h"
using std::cout;
using std::endl;
using std::ends;

int main()
{
	GLogHelper a;
	LOG(WARNING) << "test";
}