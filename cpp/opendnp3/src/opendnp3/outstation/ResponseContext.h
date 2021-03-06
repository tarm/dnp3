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
#ifndef __RESPONSE_CONTEXT_H_
#define __RESPONSE_CONTEXT_H_

#include <openpal/Uncopyable.h>

#include "opendnp3/app/StaticRange.h"
#include "opendnp3/app/APDUResponse.h"
#include "opendnp3/outstation/StaticResponseTypes.h"

#include  "opendnp3/outstation/StaticResponseContext.h"
#include  "opendnp3/outstation/EventResponseContext.h"

namespace opendnp3
{

class Database;

/**
 *  Coordinates the event & static response contexts to do multi-fragments responses
 */
class ResponseContext : private openpal::Uncopyable
{

public:

	ResponseContext(Database* pDatabase, OutstationEventBuffer* pBuffer, const StaticResponseTypes& rspTypes);

	IINField ReadAllObjects(const GroupVariationRecord& record);
	IINField ReadRange(const GroupVariationRecord& record, const StaticRange& range);

	void Reset();

	bool IsComplete() const;

	AppControlField LoadSolicited(ObjectWriter& writer, const EventResponseConfig& config);

private:

	static AppControlField GetControl(bool fir, bool fin, bool hasEvents);

	uint16_t fragmentCount;
	StaticResponseContext staticContext;
	EventResponseContext eventContext;
};

}

#endif
