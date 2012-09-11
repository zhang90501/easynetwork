/*
 * MTServerAppFramework.cpp
 *
 *  Created on: 2012-9-11
 *      Author: xl
 */

#include "MTServerAppFramework.h"
#include "slog.h"
#include "IODemuxerEpoll.h"

HANDLE_RESULT TimerHandler::on_timeout(int fd)
{
	SLOG_INFO("timer timeout...");
	m_demuxer->register_event(-1, EVENT_INVALID, 3000, this);

	return HANDLE_OK;
}

//////////////////由应用层重写 接收协议函数//////////////////
void MTServerAppFramework::run()
{
	SLOG_INFO("MTServerAppFramework[ID=%d] is running...", get_id());
	get_io_demuxer()->run_loop();
	SLOG_INFO("MTServerAppFramework end...");
}

int MTServerAppFramework::on_recv_protocol(SocketHandle socket_handle, Protocol *protocol)
{
	switch(((DefaultProtocol*)protocol)->get_type())
	{
	case PROTOCOL_STRING:
		{
			StringProtocol* string_protocol = (StringProtocol*)protocol;
			string data = string_protocol->get_string();
			SLOG_INFO("thread[ID=%d] receive string protocol from fd=%d. receive data:[%s], length=%d", get_id(), socket_handle, data.c_str(), data.length());

			Protocol* resp_protocol = ((DefaultProtocolFamily*)get_protocol_family())->create_protocol(PROTOCOL_STRING);
			string temp = "server receive data:";
			temp += data;
			((StringProtocol*)resp_protocol)->set_string(temp);
			send_protocol(socket_handle, resp_protocol);
		}
		break;
	default:
		SLOG_WARN("receive undefine protocol. ignore it.");
		break;
	}

	return 0;
}

int MTServerAppFramework::on_protocol_send_error(SocketHandle socket_handle, Protocol *protocol)
{
	SLOG_ERROR("server app on send protocol error. fd=%d, protocol=%x", socket_handle, protocol);
	get_protocol_family()->destroy_protocol(protocol);
	return 0;
}

int MTServerAppFramework::on_protocol_send_succ(SocketHandle socket_handle, Protocol *protocol)
{
	SLOG_INFO("server app on send protocol succ. fd=%d, protocol=%x", socket_handle, protocol);
	get_protocol_family()->destroy_protocol(protocol);
	return 0;
}

int MTServerAppFramework::on_socket_handle_error(SocketHandle socket_handle)
{
	SLOG_INFO("server app on socket handle error. fd=%d", socket_handle);
	return 0;
}

int MTServerAppFramework::on_socket_handle_timeout(SocketHandle socket_handle)
{
	SLOG_INFO("server app on socket handle timeout. fd=%d", socket_handle);
	return 0;
}

///////////////////////////////  thread pool  //////////////////////////////////
Thread* MTServerAppFrameworkPool::create_thread()
{
	EpollDemuxer *io_demuxer = new EpollDemuxer;
	DefaultProtocolFamily *protocol_family = new DefaultProtocolFamily;
	SocketManager *socket_manager = new SocketManager;
	return new MTServerAppFramework(io_demuxer, protocol_family, socket_manager);
}
