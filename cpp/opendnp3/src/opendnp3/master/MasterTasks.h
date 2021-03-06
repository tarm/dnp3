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

#ifndef __MASTER_TASKS_H_
#define __MASTER_TASKS_H_

#include "opendnp3/master/ClearRestartTask.h"
#include "opendnp3/master/EnableUnsolicitedTask.h"
#include "opendnp3/master/StartupIntegrityPoll.h"
#include "opendnp3/master/DisableUnsolicitedTask.h"
#include "opendnp3/master/CommandTask.h"
#include "opendnp3/master/SerialTimeSyncTask.h"

namespace opendnp3
{

class MasterTasks
{

public:

	MasterTasks(openpal::Logger* pLogger, ISOEHandler* pSOEHandler, openpal::IUTCTimeSource* pTimeSource);

	// master tasks (startup and in respond to IIN bits) that can be "failed"
	EnableUnsolicitedTask enableUnsol;
	ClearRestartTask clearRestartTask;
	StartupIntegrityPoll startupIntegrity;
	DisableUnsolicitedTask disableUnsol;	
	SerialTimeSyncTask serialTimeSync;

	// reconfigurable task for doing commands
	CommandTask commandTask;
	
};

}



#endif
