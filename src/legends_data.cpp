// legends_data.cpp - LegendsData class implementation
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
#include <QtQml>
#include "legends_data.hpp"
#include "legends_xml_parser.hpp"

using namespace demiurge;
using namespace demiurge::world;

QQmlListProperty<Region> LegendsData::qml_regions() {
  return QQmlListProperty<Region>(this, nullptr, &LegendsData::qml_regions_count_, &LegendsData::qml_regions_at_);
}

bool LegendsData::load(const QString& fileName) {
  LegendsXMLParser parser(this, fileName);
  return parser.parse();
}

int LegendsData::qml_regions_count_(QQmlListProperty<Region>* property) {
  LegendsData* legends = qobject_cast<LegendsData*>(property->object);
  if(legends) return legends->regions_.count();
  else return 0;
}

Region* LegendsData::qml_regions_at_(QQmlListProperty<Region>* property, int index) {
  LegendsData* legends = qobject_cast<LegendsData*>(property->object);
  if(legends) return legends->regions_.at(index);
  else return nullptr;
}
