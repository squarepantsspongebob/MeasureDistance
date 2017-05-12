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
            color: "blue"
        }
//    }
//    MeasureLinePoint{
//        id: mLinePoint1
//        width: 400; height: 400
//        xCenter: 100; yCenter: 100
//        color:"red"
//    }
}
