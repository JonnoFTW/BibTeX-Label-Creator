/* vi: ts=4 sw=4 sts=4
 * Program:		BibTeX label generator
 * File:		Callback.cpp
 * Namespace:   std, RSServices
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

// endnote includes
#include "RSPlugin.h"
#include "Callback.h"

// stl
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>

// rapidxml
#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_utils.hpp>
#include <rapidxml/rapidxml_print.hpp>

//boost
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/regex.hpp>

// namspaces
using namespace std;
using namespace RSServices;
using namespace rapidxml;
using namespace boost;


string gen_random(const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
	string str;
    for (int i = 0; i < len; ++i) {
        str.push_back( alphanum[rand() % (sizeof(alphanum) - 1)]);
    }
    return str;
}

/*******************************
 * MyIUIServiceNotifyCallbackImp
 *******************************/

// construction/destruction
MyIUIServiceNotifyCallbackImp::MyIUIServiceNotifyCallbackImp() {
	m_pReq			= NULL;
	m_sMenuItemName	= "Generate BibTeX Labels";
}

MyIUIServiceNotifyCallbackImp::~MyIUIServiceNotifyCallbackImp() {
	m_pReq	= NULL;
}

bool MyIUIServiceNotifyCallbackImp::AddToToolsMenu(void) {
	//make sure the CServiceRequest* is not NULL
	if( !m_pReq ) return false;

	//this is where you would check the version of RSServices,
	//if your plugin makes use of features present only in later
	//versions of RSServices, you should check the version and not
	//install to the Tools menu if the version is too old.
	IVersionPtr	pVersion;
	if( (pVersion=(IVersion*)m_pReq->GetService(kVersion)) == NULL ) return false;
	if( pVersion->GetServiceVersion() < 0x020500 ) return false;

	//Get IUIServicePtr so we can add ourself to the Tools menu
	IUIServicePtr pUI	= (IUIService*)m_pReq->GetService(kGUI);
	if( pUI && (pUI->AddToolsMenuItem(m_sMenuItemName.c_str(),this) == kServiceNoErr) )
		return true;

	return false;
}//MyIUIServiceNotifyCallbackImp::AddToToolsMenu

void MyIUIServiceNotifyCallbackImp::OnMenuItemSelected() {
	if( !m_pReq ) return;
	
	//add your code here
	//Get the IUIService because we want to only alter the showing refs
	IUIServicePtr	pIUIService;
	if( (pIUIService = (IUIService*)m_pReq->GetService(kGUI)) == NULL ) return;

	IUIDatabasePtr	pFrontMostWindow;
	if( pIUIService->GetLibrary(pIUIService->kFrontMost,&pFrontMostWindow) != kServiceNoErr ) return;

	IRecordListPtr	pRecordList;
	if( pFrontMostWindow->GetRecords(pFrontMostWindow->kShowing,&pRecordList) != kServiceNoErr ) return;

	IDatabasePtr	pDB;
	if( pFrontMostWindow->GetDatabase(&pDB) != kServiceNoErr ) return;

	IRecordListPtr	pUpdatedRecordList;
	if( pDB->GetRecordList(&pUpdatedRecordList) != kServiceNoErr ) return;
	pUpdatedRecordList->Clear();
	//ofstream myfile;
	//ofstream log;
	//myfile.open("C:\\temp\\updated.xml");
	//log.open("C:\\temp\\bibtex_log.log");
	set<string> used_labels;
	for(long i=0;i<pRecordList->GetCount();i++) {
		//get the RecordID
		IStringPtr			pRecordID;
		if( (pRecordList->GetRecordID(i,&pRecordID)) != kServiceNoErr ) continue;

		//use the record id to read the IRecord
		IRecordPtr	pRecord;
		if( (pDB->ReadRecord(pRecordID->c_str(),&pRecord)) != kServiceNoErr ) continue;
	
		//GetXML
		IStringPtr	pXML;
		if( (pRecord->GetXML(&pXML)) != kServiceNoErr ) continue;
	
		//convert the IString to string
		string	sXML(pXML->c_str());
		xml_document<> doc;
		vector<char> buffer;
		for(size_t i =0; i < sXML.length(); i++) {
			buffer.push_back(sXML.at(i));
		}
		buffer.push_back('\0'); 
		doc.parse<parse_normalize_whitespace>(&buffer[0]);
		xml_node<> * refNode = doc.first_node("records")->first_node("record");
		string str_label;
		if(refNode->first_node("label") == 0) {
			string author(refNode->first_node("contributors")->first_node("authors")->first_node("author")->first_node("style")->value());
			string year(  refNode->first_node("dates")->first_node("year")->first_node("style")->value()); 
			//log << "Author is:" << author << endl;
			//log << "Year is:" << year << endl;
			boost::algorithm::trim(year); 
			boost::algorithm::trim(author);
			boost::algorithm::to_lower(author);
			std::vector<std::string> strs;
			boost::split(strs,author,boost::is_any_of("\n\t "));
			
			string author_last = strs.back();

			// if the author string contains a comma after the first word,
			// then the first word is the surname, otherwise the 
			// surname is the last
			if(author.find(",") != string::npos /*&& 
				(author_last.at(author_last.size()-1) == '.' ||
				author_last.size() == 1)*/) {
				// there is a comma in the name,
				author_last = strs.front();
				author_last.erase(std::remove(author_last.begin(), author_last.end(), ','), author_last.end());
			}
			str_label = author_last + year.substr(2,2);
			if(used_labels.find(str_label) != used_labels.end()) {
				// label is already in use
				str_label += "-"+gen_random(5);
			} 
			// put the label into the set
			used_labels.insert(str_label);
			
			//log << "BibTex label:"+ str_label << endl;
			char* label_value = doc.allocate_string(str_label.c_str());
			xml_node<> *bibtex_label = doc.allocate_node(node_element,"label",label_value);
			refNode->append_node(bibtex_label);
		} else {
			// there is already a label, we don't need to recreate it,
			// just note that it has been used.
			string existing_label = refNode->first_node("label")->value();
			if(existing_label.empty()) {
				existing_label = refNode->first_node("label")->first_node("style")->value();
			}
			//log << existing_label << " already in use" << endl;
			used_labels.insert(existing_label);
		}
		
		string outXML;
		
		print(back_inserter(outXML),doc,print_no_indenting);
		outXML.erase(std::remove(outXML.begin(), outXML.end(), '\t'), outXML.end());
		boost:regex re("\\r\\r");
		outXML = boost::regex_replace(outXML,re,"");
		//myfile << outXML;

		if( pRecord->SetXML(outXML.c_str()) == kServiceNoErr ) {
				if( pDB->WriteRecord(pRecord) == kServiceNoErr ) {
					(void)pDB->CommitChanges();
					(void)pUpdatedRecordList->AddRecord(pRecordID->c_str());
				}
		}
		
	}
	//myfile.close();
	//log.close();
	(void)pFrontMostWindow->PostAutoGroup("Generated BibTex Labels",pUpdatedRecordList,0,0);
}// MyIUIServiceNotifyCallbackImp::OnMenuItemSelected
