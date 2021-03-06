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
#ifndef __BITFIELD_RANGE_WRITE_ITERATOR_H_
#define __BITFIELD_RANGE_WRITE_ITERATOR_H_

#include <openpal/WriteBuffer.h>
#include <openpal/ISerializer.h>

namespace opendnp3
{

// A facade for writing APDUs to an external buffer
template <class IndexType>
class BitfieldRangeWriteIterator
{
public:

	static BitfieldRangeWriteIterator Null()
	{
		auto buffer = openpal::WriteBuffer::Empty();
		return BitfieldRangeWriteIterator(0, buffer);
	}

	BitfieldRangeWriteIterator(typename IndexType::Type start_, openpal::WriteBuffer& position_) :
		start(start_),
		count(0),
		maxCount(0),
		isNull(position_.Size() < 2 * IndexType::Size),
		range(position_),
		pPosition(&position_)				
	{
		if(!isNull)
		{
			IndexType::WriteBuffer(range, start_);
			pPosition->Advance(2 * IndexType::Size);
			maxCount = pPosition->Size() * 8;
		}
	}

	bool Complete()
	{
		if(isNull || count == 0) return false;
		else
		{
			auto stop = start + count - 1;
			IndexType::Write(range, stop);

			auto num = count / 8;
			if ((count % 8) > 0) ++num;
			pPosition->Advance(num);

			return true;
		}
	}

	bool Write(bool value)
	{
		if(isNull || count >= maxCount) return false;
		else
		{
			auto byte = count / 8;
			auto bit = count % 8;

			if (bit == 0)
			{
				(*pPosition)[byte] = 0; // initialize byte to 0
			}

			if (value)
			{
				(*pPosition)[byte] = ((*pPosition)[byte] | (1 << bit));
			}

			++count;
			return true;
		}
	}

	bool IsNull() const
	{
		return isNull;
	}

private:

	typename IndexType::Type start;
	typename IndexType::Type count;

	uint32_t maxCount;

	bool isNull;

	openpal::WriteBuffer range;  // make a copy to record where we write the range
	openpal::WriteBuffer* pPosition;
};

}

#endif
