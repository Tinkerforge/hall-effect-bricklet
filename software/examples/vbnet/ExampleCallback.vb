Imports Tinkerforge

Module ExampleCallback
    Const HOST As String = "localhost"
    Const PORT As Integer = 4223
    Const UID As String = "XYZ" ' Change to your UID

    ' Callback function for edge_count callback
    Sub EdgeCountCB(ByVal sender As BrickletHallEffect, ByVal edge_count As Long, ByVal value As Boolean)
        System.Console.WriteLine("Edge Count: " + edge_count.ToString())
    End Sub

    Sub Main()
        Dim ipcon As New IPConnection() ' Create IP connection
        Dim he As New BrickletHallEffect(UID, ipcon) ' Create device object

        ipcon.Connect(HOST, PORT) ' Connect to brickd
        ' Don't use device before ipcon is connected

        ' Set Period for edge_count callback to 0.05s (50ms)
        ' Note: The edge_count callback is only called every 50ms if the
        '       edge_count has changed since the last call!
        he.SetEdgeCountCallbackPeriod(50)

        ' Register edge count callback to EdgeCountCB
        AddHandler he.EdgeCount, AddressOf EdgeCountCB

        System.Console.WriteLine("Press key to exit")
        System.Console.ReadKey()
        ipcon.Disconnect()
    End Sub
End Module
