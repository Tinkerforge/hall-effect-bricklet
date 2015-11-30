Imports System
Imports Tinkerforge

Module ExampleCallback
    Const HOST As String = "localhost"
    Const PORT As Integer = 4223
    Const UID As String = "XYZ" ' Change to your UID

    ' Callback subroutine for edge count callback
    Sub EdgeCountCB(ByVal sender As BrickletHallEffect, _
                    ByVal edgeCount As Long, ByVal value As Boolean)
        Console.WriteLine("Edge Count: " + edgeCount.ToString())
    End Sub

    Sub Main()
        Dim ipcon As New IPConnection() ' Create IP connection
        Dim he As New BrickletHallEffect(UID, ipcon) ' Create device object

        ipcon.Connect(HOST, PORT) ' Connect to brickd
        ' Don't use device before ipcon is connected

        ' Register edge count callback to subroutine EdgeCountCB
        AddHandler he.EdgeCount, AddressOf EdgeCountCB

        ' Set period for edge count callback to 0.05s (50ms)
        ' Note: The edge count callback is only called every 0.05 seconds
        '       if the edge count has changed since the last call!
        he.SetEdgeCountCallbackPeriod(50)

        Console.WriteLine("Press key to exit")
        Console.ReadLine()
        ipcon.Disconnect()
    End Sub
End Module
