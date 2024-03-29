# LuaImageTool
Description: Tool for creating images to be rendered on [OpenComputers](https://github.com/MightyPirates/OpenComputers), the mod for Minecraft.\
Author: Caden Metzgus\
Created: 1/20/2019\
Platform: Windows\
![image](https://github.com/Cadexcy23/LuaImageTool/assets/51723869/caee227d-afa9-4480-a42e-d95af586f17f)

## Controls
Left Mouse - Paint pixels\
Arrows Keys - Navigate side panels\
Shift - Toggle side panel\
Enter - Activate selected button

## Canvas
The canvas is 32x32 and can be painted on with the selected color by clicking inside it.\
![Paint](https://github.com/Cadexcy23/LuaImageTool/assets/51723869/3c64f12a-c286-4452-a58b-5816cc30dfd9)

## Pallet
Used for selecting colors to paint with.\
Arrow keys will adjust your selection.\
![image](https://github.com/Cadexcy23/LuaImageTool/assets/51723869/8aadf15a-23a4-4a41-993d-cd6e8e5d56af)

## Color Picker
Used for defining the colors of your pallet.\
Arrow keys up/down will increase/decrease the value of the selected color channel, left/right to change channels.\
![image](https://github.com/Cadexcy23/LuaImageTool/assets/51723869/d5af5b1c-2469-46a5-93a3-67a94103f4b7)

## Saving/Loading
Press enter while selecting one of these buttons to activate them.\
Save will write to the file in the save folder called "save".\
Load will read from the file in the load folder called "load".\
![image](https://github.com/Cadexcy23/LuaImageTool/assets/51723869/6d5b4565-9d1a-49eb-9864-a599a22ac2f3)

## Exporting
Export will write the canvas to a plain text document in the export folder called "export". This file contains the code required to recreate the image in-game.\
In-game you should have a computer set up with a tier 3 screen and GPU.\
Create a new Lua file and include the following code at the top (middle mouse pastes from clipboard).
```lua
local component = require("component")
local gpu = component.gpu

x = 0 -- image origin
y = 0

function drawPixel(x, y, p)
  gpu.setBackground(p, true)
  gpu.set(x, y, " ")
end
```
Open the exported text document and copy the contents under the previous code.\
![image](https://github.com/Cadexcy23/LuaImageTool/assets/51723869/02d69618-65ae-4597-95fd-3c0e41812259)\
You should now be able to run the lua file on your openComputer and see the image.\
![image](https://github.com/Cadexcy23/LuaImageTool/assets/51723869/3082aa6f-c360-4599-b011-c8d316579920)



