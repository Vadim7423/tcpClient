import QtQuick
import QtQuick.Layouts

Item {
  id: root

  property var borderColors: ["#5feafe", "#27aa27", "#6d5af6", "#faada9"]
  property var colors: ["#e6edee", "#e8ffe8", "#e9e6fe", "#feeeed"]
  property var names: ["По умолчанию", "Измерение", "Занят", "Ошибка"]

  RowLayout {
    height: parent.height
    spacing: 0
    width: parent.width

    Repeater {
      model: 4

      delegate: Item {
        id: name

        Layout.preferredHeight: parent.height
        Layout.preferredWidth: parent.width / 4

        Rectangle {
          id: marker

          color: colors[index]
          height: 20
          width: 20

          border {
            color: borderColors[index]
            width: 2
          }
        }

        Text {
          text: names[index]

          anchors {
            left: marker.right
            leftMargin: 10
          }
        }
      }
    }
  }
}
