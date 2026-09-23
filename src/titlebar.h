#pragma once

#include "rayclay.h"

#include "theme.h"

#define BAR_H 46

/* macOS puts the window controls on the left; every other platform on the right.
   The title and logo take the opposite end, logo outermost. */
#if defined(__APPLE__)
#define CONTROLS_LEFT 1
#define TITLE_ALIGN   "cr"
#else
#define CONTROLS_LEFT 0
#define TITLE_ALIGN   "cl"
#endif

static void chip(const char *id, const char *svg, RC_Color hover)
{
    rcBox(.id = id, .w = "46px", .h = "grow", .align = "cc",
          .bg = rcIsHovered(id) ? hover : CLEAR) {
        rcSvg(svg, 16.0f, FG_TEXT);
    }
}

static void controls(void)
{
    rcRow(.h = "grow", .align = "cc") {
        if (CONTROLS_LEFT) {
            chip(RC_ID_WINDOW_CLOSE, ICONS "x.svg", DANGER);
            chip(RC_ID_WINDOW_MINIMIZE, ICONS "minus.svg", BG_HOVER);
            chip(RC_ID_WINDOW_MAXIMIZE,
                 rcIsWindowMaximized() ? ICONS "minimize.svg"
                                       : ICONS "maximize.svg",
                 BG_HOVER);
        } else {
            chip(RC_ID_WINDOW_MINIMIZE, ICONS "minus.svg", BG_HOVER);
            chip(RC_ID_WINDOW_MAXIMIZE,
                 rcIsWindowMaximized() ? ICONS "minimize.svg"
                                       : ICONS "maximize.svg",
                 BG_HOVER);
            chip(RC_ID_WINDOW_CLOSE, ICONS "x.svg", DANGER);
        }
    }
}

static void titlebar(const char *title)
{
    rcUnzoomed() {
        rcRow(.id = RC_ID_WINDOW_DRAG, .w = "grow", .hType = RC_PX(BAR_H),
              .bg = BG_PANEL, .align = "cl",
              /* The control cluster runs to the window edge, so the inset
                 goes on the side it is not on. */
              .pl = CONTROLS_LEFT ? 0 : 12,
              .pr = CONTROLS_LEFT ? 12 : 0) {
            if (CONTROLS_LEFT)
                controls();

            /* The title is chrome, not content, so it opts out of text
               selection the way a native title does. */
            rcRow(.w = "grow", .h = "grow", .overflow = "hidden",
                  .gap = 10, .align = TITLE_ALIGN) {
                if (CONTROLS_LEFT)
                    rcTextC(title, .color = FG_TEXT, .select = RC_SELECT_NONE);
                rcSvg(ICONS "rayclay-logo-mono.svg", 22.0f, FG_TEXT);
                if (!CONTROLS_LEFT)
                    rcTextC(title, .color = FG_TEXT, .select = RC_SELECT_NONE);
            }

            if (!CONTROLS_LEFT)
                controls();
        }
    }
}
