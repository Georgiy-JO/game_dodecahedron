#pragma once

#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QMainWindow>

/**
 * @namespace GridConstants
 * @brief Contains, enumerations, utility classes and functions for grid of the
 * scene rendering.
 */
namespace GridConstants {

/**
 * @enum PixelSize_c
 * @brief Enum representing possible pixel/block/cell sizes for the grid items.
 */
enum PixelSize_c { ps_Small = 20, ps_Medium = 25, ps_Big = 60 };

/**
 * @enum ItemKind_c
 * @brief Enum representing the kind of item to be displayed in the grid.
 * @note Some items will only be used it future Github project versions.
 */
enum ItemKind_c {
  ik_Unknown = -1,  ///< Undefined item type.
  ik_Square = 0,    ///< Square item.
  ik_Circle = 1,    ///< Circle item.
  ik_Cross = 2,     ///< Cross item (unused here).
  ik_Ring = 3       ///< Ring item (unused here).
};

/**
 * @class Colors_c
 * @brief Utility class for managing colors of items of the grid and scene.
 */
class Colors_c {
 private:
  static constexpr int color_number =
      12;  ///< Total number of colors in the palette.
  static const QColor
      color_table[color_number];  ///< Array of predefined colors (can be found
                                  ///< in Colors_c.tpp).

 public:
  /**
   * @enum Numeration
   * @brief Enum for named color indices used in the color table.
   */
  enum Numeration {
    cl_BackGround = 0,  ///< Background color.
    cl_First,
    cl_Second,
    cl_Third,
    cl_Fourth,
    cl_Fifth,
    cl_Default = 10,  ///< Default color fallback.
    cl_GridEdge = 11  ///< Edge/border color.
  };

  /**
   * @brief Returns a color from the table by index.
   * @param index Index in the color table.
   * @return Corresponding QColor.
   */
  inline static QColor color(int index);

  /**
   * @brief Returns the color enum number for a given QColor.
   * @param color The QColor to check.
   * @return Numeration enum value matching the color.
   */
  inline static Numeration number(QColor color);
};

/**
 * @brief Keeps defenitions of functions of Colors_c and color_table.
 */
#include "Colors_c.tpp"

}  // namespace GridConstants

/**
 * @class GridScene_
 * @brief Represents a 2D graphics grid scene for displaying game fields.
 */
class GridScene_ {
 private:
  QGraphicsScene* scene;  ///< Qt graphics scene that renders items.
  int gr_width = 0, gr_height = 0,
      pixel_size = 0;               ///< Grid dimensions and cell size.
  QGraphicsItem*** grid = nullptr;  ///< 2D array of grid items.

  /**
   * @brief Deletes the current grid and frees memory.
   */
  void deleteGrid();
  /**
   * @brief Allocates memory for the grid based on dimensions.
   */
  void allocateGrid();

  /**
   * @brief Sets a background item at the specified grid position.
   * @param x X-coordinate in the grid.
   * @param y Y-coordinate in the grid.
   */
  void setBackGroundItem(int x, int y) noexcept;
  /**
   * @brief Sets a square item at the specified grid position.
   * @param x X-coordinate in the grid.
   * @param y Y-coordinate in the grid.
   */
  void setSquareItem(int x, int y) noexcept;
  /**
   * @brief Sets a circle item at the specified grid position.
   * @param x X-coordinate in the grid.
   * @param y Y-coordinate in the grid.
   */
  void setCircleItem(int x, int y) noexcept;

 public:
  /**
   * @brief Constructor for GridScene_ with parent.
   * @param parent Pointer to the parent QMainWindow.
   */
  GridScene_(QMainWindow* parent);
  /**
   * @brief Constructor with explicit dimensions and pixel size.
   * @param parent Pointer to the parent QMainWindow.
   * @param grid_width Grid width in cells.
   * @param grid_height Grid height in cells.
   * @param pixel Cell/Pixel size from PixelSize_c.
   */
  GridScene_(QMainWindow* parent, int grid_width, int grid_height,
             GridConstants::PixelSize_c pixel);
  /**
   * @brief Destructor. Cleans up grid resources.
   */
  ~GridScene_();

  /**
   * @brief Initializes the scene with specified dimensions and pixel size.
   * @param grid_width Width in grid cells.
   * @param grid_height Height in grid cells.
   * @param pixel Pixel size enum.
   */
  void setupScene(int grid_width, int grid_height,
                  GridConstants::PixelSize_c pixel);
  /**
   * @brief Clears and deletes the scene.
   */
  void cleanScene();

