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
#ifndef __SERIAL_TIME_SYNC_TASK_H_
#define __SERIAL_TIME_SYNC_TASK_H_

#include <openpal/IUTCTimeSource.h>

#include "opendnp3/master/SingleResponseTask.h"

namespace opendnp3
{

// Synchronizes the time on the outstation
class SerialTimeSyncTask : public SingleResponseTask
{

public:
	SerialTimeSyncTask(openpal::Logger* pLogger, openpal::IUTCTimeSource* pTimeSource_);

	void Reset();

	virtual bool IsSequenced() const override final { return true; }

	virtual char const* Name() const override final { return "serial (non-LAN) time sync"; }

	virtual TaskPriority Priority() const { return TaskPriority::TIME_SYNC; }

	virtual void BuildRequest(APDURequest& request, const MasterParams& params, uint8_t seq) override final;

	virtual void OnTimeoutOrBadControlOctet(const MasterParams& params, IMasterScheduler& scheduler) override final;

protected:

	virtual TaskStatus OnSingleResponse(const APDUResponseHeader& response, const openpal::ReadOnlyBuffer& objects, const MasterParams& params, IMasterScheduler& scheduler) override final;

private:
	openpal::IUTCTimeSource* pTimeSource;

	// < 0 implies the delay measure hasn't happened yet
	int64_t delay;

	// what time we sent the delay meas
	openpal::UTCTimestamp start;
};

} //ens ns

#endif

