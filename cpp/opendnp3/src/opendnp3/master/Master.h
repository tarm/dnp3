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
#ifndef __MASTER_H_
#define __MASTER_H_

#include "opendnp3/master/MasterContext.h"
#include "opendnp3/master/CommandMarshaller.h"
#include "opendnp3/master/MasterScan.h"

namespace opendnp3
{

class Master : public openpal::IUpperLayer
{
	public:

	Master(	openpal::IExecutor& executor, 				
				openpal::LogRoot& root, 
				openpal::ILowerLayer& lower,
				ISOEHandler* pSOEHandler,
				openpal::IUTCTimeSource* pTimeSource,
				const MasterParams& params
				);
	
	/// ----- Implement IUpperLayer ------

	virtual void OnLowerLayerUp() override final;
	
	virtual void OnLowerLayerDown() override final;

	virtual void OnReceive(const openpal::ReadOnlyBuffer&) override final;
	
	virtual void OnSendResult(bool isSucccess) override final;

	/// ----- Misc public members -------
	
	ICommandProcessor& GetCommandProcessor();

	MasterScan AddScan(openpal::TimeDuration period, const openpal::Function1<APDURequest&> builder);

	MasterScan AddClassScan(uint8_t classMask, openpal::TimeDuration period);

	MasterScan AddRangeScan(GroupVariationID gvId, uint16_t start, uint16_t stop, openpal::TimeDuration period);
	
	private:

	MasterContext context;
	CommandMarshaller commandMarshaller;
};

}

#endif
