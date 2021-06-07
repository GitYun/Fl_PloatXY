/*************************************************************************
*                            Fl_PlotXY.H
*
* Simple X-Y Graph Display
*************************************************************************
*               Version information see Fl_PlotXY.cxx
*************************************************************************/
#ifndef _Fl_PlotXY_H_
#define _Fl_PlotXY_H_

/*< Maximum Number of Lines per Plot */
#define FL_PLOTXY_MAXLINES 10

/*< Drawing Modes */
#define FL_PLOTXY_DOT 0
#define FL_PLOTXY_LINE 1

/*< Scale Modes */
#define FL_PLOTXY_AUTO 0
#define FL_PLOTXY_FIXED 1

/*< Zoom Modes */
#define FL_PLOTXY_ZOOMALL 0
#define FL_PLOTXY_ZOOMSELECT 1

/*< Marking Modes - OR'd together */
#define FL_PLOTXY_MARK_OFF 0x00   /*< Graduations etc OFF */
#define FL_PLOTXY_MARK_ON 0x01    /*< Show Y Graduations  */
#define FL_PLOTXY_MARK_LABEL 0x02 /*< Show Axis Label     */
#define FL_PLOTXY_MARK_VAL 0x04   /*< Show Axis Values    */
#define FL_PLOTXY_MARK_NAME 0x08  /*< Show Lines NAME     */

/*< Axis Value Types */
#define FL_PLOTXY_VAL_NUMBER 0x00   /*< Axis Value is Number */
#define FL_PLOTXY_VAL_TIMES 0x01    /*< Axis Value HH:MM:SS 0 ->3600x24 */
#define FL_PLOTXY_VAL_TIMEMS 0x02   /*< Axis Value HH:MM:SS 0 ->3600x24 */
#define FL_PLOTXY_VAL_TIMEHMS 0x03  /*< Axis Value HH:MM:SS 0 ->3600x24 */
#define FL_PLOTXY_VAL_TIMEHM 0x04   /*< Axis Value HH:MM  0 ->3600x24 */
#define FL_PLOTXY_VAL_TIMEh 0x05    /*< hh       */
#define FL_PLOTXY_VAL_TIMESh 0x06   /*< SS.hh    */
#define FL_PLOTXY_VAL_TIMEMSh 0x07  /*< MM:SS.hh */
#define FL_PLOTXY_VAL_TIMEHMSh 0x08 /*< Axis Value HH:MM:SS.hh 0.00 ->3600x24 */

#define FL_PLOTXY_VAL_DATE 0x80 /*< Date Format - Unused */

#include <FL/Fl_Widget.H>
#include <FL/fl_draw.H>

/*< Data Points */
typedef struct
{
    double X; /*< X-axis value of a point */
    double Y; /*< Y-axis value of a point */
} Fl_PlotXY_Data;

/*< Line Data and Array */
typedef struct
{
    int LineNumber; /*< Line Number for this array    */
    int DrawMode;   /*< Line Drawing Mode */
    int ScaleMode;  /*< Scaling Mode */
    int Displayed;  /*< Indicate if line shown or not */

    int XMark;        /*< X GraduYLabelation Marks mode */
    int YMark;        /*< Y Graduation Marks mode */
    double XMarkSize; /*< X Graduation step size */
    double YMarkSize; /*< Y Graduation step size */

    int XValType; /* Type of data for X Axis Value */
    int YValType; /* Type of data for Y Axis Value */

    double X_Scale, Y_Scale;
    double X_Left, Y_Bottom;

    double Xmax, Ymax; /*< Maximum Axis Value for this line */
    double Xmin, Ymin; /*< Minimum Axis Value for this line */

    const char *XLabel; /*< Pointer to string for X label */
    const char *YLabel; /*< Pointer to string for Y label */

    const char *title; /*< Pointer to string array for line title */
    Fl_Color C;        /*< Line and title Colour */

    unsigned long int DataSize; /*< Number of Points in array */
    Fl_PlotXY_Data *data;       /*< Pointer to data for this line */

    char XValFormat[10]; /*< Formatter for X Value display */
    char YValFormat[10]; /*< Formatter for Y Value display */

} Fl_PlotXY_Line;

class FL_EXPORT Fl_PlotXY : public Fl_Widget
{
    Fl_PlotXY_Line LineData[FL_PLOTXY_MAXLINES]; /*< Array of line data */

