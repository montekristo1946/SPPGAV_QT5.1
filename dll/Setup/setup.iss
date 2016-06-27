; Этот сценарий создан с помощью Мастера Inno Setup.
; ОБРАТИТЕСЬ К СПРАВОЧНОЙ ДОКУМЕНТАЦИИ, ЧТОБЫ ИСПОЛЬЗОВАТЬ ВСЕ ВОЗМОЖНОСТИ INNO SETUP!

[Setup]
; Примечание: Значение AppId является уникальным идентификатором для этого приложения.
; Не используйте одно и тоже значение AppId для разных приложений.
; (Для создания нового значения GUID, выберите в меню "Инструменты" пункт "Создать GUID".)
AppId={{C04E1F17-A9DC-4AB0-A6D7-DE81EBBE41FA}
AppName=SPP GAV
AppVersion=SPP GAV 1.2
;AppVerName=SPP GAV SPP GAV 1.2
DefaultDirName={pf}\SPP GAV
DisableDirPage=yes
DefaultGroupName=SPP GAV
AllowNoIcons=yes
OutputDir=d:\opencv\progi_qt_oencv\spp\Setup\
OutputBaseFilename=setup
SetupIconFile=d:\opencv\progi_qt_oencv\spp\step.ico
Compression=lzma
SolidCompression=yes

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "D:\opencv\progi\spp\SPP.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\opencv\progi\spp\platforms\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "D:\opencv\progi\spp\icudt51.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\opencv\progi\spp\icuin51.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\opencv\progi\spp\icuuc51.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\opencv\progi\spp\libgcc_s_dw2-1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\opencv\progi\spp\libstdc++-6.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\opencv\progi\spp\libwinpthread-1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\opencv\progi\spp\Qt5Core.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\opencv\progi\spp\Qt5Gui.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\opencv\progi\spp\Qt5Network.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\opencv\progi\spp\Qt5Widgets.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\opencv\progi\spp\SPP.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\opencv\progi\spp\tray.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\opencv\progi\spp\VideoRun.exe"; DestDir: "{app}"; Flags: ignoreversion

;построитель!
Source: "D:\opencv\progi\spp\Qt5Sql.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\opencv\progi\spp\Qt5OpenGL.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\opencv\progi\spp\Qt5PrintSupport.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\opencv\progi\spp\Qt5Svg.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\opencv\progi\spp\qwt.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\opencv\progi\spp\sqldrivers\*"; DestDir: "{app}\sqldrivers"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "D:\opencv\progi\spp\Help\*"; DestDir: "{app}\Help"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "D:\opencv\progi\spp\Builder.exe"; DestDir: "{app}"; Flags: ignoreversion

;OpenCV
 Source: "D:\opencv\progi\spp\opencv_core249.dll"; DestDir: "{app}"; Flags: ignoreversion
 Source: "D:\opencv\progi\spp\opencv_ffmpeg249.dll"; DestDir: "{app}"; Flags: ignoreversion
 Source: "D:\opencv\progi\spp\opencv_highgui249.dll"; DestDir: "{app}"; Flags: ignoreversion
 Source: "D:\opencv\progi\spp\opencv_imgproc249.dll"; DestDir: "{app}"; Flags: ignoreversion
 Source: "D:\opencv\progi\spp\opencv_imgproc249.dll"; DestDir: "{app}"; Flags: ignoreversion

;доп ресурсы
Source: "D:\opencv\progi\spp\platforms\*"; DestDir: "{app}\platforms"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "D:\opencv\progi\spp\reports\*"; DestDir: "{app}\reports"; Flags: ignoreversion
Source: "D:\opencv\progi\spp\vcredist_x86.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\opencv\progi\spp\regAdd.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\opencv\progi\spp\regDel.exe"; DestDir: "{app}"; Flags: ignoreversion


; Примечание: Не используйте флаги "ignoreversion" для общих системных файлов.

[Icons]
Name: "{group}\SPP GAV"; Filename: "{app}\SPP.exe"
Name: "{commondesktop}\SPP GAV"; Filename: "{app}\SPP.exe"; Tasks: desktopicon
Name: "{group}\Builder"; Filename: "{app}\Builder.exe"
Name: "{commondesktop}\Отчет"; Filename: "{app}\Builder.exe"; Tasks: desktopicon
Name: "{group}\Uninstall"; Filename: "{app}\uinins000.exe"

[Run]

Filename: "{app}\vcredist_x86.exe"; Parameters: "/passive";
Filename: "{app}\regAdd.exe"; Parameters: "";
  
[UninstallRun]
Filename: "{app}\regDel.exe"; Parameters: "";

[Installdelete]
Type:files; Name:"{app}\vcredist_x86.exe"
Type:files; Name:"{app}\regAdd.exe"

[Uninstalldelete]
Type:filesandordirs;Name:"{app}"

