//******************************************************************
//
//
// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//
//
//*****************************************************************
//For /Wal

#pragma once
#pragma warning(push)
#pragma warning(disable : 4820)
#pragma warning(disable : 4619)
#pragma warning(disable : 4548)
#pragma warning(disable : 4668)
#pragma warning(disable : 4365)
#pragma warning(disable : 4710)
#pragma warning(disable : 4371)
#pragma warning(disable : 4826)
#pragma warning(disable : 4061)
#pragma warning(disable : 4640)
#pragma warning(disable : 4996)


#ifndef STDAFX2_H_
#define STDAFX2_H_

// Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
// Windows Header Files:

#include <windows.h>
#include <thread>
#include <mutex>
#include <future>
#include <string>
#include <cassert>
#include <vector>
#include <iostream>
#include <fstream>

#pragma warning(pop) //For /Wall
// TODO: reference additional headers your program requires here

#endif // !STDAFX2_H_
