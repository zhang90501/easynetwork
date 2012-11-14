/*
 * STAppTemplate.h
 *
 *  Created on: #CreateDate#
 *      Author: #Author#
 */

#ifndef _STAppTemplate_H_
#define _STAppTemplate_H_

#include "NetInterface.h"

class STAppTemplate: public NetInterface
{
protected:
	////由应用层实现 -- 创建具体的协议族
	virtual ProtocolFamily* create_protocol_family();
	////由应用层实现 -- 销毁协议族
	virtual void delete_protocol_family(ProtocolFamily* protocol_family);

	////由应用层实现 -- 接收协议函数
	virtual bool on_recv_protocol(SocketHandle socket_handle, Protocol *protocol, bool &detach_protocol); //应用层设置detatch_protocol为true时,由应用层负责销毁protocol
	////由应用层实现 -- 协议发送错误处理函数
	virtual bool on_protocol_send_error(SocketHandle socket_handle, Protocol *protocol);
	////由应用层实现 -- 协议发送成功处理函数
	virtual bool on_protocol_send_succ(SocketHandle socket_handle, Protocol *protocol);
	////由应用层实现 -- 连接错误处理函数
	virtual bool on_socket_handle_error(SocketHandle socket_handle);
	////由应用层实现 -- 连接超时处理函数
	virtual bool on_socket_handle_timeout(SocketHandle socket_handle);
	////由应用层实现 -- 已经收到一个新的连接请求
	virtual bool on_socket_handler_accpet(SocketHandle socket_handle);
public:
	////由应用层实现 -- et interface实例启动入口
	bool start_server();
};

#endif //_STAppTemplate_H_


