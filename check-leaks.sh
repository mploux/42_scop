#!/bin/bash
valgrind --leak-check=full --show-leak-kinds=all --suppressions=suppr.txt ./scop data/models/monkey_t_n_uv.obj data/textures/colors.bmp
