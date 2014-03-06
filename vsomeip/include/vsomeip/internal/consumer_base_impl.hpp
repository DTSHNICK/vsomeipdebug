//
// consumer_base_impl.hpp
//
// Author: Lutz Bichler <Lutz.Bichler@bmwgroup.com>
//
// This file is part of the BMW Some/IP implementation.
//
// Copyright �� 2013, 2014 Bayerische Motoren Werke AG (BMW).
// All rights reserved.
//

#ifndef VSOMEIP_INTERNAL_CONSUMER_BASE_IMPL_HPP
#define VSOMEIP_INTERNAL_CONSUMER_BASE_IMPL_HPP

#include <deque>
#include <vector>

#include <boost/asio/system_timer.hpp>

#include <vsomeip/consumer.hpp>
#include <vsomeip/serializer.hpp>
#include <vsomeip/deserializer.hpp>
#include <vsomeip/primitive_types.hpp>
#include <vsomeip/internal/participant_impl.hpp>

namespace vsomeip {

class message_base;
class receiver;

class consumer_base_impl
		: virtual public consumer,
		  public participant_impl {
public:
	consumer_base_impl(factory *_factory,
					   	  uint32_t _max_message_size,
					   	  boost::asio::io_service &_is);
	~consumer_base_impl();

	bool send(const message_base *_message,  bool _flush);
	bool send(const uint8_t *_data, uint32_t _size, bool _flush);
	bool flush();

	virtual void connect() = 0;
	virtual void receive() = 0;

protected:
	std::deque< std::vector< uint8_t > > packet_queue_;
	std::vector< uint8_t > packetizer_;

private:
	void flush(const boost::system::error_code &_error_code);
	boost::asio::system_timer flush_timer_;

public:
	void connected(boost::system::error_code const &_error_code);

	void sent(boost::system::error_code const &_error_code,
			   std::size_t _sent_bytes);

	void received(boost::system::error_code const &_error_code,
					std::size_t _sent_bytes);
};

} // namespace vsomeip

#endif // VSOMEIP_INTERNAL_CONSUMER_BASE_IMPL_HPP
