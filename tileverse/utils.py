from typing import List, Optional

def print_tile_grid(tile_grid: List[List[Optional["Tile"]]]) -> None:
    for row in tile_grid:
        data = []
        for tile in row:
            if tile:
                data.append("T")
            else:
                data.append("E")
        print("".join(data))

def std_div(x, chunk_size):
    quotient = x // chunk_size
    remainder = x % chunk_size

    # Adjust for Python's floor division when x is negative
    if x < 0 and remainder != 0:
        quotient += 1
        remainder -= chunk_size

    return quotient, remainder