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

#ifndef NFC_NET_MODULE_H
#define NFC_NET_MODULE_H

#include <iostream>
#include <iosfwd>
#include "NFCNet.h"
#include "NFComm/NFCore/NFQueue.hpp"
#include "NFComm/NFPluginModule/NFINetModule.h"
#include "NFComm/NFPluginModule/NFILogModule.h"
#include "NFComm/NFPluginModule/NFIPluginManager.h"
#include "NFComm/NFMessageDefine/NFMsgDefine.h"

#ifdef _MSC_VER
#pragma warning(disable: 4244 4267)
#endif

#include "NFComm/NFMessageDefine/NFDefine.pb.h"

#ifdef _MSC_VER
#pragma warning(default: 4244 4267)
#endif

class NFCNetModule: public NFINetModule
{
public:
    NFCNetModule(NFIPluginManager* p);

    virtual ~NFCNetModule();

	virtual bool Init();
	virtual bool AfterInit();

    //as client
    virtual void Initialization(const char* strIP, const unsigned short nPort);

    //as server
    virtual int Initialization(const unsigned int nMaxClient, const unsigned short nPort, const int nCpuCount = 4);

    virtual int ExpandBufferSize(const unsigned int size = 1024 * 1024 * 20);

    virtual void RemoveReceiveCallBack(const int nMsgID);

    virtual bool AddReceiveCallBack(const int nMsgID, const NET_RECEIVE_FUNCTOR_PTR& cb);

    virtual bool AddReceiveCallBack(const NET_RECEIVE_FUNCTOR_PTR& cb);

    virtual bool AddEventCallBack(const NET_EVENT_FUNCTOR_PTR& cb);

    virtual bool Execute();


    virtual bool SendMsgWithOutHead(const int nMsgID, const std::string& msg, const NFSOCK nSockIndex);

    virtual bool SendMsgToAllClientWithOutHead(const int nMsgID, const std::string& msg);

    virtual bool SendMsgPB(const uint16_t nMsgID, const google::protobuf::Message& xData, const NFSOCK nSockIndex);

    virtual bool SendMsgPBToAllClient(const uint16_t nMsgID, const google::protobuf::Message& xData);

    virtual bool SendMsgPB(const uint16_t nMsgID, const google::protobuf::Message& xData, const NFSOCK nSockIndex,
                           const NFGUID nPlayer, const std::vector<NFGUID>* pClientIDList = NULL);

    virtual bool
    SendMsgPB(const uint16_t nMsgID, const std::string& strData, const NFSOCK nSockIndex, const NFGUID nPlayer,
              const std::vector<NFGUID>* pClientIDList = NULL);

    virtual NFINet* GetNet();

protected:
    void OnReceiveNetPack(const NFSOCK nSockIndex, const int nMsgID, const char* msg, const uint32_t nLen);

    void OnSocketNetEvent(const NFSOCK nSockIndex, const NF_NET_EVENT eEvent, NFINet* pNet);

    void KeepAlive();

private:

    int mnBufferSize;
    NFINet* m_pNet;
    NFINT64 nLastTime;
	std::map<int, std::list<NET_RECEIVE_FUNCTOR_PTR>> mxReceiveCallBack;
    std::list<NET_EVENT_FUNCTOR_PTR> mxEventCallBackList;
    std::list<NET_RECEIVE_FUNCTOR_PTR> mxCallBackList;

	NFILogModule* m_pLogModule;
};

#endif