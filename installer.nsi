
; The name of the installer
Name "VclImageThumbnailExtension"

; The file to write
OutFile "VclImageThumbnailExtensionInstaller.exe"

; The default installation directory
InstallDir $PROGRAMFILES64\VclImageThumbnailExtension

; Registry key to check for directory
InstallDirRegKey HKLM "Software\VclImageThumbnailExtension" "Install_Dir"

; Request application privileges for Windows Vista
RequestExecutionLevel admin

;--------------------------------

; Pages

Page directory
Page instfiles

UninstPage uninstConfirm
UninstPage instfiles

;--------------------------------

; The stuff to install
Section "VclImageThumbnailExtension (required)"

  SectionIn RO
  
  ; Set output path to the installation directory.
  SetOutPath $INSTDIR
  
  ; Put file there
  File "VclGraphicsThumbnailExt.dll"
  
  ; Register the explorer extension
  ExecWait 'regsvr32.exe /s "$INSTDIR\VclGraphicsThumbnailExt.dll"'
  
  ; Write the installation path into the registry
  WriteRegStr HKLM SOFTWARE\VclImageThumbnailExtension "Install_Dir" "$INSTDIR"
  
  ; Write the uninstall keys for Windows
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\VclImageThumbnailExtension" "DisplayName" "VclImageThumbnailExtension"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\VclImageThumbnailExtension" "Publisher" "Basil Fierz"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\VclImageThumbnailExtension" "UninstallString" '"$INSTDIR\uninstall.exe"'
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\VclImageThumbnailExtension" "NoModify" 1
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\VclImageThumbnailExtension" "NoRepair" 1
  WriteUninstaller "uninstall.exe"
  
SectionEnd

;--------------------------------

; Uninstaller

Section "Uninstall"
  
  ; Remove registry keys
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\VclImageThumbnailExtension"
  DeleteRegKey HKLM SOFTWARE\VclImageThumbnailExtension

  ; Remove the explorer extension from the explorer registry
  ExecWait 'regsvr32.exe /s /u "$INSTDIR\VclGraphicsThumbnailExt.dll"'
  
  ; Remove files and uninstaller
  Delete $INSTDIR\VclGraphicsThumbnailExt.dll
  Delete $INSTDIR\uninstall.exe

  ; Remove directories used
  RMDir "$INSTDIR"

SectionEnd
