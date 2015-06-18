program ExampleCallback;

{$ifdef MSWINDOWS}{$apptype CONSOLE}{$endif}
{$ifdef FPC}{$mode OBJFPC}{$H+}{$endif}

uses
  SysUtils, IPConnection, BrickletHallEffect;

type
  TExample = class
  private
    ipcon: TIPConnection;
    he: TBrickletHallEffect;
  public
    procedure EdgeCountCB(sender: TBrickletHallEffect;
                          const edge_count: longword; const value: Boolean);
    procedure Execute;
  end;

const
  HOST = 'localhost';
  PORT = 4223;
  UID = 'XYZ'; { Change to your UID }

var
  e: TExample;

{ Callback function for edge count callback }
procedure TExample.EdgeCountCB(sender: TBrickletHallEffect;
                               const edge_count: longword; const value: Boolean);
begin
  WriteLn(Format('Edge Count: %d', [edge_count]));
end;

procedure TExample.Execute;
begin
  { Create IP connection }
  ipcon := TIPConnection.Create;

  { Create device object }
  he := TBrickletHallEffect.Create(UID, ipcon);

  { Connect to brickd }
  ipcon.Connect(HOST, PORT);
  { Don't use device before ipcon is connected }

  { Set Period for edge_count callback to 0.05s (50ms)
    Note: The edge_count callback is only called every 50ms if the
          edge_count has changed since the last call! }
  he.SetEdgeCountCallbackPeriod(50);

  { Register edge_count callback to procedure EdgeCountCB }
  he.OnEdgeCount := {$ifdef FPC}@{$endif}EdgeCountCB;

  WriteLn('Press key to exit');
  ReadLn;
  ipcon.Destroy; { Calls ipcon.Disconnect internally }
end;

begin
  e := TExample.Create;
  e.Execute;
  e.Destroy;
end.
