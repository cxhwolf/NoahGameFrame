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

#include "NFIStateMachine.h"
#include "NFCIdleState.h"

NFCIdleState::NFCIdleState(float fHeartBeatTime, NFIPluginManager* p)
	: NFIState(IdleState, fHeartBeatTime, p)
{
    m_pKernelModule = pPluginManager->FindModule<NFIKernelModule>();
    m_pAIModule = pPluginManager->FindModule<NFIAIModule>();
    m_pMoveModule = pPluginManager->FindModule<NFIMoveModule>();
	m_pElementModule = pPluginManager->FindModule<NFIElementModule>();
	m_pHateModule = pPluginManager->FindModule<NFIHateModule>();
}

NFCIdleState::~NFCIdleState()
{

}

bool NFCIdleState::Enter(const NFGUID& self, NFIStateMachine* pStateMachine)
{
    if (!NFIState::Enter(self, pStateMachine))
    {

			//看是否有战斗能力
            switch (pStateMachine->LastState())
            {
                case NFAI_STATE::FightState:
                    //找人继续打
                    Execute(self, pStateMachine);
                    break;

                default:
                    break;
            }
    }

    return true;
}

bool NFCIdleState::Execute(const NFGUID& self, NFIStateMachine* pStateMachine)
{
    if (!NFIState::Execute(self, pStateMachine))
    {

            //查找是否有可以攻击的对象
            NFGUID ident = m_pHateModule->QueryMaxHateObject(self);
            if (!ident.IsNull())
            {
                pStateMachine->ChangeState(FightState);
            }
            else
            {
                if (m_pKernelModule->GetPropertyInt(self, "MoveSpeed") > 0)
                {
                    RandomIdle(self, pStateMachine);
                }
            }
    }

    return true;
}

bool NFCIdleState::Exit(const NFGUID& self, NFIStateMachine* pStateMachine)
{


    return true;
}

bool NFCIdleState::DoRule(const NFGUID& self, NFIStateMachine* pStateMachine)
{
    return true;
}

bool NFCIdleState::RandomIdle(const NFGUID& self, NFIStateMachine* pStateMachine)
{
	//如果是定点的，则不走，继续idle
	NFAI_NPC_TYPE eMoveType = (NFAI_NPC_TYPE)(m_pKernelModule->GetPropertyInt(self, "MoveType"));

	switch (eMoveType)
	{
	case NFAI_NPC_TYPE::MASTER_TYPE:
	case NFAI_NPC_TYPE::HERO_TYPE:
		{
			float fRand = (float)(rand() / double(RAND_MAX));
			if (fRand < 0.4f)
			{
				pStateMachine->ChangeState(PatrolState);
			}
		}
		break;

	default:
		break;
	}

    return false;
}
