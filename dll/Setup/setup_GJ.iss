; Этот сценарий создан с помощью Мастера Inno Setup.
; ОБРАТИТЕСЬ К СПРАВОЧНОЙ ДОКУМЕНТАЦИИ, ЧТОБЫ ИСПОЛЬЗОВАТЬ ВСЕ ВОЗМОЖНОСТИ INNO SETUP!

#define MyAppName "SPP GAV"
#define MyAppVersion "2.2"
#define MyAppPublisher "GAV"

[Setup]
; Примечание: Значение AppId является уникальным идентификатором для этого приложения.
; Не используйте одно и тоже значение AppId для разных приложений.
; (Для создания нового значения GUID, выберите в меню "Инструменты" пункт "Создать GUID".)
AppId={{3EE72BDA-7C4A-436E-8B3C-ECF1022A0432}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
DefaultDirName={pf}\{#MyAppName}
DefaultGroupName={#MyAppName}
AllowNoIcons=yes
LicenseFile=D:\opencv\progi_qt_oencv\spp\лицензия.txt
OutputDir=D:\opencv\progi_qt_oencv\spp\Setup
OutputBaseFilename=setup
SetupIconFile=D:\opencv\progi_qt_oencv\spp\step.ico
Password=gj88632618372
Compression=lzma
SolidCompression=yes

[Languages]
Name: "russian"; MessagesFile: "compiler:Languages\Russian.isl"

 [Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "D:\opencv\progi_qt_oencv\spp\Builder.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\opencv\progi_qt_oencv\spp\icudt52.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\opencv\progi_qt_oencv\spp\icuin52.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\opencv\progi_qt_oencv\spp\icuuc52.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\opencv\progi_qt_oencv\spp\Calibration.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\opencv\progi_qt_oencv\spp\libgcc_s_dw2-1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\opencv\progi_qt_oencv\spp\libopencv_core249.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\opencv\progi_qt_oencv\spp\libopencv_highgui249.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\opencv\progi_qt_oencv\spp\libopencv_imgproc249.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\opencv\progi_qt_oencv\spp\libstdc++-6.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\opencv\progi_qt_oencv\spp\libwinpthread-1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\opencv\progi_qt_oencv\spp\opencv_ffmpeg249.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\opencv\progi_qt_oencv\spp\Qt5Core.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\opencv\progi_qt_oencv\spp\Qt5Gui.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\opencv\progi_qt_oencv\spp\Qt5Network.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\opencv\progi_qt_oencv\spp\Qt5OpenGL.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\opencv\progi_qt_oencv\spp\Qt5PrintSupport.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\opencv\progi_qt_oencv\spp\Qt5Sql.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\opencv\progi_qt_oencv\spp\Qt5Svg.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\opencv\progi_qt_oencv\spp\Qt5Test.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\opencv\progi_qt_oencv\spp\Qt5Widgets.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\opencv\progi_qt_oencv\spp\qwt.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\opencv\progi_qt_oencv\spp\step.ico"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\opencv\progi_qt_oencv\spp\tray.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\opencv\progi_qt_oencv\spp\Help\*"; DestDir: "{app}\Help"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "D:\opencv\progi_qt_oencv\spp\platforms\*"; DestDir: "{app}\platforms"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "D:\opencv\progi\spp\reports\*"; DestDir: "{app}\reports"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "D:\opencv\progi_qt_oencv\spp\sqldrivers\*"; DestDir: "{app}\sqldrivers"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "D:\opencv\progi_qt_oencv\spp\video\*"; DestDir: "{app}\video"; Flags: ignoreversion
Source: "D:\opencv\progi_qt_oencv\spp\SPP.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\opencv\progi_qt_oencv\spp\tmp.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\opencv\progi_qt_oencv\spp\setting.ini"; DestDir: "{app}"; Flags: ignoreversion
; Примечание: Не используйте флаги "ignoreversion" для общих системных файлов.


[Registry]
Root: HKCU; Subkey: "Software\SPP Gav\Settings\"; ValueType: String; ValueName: Catalog; ValueData: "{app}"; 
Root: HKCU; Subkey: "SOFTWARE\Microsoft\Windows\CurrentVersion\Run\"; ValueType: String; ValueName: "SPP GAV"; ValueData: "{app}\SPP.exe"; Flags: preservestringtype
Root: HKCU; Subkey: "SOFTWARE\Microsoft\Windows\CurrentVersion\Run\"; ValueType: String; ValueName: "SPP GAV"; ValueData: "{app}\SPP.exe"; Flags: uninsdeletevalue
Root: HKCU; Subkey: "Software\SPP Gav\";  Flags: uninsdeletekey

[Icons]
Name: "{group}\SPP GAV"; Filename: "{app}\SPP.exe"
Name: "{commondesktop}\SPP GAV"; Filename: "{app}\SPP.exe"; Tasks: desktopicon
Name: "{group}\Builder"; Filename: "{app}\Builder.exe"
Name: "{commondesktop}\Builder"; Filename: "{app}\Builder.exe"; Tasks: desktopicon
Name: "{group}\Calibration"; Filename: "{app}\Calibration.exe"
Name: "{commondesktop}\Calibration"; Filename: "{app}\Calibration.exe"; Tasks: desktopicon

Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"

[Run]
Filename: "{app}\tmp.exe"; Parameters: "";
Filename: "cmd"; Parameters: "/c del ""{app}\tmp.exe""";
;Filename: "cmd"; Parameters: "/c del ""{app}\setting.ini""";

[Uninstalldelete]
Type:filesandordirs;Name:"{app}"
                      






