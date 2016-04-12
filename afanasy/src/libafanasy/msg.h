#pragma once

#include <time.h>

#include "afqueue.h"
#include "client.h"

namespace af
{
///   Message - Afanasy communication unit.
/**   Any type of client ( aftalk, afrender), afcmd and afserver communicate through messages.
***   Message can have some data or not, determined on its type.
***   Messages with type greater than or equal to \c Msg::TDATA must have some data to be valid.
***   They must have non zero data pointer and data length greater than zero.
***   Messages with type less than \c Msg::TDATA must not have any data to be valid.
***   They must have NULL data pointer.
**/
class Msg : public Af, public AfQueueItem
{
public:
	/// Default constructor.
	Msg( int msgType = 0, int msgInt = 0);

	/// Constructor from \c Af class.
	Msg( int msgType, Af * afClass);

	/// Construct a message and set an address
	Msg( const struct sockaddr_storage * ss);

	Msg( const char * rawData, int rawDataLen);

	~Msg();///< Destructor.

	void v_generateInfoStream( std::ostringstream & stream, bool full = false) const;

	/// To set zero (\c Msg::TNone ) message to some non data message. Return \c true on success.
	bool set( int msgType, int msgInt = 0);

	/// Write \c Af class to message.
	bool set( int msgType, Af * afClass);

	/// To set zero (\c Msg::TNone ) message to data message. Return \c true on success.
		/// On TJSON header type will be not binary - binary header will be skipped at all.
	bool setData( int i_size, const char * i_msgData, int i_type = TDATA);

	/// To JSON data message with binary header (not for python or browser).
	void setJSONBIN();
//	bool setJSON_headerBin( const std::string & i_str);
//	inline bool setJSON_headerBin( const std::ostringstream & i_str) { return setJSON_headerBin( i_str.str());}

	/// To set zero (\c Msg::TNone ) message to QString message. Return \c true on success.
	bool setString( const std::string & qstring);

	/// To set zero (\c Msg::TNone ) message to QStringList message. Return \c true on success.
	bool setStringList( const std::list<std::string> & stringlist);

	/// To set zero (\c Msg::TNone ) message to QStringList message. Return \c true on success.
	bool setInfo( const std::string & i_kind, const std::string & i_text);
	bool getInfo( std::string & o_kind, std::string & o_text);

	/// Get String ( if message type is TString ).
	bool getString( std::string & string);
	const std::string getString();

	/// Get String ( if message type is TStringList ).
	bool getStringList( std::list<std::string> & stringlist);

/**   IMPORTANT!
***   messages with (type < MText) MUST NOT have any data to be valid:
***   (( mdata == NULL) && ( data_len == 0)) ALWAYS !
***   messages with (type >= MText) MUST have some data to be valid:
***   (( mdata != NULL) && ( data_len > 0)) ALWAYS !
**/
   enum Type{
/*------------ NONDATA MESSAGES ----------------------*/
/// Default message with default type - zero. Only this type can be changed by \c set function.
/**/TNULL/**/,

/// Message set to this type itself, when reading.
/**/TVersionMismatch/**/,

/// Invalid message. This message type generated by constructors if wrong arguments provieded.
/**/TInvalid/**/,

/**/TConfirm/**/,                   ///< Simple answer with no data to confirm something.

/// Request messages, sizes, quantities statistics. Can be requested displayed by anatoly.
/**/TStatRequest/**/,

/*- Monitor messages -*/
/**/TMonitorId/**/,                 ///< Server sends ID back to monitor when no new events happened.
/**/TMonitorUpdateId/**/,           ///< Update Monitor with given id ( No information for updating Monitor needed).
/**/TMonitorDeregister/**/,         ///< Deregister monitor with given id.

/*- Render messages -*/
/** When Server successfully registered new Render it's send back it's id.**/
/**/TRenderId/**/,
/**/TRenderDeregister/**/,          ///< Deregister Render with given id.

/*- Job messages -*/
/**/TJobsWeightRequest/**/,         ///< Request all jobs weight.


TRESERVED00,TRESERVED01,TRESERVED02,TRESERVED03,TRESERVED04,TRESERVED05,TRESERVED06,TRESERVED07,TRESERVED08,TRESERVED09,

/*---------------------------------------------------------------------------------------------------------*/
/*--------------------------------- DATA MESSAGES ---------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------*/


/**/TDATA/**/,                      ///< Some data.
/**/TTESTDATA/**/,                  ///< Test some data transfer.
/**/TJSON/**/,                      ///< JSON with text header
/**/TJSONBIN/**/,                   ///< JSON with binary header
/**/THTTP/**/,                      ///< HTTP - with JSON POST data.
/**/THTTPGET/**/,                   ///< HTTP Get request.
/**/TString/**/,                    ///< String message.
/**/TStringList/**/,                ///< Strings list message.
/**/TInfo/**/,                      ///< Some info string for GUI to show.

/**/TStatData/**/,                  ///< Statistics data.

/*- Monitor messages -*/
/**/TMonitor/**/,                   ///< Server sends it for a new registered monitor.
/**/TMonitorsList/**/,              ///< Message with a list of online Monitors.
/**/TMonitorEvents/**/,             ///< Events.

/*- Render messages -*/
/** Sent by Render on start, when it's server begin to listen port.
And when Render can't connect to Afanasy. Afanasy register new Render and send back it's id \c TRenderId. **/
/**/TRenderRegister/**/,
/**/TRenderUpdate/**/,              ///< Update Render, message contains its resources.
/**/TRenderEvents/**/,              ///< Server answer on render update, it contains what to do.
/**/TRendersResourcesRequestIds/**/,///< Request a list of resources of Renders with given ids.
/**/TRendersList/**/,               ///< Message with a list of Renders.
/**/TRendersResources/**/,          ///< Message with a list of resources of Renders.

/*- Users messages -*/
/**/TUsersList/**/,                 ///< Active users information.
/**/TUserJobsOrder/**/,             ///< Jobs ids in server list order.

/*- Job messages -*/
/**/TJobsList/**/,                  ///< Jobs list information.
/**/TJobProgress/**/,               ///< Jobs progress.
/**/TJobsWeight/**/,                ///< All jobs weight data.
/**/TJob/**/,                       ///< Job (job full data, with blocks and tasks full data).

/**/TBlocksProgress/**/,            ///< Blocks running progress data.
/**/TBlocksProperties/**/,          ///< Blocks progress and properties data.
/**/TBlocks/**/,                    ///< Blocks data.

/**/TTask/**/,                      ///< A task of some job.
/**/TTaskOutputRequest/**/,         ///< Request task output from render ( by gui thought server ).
/**/TTaskFiles/**/,                 ///< Task (or entire job) files

TRESERVED10,TRESERVED11,TRESERVED12,TRESERVED13,TRESERVED14,TRESERVED15,TRESERVED16,TRESERVED17,TRESERVED18,TRESERVED19,

TLAST
};

