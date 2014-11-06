/* vi: ts=4 sw=4 sts=4
 * Program:		Name
 * File:        EntryExit.cpp
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
// platform
#include "stdafx.h"

// project
#include "RSPlugin.h"
#include "EntryExit.h"
#include "Callback.h"

// Required
bool Init(CServiceRequest* p) {
	MyIUIServiceNotifyCallbackImpPtr pIUIServiceNotifyCB	= RS::CreateInstance<MyIUIServiceNotifyCallbackImp>();
	MyIUIServiceNotifyCallbackImpPtr pIUIServiceNotifyCBSep	= RS::CreateInstance<MyIUIServiceNotifyCallbackImp>();
	pIUIServiceNotifyCBSep->useSep(true);
	pIUIServiceNotifyCBSep->appendTitle(" (with _ sep)");
	//save the pointer to the CServiceRequest*
	if( pIUIServiceNotifyCB && pIUIServiceNotifyCB->SetCServiceRequest(p) &&
		pIUIServiceNotifyCBSep && pIUIServiceNotifyCBSep->SetCServiceRequest(p) ) {
		//Install the menu item to the Tools menu
			return pIUIServiceNotifyCB->AddToToolsMenu() && pIUIServiceNotifyCBSep->AddToToolsMenu();
	}
	return false;
}

// Required
bool Exit() {
	return false;
}
