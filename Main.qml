import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import "ui"

Window {
  id: root

  height: 480
  title: qsTr("Hello World")
  visible: true
  width: 640

  ColumnLayout {
    anchors.centerIn: parent
    height: parent.height - 30
    width: parent.width - 30

    ConnectionRow {
      id: connect_row

      Layout.preferredHeight: 60
      Layout.preferredWidth: parent.width
    }

    StatusesRow {
      id: statuses

      Layout.preferredHeight: 30
      Layout.preferredWidth: parent.width
    }

    VoltMetersList {
      Layout.preferredHeight: parent.height - statuses.height - connect_row.height
      Layout.preferredWidth: parent.width
    }
  }
}
