#include "FileIn.h"

FileIn::FileIn()
	: BaseFileIO()
{
	latestReadSize = 0;
	bin = false;		// Ĭ���ַ���
}

FileIn::FileIn(std::string fileName, _mode_code op, bool binary)
	: BaseFileIO(fileName, f_in, op)
{
	latestReadSize = 0;
	bin = binary;
}

FileIn::~FileIn()
{
}

int FileIn::getLatestReadSize()
{
	return latestReadSize;
}

bool FileIn::openFile(std::string filePath, _mode_code op, bool binary)
{
	latestReadSize = 0;
	bin = binary;
	return BaseFileIO::openFile(filePath, f_in, op);
}

bool FileIn::isBinaryVisit()
{
	return bin;
}

int FileIn::strToInt(std::string str)
{
	if (str == "")
		return 0;
	// ʹ��sstream���ַ���ת������
	std::istringstream is(str);
	int num;
	is >> num;
	return num;
}

double FileIn::strToDouble(std::string str)
{
	if (str == "")
		return 0.0;
	// ʹ��sstream���ַ���ת�ɸ�����
	std::istringstream is(str);
	double num;
	is >> num;
	return num;
}

FileIn & operator >> (FileIn & fop, int & number)
{
	// �����ļ����ʷ�ʽ���в�ͬ�Ķ�ȡ�ļ�����
	if (fop.isBinaryVisit()) {		
		fop.latestReadSize = fop.readFile(&number, sizeof(int));
		// ����ļ�ʲô��û����������Ĭ��numberֵΪ0
		if (fop.latestReadSize == 0)
			number = 0;
	}
	else {
		std::string numStr;
		fop >> numStr;
		number = fop.strToInt(numStr);
	}
	return fop;
}

FileIn & operator >> (FileIn & fop, double & number)
{
	// �����ļ����ʷ�ʽ���в�ͬ�Ķ�ȡ�ļ�����
	if (fop.isBinaryVisit()) {
		fop.latestReadSize = fop.readFile(&number, sizeof(double));
		// ����ļ�ʲô��û����������Ĭ��numberֵΪ0
		if (fop.latestReadSize == 0)
			number = 0.0;
	}
	else {
		std::string strNum;
		fop >> strNum;
		number = fop.strToDouble(strNum);
	}
	return fop;
}

FileIn & operator >> (FileIn & fop, char & ch)
{
	fop.latestReadSize = fop.readFile(&ch, sizeof(char));
	// ����ļ�ʲô��û����������Ĭ��numberֵΪ0
	if (fop.latestReadSize == 0)
		ch = 0;
	return fop;
}

FileIn & operator >> (FileIn & fop, std::string & str)
{
	str.clear();
	char tar;
	fop.latestReadSize = 0;
	do {
		fop >> tar;
		// ����Ƿ񵽴��ļ�β���߶���һ�����ʣ���������ַ�����ȡ
		if (tar == ' ' || fop.isEof()) break;	
		str += tar;		// һ��ֻ��1���ַ�����˽�����װ����
		++fop.latestReadSize;	// ͳ�ƶ�����ֽ�����
	} while (true);
	return fop;
}