	static const char * TNAMES[]; ///< Type names.

	inline int   type()    const { return m_type;  }///< Get message type.
	inline char* data()    const { return m_data;  }///< Get data pointer.
	inline int   dataLen() const { return m_int32; }///< Get data length.
	inline int   int32()   const { return m_int32; }///< Get 32-bit integer, data lenght for data messages.

	inline char* buffer() const { return m_buffer;}///< Get buffer pointer.

	/// Get message full size (with data).
	inline int writeSize() const { return m_type<TDATA ? Msg::SizeHeader : Msg::SizeHeader+m_int32;}

	/// Get buffer at already written postition to write \c size bytes in it.
	char * writtenBuffer( int size);
	inline bool isWriting() const { return  m_writing; } ///< Writing or reading data in message.
	inline bool isReading() const { return !m_writing; } ///< Writing or reading data in message.

	void setInvalid();             ///< Set message invalidness.
	void readHeader( int bytes);   ///< Read header from message buffer, \c bytes - number of already written bytes in it's buffer.

	// Set header to specified values, that are get from text data
	// i_offset and i_bytes to shift message data, to remove HTTP header for example
	void setHeader( int i_type, int i_size, int i_offset = 0, int i_bytes = 0);

	inline bool      isNull() const { return m_type == TNULL;    }///< Whether message is null.
	inline bool   isInvalid() const { return m_type == TInvalid; }///< Whether message is invalid.

	void stdOutData( bool withHeader = true);

	static const int SizeHeader;     ///< size of message header.
	static const int SizeBuffer;     ///< message reading buffer size.
	static const int SizeBufferLimit;///< message buffer maximum size.
	static const int SizeDataMax;    ///< maximum data size that can handle a message.

	static const int Version;    ///< Current afanasy version.

	inline int version() const { return m_version; } ///< Get message afanasy version.

	inline void resetWrittenSize() { m_writtensize = 0; }

	inline bool addressIsEmpty() const { return m_address.isEmpty();}

	inline const Address & getAddress() const { return m_address;}

	void setTypeHTTP();
//	void createHTTPHeader();

	inline int getHeaderOffset() const { return m_header_offset;}

private:

// header:
	int32_t m_version;   ///< Afanasy network protocol version.
	int32_t m_type;      ///< Message type.
	int32_t m_int32;     ///< Some 32-bit integer, data length for data messages.

// data poiters:
	char * m_buffer;     ///< Internal buffer pointer, for header and data
	char * m_data;       ///< Message data pointer = buffer + header_size.

// buffering parameters:
	bool m_writing;                  ///< Writing or reading data in message.
	int  m_buffer_size;              ///< Buffer size.
	int  m_data_maxsize;             ///< Data maximum size ( = buffer size - header size).
	int  m_writtensize;              ///< Number of bytes already written in message buffer.
	int  m_header_offset;            ///< From where begin to write, for exampl to send json to browser
	                                 ///< we should skip header at all ( m_header_offset = Msg::SizeHeader )

// communication parameters:
	Address m_address;                ///< Address, where message came from or will be send.

private:

	void construct();                ///< Called from constuctors.
	bool checkZero( bool outerror ); ///< Check Zero type, data length and pointer.
	bool checkValidness();           ///< Check message header validness and magic number;

	/// Allocate memory for buffer, copy \c to_copy_len bytes in new buffer if any
	bool allocateBuffer( int i_size, int i_copy_len = 0, int i_copy_offset = Msg::SizeHeader);

	void rw_header( bool write); ///< Read or write message header.
	void v_readwrite( Msg * msg);
};
}
