// legends_xml_parser.cpp - LegendsXMLParser class implementation
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

#include <QtCore>
#include "legends_data.hpp"
#include "legends_xml_parser.hpp"

using namespace demiurge;
using namespace demiurge::world;

LegendsXMLParser::LegendsXMLParser(LegendsData* legends, const QString& fileName):
  fileName_(fileName), legends_(legends) {
}

bool LegendsXMLParser::parse() {
  qDebug() << "Loading legends from" << fileName_;
  QFile xmlFile(QUrl(fileName_).toLocalFile());
  if(!xmlFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
    errorMessage_ = QObject::tr("Unable to open file %1 for reading.").arg(fileName_);
    qDebug() << "ERROR: " << errorMessage_;
    return false;
  }

  xml_.setDevice(&xmlFile);
  bool ok = parse_file_();

  // Printing some statistics
  if(ok) {
    qDebug() << "Legends succesfully loaded:";
    qDebug() << "      " << legends_->regions().count() << "regions.";
  } else qDebug() << "Legends parsing failed!";

  return ok;
}

bool LegendsXMLParser::parse_file_() {
  bool ok = true;

  if(xml_.readNextStartElement()) {
    if(xml_.name() == "df_world") {
      ok = parse_world_();
    } else {
      errorMessage_ = QObject::tr("The only global tag must be df_world.");
      qDebug() << "ERROR: " << errorMessage_;
      ok = false;
    }
  }

  return ok;
}

bool LegendsXMLParser::parse_world_() {
  Q_ASSERT(xml_.isStartElement() && xml_.name() == "df_world");

  bool ok = true;
  while(ok && xml_.readNextStartElement()) {
    if(xml_.name() == "regions") ok = parse_regions_();
    else xml_.skipCurrentElement();
  }

  return ok;
}

bool LegendsXMLParser::parse_regions_() {
  Q_ASSERT(xml_.isStartElement() && xml_.name() == "regions");

  // Clean up the list of regions
  for(Region* region : legends_->regions()) region->deleteLater();
  legends_->regions().clear();

  bool ok = true;
  while(ok && xml_.readNextStartElement()) {
    if(xml_.name() == "region") ok = parse_region_();
    else xml_.skipCurrentElement();
  }

  return ok;
}

Region::Type convert_string_to_region_type(const QString& string) {
  if(string == "Desert") { return Region::Desert; }
  else if(string == "Forest") { return Region::Forest; }
  else if(string == "Glacier") { return Region::Glacier; }
  else if(string == "Grassland") { return Region::Grassland; }
  else if(string == "Hills") { return Region::Hills; }
  else if(string == "Lake") { return Region::Lake; }
  else if(string == "Mountains") { return Region::Mountains; }
  else if(string == "Ocean") { return Region::Ocean; }
  else if(string == "Tundra") { return Region::Tundra; }
  else if(string == "Wetland") { return Region::Wetland; }
  else {
    qDebug() << "WARNING: Undefined region type detected.";
    return Region::Unknown;
  }
}

bool LegendsXMLParser::parse_region_() {
  Q_ASSERT(xml_.isStartElement() && xml_.name() == "region");

  unsigned long id;
  QString name;
  QString type;

  bool ok = true;
  while(ok && xml_.readNextStartElement()) {
    if(xml_.name() == "id") {
      QString tmp = xml_.readElementText();
      id = tmp.toULong(&ok);
    } else if(xml_.name() == "name") {
      name = xml_.readElementText();
    } else if(xml_.name() == "type") {
      type = xml_.readElementText();
    } else xml_.skipCurrentElement();
  }

  if(ok) {
    if(id != (unsigned long)legends_->regions().count()) qDebug() << "WARNING: Region ID is out of order.";
    legends_->regions().append(new Region(name, convert_string_to_region_type(type), legends_));
    return true;
  } else return false;
}
