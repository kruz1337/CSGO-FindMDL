# FindMDL Hook
This repository has a internal model changer with FindMDL Hook for Counter-Strike: Global Offensive game. It's fully open source and loadable into the game as a [Dynamic-link library (DLL)](https://en.wikipedia.org/wiki/Dynamic-link_library)

![](https://img.shields.io/badge/language-c++-e76089?style=plastic) ![](https://img.shields.io/badge/game-csgo-yellow?style=plastic) ![](https://img.shields.io/badge/license-GNU-green?style=plastic) ![](https://img.shields.io/badge/arch-x86-d9654f?style=plastic)

![Image of RequestX International Developer Group on Discord](https://raw.githubusercontent.com/Kruziikrel1/CSGO-AIP/main/thumbnail.png)

## How to build FindMDL Hook Project files?
* First of all you should download project files on project page or clone this repository from GitBash or GitHub Desktop on your PC. [FindMDL.zip](https://github.com/Kruziikrel1/CSGO-FindMDL)

* If you download project files with manual method you need extract zip file.

* Run .sln file on Visual Studio (2019+).

* Change build configuration to Debug | x86 and press Build button or press <kbd>CTRL+B</kbd> on your keyboard.

* Check out bin folder include that.

* Go to the bottom heading to add your custom models.

* That's all, enjoy it :)

<br/>

## How to add your custom model?
* First go to "Hooks.cpp" in Source Files.

* Then go to hkFindMDL below the "Custom Models" comment line.

* Paste this code and read comment lines in this code.
```c++
if (strstr(FilePath, "v_.mdl"))  //v_: Name of the model to change
{
	sprintf(FilePath, "models/weapons/v_new_.mdl"); //v_new_: Name of the changing custom model: 
}
```
