/**
* FileName��FileIn.h
* Description���ļ������ࣨ���������>>��
* Author��ZiQin
* DateTime��2018-6-1
* Version��v1.0.0
*/

#ifndef FILEIN_H_
#define FILEIN_H_

#include <iostream>
#include <sstream>
#include <string>
#include "BaseFileIO.h"

/**
* ���ų���˵����
* f_bin	�ļ���д���ֽ�������ʽ
*/
#define f_bin	true	

class FileIn : public BaseFileIO {
private:
	int latestReadSize;	// ���һ�δ��ļ�������ֽڴ�С
	bool bin;					// �ļ����Ƿ����ֽ�������ʽ

public:
	// ���캯��
	FileIn();
	/* ������
		fileName���ļ�·��
		visitMode������ģʽ��f_in/f_out��
		op���򿪷�ʽ��f_exist/f_new��
		binary���Ƿ����ֽ�������ʽ��ȡ�ļ���Ĭ���ַ�����
	*/
	FileIn(std::string fileName, _mode_code op, bool binary = false);
	virtual ~FileIn();

	/**
	* ��������getLatestReadSize
	* ���ܣ���ȡ���һ�ζ�ȡ�ļ����ֽڴ�С
	* ��������
	* ����ֵ�����һ�ζ�ȡ�ļ����ֽڴ�С
	*/
	int getLatestReadSize();

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
	bool openFile(std::string filePath, _mode_code op, bool binary = false);

	/**
	* ��Ԫ������>>���������
	* ���ܣ����ļ��ж�ȡ��Ӧ�����ݷŵ��ڶ�������
	*/
	friend FileIn & operator >> (FileIn & fop, int & number);

	friend FileIn & operator >> (FileIn & fop, double & number);

	friend FileIn & operator >> (FileIn & fop, char & ch);

	friend FileIn & operator >> (FileIn & fop, std::string & str);

	/**
	* ��������isBinaryVisit
	* ���ܣ���鵱ǰ�ļ������Ƿ����ֽ�������ʽ
	* ��������
	* ����ֵ���Ƿ����ֽ�������ʽ����
	*/
	bool isBinaryVisit();

private:
	/**
	* ��������strToInt�����ڲ�ʹ�ã�
	* ���ܣ��ַ���ת����
	* ������Ҫת�����ַ���
	* ����ֵ��ת�����
	*/
	int strToInt(std::string str);

	/**
	* ��������strToDouble�����ڲ�ʹ�ã�
	* ���ܣ��ַ���ת������
	* ������Ҫת�����ַ���
	* ����ֵ��ת�����
	*/
	double strToDouble(std::string str);

};

#endif
