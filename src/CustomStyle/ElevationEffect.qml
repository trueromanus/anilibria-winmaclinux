import QtQuick 2.12

Item {
    id: effect

    property var source
    property int elevation: 0
    property color backgroundColor: "black"

    property bool fullWidth: false
    property bool fullHeight: false

    readonly property Item sourceItem: source.sourceItem

    readonly property var _shadows: [
        [{offset: 0, blur: 0, spread: 0},
         {offset: 0, blur: 0, spread: 0},
         {offset: 0, blur: 0, spread: 0}],

        [{offset: 1, blur: 3, spread: 0},
         {offset: 1, blur: 1, spread: 0},
         {offset: 2, blur: 1, spread: -1}],

        [{offset: 1, blur: 5, spread: 0},
         {offset: 2, blur: 2, spread: 0},
         {offset: 3, blur: 1, spread: -2}],

        [{offset: 1, blur: 8, spread: 0},
         {offset: 3, blur: 4, spread: 0},
         {offset: 3, blur: 3, spread: -2}],

        [{offset: 2, blur: 4, spread: -1},
         {offset: 4, blur: 5, spread: 0},
         {offset: 1, blur: 10, spread: 0}],

        [{offset: 3, blur: 5, spread: -1},
         {offset: 5, blur: 8, spread: 0},
         {offset: 1, blur: 14, spread: 0}],

        [{offset: 3, blur: 5, spread: -1},
         {offset: 6, blur: 10, spread: 0},
         {offset: 1, blur: 18, spread: 0}],

        [{offset: 4, blur: 5, spread: -2},
         {offset: 7, blur: 10, spread: 1},
         {offset: 2, blur: 16, spread: 1}],

        [{offset: 5, blur: 5, spread: -3},
         {offset: 8, blur: 10, spread: 1},
         {offset: 3, blur: 14, spread: 2}],

        [{offset: 5, blur: 6, spread: -3},
         {offset: 9, blur: 12, spread: 1},
         {offset: 3, blur: 16, spread: 2}],

        [{offset: 6, blur: 6, spread: -3},
         {offset: 10, blur: 14, spread: 1},
         {offset: 4, blur: 18, spread: 3}],

        [{offset: 6, blur: 7, spread: -4},
         {offset: 11, blur: 15, spread: 1},
         {offset: 4, blur: 20, spread: 3}],

        [{offset: 7, blur: 8, spread: -4},
         {offset: 12, blur: 17, spread: 2},
         {offset: 5, blur: 22, spread: 4}],

        [{offset: 7, blur: 8, spread: -4},
         {offset: 13, blur: 19, spread: 2},
         {offset: 5, blur: 24, spread: 4}],

        [{offset: 7, blur: 9, spread: -4},
         {offset: 14, blur: 21, spread: 2},
         {offset: 5, blur: 26, spread: 4}],

        [{offset: 8, blur: 9, spread: -5},
         {offset: 15, blur: 22, spread: 2},
         {offset: 6, blur: 28, spread: 5}],

        [{offset: 8, blur: 10, spread: -5},
         {offset: 16, blur: 24, spread: 2},
         {offset: 6, blur: 30, spread: 5}],

        [{offset: 8, blur: 11, spread: -5},
         {offset: 17, blur: 26, spread: 2},
         {offset: 6, blur: 32, spread: 5}],

        [{offset: 9, blur: 11, spread: -5},
         {offset: 18, blur: 28, spread: 2},
         {offset: 7, blur: 34, spread: 6}],

        [{offset: 9, blur: 12, spread: -6},
         {offset: 19, blur: 29, spread: 2},
         {offset: 7, blur: 36, spread: 6}],

        [{offset: 10, blur: 13, spread: -6},
         {offset: 20, blur: 31, spread: 3},
         {offset: 8, blur: 38, spread: 7}],

        [{offset: 10, blur: 13, spread: -6},
         {offset: 21, blur: 33, spread: 3},
         {offset: 8, blur: 40, spread: 7}],

        [{offset: 10, blur: 14, spread: -6},
         {offset: 22, blur: 35, spread: 3},
         {offset: 8, blur: 42, spread: 7}],

        [{offset: 11, blur: 14, spread: -7},
         {offset: 23, blur: 36, spread: 3},
         {offset: 9, blur: 44, spread: 8}],

        [{offset: 11, blur: 15, spread: -7},
         {offset: 24, blur: 38, spread: 3},
         {offset: 9, blur: 46, spread: 8}]
    ]

    readonly property var _shadow: _shadows[Math.max(0, Math.min(elevation, _shadows.length - 1))]

    Item {
        property int margin: -100

        x: margin
        y: margin
        width: parent.width - 2 * margin
        height: parent.height - 2 * margin

        layer.enabled: true
        BoxShadow {
            offsetY: effect._shadow[0].offset
            blurRadius: effect._shadow[0].blur
            spreadRadius: effect._shadow[0].spread
            color: Qt.rgba(backgroundColor.r, backgroundColor.g, backgroundColor.b, 0.2)

            fullWidth: effect.fullWidth
            fullHeight: effect.fullHeight
            source: effect.sourceItem
        }

        BoxShadow {
            offsetY: effect._shadow[1].offset
            blurRadius: effect._shadow[1].blur
            spreadRadius: effect._shadow[1].spread
            color: Qt.rgba(backgroundColor.r, backgroundColor.g, backgroundColor.b, 0.14)

            fullWidth: effect.fullWidth
            fullHeight: effect.fullHeight
            source: effect.sourceItem
        }

        BoxShadow {
            offsetY: effect._shadow[2].offset
            blurRadius: effect._shadow[2].blur
            spreadRadius: effect._shadow[2].spread
            color: Qt.rgba(backgroundColor.r, backgroundColor.g, backgroundColor.b, 0.2)

            fullWidth: effect.fullWidth
            fullHeight: effect.fullHeight
            source: effect.sourceItem
        }

        ShaderEffect {
            property alias source: effect.source

            x: (parent.width - width)/2
            y: (parent.height - height)/2
            width: effect.sourceItem.width
            height: effect.sourceItem.height
        }
    }
}
