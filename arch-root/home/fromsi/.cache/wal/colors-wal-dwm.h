static const char norm_fg[] = "#dcc4a9";
static const char norm_bg[] = "#0e0f0f";
static const char norm_border[] = "#9a8976";

static const char sel_fg[] = "#dcc4a9";
static const char sel_bg[] = "#695146";
static const char sel_border[] = "#dcc4a9";

static const char urg_fg[] = "#dcc4a9";
static const char urg_bg[] = "#6A5038";
static const char urg_border[] = "#6A5038";

static const char *colors[][3]      = {
    /*               fg           bg         border                         */
    [SchemeNorm] = { norm_fg,     norm_bg,   norm_border }, // unfocused wins
    [SchemeSel]  = { sel_fg,      sel_bg,    sel_border },  // the focused win
    [SchemeUrg] =  { urg_fg,      urg_bg,    urg_border },
};
