#include "GLogHelper.h"
#include<string>
#include<fstream>
using std::string;
using std::ofstream;

const static string LOGDIR{ "log" };//��¼��·��
const static string MKDIR{ "mkdir " + LOGDIR };//�����ļ�
const static string EXTENSION{ "log" };//�ļ���չ��

//׼��ע��ĺ���,���Գ���ϵͳ�Ĵ���,���������־�ļ�
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
	system(MKDIR.c_str());//�Զ������ļ���

	if (appName == "") {
		appName = "app.exe";
	}
	google::InitGoogleLogging(appName.c_str());//��ʼ��
	FLAGS_colorlogtostderr = true;//��ʾ������ɫ
	//������־�洢·��,�ļ���ǰ׺
	google::SetLogDestination(google::INFO, string{ LOGDIR + "/INFO_" }.c_str());
	google::SetLogDestination(google::WARNING, string{ LOGDIR + "/WARNING_" }.c_str());
	google::SetLogDestination(google::ERROR, string{ LOGDIR + "/ERROR_" }.c_str());
	google::SetLogDestination(google::FATAL, string{ LOGDIR + "/FATAL_" }.c_str());

	FLAGS_logbufsecs = 2;//������־ʱ��2��
	FLAGS_max_log_size = 200;//�����־��С200M
	FLAGS_stop_logging_if_full_disk = true;//����д��ʱֹͣд��

	google::SetLogFilenameExtension(EXTENSION.c_str());

	google::InstallFailureSignalHandler();
	google::InstallFailureWriter(&errHandle);
}

GLogHelper::~GLogHelper() {
	google::ShutdownGoogleLogging();
}
