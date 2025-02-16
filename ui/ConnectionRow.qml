import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import testQtClient

Item {
  RowLayout {
    height: parent.height
    width: parent.width

    Button {
      id: connect_btn

      enabled: !App.connection
      height: parent.height
      text: "Подключиться"
      width: 200

      onClicked: {
        App.connection = true;
      }
    }

    Button {
      id: disconnect_btn

      enabled: App.connection
      height: parent.height
      text: "Отлючиться"
      width: 200

      onClicked: {
        App.connection = false;
      }
    }

    Button {
      id: test_btn

      enabled: App.connection
      height: parent.height
      text: "Тест"
      width: 200

      onClicked: {
        App.testRequest();
      }
    }
  }
}
