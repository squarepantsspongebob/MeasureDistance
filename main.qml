import QtQuick 2.7
import QtQuick.Window 2.2
import Lines 1.0
import Points 1.0
import CurveM 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    MeasureLine{
        id: mLine1
        anchors.fill: parent
        xStart: 200; yStart: 200
        xEnd: 400; yEnd:100
        color: "blue"
    }

    MeasureLine{
        id: mLine
        anchors.fill: parent
        xStart: 200; yStart: 100
        xEnd: 200; yEnd: 400
        color: "blue"
    }

}
