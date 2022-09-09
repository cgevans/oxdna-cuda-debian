---
title: confGenerator(1) | oxDNA
date: 2022-09-15
footer: 3.4.2
---

# NAME
confGenerator - basic oxDNA configuration generator

# SYNOPSIS

| **confGenerator** \<_input\_file_\> \<_box_\> [_key_=_value_]

# DESCRIPTION

confGenerator can be used to generate simple initial configurations. 

When used to generate DNA or RNA configurations it is recommended to always set generate_consider_bonded_interactions = true in the input file.

In addition to the input file, confGenerator takes another mandatory argument whose meaning depends on its value. It specifies the simulation box if it is a single number larger than 2 (in which case the simulation box is assumed to be cubic) or if it is an x-separated triplet of numbers that specify the length of the edges of the box (which is assumed to be a cuboid). By contrast, the second mandatory argument is interpreted as a number density if it is smaller than 2.

# OPTIONS



# SEE ALSO

/usr/share/doc/oxdna-cuda/html/usage.html - full usage information.