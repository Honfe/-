/**
* FileName��FileOut.h
* Description���ļ�д���ࣨ���������<<��
* Author��ZiQin
* DateTime��2018-6-1
* Version��v1.0.0
*/

#ifndef FILEOUT_H_
#define FILEOUT_H_

#include <cstring>
#include <string>
#include <sstream>
#include "BaseFileIO.h"

/**
* ���ų���˵����
* f_bin	�ļ���д���ֽ�������ʽ
*/
#define f_bin	true

class FileOut : public BaseFileIO {
private:
	int latestWrittenSize;	// ���һ��д���ļ����ֽڴ�С
	bool bin;						// �ļ����Ƿ����ֽ�������ʽ

public:
	// ���캯��
	FileOut();
	/* ������
		fileName���ļ�·��
		visitMode������ģʽ��f_in/f_out��
		op���򿪷�ʽ��f_exist/f_new��
		binary���Ƿ����ֽ�������ʽ��ȡ�ļ���Ĭ���ַ�����
	*/
	FileOut(std::string fileName, _mode_code visitMode, _mode_code op, bool bin = false);
	virtual ~FileOut();

	/**
	* ��������getLatestWrittenSize
	* ���ܣ���ȡ���һ��д���ļ����ֽڴ�С
	* ��������
	* ����ֵ�����һ��д���ļ����ֽڴ�С
	*/
	int getLatestWrittenSize();

	/**
	* ��������openFile
	* ���ܣ����ļ�
	* ������
	fileName���ļ�·��
	visitMode������ģʽ��f_in/f_out��
	op���򿪷�ʽ��f_exist/f_new��
	binary���Ƿ����ֽ�������ʽ���루Ĭ���ַ�����
	* ����ֵ���򿪳ɹ���ʧ��
	*/
	bool openFile(std::string filePath, _mode_code visitMode, _mode_code op, bool bin = false);

	/**
	* ��Ԫ������<<���������
	* ���ܣ����ڶ�������������д�뵽�ļ���
	*/
	friend FileOut & operator << (FileOut & fop, int & number);

	friend FileOut & operator << (FileOut & fop, double & number);

	friend FileOut & operator << (FileOut & fop, char & ch);

	friend FileOut & operator << (FileOut & fop, const std::string & str);

	/**
	* ��������isBinaryVisit
	* ���ܣ���鵱ǰ�ļ������Ƿ����ֽ�������ʽ
	* ��������
	* ����ֵ���Ƿ����ֽ�������ʽ����
	*/
	bool isBinaryVisit();

private:
	/**
	* ��������numToStr
	* ���ܣ�����ת�ַ���
	* ��������Ҫת��������
	* ����ֵ��ת�����
	*/
	std::string numToStr(const int number);

	/**
	* ��������numToStr
	* ���ܣ�������ת�ַ���
	* ��������Ҫת���ĸ�����
	* ����ֵ��ת�����
	*/
	std::string numToStr(const double number);

};

#endif
