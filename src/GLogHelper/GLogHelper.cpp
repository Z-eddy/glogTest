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

const static string LOGDIR{ "log" };//��¼��·��
const static string MKDIR{ "mkdir " + LOGDIR };//�����ļ�

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
	//cout << _access("./log", 0) << endl;
	if (_access(("./"+LOGDIR).c_str(), 0)) {//�ж��Ƿ�����ļ���
		system(MKDIR.c_str());//�Զ������ļ���
	}

	if (appName == "") {
		appName = "app.exe";
	}
	//FLAGS_log_dir = "./log/";//ָ�����λ��
	FLAGS_colorlogtostderr = true;//��ʾ������ɫ
	FLAGS_alsologtostderr = true;//ͬʱ�����stderr
	//������־�洢·��,�ļ���ǰ׺
	google::SetLogDestination(google::INFO, string{ LOGDIR + "/INFO_" }.c_str());
	google::SetLogDestination(google::WARNING, string{ LOGDIR + "/WARNING_" }.c_str());
	google::SetLogDestination(google::ERROR, string{ LOGDIR + "/ERROR_" }.c_str());
	google::SetLogDestination(google::FATAL, string{ LOGDIR + "/FATAL_" }.c_str());


	FLAGS_logbufsecs = 2;//������־ʱ��2��
	FLAGS_max_log_size = 200;//�����־��С200M
	FLAGS_stop_logging_if_full_disk = true;//����д��ʱֹͣд��

	google::SetLogFilenameExtension(appName.c_str());//�����ָ��ӵ�INFO֮��ĺ���

	google::InstallFailureSignalHandler();
	google::InstallFailureWriter(&errHandle);//ϵͳ�������

	google::InitGoogleLogging("");//��ʼ��
}

GLogHelper::~GLogHelper() {
	google::ShutdownGoogleLogging();
}
