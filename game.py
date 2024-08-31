#!/usr/bin/env python3

import sys
from tileverse.grid import Field
from tileverse.utils import print_tile_grid

def main():
    field = Field("test field", 5)
    
    tiles = field.get_tile_grid(0, 0, 9, 9)
    
    print_tile_grid(tiles)


if __name__ == "__main__":
    main()