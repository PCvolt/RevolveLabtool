## Programming Info
- Language: C++
- Main Game Library: DX Library (wrapper for DirectX) https://dxlib.xsrv.jp/dxfunc.html
- .dat Compression method: Still unknown, devs used a tool from DX Library apparently

Source: Interview with Yorito Kasugano (BBBR developer) https://discord.com/channels/1178068657180516372/1178068658157797479/1277668546847178783

Meter Cheat Table: https://discord.com/channels/1178068657180516372/1178075878715048077/1307626292681773066

## .dat Files
The .dat files can be read with GARbro (Game Archive Resource Browser): https://github.com/morkt/GARbro

The files can be human-readable by changing the encoding to Japanese (Shift-JIS).

__.dat Files Nomenclature__
```
_xxx_vc = voice
_xxx_sce = scenario
_xxx_scr = script
_xxx_pct = sprites + graphical assets
```

If a file is missing from the .dat, the game will fetch uncompressed files in the directory, so it is possible to edit the sprites without having to recompress (nor knowing the compression method either!)

---
## Setting the game in Debug Mode
BBBR already come shipped with a debug mode that can be activated manually. From the ``cmd``, simply launch the game with arg ``-d``:
```bash
BBBR.exe -d
```

In Training Mode, these features become available:
- F1: kill player 1
- F2: kill player 2
- F3: kill both players
- F4: enable hitboxes
- F5: player info view (p1/p2)
- F6: ui debug
- F10: pause
