/**
 * Licensed to Green Energy Corp (www.greenenergycorp.com) under one or
 * more contributor license agreements. See the NOTICE file distributed
 * with this work for additional information regarding copyright ownership.
 * Green Energy Corp licenses this file to you under the Apache License,
 * Version 2.0 (the "License"); you may not use this file except in
 * compliance with the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * This project was forked on 01/01/2013 by Automatak, LLC and modifications
 * may have been made to this file. Automatak, LLC licenses these modifications
 * to you under the terms of the License.
 */
#include "PhysTestObject.h"

using namespace openpal;

namespace opendnp3
{

PhysTestObject::PhysTestObject(uint32_t filters, bool aAutoRead) :
	TestObjectASIO(),
	log(),
	mTCPClient(log.root, this->GetService(), "127.0.0.1", 50000),
	mTCPServer(log.root, this->GetService(), "127.0.0.1", 50000),
	mClientAdapter(log.GetLogger(), &mTCPClient, aAutoRead),
	mServerAdapter(log.GetLogger(), &mTCPServer, aAutoRead)
{
	mClientAdapter.SetUpperLayer(&mClientUpper);
	mServerAdapter.SetUpperLayer(&mServerUpper);

	mClientUpper.SetLowerLayer(&mClientAdapter);
	mServerUpper.SetLowerLayer(&mServerAdapter);
}

}
