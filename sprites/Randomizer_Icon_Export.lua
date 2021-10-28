-- This script for Aseprite takes the selected layer of an 8x8 image and creates
-- data that can be used as an icon in the OoT3D randomizer's in-game menu (icons.h)
-- Because Aseprite does not allow writing to the clipboard directly via script yet,
-- the window that pops up displays a selectable text field instead, while also showing
-- a preview of what the data will look like. The user must use Ctrl+C (or Cmd+C on Mac)
-- to copy the text manually and paste it into the appropriate location in icons.h.
-- While the window is open, it is possible to select a different layer and click 'Refresh'
-- to display another sprite's data, to make it quick to export multiple sprites.

-- Number-to-binary string representation, from https://stackoverflow.com/a/9080080
local function toBits(num,bits)
    -- returns a table of bits, most significant first.
    bits = bits or math.max(1, select(2, math.frexp(num)))
    local t = {} -- will contain the bits        
    for b = bits, 1, -1 do
        t[b] = math.fmod(num, 2)
        num = math.floor((num - t[b]) / 2)
    end
    return t
end

local function closeDialog()
    if (randoExportDlg) then
        randoExportDlgBounds = randoExportDlg.bounds
        randoExportDlg:close()
    end
end

local function createDialog()
    if randoExportDlg then
        closeDialog()
        randoExportDlg = nil
    end

    local spr = app.activeSprite
    if not spr then
        app.alert("There is no sprite to export")
        return
    end
    
    -- Make sure the selected layer and the background are the only visible ones
    for i,layer in ipairs(spr.layers) do
        local setVisible = layer == spr.backgroundLayer or layer == app.activeLayer
        layer.isVisible = setVisible
    end

    -- Copy everything to a new Image
    local img = Image(spr.spec)
    img:clear()
    img:drawSprite(spr, app.activeFrame)
    
    if img.width ~= 8 then
        app.alert("Sprite width must be 8, it is " .. img.width .. "x" .. img.height)
        return
    end

    app.refresh()
    
    local dataDlg = Dialog("Randomizer Icon Data")
    randoExportDlg = dataDlg
    dataDlg:separator{ text="Data" }
    
    local iconString = ""
    iconString = iconString .. "{   /* " .. app.activeLayer.name .. " */\n"
    dataDlg:label{ text="{   /* " .. app.activeLayer.name .. " */" }
    dataDlg:newrow()
    for py = 0,(img.height - 1) do
        local total = 0
        for px = 0,7 do
            local pixel = img:getPixel(px, py)
            if (pixel ~= 0) then
                total = total | (1 << (7 - px))
            end
        end
        local lineString = string.format("    0x%02x, /* %s */", total, table.concat(toBits(total, 8)))
        iconString = iconString .. lineString .. "\n"
        if (img.height > 16 and py == 15) then
            dataDlg:label{ text="    (" .. img.height - 16 .. " more lines)" }
            dataDlg:newrow()
        elseif (py <= 7) then
            dataDlg:label{ text=lineString }
            dataDlg:newrow()
        end
    end
    iconString = iconString .. "}"
    dataDlg.data = iconString
    dataDlg:label{ text="}" }
    
    -- No clipboard access from scripts in Aseprite yet, create an entry field the user can copy from
    dataDlg:entry{ text=iconString }
    
    dataDlg:separator()
    dataDlg:button{ text="&Close",onclick=function() closeDialog() end }
    dataDlg:button{ text="&Refresh",onclick=function() createDialog() end }
    
    dataDlg:show{ wait=false }
    if (randoExportDlgBounds) then
        dataDlg.bounds = randoExportDlgBounds
    end
end

createDialog()