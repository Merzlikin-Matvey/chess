Outfile "Chess_Installer.exe"
InstallDir "$PROGRAMFILES\chess"

Section "chess"
    SetOutPath $INSTDIR
    File /r "files/*"
    CreateShortcut "$SMPROGRAMS\Chess.lnk" "$INSTDIR\chess.exe"
    CreateShortcut "$DESKTOP\Chess.lnk" "$INSTDIR\chess.exe"
SectionEnd