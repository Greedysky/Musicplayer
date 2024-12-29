/***************************************************************************
 *   Copyright (C) 2007-2025 by Ilya Kotov                                 *
 *   forkotov02@ya.ru                                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.         *
 ***************************************************************************/

#ifndef DECODER_AUDIOFILE_H
#define DECODER_AUDIOFILE_H

#include <qmmp/decoder.h>
#ifdef Q_OS_WIN
#  include <windows.h>
#  define ENABLE_SNDFILE_WINDOWS_PROTOTYPES 1
#endif
#include <sndfile.h>

/**
    @author Ilya Kotov <forkotov02@ya.ru>
*/
class DecoderSndFile : public Decoder
{
public:
    explicit DecoderSndFile(QIODevice *input);
    virtual ~DecoderSndFile();

    // Standard Decoder API
    virtual bool initialize() override final;
    virtual qint64 totalTime() const override final;
    virtual int bitrate() const override final;
    virtual qint64 read(unsigned char *data, qint64 maxSize) override final;
    virtual void seek(qint64 time) override final;

private:
    // helper functions
    void deinit();

    SNDFILE *m_sndfile = nullptr;
    int m_bitrate = 0;
    quint32 m_freq = 0;
    qint64 m_totalTime = 0;
    SF_VIRTUAL_IO m_vio;

};

#endif
