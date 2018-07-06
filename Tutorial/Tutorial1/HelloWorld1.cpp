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

#include "HelloWorld1.h"

bool NFCHelloWorld1::Init()
{
	std::cout << typeid(NFCHelloWorld1).name() << std::endl;

    
    std::cout << "Hello, world1, Init" << std::endl;

    return true;
}

bool NFCHelloWorld1::AfterInit()
{
    
    std::cout << "Hello, world1, AfterInit" << std::endl;

    return true;
}

bool NFCHelloWorld1::Execute()
{
    
    //std::cout << "Hello, world1, Execute" << std::endl;

    return true;
}

bool NFCHelloWorld1::BeforeShut()
{
    std::cout << "Hello, world1, BeforeShut1111" << std::endl;

    system("PAUSE");

    
    std::cout << "Hello, world1, BeforeShut" << std::endl;

    return true;
}

bool NFCHelloWorld1::Shut()
{
    
    std::cout << "Hello, world1, Shut" << std::endl;

    return true;
}