  /**
   * @brief Verifies the existence of an item at (x, y).
   * @param x X-coordinate.
   * @param y Y-coordinate.
   */
  void gridItemCheck(int x, int y) const;

  /**
   * @brief Gets the size of each pixel/cell.
   * @return Pixel size in pixels.
   */
  int getPixelSize() const;
  /**
   * @brief Gets the width of the grid.
   * @return Number of columns.
   */
  int getWidth() const;
  /**
   * @brief Gets the height of the grid.
   * @return Number of rows.
   */
  int getHeight() const;
  /**
   * @brief Returns a pointer to the internal QGraphicsScene.
   * @return Pointer to QGraphicsScene.
   */
  const QGraphicsScene* getScene();
  /**
   * @brief Overloaded operator to access item at (x, y).
   * @param x X-coordinate.
   * @param y Y-coordinate.
   * @return Pointer to the QGraphicsItem.
   */
  QGraphicsItem* operator()(int x, int y);
  /**
   * @brief Gets the QColor of an item at (x, y).
   * @param x X-coordinate.
   * @param y Y-coordinate.
   * @return The QColor of the item.
   */
  QColor getItemColorQt(int x, int y) const;
  /**
   * @brief Gets the item type at (x, y).
   * @param x X-coordinate.
   * @param y Y-coordinate.
   * @return The kind of item.
   */
  GridConstants::ItemKind_c getItemKind(int x, int y) const;

  /**
   * @brief Checks if the item at (x, y) is background.
   * @param x X-coordinate.
   * @param y Y-coordinate.
   * @return True if it's a background item.
   */
  bool isItemBackGround(int x, int y) const;
  /**
   * @brief Checks if the item is a square.
   * @param x X-coordinate.
   * @param y Y-coordinate.
   * @return True if item is a square.
   */
  bool isItemSquare(int x, int y) const;
  /**
   * @brief Checks if the item is a circle.
   * @param x X-coordinate.
   * @param y Y-coordinate.
   * @return True if item is a circle.
   */
  bool isItemCircle(int x, int y) const;

  /**
   * @brief Cleans (set it background) an item at the given position.
   * @param x X-coordinate.
   * @param y Y-coordinate.
   */
  void cleanItem(int x, int y);
  /**
   * @brief Sets an item's color (main color not edge color).
   * @param x X-coordinate.
   * @param y Y-coordinate.
   * @param color The color to set.
   */
  void setItemColor(int x, int y, QColor color);
  /**
   * @brief Converts an item into a square.
   * @param x X-coordinate.
   * @param y Y-coordinate.
   */
  void setItemSquare(int x, int y);
  /**
   * @brief Converts an item into a circle.
   * @param x X-coordinate.
   * @param y Y-coordinate.
   */
  void setItemCircle(int x, int y);

  /**
   * @note for 2 following functions (setItem(...) and getItemCode(...)):
   * Item code system:
   * How it will work in future versions:
   * item_code is a number from 0 to 39 passed from the game library to UI.
   * item_code is used to determine the type of item and it's color.
   * It is set separately for every element of the fame field matrix.
   * Dozens determin the type of the item, units - colors.
   * How it works now:
   * item_code is a number from 0 to 9 passed from the game library to UI.
   * It is used to determine the type of the item.
   * It is set separately for every element of the fame field matrix.
   * 0 - empty square cell, 1 - square with color #1, 2 - circle with color #2,
   * 3 - color #3 circle.
   */
  /**
   * @brief Sets an item using a coded integer of this particular item from the
   * game library.
   * @param x X-coordinate.
   * @param y Y-coordinate.
   * @param item_code Encoded item type and color.
   */
  void setItem(int x, int y, int item_code);

  /**
   * @brief Gets the encoded item code of an item.
   * @param x X-coordinate.
   * @param y Y-coordinate.
   * @return Encoded item code.
   */
  int getItemCode(int x, int y) const;
};

/**
 * @brief Converts a relative pixel size index from the game library to a
 * PixelSize_c enum.
 * @param relativeSize_from_gameLib Integer size indicator from the game.
 * @return Corresponding PixelSize_c enum value.
 */
GridConstants::PixelSize_c pixelSizeDecoder(
    const int relativeSize_from_gameLib);