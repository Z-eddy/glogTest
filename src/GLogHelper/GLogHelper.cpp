#include "GLogHelper.h"
#include<string>
#include<fstream>
using std::string;
using std::ofstream;

const static string LOGDIR{ "log" };//记录的路径
const static string MKDIR{ "mkdir " + LOGDIR };//建立文件
const static string EXTENSION{ "log" };//文件扩展名

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
	system(MKDIR.c_str());//自动建立文件夹

	if (appName == "") {
		appName = "app.exe";
	}
	google::InitGoogleLogging(appName.c_str());//初始化
	FLAGS_colorlogtostderr = true;//显示区分颜色
	//设置日志存储路径,文件名前缀
	google::SetLogDestination(google::INFO, string{ LOGDIR + "/INFO_" }.c_str());
	google::SetLogDestination(google::WARNING, string{ LOGDIR + "/WARNING_" }.c_str());
	google::SetLogDestination(google::ERROR, string{ LOGDIR + "/ERROR_" }.c_str());
	google::SetLogDestination(google::FATAL, string{ LOGDIR + "/FATAL_" }.c_str());

	FLAGS_logbufsecs = 2;//缓冲日志时间2秒
	FLAGS_max_log_size = 200;//最大日志大小200M
	FLAGS_stop_logging_if_full_disk = true;//磁盘写满时停止写入

	google::SetLogFilenameExtension(EXTENSION.c_str());

	google::InstallFailureSignalHandler();
	google::InstallFailureWriter(&errHandle);
}

GLogHelper::~GLogHelper() {
	google::ShutdownGoogleLogging();
}
