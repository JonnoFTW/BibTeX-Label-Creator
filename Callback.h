/* vi: ts=4 sw=4 sts=4
 * Program:		Name
 * File:		Callback.h
 * Namespace:   RSServices
 * Description:	Header for the implementation of a UI Service
 *				notification callback object.
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

#include <string>
// RSServices
#include "RSPlugin.h"


// namespaces
using namespace RSServices;

struct MyIUIServiceNotifyCallbackImp : IUIServiceNotifyCallback {
	// construction/destruction
	MyIUIServiceNotifyCallbackImp();
	virtual ~MyIUIServiceNotifyCallbackImp();

	// implementations
	virtual void OnMenuItemSelected();

	// remaining is not a part of IUIServiceNotifyCallback
	bool SetCServiceRequest(CServiceRequest* p) { m_pReq = p; return m_pReq?true:false;};
	bool AddToToolsMenu(void);

	private:
		//members
		CServiceRequest*	m_pReq;
		std::string			m_sMenuItemName;

};	// MyIUIServiceNotifyCallbackImp
typedef RS::CBasePtr<MyIUIServiceNotifyCallbackImp> MyIUIServiceNotifyCallbackImpPtr;