    double MinX, MaxX, MinY, MaxY; /*< X and Y's minimum and maximum value */

    int PX, PY, PW, PH; /*< Plot area location */

protected:
    /**
     * @brief Drawing functions for different modes
     * @author vemagic (admin@vemagic.com)
     * @date 2021-06-07
     */
    virtual void draw();

    /**
     * @brief Calculate the plotable area
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     */
    void calc_plot_area(void);

    /**
     * @brief Plot line from XY data
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param L Line data structure object
     */
    void plot_line(Fl_PlotXY_Line *L);

    /**
     * @brief Plot dot from XY data
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param L Line data structure object
     */
    void plot_dot(Fl_PlotXY_Line *L);

    /**
     * @brief Draw X/Y axis scale
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param L Line data structure object
     */
    void draw_scales(Fl_PlotXY_Line *L);

    /**
     * @brief Draw axis label
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param L Line data structure object
     */
    void draw_axislabel(Fl_PlotXY_Line *L);

    /**
     * @brief Draw line label
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param L Line data structure object
     */
    void draw_linelabel(Fl_PlotXY_Line *L);

    /**
     * @brief Draw vertical line
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param L Line data structure object
     */
    void draw_vline(Fl_PlotXY_Line *L);

    /**
     * @brief Set up zoom scale etc for drawing
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param L Line data structure object
     */
    void setscale(Fl_PlotXY_Line *L);

    /**
     * @brief Min/Max calcute for auto scaling
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param L Line data structure object
     */
    void minmax(Fl_PlotXY_Line *L);

    /**
     * @brief Font Size to use on the Axis Markers
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     */
    int AxisFontSize;

    /**
     * @brief Font Face to use on the Axis Markers
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     */
    int AxisFontFace;

    /**
     * @brief Text Spaceing for X Axis Display
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     */
    int AxisTextSpaceX;

    /**
     * @brief Text Spaceing for Y Axis Display
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     */
    int AxisTextSpaceY;

    /**
     * @brief Gets selected graph details
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @return Fl_PlotXY_Line* 
     */
    Fl_PlotXY_Line *getselected(int);

    /* Vertical Line Options */
    int VLineEnable;            /*< Enable or Disable Line */
    int VLineSel;               /*< Display for this line */
    unsigned long int VLinePos; /*< Position in data to plot line and highlight */

public:
    /**
     * @brief Construct a new Fl_PlotXY object
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param X, Y the position of the widget relative to the enclosing window
     * @param W, H size of the widget in pixels
     * @param l optional text for the widget label
     */
    Fl_PlotXY(int X, int Y, int W, int H, const char *l = 0);

    ~Fl_PlotXY(void);

    /**
     * @brief Create a new line data set
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param Xmin, Ymax The x axis's minimum and maximum value for line
     * @param Ymin, Ymax The y axis's minimum and maximum value for line
     * @param scalemode The the scale mode
     * @arg     0: FL_PLOTXY_AUTO
     * @arg     1: FL_PLOTXY_FIXED
     * @param C The the line's color
     * @param t The the line's title
     * @return int The descripter ID to line
     */
    int newline(double Xmin, double Ymin, double Xmax, double Ymax, int scalemode, Fl_Color C, const char *t);

    /**
     * @brief Create a new line data set with default init value
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @return int The descripter ID to line
     */
    int newline(void) { return (newline(0.0, 0.0, 0.0, 0.0, FL_PLOTXY_AUTO, FL_BLACK, "")); };

    /**
   * @brief Add data to selected line
   * @author vemagic (adming@vemagic.com)
   * @date 2021-06-07
   * @param line The seleted line ID
   * @param X The x axis's data for drawing
   * @param Y The y axis's data for drawing
   * @return int 0 - failed, 1 - success
   */
    int add(int line, double X, double Y);

    /**
     * @brief Set lines range
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param line The seleted line ID
     * @param Xmin, Ymax The x axis's minimum and maximum value for line
     * @param Ymin, Ymax The y axis's minimum and maximum value for line
     * @return int 0 - Failed, 1 - Success
     */
    int setrange(int line, double Xmin, double Ymin, double Xmax, double Ymax);

