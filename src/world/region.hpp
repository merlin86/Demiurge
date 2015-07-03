// region.hpp - Region class definition
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

#ifndef _DEMIURGE_LEGENDS_WORLD_REGION_HPP_
#define _DEMIURGE_LEGENDS_WORLD_REGION_HPP_

#include <QObject>
#include <QString>

namespace demiurge {
  namespace world {
    class Region: public QObject {
      Q_OBJECT
      Q_ENUMS(Type)
      Q_PROPERTY(QString name READ name CONSTANT)
      Q_PROPERTY(Type type READ type CONSTANT)

    public:
      enum Type { Unknown, Desert, Forest, Glacier, Grassland, Hills, Lake, Mountains, Ocean, Tundra, Wetland };

      explicit Region(QObject* parent = nullptr): QObject(parent), type_(Unknown) {}
      Region(const QString& name, Type type, QObject* parent = nullptr):
        QObject(parent), name_(name), type_(type) {}
      virtual ~Region() {}

      const QString& name() const { return name_; }
      Type type() const { return type_; }

    private:
      Q_DISABLE_COPY(Region)

      const QString name_;
      const Type    type_;
    };
  }
}

#endif
