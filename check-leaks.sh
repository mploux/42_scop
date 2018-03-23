#!/bin/bash
make re
valgrind --leak-check=full --show-leak-kinds=all --suppressions=suppr.txt ./scop data/models/monkey_t_n_uv.obj data/textures/colors.bmp
echo "-----------------------------------------------------------------"
valgrind --leak-check=full --show-leak-kinds=all --suppressions=suppr.txt ./scop data/models/monkey_n_uv.obj data/textures/colors.bmp