    /**
     * @brief Get range from current mode
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param line The seleted line ID
     * @param Xmin, Xmax The x axis's minimum and maximum value for line
     * @param Ymin, Ymax The y axis's minimum and maximum value for line
     * @return int 0 - Failed, 1 - Success
     */
    int getrange(int line, double *Xmin, double *Ymin, double *Xmax, double *Ymax);

    /**
     * @brief Set line color
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param line The seleted line ID
     * @param C The color want to set
     * @return int 0 - Failed, 1 - Success
     */
    int linecolor(int line, Fl_Color C);

    /**
     * @brief Get line color
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param line The seleted line ID
     * @return Fl_Color The line color
     */
    Fl_Color linecolor(int line);

    /**
     * @brief Set the scale mode - Auto or manual
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param line The seleted line ID
     * @param mode The scale mode
     * @arg     0: FL_PLOTXY_AUTO
     * @arg     1: FL_PLOTXY_FIXED
     * @return int 0 - Failed, 1 - Success
     */
    int scalemode(int line, int mode);

    /**
     * @brief Set dot/line drawing mode
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param line The seleted line ID
     * @param mode The drawing mode
     * @arg     0: FL_PLOTXY_DOT
     * @arg     1: FL_PLOTXY_LINE
     * @return int 0 - Failed, 1 - Success
     */
    int drawmode(int line, int mode);

    /**
     * @brief Clear the lines data
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param line The seleted line ID
     */
    void clear(int line);

    /**
     * @brief Clear all lines data
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     */
    void clearall(void);

    /**
     * @brief Remove individual line
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param line The seleted line ID
     */
    void remove(int line);

    /**
     * @brief Remove all lines
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     */
    void removeall(void);

    /**
     * @brief Change value of a point
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param line The seleted line ID
     * @param p The index of the point in the internal data array
     * @param X The x axis's new data for the `p' point
     * @param Y The y axis's new data for the `p' point
     * @return int 0 - Failed, 1 - Success
     */
    int change(int line, unsigned long int p, double X, double Y);

    /**
     * @brief Read value of a point
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param line The seleted line ID
     * @param p The index of the point in the internal data array
     * @param X The x axis's data of the `p' point
     * @param Y The y axis's data of the `p' point
     * @return int 0 - Failed, 1 - Success
     */
    int read(int line, unsigned long int p, double *X, double *Y);

    /**
     * @brief Gets current data array size of line
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param line The seleted line ID
     * @return unsigned long int The current data array size of line
     */
    unsigned long int datasize(int line);

    /**
     * @brief Load a file into the graph
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param FileName The file name with full path
     * @return int If success, return the new line ID, or -1
     * @ntoe Loads Comma Separated Value (CSV) File from Disk
     *       Data MUST be arranged as X,Y
     *       Any NON Numerical data is Not added to the graph.
     */
    int load(const char *FileName);

    /**
     * @brief Load graph data X,Y,Y,Y...
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param Filename The file name with full path
     * @return int 0: Failed, 1: Success
     * @note Load using first column as X and remaining columns as Y data
     *       This scans for the Maximum number of Y columns
     *       First Row is treated as titles for each Axis
     * NOTE: This will Clear ALL data before Loading.
     */
    int loadxyyy(const char *Filename);

    /**
     * @brief Save graph to CSV format file
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param line The seleted line ID
     * @param FileName The file name with full path and .csv suffix
     * @return int 0 - Failed, 1 - Success
     */
    int save(int line, const char *FileName); 

    /**
     * @brief Save Graph data as X,Y,Y,Y..
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param Filename The file name with full path and .csv suffix
     * @return int 0 - Failed, 1 - Success
     * @note Save using first column as X and remaining columns as Y data
     *       This scans for the Maximum number of Y columns
     *       First Row is titles for each Axis
     */
    int savexyyy(const char *Filename);

    /**
     * @brief Indicates if line number used
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param line The seleted line ID
     * @return int 0 - Failed, 1 - Success
     */
    int used(int line);

    /**
     * @brief Show the selected line
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param line The seleted line ID
     * @return int 0 - Failed, 1 - Success
     */
    int lineshow(int line);

    /**
     * @brief Hide the selected line
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param line The seleted line ID
     * @return int 0 - Failed, 1 - Success
     */
    int linehide(int line);

