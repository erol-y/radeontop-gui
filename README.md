RadeonTop
=========

View your GPU utilization, both for the total activity percent and individual blocks.

Requires access to /dev/dri/cardN files or /dev/mem (root privileges).

Supported cards
---------------

R600 and up, even Southern Islands should work fine.
Works with both the open drivers and AMD Catalyst.

The total GPU utilization is also valid for OpenCL loads; the other blocks
are only useful in GL loads.


Graphical User Interface
========================

This is GUI with extended features.
Query window (beta): See gpu internal values.
CPU window: CPUs frequencies, realtime or avarage with reduced frequency.

GUI contains wxWidgets libraries.
Code::Blocks and wxFormBuilder are used to build the project.
