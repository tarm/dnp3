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
#ifndef __UINT8LE_H_
#define __UINT8LE_H_

#include <cstdint>
#include <cstring>

#include "WriteBuffer.h"
#include "ReadOnlyBuffer.h"

namespace openpal
{

class UInt48LE
{
public:

	static int64_t Read(const uint8_t* apStart);
	static void Write(uint8_t* apStart, int64_t aValue);

	inline static int64_t ReadBuffer(ReadOnlyBuffer& buffer)
	{
		auto ret = Read(buffer);
		buffer.Advance(Size);
		return ret;
	}

	static void WriteBuffer(WriteBuffer& buffer, int64_t aValue)
	{
		Write(buffer, aValue);
		buffer.Advance(Size);
	}

	const static int64_t MAX = 281474976710655ULL; // 2^48 -1
	const static size_t Size = 6;
	typedef int64_t Type;
};

}

#endif
