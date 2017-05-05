
#ifndef __WINSOCKMATTRANSMISSIONSEVER_H__
#define __WINSOCKMATTRANSMISSIONSEVER_H__

#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib,"WS2_32.lib")

//待传输图像默认大小为 640*480，可修改
#define IMG_WIDTH 640   // 需传输图像的宽
#define IMG_HEIGHT 480  // 需传输图像的高
//默认格式为CV_8UC3
#define BUFFER_SIZE IMG_WIDTH*IMG_HEIGHT*3/32

struct recvbuf
{
	char buf[BUFFER_SIZE];
	int flag;
};

class WinsockMatTransmissionServer
{
public:
	WinsockMatTransmissionServer(void);
	~WinsockMatTransmissionServer(void);

private:
	SOCKET sockConn;
	struct recvbuf data;

public:

	// 打开socket连接
	// params : PORT    传输端口
	// return : -1      连接失败
	//          1       连接成功
	int socketConnect(int PORT);


	// 传输图像
	// params : image   待接收图像
	// return : -1      接收失败
	//          1       接收成功
	int receive(cv::Mat& image);


	// 断开socket连接
	void socketDisconnect(void);
};

#endif</winsock2.h></stdio.h>
