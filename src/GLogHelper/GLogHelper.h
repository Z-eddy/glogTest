#pragma once
#include<string>
#include "glog/logging.h"
class GLogHelper
{
public:
	//Ĭ�ϵļ�¼·�����Ϊ��,��
	GLogHelper(std::string appName="");
	~GLogHelper();
	//GLogHelper(const GLogHelper&) = delete;
	//GLogHelper& operator=(const GLogHelper&) = delete;
};
