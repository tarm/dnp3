/**
 * Copyright 2013 Automatak, LLC
 *
 * Licensed to Automatak, LLC (www.automatak.com) under one or more
 * contributor license agreements. See the NOTICE file distributed with this
 * work for additional information regarding copyright ownership. Automatak, LLC
 * licenses this file to you under the Apache License Version 2.0 (the "License");
 * you may not use this file except in compliance with the License. You may obtain
 * a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0.html
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 */
package com.automatak.dnp3;

/**
 * Interface for dispatching command requests from a master to an outstation
 */
public interface CommandProcessor {

    /**
     * Select and operate a ControlRelayOutputBlock (Group12Variation1)
     * @param command command data
     * @param index index of request
     * @return future to the result of the operation
     */
    ListenableFuture<CommandResponse> selectAndOperate(ControlRelayOutputBlock command, long index);

    /**
     * Select and operate a 32-bit integer AnalogOutput (Group41Variation1)
     * @param command command data
     * @param index index of request
     * @return future to the result of the operation
     */
    ListenableFuture<CommandResponse> selectAndOperate(AnalogOutputInt32 command, long index);

    /**
     * Select and operate a 16-bit integer AnalogOutput (Group41Variation2)
     * @param command command data
     * @param index index of request
     * @return future to the result of the operation
     */
    ListenableFuture<CommandResponse> selectAndOperate(AnalogOutputInt16 command, long index);

    /**
     * Select and operate single precision AnalogOutput (Group41Variation3)
     * @param command command data
     * @param index index of request
     * @return future to the result of the operation
     */
    ListenableFuture<CommandResponse> selectAndOperate(AnalogOutputFloat32 command, long index);

    /**
     * Select and operate double precision AnalogOutput (Group41Variation4)
     * @param command command data
     * @param index index of request
     * @return future to the result of the operation
     */
    ListenableFuture<CommandResponse> selectAndOperate(AnalogOutputDouble64 command, long index);

    /**
     * Direct operate a ControlRelayOutputBlock (Group12Variation1)
     * @param command command data
     * @param index index of request
     * @return future to the result of the operation
     */
    ListenableFuture<CommandResponse> directOperate(ControlRelayOutputBlock command, long index);

    /**
     * Direct operate a 32-bit integer AnalogOutput (Group41Variation1)
     * @param command command data
     * @param index index of request
     * @return future to the result of the operation
     */
    ListenableFuture<CommandResponse> directOperate(AnalogOutputInt32 command, long index);

    /**
     * Direct operate a 16-bit integer AnalogOutput (Group41Variation2)
     * @param command command data
     * @param index index of request
     * @return future to the result of the operation
     */
    ListenableFuture<CommandResponse> directOperate(AnalogOutputInt16 command, long index);

    /**
     * Direct operate a single precision AnalogOutput (Group41Variation3)
     * @param command command data
     * @param index index of request
     * @return future to the result of the operation
     */
    ListenableFuture<CommandResponse> directOperate(AnalogOutputFloat32 command, long index);

    /**
     * Direct operate  a double precision AnalogOutput (Group41Variation4)
     * @param command command data
     * @param index index of request
     * @return future to the result of the operation
     */
    ListenableFuture<CommandResponse> directOperate(AnalogOutputDouble64 command, long index);

}
