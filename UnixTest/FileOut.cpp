#include "FileOut.h"

FileOut::FileOut()
	: BaseFileIO()
{
	latestWrittenSize = 0;
	bin = false;		// Ĭ���ַ���
}

FileOut::FileOut(std::string fileName, _mode_code visitMode, _mode_code op, bool bin)
	: BaseFileIO(fileName, visitMode, op)
{
	latestWrittenSize = 0;
	this->bin = bin;
}

FileOut::~FileOut()
{
}

int FileOut::getLatestWrittenSize()
{
	return latestWrittenSize;
}

bool FileOut::openFile(std::string filePath, _mode_code visitMode, _mode_code op, bool bin)
{
	latestWrittenSize = 0;
	this->bin = bin;
	return BaseFileIO::openFile(filePath, visitMode, op);
}

bool FileOut::isBinaryVisit()
{
	return bin;
}

std::string FileOut::numToStr(const int number)
{
	// ʹ��sstream������ת���ַ���
	std::ostringstream os;
	os << number;
	return os.str();
}

std::string FileOut::numToStr(const double number)
{
	// ʹ��sstream��������ת���ַ���
	std::ostringstream os;
	os << number;
	return os.str();
}

FileOut & operator<<(FileOut & fop, int & number)
{
	// �����ļ����ʷ�ʽ���в�ͬ��д���ļ�����
	if (fop.isBinaryVisit()) {
		fop.latestWrittenSize = fop.writeFile(&number, sizeof(int));
	}
	else {
		fop << fop.numToStr(number);
	}
	return fop;
}

FileOut & operator<<(FileOut & fop, double & number)
{
	// �����ļ����ʷ�ʽ���в�ͬ��д���ļ�����
	if (fop.isBinaryVisit()) {
		fop.latestWrittenSize = fop.writeFile(&number, sizeof(double));
	}
	else {
		fop << fop.numToStr(number);
	}
	return fop;
}

FileOut & operator<<(FileOut & fop, char & ch) 
 {
	fop.latestWrittenSize = fop.writeFile(&ch, sizeof(char));
	return fop;
}

FileOut & operator<<(FileOut & fop, const std::string & str)
{
	// ����ϵͳAPI����������const char*���Ͳ�������˸ĳ�char*���ʹ���
	char * pTemp = new char[str.size() + 1];
	strcpy(pTemp, str.data());
	fop.latestWrittenSize = fop.writeFile(pTemp, sizeof(char) * str.size());
	delete pTemp;
	return fop;
}