    /**
     * @brief Check if line is currently visible
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param line The seleted line ID
     * @return int 0 : hide, 1 : visible
     */
    int linevisible(int line);

    /**
     * @brief Set the line title
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param line The seleted line ID
     * @param title The line title
     * @return int 0 : hide, 1 : visible
     */
    int linetitle(int line, const char *title);

    /**
     * @brief Gets the line title
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param line The seleted line ID
     * @return const char* The pointer to character array
     */
    const char *linetitle(int line);

    /**
     * @brief check if X marks are On or Off
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param line The seleted line ID
     * @return int If success, return X marks or -1(no the ID for the line)
     */
    int xmarkon(int line);

    /**
     * @brief Turn X marks on or Off
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param line The seleted line ID
     * @param mode The marking mode (OR'd together):
     * @arg     0x00: FL_PLOTXY_MARK_OFF
     * @arg     0x01: FL_PLOTXY_MARK_ON
     * @arg     0x02: FL_PLOTXY_MARK_LABEL
     * @arg     0x04: FL_PLOTXY_MARK_VAL
     * @arg     0x08: FL_PLOTXY_MARK_NAME
     * @return int 0 - Failed, 1 - Success
     */
    int xmarkon(int line, int mode);

    /**
     * @brief Set the X mark step size
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param line The seleted line ID
     * @param size The X mark step size
     * @return int 0 - Failed, 1 - Success
     */
    int xmarkstep(int line, double size);

    /**
     * @brief Set the x axis's label
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param line The seleted line ID
     * @param xlabel The pointer to the character array
     * @return int 0 - Failed, 1 - Success
     */
    int xmarklabel(int line, const char *xlabel);

    /**
     * @brief Gets the x axis's label
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param line The seleted line ID
     * @return const char* The pointer to the character array
     */
    const char *xmarklabel(int line);       /*            */

    /**
     * @brief ymarkon Check if Y marks are On or Off
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param line The seleted line ID
     * @return int If success, return Y marks, or -1(no the ID for the line)
     */
    int ymarkon(int line);

    /**
     * @brief Turn Y marks on or Off
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param line The seleted line ID
     * @param mode The marking mode (OR'd together):
     * @arg     0x00: FL_PLOTXY_MARK_OFF
     * @arg     0x01: FL_PLOTXY_MARK_ON
     * @arg     0x02: FL_PLOTXY_MARK_LABEL
     * @arg     0x04: FL_PLOTXY_MARK_VAL
     * @arg     0x08: FL_PLOTXY_MARK_NAME
     * @return int 0 - Failed, 1 - Success
     */
    int ymarkon(int line, int mode);

    /**
     * @brief Set the Y mark step size
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param line The seleted line ID
     * @param size The Y mark step size
     * @return int 0 - Failed, 1 - Success
     */
    int ymarkstep(int line, double size);

    /**
     * @brief The y axis's label
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param line The seleted line ID
     * @param ylabel The pointer to the character array
     * @return int 0 - Failed, 1 - Success
     */
    int ymarklabel(int line, const char *ylabel);

    /**
     * @brief Gets the y axis's label
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param line The seleted line ID
     * @return const char* The pointer to the character array
     */
    const char *ymarklabel(int line);

    /**
     * @brief Set for X axis's value type
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param line The seleted line ID
     * @param type The type of data for x axis's value:
     * @arg     0x00: FL_PLOTXY_VAL_NUMBER
     * @arg     0x01: FL_PLOTXY_VAL_TIMES
     * @arg     0x02: FL_PLOTXY_VAL_TIMEMS
     * @arg     0x03: FL_PLOTXY_VAL_TIMEHMS
     * @arg     0x04: FL_PLOTXY_VAL_TIMEHM
     * @arg     0x05: FL_PLOTXY_VAL_TIMEh
     * @arg     0x06: FL_PLOTXY_VAL_TIMESh
     * @arg     0x07: FL_PLOTXY_VAL_TIMEMSh
     * @arg     0x08: FL_PLOTXY_VAL_TIMEHMSh
     * @arg     0x80: FL_PLOTXY_VAL_DATE (Date Format, unused)
     * @return int 0 - Failed, 1 - Success
     */
    int xvaltype(int line, int type);

    /**
     * @brief Gets X axis's value type
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param line The seleted line ID
     * @return int If success, return X axis's value type @see xvaltype, or -1(no the ID for the line)
     */
    int xvaltype(int line);

