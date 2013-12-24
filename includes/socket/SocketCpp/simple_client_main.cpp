#include "ClientSocket.h"
#include "SocketException.h"
#include <iostream>
#include <string>
#include "./Message/Message.pb.h"

int main ( int argc, char* argv[] )
{
	try
	{

		ClientSocket client_socket ( "localhost", 30000 );

		std::string reply;

		try
		{
			Message msg;
			msg.set_message("Test message.");

			Message_UserInfo fromUser = msg->add_fromUser();
			fromUser.set_id("justinchou@gmail.com");
			fromUser.set_type(Message::ID);

			Message_UserInfo toUser = msg->add_toUser();
			toUser.set_id("13381220537");
			toUser.set_type(Message::PHONE);

			client_socket << msg;
			client_socket >> reply;
		}
		catch ( SocketException& ) {}

		std::cout << "We received this response from the server:\n\"" << reply << "\"\n";;

	}
	catch ( SocketException& e )
	{
		std::cout << "Exception was caught:" << e.description() << "\n";
	}

	return 0;
}
