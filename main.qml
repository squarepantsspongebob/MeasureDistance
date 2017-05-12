import QtQuick 2.7
import QtQuick.Window 2.2
import Lines 1.0
import Points 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

//    Rectangle{
//        width: 600; height: 400
//        color:"blue"
//        anchors.centerIn: parent
        MeasureLine{
            id: mLine1
            width: 140; height: 140
            x: 300; y: 300
            color: "blue"
        }
        MeasureLine{
            id: mLine
            width: 140; height: 140
            x: 311; y: 311
        }

        Rectangle{
            width: mLine1.width; height: mLine1.height
            color:"red"
            opacity: 0.0
            x: mLine1.x; y: mLine1.y
        }
}
