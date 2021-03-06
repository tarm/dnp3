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
#include "MultiplexingDataObserver.h"

namespace opendnp3
{

MultiplexingDataObserver :: MultiplexingDataObserver()
{}

MultiplexingDataObserver :: MultiplexingDataObserver(IMeasurementLoader* apObserver1)
{
	AddObserver(apObserver1);
}

MultiplexingDataObserver :: MultiplexingDataObserver(IMeasurementLoader* apObserver1, IMeasurementLoader* apObserver2)
{
	AddObserver(apObserver1);
	AddObserver(apObserver2);
}

void MultiplexingDataObserver :: AddObserver(IMeasurementLoader* apObserver)
{
	mObservers.push_back(apObserver);
}

void MultiplexingDataObserver::Start()
{
	for (auto pObs : mObservers) openpal::Transaction::Start(pObs);
}

void MultiplexingDataObserver::End()
{
	for (auto pObs : mObservers) openpal::Transaction::End(pObs);
}

void MultiplexingDataObserver :: Update(const Binary& arPoint, uint16_t aIndex)
{
	for(auto pObs : mObservers) pObs->Update(arPoint, aIndex);
}
void MultiplexingDataObserver::Update(const Analog& arPoint, uint16_t aIndex)
{
	for(auto pObs : mObservers) pObs->Update(arPoint, aIndex);
}
void MultiplexingDataObserver::Update(const Counter& arPoint, uint16_t aIndex)
{
	for(auto pObs : mObservers) pObs->Update(arPoint, aIndex);
}
void MultiplexingDataObserver::Update(const BinaryOutputStatus& arPoint, uint16_t aIndex)
{
	for(auto pObs : mObservers) pObs->Update(arPoint, aIndex);
}
void MultiplexingDataObserver::Update(const AnalogOutputStatus& arPoint, uint16_t aIndex)
{
	for(auto pObs : mObservers) pObs->Update(arPoint, aIndex);
}


}
