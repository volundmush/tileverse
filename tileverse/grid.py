import sys
import typing
from typing import List, Optional, Tuple, Dict
from .utils import std_div


class Point:
    __slots__ = ["_x", "_y"]
    
    def __init__(self, x: int, y: int):
        self._x = x
        self._y = y

    def __add__(self, other):
        return Point(self._x + other._x, self._y + other._y)

    def __sub__(self, other):
        return Point(self._x - other._x, self._y - other._y)

    def __eq__(self, other):
        return self._x == other._x and self._y == other._y

    def __hash__(self):
        return hash((self._x, self._y))

    def __repr__(self):
        return f"Point({self._x}, {self._y})"

    def __str__(self):
        return f"({self._x}, {self._y})"

    def getX(self):
        return self._x
    
    def getY(self):
        return self._y


class Tile:
        
    def __init__(self):
        pass


class Chunk:
    tile_class = Tile
    
    __slots__ = ["_point", "_field", "_tiles"]
    
    @property
    def _chunk_size(self):
        return self._field._chunk_size
    
    def __init__(self, point: Point, field: "Field"):
        self._field = field
        self._point = point
        self._tiles: Tuple[Tuple[Tile]] = tuple(tuple(self.tile_class() for _ in range(self._chunk_size)) for _ in range(self._chunk_size))
    
    def get_tile(self, x: int, y: int) -> Optional[Tile]:
        if 0 <= x < self._chunk_size and 0 <= y < self._chunk_size:
            return self._tiles[y][x]
        return None

def std_div(x, chunk_size):
    quotient = x // chunk_size
    remainder = x % chunk_size

    # Adjust for Python's floor division when x is negative
    if x < 0 and remainder != 0:
        quotient += 1
        remainder -= chunk_size

    return quotient, remainder


class Field:
    chunk_class = Chunk
        
    __slots__ = ["_name", "_chunk_size", "_chunks"]
    
    def __init__(self, name: str, chunkSize: int):
        self._name = name
        self._chunk_size = chunkSize
        self._chunks: Dict[Point, Chunk] = {}
        self._chunks[Point(0, 0)] = self.chunk_class(Point(0, 0), self)
    
    def get_chunk(self, point: Point) -> Optional[Chunk]:
        return self._chunks.get(point, None)
    
    def get_tile(self, x: int, y: int) -> Optional[Tile]:
        # Calculate both the quotient (chunk coordinates) and remainder (tile coordinates within the chunk)
        chunkX, tileX = std_div(x, self._chunk_size)
        chunkY, tileY = std_div(y, self._chunk_size)

        if (chunk := self.get_chunk(Point(chunkX, chunkY))):
            # Calculate the center of the chunk in array coordinates
            center = self._chunk_size // 2

            # Convert Cartesian tile coordinates to array indices
            idxX = tileX + center
            idxY = tileY + center

            return chunk.get_tile(idxX, idxY)

        return None  # Return None if the chunk doesn't exist
    
    def get_tile_grid(self, x: int, y: int, width: int, height: int) -> List[List[Optional[Tile]]]:
        if width % 2 == 0 or height % 2 == 0:
            raise ValueError("Width and height must be odd.")
        
        # Create the result grid
        result: List[List[Optional[Tile]]] = []

        # Calculate the top-left corner of the desired area
        start_x = x - width // 2
        start_y = y + height // 2  # Top-left corner (start from the top)

        # Calculate the bottom-right corner
        end_x = start_x + width
        end_y = start_y - height

        # Loop over the area and fill the result grid
        for cur_y in range(start_y, end_y, -1):
            row = []
            for cur_x in range(start_x, end_x):
                tile = self.get_tile(cur_x, cur_y)
                row.append(tile)
            result.append(row)

        return result