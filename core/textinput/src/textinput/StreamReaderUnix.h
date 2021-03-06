//===--- TerminalReaderUnix.h - Input From UNIX Terminal --------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
//  This file defines the interface reading from a UNIX terminal. It tries to
//  support all common terminal types.
//
//  Axel Naumann <axel@cern.ch>, 2011-05-12
//===----------------------------------------------------------------------===//

#ifndef TEXTINPUT_STREAMREADERUNIX_H
#define TEXTINPUT_STREAMREADERUNIX_H

#include "textinput/StreamReader.h"
#include <queue>

namespace textinput {
  // Input from a tty, file descriptor, or pipe
  class StreamReaderUnix: public StreamReader {
  public:
    StreamReaderUnix();
    ~StreamReaderUnix();

    void GrabInputFocus();
    void ReleaseInputFocus();

    bool HavePendingInput(bool wait);
    bool HaveBufferedInput() const { return !fReadAheadBuffer.empty(); }
    bool ReadInput(size_t& nRead, InputData& in);

  private:
    int ReadRawCharacter();
    bool ProcessCSI(InputData& in);

    bool fHaveInputFocus; // whether we configured the tty
    bool fIsTTY; // whether input FD is a tty
    std::queue<char> fReadAheadBuffer; // input chars we read too much (CSI)
  };
}

#endif // TEXTINPUT_STREAMREADERUNIX_H
