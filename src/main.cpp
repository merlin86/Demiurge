// main.cpp - Application entry point
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

#include <QtQml>
#include <QApplication>
#include <QQmlApplicationEngine>
#include "legends_data.hpp"
#include "world/region.hpp"

static QObject* demiurge_legendsdata_sigletontype_provider(QQmlEngine* engine, QJSEngine* scriptEngine) {
  Q_UNUSED(engine)
  Q_UNUSED(scriptEngine)

  demiurge::LegendsData* data = new demiurge::LegendsData();
  return (QObject*)data;
}

void register_qml_types() {
  // Registering instanciable types
  qmlRegisterType<demiurge::world::Region>("Demiurge.LegendsData", 1, 0, "Region");

  // Registering singleton types
  qmlRegisterSingletonType<demiurge::LegendsData>("Demiurge.LegendsData", 1, 0, "LegendsData",
                                                  demiurge_legendsdata_sigletontype_provider);
}

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  // Setting application parameters
  app.setApplicationName(QObject::tr("Demiurge"));
  app.setApplicationVersion(QObject::tr("1.0.0"));
  app.setOrganizationDomain(QObject::tr("vlitvinov.org"));
  app.setOrganizationName(QObject::tr("vlitvinov"));

  // Registering QML types
  register_qml_types();

  // Setting up the QML engine
  QQmlApplicationEngine engine;
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

  return app.exec();
}
