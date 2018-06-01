#ifndef BASEFILEIO_H_
#define BASEFILEIO_H_

#include <iostream>
#include <string>

// ���ݻ����Ĳ�ͬѡ�������ͬ��ͷ�ļ�
#ifdef _WIN32	
// ȡ��UNICODE�Ķ��壬����Windwos.hʹ�ÿ��ַ�����
#undef UNICODE	
#include <Windows.h>
#elif __linux__ || __unix__	
#include <fcntl.h>
#include <unistd.h>
#endif

// ͳһWindows32��Unix/Linux��ƽ̨���ַ�����
#ifdef _WIN32
#define f_new		CREATE_ALWAYS
#define f_exist		OPEN_ALWAYS
#define f_in			GENERIC_READ
#define f_out		GENERIC_WRITE
#define f_cur		FILE_CURRENT
#define f_set		FILE_BEGIN
#define f_end		FILE_END
#elif __linux__ || __unix__	
#define f_new		(O_CREAT | O_TRUNC)
#define f_exist		O_CREAT
#define f_in			O_RDONLY
#define f_out		O_WRONLY
#define f_cur		SEEK_CUR
#define f_set		SEEK_SET
#define f_end		SEEK_END
#endif

// ͳһWindows��Unix/Linuxƽ̨���ַ�����
#ifdef _WIN32
#define OPEN_FAIL			INVALID_HANDLE_VALUE
#define CLOSE_SUC		TRUE
#define SEEK_FAIL			INVALID_SET_FILE_POINTER
#elif __linux__ || __unix__
#define OPEN_FAIL			-1
#define CLOSE_SUC		 0
#define SEEK_FAIL			-1
#endif

// ͳһWindows��Unix/Linux��ƽ̨�ı���������
#ifdef _WIN32
typedef	HANDLE			_file_id;
typedef	DWORD			_mode_code;
typedef	LPCTSTR			_file_string;
typedef	DWORD			_file_int;
typedef	LPCVOID			_file_pvoid;
#elif __linux__ || __unix__
typedef	int					_file_id;
typedef	int					_mode_code;
typedef	const char *		_file_string;
typedef	int					_file_int;
typedef	const void *		_file_pvoid;
#endif

// ͳһWindows��Linux/Unix��ƽ̨���ļ�IO�����ӿ�
#ifdef _WIN32
#define __OPEN_FILE(NAME, VISITMODE, OP)	 \
	::CreateFile((NAME), (VISITMODE),					\
		0, NULL, (OP), FILE_ATTRIBUTE_NORMAL,	\
		NULL)
// ʹ�����������Ժ���API����ת����ʹ֮��Ӧ�궨���API
inline int __inline_WriteToFile(_file_id id, void * buffer, int size);
#define __WRITE_TO_FILE(ID, BUFFER, SIZE)		\
	::__inline_WriteToFile((ID), (BUFFER), (SIZE))
inline int __inline_ReadFromFile(_file_id id, void * buffer, int size);
#define __READ_FROM_FILE(ID, BUFFER, SIZE)	\
	::__inline_ReadFromFile((ID), (BUFFER), (SIZE))
#define __SET_POSITION_FILE(ID, ABSPOS, OFFSET) \
	::SetFilePointer((ID), (OFFSET), NULL, (ABSPOS))
#define __CLOSE_FILE(ID)									\
	::CloseHandle((ID))
#elif __linux__ || __unix__
#define __OPEN_FILE(NAME, VISITMODE, OP)	\
	::open((NAME), (VISITMODE) | (OP))
#define __WRITE_TO_FILE(ID, BUFFER, SIZE)		\
	::write((ID), (BUFFER), (SIZE))
#define __READ_FROM_FILE(ID, BUFFER, SIZE)	\
	::read((ID), (BUFFER), (SIZE))
#define __SET_POSITION_FILE(ID, ABSPOS, OFFSET) \
	::lseek((ID), (OFFSET), (ABSPOS))
#define __CLOSE_FILE(ID)									\
	::close((ID))
#endif

// �ļ�����������
#define NO_ERR			 0
#define OPEN_ERR		-1
#define CLOSE_ERR		-2
#define READ_ERR		-3
#define WRITE_ERR		-4
#define SEEK_ERR		-5

class BaseFileIO {
protected:
	_file_id	id;			// �ļ���ʶ
	bool		eof;		// �ļ�ָ�뵽���ļ�β��־
	int		err;		// ������

public:
	// ���캯��
	BaseFileIO();
	/* ������
		fileName���ļ�·��
		visitMode������ģʽ����/д��
		op��������ʽ
	*/
	BaseFileIO(std::string fileName, _mode_code visitMode, _mode_code op);
	virtual ~BaseFileIO();

	/**
	* ��������openFile
	* ���ܣ����ļ����ߴ����ļ�
	* ������
		fileName���ļ�·��
		visitMode������ģʽ����/д��
		op��������ʽ
	* ����ֵ���򿪳ɹ���ʧ��
	*/
	bool openFile(std::string filePath, _mode_code visitMode, _mode_code op);

	/**
	* ��������readFile
	* ���ܣ����ļ��ж�ȡ����
	* ������
		buffer������д�뻺����
		type���������͵��ֽڴ�С
	* ����ֵ����ȡ�ļ����ֽڴ�С��ʧ�ܷ���-1
	*/
	int readFile(void * buffer, int type);

	/**
	* ��������writeFile
	* ���ܣ�������д���ļ�
	* ������
		buffer����Ҫд���ļ�������
		type��д�����͵��ֽڴ�С
	* ����ֵ��д���ļ����ֽڴ�С��ʧ�ܷ���-1
	*/
	int writeFile(void * buffer, int type);

	/**
	* ��������setPositionPointor
	* ���ܣ������ļ�ָ���λ��
	* ������
		absPos������λ��
		offset�����ھ���λ�õ�ƫ����
	* ����ֵ���ƶ��ļ�ָ��ĳɹ����
	*/
	bool setPositionFilePointor(int absPos, int offset);

	/**
	* ��������closeFile
	* ���ܣ��ر��ļ�
	* ��������
	* ����ֵ���رճɹ����
	*/
	bool closeFile();

	/**
	* ��������isEof
	* ���ܣ��ж��Ƿ񵽴��ļ�β
	* ��������
	* ����ֵ���ļ�ָ���Ƿ��Ѿ������ļ�β
	*/
	bool isEof();

	/**
	* ��������getErrorCode
	* ���ܣ���ȡ������
	* ��������
	* ����ֵ�����һ�β��������Ĵ�����
	*/
	int getErrorCode();

	/**
	* ��������getErrorMsg
	* ���ܣ���ȡ������Ϣ
	* ��������
	* ����ֵ�����һ�β��������Ĵ�����Ϣ
	*/
	std::string getErrorMsg();

};

#endif
