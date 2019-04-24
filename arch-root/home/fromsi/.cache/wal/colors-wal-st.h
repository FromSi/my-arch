const char *colorname[] = {

  /* 8 normal colors */
  [0] = "#0e0f0f", /* black   */
  [1] = "#6A5038", /* red     */
  [2] = "#695146", /* green   */
  [3] = "#8B663B", /* yellow  */
  [4] = "#986D54", /* blue    */
  [5] = "#768143", /* magenta */
  [6] = "#B28A64", /* cyan    */
  [7] = "#dcc4a9", /* white   */

  /* 8 bright colors */
  [8]  = "#9a8976",  /* black   */
  [9]  = "#6A5038",  /* red     */
  [10] = "#695146", /* green   */
  [11] = "#8B663B", /* yellow  */
  [12] = "#986D54", /* blue    */
  [13] = "#768143", /* magenta */
  [14] = "#B28A64", /* cyan    */
  [15] = "#dcc4a9", /* white   */

  /* special colors */
  [256] = "#0e0f0f", /* background */
  [257] = "#dcc4a9", /* foreground */
  [258] = "#dcc4a9",     /* cursor */
};

/* Default colors (colorname index)
 * foreground, background, cursor */
 unsigned int defaultbg = 0;
 unsigned int defaultfg = 257;
 unsigned int defaultcs = 258;
 unsigned int defaultrcs= 258;
