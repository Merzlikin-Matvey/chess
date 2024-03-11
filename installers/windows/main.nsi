Outfile "Chess_Installer.exe"
InstallDir "$PROGRAMFILES\chess"

Section "chess"
    SetOutPath $INSTDIR
    File /r "path\to\your\application\*.*"
    CreateShortcut "$SMPROGRAMS\My Application.lnk" "$INSTDIR\your_application.exe"
SectionEnd