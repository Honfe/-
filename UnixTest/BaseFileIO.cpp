#include "BaseFileIO.h"

BaseFileIO::BaseFileIO()
{
	id = OPEN_FAIL;	// �ļ���ʶ����Ϊ��Ч
	eof = false;			// �ļ���ʶ��Ч�������eofĬ��false
	err = NO_ERR;
}

BaseFileIO::BaseFileIO(std::string fileName, _mode_code visitMode, _mode_code op)
{
	id = __OPEN_FILE(fileName.data(), visitMode, op);
	// �����ļ������Ľ�������ô������
	if (id == OPEN_FAIL) {
		err = OPEN_ERR;
	}
	else {
		err = NO_ERR;
	}
	eof = false;
}

BaseFileIO::~BaseFileIO()
{
	// �����ʱ�ļ�δ�رգ���ر��ļ�
	if (id != OPEN_FAIL) {
		__CLOSE_FILE(id);
	}
}

bool BaseFileIO::openFile(std::string filePath, _mode_code visitMode, _mode_code op)
{
	// ����ļ��򿪲����Ľ���������´������
	if ((id = __OPEN_FILE(filePath.data(), visitMode, op)) != OPEN_FAIL) {
		err = NO_ERR;
		eof = false;		// �մ򿪵��ļ�EOFĬ��false
		return true;
	}
	else {
		err = OPEN_ERR;
		return false;
	}
}

int BaseFileIO::readFile(void * buffer, int type)
{
	int readSize = 0;
	eof = false;	// ��ȡ֮ǰĬ��eofΪfalse
	// ��ȡ�ļ�������ȡ���
	if ((readSize = __READ_FROM_FILE(id, buffer, type)) >= 0) {
		if (readSize == 0)		// �����ȡ0���ֽ���˵�������ļ�β��
			eof = true;
		err = NO_ERR;
		return readSize;
	}
	else {
		err = READ_ERR;
		return -1;
	}
}

int BaseFileIO::writeFile(void * buffer, int type)
{
	_file_int writtenSize = 0;
	// д���ļ������д�����
	if ((writtenSize = __WRITE_TO_FILE(id, buffer, type)) >= 0) {
		err = NO_ERR;
		return writtenSize;
	}
	else {
		err = WRITE_ERR;
		return -1;
	}
}

int BaseFileIO::setPositionFilePointor(int absPos, int offset)
{
	int pos = 0;
	// ���ı��ļ�ָ������
	if ((pos = __SET_POSITION_FILE(id, absPos, offset)) != SEEK_FAIL) {
		err = NO_ERR;
		return pos;
	}
	else {
		err = SEEK_ERR;
		return -1;
	}
}

bool BaseFileIO::closeFile()
{
	// ����ļ��ر����
	if (__CLOSE_FILE(id) == CLOSE_SUC) {
		err = NO_ERR;
		id = OPEN_FAIL;	// �����ļ���ʶ����
		return true;
	}
	else {
		err = CLOSE_ERR;
		return false;
	}
}

bool BaseFileIO::isEof()
{
	return eof;
}

int BaseFileIO::getErrorCode()
{
	return err;
}

std::string BaseFileIO::getErrorMsg()
{
	std::string msg;
	// ��������벢������Ӧ�Ĵ�����Ϣ
	switch (err) {
	case NO_ERR:
		msg = "no error";
		break;
	case OPEN_ERR:
		msg = "open file error";
		break;
	case READ_ERR:
		msg = "read file error";
		break;
	case WRITE_ERR:
		msg = "write file error";
		break;
	case SEEK_ERR:
		msg = "change file pointer error";
		break;
	case CLOSE_ERR:
		msg = "close file error";
		break;
	default:
		break;
	}
	return msg;
}

// Windows���������еĺ���������API��ʽת��
#ifdef _WIN32 

inline int __inline_WriteToFile(_file_id id, void * buffer, int size)
{
	_file_int writtenSize = 0;
	if (::WriteFile(id, buffer, size, &writtenSize, NULL)) {
		return writtenSize;
	}
	else {
		return WRITE_ERR;
	}
}

inline int __inline_ReadFromFile(_file_id id, void * buffer, int size)
{
	_file_int readSize = 0;
	if (::ReadFile(id, buffer, size, &readSize, NULL)) {
		return readSize;
	}
	else {
		return READ_ERR;
	}
}

#endif
