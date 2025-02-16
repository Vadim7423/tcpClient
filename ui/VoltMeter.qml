import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import testQtClient

Rectangle {
  id: root

  property var btn_text: ["Запуск измерения", "Останов измерения", "Запуск измерения", "Запуск измерения"]
  property int idx: 0
  property int range_idx: 0
  property int volt_status: 0
  property real volt_val: 0

  RowLayout {
    height: parent.height
    spacing: 10
    width: parent.width

    Button {
      Layout.alignment: Qt.AlignHCenter
      Layout.preferredHeight: parent.height - 30
      Layout.preferredWidth: 150
      text: "Обновить статус"

      onClicked: {
        App.statusRequest(root.idx);
      }
    }

    ComboBox {
      id: comboBox

      Layout.alignment: Qt.AlignHCenter
      Layout.preferredHeight: parent.height - 30
      Layout.preferredWidth: 150
      currentIndex: range_idx
      model: ["0.0000001 - 0.001 В", "0.001 - 1 В", "1 - 1000 В", "1000 - 1000000 В"]

      onActivated: {
        App.setRange(idx, currentIndex);
      }
    }

    Button {
      Layout.alignment: Qt.AlignHCenter
      Layout.preferredHeight: parent.height - 30
      Layout.preferredWidth: 150
      text: btn_text[volt_status]

      onClicked: {
        if (volt_status === 1) {
          App.stopMeasure(root.idx);
        } else {
          App.startMeasure(root.idx);
        }
      }
    }

    Text {
      Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
      Layout.preferredWidth: 90
      height: parent.height - 30
      text: root.volt_val
    }
  }
}
