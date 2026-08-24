#pragma once

#include "rayclay.h"

#include "theme.h"

static void sidebar(bool *open)
{
    rcColumn(.id = "Sidebar", .w = *open ? "240px" : "56px",
             .h = "grow", .bg = BG_PANEL, .p = 8, .gap = 8) {
        rcBox(.id = "Toggle", .w = "40px", .h = "40px", .align = "cc",
              .bg = rcIsHovered("Toggle") ? BG_HOVER : CLEAR) {
            rcSvg(*open ? ICONS "panel-left.svg" : ICONS "panel-right.svg",
                  18.0f, FG_TEXT);
        }
        if (rcClicked("Toggle"))
            *open = !*open;
    }
}
