/*
            This file is part of: 
                NoahFrame
            http://noahframe.com

   Copyright 2009 - 2018 NoahFrame(NoahGameFrame)

   File creator: lvsheng.huang
   
   NoahFrame is opensorece software and you can redistribute it and/or modify
   it under the terms of the License.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include "HelloWorld3Module.h"
#include "NFComm/NFMessageDefine/NFProtocolDefine.hpp"
#include "NFComm/NFPluginModule/NFIEventModule.h"

bool NFCHelloWorld3Module::Init()
{
	
	std::cout << "Hello, world3, Init" << std::endl;

	return true;
}

int NFCHelloWorld3Module::OnEvent(const NFGUID& self, const NFEventDefine event, const NFDataList& arg)
{
	
	std::cout << "OnEvent EventID: " << event << " self: " << self.nData64 << " argList: " << arg.Int(0) << " " << " " << arg.String(1) << std::endl;

	m_pKernelModule->SetPropertyInt(self, "Hello", arg.Int(0));
	m_pKernelModule->SetPropertyString(self, "Hello", arg.String(1));

	return 0;
}

int NFCHelloWorld3Module::OnHeartBeat(const NFGUID& self, const std::string& strHeartBeat, const float fTime, const int nCount)
{

	int64_t unNowTime = NFGetTimeMS();

	std::cout << "strHeartBeat: " << fTime << " Count: " << nCount << "  TimeDis: " << unNowTime - mLastTime << std::endl;

	mLastTime = unNowTime;

	return 0;
}

int NFCHelloWorld3Module::OnClassCallBackEvent(const NFGUID& self, const std::string& strClassName, const CLASS_OBJECT_EVENT event, const NFDataList& arg)
{
	
	std::cout << "OnClassCallBackEvent ClassName: " << strClassName << " ID: " << self.nData64 << " Event: " << event << std::endl;

	if (event == COE_CREATE_HASDATA)
	{
		m_pEventModule->AddEventCallBack(self, NFEventDefine(1), this, &NFCHelloWorld3Module::OnEvent);

		m_pScheduleModule->AddSchedule(self, "OnHeartBeat", this, &NFCHelloWorld3Module::OnHeartBeat, 5.0f, 10 );

		mLastTime = NFGetTimeMS();
	}

	return 0;
}

int NFCHelloWorld3Module::OnPropertyCallBackEvent( const NFGUID& self, const std::string& strProperty, const NFData& oldVar, const NFData& newVar)
{
	
	std::cout << "OnPropertyCallBackEvent Property: " << strProperty << " OldValue: " << oldVar.GetInt() << " NewValue: " << newVar.GetInt() << std::endl;

	return 0;
}

int NFCHelloWorld3Module::OnPropertyStrCallBackEvent( const NFGUID& self, const std::string& strProperty, const NFData& oldVar, const NFData& newVar)
{
	
	std::cout << "OnPropertyCallBackEvent Property: " << strProperty << " OldValue: " << oldVar.GetString() << " NewValue: " << newVar.GetString() << std::endl;

	return 0;
}

bool NFCHelloWorld3Module::AfterInit()
{
	
	std::cout << "Hello, world3, AfterInit" << std::endl;

	m_pKernelModule = pPluginManager->FindModule<NFIKernelModule>();
	m_pElementModule = pPluginManager->FindModule<NFIElementModule>();
	m_pEventModule = pPluginManager->FindModule<NFIEventModule>();
	m_pScheduleModule = pPluginManager->FindModule<NFIScheduleModule>();
	
	
	m_pKernelModule->CreateScene(1);

	m_pKernelModule->AddClassCallBack(NFrame::Player::ThisName(), this, &NFCHelloWorld3Module::OnClassCallBackEvent);

	
	NF_SHARE_PTR<NFIObject> pObject = m_pKernelModule->CreateObject(NFGUID(0, 10), 1, 0, NFrame::Player::ThisName(), "", NFDataList());
	if (!pObject)
	{
		return false;
	}

	pObject->GetPropertyManager()->AddProperty(pObject->Self(), "Hello", TDATA_STRING);
	pObject->GetPropertyManager()->AddProperty(pObject->Self(), "World", TDATA_INT);

	pObject->AddPropertyCallBack("Hello", this, &NFCHelloWorld3Module::OnPropertyStrCallBackEvent);
	pObject->AddPropertyCallBack("World", this, &NFCHelloWorld3Module::OnPropertyCallBackEvent);

	pObject->SetPropertyString("Hello", "hello,World");
	pObject->SetPropertyInt("World", 1111);


	m_pEventModule->DoEvent(pObject->Self(), NFEventDefine(1), NFDataList() << int(100) << "200");

	return true;
}

bool NFCHelloWorld3Module::Execute()
{
	
	//std::cout << "Hello, world3, Execute" << std::endl;

	return true;
}

bool NFCHelloWorld3Module::BeforeShut()
{
	
	std::cout << "Hello, world3, BeforeShut" << std::endl;

	m_pKernelModule->DestroyAll();

	return true;
}

bool NFCHelloWorld3Module::Shut()
{
	
	std::cout << "Hello, world3, Shut" << std::endl;

	return true;
}
