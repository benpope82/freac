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

#include <engine/converter.h>

#include <joblist.h>
#include <playback.h>
#include <config.h>
#include <utilities.h>

#include <jobs/engine/convert.h>

using namespace BoCA;
using namespace BoCA::AS;

freac::Converter::Converter()
{
	conversionFinished = False;
}

freac::Converter::~Converter()
{
}

Void freac::Converter::Convert(JobList *joblist, Bool useThread)
{
	/* Check if currently playing a track.
	 */
	if (Playback::Get()->IsPlaying())
	{
		BoCA::Utilities::ErrorMessage("Cannot start encoding while playing a file!");

		return;
	}

	/* Create array of tracks to convert.
	 */
	Array<Track>	 tracks;

	for (Int i = 0; i < joblist->GetNOfTracks(); i++)
	{
		if (!joblist->GetNthEntry(i)->IsMarked()) continue;

		tracks.Add(joblist->GetNthTrack(i), joblist->GetNthTrack(i).GetTrackID());
	}

	/* Start conversion job.
	 */
	Job	*convert = new JobConvert(tracks);

	if (!useThread)	convert->onFinish.Connect(&Converter::OnFinishJob, this);

	convert->Schedule();

	if (!useThread)	while (!conversionFinished) S::System::System::Sleep(10);
}

Void freac::Converter::OnFinishJob()
{
	conversionFinished = True;
}