    /**
     * @brief Set the Y axis's value type (time, data etc)
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param line The seleted line ID
     * @param type The type of data for y axis's value:
     * @arg     0x00: FL_PLOTXY_VAL_NUMBER
     * @arg     0x01: FL_PLOTXY_VAL_TIMES
     * @arg     0x02: FL_PLOTXY_VAL_TIMEMS
     * @arg     0x03: FL_PLOTXY_VAL_TIMEHMS
     * @arg     0x04: FL_PLOTXY_VAL_TIMEHM
     * @arg     0x05: FL_PLOTXY_VAL_TIMEh
     * @arg     0x06: FL_PLOTXY_VAL_TIMESh
     * @arg     0x07: FL_PLOTXY_VAL_TIMEMSh
     * @arg     0x08: FL_PLOTXY_VAL_TIMEHMSh
     * @arg     0x80: FL_PLOTXY_VAL_DATE (Date Format, unused)
     * @return int 0 - Failed, 1 - Success
     */
    int yvaltype(int line, int type);

    /**
     * @brief Gets type for Y axis's value
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param line The seleted line ID
     * @return int If success, return X axis's value type @see yvaltype, or -1(no the ID for the line)
     */
    int yvaltype(int line);

    /**
     * @brief Set the X value format %0whole.0pointslf
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param line The seleted line ID
     * @param whole 
     * @param points The point of the line
     * @return int 0 - Failed, 1 - Success
     */
    int xvalformat(int line, int whole, int points);

    /**
     * @brief Set the Y value format %0whole.0pointslf
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param line The seleted line ID
     * @param whole 
     * @param points 
     * @return int 0 - Failed, 1 - Success
     */
    int yvalformat(int line, int whole, int points);

    /**
     * @brief Set axis's font size
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param a The font size to use on the axis
     */
    void axisfontsize(int a) { AxisFontSize = a; };

    /**
     * @brief Gets axis's font size
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @return int Return the font size of the axis
     */
    int axisfontsize(void) { return (AxisFontSize); };

    /**
     * @brief Set axis's font face
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param f The font face to use on the axis
     */
    void axisfontface(int f) { AxisFontFace = f; };

    /**
     * @brief Gets axis's font face
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @return int Return the font face of the axis
     */
    int axisfontface(void) { return (AxisFontFace); };

    /**
     * @brief Set text space for X axis display
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param s The text space for X axis display
     */
    void axistextspacex(int s) { AxisTextSpaceX = s; };

    /**
     * @brief Gets text space for X axis display
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @return int Return text space for X axis display
     */
    int axistextspacex(void) { return (AxisTextSpaceX); };

    /**
     * @brief Set text space for Y axis display
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param s The text space for Y axis display
     */
    void axistextspacey(int s) { AxisTextSpaceY = s; };

    /**
     * @brief Gets text space for Y axis display
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @return int Return text space for Y axis display
     */
    int axistextspacey(void) { return (AxisTextSpaceY); };

    /**
     * @brief Gets Fl_PlotXY widget current version
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @return const char* The pointer to version character array
     */
    const char *version(void);

    /**
     * @brief Enable or Disable line
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param e 0: Disable vertical line,
     *          not zero: Enable vertical line
     */
    void vlineenable(int e) { VLineEnable = e; };

    /**
     * @brief Gets the vertical line enable state
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @return int 0: Disbale vertical line,
     *             not zero: Enable vertical line
     */
    int vlineenable(void) { return (VLineEnable); };

    /**
     * @brief Set the current display vertical line ID
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param l The current display vertical line ID
     */
    void vlinesel(int l) { VLineSel = l; };

    /**
     * @brief Gets the current display vertical line for drawing
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @return int The current display vertical line for drawing
     */
    int vlinesel(void) { return (VLineSel); };

    /**
     * @brief Position in data to plot line and highlight
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @param p The position in data
     */
    void vlinepos(unsigned long int p) { VLinePos = p; };

    /**
     * @brief Gets position in data to plot line and highlight
     * @author vemagic (adming@vemagic.com)
     * @date 2021-06-07
     * @return unsigned long int The position in data
     */
    unsigned long int vlinepos(void) { return (VLinePos); };
};

/******* END OF FILE ********/
#endif
