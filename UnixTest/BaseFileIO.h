/**
* FileName��BaseFileIO.h
* Description�������ļ�IO����
* Author��ZiQin
* DateTime��2018-6-1
* Version��v1.0.0
*/

#ifndef BASEFILEIO_H_
#define BASEFILEIO_H_

#include <iostream>
#include <string>

// ���ݻ����Ĳ�ͬѡ�������ͬ��ͷ�ļ�
#ifdef _WIN32	
// ȡ��UNICODE�궨�壬����Windwos.hʹ�ÿ��ַ�����
#undef UNICODE	
#include <Windows.h>
#elif __linux__ || __unix__	
#include <fcntl.h>
#include <unistd.h>
#endif

// ͳһWindows32��Unix/Linux��ƽ̨���ַ�����
/**
* ���ų���ʹ��˵����
* f_new		��д�ļ�
* f_exist	�����ļ������ļ����������½��ļ�
* f_in		�����ļ�
* f_out		д���ļ�
* f_cur		�ļ�ָ�뵱ǰλ��
* f_set		�ļ�ָ��ָ���ļ���ͷ
* f_end		�ļ�ָ��ָ���ļ���β
*/
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
/**
* ���ų�������˵����
* OPEN_FAIL	���ļ�ʧ�ܣ������ļ���ʶ������Ч
* CLOSE_SUC	�ر��ļ�ʧ�ܱ�ʶ
* SEEK_FAIL		�ļ�ָ���ƶ�ʧ��
*/
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
#elif __linux__ || __unix__
typedef	int					_file_id;
typedef	int					_mode_code;
typedef	const char *		_file_string;
typedef	int					_file_int;
#endif

// ͳһWindows��Linux/Unix��ƽ̨���ļ�IO�����ӿ�
#ifdef _WIN32				// Windows����
// ���ļ��궨��
#define __OPEN_FILE(NAME, VISITMODE, OP)	 \
	::CreateFile((NAME), (VISITMODE),					\
		0, NULL, (OP), FILE_ATTRIBUTE_NORMAL,	\
		NULL)
// ʹ�����������Ժ���API����ת����ʹ֮��Ӧ�궨���API
inline int __inline_WriteToFile(_file_id id, void * buffer, int size);
inline int __inline_ReadFromFile(_file_id id, void * buffer, int size);
// д�������ļ��궨��
#define __WRITE_TO_FILE(ID, BUFFER, SIZE)		\
	::__inline_WriteToFile((ID), (BUFFER), (SIZE))
// ���ļ������ݺ궨��
#define __READ_FROM_FILE(ID, BUFFER, SIZE)	\
	::__inline_ReadFromFile((ID), (BUFFER), (SIZE))
// �����ļ�ָ��궨��
#define __SET_POSITION_FILE(ID, ABSPOS, OFFSET) \
	::SetFilePointer((ID), (OFFSET), NULL, (ABSPOS))
// �ر��ļ��궨��
#define __CLOSE_FILE(ID)									\
	::CloseHandle((ID))
#elif __linux__ || __unix__	// Unix/Linux����
// ���ļ��궨��
#define __OPEN_FILE(NAME, VISITMODE, OP)	\
	::open((NAME), (VISITMODE) | (OP), S_IRUSR | S_IWUSR | S_IXUSR)
// д�������ļ��궨��
#define __WRITE_TO_FILE(ID, BUFFER, SIZE)		\
	::write((ID), (BUFFER), (SIZE))
// ���ļ������ݺ궨��
#define __READ_FROM_FILE(ID, BUFFER, SIZE)	\
	::read((ID), (BUFFER), (SIZE))
// �����ļ�ָ��궨��
#define __SET_POSITION_FILE(ID, ABSPOS, OFFSET) \
	::lseek((ID), (OFFSET), (ABSPOS))
// �ر��ļ��궨��
#define __CLOSE_FILE(ID)									\
	::close((ID))
#endif

// �ļ�����������
#define NO_ERR			 0		// �޴���
#define OPEN_ERR		-1		// ���ļ�����
#define CLOSE_ERR		-2		// �ر��ļ�����
#define READ_ERR		-3		// ��ȡ�ļ�����
#define WRITE_ERR		-4		// д���ļ�����
#define SEEK_ERR		-5		// �����ļ�ָ�����

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
		visitMode������ģʽ��f_in/f_out��
		op���򿪷�ʽ��f_exist/f_new��
	*/
	BaseFileIO(std::string fileName, _mode_code visitMode, _mode_code op);
	virtual ~BaseFileIO();

	/**
	* ��������openFile
	* ���ܣ����ļ����ߴ����ļ�
	* ������
		fileName���ļ�·��
		visitMode������ģʽ��f_in/f_out��
		op���򿪷�ʽ��f_exist/f_new��
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
	int setPositionFilePointor(int absPos, int offset);

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
