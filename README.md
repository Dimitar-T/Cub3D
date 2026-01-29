 # Cub3D

Small Wolfenstein-style raycaster in C. Two variants: `src/` (mandatory) and `bonus_src/` (extra features).

## Build

Use the Makefile in the project root:

- Build normal: make
- Build bonus: make bonus
- Clean: make clean / make fclean / make re

Ensure MLX42 and libft are available as the Makefile expects.

## Run

./cub3D path/to/map.cub

The program parses the map, textures, and colors, then opens a window to render the scene.

## Maps

Place .cub files in a `maps/` folder. The folder may contain both valid and invalid maps. To test a single map, run the binary with that map path and check the exit code/program output for errors.

## Controls

- Movement and turning: W/A/S/D or arrow keys
- ESC to exit

(Exact bindings in moves/)

## Project layout

- src/ — mandatory implementation
- bonus_src/ — bonus implementation
- parsing/ — map and texture parsing
- ray_caster/ — rendering and raycasting
- init/, moves/, garbage_collector/ — helpers and lifecycle

## Notes

- macOS: link with MLX42 / MiniLibX as described in Makefile.
- Errors call exit routines that free tracked allocations (see garbage_collector/).
