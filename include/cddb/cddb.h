 /* fre:ac - free audio converter
  * Copyright (C) 2001-2016 Robert Kausch <robert.kausch@freac.org>
  *
  * This program is free software; you can redistribute it and/or
  * modify it under the terms of the GNU General Public License as
  * published by the Free Software Foundation, either version 2 of
  * the License, or (at your option) any later version.
  *
  * THIS PACKAGE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS OR
  * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
  * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE. */

#ifndef H_FREAC_CDDB
#define H_FREAC_CDDB

#include <boca.h>

#include <cddb/cddbinfo.h>

const Int	 FREEDB_MODE_HTTP_POST	= 0;
const Int	 FREEDB_MODE_HTTP_GET	= 1;
const Int	 FREEDB_MODE_CDDBP	= 2;

const Int	 QUERY_RESULT_ERROR	= -1;
const Int	 QUERY_RESULT_NONE	= 0;
const Int	 QUERY_RESULT_SINGLE	= 1;
const Int	 QUERY_RESULT_MULTIPLE	= 2;
const Int	 QUERY_RESULT_FUZZY	= 3;

namespace freac
{
	abstract class CDDB
	{
		protected:
			Array<Int>	 ids;
			Array<String>	 titles;
			Array<String>	 categories;

			Bool		 UpdateEntry(CDDBInfo &);

			String		 FormatCDDBEntry(const String &, const String &);
			String		 ParseCDDBEntry(const String &, Int &);

			String		 FormatCDDBRecord(const CDDBInfo &);
			Bool		 ParseCDDBRecord(const String &, CDDBInfo &);
		public:
					 CDDB();
			virtual		~CDDB();

			virtual Bool	 ConnectToServer()			= 0;
			virtual Int	 Query(const String &)			= 0;
			virtual Bool	 Read(const String &, Int, CDDBInfo &)	= 0;
			virtual Bool	 Submit(const CDDBInfo &)		= 0;
			virtual Bool	 CloseConnection()			= 0;

			Int		 GetNumberOfMatches()	{ return ids.Length(); }
			Int		 GetNthDiscID(Int n)	{ return ids.GetNth(n); }
			const String	&GetNthTitle(Int n)	{ return titles.GetNth(n); }
			const String	&GetNthCategory(Int n)	{ return categories.GetNth(n); }

			static String	 DiscIDToString(Int);
			static Int	 StringToDiscID(const String &);

			static Int	 DiscIDFromMCDI(const BoCA::MCDI &);
			static String	 QueryStringFromMCDI(const BoCA::MCDI &);

			static Int	 DiscIDFromOffsets(const String &);
			static String	 QueryStringFromOffsets(const String &);
	};
};

#endif
