program ExampleSimple;

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
    procedure Execute;
  end;

const
  HOST = 'localhost';
  PORT = 4223;
  UID = 'XYZ'; { Change to your UID }

var
  e: TExample;

procedure TExample.Execute;
var edge_count: longword;
begin
  { Create IP connection }
  ipcon := TIPConnection.Create;

  { Create device object }
  he := TBrickletHallEffect.Create(UID, ipcon);

  { Connect to brickd }
  ipcon.Connect(HOST, PORT);
  { Don't use device before ipcon is connected }

  { Get current edge count without reset }
  edge_count := he.GetEdgeCount(false);
  WriteLn(Format('Edge Count: %d', [edge_count]));

  WriteLn('Press key to exit');
  ReadLn;
  ipcon.Destroy; { Calls ipcon.Disconnect internally }
end;

begin
  e := TExample.Create;
  e.Execute;
  e.Destroy;
end.
