// main.qml - Application main window
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

import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

import Demiurge.LegendsData 1.0

ApplicationWindow {
  title: qsTr("Demiurge")
  width: 1024
  height: 768
  visible: true

  menuBar: MenuBar {
    Menu {
      title: qsTr("&File")

      MenuItem {
        text: qsTr("&Open...")
        shortcut: "Ctrl+O"
        onTriggered: openFileDialog.open()
      }

      MenuSeparator {}

      MenuItem {
        text: qsTr("&Quit")
        shortcut: "Ctrl+Q"
        onTriggered: Qt.quit();
      }
    }
  }

  FileDialog {
    id: openFileDialog
    title: qsTr("Choose the main legends XML file...")
    nameFilters: [qsTr("XML files (*.xml)"), qsTr("All files (*.*)")]

    onAccepted: LegendsData.load(openFileDialog.fileUrl)
  }
}
