#include <iostream>
#include "glog/logging.h"
using std::cout;
using std::ends;
using std::endl;

/*
以下是参数,记得在前面加上FLAGS_
logtostderr (bool, default=false)    //是否将所有日志输出到 stderr，而非文件
alsologtostderr(bool,default=false)　　//是否同时将日志输出到文件和stderr
minloglevel (int, default=google::INFO)　　//限制输出到 stderr 的部分信息，包括此错误级别和更高错误级别的日志信息
stderrthreshold (int, default=google::ERROR)　　//除了将日志输出到文件之外，还将此错误级别和更高错误级别的日志同时输出到 stderr，这个只能使用 -stderrthreshold=1 或代码中设置，而不能使用环境变量的形式。（这个参数可以替代上面两个参数）
colorlogtostderr(bool, default=false)　　//将输出到 stderr 上的错误日志显示相应的颜色
v (int, default=0)　　//只记录此错误级别和更高错误级别的 VLOG 日志信息
log_dir (string, default="")　　//设置日志文件输出目录
v (int, default=0)　　//只有当自定义日志（VLOG）级别值小于此值时，才进行输出，默认为0(注：自定义日志的优先级与GLOG内置日志优级相反，值越小优先级越高！！！)。
vmodule (string, default="")　　//分文件（不包括文件名后缀，支持通配符）设置自定义日志的可输出级别，如：GLOG_vmodule=server=2,client=3 表示文件名为server.* 的只输出小于 2 的日志，文件名为 client.* 的只输出小于 3 的日志。如果同时使用 GLOG_v 选项，将覆盖 GLOG_v 选项。
*/

/*
输出格式问题:
E0924 22:19:15.123456 19552 filename.py:87] some message
（1）第一个字母表示日志的类型，E表示error，I表示info，W表示warning，F表示fatal
（2）紧接在后面的表示记录日志的时间，格式为MMDD，比如这里0924，表示的是9月24日
（3）紧接在日期后面的是时间，格式为HH:MM:SS.microseconds，比如这里的时间是22时19分15秒123456毫秒
（4）紧接着是线程的ID，即Process ID，也就是上面的19552
（5）紧接着是运行的程序文件，比如test.py
（6）最后是记录这一句日志是在文件中的哪一行发生的，比如87，指的是这句话是在py文件中的87行
*/
int main(int argc,char *argv[])
{
	FLAGS_log_dir = "./logs/";//设置存访的文件夹
	FLAGS_colorlogtostderr = true;//设置stderr输出的字体是否区分颜色
	FLAGS_alsologtostderr = true;//是否同时输入到文件和stderr
	FLAGS_v = 3;//VLOG只记录<=3的日志
	//FLAGS_logtostderr = true;//全部输出到stderr中
	google::InitGoogleLogging(argv[0]);//根据获得的运行程序名来命名文件,也可以自定义指定程序名
	//gflags::ParseCommandLineFlags(&argc, &argv, true);//此必须启用gflags的lib、include后,才能通过命令行预设FLAGS的值
	//google::SetStderrLogging(google::INFO);//输入到stderr的级别
	VLOG(3) << "test";
	LOG(INFO) << "test0";//白色字体
	LOG(WARNING) << "test1";//黄色字体
	LOG(ERROR) << "test2";//红色字体
	//LOG(FATAL) << "test3";//红色字体
	for (int i{ 0 }; i != 10; ++i) {
		LOG_FIRST_N(ERROR, 5) << "LOG_FIRST_N(ERROR,5):" << i;
	}
	google::ShutdownGoogleLogging();//与InitGoogleLogging成对出现,关闭文件记录
}