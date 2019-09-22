// Generated by the protocol compiler version 1.3.8
// DO NOT EDIT THIS FILE DIRECTLY!

#ifndef _BROADCAST_PROTOCOL_H_
#define _BROADCAST_PROTOCOL_H_

#include <iostream>
#include <iterator>
#include <vector>
#include <string>
#include <memory>

namespace protocol {
    typedef std::ostream::char_type byte;
    typedef std::basic_ostream<protocol::byte> ostream;
    typedef std::basic_istream<protocol::byte> istream;

    namespace broadcast {

	// Data types used in messages, but which aren't messages themselves.

	namespace request {

	    // Forward declaration of messages.

	    struct connect;
	    struct frame;

	    class Receiver {
	     public:
	        virtual ~Receiver();
		virtual void handle(connect&) = 0;
		virtual void handle(frame&) = 0;
	    };

	    // Start of the message object hierarchy.

	    struct Base {
		typedef std::unique_ptr< Base > Ptr;

		virtual ~Base();
	     public:
		virtual void deliverTo(Receiver&) = 0;
		virtual void marshal(protocol::ostream&) const = 0;
		virtual bool needsReply() const = 0;
		static Ptr unmarshal(protocol::istream&);
	    };

	    struct connect : public Base {
		int32_t version_client;

		void swap(connect&) noexcept(true);
		virtual void deliverTo(Receiver&);
	     public:
		connect() :
		    version_client(0)
		    {}
		virtual void marshal(protocol::ostream&) const;
		virtual bool needsReply() const { return true; };

		inline int operator==(connect const& o) const noexcept(true)
		{
		    return (version_client == o.version_client);
		}
	    };

	    struct frame : public Base {
		std::vector<uint8_t> data;

		void swap(frame&) noexcept(true);
		virtual void deliverTo(Receiver&);
	     public:
		frame() 
		    {}
		virtual void marshal(protocol::ostream&) const;
		virtual bool needsReply() const { return true; };

		inline int operator==(frame const& o) const noexcept(true)
		{
		    return (data == o.data);
		}
	    };

	}
	namespace reply {

	    // Forward declaration of messages.

	    struct Error;
	    struct connected;
	    struct frame_ack;

	    class Receiver {
	     public:
	        virtual ~Receiver();
		virtual void handle(Error&) = 0;
		virtual void handle(connected&) = 0;
		virtual void handle(frame_ack&) = 0;
	    };

	    // Start of the message object hierarchy.

	    struct Base {
		typedef std::unique_ptr< Base > Ptr;

		virtual ~Base();
	     public:
		virtual void deliverTo(Receiver&) = 0;
		virtual void marshal(protocol::ostream&) const = 0;
		virtual bool needsReply() const = 0;
		static Ptr unmarshal(protocol::istream&);
	    };

	    struct Error : public Base {
		int32_t code;
		std::string message;

		void swap(Error&) noexcept(true);
		virtual void deliverTo(Receiver&);
	     public:
		Error() :
		    code(0)
		    {}
		virtual void marshal(protocol::ostream&) const;
		virtual bool needsReply() const { return false; };

		inline int operator==(Error const& o) const noexcept(true)
		{
		    return (code == o.code) &&
			(message == o.message);
		}
	    };

	    struct connected : public Base {
		int32_t server_version;

		void swap(connected&) noexcept(true);
		virtual void deliverTo(Receiver&);
	     public:
		connected() :
		    server_version(0)
		    {}
		virtual void marshal(protocol::ostream&) const;
		virtual bool needsReply() const { return false; };

		inline int operator==(connected const& o) const noexcept(true)
		{
		    return (server_version == o.server_version);
		}
	    };

	    struct frame_ack : public Base {

		void swap(frame_ack&) noexcept(true);
		virtual void deliverTo(Receiver&);
	     public:
		frame_ack() 
		    {}
		virtual void marshal(protocol::ostream&) const;
		virtual bool needsReply() const { return false; };

		inline int operator==(frame_ack const&) const noexcept(true)
		{
		    return true;
		}
	    };

	}
    }
}

#endif
