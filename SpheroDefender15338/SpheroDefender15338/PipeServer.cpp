#include "PipeServer.h"
#include <string>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <Windows.h>
using namespace std;
using namespace std::chrono;

string stringData(int xPos[10], int yPos[10], int detectedObject)
{
	string data;
	// add xPos and yPos of blobs to the string
	for (int i = 0; i < 10; i++)
	{
		data = data + to_string(round((float)xPos[i] * 2.135)) + "," + to_string(round(((float)yPos[i]) * 2.2)) + ",";
	}
	// add detectedObject as last number of the string
	data = data + to_string(detectedObject);
	return data;
}

void pipeToUnity(string myString) {
	HANDLE mypipe = INVALID_HANDLE_VALUE;
	mypipe = CreateNamedPipe("\\\\.\\pipe\\mypipe", PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, PIPE_UNLIMITED_INSTANCES, 1024, 1024, NMPWAIT_USE_DEFAULT_WAIT, NULL);
	if (mypipe == INVALID_HANDLE_VALUE) {
		//cout << "Failed" << endl; 
	}
	////cout << "Waiting for client" << endl; 
	if (!ConnectNamedPipe(mypipe, NULL)) {
		if (ERROR_PIPE_CONNECTED != GetLastError()) {
			//cout << "FAIL" << endl; 
		}
		//cout << "Named pipe didn't connect" << endl; 
	}
	////cout << "Connected!" << endl; 
	//Send over the message 
	const byte * byteArray = new byte[myString.length() + 1];
	byteArray = (const unsigned char*)myString.c_str();
	////cout << "make array of size " << myString.length() + 1 << endl; 
	DWORD arrayLength, cbWritten; arrayLength = myString.length() + 1;
	////cout << "arrayLength value is " << arrayLength; 
	if (!WriteFile(mypipe, byteArray, arrayLength, &cbWritten, NULL)) {
		wprintf(L"failiure w/err 0x%08lx\n", GetLastError);
	}
	////cout << "Sent bytes " << endl; 
	CloseHandle(mypipe);
	//system("pause"); 
}


PipeServer::PipeServer()
{
}


PipeServer::~PipeServer()
{
}
