// legends_xml_parser.hpp - LegendsXMLParser class definition
// Demiurge - A Dwarf Fortress Legends visualization tool
// Copyright (c) 2015 Vadim Litvinov <vadim_litvinov@fastmail.com>
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
// 3. Neither the name of the author nor the names of its contributors
//    may be used to endorse or promote products derived from this software
//    without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
// OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
// OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
// SUCH DAMAGE.

#ifndef _DEMIURGE_LEGENDS_XML_PARSER_HPP_
#define _DEMIURGE_LEGENDS_XML_PARSER_HPP_

#include <QString>
#include <QXmlStreamReader>

namespace demiurge {
  class LegendsData;

  class LegendsXMLParser {
  public:
    LegendsXMLParser(LegendsData* legends, const QString& fileName);

    bool parse();
    const QString& errorMessage() const { return errorMessage_; }

  private:
    Q_DISABLE_COPY(LegendsXMLParser)

    bool parse_file_();
    bool parse_world_();
    bool parse_regions_();

    bool parse_region_();

    QString           fileName_;
    QXmlStreamReader  xml_;
    LegendsData*      legends_;

    QString           errorMessage_;
  };
}

#endif
