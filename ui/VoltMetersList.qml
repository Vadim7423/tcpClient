import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Item {
  id: root

  property var borderColors: ["#5feafe", "#27aa27", "#6d5af6", "#faada9"]
  property var colors: ["#e6edee", "#e8ffe8", "#e9e6fe", "#feeeed"]

  Item {
    height: !volt_meter_model.rowCount() ? 20 : 0
    width: parent.width

    Text {
      text: "необходимо обновить данные"
    }
  }

  ListView {
    id: list

    height: parent.height
    model: volt_meter_model
    spacing: 10
    width: parent.width

    delegate: VoltMeter {
      color: root.colors[status]
      height: 70
      idx: index
      range_idx: range
      volt_status: status
      volt_val: {
        if (val < 1) {
          return val.toFixed(7);
        } else {
          return val;
        }
      }
      width: list.width

      border {
        color: root.borderColors[status]
        width: 2
      }
    }
  }
}
