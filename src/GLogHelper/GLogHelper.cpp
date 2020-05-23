#include "GLogHelper.h"
#include<string>
#include<fstream>
#include <io.h>
#include<iostream>
using std::cout;
using std::endl;
using std::ends;
using std::string;
using std::ofstream;

const static string LOGDIR{ "log" };//记录的路径
const static string MKDIR{ "mkdir " + LOGDIR };//建立文件

//准备注册的函数,用以持有系统的错误,并输出到日志文件
void errHandle(const char*data, int size) {
	const string str( data,size );
	ofstream ofs{ "glog_dump.log",std::ios::app };
	if (ofs) {
		ofs << str;
		ofs.close();
	}
	LOG(ERROR) << str;
}

GLogHelper::GLogHelper(std::string appName/*=""*/) {
	//cout << _access("./log", 0) << endl;
	if (_access(("./"+LOGDIR).c_str(), 0)) {//判定是否存在文件夹
		system(MKDIR.c_str());//自动建立文件夹
	}

	if (appName == "") {
		appName = "app.exe";
	}
	//FLAGS_log_dir = "./log/";//指定输出位置
	FLAGS_colorlogtostderr = true;//显示区分颜色
	FLAGS_alsologtostderr = true;//同时输出到stderr
	//设置日志存储路径,文件名前缀
	google::SetLogDestination(google::INFO, string{ LOGDIR + "/INFO_" }.c_str());
	google::SetLogDestination(google::WARNING, string{ LOGDIR + "/WARNING_" }.c_str());
	google::SetLogDestination(google::ERROR, string{ LOGDIR + "/ERROR_" }.c_str());
	google::SetLogDestination(google::FATAL, string{ LOGDIR + "/FATAL_" }.c_str());


	FLAGS_logbufsecs = 2;//缓冲日志时间2秒
	FLAGS_max_log_size = 200;//最大日志大小200M
	FLAGS_stop_logging_if_full_disk = true;//磁盘写满时停止写入

	google::SetLogFilenameExtension(appName.c_str());//将名字附加到INFO之类的后面

	google::InstallFailureSignalHandler();
	google::InstallFailureWriter(&errHandle);//系统错误持有

	google::InitGoogleLogging("");//初始化
}

GLogHelper::~GLogHelper() {
	google::ShutdownGoogleLogging();
}
