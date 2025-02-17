import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import testQtClient

Item {
  id: root

  RowLayout {
    height: parent.height
    spacing: 10
    width: parent.width

    Button {
      id: connect_btn

      Layout.preferredHeight: parent.height
      Layout.preferredWidth: parent.width / 3 - 10
      enabled: !App.connection
      text: "Подключиться"

      background: Rectangle {
        color: App.connection ? "#d7d5d7" : "#cae7cd"
      }

      onClicked: {
        App.connection = true;
      }
    }

    Button {
      id: disconnect_btn

      Layout.preferredHeight: parent.height
      Layout.preferredWidth: parent.width / 3 - 10
      enabled: App.connection
      text: "Отлючиться"

      background: Rectangle {
        color: !App.connection ? "#d7d5d7" : "#cae7cd"
      }

      onClicked: {
        App.connection = false;
      }
    }

    Button {
      id: test_btn

      Layout.preferredHeight: parent.height
      Layout.preferredWidth: parent.width / 3 - 10
      enabled: App.connection
      text: "Обновить данные"

      background: Rectangle {
        color: !App.connection ? "#d7d5d7" : "#cae7cd"
      }

      onClicked: {
        App.testRequest();
      }
    }
  }
}
