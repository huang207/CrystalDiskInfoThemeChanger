# CrystalDiskInfoThemeChanger

A simple CLI tool to change [CrystalDiskInfo](https://github.com/hiyohiyo/CrystalDiskInfo)'s theme.

You can use with software like [Auto Dark Mode](https://github.com/AutoDarkMode/Windows-Auto-Night-Mode) to change theme automatically.

## Usage

Place `CdiTC.exe` to the installation directory of CrystalDiskInfo.

### Use with theme name only

```bash
CdiTC.exe ShizukuDark~TenmuShinryuusai
```

### Use with PRODUCT_VERSION and PRODUCT_EDITION

> [Definition](https://github.com/hiyohiyo/CrystalDiskInfo/blob/master/Library/stdafx.h).

```bash
CdiTC.exe 9.8.0 "Shizuku Edition x64" ShizukuDark~TenmuShinryuusai
```

### Use with specific window title

> [windowTitle Format](https://github.com/hiyohiyo/CrystalDiskInfo/blob/63dc71793cb587a721f5ee6fa2220845eaea174f/Priscilla/MainDialogFx.cpp#L184)

```bash
CdiTC.exe " CrystalDiskInfo 9.8.0 Shizuku Edition x64" ShizukuDark~TenmuShinryuusai
```
