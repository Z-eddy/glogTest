#pragma once
#include<string>
#include "glog/logging.h"
class GLogHelper
{
public:
	//默认的记录路径如果为空,则
	GLogHelper(std::string appName="");
	~GLogHelper();
	//GLogHelper(const GLogHelper&) = delete;
	//GLogHelper& operator=(const GLogHelper&) = delete;
};
