/*
 *  zlib_stream.h
 *  macstl
 *
 *  Created by Glen Low on Fri Mar 14 2003.
 *
 *  Copyright (c) 2003, Pixelglow Software.
 *  http://www.pixelglow.com/macstl/
 *
 *  You may copy, modify, distribute and sell this software and its
 *  documentation without fee, provided that the above copyright notice
 *  appear in all copies and that both the copyright notice and these
 *  permission notices appear in supporting documentation. You may modify
 *  this software without further permission from the copyright holders,
 *  but all such modified files must carry prominent notices stating
 *  that you changed the files and the date of any change.
 *
 *  If you register this software with the copyright holders, you may
 *  compile any part of it from source code to object code. If you
 *  do not register, you may only compile it within 30 days of the first
 *  compilation, and must ensure that all the compiled code and its copies,
 *  modifications, distributions and sales are deleted within the 30 days.
 *
 *  The copyright holders make no representations about the suitability
 *  of this software for any purpose.  It is provided "as is" without
 *  express or implied warranty.
 */

#include <iostream>
#include <streambuf>
#include <stdexcept>
#include <zlib.h>          

namespace macstl
	{
		class zlib_error: public std::runtime_error
			{
				public:
					explicit zlib_error (const char* msg): runtime_error (msg)
						{
						}
			};
			
		class stream_error: public zlib_error
			{
				public:
					explicit stream_error (const char* msg): zlib_error (msg ? msg : "stream error")
						{
						}
			};
		
		class data_error: public zlib_error
			{
				public:
					explicit data_error (const char* msg): zlib_error (msg ? msg : "data error")
						{
						}
			};
		
		class memory_error: public zlib_error
			{
				public:
					explicit memory_error (const char* msg): zlib_error (msg ? msg : "memory error")
						{
						}
			};
		
		class version_error: public zlib_error
			{
				public:
					explicit version_error (const char* msg): zlib_error (msg ? msg : "version error")
						{
						}
			};
			
		class flate_base
			{
				public:
					enum method
						{
							deflated = Z_DEFLATED,
						};
						
					enum strategy
						{
							filtered = Z_FILTERED,
							huffman_only = Z_HUFFMAN_ONLY,
							default_strategy = Z_DEFAULT_STRATEGY		
						};
						
					enum header
						{
							suppress_header = -1,
							use_header = 1
						};
		
					static const std::streamsize default_size = 1024;
						
				protected:
					z_stream strm_;
					Bytef* inbegin_;
					Bytef* inend_;
					Bytef* outbegin_;
					Bytef* outend_;
					
					flate_base (uInt size)
						{
							// define buffer areas
							inbegin_ = new Bytef [size];
							inend_ = outbegin_ = inbegin_ + size / 2;
							outend_ = inbegin_ + size;
							
							strm_.zalloc = Z_NULL;
							strm_.zfree = Z_NULL;
						}
						
					~flate_base ()
						{
							delete [] inbegin_;
						}
						
					void check (int result)
						{
							switch (result)
								{
									case Z_STREAM_ERROR:
										throw stream_error (strm_.msg);
									case Z_DATA_ERROR:
										throw data_error (strm_.msg);
									case Z_MEM_ERROR:
										throw memory_error (strm_.msg);
									case Z_VERSION_ERROR:
										throw version_error (strm_.msg);						
								}
						}
						
			};
		
		template <typename CharT, typename Traits> class basic_deflatebuf:
			public std::basic_streambuf <CharT, Traits>, public flate_base
			{
				public:
					typedef CharT							char_type;
					typedef Traits							traits_type;
					typedef typename traits_type::int_type	int_type;
					typedef typename traits_type::pos_type	pos_type;
					typedef typename traits_type::off_type	off_type;
						
					explicit basic_deflatebuf (std::basic_streambuf <CharT, Traits>* inner,
						std::ios_base::openmode mode = std::ios_base::in,
						std::streamsize size = default_size,
						flate_base::header header = suppress_header,
						int level = Z_DEFAULT_COMPRESSION,
						flate_base::method method = deflated,
						int windowBits = MAX_WBITS,
						int memLevel = MAX_MEM_LEVEL,
						flate_base::strategy strategy = default_strategy):
						std::basic_streambuf <CharT, Traits> (),
						flate_base (std::max (2, size / 2 * 2)),
						inner_ (inner),
						stage_ (midstream)
						{
							// exactly one of in or out
							assert ((mode & std::ios_base::in) ^ (mode & std::ios_base::out));
							
							if (mode & std::ios_base::in)
								{
									setg (reinterpret_cast <char_type*> (outbegin_),
										reinterpret_cast <char_type*> (outbegin_),
										reinterpret_cast <char_type*> (outbegin_));
									strm_.next_in = inend_;
									strm_.avail_in = 0;
		
									check (inflateInit2 (&strm_, header * windowBits));
								}
							else if (mode & std::ios_base::out)
								{
									setp (reinterpret_cast <char_type*> (inbegin_),
										reinterpret_cast <char_type*> (inend_));
									strm_.next_out = outbegin_;
									strm_.avail_out = outend_ - outbegin_;
				
									check (deflateInit2 (
										&strm_,
										level,
										method,
										header * windowBits,
										memLevel,
										strategy));
								}
						}
						
					virtual ~basic_deflatebuf ()
						{
							// since zlib works with bytes, our buffers need to be same size as bytes as well
							assert (sizeof (CharT) == sizeof (Bytef));
							
							if (gptr ())
								inflateEnd (&strm_);
							else if (pptr ())
								{
									if (pptr () > pbase ())
										put ();
										
									strm_.next_in = NULL;
									strm_.avail_in = 0;
									while ((strm_.avail_out || drain ())
										&& ::deflate (&strm_, Z_FINISH) == Z_OK);
									drain ();
									
									deflateEnd (&strm_);
								}
						}
						
				protected:
					virtual int_type overflow (int_type c)
						{
							// overflow is called when put area is full					
							assert (pptr () == epptr ());
							
							if (put ())
								{
									if (traits_type::eq_int_type (c, traits_type::eof ()))
										return traits_type::not_eof (c);
									else
										{
											// store the one char into the buffer
											*pptr () = c;
											pbump (1);
											return c;
										}
								}
							else
								return traits_type::eof ();
						}
		
					virtual int_type underflow ()
						{
							// underflow is called when get area is empty
							assert (gptr () == egptr ());
							
							fill ();
							return gptr () < egptr () ?
								traits_type::to_int_type (*gptr ()) :
								traits_type::eof ();
		
						}
						
					virtual std::streamsize
						xsgetn (char_type* s, std::streamsize n)
						{
							assert (s != NULL);
							assert (n > 0);
							
							std::streamsize unread = egptr () - gptr ();
							std::streamsize toread = n - unread;
							
							if (toread <= 0)
								{
									traits_type::copy (s, gptr (), n);
									gbump (n);
									return n;
								}
							else
								{
									if (unread)
										{
											traits_type::copy (s, gptr (), unread);
											gbump (unread);
										}
										
									if (toread < outend_ - outbegin_)
										{
											fill ();
											std::streamsize rest = std::min (egptr () - gptr (), toread);
											traits_type::copy (s + unread, gptr (), rest);
											gbump (rest);
											return unread + rest;								
										}
									else
										{
											check (inflate (reinterpret_cast <Bytef*> (s + unread), toread));
											return n - strm_.avail_out;
										}
								}
						}
						
					virtual std::streamsize 
						xsputn (const char_type* s, std::streamsize n)
						{
							assert (s != NULL);
							assert (n > 0);
							
							bool directcopy;
							if (epptr () - pptr () >= n)	// enough room in put area -> direct copy
								directcopy = true;
							else if (pptr () == pbase ())	// no room, nothing to put -> indirect copy
								directcopy = false;
							else if (put ())				// no room, something to put, put OK...
								// after flushing, enough room <-> direct copy
								directcopy = epptr () - pptr () >= n;
							else							// no room, something to put, put bad...
								return 0;
								
							if (directcopy)
								{
									// enough room in the put area to copy the data over without deflating
									traits_type::copy (pptr (), s, n);
									pbump (n);
									return n;
								}
							else
								// deflate the data directly
								{
									check (deflate (reinterpret_cast <const Bytef*> (s), n));
									return n - strm_.avail_in;
								}
						}
						
					virtual int sync ()
						{
							if (pptr () == pbase () || put ())
								{
									check (flush ());
									if (drain () && inner_->pubsync () == 0)
										return 0;
								}
							return -1;
							
						}
						
				private:
					enum stage
						{
							midstream,
							getdone,
							readdone				
						};
						
					std::basic_streambuf <CharT, Traits>* inner_;
					stage stage_;
								
					int inflate (Bytef* s, uInt n)
						{
							strm_.next_out = s;
							strm_.avail_out = n;
							int result = Z_OK;
		
							switch (stage_)
								{
									case midstream:
										while (result == Z_OK && strm_.avail_out)
											{
												// if we run out of input and we're still in the midstream,
												// fetch more input from the inner stream
												if (strm_.avail_in == 0)
													{
														std::streamsize toread =
															strm_.next_in - inbegin_;
														strm_.avail_in = inner_->sgetn 
															(reinterpret_cast <char_type*> (inbegin_), toread);
														strm_.next_in = inbegin_;
														if (static_cast <std::streamsize> (strm_.avail_in) < toread)
															{
																stage_ = getdone;
																break;
															}
													}
												result = ::inflate (&strm_, Z_NO_FLUSH);
											}
											
									case getdone:
										// if we're already at end of inner stream, don't bother getting more input
										while (result == Z_OK && strm_.avail_out)
											result = ::inflate (&strm_, Z_NO_FLUSH);
										
										if (result == Z_STREAM_END)
											stage_ = readdone;
		
										if (result == Z_BUF_ERROR)
											std::cout << "*** BUFFER ERROR ***\n";
										break;
										
									case readdone:
										break;
								}
							return result;
						}
						
					void fill ()
						{
							assert (gptr () == egptr ());
							
							std::streamsize tofill = outend_ - outbegin_;
							int result = inflate (outbegin_, tofill);
							setg (reinterpret_cast <char_type*> (outbegin_),
								reinterpret_cast <char_type*> (outbegin_),
								reinterpret_cast <char_type*> (strm_.next_out));
							check (result);
						}
									
					bool drain ()
						{
							std::streamsize unwritten = 0;
							std::streamsize written = 0;
							std::streamsize write = strm_.next_out - outbegin_;
							if (written = inner_->sputn (reinterpret_cast <char_type*> (outbegin_), write))
								{
									if (unwritten = write - written)
										::memmove (outbegin_, outbegin_ + written, unwritten);
									strm_.next_out = outbegin_ + unwritten;
									strm_.avail_out += written;
								}
							return unwritten == 0;
						}
						
					int deflate (const Bytef* s, uInt n)
						{
							assert (s != NULL);
							assert (n > 0);
							
							strm_.next_in = const_cast <Bytef*> (s);
							strm_.avail_in = n;
							int result = Z_OK;
							
							while ((strm_.avail_out || drain ())
								&& (result = ::deflate (&strm_, Z_NO_FLUSH)) == Z_OK
								&& strm_.avail_in);
												
							return result;
						}
						
					int flush ()
						{
							strm_.next_in = NULL;
							strm_.avail_in = 0;
							int result = Z_OK;
							while ((strm_.avail_out || drain ())
								&& (result = ::deflate (&strm_, Z_SYNC_FLUSH)) == Z_OK
								&& strm_.avail_out == 0);
							return result;
						}
						
					bool put ()
						{
							// try to deflate entire put area
							int result = deflate (reinterpret_cast <Bytef*> (pbase ()), pptr () - pbase ());
							
							if (strm_.avail_in)
								::memmove (reinterpret_cast <Bytef*> (pbase ()), strm_.next_in, strm_.avail_in);
							pbump (reinterpret_cast <Bytef*> (pbase ()) - strm_.next_in);
							
							check (result);
							
							return strm_.avail_in == 0;
						}
			};
			
		typedef basic_deflatebuf <char, std::char_traits <char> > deflatebuf;
		
	};
