/* vi: ts=4 sw=4 sts=4
 * Program:		Name
 * File:        EntryExit.h
 * Namespace:   RSServices
 * Description: 
 * Disposition:
 *
 * Copyright:   (c) Copyright 2010 Thomson Reuters.
 *
 * All users of this sample code and any associated documentation or files are
 * bound by the terms and conditions in the EndNote(R) API - RSServices Development
 * Kit License Agreement.  This code is provided “as is” without warranty of 
 * any kind, either express or implied.
 *
*/
#pragma once

#include "RSPlugin.h"

#if OS_MAC > 0
#  define DECLSPEC
#else
#  define DECLSPEC	__declspec(dllexport)
#endif


// namespace
using namespace RSServices;


extern "C" {

#if OS_MAC > 0
#  pragma GCC visibility push(default)
#endif

	// Required functions for an RSPlugin
DECLSPEC	bool Init(CServiceRequest* p);
DECLSPEC	bool Exit();

#if OS_MAC > 0
#  pragma GCC visibility pop
#endif
}	// extern "C"
