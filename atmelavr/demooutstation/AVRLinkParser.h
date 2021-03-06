
#ifndef __AVR_LINK_PARSER_H_
#define __AVR_LINK_PARSER_H_

#include <opendnp3/link/ILinkRouter.h>
#include <opendnp3/link/ILinkContext.h>

#include <opendnp3/Settable.h>
#include <opendnp3/link/LinkLayerParser.h>

#include <openpal/LogRoot.h>
#include <openpal/StaticQueue.h>
#include <openpal/RingBuffer.h>
#include <openpal/IExecutor.h>

namespace arduino {

class AVRLinkParser : public opendnp3::ILinkRouter
{
	public:

	AVRLinkParser(openpal::LogRoot& root, openpal::IExecutor& exe, opendnp3::ILinkContext& context);
	
	virtual void QueueTransmit(const openpal::ReadOnlyBuffer& buffer, opendnp3::ILinkContext* pContext, bool primary) final override;	
	
	void Receive(uint8_t byte);
	
	void Init();
	
	void CheckTransmit();
	
	void ProcessRx();
	
	private:
	
	uint32_t CopyRxBuffer();
		
	struct Transmission
	{
		Transmission(const openpal::ReadOnlyBuffer& buffer_, bool primary_) :
			buffer(buffer_),
			primary(primary_)
			{}

		Transmission() : buffer(), primary(false)
		{}

		openpal::ReadOnlyBuffer buffer;
		bool primary;
	};
	
	openpal::StaticQueue<Transmission, uint8_t, 2> txQueue;
	openpal::RingBuffer<8> rxBuffer;
	
	opendnp3::Settable<openpal::ReadOnlyBuffer> primaryTx;
	opendnp3::Settable<openpal::ReadOnlyBuffer> secondaryTx;
	
	openpal::IExecutor* pExecutor;
	opendnp3::ILinkContext* pContext;		
	opendnp3::LinkLayerParser parser;
};

}

#endif

